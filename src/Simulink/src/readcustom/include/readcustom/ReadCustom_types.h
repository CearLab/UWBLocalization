/*
 * ReadCustom_types.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ReadCustom".
 *
 * Model version              : 10.0
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Tue Jul  4 12:20:17 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ReadCustom_types_h_
#define RTW_HEADER_ReadCustom_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_ros_time_Time_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_ros_time_Time_

struct SL_Bus_ReadCustom_ros_time_Time
{
  real_T Sec;
  real_T Nsec;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_std_msgs_Header_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_std_msgs_Header_

struct SL_Bus_ReadCustom_std_msgs_Header
{
  uint32_T Seq;
  SL_Bus_ReadCustom_ros_time_Time Stamp;
  uint8_T FrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo FrameId_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Point_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Point_

struct SL_Bus_ReadCustom_geometry_msgs_Point
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Quaternion_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Quaternion_

struct SL_Bus_ReadCustom_geometry_msgs_Quaternion
{
  real_T X;
  real_T Y;
  real_T Z;
  real_T W;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Pose_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Pose_

struct SL_Bus_ReadCustom_geometry_msgs_Pose
{
  SL_Bus_ReadCustom_geometry_msgs_Point Position;
  SL_Bus_ReadCustom_geometry_msgs_Quaternion Orientation;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_PoseWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_PoseWithCovariance_

struct SL_Bus_ReadCustom_geometry_msgs_PoseWithCovariance
{
  SL_Bus_ReadCustom_geometry_msgs_Pose Pose;
  real_T Covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Vector3_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Vector3_

struct SL_Bus_ReadCustom_geometry_msgs_Vector3
{
  real_T X;
  real_T Y;
  real_T Z;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Twist_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_Twist_

struct SL_Bus_ReadCustom_geometry_msgs_Twist
{
  SL_Bus_ReadCustom_geometry_msgs_Vector3 Linear;
  SL_Bus_ReadCustom_geometry_msgs_Vector3 Angular;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_TwistWithCovariance_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_geometry_msgs_TwistWithCovariance_

struct SL_Bus_ReadCustom_geometry_msgs_TwistWithCovariance
{
  SL_Bus_ReadCustom_geometry_msgs_Twist Twist;
  real_T Covariance[36];
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_nav_msgs_Odometry_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ReadCustom_nav_msgs_Odometry_

struct SL_Bus_ReadCustom_nav_msgs_Odometry
{
  SL_Bus_ReadCustom_std_msgs_Header Header;
  uint8_T ChildFrameId[128];
  SL_Bus_ROSVariableLengthArrayInfo ChildFrameId_SL_Info;
  SL_Bus_ReadCustom_geometry_msgs_PoseWithCovariance Pose;
  SL_Bus_ReadCustom_geometry_msgs_TwistWithCovariance Twist;
};

#endif

#ifndef struct_ros_slroscpp_internal_block_S_T
#define struct_ros_slroscpp_internal_block_S_T

struct ros_slroscpp_internal_block_S_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                              /* struct_ros_slroscpp_internal_block_S_T */

/* Parameters (default storage) */
typedef struct P_ReadCustom_T_ P_ReadCustom_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_ReadCustom_T RT_MODEL_ReadCustom_T;

#endif                                 /* RTW_HEADER_ReadCustom_types_h_ */
