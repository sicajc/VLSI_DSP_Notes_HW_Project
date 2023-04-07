/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: dwt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 12:06:50
 */

/* Include Files */
#include "dwt.h"
#include "octave.h"
#include <string.h>

/* Function Definitions */

/*
 * Octave 1
 * Arguments    : const int raw_img[262144]
 *                double stride
 *                int filtered_img[262144]
 * Return Type  : void
 */
void dwt(const int raw_img[262144], double stride, int filtered_img[262144])
{
  memcpy(&filtered_img[0], &raw_img[0], 262144U * sizeof(int));
  octave(filtered_img, stride);

  /*  Octave 2 */
  b_octave(filtered_img, stride);

  /*  Octave 3 */
  c_octave(filtered_img, stride);
}

/*
 * File trailer for dwt.c
 *
 * [EOF]
 */
