/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: main.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 09-May-2023 23:11:02
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
#include "qr_cordic.h"
#include "qr_cordic_terminate.h"

/* Function Declarations */
static void argInit_4x4_sfix12_En10(short result[16]);
static short argInit_sfix12_En10(void);
static void main_qr_cordic(void);

/* Function Definitions */

/*
 * Arguments    : short result[16]
 * Return Type  : void
 */
static void argInit_4x4_sfix12_En10(short result[16])
{
  short result_tmp;
  int idx0;

  /* Loop over the array to initialize each element. */
  result_tmp = argInit_sfix12_En10();
  for (idx0 = 0; idx0 < 4; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 4] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 8] = result_tmp;

    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0 + 12] = result_tmp;
  }
}

/*
 * Arguments    : void
 * Return Type  : short
 */
static short argInit_sfix12_En10(void)
{
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_qr_cordic(void)
{
  short b_iv[16];
  short Q[16];
  short R[16];

  /* Initialize function 'qr_cordic' input arguments. */
  /* Initialize function input argument 'M'. */
  /* Initialize function input argument 'T'. */
  /* Call the entry-point 'qr_cordic'. */
  argInit_4x4_sfix12_En10(b_iv);
  qr_cordic(b_iv, Q, R);
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
  main_qr_cordic();

  /* Terminate the application.
     You do not need to do this more than one time. */
  qr_cordic_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
