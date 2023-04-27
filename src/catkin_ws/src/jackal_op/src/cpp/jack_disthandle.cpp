// node handling a single tag and doing the trilateration
#include "libful.cpp"

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
    ros::init(argc, argv, "jack_disthandle");

    /**
     * define nodehandle instance (general purpose)
     */
    ros::NodeHandle np;

    // general stuff
    int cnt = 0;
    int rate = 5;

    // init rate for the node
    if (np.hasParam("/DT7/UWBrate")){
        np.getParam("/DT7/UWBrate", rate);
    }
    ros::Rate loop_rate(rate);

    /**
     * define topic to subscribe to. Get the topics name from params server. Then create handle for subscribing.
     */
    std::string subNameT, subNameA, pubNameT, pubNameTril, jackName, pubNameTrilodom;
    int Nanchors, tagID, GradientFlag;    

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (np.hasParam("/DT7/jack_disthandle_subT") && np.hasParam("/DT7/jack_disthandle_pubDist") && 
        np.hasParam("/DT7/jackAPIName") && np.hasParam("/DT7/NanchorMesh") &&
        np.hasParam("/DT7/jack_disthandle_subA") && np.hasParam("/DT7/jack_disthandle_pubGrad") &&
        np.hasParam("/DT7/jack_disthandle_tagID")) {

        // params found
        ROS_INFO("Params found");

        // get topics and init data
        np.getParam("/DT7/jack_disthandle_subT", subNameT);  
        np.getParam("/DT7/jack_disthandle_subA", subNameA);  
        np.getParam("/DT7/jack_disthandle_pubDist", pubNameT);
        np.getParam("/DT7/jackAPIName", jackName); 
        np.getParam("/DT7/NanchorMesh", Nanchors);  
        np.getParam("/DT7/jack_disthandle_pubGrad", pubNameTril);
        np.getParam("/DT7/jack_disthandle_tagID", tagID);

        // concatenate string - odom
        pubNameTrilodom = pubNameTril + "Odom";

        // instance of a class
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID);
        ROS_INFO("jackAPI - Class instance created");

        // set gradient flag if param is present
        if (np.hasParam("/DT7/GradientFlag")){
            np.getParam("/DT7/GradientFlag", GradientFlag);
            jackNode._GradientFlag = GradientFlag;
        }

        // subscribe
        jackNode._jack_disthandle_ST = np.subscribe(subNameT, 1000, &jackAPI::ChatterCallbackT, &jackNode);
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);

        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<jackal_op::MeshUWB>(pubNameT, 1000);
        jackNode._jack_trilateration_P = np.advertise<jackal_op::GradientDescent>(pubNameTril, 1000);
        jackNode._jack_odometry_P = np.advertise<nav_msgs::Odometry>(pubNameTrilodom, 1000);    
        ROS_INFO("Publishers initialized");

        // spin
        ROS_INFO("Spinning");

        // spin with loop rate
        while (ros::ok()) {
            ros::spinOnce();
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