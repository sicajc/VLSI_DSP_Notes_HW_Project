/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: downSampler.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 09:47:10
 */

#ifndef DOWNSAMPLER_H
#define DOWNSAMPLER_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "downSampler_types.h"

/* Function Declarations */
extern void downSampler(const double img[262144], double stride, double odd,
  double n, double horizontal, double downSampledimg[262144]);

#endif

/*
 * File trailer for downSampler.h
 *
 * [EOF]
 */
