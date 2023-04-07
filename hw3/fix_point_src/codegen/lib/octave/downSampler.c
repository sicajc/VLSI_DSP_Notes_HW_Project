/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: downSampler.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

/* Include Files */
#include "downSampler.h"
#include "octave.h"
#include "octave_emxutil.h"
#include "octave_rtwutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *img
 *                double stride
 *                emxArray_real_T *downSampledimg
 * Return Type  : void
 */
void b_downSampler(const emxArray_real_T *img, double stride, emxArray_real_T
                   *downSampledimg)
{
  int i;
  int loop_ub;
  int i1;
  int i2;
  int b_loop_ub;
  int i3;
  i = downSampledimg->size[0] * downSampledimg->size[1];
  downSampledimg->size[0] = img->size[0];
  downSampledimg->size[1] = img->size[0];
  emxEnsureCapacity_real_T(downSampledimg, i);
  loop_ub = img->size[0] * img->size[0];
  for (i = 0; i < loop_ub; i++) {
    downSampledimg->data[i] = 0.0;
  }

  /* odd for LPF */
  if ((stride == 0.0) || (((stride > 0.0) && (1 > img->size[0])) || ((0.0 >
         stride) && (img->size[0] > 1)))) {
    i = 1;
    i1 = 0;
  } else {
    i = (int)stride;
    i1 = img->size[0];
  }

  if (1 > img->size[1]) {
    loop_ub = 0;
  } else {
    loop_ub = img->size[1];
  }

  for (i2 = 0; i2 < loop_ub; i2++) {
    b_loop_ub = div_s32_floor(i1 - 1, i);
    for (i3 = 0; i3 <= b_loop_ub; i3++) {
      downSampledimg->data[i3 + downSampledimg->size[0] * i2] = img->data[i * i3
        + img->size[0] * i2] * 2.0;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *img
 *                double stride
 *                emxArray_real_T *downSampledimg
 * Return Type  : void
 */
void downSampler(const emxArray_real_T *img, double stride, emxArray_real_T
                 *downSampledimg)
{
  int i;
  int loop_ub;
  int i1;
  int i2;
  int i3;
  int b_loop_ub;
  int i4;
  i = downSampledimg->size[0] * downSampledimg->size[1];
  downSampledimg->size[0] = img->size[0];
  downSampledimg->size[1] = img->size[0];
  emxEnsureCapacity_real_T(downSampledimg, i);
  loop_ub = img->size[0] * img->size[0];
  for (i = 0; i < loop_ub; i++) {
    downSampledimg->data[i] = 0.0;
  }

  /* even for HPF */
  if ((stride == 0.0) || (((stride > 0.0) && (2 > img->size[0])) || ((0.0 >
         stride) && (img->size[0] > 2)))) {
    i = 0;
    i1 = 1;
    i2 = 0;
  } else {
    i = 1;
    i1 = (int)stride;
    i2 = img->size[0];
  }

  if (1 > img->size[1]) {
    loop_ub = 0;
  } else {
    loop_ub = img->size[1];
  }

  for (i3 = 0; i3 < loop_ub; i3++) {
    b_loop_ub = div_s32_floor((i2 - i) - 1, i1);
    for (i4 = 0; i4 <= b_loop_ub; i4++) {
      downSampledimg->data[i4 + downSampledimg->size[0] * i3] = img->data[(i +
        i1 * i4) + img->size[0] * i3];
    }
  }
}

/*
 * File trailer for downSampler.c
 *
 * [EOF]
 */
