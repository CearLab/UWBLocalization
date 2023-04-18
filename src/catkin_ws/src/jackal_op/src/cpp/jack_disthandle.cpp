#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include <gtec_msgs/Ranging.h>
#include <jackal_op/MeshUWB.h>

#include "libful.h"

/**
 * Node used to get distance measurements from UWB plugin and divide them into the related anchors and tags
 */

/**
* Subscriber callback
*/
void chatterCallback(const gtec_msgs::Ranging::ConstPtr& msg)
{

    // define nodehandler - general purpose
    ros::NodeHandle n;

    /**
     * define topic to publish on. There will be two, one for each tag on the jackal.
     * First get the topics name from param server. The create two handles for publishing.
     */
    std::string T1, T2;
    if (n.hasParam("jack_disthandle_pubT1") && n.hasParam("jack_disthandle_pubT2")) {

        // get pub names
        n.getParam("jack_disthandle_pubT1", T1);    
        n.getParam("jack_disthandle_pubT2", T2);    

        // set publisher
        ros::Publisher T1_pub = n.advertise<jackal_op::MeshUWB>(T1, 1000);
        ros::Publisher T2_pub = n.advertise<jackal_op::MeshUWB>(T2, 1000);
        ros::Rate loop_rate(10);
    }
    else {
        ROS_INFO("Missing publishers\n");
    }
}


/**
* Node code
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
    std::string UWB_plugin;
    if (np.hasParam("jack_disthandle_sub")) {
        np.getParam("jack_disthandle_sub", UWB_plugin);    
    }
    ros::Subscriber jack_disthandle_S = np.subscribe("chatter", 1000, chatterCallback);

    // spin the listener
    ros::spin();

    return 0;
}