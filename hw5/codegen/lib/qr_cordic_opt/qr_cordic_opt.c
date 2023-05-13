/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qr_cordic_opt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 12-May-2023 15:28:17
 */

/* Include Files */
#include "qr_cordic_opt.h"

/* Function Definitions */

/*
 * Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
 * Arguments    : const signed char M[16]
 *                short Q[16]
 *                short R[16]
 * Return Type  : void
 */
void qr_cordic_opt(const signed char M[16], short Q[16], short R[16])
{
  int i;
  int k;
  short i1;
  int b_i;
  static const short iv[16] = { 1024, 0, 0, 0, 0, 1024, 0, 0, 0, 0, 1024, 0, 0,
    0, 0, 1024 };

  int x_tmp;
  int b_x_tmp;
  int x;
  int y;
  int c_i;
  int j;
  int b_x;
  short c_x;
  short b_y;
  int i2;
  int i3;
  double d[12];
  short c;

  /*  Augmenting the matrix I to the left, updating I alongside with A when performing rotation */
  /*  Turning into fixed point */
  for (i = 0; i < 16; i++) {
    i1 = (short)(M[i] << 3);
    if ((i1 & 2048) != 0) {
      R[i] = (short)(i1 | -2048);
    } else {
      R[i] = (short)(i1 & 2047);
    }

    Q[i] = iv[i];
  }

  for (k = 0; k < 4; k++) {
    i = (int)(((((double)k + 1.0) + 1.0) + -5.0) / -1.0);
    for (b_i = 0; b_i < i; b_i++) {
      /*  This needed to be replaced with cordic, vectoring mode. */
      /*  Use vector mode to calculate of givens rotation */
      /*  Vectoring mode */
      /*  Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively */
      /*  Input:  vector (x,y) rotates it with the angle z */
      /*  Output: Value after rotation (x,y) also the angle of tan(y/x) */
      /*  Goal is trying to nullify y accumulating the angle when rotating. */
      /*  Turning into fixed point */
      /*  The partial result during calculation */
      x_tmp = (k << 2) - b_i;
      b_x_tmp = R[x_tmp + 2] << 7;
      if ((b_x_tmp & 524288) != 0) {
        x = b_x_tmp | -524288;
      } else {
        x = b_x_tmp & 524287;
      }

      x_tmp = R[x_tmp + 3] << 7;
      if ((x_tmp & 524288) != 0) {
        y = x_tmp | -524288;
      } else {
        y = x_tmp & 524287;
      }

      /*  The result of each stage. */
      for (c_i = 0; c_i < 12; c_i++) {
        /*  Z is the current angle, and also the angle I want to shift toward to. */
        if ((int)(((long long)x * y) >> 8) > 0) {
          /*  Since it is at the first dimension, we shoudl shift in a clockwise manner. */
          /*  Since we are trying to obtain the angle, we must first add when we are rotating. */
          x_tmp = y >> c_i;
          if ((x_tmp & 524288) != 0) {
            x_tmp |= -524288;
          } else {
            x_tmp &= 524287;
          }

          if ((x & 1048576) != 0) {
            b_x = x | -1048576;
          } else {
            b_x = x & 1048575;
          }

          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          x_tmp += b_x;
          if ((x_tmp & 1048576) != 0) {
            b_x = x_tmp | -1048576;
          } else {
            b_x = x_tmp & 1048575;
          }

          x_tmp = x >> c_i;
          if ((x_tmp & 524288) != 0) {
            x_tmp |= -524288;
          } else {
            x_tmp &= 524287;
          }

          if ((y & 1048576) != 0) {
            y |= -1048576;
          } else {
            y &= 1048575;
          }

          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          x_tmp = y - x_tmp;
          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          if ((x_tmp & 524288) != 0) {
            y = x_tmp | -524288;
          } else {
            y = x_tmp & 524287;
          }

          if ((b_x & 524288) != 0) {
            x = b_x | -524288;
          } else {
            x = b_x & 524287;
          }

          d[c_i] = 0.0;
        } else {
          /*  Otherwise shift in a CounterClockwise(CC) manner */
          x_tmp = y >> c_i;
          if ((x_tmp & 524288) != 0) {
            x_tmp |= -524288;
          } else {
            x_tmp &= 524287;
          }

          if ((x & 1048576) != 0) {
            b_x = x | -1048576;
          } else {
            b_x = x & 1048575;
          }

          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          x_tmp = b_x - x_tmp;
          if ((x_tmp & 1048576) != 0) {
            b_x = x_tmp | -1048576;
          } else {
            b_x = x_tmp & 1048575;
          }

          x_tmp = x >> c_i;
          if ((x_tmp & 524288) != 0) {
            x_tmp |= -524288;
          } else {
            x_tmp &= 524287;
          }

          if ((y & 1048576) != 0) {
            y |= -1048576;
          } else {
            y &= 1048575;
          }

          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          x_tmp += y;
          if ((x_tmp & 1048576) != 0) {
            x_tmp |= -1048576;
          } else {
            x_tmp &= 1048575;
          }

          if ((x_tmp & 524288) != 0) {
            y = x_tmp | -524288;
          } else {
            y = x_tmp & 524287;
          }

          if ((b_x & 524288) != 0) {
            x = b_x | -524288;
          } else {
            x = b_x & 524287;
          }

          d[c_i] = 1.0;
        }
      }

      /*  fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i); */
      x_tmp = 3 - k;
      for (j = 0; j <= x_tmp; j++) {
        /*  For R */
        /*  This needed to be replaced with cordic, rotation mode */
        /*  Rotation mode */
        /*  Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching */
        /*  Input:  vector (x,y) rotates it with the angle z */
        /*  Output: vector (xcos(z),ysin(z)) */
        /*  Enables shift add multiply instead of calculation trigonemetric function */
        /*  tan(a^i) = 2^(-i), thus tan(a^i) is simply shift. */
        /*  Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation. */
        /*  Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero. */
        /*  This is Products of K_12 */
        /*  Turning into fixed point */
        /*  The partial result during calculation */
        b_x_tmp = ((k + j) << 2) - b_i;
        i2 = b_x_tmp + 2;
        i3 = R[i2] << 7;
        if ((i3 & 524288) != 0) {
          x = i3 | -524288;
        } else {
          x = i3 & 524287;
        }

        b_x_tmp += 3;
        i3 = R[b_x_tmp] << 7;
        if ((i3 & 524288) != 0) {
          y = i3 | -524288;
        } else {
          y = i3 & 524287;
        }

        /*  The result of each stage. */
        for (c_i = 0; c_i < 12; c_i++) {
          /*  Z is the current angle, and also the angle I want to shift toward to. */
          if (d[c_i] == 0.0) {
            /*  If angle is above 0, I would like to rotate in a clockwise manner */
            i3 = y >> c_i;
            if ((i3 & 524288) != 0) {
              i3 |= -524288;
            } else {
              i3 &= 524287;
            }

            if ((x & 1048576) != 0) {
              b_x = x | -1048576;
            } else {
              b_x = x & 1048575;
            }

            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            i3 += b_x;
            if ((i3 & 1048576) != 0) {
              b_x = i3 | -1048576;
            } else {
              b_x = i3 & 1048575;
            }

            i3 = x >> c_i;
            if ((i3 & 524288) != 0) {
              i3 |= -524288;
            } else {
              i3 &= 524287;
            }

            if ((y & 1048576) != 0) {
              y |= -1048576;
            } else {
              y &= 1048575;
            }

            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            i3 = y - i3;
            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            if ((i3 & 524288) != 0) {
              y = i3 | -524288;
            } else {
              y = i3 & 524287;
            }

            if ((b_x & 524288) != 0) {
              x = b_x | -524288;
            } else {
              x = b_x & 524287;
            }
          } else {
            /*  Otherwise, rotate counter clockwise. */
            i3 = y >> c_i;
            if ((i3 & 524288) != 0) {
              i3 |= -524288;
            } else {
              i3 &= 524287;
            }

            if ((x & 1048576) != 0) {
              b_x = x | -1048576;
            } else {
              b_x = x & 1048575;
            }

            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            i3 = b_x - i3;
            if ((i3 & 1048576) != 0) {
              b_x = i3 | -1048576;
            } else {
              b_x = i3 & 1048575;
            }

            i3 = x >> c_i;
            if ((i3 & 524288) != 0) {
              i3 |= -524288;
            } else {
              i3 &= 524287;
            }

            if ((y & 1048576) != 0) {
              y |= -1048576;
            } else {
              y &= 1048575;
            }

            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            i3 += y;
            if ((i3 & 1048576) != 0) {
              i3 |= -1048576;
            } else {
              i3 &= 1048575;
            }

            if ((i3 & 524288) != 0) {
              y = i3 | -524288;
            } else {
              y = i3 & 524287;
            }

            if ((b_x & 524288) != 0) {
              x = b_x | -524288;
            } else {
              x = b_x & 524287;
            }
          }
        }

        /*  Output xn, yn */
        i1 = (short)((x * 621) >> 17);
        if ((i1 & 2048) != 0) {
          R[i2] = (short)(i1 | -2048);
        } else {
          R[i2] = (short)(i1 & 2047);
        }

        i1 = (short)((y * 621) >> 17);
        if ((i1 & 2048) != 0) {
          R[b_x_tmp] = (short)(i1 | -2048);
        } else {
          R[b_x_tmp] = (short)(i1 & 2047);
        }

        /*  fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j); */
      }

      for (j = 0; j < 4; j++) {
        /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
        x_tmp = (j << 2) - b_i;
        b_x_tmp = x_tmp + 2;
        c_x = Q[b_x_tmp];
        x_tmp += 3;
        b_y = Q[x_tmp];

        /*  Rotation mode */
        /*  Description: Rotation mode using Linear rotation and multiplied by a constant K = 0.607252935 for stretching */
        /*  Input:  vector (x,y) rotates it with the angle z */
        /*  Output: vector (xcos(z),ysin(z)) */
        /*  Enables shift add multiply instead of calculation trigonemetric function */
        /*  tan(a^i) = 2^(-i), thus tan(a^i) is simply shift. */
        /*  Try to approach the desirable angle, we multiply the cos(a^i) only after the complete rotation. */
        /*  Simply multiply K = 0.607252935 after the rotations. See if the angle difference approach to zero. */
        /*  This is Products of K_12 */
        /*  Turning into fixed point */
        /*  The partial result during calculation */
        /*  The result of each stage. */
        for (c_i = 0; c_i < 12; c_i++) {
          /*  Z is the current angle, and also the angle I want to shift toward to. */
          if (d[c_i] == 0.0) {
            /*  If angle is above 0, I would like to rotate in a clockwise manner */
            i1 = (short)(b_y >> c_i);
            if ((i1 & 2048) != 0) {
              i1 = (short)(i1 | -2048);
            } else {
              i1 = (short)(i1 & 2047);
            }

            if ((c_x & 4096) != 0) {
              x = c_x | -4096;
            } else {
              x = c_x & 4095;
            }

            if ((i1 & 4096) != 0) {
              i2 = i1 | -4096;
            } else {
              i2 = i1 & 4095;
            }

            i1 = (short)(x + i2);
            if ((i1 & 4096) != 0) {
              c = (short)(i1 | -4096);
            } else {
              c = (short)(i1 & 4095);
            }

            i1 = (short)(c_x >> c_i);
            if ((i1 & 2048) != 0) {
              i1 = (short)(i1 | -2048);
            } else {
              i1 = (short)(i1 & 2047);
            }

            if ((b_y & 4096) != 0) {
              y = b_y | -4096;
            } else {
              y = b_y & 4095;
            }

            if ((i1 & 4096) != 0) {
              i2 = i1 | -4096;
            } else {
              i2 = i1 & 4095;
            }

            i1 = (short)(y - i2);
            if ((i1 & 4096) != 0) {
              i1 = (short)(i1 | -4096);
            } else {
              i1 = (short)(i1 & 4095);
            }

            if ((i1 & 2048) != 0) {
              b_y = (short)(i1 | -2048);
            } else {
              b_y = (short)(i1 & 2047);
            }

            if ((c & 2048) != 0) {
              c_x = (short)(c | -2048);
            } else {
              c_x = (short)(c & 2047);
            }
          } else {
            /*  Otherwise, rotate counter clockwise. */
            i1 = (short)(b_y >> c_i);
            if ((i1 & 2048) != 0) {
              i1 = (short)(i1 | -2048);
            } else {
              i1 = (short)(i1 & 2047);
            }

            if ((c_x & 4096) != 0) {
              x = c_x | -4096;
            } else {
              x = c_x & 4095;
            }

            if ((i1 & 4096) != 0) {
              i2 = i1 | -4096;
            } else {
              i2 = i1 & 4095;
            }

            i1 = (short)(x - i2);
            if ((i1 & 4096) != 0) {
              c = (short)(i1 | -4096);
            } else {
              c = (short)(i1 & 4095);
            }

            i1 = (short)(c_x >> c_i);
            if ((i1 & 2048) != 0) {
              i1 = (short)(i1 | -2048);
            } else {
              i1 = (short)(i1 & 2047);
            }

            if ((b_y & 4096) != 0) {
              y = b_y | -4096;
            } else {
              y = b_y & 4095;
            }

            if ((i1 & 4096) != 0) {
              i2 = i1 | -4096;
            } else {
              i2 = i1 & 4095;
            }

            i1 = (short)(y + i2);
            if ((i1 & 4096) != 0) {
              i1 = (short)(i1 | -4096);
            } else {
              i1 = (short)(i1 & 4095);
            }

            if ((i1 & 2048) != 0) {
              b_y = (short)(i1 | -2048);
            } else {
              b_y = (short)(i1 & 2047);
            }

            if ((c & 2048) != 0) {
              c_x = (short)(c | -2048);
            } else {
              c_x = (short)(c & 2047);
            }
          }
        }

        /*  Output xn, yn */
        i1 = (short)(((c_x * 1242) << 7) >> 18);
        if ((i1 & 2048) != 0) {
          Q[b_x_tmp] = (short)(i1 | -2048);
        } else {
          Q[b_x_tmp] = (short)(i1 & 2047);
        }

        i1 = (short)(((b_y * 1242) << 7) >> 18);
        if ((i1 & 2048) != 0) {
          Q[x_tmp] = (short)(i1 | -2048);
        } else {
          Q[x_tmp] = (short)(i1 & 2047);
        }
      }
    }
  }
}

/*
 * File trailer for qr_cordic_opt.c
 *
 * [EOF]
 */
