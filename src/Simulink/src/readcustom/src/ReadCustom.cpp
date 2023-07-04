/*
 * ReadCustom.cpp
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

#include "ReadCustom.h"
#include "rtwtypes.h"
#include "ReadCustom_private.h"
#include <string.h>
#include "ReadCustom_dt.h"

/* Block signals (default storage) */
B_ReadCustom_T ReadCustom_B;

/* Block states (default storage) */
DW_ReadCustom_T ReadCustom_DW;

/* Real-time model */
RT_MODEL_ReadCustom_T ReadCustom_M_ = RT_MODEL_ReadCustom_T();
RT_MODEL_ReadCustom_T *const ReadCustom_M = &ReadCustom_M_;

/* Model step function */
void ReadCustom_step(void)
{
  boolean_T b_varargout_1;

  /* Reset subsysRan breadcrumbs */
  srClearBC(ReadCustom_DW.EnabledSubsystem_SubsysRanBC_d);

  /* Reset subsysRan breadcrumbs */
  srClearBC(ReadCustom_DW.EnabledSubsystem_SubsysRanBC);

  /* Outputs for Atomic SubSystem: '<Root>/Subscribe1' */
  /* MATLABSystem: '<S2>/SourceBlock' */
  b_varargout_1 = Sub_ReadCustom_22.getLatestMessage(&ReadCustom_B.b_varargout_2);

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S3>/Enable'
   */
  if (b_varargout_1) {
    srUpdateBC(ReadCustom_DW.EnabledSubsystem_SubsysRanBC);
    ReadCustom_DW.EnabledSubsystem_MODE = true;

    /* SignalConversion generated from: '<S1>/Bus Selector' */
    ReadCustom_B.Y = ReadCustom_B.b_varargout_2.Pose.Pose.Position.Y;

    /* SignalConversion generated from: '<S1>/Bus Selector' */
    ReadCustom_B.Z = ReadCustom_B.b_varargout_2.Pose.Pose.Position.Z;

    /* SignalConversion generated from: '<S1>/Bus Selector' */
    ReadCustom_B.X = ReadCustom_B.b_varargout_2.Pose.Pose.Position.X;
    srUpdateBC(ReadCustom_DW.EnabledSubsystem_SubsysRanBC_d);
  } else {
    ReadCustom_DW.EnabledSubsystem_MODE = false;
  }

  /* End of MATLABSystem: '<S2>/SourceBlock' */
  /* End of Outputs for SubSystem: '<S2>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem' */
  /* End of Outputs for SubSystem: '<Root>/Subscribe1' */

  /* External mode */
  rtExtModeUploadCheckTrigger(1);

  {                                    /* Sample time: [0.01s, 0.0s] */
    rtExtModeUpload(0, (real_T)ReadCustom_M->Timing.taskTime0);
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(ReadCustom_M)!=-1) &&
        !((rtmGetTFinal(ReadCustom_M)-ReadCustom_M->Timing.taskTime0) >
          ReadCustom_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(ReadCustom_M, "Simulation finished");
    }

    if (rtmGetStopRequested(ReadCustom_M)) {
      rtmSetErrorStatus(ReadCustom_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  ReadCustom_M->Timing.taskTime0 =
    ((time_T)(++ReadCustom_M->Timing.clockTick0)) *
    ReadCustom_M->Timing.stepSize0;
}

/* Model initialize function */
void ReadCustom_initialize(void)
{
  /* Registration code */
  rtmSetTFinal(ReadCustom_M, 10.0);
  ReadCustom_M->Timing.stepSize0 = 0.01;

  /* External mode info */
  ReadCustom_M->Sizes.checksums[0] = (3778960389U);
  ReadCustom_M->Sizes.checksums[1] = (2625739277U);
  ReadCustom_M->Sizes.checksums[2] = (1891941053U);
  ReadCustom_M->Sizes.checksums[3] = (847127604U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    ReadCustom_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&ReadCustom_DW.EnabledSubsystem_SubsysRanBC_d;
    systemRan[2] = (sysRanDType *)&ReadCustom_DW.EnabledSubsystem_SubsysRanBC;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(ReadCustom_M->extModeInfo,
      &ReadCustom_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(ReadCustom_M->extModeInfo, ReadCustom_M->Sizes.checksums);
    rteiSetTPtr(ReadCustom_M->extModeInfo, rtmGetTPtr(ReadCustom_M));
  }

  /* block I/O */
  (void) memset((static_cast<void *>(&ReadCustom_B)), 0,
                sizeof(B_ReadCustom_T));

  /* states (dwork) */
  (void) memset(static_cast<void *>(&ReadCustom_DW), 0,
                sizeof(DW_ReadCustom_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    ReadCustom_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 31;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  {
    int32_T i;
    char_T b_zeroDelimTopic[20];
    static const char_T tmp[19] = { '/', 'g', 'r', 'o', 'u', 'n', 'd', '_', 't',
      'r', 'u', 't', 'h', '/', 's', 't', 'a', 't', 'e' };

    /* Start for Atomic SubSystem: '<Root>/Subscribe1' */
    /* Start for MATLABSystem: '<S2>/SourceBlock' */
    ReadCustom_DW.obj.matlabCodegenIsDeleted = false;
    ReadCustom_DW.objisempty = true;
    ReadCustom_DW.obj.isInitialized = 1;
    for (i = 0; i < 19; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[19] = '\x00';
    Sub_ReadCustom_22.createSubscriber(&b_zeroDelimTopic[0], 51);
    ReadCustom_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SourceBlock' */
    /* End of Start for SubSystem: '<Root>/Subscribe1' */

    /* Start for Enabled SubSystem: '<Root>/Enabled Subsystem' */
    ReadCustom_DW.EnabledSubsystem_MODE = false;

    /* End of Start for SubSystem: '<Root>/Enabled Subsystem' */
  }

  /* SystemInitialize for Enabled SubSystem: '<Root>/Enabled Subsystem' */
  /* SystemInitialize for SignalConversion generated from: '<S1>/Bus Selector' incorporates:
   *  Outport: '<S1>/X'
   */
  ReadCustom_B.X = ReadCustom_P.X_Y0;

  /* SystemInitialize for SignalConversion generated from: '<S1>/Bus Selector' incorporates:
   *  Outport: '<S1>/Y'
   */
  ReadCustom_B.Z = ReadCustom_P.Y_Y0;

  /* SystemInitialize for SignalConversion generated from: '<S1>/Bus Selector' incorporates:
   *  Outport: '<S1>/Z'
   */
  ReadCustom_B.Y = ReadCustom_P.Z_Y0;

  /* End of SystemInitialize for SubSystem: '<Root>/Enabled Subsystem' */
}

/* Model terminate function */
void ReadCustom_terminate(void)
{
  /* Terminate for Atomic SubSystem: '<Root>/Subscribe1' */
  /* Terminate for MATLABSystem: '<S2>/SourceBlock' */
  if (!ReadCustom_DW.obj.matlabCodegenIsDeleted) {
    ReadCustom_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S2>/SourceBlock' */
  /* End of Terminate for SubSystem: '<Root>/Subscribe1' */
}
