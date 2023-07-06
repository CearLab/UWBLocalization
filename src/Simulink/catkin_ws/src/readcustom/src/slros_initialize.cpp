#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "ReadCustom";

// For Block ReadCustom/Subscribe1
SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_ReadCustom_sensor_msgs_Imu> Sub_ReadCustom_22;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

