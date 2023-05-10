/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_qr_cordic_opt_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 10-May-2023 19:30:40
 */

#ifndef _CODER_QR_CORDIC_OPT_API_H
#define _CODER_QR_CORDIC_OPT_API_H

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
extern void qr_cordic_opt(int16_T M[16], int16_T Q[16], int16_T R[16]);
extern void qr_cordic_opt_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[2]);
extern void qr_cordic_opt_atexit(void);
extern void qr_cordic_opt_initialize(void);
extern void qr_cordic_opt_terminate(void);
extern void qr_cordic_opt_xil_shutdown(void);
extern void qr_cordic_opt_xil_terminate(void);

#endif

/*
 * File trailer for _coder_qr_cordic_opt_api.h
 *
 * [EOF]
 */
