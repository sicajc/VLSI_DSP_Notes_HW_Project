/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: cordic_rotation_mode.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 09-May-2023 23:11:02
 */

/* Include Files */
#include "cordic_rotation_mode.h"
#include "qr_cordic.h"
#include "qr_cordic_data.h"
#include <math.h>

/* Function Definitions */

/*
 * Rotation mode
 *  Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching
 *  Input:  vector (x,y) rotates it with the angle z
 *  Output: vector (xcos(z),ysin(z))
 *  Enables shift add multiply instead of calculation trigonemetric function
 *  tan(a^i) = 2^(-i), thus tan(a^i) is simply shift.
 *  Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation.
 *  Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero.
 * Arguments    : short x
 *                short y
 *                short *angle
 *                double iters_num
 *                int *x_result
 *                int *y_result
 * Return Type  : void
 */
void cordic_rotation_mode(short x, short y, short *angle, double iters_num, int *
  x_result, int *y_result)
{
  int i;
  int b_i;
  int i1;
  short i2;
  int b_x;
  int i3;
  short c;

  /*  This is Products of K_12 */
  /*  Turning into fixed point */
  i = (int)iters_num;
  for (b_i = 0; b_i < i; b_i++) {
    /*  Z is the current angle, and also the angle I want to shift toward to. */
    if (*angle > 0) {
      i1 = (int)fmod(b_i, 65536.0);
      i2 = (short)(y >> (short)i1);
      if ((i2 & 2048) != 0) {
        i2 = (short)(i2 | -2048);
      } else {
        i2 = (short)(i2 & 2047);
      }

      if ((x & 4096) != 0) {
        b_x = x | -4096;
      } else {
        b_x = x & 4095;
      }

      if ((i2 & 4096) != 0) {
        i3 = i2 | -4096;
      } else {
        i3 = i2 & 4095;
      }

      i2 = (short)(b_x + i3);
      if ((i2 & 4096) != 0) {
        c = (short)(i2 | -4096);
      } else {
        c = (short)(i2 & 4095);
      }

      i2 = (short)(x >> (short)i1);
      if ((i2 & 2048) != 0) {
        i2 = (short)(i2 | -2048);
      } else {
        i2 = (short)(i2 & 2047);
      }

      if ((y & 4096) != 0) {
        b_x = y | -4096;
      } else {
        b_x = y & 4095;
      }

      if ((i2 & 4096) != 0) {
        i1 = i2 | -4096;
      } else {
        i1 = i2 & 4095;
      }

      i2 = (short)(b_x - i1);
      if ((i2 & 4096) != 0) {
        y = (short)(i2 | -4096);
      } else {
        y = (short)(i2 & 4095);
      }

      if (y > 2047) {
        y = 2047;
      } else {
        if (y < -2048) {
          y = -2048;
        }
      }

      if (c > 2047) {
        c = 2047;
      } else {
        if (c < -2048) {
          c = -2048;
        }
      }

      x = c;
      i2 = (short)(*angle << 1);
      if ((i2 & 8192) != 0) {
        i1 = i2 | -8192;
      } else {
        i1 = i2 & 8191;
      }

      i2 = (short)(i1 - iv[b_i]);
      if ((i2 & 8192) != 0) {
        i1 = i2 | -8192;
      } else {
        i1 = i2 & 8191;
      }

      i2 = (short)((i1 + 1) >> 1);
      if (i2 > 2047) {
        i2 = 2047;
      } else {
        if (i2 < -2048) {
          i2 = -2048;
        }
      }

      *angle = i2;
    } else {
      i1 = (int)fmod(b_i, 65536.0);
      i2 = (short)(y >> (short)i1);
      if ((i2 & 2048) != 0) {
        i2 = (short)(i2 | -2048);
      } else {
        i2 = (short)(i2 & 2047);
      }

      if ((x & 4096) != 0) {
        b_x = x | -4096;
      } else {
        b_x = x & 4095;
      }

      if ((i2 & 4096) != 0) {
        i3 = i2 | -4096;
      } else {
        i3 = i2 & 4095;
      }

      i2 = (short)(b_x - i3);
      if ((i2 & 4096) != 0) {
        c = (short)(i2 | -4096);
      } else {
        c = (short)(i2 & 4095);
      }

      i2 = (short)(x >> (short)i1);
      if ((i2 & 2048) != 0) {
        i2 = (short)(i2 | -2048);
      } else {
        i2 = (short)(i2 & 2047);
      }

      if ((y & 4096) != 0) {
        b_x = y | -4096;
      } else {
        b_x = y & 4095;
      }

      if ((i2 & 4096) != 0) {
        i1 = i2 | -4096;
      } else {
        i1 = i2 & 4095;
      }

      i2 = (short)(b_x + i1);
      if ((i2 & 4096) != 0) {
        y = (short)(i2 | -4096);
      } else {
        y = (short)(i2 & 4095);
      }

      if (y > 2047) {
        y = 2047;
      } else {
        if (y < -2048) {
          y = -2048;
        }
      }

      if (c > 2047) {
        c = 2047;
      } else {
        if (c < -2048) {
          c = -2048;
        }
      }

      x = c;
      i2 = (short)(*angle << 1);
      if ((i2 & 8192) != 0) {
        i1 = i2 | -8192;
      } else {
        i1 = i2 & 8191;
      }

      i2 = (short)(i1 + iv[b_i]);
      if ((i2 & 8192) != 0) {
        i1 = i2 | -8192;
      } else {
        i1 = i2 & 8191;
      }

      i2 = (short)((i1 + 1) >> 1);
      if (i2 > 2047) {
        i2 = 2047;
      } else {
        if (i2 < -2048) {
          i2 = -2048;
        }
      }

      *angle = i2;
    }
  }

  i = x * 1244;
  if ((i & 8388608) != 0) {
    *x_result = i | -8388608;
  } else {
    *x_result = i & 8388607;
  }

  i = y * 1244;
  if ((i & 8388608) != 0) {
    *y_result = i | -8388608;
  } else {
    *y_result = i & 8388607;
  }
}

/*
 * File trailer for cordic_rotation_mode.c
 *
 * [EOF]
 */
