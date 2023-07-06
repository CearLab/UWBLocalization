#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <ros/time.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Header.h>
#include "ReadCustom_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(geometry_msgs::Quaternion* msgPtr, SL_Bus_ReadCustom_geometry_msgs_Quaternion const* busPtr);
void convertToBus(SL_Bus_ReadCustom_geometry_msgs_Quaternion* busPtr, geometry_msgs::Quaternion const* msgPtr);

void convertFromBus(geometry_msgs::Vector3* msgPtr, SL_Bus_ReadCustom_geometry_msgs_Vector3 const* busPtr);
void convertToBus(SL_Bus_ReadCustom_geometry_msgs_Vector3* busPtr, geometry_msgs::Vector3 const* msgPtr);

void convertFromBus(ros::Time* msgPtr, SL_Bus_ReadCustom_ros_time_Time const* busPtr);
void convertToBus(SL_Bus_ReadCustom_ros_time_Time* busPtr, ros::Time const* msgPtr);

void convertFromBus(sensor_msgs::Imu* msgPtr, SL_Bus_ReadCustom_sensor_msgs_Imu const* busPtr);
void convertToBus(SL_Bus_ReadCustom_sensor_msgs_Imu* busPtr, sensor_msgs::Imu const* msgPtr);

void convertFromBus(std_msgs::Header* msgPtr, SL_Bus_ReadCustom_std_msgs_Header const* busPtr);
void convertToBus(SL_Bus_ReadCustom_std_msgs_Header* busPtr, std_msgs::Header const* msgPtr);


#endif
