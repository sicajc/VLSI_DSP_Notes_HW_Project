/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: dwt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 19:49:54
 */

/* Include Files */
#include "dwt.h"
#include "octave.h"

/* Function Definitions */

/*
 * Octave 1
 * Arguments    : const double raw_img[262144]
 *                double stride
 *                double filtered_img[262144]
 * Return Type  : void
 */
void dwt(const double raw_img[262144], double stride, double filtered_img[262144])
{
  static double b_dv[262144];
  static double b_dv1[262144];

  /*  Octave 2 */
  /*  Octave 3 */
  octave(raw_img, stride, b_dv);
  b_octave(b_dv, stride, b_dv1);
  c_octave(b_dv1, stride, filtered_img);
}

/*
 * File trailer for dwt.c
 *
 * [EOF]
 */
