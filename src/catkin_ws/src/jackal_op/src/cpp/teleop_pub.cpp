#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"

#include "libful.h"

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
    /**
     * The ros::init() function needs to see argc and argv so that it can perform
     * any ROS arguments and name remapping that were provided at the command line.
     * For programmatic remappings you can use a different version of init() which takes
     * remappings directly, but for most command-line programs, passing argc and argv is
     * the easiest way to do it.  The third argument to init() is the name of the node.
     *
     * You must call one of the versions of ros::init() before using any other
     * part of the ROS system.
     */
    ros::init(argc, argv, "teleop_pub");

    /**
     * NodeHandle is the main access point to communications with the ROS system.
     * The first NodeHandle constructed will fully initialize this node, and the last
     * NodeHandle destructed will close down the node.
     */
    ros::NodeHandle n;

    /**
     * The advertise() function is how you tell ROS that you want to
     * publish on a given topic name. This invokes a call to the ROS
     * master node, which keeps a registry of who is publishing and who
     * is subscribing. After this advertise() call is made, the master
     * node will notify anyone who is trying to subscribe to this topic name,
     * and they will in turn negotiate a peer-to-peer connection with this
     * node.  advertise() returns a Publisher object which allows you to
     * publish messages on that topic through a call to publish().  Once
     * all copies of the returned Publisher object are destroyed, the topic
     * will be automatically unadvertised.
     *
     * The second parameter to advertise() is the size of the message queue
     * used for publishing messages.  If messages are published more quickly
     * than we can send them, the number here specifies how many messages to
     * buffer up before throwing some away.
     */
    ros::Publisher teleop_pub = n.advertise<geometry_msgs::Twist>("Jackal1/cmd_vel", 1000);

    ros::Rate loop_rate(10);

    /**
     * A count of how many messages we have sent. This is used to create
     * a unique string for each message.
     */
    int count = 0;

    // declare linvel and pose
    std::vector<double> linvel(3, 0.0);
    std::vector<double> angvel(3, 0.0);

    // general stuff
    int cnt = 0;
    ros::NodeHandle nh;

    // test
    //linvel[0] = -0.5;

    // set default params
    nh.setParam("/jack_linvel_res",linvel);
    nh.setParam("/jack_angvel_res",angvel);

    while (ros::ok())
    {
        /**
         * This is a message object. You stuff it with data, and then publish it.
         */
        geometry_msgs::Twist msg;

        if (nh.hasParam("/jack_linvel_res") && nh.hasParam("/jack_angvel_res")){
            nh.getParam("/jack_linvel_res",linvel);
            nh.getParam("/jack_angvel_res",angvel);

            // show what you got
            ROS_INFO("v: %g",linvel[0]);
            ROS_INFO("w: %g",angvel[2]);
        }
        else {
            ROS_INFO("params not found");
        }
        
        // fill the message - linvel
        msg.linear.x = linvel[0];
        msg.linear.y = linvel[1];
        msg.linear.z = linvel[2];

        // fill the message - pose
        msg.angular.x = angvel[0];
        msg.angular.y = angvel[1];
        msg.angular.z = angvel[2];

        /**
         * The publish() function is how you send messages. The parameter
         * is the message object. The type of this object must agree with the type
         * given as a template parameter to the advertise<>() call, as was done
         * in the constructor above.
         */
        teleop_pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }

    return 0;
}