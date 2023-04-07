/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
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
#include "dwt.h"
#include "dwt_terminate.h"

/* Function Declarations */
static void argInit_512x512_sfix12(short result[262144]);
static double argInit_real_T(void);
static short argInit_sfix12(void);
static void main_dwt(void);

/* Function Definitions */

/*
 * Arguments    : short result[262144]
 * Return Type  : void
 */
static void argInit_512x512_sfix12(short result[262144])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 512; idx0++) {
    for (idx1 = 0; idx1 < 512; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 9)] = argInit_sfix12();
    }
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : short
 */
static short argInit_sfix12(void)
{
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_dwt(void)
{
  static short b_iv[262144];
  static short filtered_img[262144];

  /* Initialize function 'dwt' input arguments. */
  /* Initialize function input argument 'raw_img'. */
  /* Initialize function input argument 'T'. */
  /* Call the entry-point 'dwt'. */
  argInit_512x512_sfix12(b_iv);
  dwt(b_iv, argInit_real_T(), filtered_img);
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
  main_dwt();

  /* Terminate the application.
     You do not need to do this more than one time. */
  dwt_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
