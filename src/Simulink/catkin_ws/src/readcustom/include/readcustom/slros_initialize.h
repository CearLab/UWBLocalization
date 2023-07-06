#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"
#include "ReadCustom_types.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ReadCustom/Subscribe1
extern SimulinkSubscriber<sensor_msgs::Imu, SL_Bus_ReadCustom_sensor_msgs_Imu> Sub_ReadCustom_22;

void slros_node_init(int argc, char** argv);

#endif
