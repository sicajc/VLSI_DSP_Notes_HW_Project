/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 19:49:54
 */

/* Include Files */
#include "octave.h"
#include "dwt.h"
#include "dwt_emxutil.h"
#include "filterSystem.h"
#include <string.h>

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

/* Function Definitions */

/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

/*
 * Arguments    : const double raw_img[262144]
 *                double stride
 *                double filtered_img[262144]
 * Return Type  : void
 */
void b_octave(const double raw_img[262144], double stride, double filtered_img
              [262144])
{
  int i;
  int i1;
  int b_i;
  static double LL_[65536];
  static double H1_[65536];
  double b_LL_[256];
  double b_dv[256];
  int filtered_img_tmp;
  emxArray_real_T *c_LL_;
  int b_filtered_img_tmp;
  static double L1_[65536];
  static double HH_[65536];
  static double b_raw_img[32768];
  emxArray_real_T *c_raw_img;
  static double LH_[65536];
  unsigned char c_filtered_img_tmp[128];
  for (i = 0; i < 262144; i++) {
    filtered_img[i] = raw_img[i] * 32.0;
  }

  /*  Horizontal */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      LL_[i1 + (i << 8)] = raw_img[i1 + (i << 9)] * 32.0;
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    for (i = 0; i < 256; i++) {
      b_LL_[i] = LL_[b_i + (i << 8)];
    }

    c_filterSystem(b_LL_, b_dv);
    for (i = 0; i < 256; i++) {
      LL_[b_i + (i << 8)] = b_dv[i];
    }
  }

  memset(&H1_[0], 0, 65536U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 255;
  }

  emxInit_real_T(&c_LL_, 2);
  b_filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 256;
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, b_filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp < 256; b_filtered_img_tmp++)
    {
      c_LL_->data[b_filtered_img_tmp + 256 * filtered_img_tmp] =
        LL_[b_filtered_img_tmp + ((i + i1 * filtered_img_tmp) << 8)];
    }
  }

  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      b_i = i1 + (i << 8);
      H1_[b_i] = c_LL_->data[b_i];
    }
  }

  /*  Output types */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      LL_[i1 + (i << 8)] = raw_img[i1 + (i << 9)] * 32.0;
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 256; i++) {
      b_LL_[i] = LL_[b_i + (i << 8)];
    }

    d_filterSystem(b_LL_, b_dv);
    for (i = 0; i < 256; i++) {
      LL_[b_i + (i << 8)] = b_dv[i];
    }
  }

  memset(&L1_[0], 0, 65536U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 255;
  }

  filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 256;
  b_i = div_s32_floor(i1, i);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, filtered_img_tmp);
  for (i1 = 0; i1 <= b_i; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
      c_LL_->data[filtered_img_tmp + 256 * i1] = LL_[filtered_img_tmp + ((i * i1)
        << 8)];
    }
  }

  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      b_i = i1 + (i << 8);
      L1_[b_i] = c_LL_->data[b_i];
      b_raw_img[b_i] = H1_[b_i];
    }
  }

  emxFree_real_T(&c_LL_);

  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    i = b_i << 8;
    c_filterSystem(*(double (*)[256])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 256U * sizeof(double));
  }

  memset(&HH_[0], 0, 65536U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 255;
  }

  emxInit_real_T(&c_raw_img, 2);
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 128;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 128; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp <= b_i; b_filtered_img_tmp++)
    {
      c_raw_img->data[b_filtered_img_tmp + c_raw_img->size[0] * filtered_img_tmp]
        = b_raw_img[(i + i1 * b_filtered_img_tmp) + (filtered_img_tmp << 8)];
    }
  }

  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      HH_[i1 + (i << 8)] = c_raw_img->data[i1 + (i << 7)];
    }

    memcpy(&b_raw_img[i * 256], &H1_[i * 256], 256U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 8;
    d_filterSystem(*(double (*)[256])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 256U * sizeof(double));
  }

  memset(&H1_[0], 0, 65536U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 255;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 128;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 128; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 8)];
    }
  }

  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      H1_[i1 + (i << 8)] = c_raw_img->data[i1 + (i << 7)];
    }

    memcpy(&b_raw_img[i * 256], &L1_[i * 256], 256U * sizeof(double));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    i = b_i << 8;
    c_filterSystem(*(double (*)[256])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 256U * sizeof(double));
  }

  memset(&LH_[0], 0, 65536U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 255;
  }

  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 128;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 128; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp <= b_i; b_filtered_img_tmp++)
    {
      c_raw_img->data[b_filtered_img_tmp + c_raw_img->size[0] * filtered_img_tmp]
        = b_raw_img[(i + i1 * b_filtered_img_tmp) + (filtered_img_tmp << 8)];
    }
  }

  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      LH_[i1 + (i << 8)] = c_raw_img->data[i1 + (i << 7)];
    }

    memcpy(&b_raw_img[i * 256], &L1_[i * 256], 256U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 8;
    d_filterSystem(*(double (*)[256])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 256U * sizeof(double));
  }

  memset(&LL_[0], 0, 65536U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 255;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 128;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 128; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 8)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      LL_[i1 + (i << 8)] = c_raw_img->data[i1 + (i << 7)];
    }

    c_filtered_img_tmp[i] = (unsigned char)(i + 1U);
  }

  emxFree_real_T(&c_raw_img);
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      b_i = i1 + (i << 9);
      filtered_img[b_i] = LL_[(c_filtered_img_tmp[i1] + ((c_filtered_img_tmp[i]
        - 1) << 8)) - 1];
      filtered_img_tmp = i1 + (i << 8);
      b_filtered_img_tmp = i1 + ((i + 128) << 9);
      filtered_img[b_filtered_img_tmp] = H1_[filtered_img_tmp];
      filtered_img[b_i + 128] = LH_[filtered_img_tmp];
      filtered_img[b_filtered_img_tmp + 128] = HH_[filtered_img_tmp];
    }
  }
}

