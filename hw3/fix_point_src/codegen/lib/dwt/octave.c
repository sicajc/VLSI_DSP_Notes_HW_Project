/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 12:06:50
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
 * Arguments    : int raw_img[262144]
 *                double stride
 * Return Type  : void
 */
void b_octave(int raw_img[262144], double stride)
{
  int i;
  static int H1_[65536];
  int b_i;
  int filtered_col[256];
  int b_iv[256];
  int i1;
  static int LL_[65536];
  emxArray_int32_T *b_LL_;
  int i2;
  int loop_ub;
  static int L1_[65536];
  static int HH_[65536];
  int L1__tmp;
  int filtered_img[32768];
  emxArray_int32_T *b_filtered_img;
  static int LH_[65536];
  unsigned char filtered_img_tmp[128];

  /*  Horizontal */
  /* Horizontal filtering */
  for (i = 0; i < 256; i++) {
    for (b_i = 0; b_i < 256; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    c_filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 256; b_i++) {
      LL_[i + (b_i << 8)] = b_iv[b_i];
    }
  }

  memset(&H1_[0], 0, 65536U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 255;
  }

  emxInit_int32_T(&b_LL_, 2);
  i2 = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 256;
  loop_ub = div_s32_floor(i - b_i, i1);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, i2);
  for (i = 0; i <= loop_ub; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      b_LL_->data[i2 + 256 * i] = LL_[i2 + ((b_i + i1 * i) << 8)];
    }
  }

  for (b_i = 0; b_i < 128; b_i++) {
    for (i1 = 0; i1 < 256; i1++) {
      loop_ub = i1 + (b_i << 8);
      H1_[loop_ub] = b_LL_->data[loop_ub];
    }
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /* Outputs */
  /* Horizontal filtering */
  for (i = 0; i < 256; i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (b_i = 0; b_i < 256; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    d_filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 256; b_i++) {
      LL_[i + (b_i << 8)] = b_iv[b_i];
    }
  }

  memset(&L1_[0], 0, 65536U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 255;
  }

  i = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 256;
  loop_ub = div_s32_floor(i1, b_i);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, i);
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 256; i++) {
      b_LL_->data[i + 256 * i1] = LL_[i + ((b_i * i1) << 8)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  /*  Vertical filtering */
  for (i = 0; i < 128; i++) {
    loop_ub = i << 8;
    c_filterSystem(*(int (*)[256])&(*(int (*)[32768])&H1_[0])[loop_ub],
                   filtered_col);
    for (b_i = 0; b_i < 256; b_i++) {
      L1__tmp = b_i + loop_ub;
      L1_[L1__tmp] = b_LL_->data[L1__tmp];
      filtered_img[L1__tmp] = filtered_col[b_i];
    }
  }

  emxFree_int32_T(&b_LL_);
  memset(&HH_[0], 0, 65536U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 255;
  }

  emxInit_int32_T(&b_filtered_img, 2);
  loop_ub = div_s32_floor(i - b_i, i1);
  i = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 128;
  emxEnsureCapacity_int32_T(b_filtered_img, i);
  for (i = 0; i < 128; i++) {
    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_filtered_img->data[i2 + b_filtered_img->size[0] * i] = filtered_img[(b_i
        + i1 * i2) + (i << 8)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 128; i++) {
    for (b_i = 0; b_i < 128; b_i++) {
      HH_[b_i + (i << 8)] = b_filtered_img->data[b_i + (i << 7)];
    }

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 8;
    d_filterSystem(*(int (*)[256])&(*(int (*)[32768])&H1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 256U * sizeof(int));
  }

  memset(&H1_[0], 0, 65536U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 255;
  }

  loop_ub = div_s32_floor(i1, b_i);
  i1 = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 128;
  emxEnsureCapacity_int32_T(b_filtered_img, i1);
  for (i1 = 0; i1 < 128; i1++) {
    for (i = 0; i <= loop_ub; i++) {
      b_filtered_img->data[i + b_filtered_img->size[0] * i1] = filtered_img[b_i *
        i + (i1 << 8)];
    }
  }

  /*  Vertical filtering */
  for (i = 0; i < 128; i++) {
    for (b_i = 0; b_i < 128; b_i++) {
      H1_[b_i + (i << 8)] = b_filtered_img->data[b_i + (i << 7)];
    }

    loop_ub = i << 8;
    c_filterSystem(*(int (*)[256])&(*(int (*)[32768])&L1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 256U * sizeof(int));
  }

  memset(&LH_[0], 0, 65536U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 255;
  }

  loop_ub = div_s32_floor(i - b_i, i1);
  i = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 128;
  emxEnsureCapacity_int32_T(b_filtered_img, i);
  for (i = 0; i < 128; i++) {
    for (i2 = 0; i2 <= loop_ub; i2++) {
      b_filtered_img->data[i2 + b_filtered_img->size[0] * i] = filtered_img[(b_i
        + i1 * i2) + (i << 8)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 128; i++) {
    for (b_i = 0; b_i < 128; b_i++) {
      LH_[b_i + (i << 8)] = b_filtered_img->data[b_i + (i << 7)];
    }

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 8;
    d_filterSystem(*(int (*)[256])&(*(int (*)[32768])&L1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 256U * sizeof(int));
  }

  memset(&LL_[0], 0, 65536U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 255;
  }

  loop_ub = div_s32_floor(i1, b_i);
  i1 = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 128;
  emxEnsureCapacity_int32_T(b_filtered_img, i1);
  for (i1 = 0; i1 < 128; i1++) {
    for (i = 0; i <= loop_ub; i++) {
      b_filtered_img->data[i + b_filtered_img->size[0] * i1] = filtered_img[b_i *
        i + (i1 << 8)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (b_i = 0; b_i < 128; b_i++) {
    for (i1 = 0; i1 < 128; i1++) {
      LL_[i1 + (b_i << 8)] = b_filtered_img->data[i1 + (b_i << 7)];
    }

    filtered_img_tmp[b_i] = (unsigned char)(b_i + 1U);
  }

  emxFree_int32_T(&b_filtered_img);
  for (b_i = 0; b_i < 128; b_i++) {
    for (i1 = 0; i1 < 128; i1++) {
      i = i1 + (b_i << 9);
      raw_img[i] = LL_[(filtered_img_tmp[i1] + ((filtered_img_tmp[b_i] - 1) << 8))
        - 1];
      i2 = i1 + (b_i << 8);
      L1__tmp = i1 + ((b_i + 128) << 9);
      raw_img[L1__tmp] = H1_[i2];
      raw_img[i + 128] = LH_[i2];
      raw_img[L1__tmp + 128] = HH_[i2];
    }
  }
}

/*
 * Arguments    : int raw_img[262144]
 *                double stride
 * Return Type  : void
 */
void c_octave(int raw_img[262144], double stride)
{
  int i;
  static int H1_[16384];
  int b_i;
  int filtered_col[128];
  int b_iv[128];
  int i1;
  static int LL_[16384];
  emxArray_int32_T *b_LL_;
  int i2;
  int loop_ub;
  static int L1_[16384];
  static int HH_[16384];
  int L1__tmp;
  int filtered_img[8192];
  int filtered_img_data[8192];
  int LH_[16384];
  signed char filtered_img_tmp[64];

  /*  Horizontal */
  /* Horizontal filtering */
  for (i = 0; i < 128; i++) {
    for (b_i = 0; b_i < 128; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    e_filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 128; b_i++) {
      LL_[i + (b_i << 7)] = b_iv[b_i];
    }
  }

  memset(&H1_[0], 0, 16384U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 127;
  }

  emxInit_int32_T(&b_LL_, 2);
  i2 = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 128;
  loop_ub = div_s32_floor(i - b_i, i1);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, i2);
  for (i = 0; i <= loop_ub; i++) {
    for (i2 = 0; i2 < 128; i2++) {
      b_LL_->data[i2 + 128 * i] = LL_[i2 + ((b_i + i1 * i) << 7)];
    }
  }

  for (b_i = 0; b_i < 64; b_i++) {
    for (i1 = 0; i1 < 128; i1++) {
      loop_ub = i1 + (b_i << 7);
      H1_[loop_ub] = b_LL_->data[loop_ub];
    }
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /* Outputs */
  /* Horizontal filtering */
  for (i = 0; i < 128; i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (b_i = 0; b_i < 128; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    f_filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 128; b_i++) {
      LL_[i + (b_i << 7)] = b_iv[b_i];
    }
  }

  memset(&L1_[0], 0, 16384U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 127;
  }

  i = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 128;
  loop_ub = div_s32_floor(i1, b_i);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, i);
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (i = 0; i < 128; i++) {
      b_LL_->data[i + 128 * i1] = LL_[i + ((b_i * i1) << 7)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  /*  Vertical filtering */
  for (i = 0; i < 64; i++) {
    loop_ub = i << 7;
    e_filterSystem(*(int (*)[128])&(*(int (*)[8192])&H1_[0])[loop_ub],
                   filtered_col);
    for (b_i = 0; b_i < 128; b_i++) {
      L1__tmp = b_i + loop_ub;
      L1_[L1__tmp] = b_LL_->data[L1__tmp];
      filtered_img[L1__tmp] = filtered_col[b_i];
    }
  }

  emxFree_int32_T(&b_LL_);
  memset(&HH_[0], 0, 16384U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 127;
  }

  loop_ub = div_s32_floor(i - b_i, i1);
  L1__tmp = loop_ub + 1;
  for (i = 0; i < 64; i++) {
    for (i2 = 0; i2 <= loop_ub; i2++) {
      filtered_img_data[i2 + L1__tmp * i] = filtered_img[(b_i + i1 * i2) + (i <<
        7)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 64; i++) {
    memcpy(&HH_[i * 128], &filtered_img_data[i * 64], 64U * sizeof(int));

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 7;
    f_filterSystem(*(int (*)[128])&(*(int (*)[8192])&H1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 128U * sizeof(int));
  }

  memset(&H1_[0], 0, 16384U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 127;
  }

  loop_ub = div_s32_floor(i1, b_i);
  L1__tmp = loop_ub + 1;
  for (i1 = 0; i1 < 64; i1++) {
    for (i = 0; i <= loop_ub; i++) {
      filtered_img_data[i + L1__tmp * i1] = filtered_img[b_i * i + (i1 << 7)];
    }
  }

  /*  Vertical filtering */
  for (i = 0; i < 64; i++) {
    memcpy(&H1_[i * 128], &filtered_img_data[i * 64], 64U * sizeof(int));
    loop_ub = i << 7;
    e_filterSystem(*(int (*)[128])&(*(int (*)[8192])&L1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 128U * sizeof(int));
  }

  memset(&LH_[0], 0, 16384U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    i = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    i = 127;
  }

  loop_ub = div_s32_floor(i - b_i, i1);
  L1__tmp = loop_ub + 1;
  for (i = 0; i < 64; i++) {
    for (i2 = 0; i2 <= loop_ub; i2++) {
      filtered_img_data[i2 + L1__tmp * i] = filtered_img[(b_i + i1 * i2) + (i <<
        7)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 64; i++) {
    memcpy(&LH_[i * 128], &filtered_img_data[i * 64], 64U * sizeof(int));

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 7;
    f_filterSystem(*(int (*)[128])&(*(int (*)[8192])&L1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 128U * sizeof(int));
  }

  memset(&LL_[0], 0, 16384U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 127;
  }

  loop_ub = div_s32_floor(i1, b_i);
  L1__tmp = loop_ub + 1;
  for (i1 = 0; i1 < 64; i1++) {
    for (i = 0; i <= loop_ub; i++) {
      filtered_img_data[i + L1__tmp * i1] = filtered_img[b_i * i + (i1 << 7)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (b_i = 0; b_i < 64; b_i++) {
    memcpy(&LL_[b_i * 128], &filtered_img_data[b_i * 64], 64U * sizeof(int));
    filtered_img_tmp[b_i] = (signed char)(b_i + 1);
  }

  for (b_i = 0; b_i < 64; b_i++) {
    for (i1 = 0; i1 < 64; i1++) {
      i = i1 + (b_i << 9);
      raw_img[i] = LL_[(filtered_img_tmp[i1] + ((filtered_img_tmp[b_i] - 1) << 7))
        - 1];
      i2 = i1 + (b_i << 7);
      loop_ub = i1 + ((b_i + 64) << 9);
      raw_img[loop_ub] = H1_[i2];
      raw_img[i + 64] = LH_[i2];
      raw_img[loop_ub + 64] = HH_[i2];
    }
  }
}

/*
 * Arguments    : int raw_img[262144]
 *                double stride
 * Return Type  : void
 */
void octave(int raw_img[262144], double stride)
{
  int i;
  static int H1_[262144];
  int b_i;
  int filtered_col[512];
  int b_iv[512];
  int i1;
  int L1__tmp;
  static int LL_[262144];
  emxArray_int32_T *b_LL_;
  int loop_ub;
  static int L1_[262144];
  static int HH_[262144];
  static int filtered_img[131072];
  emxArray_int32_T *b_filtered_img;
  static int LH_[262144];
  short filtered_img_tmp[256];

  /*  Horizontal */
  /* Horizontal filtering */
  for (i = 0; i < 512; i++) {
    for (b_i = 0; b_i < 512; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 512; b_i++) {
      LL_[i + (b_i << 9)] = b_iv[b_i];
    }
  }

  memset(&H1_[0], 0, 262144U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    L1__tmp = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    L1__tmp = 511;
  }

  emxInit_int32_T(&b_LL_, 2);
  i = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 512;
  loop_ub = div_s32_floor(L1__tmp - b_i, i1);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, i);
  for (L1__tmp = 0; L1__tmp <= loop_ub; L1__tmp++) {
    for (i = 0; i < 512; i++) {
      b_LL_->data[i + 512 * L1__tmp] = LL_[i + ((b_i + i1 * L1__tmp) << 9)];
    }
  }

  for (b_i = 0; b_i < 256; b_i++) {
    for (i1 = 0; i1 < 512; i1++) {
      loop_ub = i1 + (b_i << 9);
      H1_[loop_ub] = b_LL_->data[loop_ub];
    }
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /* Outputs */
  /* Horizontal filtering */
  for (i = 0; i < 512; i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (b_i = 0; b_i < 512; b_i++) {
      filtered_col[b_i] = raw_img[i + (b_i << 9)];
    }

    b_filterSystem(filtered_col, b_iv);
    for (b_i = 0; b_i < 512; b_i++) {
      LL_[i + (b_i << 9)] = b_iv[b_i];
    }
  }

  memset(&L1_[0], 0, 262144U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 511;
  }

  L1__tmp = b_LL_->size[0] * b_LL_->size[1];
  b_LL_->size[0] = 512;
  loop_ub = div_s32_floor(i1, b_i);
  b_LL_->size[1] = loop_ub + 1;
  emxEnsureCapacity_int32_T(b_LL_, L1__tmp);
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (L1__tmp = 0; L1__tmp < 512; L1__tmp++) {
      b_LL_->data[L1__tmp + 512 * i1] = LL_[L1__tmp + ((b_i * i1) << 9)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  /*  Vertical filtering */
  for (i = 0; i < 256; i++) {
    loop_ub = i << 9;
    filterSystem(*(int (*)[512])&(*(int (*)[131072])&H1_[0])[loop_ub],
                 filtered_col);
    for (b_i = 0; b_i < 512; b_i++) {
      L1__tmp = b_i + loop_ub;
      L1_[L1__tmp] = b_LL_->data[L1__tmp];
      filtered_img[L1__tmp] = filtered_col[b_i];
    }
  }

  emxFree_int32_T(&b_LL_);
  memset(&HH_[0], 0, 262144U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    L1__tmp = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    L1__tmp = 511;
  }

  emxInit_int32_T(&b_filtered_img, 2);
  loop_ub = div_s32_floor(L1__tmp - b_i, i1);
  L1__tmp = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 256;
  emxEnsureCapacity_int32_T(b_filtered_img, L1__tmp);
  for (L1__tmp = 0; L1__tmp < 256; L1__tmp++) {
    for (i = 0; i <= loop_ub; i++) {
      b_filtered_img->data[i + b_filtered_img->size[0] * L1__tmp] =
        filtered_img[(b_i + i1 * i) + (L1__tmp << 9)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 256; i++) {
    for (b_i = 0; b_i < 256; b_i++) {
      HH_[b_i + (i << 9)] = b_filtered_img->data[b_i + (i << 8)];
    }

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 9;
    b_filterSystem(*(int (*)[512])&(*(int (*)[131072])&H1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 512U * sizeof(int));
  }

  memset(&H1_[0], 0, 262144U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 511;
  }

  loop_ub = div_s32_floor(i1, b_i);
  i1 = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 256;
  emxEnsureCapacity_int32_T(b_filtered_img, i1);
  for (i1 = 0; i1 < 256; i1++) {
    for (L1__tmp = 0; L1__tmp <= loop_ub; L1__tmp++) {
      b_filtered_img->data[L1__tmp + b_filtered_img->size[0] * i1] =
        filtered_img[b_i * L1__tmp + (i1 << 9)];
    }
  }

  /*  Vertical filtering */
  for (i = 0; i < 256; i++) {
    for (b_i = 0; b_i < 256; b_i++) {
      H1_[b_i + (i << 9)] = b_filtered_img->data[b_i + (i << 8)];
    }

    loop_ub = i << 9;
    filterSystem(*(int (*)[512])&(*(int (*)[131072])&L1_[0])[loop_ub],
                 filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 512U * sizeof(int));
  }

  memset(&LH_[0], 0, 262144U * sizeof(int));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 0;
    i1 = 1;
    L1__tmp = -1;
  } else {
    b_i = 1;
    i1 = (int)stride;
    L1__tmp = 511;
  }

  loop_ub = div_s32_floor(L1__tmp - b_i, i1);
  L1__tmp = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 256;
  emxEnsureCapacity_int32_T(b_filtered_img, L1__tmp);
  for (L1__tmp = 0; L1__tmp < 256; L1__tmp++) {
    for (i = 0; i <= loop_ub; i++) {
      b_filtered_img->data[i + b_filtered_img->size[0] * L1__tmp] =
        filtered_img[(b_i + i1 * i) + (L1__tmp << 9)];
    }
  }

  /* Outputs */
  /*  Vertical filtering */
  for (i = 0; i < 256; i++) {
    for (b_i = 0; b_i < 256; b_i++) {
      LH_[b_i + (i << 9)] = b_filtered_img->data[b_i + (i << 8)];
    }

    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    loop_ub = i << 9;
    b_filterSystem(*(int (*)[512])&(*(int (*)[131072])&L1_[0])[loop_ub],
                   filtered_col);
    memcpy(&filtered_img[loop_ub], &filtered_col[0], 512U * sizeof(int));
  }

  memset(&LL_[0], 0, 262144U * sizeof(int));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    b_i = 1;
    i1 = -1;
  } else {
    b_i = (int)stride;
    i1 = 511;
  }

  loop_ub = div_s32_floor(i1, b_i);
  i1 = b_filtered_img->size[0] * b_filtered_img->size[1];
  b_filtered_img->size[0] = loop_ub + 1;
  b_filtered_img->size[1] = 256;
  emxEnsureCapacity_int32_T(b_filtered_img, i1);
  for (i1 = 0; i1 < 256; i1++) {
    for (L1__tmp = 0; L1__tmp <= loop_ub; L1__tmp++) {
      b_filtered_img->data[L1__tmp + b_filtered_img->size[0] * i1] =
        filtered_img[b_i * L1__tmp + (i1 << 9)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (b_i = 0; b_i < 256; b_i++) {
    for (i1 = 0; i1 < 256; i1++) {
      LL_[i1 + (b_i << 9)] = b_filtered_img->data[i1 + (b_i << 8)];
    }

    filtered_img_tmp[b_i] = (short)(b_i + 1);
  }

  emxFree_int32_T(&b_filtered_img);
  for (b_i = 0; b_i < 256; b_i++) {
    for (i1 = 0; i1 < 256; i1++) {
      L1__tmp = i1 + (b_i << 9);
      raw_img[L1__tmp] = LL_[(filtered_img_tmp[i1] + ((filtered_img_tmp[b_i] - 1)
        << 9)) - 1];
      i = i1 + ((b_i + 256) << 9);
      raw_img[i] = H1_[L1__tmp];
      raw_img[L1__tmp + 256] = LH_[L1__tmp];
      raw_img[i + 256] = HH_[L1__tmp];
    }
  }
}

/*
 * File trailer for octave.c
 *
 * [EOF]
 */
