/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_dwt_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
 */

#ifndef _CODER_DWT_API_H
#define _CODER_DWT_API_H

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
extern void dwt(int16_T raw_img[262144], real_T stride, int16_T filtered_img
                [262144]);
extern void dwt_api(const mxArray * const prhs[3], int32_T nlhs, const mxArray
                    *plhs[1]);
extern void dwt_atexit(void);
extern void dwt_initialize(void);
extern void dwt_terminate(void);
extern void dwt_xil_shutdown(void);
extern void dwt_xil_terminate(void);

#endif

/*
 * File trailer for _coder_dwt_api.h
 *
 * [EOF]
 */
