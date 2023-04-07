/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_filterSystem_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 31-Mar-2023 20:58:47
 */

#ifndef _CODER_FILTERSYSTEM_API_H
#define _CODER_FILTERSYSTEM_API_H

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
extern void filterSystem(real_T xn[8], real_T wn[9], real_T N, real_T b_yn[8]);
extern void filterSystem_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[1]);
extern void filterSystem_atexit(void);
extern void filterSystem_initialize(void);
extern void filterSystem_terminate(void);
extern void filterSystem_xil_shutdown(void);
extern void filterSystem_xil_terminate(void);

#endif

/*
 * File trailer for _coder_filterSystem_api.h
 *
 * [EOF]
 */
