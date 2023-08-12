/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qr_cordic.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 09-May-2023 23:11:02
 */

/* Include Files */
#include "qr_cordic.h"
#include "cordic_rotation_mode.h"
#include "qr_cordic_data.h"

/* Function Definitions */

/*
 * Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
 * Arguments    : short M[16]
 *                short Q[16]
 *                short R[16]
 * Return Type  : void
 */
void qr_cordic(short M[16], short Q[16], short R[16])
{
  int i;
  int k;
  static const short b_iv[16] = { 1024, 0, 0, 0, 0, 1024, 0, 0, 0, 0, 1024, 0, 0,
    0, 0, 1024 };

  int b_i;
  int x_tmp;
  short b_Q[16];
  short x;
  short y;
  short theta;
  int c_i;
  int i1;
  int j;
  int tmp2;
  short i2;
  int i3;
  short c;

  /*  Augmenting the matrix I to the left, updating I alongside with A when performing rotation */
  /*  Turning into fixed point */
  for (i = 0; i < 16; i++) {
    Q[i] = b_iv[i];
  }

  for (k = 0; k < 4; k++) {
    i = (int)(((((double)k + 1.0) + 1.0) + -5.0) / -1.0);
    for (b_i = 0; b_i < i; b_i++) {
      /*  This needed to be replaced with cordic, vectoring mode. */
      /*  Use vector mode to calculate of givens rotation */
      /*  Fixed point */
      x_tmp = (k << 2) - b_i;
      x = M[x_tmp + 2];
      y = M[x_tmp + 3];

      /*  Vectoring mode */
      /*  Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively */
      /*  Input:  vector (x,y) rotates it with the angle z */
      /*  Output: Value after rotation (x,y) also the angle of tan(y/x) */
      /*  Goal is trying to nullify y accumulating the angle when rotating. */
      /*  Turning into fixed point */
      theta = 0;
      for (c_i = 0; c_i < 12; c_i++) {
        /*  Z is the current angle, and also the angle I want to shift toward to. */
        i1 = x * y;
        if ((i1 & 8388608) != 0) {
          x_tmp = i1 | -8388608;
        } else {
          x_tmp = i1 & 8388607;
        }

        if ((x_tmp > 0) || (x_tmp >= 0)) {
          i2 = (short)(y >> c_i);
          if ((i2 & 2048) != 0) {
            i2 = (short)(i2 | -2048);
          } else {
            i2 = (short)(i2 & 2047);
          }

          if ((x & 4096) != 0) {
            x_tmp = x | -4096;
          } else {
            x_tmp = x & 4095;
          }

          if ((i2 & 4096) != 0) {
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(x_tmp + i1);
          if ((i2 & 4096) != 0) {
            c = (short)(i2 | -4096);
          } else {
            c = (short)(i2 & 4095);
          }

          i2 = (short)(x >> c_i);
          if ((i2 & 2048) != 0) {
            i2 = (short)(i2 | -2048);
          } else {
            i2 = (short)(i2 & 2047);
          }

          if ((y & 4096) != 0) {
            x_tmp = y | -4096;
          } else {
            x_tmp = y & 4095;
          }

          if ((i2 & 4096) != 0) {
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(x_tmp - i1);
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
          i2 = (short)(theta << 1);
          if ((i2 & 8192) != 0) {
            i1 = i2 | -8192;
          } else {
            i1 = i2 & 8191;
          }

          i2 = (short)(i1 + iv[c_i]);
          if ((i2 & 8192) != 0) {
            i1 = i2 | -8192;
          } else {
            i1 = i2 & 8191;
          }

          theta = (short)((i1 + 1) >> 1);
          if (theta > 2047) {
            theta = 2047;
          } else {
            if (theta < -2048) {
              theta = -2048;
            }
          }
        } else {
          /*  Because in vector mode, di is defined as -sign(x,y), deriving this from the rotation matrix. */
          /*  Since counterclockwise rotation is of (c  s) however, my version uses clockwise rotation, thus should be (c -s) */
          /*                                        (-s c),                                                            (s  c). */
          i2 = (short)(y >> c_i);
          if ((i2 & 2048) != 0) {
            i2 = (short)(i2 | -2048);
          } else {
            i2 = (short)(i2 & 2047);
          }

          if ((x & 4096) != 0) {
            x_tmp = x | -4096;
          } else {
            x_tmp = x & 4095;
          }

          if ((i2 & 4096) != 0) {
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(x_tmp - i1);
          if ((i2 & 4096) != 0) {
            c = (short)(i2 | -4096);
          } else {
            c = (short)(i2 & 4095);
          }

          i2 = (short)(x >> c_i);
          if ((i2 & 2048) != 0) {
            i2 = (short)(i2 | -2048);
          } else {
            i2 = (short)(i2 & 2047);
          }

          if ((y & 4096) != 0) {
            x_tmp = y | -4096;
          } else {
            x_tmp = y & 4095;
          }

          if ((i2 & 4096) != 0) {
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(x_tmp + i1);
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
          i2 = (short)(theta << 1);
          if ((i2 & 8192) != 0) {
            i1 = i2 | -8192;
          } else {
            i1 = i2 & 8191;
          }

          i2 = (short)(i1 - iv[c_i]);
          if ((i2 & 8192) != 0) {
            i1 = i2 | -8192;
          } else {
            i1 = i2 & 8191;
          }

          theta = (short)((i1 + 1) >> 1);
          if (theta > 2047) {
            theta = 2047;
          } else {
            if (theta < -2048) {
              theta = -2048;
            }
          }
        }
      }

      /*  fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i); */
      i1 = 3 - k;
      for (j = 0; j <= i1; j++) {
        c_i = k + j;

        /*  For R */
        /*  This needed to be replaced with cordic, rotation mode */
        x = theta;
        cordic_rotation_mode(M[((c_i << 2) - b_i) + 2], M[((c_i << 2) - b_i) + 3],
                             &x, 12.0, &x_tmp, &tmp2);

        /*  fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j); */
        i3 = (x_tmp + 1024) >> 11;
        if (i3 > 2047) {
          i3 = 2047;
        } else {
          if (i3 < -2048) {
            i3 = -2048;
          }
        }

        x_tmp = (c_i << 2) - b_i;
        M[x_tmp + 2] = (short)i3;
        i3 = (tmp2 + 1024) >> 11;
        if (i3 > 2047) {
          i3 = 2047;
        } else {
          if (i3 < -2048) {
            i3 = -2048;
          }
        }

        M[x_tmp + 3] = (short)i3;
      }

      /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
      x = theta;
      cordic_rotation_mode(Q[2 - b_i], Q[3 - b_i], &x, 12.0, &x_tmp, &tmp2);
      i1 = (x_tmp + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[2 - b_i] = (short)i1;
      i1 = (tmp2 + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[3 - b_i] = (short)i1;

      /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
      x = theta;
      cordic_rotation_mode(Q[6 - b_i], Q[7 - b_i], &x, 12.0, &x_tmp, &tmp2);
      i1 = (x_tmp + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[6 - b_i] = (short)i1;
      i1 = (tmp2 + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[7 - b_i] = (short)i1;

      /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
      x = theta;
      cordic_rotation_mode(Q[10 - b_i], Q[11 - b_i], &x, 12.0, &x_tmp, &tmp2);
      i1 = (x_tmp + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[10 - b_i] = (short)i1;
      i1 = (tmp2 + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[11 - b_i] = (short)i1;

      /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
      x = theta;
      cordic_rotation_mode(Q[14 - b_i], Q[15 - b_i], &x, 12.0, &x_tmp, &tmp2);
      i1 = (x_tmp + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[14 - b_i] = (short)i1;
      i1 = (tmp2 + 1024) >> 11;
      if (i1 > 2047) {
        i1 = 2047;
      } else {
        if (i1 < -2048) {
          i1 = -2048;
        }
      }

      Q[15 - b_i] = (short)i1;
    }
  }

  for (i = 0; i < 16; i++) {
    R[i] = M[i];
  }

  for (i = 0; i < 4; i++) {
    x_tmp = i << 2;
    b_Q[x_tmp] = Q[i];
    b_Q[x_tmp + 1] = Q[i + 4];
    b_Q[x_tmp + 2] = Q[i + 8];
    b_Q[x_tmp + 3] = Q[i + 12];
  }

  for (i = 0; i < 16; i++) {
    Q[i] = b_Q[i];
  }
}

/*
 * File trailer for qr_cordic.c
 *
 * [EOF]
 */
