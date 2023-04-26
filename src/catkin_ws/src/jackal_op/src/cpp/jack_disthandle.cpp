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
    if (np.hasParam("/UWBrate")){
        np.getParam("/UWBrate", rate);
    }
    ros::Rate loop_rate(rate);

    /**
     * define topic to subscribe to. Get the topics name from params server. Then create handle for subscribing.
     */
    std::string subNameT, subNameA, pubNameT, pubNameTril, jackName;
    int Nanchors, tagID, GradientFlag;    

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (np.hasParam("/jack_disthandle_subT") && np.hasParam("/jack_disthandle_pubDist") && 
        np.hasParam("/jackAPIName") && np.hasParam("/NanchorMesh") &&
        np.hasParam("/jack_disthandle_subA") && np.hasParam("/jack_disthandle_pubGrad") &&
        np.hasParam("/jack_disthandle_tagID")) {

        // params found
        ROS_INFO("Params found");

        // get topics and init data
        np.getParam("/jack_disthandle_subT", subNameT);  
        np.getParam("/jack_disthandle_subA", subNameA);  
        np.getParam("/jack_disthandle_pubDist", pubNameT);
        np.getParam("/jackAPIName", jackName); 
        np.getParam("/NanchorMesh", Nanchors);  
        np.getParam("/jack_disthandle_pubGrad", pubNameTril);
        np.getParam("/jack_disthandle_tagID", tagID);

        // instance of a class
        jackAPI jackNode = jackAPI(jackName, Nanchors, tagID);
        ROS_INFO("jackAPI - Class instance created");

        // set gradient flag if param is present
        if (np.hasParam("/GradientFlag")){
            np.getParam("/GradientFlag", GradientFlag);
            jackNode._GradientFlag = GradientFlag;
        }

        // subscribe
        jackNode._jack_disthandle_ST = np.subscribe(subNameT, 1000, &jackAPI::ChatterCallbackT, &jackNode);
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);

        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<jackal_op::MeshUWB>(pubNameT, 1000);
        jackNode._jack_trilateration_P = np.advertise<jackal_op::GradientDescent>(pubNameTril, 1000);    
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