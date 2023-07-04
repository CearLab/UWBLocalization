/*
 * ReadCustom.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ReadCustom".
 *
 * Model version              : 10.1
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C++ source code generated on : Tue Jul  4 15:35:54 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ReadCustom_h_
#define RTW_HEADER_ReadCustom_h_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "dt_info.h"
#include "ext_work.h"
#include "slros_initialize.h"
#include "ReadCustom_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block signals (default storage) */
struct B_ReadCustom_T {
  SL_Bus_ReadCustom_nav_msgs_Odometry b_varargout_2;
  real_T Y;
  real_T Z;
  real_T X;
};

/* Block states (default storage) for system '<Root>' */
struct DW_ReadCustom_T {
  ros_slroscpp_internal_block_S_T obj; /* '<S2>/SourceBlock' */
  struct {
    void *LoggedData[3];
  } Scope_PWORK;                       /* '<S1>/Scope' */

  int8_T EnabledSubsystem_SubsysRanBC; /* '<S2>/Enabled Subsystem' */
  int8_T EnabledSubsystem_SubsysRanBC_d;/* '<Root>/Enabled Subsystem' */
  boolean_T objisempty;                /* '<S2>/SourceBlock' */
  boolean_T EnabledSubsystem_MODE;     /* '<Root>/Enabled Subsystem' */
};

/* Parameters (default storage) */
struct P_ReadCustom_T_ {
  SL_Bus_ReadCustom_nav_msgs_Odometry Out1_Y0;/* Computed Parameter: Out1_Y0
                                               * Referenced by: '<S3>/Out1'
                                               */
  SL_Bus_ReadCustom_nav_msgs_Odometry Constant_Value;/* Computed Parameter: Constant_Value
                                                      * Referenced by: '<S2>/Constant'
                                                      */
  real_T X_Y0;                         /* Computed Parameter: X_Y0
                                        * Referenced by: '<S1>/X'
                                        */
  real_T Y_Y0;                         /* Computed Parameter: Y_Y0
                                        * Referenced by: '<S1>/Y'
                                        */
  real_T Z_Y0;                         /* Computed Parameter: Z_Y0
                                        * Referenced by: '<S1>/Z'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_ReadCustom_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
#ifdef __cplusplus

extern "C"
{

#endif

  extern P_ReadCustom_T ReadCustom_P;

#ifdef __cplusplus

}

#endif

/* Block signals (default storage) */
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_ReadCustom_T ReadCustom_B;

#ifdef __cplusplus

}

#endif

/* Block states (default storage) */
extern struct DW_ReadCustom_T ReadCustom_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  /* Model entry point functions */
  extern void ReadCustom_initialize(void);
  extern void ReadCustom_step(void);
  extern void ReadCustom_terminate(void);

#ifdef __cplusplus

}

#endif

/* Real-time Model object */
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_ReadCustom_T *const ReadCustom_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'ReadCustom'
 * '<S1>'   : 'ReadCustom/Enabled Subsystem'
 * '<S2>'   : 'ReadCustom/Subscribe1'
 * '<S3>'   : 'ReadCustom/Subscribe1/Enabled Subsystem'
 */
#endif                                 /* RTW_HEADER_ReadCustom_h_ */
