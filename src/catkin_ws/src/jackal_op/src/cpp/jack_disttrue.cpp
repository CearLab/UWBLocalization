// node creating and publishing the true distances
#include "MelodicAPI.hpp"

void DummyCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("ARARMAX");
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
    std::string ID;

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

    ROS_INFO("ID %d", tagID);

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
    int Nanchors;

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

        // init buffer and listener
        static tf2_ros::Buffer tfBuffer; // problem line
        tf2_ros::TransformListener tfListener(tfBuffer);

        // instance of a class - tagID 7 
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID, rate);
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

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {

            //spin
            ros::spinOnce();

            // get transform
            if (tagID >= 0){
                try{
                    jackNode._transformStamped = tfBuffer.lookupTransform(jackNode._G.odom.header.frame_id,
                    jackNode._G.odom.child_frame_id,ros::Time(0));
                }
                catch (tf2::TransformException &ex) {
                    ROS_WARN("ARARMAX: %s",ex.what());
                }
            }

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