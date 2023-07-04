#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ReadCustom";

// For Block ReadCustom/Subscribe1
SimulinkSubscriber<nav_msgs::Odometry, SL_Bus_ReadCustom_nav_msgs_Odometry> Sub_ReadCustom_22;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

