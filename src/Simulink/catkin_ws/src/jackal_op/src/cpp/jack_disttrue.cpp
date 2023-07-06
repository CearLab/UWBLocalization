// node creating and publishing the true distances
#include "MelodicAPI.hpp"

// service for ground truth
#include <gazebo_msgs/LinkStates.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/GetModelState.h>

// Messages for getting model and link poses
geometry_msgs::Pose model_pose;

void DummyCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("ARARMAX");
}

int getIndex(std::vector<std::string> v, std::string value)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i].compare(value) == 0)
            return i;
    }
    return -1;
}

void model_states_callback(gazebo_msgs::ModelStates model_states)
{
    int ball_model_index = getIndex(model_states.name, "jackal");
    model_pose = model_states.pose[ball_model_index];
}

/**
 * Node used to get distance measurements from UWB plugin and divide them into the related anchors and tags
 */
int main(int argc, char **argv)
{
    /**
     * ros::init() the node
     */
    ros::init(argc, argv, "jack_disttrue");

    /**
     * define nodehandle instance (general purpose)
     */
    ros::NodeHandle np;

    // general stuff
    int cnt = 0;
    int rate = 5;
    int tagID = 7;
    int i;
    bool isFramePresent;

    std::string ID;
    std::string child, base;

    // get tagID - default 7
    if (argc > 1){
        std::string value_from_cl = argv[1];
        ID = value_from_cl.c_str();
    }
    else{
        ID = "MeshTrue";
    }

    if (argc > 2){
        std::string value_from_cl = argv[2];
        tagID = atoi(value_from_cl.c_str());
    }

    ROS_WARN("ID %s", ID.c_str());

    // check params
    std::string tmp;
    std::vector<bool> flags;
    tmp = "/" + ID + "/jack_disttrue_subA";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_disttrue_subOdom";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_disttrue_pubDist";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_disttrue_pubAnchors";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/DistjackAPIName";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/NanchorMesh";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/Ntags";
    flags.push_back(np.hasParam(tmp));

    // init rate for the node
    tmp = "/" + ID + "/UWBrate";
    if (np.hasParam(tmp)){
        np.getParam(tmp, rate);
    }
    ros::Rate loop_rate(rate);

    /**
     * define topic to subscribe to. Get the topics name from params server. 
     * Then create handle for subscribing.
     */
    std::string subNameA, subNameOdom, pubNameDist, pubNameAnchors, jackName;
    int Nanchors, Ntags;

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (std::all_of(std::begin(flags), std::end(flags),[](bool b){return b;})) {

        // params found
        ROS_INFO("Params found");

        // get topics and init data
        tmp = "/" + ID + "/jack_disttrue_subA";
        np.getParam(tmp, subNameA);  
        tmp = "/" + ID + "/jack_disttrue_subOdom";
        np.getParam(tmp, subNameOdom);  
        tmp = "/" + ID + "/jack_disttrue_pubDist";
        np.getParam(tmp, pubNameDist);  
        tmp = "/" + ID + "/jack_disttrue_pubAnchors";
        np.getParam(tmp, pubNameAnchors);  
        tmp = "/" + ID + "/DistjackAPIName";
        np.getParam(tmp, jackName);  
        tmp = "/" + ID + "/NanchorMesh";
        np.getParam(tmp, Nanchors);
        tmp = "/" + ID + "/Ntags";
        np.getParam(tmp, Ntags);  

        // init buffer and listener
        static tf2_ros::Buffer tfBuffer; // problem line
        tf2_ros::TransformListener tfListener(tfBuffer);

        // instance of a class - tagID 7 
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID, Ntags, rate);
        ROS_INFO("jackAPI - Class instance created");

        // subscribe
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);
        jackNode._jack_disthandle_ST = np.subscribe(subNameOdom, 1000, &jackAPI::ChatterCallbackDtrue, &jackNode);
        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<gtec_msgs::Ranging>(pubNameDist, 1000);
        jackNode._jack_disthandle_PA = np.advertise<visualization_msgs::MarkerArray>(pubNameAnchors, 1000);

        // timer callaback for publishing anchors
        ros::Timer TimerAnchors = np.createTimer(ros::Duration(1.0), &jackAPI::ChatterCallbackAtrue, &jackNode);

        // code to publish the ground truth taking it from gazebo
        // Service client for getting model poses
        ros::ServiceClient get_model_state_client;

        // Create suvsvribers for Gazebo model and link states
        ros::Subscriber model_states_subscriber = np.subscribe("/gazebo/model_states", 100, model_states_callback);
        ros::Publisher ground_truth_publisher = np.advertise<nav_msgs::Odometry>("/ground_truth/state", 1000);
        nav_msgs::Odometry ground_truth;

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {

            //spin
            ros::spinOnce();

            // get transform
            if (tagID >= 0){
                try{
                    
                    jackNode.GetFrames(child, base, tagID);
                    isFramePresent = (tfBuffer._frameExists(child) && tfBuffer._frameExists(base));
                    if (isFramePresent){
                        jackNode._transformStamped.transforms[tagID] = tfBuffer.lookupTransform(base,child,ros::Time(0));
                    }

                    // wanna see the transformation?
                    // ROS_INFO("Trasl: %g %g %g", 
                    // jackNode._transformStamped.transforms[0].transform.translation.x,
                    // jackNode._transformStamped.transforms[0].transform.translation.y,
                    // jackNode._transformStamped.transforms[0].transform.translation.z);
                }
                catch (tf2::TransformException &ex) {
                    ROS_WARN("ARARMAX DISTTRUE: %s",ex.what());
                }
            }

            // show the ground truth
            // ROS_WARN("GT: %g %g %g", model_pose.position.x, model_pose.position.y, model_pose.position.z);
            // ground_truth.header.seq += ground_truth.header.seq;
            // ground_truth.header.stamp = ros::Time::now();
            // ground_truth.header.frame_id = "world";
            // ground_truth.child_frame_id = "base_link";
            // ground_truth.pose.pose.position.x = model_pose.position.x;
            // ground_truth.pose.pose.position.y = model_pose.position.y;
            // ground_truth.pose.pose.position.z = model_pose.position.z;
            // ground_truth.pose.pose.orientation.w = model_pose.orientation.w;
            // ground_truth.pose.pose.orientation.x = model_pose.orientation.x;
            // ground_truth.pose.pose.orientation.y = model_pose.orientation.y;
            // ground_truth.pose.pose.orientation.z = model_pose.orientation.z;
            // ground_truth_publisher.publish(ground_truth);

            // sleep
            loop_rate.sleep();
            ++cnt;
        }
                
        return 0;

    }
    else {

        // throw error
        ROS_ERROR("Params not found for jackal_op - jack_disttrue");
        return -1;
      
    }
}