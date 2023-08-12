/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: gn_HPF.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

/* Include Files */
#include "gn_HPF.h"
#include "filterSystem.h"
#include "octave.h"
#include "octave_emxutil.h"
#include "rt_nonfinite.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *raw_img
 *                emxArray_real_T *filtered_img
 * Return Type  : void
 */
void b_gn_HPF(const emxArray_real_T *raw_img, emxArray_real_T *filtered_img)
{
  int i;
  int loop_ub;
  int raw_img_size[2];
  int b_i;
  int i1;
  double raw_img_data[512];
  double filtered_col_data[512];
  int filtered_col_size[2];
  i = filtered_img->size[0] * filtered_img->size[1];
  filtered_img->size[0] = raw_img->size[0];
  filtered_img->size[1] = raw_img->size[1];
  emxEnsureCapacity_real_T(filtered_img, i);
  loop_ub = raw_img->size[0] * raw_img->size[1];
  for (i = 0; i < loop_ub; i++) {
    filtered_img->data[i] = raw_img->data[i];
  }

  /*  Vertical filtering */
  i = raw_img->size[1];
  if (0 <= i - 1) {
    raw_img_size[0] = 1;
  }

  for (b_i = 0; b_i < i; b_i++) {
    loop_ub = raw_img->size[0];
    raw_img_size[1] = raw_img->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      raw_img_data[i1] = raw_img->data[i1 + raw_img->size[0] * b_i];
    }

    filterSystem(raw_img_data, raw_img_size, filtered_col_data,
                 filtered_col_size);
    loop_ub = filtered_img->size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      filtered_img->data[i1 + filtered_img->size[0] * b_i] =
        filtered_col_data[i1];
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *raw_img
 *                emxArray_real_T *filtered_img
 * Return Type  : void
 */
void gn_HPF(const emxArray_real_T *raw_img, emxArray_real_T *filtered_img)
{
  int i;
  int loop_ub;
  int raw_img_size[2];
  int b_i;
  int i1;
  double raw_img_data[512];
  double filtered_row_data[512];
  int filtered_row_size[2];
  i = filtered_img->size[0] * filtered_img->size[1];
  filtered_img->size[0] = raw_img->size[0];
  filtered_img->size[1] = raw_img->size[1];
  emxEnsureCapacity_real_T(filtered_img, i);
  loop_ub = raw_img->size[0] * raw_img->size[1];
  for (i = 0; i < loop_ub; i++) {
    filtered_img->data[i] = raw_img->data[i];
  }

  /* Horizontal filtering */
  i = raw_img->size[0];
  if (0 <= i - 1) {
    raw_img_size[0] = 1;
  }

  for (b_i = 0; b_i < i; b_i++) {
    loop_ub = raw_img->size[1];
    raw_img_size[1] = raw_img->size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      raw_img_data[i1] = raw_img->data[b_i + raw_img->size[0] * i1];
    }

    filterSystem(raw_img_data, raw_img_size, filtered_row_data,
                 filtered_row_size);
    loop_ub = filtered_row_size[1];
    for (i1 = 0; i1 < loop_ub; i1++) {
      filtered_img->data[b_i + filtered_img->size[0] * i1] =
        filtered_row_data[i1];
    }
  }
}

/*
 * File trailer for gn_HPF.c
 *
 * [EOF]
 */
