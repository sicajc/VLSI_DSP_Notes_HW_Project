/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: downSampler.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 09:47:10
 */

/* Include Files */
#include "downSampler.h"
#include "downSampler_emxutil.h"
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
 * Arguments    : const double img[262144]
 *                double stride
 *                double odd
 *                double n
 *                double horizontal
 *                double downSampledimg[262144]
 * Return Type  : void
 */
void downSampler(const double img[262144], double stride, double odd, double n,
                 double horizontal, double downSampledimg[262144])
{
  emxArray_real_T *b_img;
  emxArray_real_T *c_img;
  int i;
  int i1;
  int i2;
  int loop_ub;
  int i3;
  (void)n;
  memset(&downSampledimg[0], 0, 262144U * sizeof(double));
  if (horizontal == 1.0) {
    emxInit_real_T(&c_img, 2);
    if (odd == 0.0) {
      /* even for HPF */
      if ((stride == 0.0) || (0.0 > stride)) {
        i = 0;
        i1 = 1;
        i2 = -1;
      } else {
        i = 1;
        i1 = (int)stride;
        i2 = 511;
      }

      i3 = c_img->size[0] * c_img->size[1];
      c_img->size[0] = 512;
      loop_ub = div_s32_floor(i2 - i, i1);
      c_img->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_img, i3);
      for (i2 = 0; i2 <= loop_ub; i2++) {
        for (i3 = 0; i3 < 512; i3++) {
          c_img->data[i3 + 512 * i2] = img[i3 + ((i + i1 * i2) << 9)] * 0.5;
        }
      }

      for (i = 0; i < 256; i++) {
        for (i1 = 0; i1 < 512; i1++) {
          loop_ub = i1 + (i << 9);
          downSampledimg[loop_ub] = c_img->data[loop_ub];
        }
      }
    } else {
      /* odd for LPF */
      if ((stride == 0.0) || (0.0 > stride)) {
        i = 1;
        i1 = -1;
      } else {
        i = (int)stride;
        i1 = 511;
      }

      i2 = c_img->size[0] * c_img->size[1];
      c_img->size[0] = 512;
      loop_ub = div_s32_floor(i1, i);
      c_img->size[1] = loop_ub + 1;
      emxEnsureCapacity_real_T(c_img, i2);
      for (i1 = 0; i1 <= loop_ub; i1++) {
        for (i2 = 0; i2 < 512; i2++) {
          c_img->data[i2 + 512 * i1] = img[i2 + ((i * i1) << 9)] * 0.5;
        }
      }

      for (i = 0; i < 256; i++) {
        for (i1 = 0; i1 < 512; i1++) {
          loop_ub = i1 + (i << 9);
          downSampledimg[loop_ub] = c_img->data[loop_ub];
        }
      }
    }

    emxFree_real_T(&c_img);
  } else {
    emxInit_real_T(&b_img, 2);
    if (odd == 0.0) {
      /* even for HPF */
      if ((stride == 0.0) || (0.0 > stride)) {
        i = 0;
        i1 = 1;
        i2 = -1;
      } else {
        i = 1;
        i1 = (int)stride;
        i2 = 511;
      }

      loop_ub = div_s32_floor(i2 - i, i1);
      i2 = b_img->size[0] * b_img->size[1];
      b_img->size[0] = loop_ub + 1;
      b_img->size[1] = 512;
      emxEnsureCapacity_real_T(b_img, i2);
      for (i2 = 0; i2 < 512; i2++) {
        for (i3 = 0; i3 <= loop_ub; i3++) {
          b_img->data[i3 + b_img->size[0] * i2] = img[(i + i1 * i3) + (i2 << 9)]
            * 0.5;
        }
      }

      for (i = 0; i < 512; i++) {
        for (i1 = 0; i1 < 256; i1++) {
          downSampledimg[i1 + (i << 9)] = b_img->data[i1 + (i << 8)];
        }
      }
    } else {
      /* odd for LPF */
      if ((stride == 0.0) || (0.0 > stride)) {
        i = 1;
        i1 = -1;
      } else {
        i = (int)stride;
        i1 = 511;
      }

      loop_ub = div_s32_floor(i1, i);
      i1 = b_img->size[0] * b_img->size[1];
      b_img->size[0] = loop_ub + 1;
      b_img->size[1] = 512;
      emxEnsureCapacity_real_T(b_img, i1);
      for (i1 = 0; i1 < 512; i1++) {
        for (i2 = 0; i2 <= loop_ub; i2++) {
          b_img->data[i2 + b_img->size[0] * i1] = img[i * i2 + (i1 << 9)] * 0.5;
        }
      }

      for (i = 0; i < 512; i++) {
        for (i1 = 0; i1 < 256; i1++) {
          downSampledimg[i1 + (i << 9)] = b_img->data[i1 + (i << 8)];
        }
      }
    }

    emxFree_real_T(&b_img);
  }
}

/*
 * File trailer for downSampler.c
 *
 * [EOF]
 */
