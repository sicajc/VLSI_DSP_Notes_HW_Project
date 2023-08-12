/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 19:49:54
 */

/* Include Files */
#include "filterSystem.h"
#include "dwt.h"
#include <string.h>

/* Variable Definitions */
static const double dv[7] = { -66.087815812096, 41.665963631616,
  428.126487779328, -807.409271199744, 428.126487779328, 41.665963631616,
  -66.087815812096 };

static const double dv1[9] = { 38.736338439168, -24.42185218048,
  -113.279390124032, 386.460524147712, 873.163447305216, 386.460524147712,
  -113.279390124032, -24.42185218048, 38.736338439168 };

/* Function Definitions */

/*
 * Arguments    : const double xn[512]
 *                double b_yn[512]
 * Return Type  : void
 */
void b_filterSystem(const double xn[512], double b_yn[512])
{
  double x[520];
  int i;
  double b0_data[520];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 512U * sizeof(double));
  x[516] = xn[510];
  x[517] = xn[509];
  x[518] = xn[508];
  x[519] = xn[507];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&b0_data[0], &x[i], 9U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      c += dv1[loop_ub] * 0.0009765625 * (b0_data[loop_ub] * 0.25) * 4096.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * Arguments    : const double xn[256]
 *                double b_yn[256]
 * Return Type  : void
 */
void c_filterSystem(const double xn[256], double b_yn[256])
{
  double x[262];
  int i;
  double b0_data[262];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 256U * sizeof(double));
  x[259] = xn[254];
  x[260] = xn[253];
  x[261] = xn[252];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      c += dv[loop_ub] * 0.0009765625 * (b0_data[loop_ub] * 0.0078125) *
        131072.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * Arguments    : const double xn[256]
 *                double b_yn[256]
 * Return Type  : void
 */
void d_filterSystem(const double xn[256], double b_yn[256])
{
  double x[264];
  int i;
  double y_data[264];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 256U * sizeof(double));
  x[260] = xn[254];
  x[261] = xn[253];
  x[262] = xn[252];
  x[263] = xn[251];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      c += dv1[loop_ub] * 0.0009765625 * (y_data[loop_ub] * 0.0078125) *
        131072.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * Arguments    : const double xn[128]
 *                double b_yn[128]
 * Return Type  : void
 */
void e_filterSystem(const double xn[128], double b_yn[128])
{
  double x[134];
  int i;
  double b0_data[134];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 128U * sizeof(double));
  x[131] = xn[126];
  x[132] = xn[125];
  x[133] = xn[124];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      c += dv[loop_ub] * 0.0009765625 * (b0_data[loop_ub] * 0.125) * 8192.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * Arguments    : const double xn[128]
 *                double b_yn[128]
 * Return Type  : void
 */
void f_filterSystem(const double xn[128], double b_yn[128])
{
  double x[136];
  int i;
  double y_data[136];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 128U * sizeof(double));
  x[132] = xn[126];
  x[133] = xn[125];
  x[134] = xn[124];
  x[135] = xn[123];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      c += dv1[loop_ub] * 0.0009765625 * (y_data[loop_ub] * 0.125) * 8192.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * Arguments    : const double xn[512]
 *                double b_yn[512]
 * Return Type  : void
 */
void filterSystem(const double xn[512], double b_yn[512])
{
  double x[518];
  int i;
  double b0_data[518];
  double c;
  int loop_ub;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 512U * sizeof(double));
  x[515] = xn[510];
  x[516] = xn[509];
  x[517] = xn[508];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(double));
    c = 0.0;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      c += dv[loop_ub] * 0.0009765625 * (b0_data[loop_ub] * 0.25) * 4096.0;
    }

    b_yn[i] = c * 0.0009765625;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
