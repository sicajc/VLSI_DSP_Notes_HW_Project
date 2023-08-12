/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_octave_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

#ifndef _CODER_OCTAVE_API_H
#define _CODER_OCTAVE_API_H

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
extern void octave(real_T raw_img[262144], real_T stride, real_T n, real_T
                   filtered_img[262144]);
extern void octave_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[1]);
extern void octave_atexit(void);
extern void octave_initialize(void);
extern void octave_terminate(void);
extern void octave_xil_shutdown(void);
extern void octave_xil_terminate(void);

#endif

/*
 * File trailer for _coder_octave_api.h
 *
 * [EOF]
 */
