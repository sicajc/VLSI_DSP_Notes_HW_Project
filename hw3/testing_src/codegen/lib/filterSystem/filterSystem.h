/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 31-Mar-2023 20:58:47
 */

#ifndef FILTERSYSTEM_H
#define FILTERSYSTEM_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "filterSystem_types.h"

/* Function Declarations */
extern void filterSystem(const double xn[8], const double wn[9], double N,
  double b_yn[8]);

#endif

/*
 * File trailer for filterSystem.h
 *
 * [EOF]
 */
