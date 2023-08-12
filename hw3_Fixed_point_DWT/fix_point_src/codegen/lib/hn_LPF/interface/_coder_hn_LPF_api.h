/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_hn_LPF_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:10:07
 */

#ifndef _CODER_HN_LPF_API_H
#define _CODER_HN_LPF_API_H

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
extern void hn_LPF(real_T raw_img[262144], real_T horizontal, real_T
                   filtered_img[262144]);
extern void hn_LPF_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1]);
extern void hn_LPF_atexit(void);
extern void hn_LPF_initialize(void);
extern void hn_LPF_terminate(void);
extern void hn_LPF_xil_shutdown(void);
extern void hn_LPF_xil_terminate(void);

#endif

/*
 * File trailer for _coder_hn_LPF_api.h
 *
 * [EOF]
 */
