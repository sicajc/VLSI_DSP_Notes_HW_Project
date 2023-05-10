/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qr_cordic_opt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 10-May-2023 19:30:40
 */

/* Include Files */
#include "qr_cordic_opt.h"

/* Function Definitions */

/*
 * Algorithm from VLSI DSP lecture notes, 5-54, modify it using CORDIC algorithm
 * Arguments    : short M[16]
 *                short Q[16]
 *                short R[16]
 * Return Type  : void
 */
void qr_cordic_opt(short M[16], short Q[16], short R[16])
{
  int i;
  int k;
  static const short iv[16] = { 512, 0, 0, 0, 0, 512, 0, 0, 0, 0, 512, 0, 0, 0,
    0, 512 };

  int b_i;
  int x_tmp;
  short b_Q[16];
  short x;
  short y;
  int i1;
  int j;
  int b_x_tmp;
  short i2;
  int y_tmp;
  int b_x;
  short c;
  double d[12];
  int i3;

  /*  Augmenting the matrix I to the left, updating I alongside with A when performing rotation */
  /*  Turning into fixed point */
  for (i = 0; i < 16; i++) {
    Q[i] = iv[i];
  }

  for (k = 0; k < 4; k++) {
    i = (int)(((((double)k + 1.0) + 1.0) + -5.0) / -1.0);
    for (b_i = 0; b_i < i; b_i++) {
      /*  This needed to be replaced with cordic, vectoring mode. */
      /*  Use vector mode to calculate of givens rotation */
      x_tmp = (k << 2) - b_i;
      x = M[x_tmp + 2];
      y = M[x_tmp + 3];

      /*  Vectoring mode */
      /*  Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively */
      /*  Input:  vector (x,y) rotates it with the angle z */
      /*  Output: Value after rotation (x,y) also the angle of tan(y/x) */
      /*  Goal is trying to nullify y accumulating the angle when rotating. */
      /*  Turning into fixed point */
      for (x_tmp = 0; x_tmp < 12; x_tmp++) {
        /*  Z is the current angle, and also the angle I want to shift toward to. */
        i1 = x * y;
        if ((i1 & 8388608) != 0) {
          i1 |= -8388608;
        } else {
          i1 &= 8388607;
        }

        if (i1 > 0) {
          /*  Since it is at the first dimension, we shoudl shift in a clockwise manner. */
          /*  Since we are trying to obtain the angle, we must first add when we are rotating. */
          i2 = (short)(y >> x_tmp);
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
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(b_x + i1);
          if ((i2 & 4096) != 0) {
            c = (short)(i2 | -4096);
          } else {
            c = (short)(i2 & 4095);
          }

          i2 = (short)(x >> x_tmp);
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
          d[x_tmp] = 0.0;
        } else {
          /*  Otherwise shift in a CounterClockwise(CC) manner */
          i2 = (short)(y >> x_tmp);
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
            i1 = i2 | -4096;
          } else {
            i1 = i2 & 4095;
          }

          i2 = (short)(b_x - i1);
          if ((i2 & 4096) != 0) {
            c = (short)(i2 | -4096);
          } else {
            c = (short)(i2 & 4095);
          }

          i2 = (short)(x >> x_tmp);
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
          d[x_tmp] = 1.0;
        }
      }

      /*  fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i); */
      i1 = 3 - k;
      for (j = 0; j <= i1; j++) {
        /*  For R */
        /*  This needed to be replaced with cordic, rotation mode */
        x_tmp = ((k + j) << 2) - b_i;
        b_x_tmp = x_tmp + 2;
        x = M[b_x_tmp];
        y_tmp = x_tmp + 3;
        y = M[y_tmp];

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
        for (x_tmp = 0; x_tmp < 12; x_tmp++) {
          /*  Z is the current angle, and also the angle I want to shift toward to. */
          if (d[x_tmp] == 0.0) {
            /*  If angle is above 0, I would like to rotate in a clockwise manner */
            i2 = (short)(y >> x_tmp);
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

            i2 = (short)(x >> x_tmp);
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
              i3 = i2 | -4096;
            } else {
              i3 = i2 & 4095;
            }

            i2 = (short)(b_x - i3);
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
          } else {
            /*  Otherwise, rotate counter clockwise. */
            i2 = (short)(y >> x_tmp);
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

            i2 = (short)(x >> x_tmp);
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
              i3 = i2 | -4096;
            } else {
              i3 = i2 & 4095;
            }

            i2 = (short)(b_x + i3);
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
          }
        }

        /*  fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j); */
        x_tmp = x * 311;
        if ((x_tmp & 8388608) != 0) {
          x_tmp |= -8388608;
        } else {
          x_tmp &= 8388607;
        }

        x_tmp = (x_tmp + 256) >> 9;
        if (x_tmp > 2047) {
          x_tmp = 2047;
        } else {
          if (x_tmp < -2048) {
            x_tmp = -2048;
          }
        }

        M[b_x_tmp] = (short)x_tmp;
        x_tmp = y * 311;
        if ((x_tmp & 8388608) != 0) {
          x_tmp |= -8388608;
        } else {
          x_tmp &= 8388607;
        }

        x_tmp = (x_tmp + 256) >> 9;
        if (x_tmp > 2047) {
          x_tmp = 2047;
        } else {
          if (x_tmp < -2048) {
            x_tmp = -2048;
          }
        }

        M[y_tmp] = (short)x_tmp;
      }

      for (j = 0; j < 4; j++) {
        /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
        x_tmp = (j << 2) - b_i;
        b_x_tmp = x_tmp + 2;
        x = Q[b_x_tmp];
        y_tmp = x_tmp + 3;
        y = Q[y_tmp];

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
        for (x_tmp = 0; x_tmp < 12; x_tmp++) {
          /*  Z is the current angle, and also the angle I want to shift toward to. */
          if (d[x_tmp] == 0.0) {
            /*  If angle is above 0, I would like to rotate in a clockwise manner */
            i2 = (short)(y >> x_tmp);
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
              i1 = i2 | -4096;
            } else {
              i1 = i2 & 4095;
            }

            i2 = (short)(b_x + i1);
            if ((i2 & 4096) != 0) {
              c = (short)(i2 | -4096);
            } else {
              c = (short)(i2 & 4095);
            }

            i2 = (short)(x >> x_tmp);
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
          } else {
            /*  Otherwise, rotate counter clockwise. */
            i2 = (short)(y >> x_tmp);
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
              i1 = i2 | -4096;
            } else {
              i1 = i2 & 4095;
            }

            i2 = (short)(b_x - i1);
            if ((i2 & 4096) != 0) {
              c = (short)(i2 | -4096);
            } else {
              c = (short)(i2 & 4095);
            }

            i2 = (short)(x >> x_tmp);
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
          }
        }

        i1 = x * 311;
        if ((i1 & 8388608) != 0) {
          i1 |= -8388608;
        } else {
          i1 &= 8388607;
        }

        i1 = (i1 + 256) >> 9;
        if (i1 > 2047) {
          i1 = 2047;
        } else {
          if (i1 < -2048) {
            i1 = -2048;
          }
        }

        Q[b_x_tmp] = (short)i1;
        i1 = y * 311;
        if ((i1 & 8388608) != 0) {
          i1 |= -8388608;
        } else {
          i1 &= 8388607;
        }

        i1 = (i1 + 256) >> 9;
        if (i1 > 2047) {
          i1 = 2047;
        } else {
          if (i1 < -2048) {
            i1 = -2048;
          }
        }

        Q[y_tmp] = (short)i1;
      }
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
 * File trailer for qr_cordic_opt.c
 *
 * [EOF]
 */
