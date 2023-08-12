/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 10:37:01
 */

#ifndef FILTERSYSTEM_H
#define FILTERSYSTEM_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "octave_types.h"

/* Function Declarations */
extern void b_filterSystem(const double xn_data[], const int xn_size[2], double
  yn_data[], int yn_size[2]);
extern void filterSystem(const double xn_data[], const int xn_size[2], double
  yn_data[], int yn_size[2]);

#endif

/*
 * File trailer for filterSystem.h
 *
 * [EOF]
 */
