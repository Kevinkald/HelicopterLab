/*
 * P4p2.c
 *
 * Code generation for model "P4p2".
 *
 * Model version              : 1.87
 * Simulink Coder version : 8.6 (R2014a) 27-Dec-2013
 * C source code generated on : Wed Oct 17 20:04:36 2018
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "P4p2.h"
#include "P4p2_private.h"
#include "P4p2_dt.h"

/* Block signals (auto storage) */
B_P4p2_T P4p2_B;

/* Continuous states */
X_P4p2_T P4p2_X;

/* Block states (auto storage) */
DW_P4p2_T P4p2_DW;

/* Real-time model */
RT_MODEL_P4p2_T P4p2_M_;
RT_MODEL_P4p2_T *const P4p2_M = &P4p2_M_;
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(P4p2_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(P4p2_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (P4p2_M->Timing.TaskCounters.TID[1] == 0) {
    P4p2_M->Timing.RateInteraction.TID1_2 = (P4p2_M->Timing.TaskCounters.TID[2] ==
      0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    P4p2_M->Timing.perTaskSampleHits[5] = P4p2_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (P4p2_M->Timing.TaskCounters.TID[2])++;
  if ((P4p2_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    P4p2_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 9;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  P4p2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void P4p2_output0(void)                /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtToFile[12];
  real_T rtb_DeadZoney;
  real_T rtb_C_e[3];
  real_T rtb_u[2];
  int32_T i;
  real_T tmp[6];
  real_T tmp_0[6];
  int32_T i_0;
  real_T u0;
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* set solver stop time */
    if (!(P4p2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&P4p2_M->solverInfo, ((P4p2_M->Timing.clockTickH0 +
        1) * P4p2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&P4p2_M->solverInfo, ((P4p2_M->Timing.clockTick0 + 1)
        * P4p2_M->Timing.stepSize0 + P4p2_M->Timing.clockTickH0 *
        P4p2_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(P4p2_M)) {
    P4p2_M->Timing.t[0] = rtsiGetT(&P4p2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: P4p2/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(P4p2_DW.HILReadEncoderTimebase_Task, 1,
        &P4p2_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 = P4p2_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 = P4p2_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = P4p2_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* Gain: '<S5>/radtodeg1' incorporates:
   *  Integrator: '<S6>/Integrator'
   */
  for (i = 0; i < 6; i++) {
    P4p2_B.radtodeg1[i] = P4p2_P.radtodeg1_Gain * P4p2_X.Integrator_CSTATE[i];
  }

  /* End of Gain: '<S5>/radtodeg1' */
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* Gain: '<S2>/Pitch: Count to rad' */
    P4p2_B.PitchCounttorad = P4p2_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Constant: '<S2>/Pitch offset ' */
    P4p2_B.Pitchoffset = P4p2_P.Pitchoffset_Value;
  }

  /* Sum: '<S2>/Sum1' incorporates:
   *  Gain: '<S10>/Gain'
   *  TransferFcn: '<S2>/Pitch: Transfer Fcn'
   */
  P4p2_B.Sum1 = (P4p2_P.PitchTransferFcn_C * P4p2_X.PitchTransferFcn_CSTATE +
                 P4p2_P.PitchTransferFcn_D * P4p2_B.PitchCounttorad) *
    P4p2_P.Gain_Gain + P4p2_B.Pitchoffset;
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* Gain: '<S2>/Elevation: Count to rad' */
    P4p2_B.ElevationCounttorad = P4p2_P.ElevationCounttorad_Gain * rtb_DeadZoney;
  }

  /* Gain: '<S8>/Gain' incorporates:
   *  TransferFcn: '<S2>/Elevation: Transfer Fcn'
   */
  P4p2_B.Gain = (P4p2_P.ElevationTransferFcn_C *
                 P4p2_X.ElevationTransferFcn_CSTATE +
                 P4p2_P.ElevationTransferFcn_D * P4p2_B.ElevationCounttorad) *
    P4p2_P.Gain_Gain_n;
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* Gain: '<S2>/Travel: Count to rad' */
    P4p2_B.TravelCounttorad = P4p2_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* Gain: '<S12>/Gain' incorporates:
   *  TransferFcn: '<S2>/Travel: Transfer Fcn'
   */
  P4p2_B.Gain_d = (P4p2_P.TravelTransferFcn_C * P4p2_X.TravelTransferFcn_CSTATE
                   + P4p2_P.TravelTransferFcn_D * P4p2_B.TravelCounttorad) *
    P4p2_P.Gain_Gain_l;
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* Gain: '<S9>/Gain' */
    P4p2_B.Gain_i = P4p2_P.Gain_Gain_a * P4p2_B.PitchCounttorad;

    /* Sum: '<S2>/Sum2' incorporates:
     *  Constant: '<S2>/Elevation offset'
     *  Gain: '<S7>/Gain'
     */
    P4p2_B.Sum2 = P4p2_P.Gain_Gain_lv * P4p2_B.ElevationCounttorad +
      P4p2_P.Elevationoffset_Value;

    /* Sum: '<S2>/Sum' incorporates:
     *  Constant: '<S2>/Travel offset '
     *  Gain: '<S11>/Gain'
     */
    P4p2_B.Sum = P4p2_P.Gain_Gain_ar * P4p2_B.TravelCounttorad +
      P4p2_P.Traveloffset_Value;

    /* SignalConversion: '<S5>/TmpSignal ConversionAtTo FileInport1' */
    for (i = 0; i < 6; i++) {
      rtb_TmpSignalConversionAtToFile[i] = P4p2_B.radtodeg1[i];
    }

    rtb_TmpSignalConversionAtToFile[6] = P4p2_B.Gain_i;
    rtb_TmpSignalConversionAtToFile[7] = P4p2_B.Sum1;
    rtb_TmpSignalConversionAtToFile[8] = P4p2_B.Sum2;
    rtb_TmpSignalConversionAtToFile[9] = P4p2_B.Gain;
    rtb_TmpSignalConversionAtToFile[10] = P4p2_B.Sum;
    rtb_TmpSignalConversionAtToFile[11] = P4p2_B.Gain_d;

    /* End of SignalConversion: '<S5>/TmpSignal ConversionAtTo FileInport1' */

    /* ToFile: '<S5>/To File' */
    if (rtmIsMajorTimeStep(P4p2_M)) {
      {
        if (!(++P4p2_DW.ToFile_IWORK.Decimation % 1) &&
            (P4p2_DW.ToFile_IWORK.Count*13)+1 < 100000000 ) {
          FILE *fp = (FILE *) P4p2_DW.ToFile_PWORK.FilePtr;
          if (fp != (NULL)) {
            real_T u[13];
            P4p2_DW.ToFile_IWORK.Decimation = 0;
            u[0] = P4p2_M->Timing.t[1];
            u[1] = rtb_TmpSignalConversionAtToFile[0];
            u[2] = rtb_TmpSignalConversionAtToFile[1];
            u[3] = rtb_TmpSignalConversionAtToFile[2];
            u[4] = rtb_TmpSignalConversionAtToFile[3];
            u[5] = rtb_TmpSignalConversionAtToFile[4];
            u[6] = rtb_TmpSignalConversionAtToFile[5];
            u[7] = rtb_TmpSignalConversionAtToFile[6];
            u[8] = rtb_TmpSignalConversionAtToFile[7];
            u[9] = rtb_TmpSignalConversionAtToFile[8];
            u[10] = rtb_TmpSignalConversionAtToFile[9];
            u[11] = rtb_TmpSignalConversionAtToFile[10];
            u[12] = rtb_TmpSignalConversionAtToFile[11];
            if (fwrite(u, sizeof(real_T), 13, fp) != 13) {
              rtmSetErrorStatus(P4p2_M, "Error writing to MAT-file FILENAME.mat");
              return;
            }

            if (((++P4p2_DW.ToFile_IWORK.Count)*13)+1 >= 100000000) {
              (void)fprintf(stdout,
                            "*** The ToFile block will stop logging data before\n"
                            "    the simulation has ended, because it has reached\n"
                            "    the maximum number of elements (100000000)\n"
                            "    allowed in MAT-file FILENAME.mat.\n");
            }
          }
        }
      }
    }
  }

  /* Gain: '<Root>/Deg to rad' incorporates:
   *  Gain: '<Root>/C_e'
   */
  tmp[0] = P4p2_B.Gain_i;
  tmp[1] = P4p2_B.Sum1;
  tmp[2] = P4p2_B.Sum2;
  tmp[3] = P4p2_B.Gain;
  tmp[4] = P4p2_B.Sum;
  tmp[5] = P4p2_B.Gain_d;
  for (i = 0; i < 6; i++) {
    tmp_0[i] = P4p2_P.Degtorad_Gain * tmp[i];
  }

  /* End of Gain: '<Root>/Deg to rad' */

  /* Gain: '<Root>/C_e' */
  for (i = 0; i < 3; i++) {
    rtb_C_e[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_C_e[i] += P4p2_P.C_e[3 * i_0 + i] * tmp_0[i_0];
    }
  }

  /* RateTransition: '<S3>/Rate Transition: x' */
  if (rtmIsMajorTimeStep(P4p2_M)) {
    if (P4p2_M->Timing.RateInteraction.TID1_2) {
      P4p2_B.RateTransitionx = P4p2_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S3>/Dead Zone: x' */
    if (P4p2_B.RateTransitionx > P4p2_P.DeadZonex_End) {
      rtb_DeadZoney = P4p2_B.RateTransitionx - P4p2_P.DeadZonex_End;
    } else if (P4p2_B.RateTransitionx >= P4p2_P.DeadZonex_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = P4p2_B.RateTransitionx - P4p2_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: x' */

    /* Gain: '<S3>/Joystick_gain_x' incorporates:
     *  Gain: '<S3>/Gain: x'
     */
    P4p2_B.Joystick_gain_x = P4p2_P.Gainx_Gain * rtb_DeadZoney *
      P4p2_P.Joystick_gain_x;

    /* RateTransition: '<S3>/Rate Transition: y' */
    if (P4p2_M->Timing.RateInteraction.TID1_2) {
      P4p2_B.RateTransitiony = P4p2_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: y' */

    /* DeadZone: '<S3>/Dead Zone: y' */
    if (P4p2_B.RateTransitiony > P4p2_P.DeadZoney_End) {
      rtb_DeadZoney = P4p2_B.RateTransitiony - P4p2_P.DeadZoney_End;
    } else if (P4p2_B.RateTransitiony >= P4p2_P.DeadZoney_Start) {
      rtb_DeadZoney = 0.0;
    } else {
      rtb_DeadZoney = P4p2_B.RateTransitiony - P4p2_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: y' */

    /* Gain: '<S3>/Joystick_gain_y' incorporates:
     *  Gain: '<S3>/Gain: y'
     */
    P4p2_B.Joystick_gain_y = P4p2_P.Gainy_Gain * rtb_DeadZoney *
      P4p2_P.Joystick_gain_y;

    /* Gain: '<S4>/Reference feed forward ' incorporates:
     *  SignalConversion: '<S4>/TmpSignal ConversionAtReference feed forward Inport1'
     */
    P4p2_B.Referencefeedforward[0] = 0.0;
    P4p2_B.Referencefeedforward[0] += P4p2_P.P[0] * P4p2_B.Joystick_gain_x;
    P4p2_B.Referencefeedforward[0] += P4p2_P.P[2] * P4p2_B.Joystick_gain_y;
    P4p2_B.Referencefeedforward[1] = 0.0;
    P4p2_B.Referencefeedforward[1] += P4p2_P.P[1] * P4p2_B.Joystick_gain_x;
    P4p2_B.Referencefeedforward[1] += P4p2_P.P[3] * P4p2_B.Joystick_gain_y;
  }

  /* End of RateTransition: '<S3>/Rate Transition: x' */

  /* Sum: '<S4>/Sum3' incorporates:
   *  Gain: '<S4>/State feedback'
   *  Integrator: '<S6>/Integrator'
   *  SignalConversion: '<S4>/TmpSignal ConversionAtState feedbackInport1'
   */
  for (i = 0; i < 2; i++) {
    rtb_u[i] = P4p2_B.Referencefeedforward[i] - ((P4p2_P.K[i + 2] *
      P4p2_X.Integrator_CSTATE[1] + P4p2_P.K[i] * P4p2_X.Integrator_CSTATE[0]) +
      P4p2_P.K[i + 4] * P4p2_X.Integrator_CSTATE[3]);
  }

  /* End of Sum: '<S4>/Sum3' */
  if (rtmIsMajorTimeStep(P4p2_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (rtb_u[1] + rtb_u[0]) * P4p2_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (u0 > P4p2_P.FrontmotorSaturation_UpperSat) {
    P4p2_B.FrontmotorSaturation = P4p2_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < P4p2_P.FrontmotorSaturation_LowerSat) {
    P4p2_B.FrontmotorSaturation = P4p2_P.FrontmotorSaturation_LowerSat;
  } else {
    P4p2_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (rtb_u[0] - rtb_u[1]) * P4p2_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (u0 > P4p2_P.BackmotorSaturation_UpperSat) {
    P4p2_B.BackmotorSaturation = P4p2_P.BackmotorSaturation_UpperSat;
  } else if (u0 < P4p2_P.BackmotorSaturation_LowerSat) {
    P4p2_B.BackmotorSaturation = P4p2_P.BackmotorSaturation_LowerSat;
  } else {
    P4p2_B.BackmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(P4p2_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: P4p2/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      P4p2_DW.HILWriteAnalog_Buffer[0] = P4p2_B.FrontmotorSaturation;
      P4p2_DW.HILWriteAnalog_Buffer[1] = P4p2_B.BackmotorSaturation;
      result = hil_write_analog(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILWriteAnalog_channels, 2, &P4p2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
      }
    }
  }

  for (i = 0; i < 6; i++) {
    /* Gain: '<S6>/B' incorporates:
     *  Sum: '<S6>/Sum'
     */
    tmp[i] = P4p2_P.B_e[i + 6] * rtb_u[1] + P4p2_P.B_e[i] * rtb_u[0];

    /* Gain: '<S6>/L' incorporates:
     *  Sum: '<S6>/Sum'
     */
    tmp_0[i] = P4p2_P.L[i + 12] * rtb_C_e[2] + (P4p2_P.L[i + 6] * rtb_C_e[1] +
      P4p2_P.L[i] * rtb_C_e[0]);
  }

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<S6>/A-LC'
   *  Integrator: '<S6>/Integrator'
   */
  for (i = 0; i < 6; i++) {
    u0 = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      u0 += P4p2_P.A_est[6 * i_0 + i] * P4p2_X.Integrator_CSTATE[i_0];
    }

    P4p2_B.Sum_c[i] = (tmp[i] + tmp_0[i]) + u0;
  }
}

/* Model update function for TID0 */
void P4p2_update0(void)                /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(P4p2_M)) {
    rt_ertODEUpdateContinuousStates(&P4p2_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P4p2_M->Timing.clockTick0)) {
    ++P4p2_M->Timing.clockTickH0;
  }

  P4p2_M->Timing.t[0] = rtsiGetSolverStopTime(&P4p2_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P4p2_M->Timing.clockTick1)) {
    ++P4p2_M->Timing.clockTickH1;
  }

  P4p2_M->Timing.t[1] = P4p2_M->Timing.clockTick1 * P4p2_M->Timing.stepSize1 +
    P4p2_M->Timing.clockTickH1 * P4p2_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void P4p2_derivatives(void)
{
  int32_T i;
  XDot_P4p2_T *_rtXdot;
  _rtXdot = ((XDot_P4p2_T *) P4p2_M->ModelData.derivs);

  /* Derivatives for Integrator: '<S6>/Integrator' */
  for (i = 0; i < 6; i++) {
    _rtXdot->Integrator_CSTATE[i] = P4p2_B.Sum_c[i];
  }

  /* End of Derivatives for Integrator: '<S6>/Integrator' */

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += P4p2_P.PitchTransferFcn_A *
    P4p2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += P4p2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += P4p2_P.ElevationTransferFcn_A *
    P4p2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += P4p2_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += P4p2_P.TravelTransferFcn_A *
    P4p2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += P4p2_B.TravelCounttorad;
}

/* Model output function for TID2 */
void P4p2_output2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P4p2/Joystick/Game Controller (game_controller_block) */
  {
    if (P4p2_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(P4p2_DW.GameController_Controller, &state,
        &new_data);
      if (result == 0) {
        P4p2_B.GameController_o4 = state.x;
        P4p2_B.GameController_o5 = state.y;
      }
    } else {
      P4p2_B.GameController_o4 = 0;
      P4p2_B.GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void P4p2_update2(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* Update for RateTransition: '<S3>/Rate Transition: x' */
  P4p2_DW.RateTransitionx_Buffer0 = P4p2_B.GameController_o4;

  /* Update for RateTransition: '<S3>/Rate Transition: y' */
  P4p2_DW.RateTransitiony_Buffer0 = P4p2_B.GameController_o5;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++P4p2_M->Timing.clockTick2)) {
    ++P4p2_M->Timing.clockTickH2;
  }

  P4p2_M->Timing.t[2] = P4p2_M->Timing.clockTick2 * P4p2_M->Timing.stepSize2 +
    P4p2_M->Timing.clockTickH2 * P4p2_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void P4p2_output(int_T tid)
{
  switch (tid) {
   case 0 :
    P4p2_output0();
    break;

   case 2 :
    P4p2_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void P4p2_update(int_T tid)
{
  switch (tid) {
   case 0 :
    P4p2_update0();
    break;

   case 2 :
    P4p2_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void P4p2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P4p2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &P4p2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P4p2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(P4p2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P4p2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(P4p2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P4p2_M, _rt_error_message);
      return;
    }

    if ((P4p2_P.HILInitialize_set_analog_input_ && !is_switching) ||
        (P4p2_P.HILInitialize_set_analog_inpu_m && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &P4p2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = P4p2_P.HILInitialize_analog_input_mini;
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &P4p2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = P4p2_P.HILInitialize_analog_input_maxi;
        }
      }

      result = hil_set_analog_input_ranges(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_analog_input_chan, 8U,
        &P4p2_DW.HILInitialize_AIMinimums[0], &P4p2_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_analog_output && !is_switching) ||
        (P4p2_P.HILInitialize_set_analog_outp_b && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &P4p2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = P4p2_P.HILInitialize_analog_output_min;
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &P4p2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = P4p2_P.HILInitialize_analog_output_max;
        }
      }

      result = hil_set_analog_output_ranges(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_analog_output_cha, 8U,
        &P4p2_DW.HILInitialize_AOMinimums[0], &P4p2_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_analog_outp_e && !is_switching) ||
        (P4p2_P.HILInitialize_set_analog_outp_j && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P4p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P4p2_P.HILInitialize_initial_analog_ou;
        }
      }

      result = hil_write_analog(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_analog_output_cha, 8U,
        &P4p2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if (P4p2_P.HILInitialize_set_analog_outp_p) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P4p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P4p2_P.HILInitialize_watchdog_analog_o;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (P4p2_DW.HILInitialize_Card, P4p2_P.HILInitialize_analog_output_cha, 8U,
         &P4p2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_encoder_param && !is_switching) ||
        (P4p2_P.HILInitialize_set_encoder_par_m && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes = &P4p2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = P4p2_P.HILInitialize_quadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_encoder_channels, 8U, (t_encoder_quadrature_mode *)
        &P4p2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_encoder_count && !is_switching) ||
        (P4p2_P.HILInitialize_set_encoder_cou_k && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts = &P4p2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = P4p2_P.HILInitialize_initial_encoder_c;
        }
      }

      result = hil_set_encoder_counts(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_encoder_channels, 8U,
        &P4p2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_pwm_params_at && !is_switching) ||
        (P4p2_P.HILInitialize_set_pwm_params__f && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &P4p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P4p2_P.HILInitialize_pwm_modes;
        }
      }

      result = hil_set_pwm_mode(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_pwm_channels, 8U, (t_pwm_mode *)
        &P4p2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_pwm_channels =
          P4p2_P.HILInitialize_pwm_channels;
        int32_T *dw_POModeValues = &P4p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE) {
            P4p2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              p_HILInitialize_pwm_channels[i1];
            P4p2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              P4p2_P.HILInitialize_pwm_frequency;
            num_duty_cycle_modes++;
          } else {
            P4p2_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              p_HILInitialize_pwm_channels[i1];
            P4p2_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              P4p2_P.HILInitialize_pwm_frequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(P4p2_DW.HILInitialize_Card,
          &P4p2_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &P4p2_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P4p2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(P4p2_DW.HILInitialize_Card,
          &P4p2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &P4p2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P4p2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &P4p2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = P4p2_P.HILInitialize_pwm_configuration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &P4p2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = P4p2_P.HILInitialize_pwm_alignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals = &P4p2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = P4p2_P.HILInitialize_pwm_polarity;
        }
      }

      result = hil_set_pwm_configuration(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_pwm_channels, 8U,
        (t_pwm_configuration *) &P4p2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &P4p2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &P4p2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &P4p2_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = P4p2_P.HILInitialize_pwm_leading_deadb;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &P4p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P4p2_P.HILInitialize_pwm_trailing_dead;
        }
      }

      result = hil_set_pwm_deadband(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_pwm_channels, 8U,
        &P4p2_DW.HILInitialize_POSortedFreqs[0],
        &P4p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if ((P4p2_P.HILInitialize_set_pwm_outputs_a && !is_switching) ||
        (P4p2_P.HILInitialize_set_pwm_outputs_g && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P4p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P4p2_P.HILInitialize_initial_pwm_outpu;
        }
      }

      result = hil_write_pwm(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_pwm_channels, 8U, &P4p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }

    if (P4p2_P.HILInitialize_set_pwm_outputs_o) {
      {
        int_T i1;
        real_T *dw_POValues = &P4p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P4p2_P.HILInitialize_watchdog_pwm_outp;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state(P4p2_DW.HILInitialize_Card,
        P4p2_P.HILInitialize_pwm_channels, 8U, &P4p2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: P4p2/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(P4p2_DW.HILInitialize_Card,
      P4p2_P.HILReadEncoderTimebase_samples_,
      P4p2_P.HILReadEncoderTimebase_channels, 3,
      &P4p2_DW.HILReadEncoderTimebase_Task);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(P4p2_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<S5>/To File' */
  {
    char fileName[509] = "FILENAME.mat";
    FILE *fp = (NULL);
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(P4p2_M, "Error creating .mat file FILENAME.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp,13,0,"ans")) {
      rtmSetErrorStatus(P4p2_M,
                        "Error writing mat file header to file FILENAME.mat");
      return;
    }

    P4p2_DW.ToFile_IWORK.Count = 0;
    P4p2_DW.ToFile_IWORK.Decimation = -1;
    P4p2_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S3>/Rate Transition: x' */
  P4p2_B.RateTransitionx = P4p2_P.RateTransitionx_X0;

  /* Start for RateTransition: '<S3>/Rate Transition: y' */
  P4p2_B.RateTransitiony = P4p2_P.RateTransitiony_X0;

  /* Start for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P4p2/Joystick/Game Controller (game_controller_block) */
  {
    if (P4p2_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open(P4p2_P.GameController_ControllerNumber,
        P4p2_P.GameController_BufferSize, deadzone, saturation,
        P4p2_P.GameController_AutoCenter, 0, 1.0,
        &P4p2_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(P4p2_M, _rt_error_message);
      }
    }
  }

  {
    int32_T i;

    /* InitializeConditions for Integrator: '<S6>/Integrator' */
    for (i = 0; i < 6; i++) {
      P4p2_X.Integrator_CSTATE[i] = P4p2_P.Integrator_IC;
    }

    /* End of InitializeConditions for Integrator: '<S6>/Integrator' */

    /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
    P4p2_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
    P4p2_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
    P4p2_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for RateTransition: '<S3>/Rate Transition: x' */
    P4p2_DW.RateTransitionx_Buffer0 = P4p2_P.RateTransitionx_X0;

    /* InitializeConditions for RateTransition: '<S3>/Rate Transition: y' */
    P4p2_DW.RateTransitiony_Buffer0 = P4p2_P.RateTransitiony_X0;
  }
}

/* Model terminate function */
void P4p2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: P4p2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(P4p2_DW.HILInitialize_Card);
    hil_monitor_stop_all(P4p2_DW.HILInitialize_Card);
    is_switching = false;
    if ((P4p2_P.HILInitialize_set_analog_out_ex && !is_switching) ||
        (P4p2_P.HILInitialize_set_analog_outp_c && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &P4p2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = P4p2_P.HILInitialize_final_analog_outp;
        }
      }

      num_final_analog_outputs = 8U;
    }

    if ((P4p2_P.HILInitialize_set_pwm_output_ap && !is_switching) ||
        (P4p2_P.HILInitialize_set_pwm_outputs_p && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &P4p2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = P4p2_P.HILInitialize_final_pwm_outputs;
        }
      }

      num_final_pwm_outputs = 8U;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(P4p2_DW.HILInitialize_Card
                         , P4p2_P.HILInitialize_analog_output_cha,
                         num_final_analog_outputs
                         , P4p2_P.HILInitialize_pwm_channels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &P4p2_DW.HILInitialize_AOVoltages[0]
                         , &P4p2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(P4p2_DW.HILInitialize_Card,
            P4p2_P.HILInitialize_analog_output_cha, num_final_analog_outputs,
            &P4p2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(P4p2_DW.HILInitialize_Card,
            P4p2_P.HILInitialize_pwm_channels, num_final_pwm_outputs,
            &P4p2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(P4p2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(P4p2_DW.HILInitialize_Card);
    hil_monitor_delete_all(P4p2_DW.HILInitialize_Card);
    hil_close(P4p2_DW.HILInitialize_Card);
    P4p2_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<S5>/To File' */
  {
    FILE *fp = (FILE *) P4p2_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "FILENAME.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P4p2_M, "Error closing MAT-file FILENAME.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(P4p2_M, "Error reopening MAT-file FILENAME.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 13, P4p2_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(P4p2_M,
                          "Error writing header for ans to MAT-file FILENAME.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(P4p2_M, "Error closing MAT-file FILENAME.mat");
        return;
      }

      P4p2_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: P4p2/Joystick/Game Controller (game_controller_block) */
  {
    if (P4p2_P.GameController_Enabled) {
      game_controller_close(P4p2_DW.GameController_Controller);
      P4p2_DW.GameController_Controller = NULL;
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P4p2_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  P4p2_update(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  P4p2_initialize();
}

void MdlTerminate(void)
{
  P4p2_terminate();
}

/* Registration function */
RT_MODEL_P4p2_T *P4p2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)P4p2_M, 0,
                sizeof(RT_MODEL_P4p2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&P4p2_M->solverInfo, &P4p2_M->Timing.simTimeStep);
    rtsiSetTPtr(&P4p2_M->solverInfo, &rtmGetTPtr(P4p2_M));
    rtsiSetStepSizePtr(&P4p2_M->solverInfo, &P4p2_M->Timing.stepSize0);
    rtsiSetdXPtr(&P4p2_M->solverInfo, &P4p2_M->ModelData.derivs);
    rtsiSetContStatesPtr(&P4p2_M->solverInfo, (real_T **)
                         &P4p2_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&P4p2_M->solverInfo, &P4p2_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&P4p2_M->solverInfo, (&rtmGetErrorStatus(P4p2_M)));
    rtsiSetRTModelPtr(&P4p2_M->solverInfo, P4p2_M);
  }

  rtsiSetSimTimeStep(&P4p2_M->solverInfo, MAJOR_TIME_STEP);
  P4p2_M->ModelData.intgData.f[0] = P4p2_M->ModelData.odeF[0];
  P4p2_M->ModelData.contStates = ((real_T *) &P4p2_X);
  rtsiSetSolverData(&P4p2_M->solverInfo, (void *)&P4p2_M->ModelData.intgData);
  rtsiSetSolverName(&P4p2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = P4p2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    P4p2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    P4p2_M->Timing.sampleTimes = (&P4p2_M->Timing.sampleTimesArray[0]);
    P4p2_M->Timing.offsetTimes = (&P4p2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    P4p2_M->Timing.sampleTimes[0] = (0.0);
    P4p2_M->Timing.sampleTimes[1] = (0.002);
    P4p2_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    P4p2_M->Timing.offsetTimes[0] = (0.0);
    P4p2_M->Timing.offsetTimes[1] = (0.0);
    P4p2_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(P4p2_M, &P4p2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = P4p2_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = P4p2_M->Timing.perTaskSampleHitsArray;
    P4p2_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    P4p2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(P4p2_M, -1);
  P4p2_M->Timing.stepSize0 = 0.002;
  P4p2_M->Timing.stepSize1 = 0.002;
  P4p2_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  P4p2_M->Sizes.checksums[0] = (2143762869U);
  P4p2_M->Sizes.checksums[1] = (3852614352U);
  P4p2_M->Sizes.checksums[2] = (2921030457U);
  P4p2_M->Sizes.checksums[3] = (3379520128U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    P4p2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(P4p2_M->extModeInfo,
      &P4p2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(P4p2_M->extModeInfo, P4p2_M->Sizes.checksums);
    rteiSetTPtr(P4p2_M->extModeInfo, rtmGetTPtr(P4p2_M));
  }

  P4p2_M->solverInfoPtr = (&P4p2_M->solverInfo);
  P4p2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&P4p2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&P4p2_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  P4p2_M->ModelData.blockIO = ((void *) &P4p2_B);

  {
    int_T i;
    for (i = 0; i < 6; i++) {
      P4p2_B.radtodeg1[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      P4p2_B.Sum_c[i] = 0.0;
    }

    P4p2_B.PitchCounttorad = 0.0;
    P4p2_B.Pitchoffset = 0.0;
    P4p2_B.Sum1 = 0.0;
    P4p2_B.ElevationCounttorad = 0.0;
    P4p2_B.Gain = 0.0;
    P4p2_B.TravelCounttorad = 0.0;
    P4p2_B.Gain_d = 0.0;
    P4p2_B.Gain_i = 0.0;
    P4p2_B.Sum2 = 0.0;
    P4p2_B.Sum = 0.0;
    P4p2_B.RateTransitionx = 0.0;
    P4p2_B.Joystick_gain_x = 0.0;
    P4p2_B.RateTransitiony = 0.0;
    P4p2_B.Joystick_gain_y = 0.0;
    P4p2_B.Referencefeedforward[0] = 0.0;
    P4p2_B.Referencefeedforward[1] = 0.0;
    P4p2_B.FrontmotorSaturation = 0.0;
    P4p2_B.BackmotorSaturation = 0.0;
    P4p2_B.GameController_o4 = 0.0;
    P4p2_B.GameController_o5 = 0.0;
  }

  /* parameters */
  P4p2_M->ModelData.defaultParam = ((real_T *)&P4p2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &P4p2_X;
    P4p2_M->ModelData.contStates = (x);
    (void) memset((void *)&P4p2_X, 0,
                  sizeof(X_P4p2_T));
  }

  /* states (dwork) */
  P4p2_M->ModelData.dwork = ((void *) &P4p2_DW);
  (void) memset((void *)&P4p2_DW, 0,
                sizeof(DW_P4p2_T));

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int_T i;
    for (i = 0; i < 8; i++) {
      P4p2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  P4p2_DW.RateTransitionx_Buffer0 = 0.0;
  P4p2_DW.RateTransitiony_Buffer0 = 0.0;
  P4p2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  P4p2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    P4p2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  P4p2_M->Sizes.numContStates = (9);   /* Number of continuous states */
  P4p2_M->Sizes.numY = (0);            /* Number of model outputs */
  P4p2_M->Sizes.numU = (0);            /* Number of model inputs */
  P4p2_M->Sizes.sysDirFeedThru = (0);  /* The model is not direct feedthrough */
  P4p2_M->Sizes.numSampTimes = (3);    /* Number of sample times */
  P4p2_M->Sizes.numBlocks = (61);      /* Number of blocks */
  P4p2_M->Sizes.numBlockIO = (21);     /* Number of block outputs */
  P4p2_M->Sizes.numBlockPrms = (241);  /* Sum of parameter "widths" */
  return P4p2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
