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
    ros::init(argc, argv, "jack_disthandle");

    /**
     * define nodehandle instance (general purpose)
     */
    ros::NodeHandle np;

    // general stuff
    int cnt = 0;
    ros::Rate loop_rate(20);

    /**
     * define topic to subscribe to. Get the topics name from params server. Then create handle for subscribing.
     */
    std::string subNameT, subNameA, pubNameT, pubNameTril, jackName;
    int Nanchors;

    // read distances from UWB and simplify them (publish on /disthandle_pub)
    if (np.hasParam("/jack_disthandle_subT") && np.hasParam("/jack_disthandle_pub") && 
        np.hasParam("/jackAPIName") && np.hasParam("/NanchorMesh") &&
        np.hasParam("/jack_disthandle_subA")) {

        // params found
        ROS_INFO("Params found");

        // get topics and init data
        np.getParam("/jack_disthandle_subT", subNameT);  
        np.getParam("/jack_disthandle_subA", subNameA);  
        np.getParam("/jack_disthandle_pub", pubNameT);
        np.getParam("/jackAPIName", jackName); 
        np.getParam("/NanchorMesh", Nanchors);  

        // instance of a class
        jackAPI jackNode = jackAPI(jackName, Nanchors);
        ROS_INFO("jackAPI - Class instance created");

        // subscribe
        jackNode._jack_disthandle_ST = np.subscribe(subNameT, 1000, &jackAPI::ChatterCallbackT, &jackNode);
        jackNode._jack_disthandle_SA = np.subscribe(subNameA, 1000, &jackAPI::ChatterCallbackA, &jackNode);

        ROS_INFO("Subscriptions done");

        // publisher
        jackNode._jack_disthandle_P = np.advertise<jackal_op::MeshUWB>(pubNameT, 1000);

        ROS_INFO("Publisher MeshUWB initialized");

        // compute trilateration and publish odometry
        if (np.hasParam("/jack_gradient_pub")){


            np.getParam("/jack_gradient_pub", pubNameTril);
            // publisher
            jackNode._jack_trilateration_P = np.advertise<jackal_op::GradientDescent>(pubNameTril, 1000);    

            ROS_INFO("Publisher GradientDescent initialized");    

            // spin
            ROS_INFO("Spinning");

            while (ros::ok()) {
                ros::spinOnce();
                loop_rate.sleep();
                ++cnt;
            }
                
            return 0;

        }
        else{

            // throw error
            ROS_ERROR("Params not found for jackal_op - jack_disthandle - trilateration");
            return -1;

        }

    }
    else {

        // throw error
        ROS_ERROR("Params not found for jackal_op - jack_disthandle - get UWB");
        return -1;
    }
}