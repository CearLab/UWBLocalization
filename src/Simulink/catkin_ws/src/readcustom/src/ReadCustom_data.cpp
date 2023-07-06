/*
 * ReadCustom_data.cpp
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

#include "ReadCustom.h"

/* Block parameters (default storage) */
P_ReadCustom_T ReadCustom_P = {
  /* Computed Parameter: Out1_Y0
   * Referenced by: '<S3>/Out1'
   */
  {
    {
      0U,                              /* Seq */

      {
        0.0,                           /* Sec */
        0.0                            /* Nsec */
      },                               /* Stamp */

      {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U }
      ,                                /* FrameId */

      {
        0U,                            /* CurrentLength */
        0U                             /* ReceivedLength */
      }                                /* FrameId_SL_Info */
    },                                 /* Header */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0,                             /* Z */
      0.0                              /* W */
    },                                 /* Orientation */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    ,                                  /* OrientationCovariance */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },                                 /* AngularVelocity */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    ,                                  /* AngularVelocityCovariance */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },                                 /* LinearAcceleration */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    /* LinearAccelerationCovariance */
  },

  /* Computed Parameter: Constant_Value
   * Referenced by: '<S2>/Constant'
   */
  {
    {
      0U,                              /* Seq */

      {
        0.0,                           /* Sec */
        0.0                            /* Nsec */
      },                               /* Stamp */

      {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U }
      ,                                /* FrameId */

      {
        0U,                            /* CurrentLength */
        0U                             /* ReceivedLength */
      }                                /* FrameId_SL_Info */
    },                                 /* Header */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0,                             /* Z */
      0.0                              /* W */
    },                                 /* Orientation */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    ,                                  /* OrientationCovariance */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },                                 /* AngularVelocity */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    ,                                  /* AngularVelocityCovariance */

    {
      0.0,                             /* X */
      0.0,                             /* Y */
      0.0                              /* Z */
    },                                 /* LinearAcceleration */

    {
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }
    /* LinearAccelerationCovariance */
  },

  /* Computed Parameter: X_Y0
   * Referenced by: '<S1>/X'
   */
  0.0,

  /* Computed Parameter: Y_Y0
   * Referenced by: '<S1>/Y'
   */
  0.0,

  /* Computed Parameter: Z_Y0
   * Referenced by: '<S1>/Z'
   */
  0.0
};
