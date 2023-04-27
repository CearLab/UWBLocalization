// node creating and publishing the true distances
#include "libful.cpp"

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
    std::string ID;

    // get tagID - default 7
    if (argc > 1){
        std::string value_from_cl = argv[1];
        ID = value_from_cl.c_str();
    }
    else{
        ID = "MeshTrue";
    }

    // check params
    std::string tmp;
    std::vector<bool> flags;
    tmp = "/" + ID + "/jack_disttrue_subA";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_disttrue_subOdom";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_disttrue_pub";
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
    std::string subNameA, subNameOdom, pubName, jackName;
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
        tmp = "/" + ID + "/jack_disttrue_pub";
        np.getParam(tmp, pubName);  
        tmp = "/" + ID + "/DistjackAPIName";
        np.getParam(tmp, jackName);  
        tmp = "/" + ID + "/NanchorMesh";
        np.getParam(tmp, Nanchors);  

        // instance of a class - tagID 7 
        jackAPI jackNode = jackAPI(jackName, Nanchors, 7);
        ROS_INFO("jackAPI - Class instance created");

        // subscribe
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);
        jackNode._jack_disthandle_ST = np.subscribe(subNameOdom, 1000, &jackAPI::ChatterCallbackDtrue, &jackNode);
        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<gtec_msgs::Ranging>(pubName, 1000);

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {
            ros::spinOnce();
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