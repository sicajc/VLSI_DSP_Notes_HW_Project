/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

/* Include Files */
#include "filterSystem.h"
#include "octave.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Variable Definitions */
static const double dv[9] = { 0.302627644056, -0.19079572016, -0.884995235344,
  3.019222844904, 6.821589432072, 3.019222844904, -0.884995235344,
  -0.19079572016, 0.302627644056 };

/* Function Definitions */

/*
 * Arguments    : const double xn_data[]
 *                const int xn_size[2]
 *                double yn_data[]
 *                int yn_size[2]
 * Return Type  : void
 */
void b_filterSystem(const double xn_data[], const int xn_size[2], double
                    yn_data[], int yn_size[2])
{
  int loop_ub;
  int i;
  int nd2;
  double x_data[511];
  int n;
  double b_x_data[1027];
  int k;
  double tmp;
  int x_tmp;
  double b0_data[520];

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  yn_size[0] = 1;
  yn_size[1] = xn_size[1];
  loop_ub = xn_size[1];
  if (0 <= loop_ub - 1) {
    memset(&yn_data[0], 0, loop_ub * sizeof(double));
  }

  if (xn_size[1] - 4 > xn_size[1] - 1) {
    i = -1;
    nd2 = -1;
  } else {
    i = xn_size[1] - 6;
    nd2 = xn_size[1] - 2;
  }

  loop_ub = nd2 - i;
  for (nd2 = 0; nd2 < loop_ub; nd2++) {
    x_data[nd2] = xn_data[(i + nd2) + 1];
  }

  i = (short)loop_ub;
  if ((i != 0) && (i > 1)) {
    n = i - 1;
    nd2 = i >> 1;
    for (k = 0; k < nd2; k++) {
      tmp = x_data[k];
      x_tmp = n - k;
      x_data[k] = x_data[x_tmp];
      x_data[x_tmp] = tmp;
    }
  }

  b_x_data[0] = xn_data[4];
  b_x_data[1] = xn_data[3];
  b_x_data[2] = xn_data[2];
  b_x_data[3] = xn_data[1];
  nd2 = xn_size[1];
  if (0 <= nd2 - 1) {
    memcpy(&b_x_data[4], &xn_data[0], nd2 * sizeof(double));
  }

  for (i = 0; i < loop_ub; i++) {
    b_x_data[(i + xn_size[1]) + 4] = x_data[i];
  }

  /*  Symmetric extension! */
  i = xn_size[1];
  for (n = 0; n < i; n++) {
    if (n + 1 > n + 9) {
      nd2 = 0;
      x_tmp = -1;
    } else {
      nd2 = n;
      x_tmp = n + 8;
    }

    loop_ub = x_tmp - nd2;
    for (x_tmp = 0; x_tmp <= loop_ub; x_tmp++) {
      b0_data[x_tmp] = b_x_data[nd2 + x_tmp];
    }

    tmp = 0.0;
    for (k = 0; k < 9; k++) {
      tmp += dv[k] * 0.125 * (b0_data[k] * 0.125) * 64.0;
    }

    yn_data[n] = tmp * 0.125;
  }
}

/*
 * Arguments    : const double xn_data[]
 *                const int xn_size[2]
 *                double yn_data[]
 *                int yn_size[2]
 * Return Type  : void
 */
void filterSystem(const double xn_data[], const int xn_size[2], double yn_data[],
                  int yn_size[2])
{
  int loop_ub;
  int i;
  int nd2;
  double x_data[511];
  int n;
  double b_x_data[1026];
  int k;
  double tmp;
  int x_tmp;
  double b0_data[518];
  static const double a[7] = { -0.516311061032, 0.325515340872, 3.344738185776,
    -6.307884931248, 3.344738185776, 0.325515340872, -0.516311061032 };

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  yn_size[0] = 1;
  yn_size[1] = xn_size[1];
  loop_ub = xn_size[1];
  if (0 <= loop_ub - 1) {
    memset(&yn_data[0], 0, loop_ub * sizeof(double));
  }

  if (xn_size[1] - 3 > xn_size[1] - 1) {
    i = -1;
    nd2 = -1;
  } else {
    i = xn_size[1] - 5;
    nd2 = xn_size[1] - 2;
  }

  loop_ub = nd2 - i;
  for (nd2 = 0; nd2 < loop_ub; nd2++) {
    x_data[nd2] = xn_data[(i + nd2) + 1];
  }

  i = (short)loop_ub;
  if ((i != 0) && (i > 1)) {
    n = i - 1;
    nd2 = i >> 1;
    for (k = 0; k < nd2; k++) {
      tmp = x_data[k];
      x_tmp = n - k;
      x_data[k] = x_data[x_tmp];
      x_data[x_tmp] = tmp;
    }
  }

  b_x_data[0] = xn_data[3];
  b_x_data[1] = xn_data[2];
  b_x_data[2] = xn_data[1];
  nd2 = xn_size[1];
  if (0 <= nd2 - 1) {
    memcpy(&b_x_data[3], &xn_data[0], nd2 * sizeof(double));
  }

  for (i = 0; i < loop_ub; i++) {
    b_x_data[(i + xn_size[1]) + 3] = x_data[i];
  }

  /*  Symmetric extension! */
  i = xn_size[1];
  for (n = 0; n < i; n++) {
    if (n + 1 > n + 7) {
      nd2 = 0;
      x_tmp = -1;
    } else {
      nd2 = n;
      x_tmp = n + 6;
    }

    loop_ub = x_tmp - nd2;
    for (x_tmp = 0; x_tmp <= loop_ub; x_tmp++) {
      b0_data[x_tmp] = b_x_data[nd2 + x_tmp];
    }

    tmp = 0.0;
    for (k = 0; k < 7; k++) {
      tmp += a[k] * 0.125 * (b0_data[k] * 0.125) * 64.0;
    }

    yn_data[n] = tmp * 0.125;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
