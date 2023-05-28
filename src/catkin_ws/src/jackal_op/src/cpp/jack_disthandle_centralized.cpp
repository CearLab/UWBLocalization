// node handling a single tag and doing the trilateration
#include "MelodicAPI.hpp"

// dummy calback just for test
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
    ros::init(argc, argv, "jack_disthandle_centralized");

    /**
     * define nodehandle instance (general purpose)
     */
    ros::NodeHandle np;

    // general stuff
    int cnt = 0;
    int rate = 5;
    int i;

    /**
     * define topic to subscribe to. Get the topics name from params server. Then create handle for subscribing.
     */
    std::string subNameT, subNameA, pubNameT, pubNameTril, pubNameTrilodom, jackName;  
    std::string child, base;
    std::vector<_Float64> TagDists;
    int Nanchors, Ntags, tagID;  

    // get tagID - default 7
    if (argc > 1){
        std::string value_from_cl = argv[1];
        tagID = atoi(value_from_cl.c_str());
    }
    else{
        tagID = 7;
    }

    ROS_WARN("ID received: %d", tagID);

    // check params
    std::string tmp;
    std::vector<bool> flags;
    tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_subT";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_pubDist";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/jackAPIName";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/NanchorMesh";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_subA";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_pubGrad";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/Ntags";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/TagDists";
    flags.push_back(np.hasParam(tmp));
    
    // init rate for the node
    tmp = "/DT" + std::to_string(tagID) + "/UWBrate";
    if (np.hasParam(tmp)){
        np.getParam(tmp, rate);
    }
    ros::Rate loop_rate(rate);

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (std::all_of(std::begin(flags), std::end(flags),[](bool b){return b;})) {

        // params found
        ROS_INFO("Params found");

        // get topics and init data
        std::string tmp;
        std::vector<bool> flags;
        tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_subT";
        np.getParam(tmp, subNameT);  
        tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_pubDist";
        np.getParam(tmp, pubNameT);  
        tmp = "/DT" + std::to_string(tagID) + "/jackAPIName";
        np.getParam(tmp, jackName);  
        tmp = "/DT" + std::to_string(tagID) + "/NanchorMesh";
        np.getParam(tmp, Nanchors);  
        tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_subA";
        np.getParam(tmp, subNameA);  
        tmp = "/DT" + std::to_string(tagID) + "/jack_disthandle_pubGrad";
        np.getParam(tmp, pubNameTril);
        tmp = "/DT" + std::to_string(tagID) + "/Ntags";
        np.getParam(tmp, Ntags);  
        tmp = "/DT" + std::to_string(tagID) + "/TagDists";
        np.getParam(tmp, TagDists);

        // concatenate string - odom
        pubNameTrilodom = pubNameTril + "Odom";

        // init buffer and listener
        static tf2_ros::Buffer tfBuffer; // problem line
        tf2_ros::TransformListener tfListener(tfBuffer);

        // instance of a class
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID, Ntags, TagDists, rate);
        ROS_INFO("jackAPI - Class instance created");

        // subscribe
        jackNode._jack_disthandle_ST = np.subscribe(subNameT, 1000, &jackAPI::ChatterCallbackTCentral, &jackNode);
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);

        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<jackal_op::MeshUWBCentral>(pubNameT, 1000);
        jackNode._jack_trilateration_P = np.advertise<jackal_op::GradientDescent>(pubNameTril, 1000);
        jackNode._jack_odometry_P = np.advertise<nav_msgs::Odometry>(pubNameTrilodom, 1000);    
        ROS_INFO("Publishers initialized");

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {
            
            //spin
            ros::spinOnce();

            // get transform
            if (tagID >= 0){
                try{

                    for (i=0;i<jackNode._Ntags;i++){

                        jackNode.GetFrames(child, base, i);
                        jackNode._transformStamped.transforms[i] = tfBuffer.lookupTransform(child,base,ros::Time(0));

                        // wanna see the transformation?
                        // ROS_INFO("Trasl: %g %g %g", jackNode._transformStamped.transforms[i].transform.translation.x,
                        // jackNode._transformStamped.transforms[i].transform.translation.y,
                        // jackNode._transformStamped.transforms[i].transform.translation.z);
                    }
                    
                }
                catch (tf2::TransformException &ex) {
                    ROS_WARN("ARARMAX: %s",ex.what());
                }
            }

            // sleep
            loop_rate.sleep();
            ++cnt;

        }

    }
    else {

        // throw error
        ROS_ERROR("Params not found for jackal_op - jack_disthandle - get UWB");
        return -1;
    }
}