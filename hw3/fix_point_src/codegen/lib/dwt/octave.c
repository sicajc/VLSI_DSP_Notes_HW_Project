/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
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
 * Arguments    : const short raw_img[262144]
 *                double stride
 *                short filtered_img[262144]
 * Return Type  : void
 */
void b_octave(const short raw_img[262144], double stride, short filtered_img
              [262144])
{
  int i;
  int i1;
  int b_i;
  short i2;
  static short H1_[65536];
  static short LL_[65536];
  short b_LL_[256];
  short b_iv[256];
  int filtered_img_tmp;
  emxArray_int16_T *c_LL_;
  int b_filtered_img_tmp;
  static short L1_[65536];
  static short HH_[65536];
  short b_raw_img[32768];
  emxArray_int16_T *c_raw_img;
  short LH_[65536];
  unsigned char c_filtered_img_tmp[128];
  for (i = 0; i < 262144; i++) {
    if ((raw_img[i] & 1024) != 0) {
      filtered_img[i] = (short)(raw_img[i] | -1024);
    } else {
      filtered_img[i] = (short)(raw_img[i] & 1023);
    }
  }

  /*  Horizontal */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      i2 = raw_img[i1 + (i << 9)];
      if ((i2 & 1024) != 0) {
        LL_[i1 + (i << 8)] = (short)(i2 | -1024);
      } else {
        LL_[i1 + (i << 8)] = (short)(i2 & 1023);
      }
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    for (i = 0; i < 256; i++) {
      b_LL_[i] = LL_[b_i + (i << 8)];
    }

    c_filterSystem(b_LL_, b_iv);
    for (i = 0; i < 256; i++) {
      LL_[b_i + (i << 8)] = b_iv[i];
    }
  }

  memset(&H1_[0], 0, 65536U * sizeof(short));

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

  emxInit_int16_T(&c_LL_, 2);
  b_filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 256;
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_int16_T(c_LL_, b_filtered_img_tmp);
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

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /*  Output types */
  for (i = 0; i < 256; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      i2 = raw_img[i1 + (i << 9)];
      if ((i2 & 1024) != 0) {
        LL_[i1 + (i << 8)] = (short)(i2 | -1024);
      } else {
        LL_[i1 + (i << 8)] = (short)(i2 & 1023);
      }
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 256; i++) {
      b_LL_[i] = LL_[b_i + (i << 8)];
    }

    d_filterSystem(b_LL_, b_iv);
    for (i = 0; i < 256; i++) {
      LL_[b_i + (i << 8)] = b_iv[i];
    }
  }

  memset(&L1_[0], 0, 65536U * sizeof(short));

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
  emxEnsureCapacity_int16_T(c_LL_, filtered_img_tmp);
  for (i1 = 0; i1 <= b_i; i1++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
      c_LL_->data[filtered_img_tmp + 256 * i1] = LL_[filtered_img_tmp + ((i * i1)
        << 8)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 256; i1++) {
      b_i = i1 + (i << 8);
      L1_[b_i] = c_LL_->data[b_i];
      b_raw_img[b_i] = H1_[b_i];
    }
  }

  emxFree_int16_T(&c_LL_);

  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    i = b_i << 8;
    c_filterSystem(*(short (*)[256])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 256U * sizeof(short));
  }

  memset(&HH_[0], 0, 65536U * sizeof(short));

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

  emxInit_int16_T(&c_raw_img, 2);
  b_i = div_s32_floor(filtered_img_tmp - i, i1);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 128;
  emxEnsureCapacity_int16_T(c_raw_img, filtered_img_tmp);
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

    memcpy(&b_raw_img[i * 256], &H1_[i * 256], 256U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 8;
    d_filterSystem(*(short (*)[256])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 256U * sizeof(short));
  }

  memset(&H1_[0], 0, 65536U * sizeof(short));

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
  emxEnsureCapacity_int16_T(c_raw_img, i1);
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

    memcpy(&b_raw_img[i * 256], &L1_[i * 256], 256U * sizeof(short));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    i = b_i << 8;
    c_filterSystem(*(short (*)[256])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 256U * sizeof(short));
  }

  memset(&LH_[0], 0, 65536U * sizeof(short));

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
  emxEnsureCapacity_int16_T(c_raw_img, filtered_img_tmp);
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

    memcpy(&b_raw_img[i * 256], &L1_[i * 256], 256U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 8;
    d_filterSystem(*(short (*)[256])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 256U * sizeof(short));
  }

  memset(&LL_[0], 0, 65536U * sizeof(short));

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
  emxEnsureCapacity_int16_T(c_raw_img, i1);
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

  emxFree_int16_T(&c_raw_img);
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
 * Arguments    : const short raw_img[262144]
 *                double stride
 *                short filtered_img[262144]
 * Return Type  : void
 */
