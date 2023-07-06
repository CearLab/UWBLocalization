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
    ros::init(argc, argv, "jack_hybobs_centralized");

    /**
     * define nodehandle instance (general purpose)
     */
    ros::NodeHandle np;

    // general stuff
    int cnt = 0;
    int rate = 100;
    int tagID = 5;
    bool isFramePresent;
    std::string ID;

    // get tagID - default 5
    if (argc > 1){
        std::string value_from_cl = argv[1];
        ID = value_from_cl.c_str();
    }
    else{
        ID = "HybObs";
    }

    if (argc > 2){
        std::string value_from_cl = argv[2];
        tagID = atoi(value_from_cl.c_str());
    }

    ROS_INFO("ID %d", tagID);

    /**
     * define topic to subscribe to. Get the topics name from params server. 
     * Then create handle for subscribing.
     */
    std::string subNameIMU, subNameOdom, pubNameOdom, pubNameIMU, pubNameBias, jackName;
    int Nanchors, Ntags; 

    // check params
    std::string tmp;
    std::vector<bool> flags;
    tmp = "/" + ID + "/jack_hybobs_subIMU";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_hybobs_subOdom";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_hybobs_pubOdom";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_hybobs_pubIMU";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/jack_hybobs_pubBias";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/DistjackAPIName";
    flags.push_back(np.hasParam(tmp));
    tmp = "/" + ID + "/NanchorMesh";
    flags.push_back(np.hasParam(tmp));
    tmp = "/DT" + std::to_string(tagID) + "/Ntags";
    flags.push_back(np.hasParam(tmp));

    // init rate for the node
    tmp = "/" + ID + "/HYBrate";
    if (np.hasParam(tmp)){
        np.getParam(tmp, rate);
    }
    ros::Rate loop_rate(rate);

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (std::all_of(std::begin(flags), std::end(flags),[](bool b){return b;})) {

        // params found
        ROS_WARN("Params found");

        // get topics and init data
        tmp = "/" + ID + "/jack_hybobs_subIMU";
        np.getParam(tmp, subNameIMU);  
        tmp = "/" + ID + "/jack_hybobs_subOdom";
        np.getParam(tmp, subNameOdom);  
        tmp = "/" + ID + "/jack_hybobs_pubOdom";
        np.getParam(tmp, pubNameOdom);  
        tmp = "/" + ID + "/jack_hybobs_pubIMU";
        np.getParam(tmp, pubNameIMU); 
        tmp = "/" + ID + "/jack_hybobs_pubBias";
        np.getParam(tmp, pubNameBias);  
        tmp = "/" + ID + "/DistjackAPIName";
        np.getParam(tmp, jackName);  
        tmp = "/" + ID + "/NanchorMesh";
        np.getParam(tmp, Nanchors); 
        tmp = "/DT" + std::to_string(tagID) + "/Ntags";
        np.getParam(tmp, Ntags);  

        // instance of a class - tagID 7 
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID, Ntags, rate);
        ROS_WARN("jackAPI - Class instance created");

        // init buffer and listener
        static tf2_ros::Buffer tfBuffer; // problem line
        tf2_ros::TransformListener tfListener(tfBuffer);

        // subscribe
        jackNode._jack_disthandle_SIMU = np.subscribe(subNameIMU, 1000, &jackAPI::ChatterCallbackHybCont, &jackNode);
        jackNode._jack_disthandle_SJump = np.subscribe(subNameOdom, 1000, &jackAPI::ChatterCallbackHybJump, &jackNode);
        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_odometry_P = np.advertise<nav_msgs::Odometry>(pubNameOdom, 1000);
        jackNode._jack_IMU_P = np.advertise<sensor_msgs::Imu>(pubNameIMU, 1000);
        jackNode._jack_Bias_P = np.advertise<sensor_msgs::Imu>(pubNameBias, 1000);

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {

            // from odom to world
            isFramePresent = (tfBuffer._frameExists("base_link") && tfBuffer._frameExists("imu_link"));
            if (isFramePresent){
                jackNode._transformStamped.transforms[jackNode._Ntags] = tfBuffer.lookupTransform("base_link","imu_link",ros::Time(0));
            }

            //spin
            ros::spinOnce();

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