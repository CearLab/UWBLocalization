#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include <gtec_msgs/Ranging.h>
#include <jackal_op/MeshUWB.h>
#include "libful.h"

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

    /**
     * define topic to subscribe to. Get the topics name params server. Then create handle for subscribing.
     */
    std::string UWB_plugin, pubT1, pubT2, jackName;
    int Nanchors;
    if (np.hasParam("jack_disthandle_sub") && np.hasParam("jack_disthandle_pubT1") && 
        np.hasParam("jack_disthandle_pubT2") && np.hasParam("jackAPIName") &&
        np.hasParam("NanchorMesh")) {

        // get topics and init data
        np.getParam("jack_disthandle_sub", UWB_plugin);  
        np.getParam("jack_disthandle_pubT1", pubT1);
        np.getParam("jack_disthandle_pubT2", pubT2);  
        np.getParam("jackAPIName", jackName); 
        np.getParam("NanchorMesh", Nanchors);  

        // instance of a class
        jackAPI jackNode(jackName, Nanchors);
    }

    // spin the listener
    ros::spin();

    return 0;
}