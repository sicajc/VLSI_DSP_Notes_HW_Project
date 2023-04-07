/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave_terminate.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

/* Include Files */
#include "octave_terminate.h"
#include "octave.h"
#include "octave_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void octave_terminate(void)
{
  /* (no terminate code required) */
  isInitialized_octave = false;
}

/*
 * File trailer for octave_terminate.c
 *
 * [EOF]
 */