/*
 * Arguments    : const double raw_img[262144]
 *                double stride
 *                double filtered_img[262144]
 * Return Type  : void
 */
void c_octave(const double raw_img[262144], double stride, double filtered_img
              [262144])
{
  int i;
  int i1;
  int b_i;
  static double LL_[16384];
  static double H1_[16384];
  double b_LL_[128];
  double b_dv[128];
  int filtered_img_tmp;
  emxArray_real_T *c_LL_;
  int b_filtered_img_tmp;
  static double L1_[16384];
  static double HH_[16384];
  double b_raw_img[8192];
  emxArray_real_T *c_raw_img;
  static double LH_[16384];
  signed char c_filtered_img_tmp[64];
  for (i = 0; i < 262144; i++) {
    filtered_img[i] = raw_img[i] * 0.0625;
  }

  /*  Horizontal */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      LL_[i1 + (i << 7)] = raw_img[i1 + (i << 9)] * 0.0625;
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    for (i = 0; i < 128; i++) {
      b_LL_[i] = LL_[b_i + (i << 7)];
    }

    e_filterSystem(b_LL_, b_dv);
    for (i = 0; i < 128; i++) {
      LL_[b_i + (i << 7)] = b_dv[i];
    }
  }

  memset(&H1_[0], 0, 16384U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 127;
  }

  emxInit_real_T(&c_LL_, 2);
  b_filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 128;
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, b_filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp < 128; b_filtered_img_tmp++)
    {
      c_LL_->data[b_filtered_img_tmp + 128 * filtered_img_tmp] =
        LL_[b_filtered_img_tmp + ((i + i1 * filtered_img_tmp) << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      b_i = i1 + (i << 7);
      H1_[b_i] = c_LL_->data[b_i];
    }
  }

  /*  Output types */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      LL_[i1 + (i << 7)] = raw_img[i1 + (i << 9)] * 0.0625;
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 128; i++) {
      b_LL_[i] = LL_[b_i + (i << 7)];
    }

    f_filterSystem(b_LL_, b_dv);
    for (i = 0; i < 128; i++) {
      LL_[b_i + (i << 7)] = b_dv[i];
    }
  }

  memset(&L1_[0], 0, 16384U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 128;
  b_i = div_s32_floor(i1, i);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, filtered_img_tmp);
  for (i1 = 0; i1 <= b_i; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 128; filtered_img_tmp++) {
      c_LL_->data[filtered_img_tmp + 128 * i1] = LL_[filtered_img_tmp + ((i * i1)
        << 7)];
    }
  }

  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      b_i = i1 + (i << 7);
      L1_[b_i] = c_LL_->data[b_i];
      b_raw_img[b_i] = H1_[b_i];
    }
  }

  emxFree_real_T(&c_LL_);

  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    i = b_i << 7;
    e_filterSystem(*(double (*)[128])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 128U * sizeof(double));
  }

  memset(&HH_[0], 0, 16384U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 127;
  }

  emxInit_real_T(&c_raw_img, 2);
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 64;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 64; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp <= b_i; b_filtered_img_tmp++)
    {
      c_raw_img->data[b_filtered_img_tmp + c_raw_img->size[0] * filtered_img_tmp]
        = b_raw_img[(i + i1 * b_filtered_img_tmp) + (filtered_img_tmp << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      HH_[i1 + (i << 7)] = c_raw_img->data[i1 + (i << 6)];
    }

    memcpy(&b_raw_img[i * 128], &H1_[i * 128], 128U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 7;
    f_filterSystem(*(double (*)[128])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 128U * sizeof(double));
  }

  memset(&H1_[0], 0, 16384U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 64;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 64; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      H1_[i1 + (i << 7)] = c_raw_img->data[i1 + (i << 6)];
    }

    memcpy(&b_raw_img[i * 128], &L1_[i * 128], 128U * sizeof(double));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    i = b_i << 7;
    e_filterSystem(*(double (*)[128])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 128U * sizeof(double));
  }

  memset(&LH_[0], 0, 16384U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 127;
  }

  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 64;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 64; filtered_img_tmp++) {
    for (b_filtered_img_tmp = 0; b_filtered_img_tmp <= b_i; b_filtered_img_tmp++)
    {
      c_raw_img->data[b_filtered_img_tmp + c_raw_img->size[0] * filtered_img_tmp]
        = b_raw_img[(i + i1 * b_filtered_img_tmp) + (filtered_img_tmp << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      LH_[i1 + (i << 7)] = c_raw_img->data[i1 + (i << 6)];
    }

    memcpy(&b_raw_img[i * 128], &L1_[i * 128], 128U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 7;
    f_filterSystem(*(double (*)[128])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 128U * sizeof(double));
  }

  memset(&LL_[0], 0, 16384U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 64;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 64; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 7)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      LL_[i1 + (i << 7)] = c_raw_img->data[i1 + (i << 6)];
    }

    c_filtered_img_tmp[i] = (signed char)(i + 1);
  }

  emxFree_real_T(&c_raw_img);
  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      b_i = i1 + (i << 9);
      filtered_img[b_i] = LL_[(c_filtered_img_tmp[i1] + ((c_filtered_img_tmp[i]
        - 1) << 7)) - 1];
      filtered_img_tmp = i1 + (i << 7);
      b_filtered_img_tmp = i1 + ((i + 64) << 9);
      filtered_img[b_filtered_img_tmp] = H1_[filtered_img_tmp];
      filtered_img[b_i + 64] = LH_[filtered_img_tmp];
      filtered_img[b_filtered_img_tmp + 64] = HH_[filtered_img_tmp];
    }
  }
}

