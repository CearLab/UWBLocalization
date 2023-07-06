/*
 * ReadCustom_dt.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ReadCustom".
 *
 * Model version              : 10.3
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Tue Jul  4 22:53:46 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(SL_Bus_ReadCustom_ros_time_Time),
  sizeof(SL_Bus_ROSVariableLengthArrayInfo),
  sizeof(SL_Bus_ReadCustom_std_msgs_Header),
  sizeof(SL_Bus_ReadCustom_geometry_msgs_Quaternion),
  sizeof(SL_Bus_ReadCustom_geometry_msgs_Vector3),
  sizeof(SL_Bus_ReadCustom_sensor_msgs_Imu),
  sizeof(ros_slroscpp_internal_block_S_T),
  sizeof(uint_T),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "SL_Bus_ReadCustom_ros_time_Time",
  "SL_Bus_ROSVariableLengthArrayInfo",
  "SL_Bus_ReadCustom_std_msgs_Header",
  "SL_Bus_ReadCustom_geometry_msgs_Quaternion",
  "SL_Bus_ReadCustom_geometry_msgs_Vector3",
  "SL_Bus_ReadCustom_sensor_msgs_Imu",
  "ros_slroscpp_internal_block_S_T",
  "uint_T",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&ReadCustom_B.Z), 0, 0, 3 }
  ,

  { (char_T *)(&ReadCustom_DW.obj), 21, 0, 1 },

  { (char_T *)(&ReadCustom_DW.Scope_PWORK.LoggedData[0]), 11, 0, 3 },

  { (char_T *)(&ReadCustom_DW.EnabledSubsystem_SubsysRanBC), 2, 0, 2 },

  { (char_T *)(&ReadCustom_DW.objisempty), 8, 0, 2 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  5U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&ReadCustom_P.Out1_Y0), 20, 0, 1 },

  { (char_T *)(&ReadCustom_P.Constant_Value), 20, 0, 1 },

  { (char_T *)(&ReadCustom_P.X_Y0), 0, 0, 3 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  3U,
  rtPTransitions
};

/* [EOF] ReadCustom_dt.h */
