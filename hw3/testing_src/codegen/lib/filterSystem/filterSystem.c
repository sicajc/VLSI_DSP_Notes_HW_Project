/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 31-Mar-2023 20:58:47
 */

/* Include Files */
#include "filterSystem.h"
#include <string.h>

/* Function Definitions */

/*
 * Arguments    : const double xn[8]
 *                const double wn[9]
 *                double N
 *                double b_yn[8]
 * Return Type  : void
 */
void filterSystem(const double xn[8], const double wn[9], double N, double b_yn
                  [8])
{
  double x[16];
  int i;
  double c;
  int k;
  (void)N;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 8U * sizeof(double));
  x[12] = xn[6];
  x[13] = xn[5];
  x[14] = xn[4];
  x[15] = xn[3];

  /*  Symmetric extension! */
  for (i = 0; i < 8; i++) {
    c = 0.0;
    for (k = 0; k < 9; k++) {
      c += wn[k] * 3.0517578125E-5 * (x[i + k] * 3.0517578125E-5) *
        1.073741824E+9;
    }

    b_yn[i] = c * 1.52587890625E-5;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