/*
 * Arguments    : const double raw_img[262144]
 *                double stride
 *                double filtered_img[262144]
 * Return Type  : void
 */
void octave(const double raw_img[262144], double stride, double filtered_img
            [262144])
{
  int i;
  int b_i;
  static double LL_[262144];
  static double H1_[262144];
  double b_LL_[512];
  double b_dv[512];
  int i1;
  int filtered_img_tmp;
  emxArray_real_T *c_LL_;
  int i2;
  static double L1_[262144];
  static double HH_[262144];
  static double b_raw_img[131072];
  emxArray_real_T *c_raw_img;
  static double LH_[262144];
  short b_filtered_img_tmp[256];

  /*  Horizontal */
  for (i = 0; i < 262144; i++) {
    filtered_img[i] = raw_img[i] * 0.5;
    LL_[i] = raw_img[i] * 0.5;
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 512; b_i++) {
    for (i = 0; i < 512; i++) {
      b_LL_[i] = LL_[b_i + (i << 9)];
    }

    filterSystem(b_LL_, b_dv);
    for (i = 0; i < 512; i++) {
      LL_[b_i + (i << 9)] = b_dv[i];
    }
  }

  memset(&H1_[0], 0, 262144U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 511;
  }

  emxInit_real_T(&c_LL_, 2);
  i2 = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 512;
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, i2);
  for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
    for (i2 = 0; i2 < 512; i2++) {
      c_LL_->data[i2 + 512 * filtered_img_tmp] = LL_[i2 + ((i + i1 *
        filtered_img_tmp) << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 512; i1++) {
      b_i = i1 + (i << 9);
      H1_[b_i] = c_LL_->data[b_i];
    }
  }

  /*  Output types */
  for (i = 0; i < 262144; i++) {
    LL_[i] = raw_img[i] * 0.5;
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 512; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 512; i++) {
      b_LL_[i] = LL_[b_i + (i << 9)];
    }

    b_filterSystem(b_LL_, b_dv);
    for (i = 0; i < 512; i++) {
      LL_[b_i + (i << 9)] = b_dv[i];
    }
  }

  memset(&L1_[0], 0, 262144U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 511;
  }

  filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 512;
  b_i = div_s32_floor(i1, i);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_real_T(c_LL_, filtered_img_tmp);
  for (i1 = 0; i1 <= b_i; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 512; filtered_img_tmp++) {
      c_LL_->data[filtered_img_tmp + 512 * i1] = LL_[filtered_img_tmp + ((i * i1)
        << 9)];
    }
  }

  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 512; i1++) {
      b_i = i1 + (i << 9);
      L1_[b_i] = c_LL_->data[b_i];
      b_raw_img[b_i] = H1_[b_i];
    }
  }

  emxFree_real_T(&c_LL_);

  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    i = b_i << 9;
    filterSystem(*(double (*)[512])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 512U * sizeof(double));
  }

  memset(&HH_[0], 0, 262144U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 511;
  }

  emxInit_real_T(&c_raw_img, 2);
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
    for (i2 = 0; i2 <= b_i; i2++) {
      c_raw_img->data[i2 + c_raw_img->size[0] * filtered_img_tmp] = b_raw_img[(i
        + i1 * i2) + (filtered_img_tmp << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      HH_[i1 + (i << 9)] = c_raw_img->data[i1 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &H1_[i * 512], 512U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 9;
    b_filterSystem(*(double (*)[512])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 512U * sizeof(double));
  }

  memset(&H1_[0], 0, 262144U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 511;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 256; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      H1_[i1 + (i << 9)] = c_raw_img->data[i1 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &L1_[i * 512], 512U * sizeof(double));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    i = b_i << 9;
    filterSystem(*(double (*)[512])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 512U * sizeof(double));
  }

  memset(&LH_[0], 0, 262144U * sizeof(double));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    filtered_img_tmp = 511;
  }

  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_real_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
    for (i2 = 0; i2 <= b_i; i2++) {
      c_raw_img->data[i2 + c_raw_img->size[0] * filtered_img_tmp] = b_raw_img[(i
        + i1 * i2) + (filtered_img_tmp << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      LH_[i1 + (i << 9)] = c_raw_img->data[i1 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &L1_[i * 512], 512U * sizeof(double));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 9;
    b_filterSystem(*(double (*)[512])&b_raw_img[i], b_dv);
    memcpy(&b_raw_img[i], &b_dv[0], 512U * sizeof(double));
  }

  memset(&LL_[0], 0, 262144U * sizeof(double));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 511;
  }

  b_i = div_s32_floor(i1, i);
  i1 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_real_T(c_raw_img, i1);
  for (i1 = 0; i1 < 256; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i1] = b_raw_img[i *
        filtered_img_tmp + (i1 << 9)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      LL_[i1 + (i << 9)] = c_raw_img->data[i1 + (i << 8)];
    }

    b_filtered_img_tmp[i] = (short)(i + 1);
  }

  emxFree_real_T(&c_raw_img);
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      b_i = i1 + (i << 9);
      filtered_img[b_i] = LL_[(b_filtered_img_tmp[i1] + ((b_filtered_img_tmp[i]
        - 1) << 9)) - 1];
      filtered_img_tmp = i1 + ((i + 256) << 9);
      filtered_img[filtered_img_tmp] = H1_[b_i];
      filtered_img[b_i + 256] = LH_[b_i];
      filtered_img[filtered_img_tmp + 256] = HH_[b_i];
    }
  }
}

/*
 * File trailer for octave.c
 *
 * [EOF]
 */
