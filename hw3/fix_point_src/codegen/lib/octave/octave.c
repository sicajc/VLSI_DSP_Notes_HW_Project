/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

/* Include Files */
#include "octave.h"
#include "downSampler.h"
#include "gn_HPF.h"
#include "hn_LPF.h"
#include "octave_data.h"
#include "octave_emxutil.h"
#include "octave_initialize.h"
#include "octave_rtwutil.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double y;
  double d;
  double d1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

/*
 * Arguments    : const double raw_img[262144]
 *                double stride
 *                double n
 *                double filtered_img[262144]
 * Return Type  : void
 */
void octave(const double raw_img[262144], double stride, double n, double
            filtered_img[262144])
{
  int i;
  emxArray_real_T *b_raw_img;
  double partition;
  double d;
  int loop_ub;
  int b_loop_ub;
  emxArray_real_T *H1;
  int i1;
  emxArray_real_T *H1_;
  int i2;
  int i3;
  emxArray_real_T *L1_;
  emxArray_real_T *LH_;
  double d1;
  emxArray_real_T *HH_;
  double d2;
  if (!isInitialized_octave) {
    octave_initialize();
  }

  for (i = 0; i < 262144; i++) {
    filtered_img[i] = raw_img[i] * 0.5;
  }

  emxInit_real_T(&b_raw_img, 2);
  partition = rt_powd_snf(2.0, n);

  /*  Horizontal */
  d = 512.0 / (partition / 2.0);
  if (1.0 > d) {
    loop_ub = 0;
    b_loop_ub = 0;
  } else {
    loop_ub = (int)d;
    b_loop_ub = (int)d;
  }

  i = b_raw_img->size[0] * b_raw_img->size[1];
  b_raw_img->size[0] = loop_ub;
  b_raw_img->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_raw_img, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_raw_img->data[i1 + b_raw_img->size[0] * i] = raw_img[i1 + (i << 9)];
    }
  }

  emxInit_real_T(&H1, 2);
  emxInit_real_T(&H1_, 2);
  gn_HPF(b_raw_img, H1);
  i = H1_->size[0] * H1_->size[1];
  H1_->size[0] = H1->size[0];
  H1_->size[1] = H1->size[0];
  emxEnsureCapacity_real_T(H1_, i);
  loop_ub = H1->size[0] * H1->size[0];
  for (i = 0; i < loop_ub; i++) {
    H1_->data[i] = 0.0;
  }

  /* even for HPF */
  if (1 > H1->size[0]) {
    loop_ub = 0;
  } else {
    loop_ub = H1->size[0];
  }

  if ((stride == 0.0) || (((stride > 0.0) && (2 > H1->size[1])) || ((0.0 >
         stride) && (H1->size[1] > 2)))) {
    i = 0;
    i1 = 1;
    i2 = 0;
  } else {
    i = 1;
    i1 = (int)stride;
    i2 = H1->size[1];
  }

  b_loop_ub = div_s32_floor((i2 - i) - 1, i1);
  for (i2 = 0; i2 <= b_loop_ub; i2++) {
    for (i3 = 0; i3 < loop_ub; i3++) {
      H1_->data[i3 + H1_->size[0] * i2] = H1->data[i3 + H1->size[0] * (i + i1 *
        i2)];
    }
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  if (1.0 > d) {
    loop_ub = 0;
    b_loop_ub = 0;
  } else {
    loop_ub = (int)d;
    b_loop_ub = (int)d;
  }

  i = b_raw_img->size[0] * b_raw_img->size[1];
  b_raw_img->size[0] = loop_ub;
  b_raw_img->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_raw_img, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_raw_img->data[i1 + b_raw_img->size[0] * i] = raw_img[i1 + (i << 9)];
    }
  }

  emxInit_real_T(&L1_, 2);
  hn_LPF(b_raw_img, H1);
  i = L1_->size[0] * L1_->size[1];
  L1_->size[0] = H1->size[0];
  L1_->size[1] = H1->size[0];
  emxEnsureCapacity_real_T(L1_, i);
  loop_ub = H1->size[0] * H1->size[0];
  for (i = 0; i < loop_ub; i++) {
    L1_->data[i] = 0.0;
  }

  /* odd for LPF */
  if (1 > H1->size[0]) {
    loop_ub = 0;
  } else {
    loop_ub = H1->size[0];
  }

  if ((stride == 0.0) || (((stride > 0.0) && (1 > H1->size[1])) || ((0.0 >
         stride) && (H1->size[1] > 1)))) {
    i = 1;
    i1 = 0;
  } else {
    i = (int)stride;
    i1 = H1->size[1];
  }

  b_loop_ub = div_s32_floor(i1 - 1, i);
  for (i1 = 0; i1 <= b_loop_ub; i1++) {
    for (i2 = 0; i2 < loop_ub; i2++) {
      L1_->data[i2 + L1_->size[0] * i1] = H1->data[i2 + H1->size[0] * (i * i1)] *
        2.0;
    }
  }

  emxInit_real_T(&LH_, 2);

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  if (1.0 > d) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  i = LH_->size[0] * LH_->size[1];
  LH_->size[0] = loop_ub;
  LH_->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(LH_, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      LH_->data[i1 + LH_->size[0] * i] = H1_->data[i1 + H1_->size[0] * i];
    }
  }

  emxInit_real_T(&HH_, 2);
  b_gn_HPF(LH_, b_raw_img);
  downSampler(b_raw_img, stride, HH_);
  if (1.0 > d) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  i = b_raw_img->size[0] * b_raw_img->size[1];
  b_raw_img->size[0] = loop_ub;
  b_raw_img->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_raw_img, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_raw_img->data[i1 + b_raw_img->size[0] * i] = H1_->data[i1 + H1_->size[0]
        * i];
    }
  }

  i = H1_->size[0] * H1_->size[1];
  H1_->size[0] = b_raw_img->size[0];
  H1_->size[1] = b_raw_img->size[1];
  emxEnsureCapacity_real_T(H1_, i);
  loop_ub = b_raw_img->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_raw_img->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      H1_->data[i1 + H1_->size[0] * i] = b_raw_img->data[i1 + b_raw_img->size[0]
        * i];
    }
  }

  b_hn_LPF(H1_, b_raw_img);
  b_downSampler(b_raw_img, stride, H1_);
  if (1.0 > d) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  i = LH_->size[0] * LH_->size[1];
  LH_->size[0] = loop_ub;
  LH_->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(LH_, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      LH_->data[i1 + LH_->size[0] * i] = L1_->data[i1 + L1_->size[0] * i];
    }
  }

  b_gn_HPF(LH_, b_raw_img);
  downSampler(b_raw_img, stride, LH_);
  if (1.0 > d) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  i = b_raw_img->size[0] * b_raw_img->size[1];
  b_raw_img->size[0] = loop_ub;
  b_raw_img->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_raw_img, i);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      b_raw_img->data[i1 + b_raw_img->size[0] * i] = L1_->data[i1 + L1_->size[0]
        * i];
    }
  }

  i = L1_->size[0] * L1_->size[1];
  L1_->size[0] = b_raw_img->size[0];
  L1_->size[1] = b_raw_img->size[1];
  emxEnsureCapacity_real_T(L1_, i);
  loop_ub = b_raw_img->size[1];
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_raw_img->size[0];
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      L1_->data[i1 + L1_->size[0] * i] = b_raw_img->data[i1 + b_raw_img->size[0]
        * i];
    }
  }

  b_hn_LPF(L1_, b_raw_img);
  b_downSampler(b_raw_img, stride, H1);

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  d1 = 512.0 / partition;
  if (1.0 > d1) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d1;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  emxFree_real_T(&b_raw_img);
  emxFree_real_T(&L1_);
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      filtered_img[i1 + (i << 9)] = H1->data[i1 + H1->size[0] * i] * 0.5;
    }
  }

  emxFree_real_T(&H1);
  d1 = 512.0 / partition;
  if (1.0 > d1) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d1;
  }

  d1 = 512.0 / partition;
  if (1.0 > d1) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d1;
  }

  d1 = 512.0 / partition + 1.0;
  if (d1 > d) {
    i = 1;
  } else {
    i = (int)d1;
  }

  for (i1 = 0; i1 < b_loop_ub; i1++) {
    for (i2 = 0; i2 < loop_ub; i2++) {
      filtered_img[i2 + (((i + i1) - 1) << 9)] = H1_->data[i2 + H1_->size[0] *
        i1] * 0.5;
    }
  }

  emxFree_real_T(&H1_);
  d2 = 512.0 / partition;
  if (1.0 > d2) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d2;
  }

  d2 = 512.0 / partition;
  if (1.0 > d2) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d2;
  }

  if (d1 > d) {
    i = 1;
  } else {
    i = (int)d1;
  }

  for (i1 = 0; i1 < b_loop_ub; i1++) {
    for (i2 = 0; i2 < loop_ub; i2++) {
      filtered_img[((i + i2) + (i1 << 9)) - 1] = LH_->data[i2 + LH_->size[0] *
        i1] * 0.5;
    }
  }

  emxFree_real_T(&LH_);
  d2 = 512.0 / partition;
  if (1.0 > d2) {
    loop_ub = 0;
  } else {
    loop_ub = (int)d2;
  }

  d2 = 512.0 / partition;
  if (1.0 > d2) {
    b_loop_ub = 0;
  } else {
    b_loop_ub = (int)d2;
  }

  if (d1 > d) {
    i = 1;
    i1 = 1;
  } else {
    i = (int)d1;
    i1 = i;
  }

  for (i2 = 0; i2 < b_loop_ub; i2++) {
    for (i3 = 0; i3 < loop_ub; i3++) {
      filtered_img[((i + i3) + (((i1 + i2) - 1) << 9)) - 1] = HH_->data[i3 +
        HH_->size[0] * i2] * 0.5;
    }
  }

  emxFree_real_T(&HH_);
}

/*
 * File trailer for octave.c
 *
 * [EOF]
 */
