/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
 */

#ifndef FILTERSYSTEM_H
#define FILTERSYSTEM_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "dwt_types.h"

/* Function Declarations */
extern void b_filterSystem(const short xn[512], short b_yn[512]);
extern void c_filterSystem(const short xn[256], short b_yn[256]);
extern void d_filterSystem(const short xn[256], short b_yn[256]);
extern void e_filterSystem(const short xn[128], short b_yn[128]);
extern void f_filterSystem(const short xn[128], short b_yn[128]);
extern void filterSystem(const short xn[512], short b_yn[512]);

#endif

/*
 * File trailer for filterSystem.h
 *
 * [EOF]
 */
