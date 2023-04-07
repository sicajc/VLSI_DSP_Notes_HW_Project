/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: octave.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 12:06:50
 */

#ifndef OCTAVE_H
#define OCTAVE_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "dwt_types.h"

/* Function Declarations */
extern void b_octave(int raw_img[262144], double stride);
extern void c_octave(int raw_img[262144], double stride);
extern void octave(int raw_img[262144], double stride);

#endif

/*
 * File trailer for octave.h
 *
 * [EOF]
 */