void c_octave(const short raw_img[262144], double stride, short filtered_img
              [262144])
{
  int i;
  int i1;
  int b_i;
  short i2;
  short H1_[16384];
  short LL_[16384];
  short b_LL_[128];
  short b_iv[128];
  int loop_ub;
  int filtered_img_tmp;
  short HH_[16384];
  short L1_[16384];
  short b_raw_img[8192];
  int raw_img_size_idx_0;
  short raw_img_data[8192];
  short LH_[16384];
  signed char b_filtered_img_tmp[64];
  for (i = 0; i < 262144; i++) {
    if ((raw_img[i] & 2048) != 0) {
      filtered_img[i] = (short)(raw_img[i] | -2048);
    } else {
      filtered_img[i] = (short)(raw_img[i] & 2047);
    }
  }

  /*  Horizontal */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      i2 = raw_img[i1 + (i << 9)];
      if ((i2 & 2048) != 0) {
        LL_[i1 + (i << 7)] = (short)(i2 | -2048);
      } else {
        LL_[i1 + (i << 7)] = (short)(i2 & 2047);
      }
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    for (i = 0; i < 128; i++) {
      b_LL_[i] = LL_[b_i + (i << 7)];
    }

    e_filterSystem(b_LL_, b_iv);
    for (i = 0; i < 128; i++) {
      LL_[b_i + (i << 7)] = b_iv[i];
    }
  }

  memset(&H1_[0], 0, 16384U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    b_i = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    b_i = 127;
  }

  loop_ub = div_s32_floor(b_i - i, i1);
  for (b_i = 0; b_i <= loop_ub; b_i++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 128; filtered_img_tmp++) {
      HH_[filtered_img_tmp + 128 * b_i] = LL_[filtered_img_tmp + ((i + i1 * b_i)
        << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    memcpy(&H1_[i * 128], &HH_[i * 128], 128U * sizeof(short));
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /*  Output types */
  for (i = 0; i < 128; i++) {
    for (i1 = 0; i1 < 128; i1++) {
      i2 = raw_img[i1 + (i << 9)];
      if ((i2 & 2048) != 0) {
        LL_[i1 + (i << 7)] = (short)(i2 | -2048);
      } else {
        LL_[i1 + (i << 7)] = (short)(i2 & 2047);
      }
    }
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 128; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 128; i++) {
      b_LL_[i] = LL_[b_i + (i << 7)];
    }

    f_filterSystem(b_LL_, b_iv);
    for (i = 0; i < 128; i++) {
      LL_[b_i + (i << 7)] = b_iv[i];
    }
  }

  memset(&L1_[0], 0, 16384U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  loop_ub = div_s32_floor(i1, i);
  for (i1 = 0; i1 <= loop_ub; i1++) {
    for (b_i = 0; b_i < 128; b_i++) {
      HH_[b_i + 128 * i1] = LL_[b_i + ((i * i1) << 7)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 64; i++) {
    memcpy(&L1_[i * 128], &HH_[i * 128], 128U * sizeof(short));
    memcpy(&b_raw_img[i * 128], &H1_[i * 128], 128U * sizeof(short));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    i = b_i << 7;
    e_filterSystem(*(short (*)[128])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 128U * sizeof(short));
  }

  memset(&HH_[0], 0, 16384U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    b_i = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    b_i = 127;
  }

  loop_ub = div_s32_floor(b_i - i, i1);
  raw_img_size_idx_0 = loop_ub + 1;
  for (b_i = 0; b_i < 64; b_i++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= loop_ub; filtered_img_tmp++)
    {
      raw_img_data[filtered_img_tmp + raw_img_size_idx_0 * b_i] = b_raw_img[(i +
        i1 * filtered_img_tmp) + (b_i << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    memcpy(&HH_[i * 128], &raw_img_data[i * 64], 64U * sizeof(short));
    memcpy(&b_raw_img[i * 128], &H1_[i * 128], 128U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 7;
    f_filterSystem(*(short (*)[128])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 128U * sizeof(short));
  }

  memset(&H1_[0], 0, 16384U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  loop_ub = div_s32_floor(i1, i);
  raw_img_size_idx_0 = loop_ub + 1;
  for (i1 = 0; i1 < 64; i1++) {
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      raw_img_data[b_i + raw_img_size_idx_0 * i1] = b_raw_img[i * b_i + (i1 << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    memcpy(&H1_[i * 128], &raw_img_data[i * 64], 64U * sizeof(short));
    memcpy(&b_raw_img[i * 128], &L1_[i * 128], 128U * sizeof(short));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    i = b_i << 7;
    e_filterSystem(*(short (*)[128])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 128U * sizeof(short));
  }

  memset(&LH_[0], 0, 16384U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i1 = 1;
    b_i = -1;
  } else {
    i = 1;
    i1 = (int)stride;
    b_i = 127;
  }

  loop_ub = div_s32_floor(b_i - i, i1);
  raw_img_size_idx_0 = loop_ub + 1;
  for (b_i = 0; b_i < 64; b_i++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= loop_ub; filtered_img_tmp++)
    {
      raw_img_data[filtered_img_tmp + raw_img_size_idx_0 * b_i] = b_raw_img[(i +
        i1 * filtered_img_tmp) + (b_i << 7)];
    }
  }

  for (i = 0; i < 64; i++) {
    memcpy(&LH_[i * 128], &raw_img_data[i * 64], 64U * sizeof(short));
    memcpy(&b_raw_img[i * 128], &L1_[i * 128], 128U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 64; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 7;
    f_filterSystem(*(short (*)[128])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 128U * sizeof(short));
  }

  memset(&LL_[0], 0, 16384U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i1 = -1;
  } else {
    i = (int)stride;
    i1 = 127;
  }

  loop_ub = div_s32_floor(i1, i);
  raw_img_size_idx_0 = loop_ub + 1;
  for (i1 = 0; i1 < 64; i1++) {
    for (b_i = 0; b_i <= loop_ub; b_i++) {
      raw_img_data[b_i + raw_img_size_idx_0 * i1] = b_raw_img[i * b_i + (i1 << 7)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (i = 0; i < 64; i++) {
    memcpy(&LL_[i * 128], &raw_img_data[i * 64], 64U * sizeof(short));
    b_filtered_img_tmp[i] = (signed char)(i + 1);
  }

  for (i = 0; i < 64; i++) {
    for (i1 = 0; i1 < 64; i1++) {
      b_i = i1 + (i << 9);
      filtered_img[b_i] = LL_[(b_filtered_img_tmp[i1] + ((b_filtered_img_tmp[i]
        - 1) << 7)) - 1];
      loop_ub = i1 + (i << 7);
      filtered_img_tmp = i1 + ((i + 64) << 9);
      filtered_img[filtered_img_tmp] = H1_[loop_ub];
      filtered_img[b_i + 64] = LH_[loop_ub];
      filtered_img[filtered_img_tmp + 64] = HH_[loop_ub];
    }
  }
}

/*
 * Arguments    : const short raw_img[262144]
 *                double stride
 *                short filtered_img[262144]
 * Return Type  : void
 */
void octave(const short raw_img[262144], double stride, short filtered_img
            [262144])
{
  int i;
  short i1;
  int b_i;
  static short H1_[262144];
  short LL_[512];
  short b_iv[512];
  static short b_LL_[262144];
  int i2;
  int filtered_img_tmp;
  emxArray_int16_T *c_LL_;
  int i3;
  static short L1_[262144];
  static short HH_[262144];
  static short b_raw_img[131072];
  emxArray_int16_T *c_raw_img;
  static short LH_[262144];
  short b_filtered_img_tmp[256];

  /*  Horizontal */
  for (i = 0; i < 262144; i++) {
    i1 = raw_img[i];
    if (raw_img[i] > 511) {
      i1 = 511;
    } else {
      if (raw_img[i] < -512) {
        i1 = -512;
      }
    }

    filtered_img[i] = i1;
    i1 = raw_img[i];
    if (raw_img[i] > 511) {
      i1 = 511;
    } else {
      if (raw_img[i] < -512) {
        i1 = -512;
      }
    }

    b_LL_[i] = i1;
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 512; b_i++) {
    for (i = 0; i < 512; i++) {
      LL_[i] = b_LL_[b_i + (i << 9)];
    }

    filterSystem(LL_, b_iv);
    for (i = 0; i < 512; i++) {
      b_LL_[b_i + (i << 9)] = b_iv[i];
    }
  }

  memset(&H1_[0], 0, 262144U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i2 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i2 = (int)stride;
    filtered_img_tmp = 511;
  }

  emxInit_int16_T(&c_LL_, 2);
  i3 = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 512;
  b_i = div_s32_floor(filtered_img_tmp - i, i2);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_int16_T(c_LL_, i3);
  for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
    for (i3 = 0; i3 < 512; i3++) {
      c_LL_->data[i3 + 512 * filtered_img_tmp] = b_LL_[i3 + ((i + i2 *
        filtered_img_tmp) << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 512; i2++) {
      b_i = i2 + (i << 9);
      H1_[b_i] = c_LL_->data[b_i];
    }
  }

  /*  H1f = double(H1_); */
  /*  figure(7); */
  /*  imshow(H1f, []); */
  /*  title('H1_'); */
  /*  Output types */
  for (i = 0; i < 262144; i++) {
    i1 = raw_img[i];
    if (raw_img[i] > 511) {
      i1 = 511;
    } else {
      if (raw_img[i] < -512) {
        i1 = -512;
      }
    }

    b_LL_[i] = i1;
  }

  /* Horizontal filtering */
  for (b_i = 0; b_i < 512; b_i++) {
    /*  row_img = cast(raw_img(i, :), 'like', T.filter_coef); */
    for (i = 0; i < 512; i++) {
      LL_[i] = b_LL_[b_i + (i << 9)];
    }

    b_filterSystem(LL_, b_iv);
    for (i = 0; i < 512; i++) {
      b_LL_[b_i + (i << 9)] = b_iv[i];
    }
  }

  memset(&L1_[0], 0, 262144U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i2 = -1;
  } else {
    i = (int)stride;
    i2 = 511;
  }

  filtered_img_tmp = c_LL_->size[0] * c_LL_->size[1];
  c_LL_->size[0] = 512;
  b_i = div_s32_floor(i2, i);
  c_LL_->size[1] = b_i + 1;
  emxEnsureCapacity_int16_T(c_LL_, filtered_img_tmp);
  for (i2 = 0; i2 <= b_i; i2++) {
    for (filtered_img_tmp = 0; filtered_img_tmp < 512; filtered_img_tmp++) {
      c_LL_->data[filtered_img_tmp + 512 * i2] = b_LL_[filtered_img_tmp + ((i *
        i2) << 9)];
    }
  }

  /*  L1f = double(L1_); */
  /*  figure(7); */
  /*  imshow(L1f, []); */
  /*  title('L1_'); */
  /*  Vertical!, i have problem here! The high pass components leads to some errors. */
  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 512; i2++) {
      b_i = i2 + (i << 9);
      L1_[b_i] = c_LL_->data[b_i];
      b_raw_img[b_i] = H1_[b_i];
    }
  }

  emxFree_int16_T(&c_LL_);

  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    i = b_i << 9;
    filterSystem(*(short (*)[512])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 512U * sizeof(short));
  }

  memset(&HH_[0], 0, 262144U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i2 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i2 = (int)stride;
    filtered_img_tmp = 511;
  }

  emxInit_int16_T(&c_raw_img, 2);
  b_i = div_s32_floor(filtered_img_tmp - i, i2);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_int16_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
    for (i3 = 0; i3 <= b_i; i3++) {
      c_raw_img->data[i3 + c_raw_img->size[0] * filtered_img_tmp] = b_raw_img[(i
        + i2 * i3) + (filtered_img_tmp << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      HH_[i2 + (i << 9)] = c_raw_img->data[i2 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &H1_[i * 512], 512U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 9;
    b_filterSystem(*(short (*)[512])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 512U * sizeof(short));
  }

  memset(&H1_[0], 0, 262144U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i2 = -1;
  } else {
    i = (int)stride;
    i2 = 511;
  }

  b_i = div_s32_floor(i2, i);
  i2 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_int16_T(c_raw_img, i2);
  for (i2 = 0; i2 < 256; i2++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i2] = b_raw_img[i *
        filtered_img_tmp + (i2 << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      H1_[i2 + (i << 9)] = c_raw_img->data[i2 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &L1_[i * 512], 512U * sizeof(short));
  }

  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    i = b_i << 9;
    filterSystem(*(short (*)[512])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 512U * sizeof(short));
  }

  memset(&LH_[0], 0, 262144U * sizeof(short));

  /* even for HPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 0;
    i2 = 1;
    filtered_img_tmp = -1;
  } else {
    i = 1;
    i2 = (int)stride;
    filtered_img_tmp = 511;
  }

  b_i = div_s32_floor(filtered_img_tmp - i, i2);
  filtered_img_tmp = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_int16_T(c_raw_img, filtered_img_tmp);
  for (filtered_img_tmp = 0; filtered_img_tmp < 256; filtered_img_tmp++) {
    for (i3 = 0; i3 <= b_i; i3++) {
      c_raw_img->data[i3 + c_raw_img->size[0] * filtered_img_tmp] = b_raw_img[(i
        + i2 * i3) + (filtered_img_tmp << 9)];
    }
  }

  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      LH_[i2 + (i << 9)] = c_raw_img->data[i2 + (i << 8)];
    }

    memcpy(&b_raw_img[i * 512], &L1_[i * 512], 512U * sizeof(short));
  }

  /*  Output types */
  /*  Vertical filtering */
  for (b_i = 0; b_i < 256; b_i++) {
    /*  col_img = cast(raw_img(:, i), 'like', T.filter_coef); */
    i = b_i << 9;
    b_filterSystem(*(short (*)[512])&b_raw_img[i], b_iv);
    memcpy(&b_raw_img[i], &b_iv[0], 512U * sizeof(short));
  }

  memset(&b_LL_[0], 0, 262144U * sizeof(short));

  /* odd for LPF */
  if ((stride == 0.0) || (0.0 > stride)) {
    i = 1;
    i2 = -1;
  } else {
    i = (int)stride;
    i2 = 511;
  }

  b_i = div_s32_floor(i2, i);
  i2 = c_raw_img->size[0] * c_raw_img->size[1];
  c_raw_img->size[0] = b_i + 1;
  c_raw_img->size[1] = 256;
  emxEnsureCapacity_int16_T(c_raw_img, i2);
  for (i2 = 0; i2 < 256; i2++) {
    for (filtered_img_tmp = 0; filtered_img_tmp <= b_i; filtered_img_tmp++) {
      c_raw_img->data[filtered_img_tmp + c_raw_img->size[0] * i2] = b_raw_img[i *
        filtered_img_tmp + (i2 << 9)];
    }
  }

  /*  Trace till here, problems happens with LL_ */
  /*  Recombination */
  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      b_LL_[i2 + (i << 9)] = c_raw_img->data[i2 + (i << 8)];
    }

    b_filtered_img_tmp[i] = (short)(i + 1);
  }

  emxFree_int16_T(&c_raw_img);
  for (i = 0; i < 256; i++) {
    for (i2 = 0; i2 < 256; i2++) {
      b_i = i2 + (i << 9);
      filtered_img[b_i] = b_LL_[(b_filtered_img_tmp[i2] + ((b_filtered_img_tmp[i]
        - 1) << 9)) - 1];
      filtered_img_tmp = i2 + ((i + 256) << 9);
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
