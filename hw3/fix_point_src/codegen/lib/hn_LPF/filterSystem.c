/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:10:07
 */

/* Include Files */
#include "filterSystem.h"
#include "hn_LPF.h"
#include <string.h>

/* Function Definitions */

/*
 * Arguments    : const double xn[512]
 *                double b_yn[512]
 * Return Type  : void
 */
void filterSystem(const double xn[512], double b_yn[512])
{
  double x[520];
  int i;
  double b0_data[520];
  double c;
  int loop_ub;
  static const double a[9] = { 0.605255288112, -0.38159144032, -1.769990470688,
    6.038445689808, 13.643178864144, 6.038445689808, -1.769990470688,
    -0.38159144032, 0.605255288112 };

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
