/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:07:33
 */

/* Include Files */
#include "filterSystem.h"
#include "gn_HPF.h"
#include <string.h>

/* Function Definitions */

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
  static const double a[7] = { -1.032622122064, 0.651030681744, 6.689476371552,
    -12.615769862496, 6.689476371552, 0.651030681744, -1.032622122064 };

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
      c += a[loop_ub] * 0.0625 * (b0_data[loop_ub] * 0.0625) * 256.0;
    }

    b_yn[i] = c * 0.0625;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
