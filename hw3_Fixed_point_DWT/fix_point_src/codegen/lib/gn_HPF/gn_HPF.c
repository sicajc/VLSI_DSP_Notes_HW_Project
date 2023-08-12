/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: gn_HPF.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:07:33
 */

/* Include Files */
#include "gn_HPF.h"
#include "filterSystem.h"
#include <string.h>

/* Function Definitions */

/*
 * Arguments    : const double raw_img[262144]
 *                double horizontal
 *                double filtered_img[262144]
 * Return Type  : void
 */
void gn_HPF(const double raw_img[262144], double horizontal, double
            filtered_img[262144])
{
  int i;
  int filtered_col_tmp;
  double filtered_col[512];
  double dv[512];
  if (horizontal == 1.0) {
    /* Horizontal filtering */
    for (i = 0; i < 512; i++) {
      for (filtered_col_tmp = 0; filtered_col_tmp < 512; filtered_col_tmp++) {
        filtered_col[filtered_col_tmp] = raw_img[i + (filtered_col_tmp << 9)];
      }

      filterSystem(filtered_col, dv);
      for (filtered_col_tmp = 0; filtered_col_tmp < 512; filtered_col_tmp++) {
        filtered_img[i + (filtered_col_tmp << 9)] = dv[filtered_col_tmp];
      }
    }
  } else {
    /*  Vertical filtering */
    for (i = 0; i < 512; i++) {
      filtered_col_tmp = i << 9;
      filterSystem(*(double (*)[512])&raw_img[filtered_col_tmp], filtered_col);
      memcpy(&filtered_img[filtered_col_tmp], &filtered_col[0], 512U * sizeof
             (double));
    }
  }
}

/*
 * File trailer for gn_HPF.c
 *
 * [EOF]
 */
