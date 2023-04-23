// standard includes
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cmath>

// ros includes
#include "ros/ros.h"
#include "std_msgs/String.h"

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

    return 0;
}