/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 31-Mar-2023 20:58:47
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "filterSystem.h"
#include "filterSystem_terminate.h"

/* Function Declarations */
static void argInit_1x8_flts16_En15(double result[8]);
static void argInit_1x9_flts16_En15(double result[9]);
static double argInit_flts16_En15(void);
static void main_filterSystem(void);

/* Function Definitions */

/*
 * Arguments    : double result[8]
 * Return Type  : void
 */
static void argInit_1x8_flts16_En15(double result[8])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 8; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_flts16_En15();
  }
}

/*
 * Arguments    : double result[9]
 * Return Type  : void
 */
static void argInit_1x9_flts16_En15(double result[9])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 9; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_flts16_En15();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_flts16_En15(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_filterSystem(void)
{
  double dv[8];
  double dv1[9];
  double b_yn[8];

  /* Initialize function 'filterSystem' input arguments. */
  /* Initialize function input argument 'xn'. */
  /* Initialize function input argument 'wn'. */
  /* Initialize function input argument 'T'. */
  /* Call the entry-point 'filterSystem'. */
  argInit_1x8_flts16_En15(dv);
  argInit_1x9_flts16_En15(dv1);
  filterSystem(dv, dv1, argInit_flts16_En15(), b_yn);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* The initialize function is being called automatically from your entry-point function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_filterSystem();

  /* Terminate the application.
     You do not need to do this more than one time. */
  filterSystem_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
