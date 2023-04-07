/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: dwt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
 */

/* Include Files */
#include "dwt.h"
#include "octave.h"

/* Function Definitions */

/*
 * Octave 1
 * Arguments    : const short raw_img[262144]
 *                double stride
 *                short filtered_img[262144]
 * Return Type  : void
 */
void dwt(const short raw_img[262144], double stride, short filtered_img[262144])
{
  static short b_iv[262144];
  static short b_iv1[262144];

  /*  Octave 2 */
  /*  Octave 3 */
  octave(raw_img, stride, b_iv);
  b_octave(b_iv, stride, b_iv1);
  c_octave(b_iv1, stride, filtered_img);
}

/*
 * File trailer for dwt.c
 *
 * [EOF]
 */
