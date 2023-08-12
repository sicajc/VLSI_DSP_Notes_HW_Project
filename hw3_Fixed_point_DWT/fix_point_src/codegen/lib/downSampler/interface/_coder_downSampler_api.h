/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_downSampler_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 09:47:10
 */

#ifndef _CODER_DOWNSAMPLER_API_H
#define _CODER_DOWNSAMPLER_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void downSampler(real_T img[262144], real_T stride, real_T odd, real_T n,
  real_T horizontal, real_T downSampledimg[262144]);
extern void downSampler_api(const mxArray * const prhs[6], int32_T nlhs, const
  mxArray *plhs[1]);
extern void downSampler_atexit(void);
extern void downSampler_initialize(void);
extern void downSampler_terminate(void);
extern void downSampler_xil_shutdown(void);
extern void downSampler_xil_terminate(void);

#endif

/*
 * File trailer for _coder_downSampler_api.h
 *
 * [EOF]
 */
