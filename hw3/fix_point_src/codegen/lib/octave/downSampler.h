/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: downSampler.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

#ifndef DOWNSAMPLER_H
#define DOWNSAMPLER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "octave_types.h"

/* Function Declarations */
extern void b_downSampler(const emxArray_real_T *img, double stride,
  emxArray_real_T *downSampledimg);
extern void downSampler(const emxArray_real_T *img, double stride,
  emxArray_real_T *downSampledimg);

#endif

/*
 * File trailer for downSampler.h
 *
 * [EOF]
 */
