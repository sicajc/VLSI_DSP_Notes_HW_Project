/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 19:49:54
 */

#ifndef FILTERSYSTEM_H
#define FILTERSYSTEM_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "dwt_types.h"

/* Function Declarations */
extern void b_filterSystem(const double xn[512], double b_yn[512]);
extern void c_filterSystem(const double xn[256], double b_yn[256]);
extern void d_filterSystem(const double xn[256], double b_yn[256]);
extern void e_filterSystem(const double xn[128], double b_yn[128]);
extern void f_filterSystem(const double xn[128], double b_yn[128]);
extern void filterSystem(const double xn[512], double b_yn[512]);

#endif

/*
 * File trailer for filterSystem.h
 *
 * [EOF]
 */
