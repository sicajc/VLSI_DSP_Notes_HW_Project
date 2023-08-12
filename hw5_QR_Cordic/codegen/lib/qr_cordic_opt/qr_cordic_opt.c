/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: qr_cordic_opt.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 20-Jun-2023 16:58:11
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
  signed char d_data[12];
  int i1;
  int k;
  int M_[16];
  int b_i;
  static const short iv[16] = { 1024, 0, 0, 0, 0, 1024, 0, 0, 0, 0, 1024, 0, 0,
    0, 0, 1024 };

  boolean_T exitg1;
  int x_tmp;
  int b_x_tmp;
  int x;
  int y;
  int j;
  int c_i;
  short b_x;
  long long X;
  short b_y;
  int c_x;
  short i2;
  int i3;
  short c;

  /*  Augmenting the matrix I to the left, updating I alongside with A when performing rotation */
  /*  Turning into fixed point */
  for (i = 0; i < 16; i++) {
    i1 = M[i] << 10;
    if ((i1 & 524288) != 0) {
      M_[i] = i1 | -524288;
    } else {
      M_[i] = i1 & 524287;
    }

    Q[i] = iv[i];
  }

  d_data[0] = 0;
  for (k = 0; k < 4; k++) {
    i = (int)((((double)k + 1.0) + -5.0) / -1.0);
    b_i = 0;
    exitg1 = false;
    while ((!exitg1) && (b_i <= i - 1)) {
      /*  This needed to be replaced with cordic, vectoring mode. */
      /*  Use vector mode to calculate of givens rotation */
      /*  The boundary condition of cordics. While N = 4, the input value is 0. */
      if (4 - b_i == 4) {
        if (k + 1 != 4) {
          /*  The boundary condition for r44, do not rotate it anymore! */
          x_tmp = (k << 2) + 3;
          x = M_[x_tmp];

          /*  Vectoring mode */
          /*  Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively */
          /*  Input:  vector (x,y) rotates it with the angle z */
          /*  Output: Value after rotation (x,y) also the angle of tan(y/x) */
          /*  Goal is trying to nullify y accumulating the angle when rotating. */
          /*  Beware the boundary condition!!! The first qr cordic starts from the N+1 rows. Thus the first operation */
          /*  Is (x,0) -> (r,0)!! */
          /*  Turning into fixed point */
          /*  The partial result during calculation */
          y = 0;

          /*  bin(K); */
          /*  The result of each stage. */
          for (c_i = 0; c_i < 12; c_i++) {
            /*  Z is the current angle, and also the angle I want to shift toward to. */
            X = (long long)x * y;
            if ((X & 549755813888LL) != 0LL) {
              X |= -549755813888LL;
            } else {
              X &= 549755813887LL;
            }

            if ((X > 0LL) || (X >= 0LL)) {
              /*  Since it is at the first dimension, we shoudl shift in a clockwise manner. */
              /*  Since we are trying to obtain the angle, we must first add when we are rotating. */
              i1 = y >> c_i;
              if ((i1 & 524288) != 0) {
                i1 |= -524288;
              } else {
                i1 &= 524287;
              }

              if ((x & 1048576) != 0) {
                c_x = x | -1048576;
              } else {
                c_x = x & 1048575;
              }

              if ((i1 & 1048576) != 0) {
                i1 |= -1048576;
              } else {
                i1 &= 1048575;
              }

              i1 += c_x;
              if ((i1 & 1048576) != 0) {
                c_x = i1 | -1048576;
              } else {
                c_x = i1 & 1048575;
              }

              i1 = x >> c_i;
              if ((i1 & 524288) != 0) {
                i1 |= -524288;
              } else {
                i1 &= 524287;
              }

              if ((y & 1048576) != 0) {
                y |= -1048576;
              } else {
                y &= 1048575;
              }

              if ((i1 & 1048576) != 0) {
                i1 |= -1048576;
              } else {
                i1 &= 1048575;
              }

              i1 = y - i1;
              if ((i1 & 1048576) != 0) {
                y = i1 | -1048576;
              } else {
                y = i1 & 1048575;
              }

              if (y > 524287) {
                y = 524287;
              } else {
                if (y < -524288) {
                  y = -524288;
                }
              }

              if (c_x > 524287) {
                c_x = 524287;
              } else {
                if (c_x < -524288) {
                  c_x = -524288;
                }
              }

              x = c_x;
              i1 = 0;
            } else {
              /*  Otherwise shift in a CounterClockwise(CC) manner */
              i1 = y >> c_i;
              if ((i1 & 524288) != 0) {
                i1 |= -524288;
              } else {
                i1 &= 524287;
              }

              if ((x & 1048576) != 0) {
                c_x = x | -1048576;
              } else {
                c_x = x & 1048575;
              }

              if ((i1 & 1048576) != 0) {
                i1 |= -1048576;
              } else {
                i1 &= 1048575;
              }

              i1 = c_x - i1;
              if ((i1 & 1048576) != 0) {
                c_x = i1 | -1048576;
              } else {
                c_x = i1 & 1048575;
              }

              i1 = x >> c_i;
              if ((i1 & 524288) != 0) {
                i1 |= -524288;
              } else {
                i1 &= 524287;
              }

              if ((y & 1048576) != 0) {
                y |= -1048576;
              } else {
                y &= 1048575;
              }

              if ((i1 & 1048576) != 0) {
                i1 |= -1048576;
              } else {
                i1 &= 1048575;
              }

              i1 += y;
              if ((i1 & 1048576) != 0) {
                y = i1 | -1048576;
              } else {
                y = i1 & 1048575;
              }

              if (y > 524287) {
                y = 524287;
              } else {
                if (y < -524288) {
                  y = -524288;
                }
              }

              if (c_x > 524287) {
                c_x = 524287;
              } else {
                if (c_x < -524288) {
                  c_x = -524288;
                }
              }

              x = c_x;
              i1 = 1;
            }

            d_data[c_i] = (signed char)i1;
          }

          X = x * 621;
          if ((X & 549755813888LL) != 0LL) {
            X |= -549755813888LL;
          } else {
            X &= 549755813887LL;
          }

          X >>= 10;
          if (X > 524287LL) {
            X = 524287LL;
          } else {
            if (X < -524288LL) {
              X = -524288LL;
            }
          }

          M_[x_tmp] = (int)X;
        }
      } else {
        x_tmp = (k << 2) - b_i;
        b_x_tmp = x_tmp + 3;
        x = M_[b_x_tmp];
        x_tmp += 4;
        y = M_[x_tmp];

        /*  Vectoring mode */
        /*  Description: Vectoring mode uses linear rotation s.t. y approach to 0 iteratively */
        /*  Input:  vector (x,y) rotates it with the angle z */
        /*  Output: Value after rotation (x,y) also the angle of tan(y/x) */
        /*  Goal is trying to nullify y accumulating the angle when rotating. */
        /*  Beware the boundary condition!!! The first qr cordic starts from the N+1 rows. Thus the first operation */
        /*  Is (x,0) -> (r,0)!! */
        /*  Turning into fixed point */
        /*  The partial result during calculation */
        /*  bin(K); */
        /*  The result of each stage. */
        for (c_i = 0; c_i < 12; c_i++) {
          /*  Z is the current angle, and also the angle I want to shift toward to. */
          X = (long long)x * y;
          if ((X & 549755813888LL) != 0LL) {
            X |= -549755813888LL;
          } else {
            X &= 549755813887LL;
          }

          if ((X > 0LL) || (X >= 0LL)) {
            /*  Since it is at the first dimension, we shoudl shift in a clockwise manner. */
            /*  Since we are trying to obtain the angle, we must first add when we are rotating. */
            i1 = y >> c_i;
            if ((i1 & 524288) != 0) {
              i1 |= -524288;
            } else {
              i1 &= 524287;
            }

            if ((x & 1048576) != 0) {
              c_x = x | -1048576;
            } else {
              c_x = x & 1048575;
            }

            if ((i1 & 1048576) != 0) {
              i1 |= -1048576;
            } else {
              i1 &= 1048575;
            }

            i1 += c_x;
            if ((i1 & 1048576) != 0) {
              c_x = i1 | -1048576;
            } else {
              c_x = i1 & 1048575;
            }

            i1 = x >> c_i;
            if ((i1 & 524288) != 0) {
              i1 |= -524288;
            } else {
              i1 &= 524287;
            }

            if ((y & 1048576) != 0) {
              y |= -1048576;
            } else {
              y &= 1048575;
            }

            if ((i1 & 1048576) != 0) {
              i1 |= -1048576;
            } else {
              i1 &= 1048575;
            }

            i1 = y - i1;
            if ((i1 & 1048576) != 0) {
              y = i1 | -1048576;
            } else {
              y = i1 & 1048575;
            }

            if (y > 524287) {
              y = 524287;
            } else {
              if (y < -524288) {
                y = -524288;
              }
            }

            if (c_x > 524287) {
              c_x = 524287;
            } else {
              if (c_x < -524288) {
                c_x = -524288;
              }
            }

            x = c_x;
            i1 = 0;
          } else {
            /*  Otherwise shift in a CounterClockwise(CC) manner */
            i1 = y >> c_i;
            if ((i1 & 524288) != 0) {
              i1 |= -524288;
            } else {
              i1 &= 524287;
            }

            if ((x & 1048576) != 0) {
              c_x = x | -1048576;
            } else {
              c_x = x & 1048575;
            }

            if ((i1 & 1048576) != 0) {
              i1 |= -1048576;
            } else {
              i1 &= 1048575;
            }

            i1 = c_x - i1;
            if ((i1 & 1048576) != 0) {
              c_x = i1 | -1048576;
            } else {
              c_x = i1 & 1048575;
            }

            i1 = x >> c_i;
            if ((i1 & 524288) != 0) {
              i1 |= -524288;
            } else {
              i1 &= 524287;
            }

            if ((y & 1048576) != 0) {
              y |= -1048576;
            } else {
              y &= 1048575;
            }

            if ((i1 & 1048576) != 0) {
              i1 |= -1048576;
            } else {
              i1 &= 1048575;
            }

            i1 += y;
            if ((i1 & 1048576) != 0) {
              y = i1 | -1048576;
            } else {
              y = i1 & 1048575;
            }

            if (y > 524287) {
              y = 524287;
            } else {
              if (y < -524288) {
                y = -524288;
              }
            }

            if (c_x > 524287) {
              c_x = 524287;
            } else {
              if (c_x < -524288) {
                c_x = -524288;
              }
            }

            x = c_x;
            i1 = 1;
          }

          d_data[c_i] = (signed char)i1;
        }

        X = x * 621;
        if ((X & 549755813888LL) != 0LL) {
          X |= -549755813888LL;
        } else {
          X &= 549755813887LL;
        }

        X >>= 10;
        if (X > 524287LL) {
          X = 524287LL;
        } else {
          if (X < -524288LL) {
            X = -524288LL;
          }
        }

        M_[b_x_tmp] = (int)X;

        /*  fprintf('Entry: (%d,%d)',i,k); */
        M_[x_tmp] = 0;
      }

      /*  disp("After Vector mode"); */
      /*  M_ */
      /*  fprintf('Vector Mode:\n theta = %f , i = %d  \n',theta,i); */
      i1 = 2 - k;
      for (j = 0; j <= i1; j++) {
        x_tmp = (k + j) + 1;

        /*  For R */
        /*  This needed to be replaced with cordic, rotation mode */
        /*  The boundary conditions. */
        if (4 - b_i == 4) {
          if (k + 1 != 4) {
            x_tmp = (x_tmp << 2) + 3;
            x = M_[x_tmp];

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
            y = 0;

            /*  bin(K) */
            /*  The result of each stage. */
            for (c_i = 0; c_i < 12; c_i++) {
              /*  Z is the current angle, and also the angle I want to shift toward to. */
              if (d_data[c_i] == 0) {
                /*  If angle is above 0, I would like to rotate in a clockwise manner */
                i3 = y >> c_i;
                if ((i3 & 524288) != 0) {
                  i3 |= -524288;
                } else {
                  i3 &= 524287;
                }

                if ((x & 1048576) != 0) {
                  c_x = x | -1048576;
                } else {
                  c_x = x & 1048575;
                }

                if ((i3 & 1048576) != 0) {
                  i3 |= -1048576;
                } else {
                  i3 &= 1048575;
                }

                i3 += c_x;
                if ((i3 & 1048576) != 0) {
                  c_x = i3 | -1048576;
                } else {
                  c_x = i3 & 1048575;
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
                  y = i3 | -1048576;
                } else {
                  y = i3 & 1048575;
                }

                if (y > 524287) {
                  y = 524287;
                } else {
                  if (y < -524288) {
                    y = -524288;
                  }
                }

                if (c_x > 524287) {
                  c_x = 524287;
                } else {
                  if (c_x < -524288) {
                    c_x = -524288;
                  }
                }

                x = c_x;
              } else {
                /*  Otherwise, rotate counter clockwise. */
                i3 = y >> c_i;
                if ((i3 & 524288) != 0) {
                  i3 |= -524288;
                } else {
                  i3 &= 524287;
                }

                if ((x & 1048576) != 0) {
                  c_x = x | -1048576;
                } else {
                  c_x = x & 1048575;
                }

                if ((i3 & 1048576) != 0) {
                  i3 |= -1048576;
                } else {
                  i3 &= 1048575;
                }

                i3 = c_x - i3;
                if ((i3 & 1048576) != 0) {
                  c_x = i3 | -1048576;
                } else {
                  c_x = i3 & 1048575;
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
                  y = i3 | -1048576;
                } else {
                  y = i3 & 1048575;
                }

                if (y > 524287) {
                  y = 524287;
                } else {
                  if (y < -524288) {
                    y = -524288;
                  }
                }

                if (c_x > 524287) {
                  c_x = 524287;
                } else {
                  if (c_x < -524288) {
                    c_x = -524288;
                  }
                }

                x = c_x;
              }
            }

            /*  temp = 0; */
            /*  temp = fi(temp,1,40,20); */
            /*  disp("x * K is"); */
            /*  x*K */
            /*  bin(temp) */
            /*  bin(x*K) */
            /*  Output xn, yn */
            X = x * 621;
            if ((X & 549755813888LL) != 0LL) {
              X |= -549755813888LL;
            } else {
              X &= 549755813887LL;
            }

            X >>= 10;
            if (X > 524287LL) {
              X = 524287LL;
            } else {
              if (X < -524288LL) {
                X = -524288LL;
              }
            }

            M_[x_tmp] = (int)X;

            /*  bin(x_result); */
            /*  bin(y_result); */
          }
        } else {
          x_tmp = (x_tmp << 2) - b_i;
          b_x_tmp = x_tmp + 3;
          x = M_[b_x_tmp];
          x_tmp += 4;
          y = M_[x_tmp];

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
          /*  bin(K) */
          /*  The result of each stage. */
          for (c_i = 0; c_i < 12; c_i++) {
            /*  Z is the current angle, and also the angle I want to shift toward to. */
            if (d_data[c_i] == 0) {
              /*  If angle is above 0, I would like to rotate in a clockwise manner */
              i3 = y >> c_i;
              if ((i3 & 524288) != 0) {
                i3 |= -524288;
              } else {
                i3 &= 524287;
              }

              if ((x & 1048576) != 0) {
                c_x = x | -1048576;
              } else {
                c_x = x & 1048575;
              }

              if ((i3 & 1048576) != 0) {
                i3 |= -1048576;
              } else {
                i3 &= 1048575;
              }

              i3 += c_x;
              if ((i3 & 1048576) != 0) {
                c_x = i3 | -1048576;
              } else {
                c_x = i3 & 1048575;
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
                y = i3 | -1048576;
              } else {
                y = i3 & 1048575;
              }

              if (y > 524287) {
                y = 524287;
              } else {
                if (y < -524288) {
                  y = -524288;
                }
              }

              if (c_x > 524287) {
                c_x = 524287;
              } else {
                if (c_x < -524288) {
                  c_x = -524288;
                }
              }

              x = c_x;
            } else {
              /*  Otherwise, rotate counter clockwise. */
              i3 = y >> c_i;
              if ((i3 & 524288) != 0) {
                i3 |= -524288;
              } else {
                i3 &= 524287;
              }

              if ((x & 1048576) != 0) {
                c_x = x | -1048576;
              } else {
                c_x = x & 1048575;
              }

              if ((i3 & 1048576) != 0) {
                i3 |= -1048576;
              } else {
                i3 &= 1048575;
              }

              i3 = c_x - i3;
              if ((i3 & 1048576) != 0) {
                c_x = i3 | -1048576;
              } else {
                c_x = i3 & 1048575;
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
                y = i3 | -1048576;
              } else {
                y = i3 & 1048575;
              }

              if (y > 524287) {
                y = 524287;
              } else {
                if (y < -524288) {
                  y = -524288;
                }
              }

              if (c_x > 524287) {
                c_x = 524287;
              } else {
                if (c_x < -524288) {
                  c_x = -524288;
                }
              }

              x = c_x;
            }
          }

          /*  temp = 0; */
          /*  temp = fi(temp,1,40,20); */
          /*  disp("x * K is"); */
          /*  x*K */
          /*  bin(temp) */
          /*  bin(x*K) */
          /*  Output xn, yn */
          X = x * 621;
          if ((X & 549755813888LL) != 0LL) {
            X |= -549755813888LL;
          } else {
            X &= 549755813887LL;
          }

          X >>= 10;
          if (X > 524287LL) {
            X = 524287LL;
          } else {
            if (X < -524288LL) {
              X = -524288LL;
            }
          }

          M_[b_x_tmp] = (int)X;

          /*  bin(x_result); */
          X = y * 621;
          if ((X & 549755813888LL) != 0LL) {
            X |= -549755813888LL;
          } else {
            X &= 549755813887LL;
          }

          X >>= 10;
          if (X > 524287LL) {
            X = 524287LL;
          } else {
            if (X < -524288LL) {
              X = -524288LL;
            }
          }

          M_[x_tmp] = (int)X;

          /*  bin(y_result); */
          /*  fprintf('Entry: (%d,%d)',i,j); */
          /*  disp("Rotation mode Result x:"); */
          /*  tmp1 */
          /*  bin(tmp1) */
          /*  disp("Rotation mode Result y:"); */
          /*  tmp2 */
          /*  bin(tmp2) */
        }

        /*  [tmp1, tmp2] = cordic_rotation_mode_opt(M_(i,j), M_( i+1,j ), d, iters_num,T); */
        /*  fprintf('Rotation Mode:\n x = %f , y = %f , j = %d  \n',tmp1,tmp2,j); */
      }

      /*  disp("After Rotations"); */
      /*  M_; */
      if (k + 1 == 4) {
        exitg1 = true;
      } else {
        for (j = 0; j < 4; j++) {
          if (4 - b_i == 4) {
            x_tmp = (j << 2) + 3;
            b_x = Q[x_tmp];

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
            b_y = 0;

            /*  bin(K) */
            /*  The result of each stage. */
            for (c_i = 0; c_i < 12; c_i++) {
              /*  Z is the current angle, and also the angle I want to shift toward to. */
              if (d_data[c_i] == 0) {
                /*  If angle is above 0, I would like to rotate in a clockwise manner */
                i2 = (short)(b_y >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_x & 4096) != 0) {
                  x = b_x | -4096;
                } else {
                  x = b_x & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(x + i1);
                if ((i2 & 4096) != 0) {
                  c = (short)(i2 | -4096);
                } else {
                  c = (short)(i2 & 4095);
                }

                i2 = (short)(b_x >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_y & 4096) != 0) {
                  y = b_y | -4096;
                } else {
                  y = b_y & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(y - i1);
                if ((i2 & 4096) != 0) {
                  b_y = (short)(i2 | -4096);
                } else {
                  b_y = (short)(i2 & 4095);
                }

                if (b_y > 2047) {
                  b_y = 2047;
                } else {
                  if (b_y < -2048) {
                    b_y = -2048;
                  }
                }

                if (c > 2047) {
                  c = 2047;
                } else {
                  if (c < -2048) {
                    c = -2048;
                  }
                }

                b_x = c;
              } else {
                /*  Otherwise, rotate counter clockwise. */
                i2 = (short)(b_y >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_x & 4096) != 0) {
                  x = b_x | -4096;
                } else {
                  x = b_x & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(x - i1);
                if ((i2 & 4096) != 0) {
                  c = (short)(i2 | -4096);
                } else {
                  c = (short)(i2 & 4095);
                }

                i2 = (short)(b_x >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_y & 4096) != 0) {
                  y = b_y | -4096;
                } else {
                  y = b_y & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(y + i1);
                if ((i2 & 4096) != 0) {
                  b_y = (short)(i2 | -4096);
                } else {
                  b_y = (short)(i2 & 4095);
                }

                if (b_y > 2047) {
                  b_y = 2047;
                } else {
                  if (b_y < -2048) {
                    b_y = -2048;
                  }
                }

                if (c > 2047) {
                  c = 2047;
                } else {
                  if (c < -2048) {
                    c = -2048;
                  }
                }

                b_x = c;
              }
            }

            /*  temp = 0; */
            /*  temp = fi(temp,1,40,20); */
            /*  disp("x * K is"); */
            /*  x*K */
            /*  bin(temp) */
            /*  bin(x*K) */
            /*  Output xn, yn */
            i1 = b_x * 621;
            if ((i1 & 8388608) != 0) {
              i1 |= -8388608;
            } else {
              i1 &= 8388607;
            }

            i1 >>= 10;
            if (i1 > 2047) {
              i1 = 2047;
            } else {
              if (i1 < -2048) {
                i1 = -2048;
              }
            }

            Q[x_tmp] = (short)i1;

            /*  bin(x_result); */
            /*  bin(y_result); */
            /*  tmp1 */
            /*  bin(tmp1) */
          } else {
            x_tmp = (j << 2) - b_i;
            b_x_tmp = x_tmp + 3;
            b_x = Q[b_x_tmp];
            x_tmp += 4;
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
            /*  bin(K) */
            /*  The result of each stage. */
            for (c_i = 0; c_i < 12; c_i++) {
              /*  Z is the current angle, and also the angle I want to shift toward to. */
              if (d_data[c_i] == 0) {
                /*  If angle is above 0, I would like to rotate in a clockwise manner */
                i2 = (short)(b_y >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_x & 4096) != 0) {
                  x = b_x | -4096;
                } else {
                  x = b_x & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(x + i1);
                if ((i2 & 4096) != 0) {
                  c = (short)(i2 | -4096);
                } else {
                  c = (short)(i2 & 4095);
                }

                i2 = (short)(b_x >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_y & 4096) != 0) {
                  y = b_y | -4096;
                } else {
                  y = b_y & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(y - i1);
                if ((i2 & 4096) != 0) {
                  b_y = (short)(i2 | -4096);
                } else {
                  b_y = (short)(i2 & 4095);
                }

                if (b_y > 2047) {
                  b_y = 2047;
                } else {
                  if (b_y < -2048) {
                    b_y = -2048;
                  }
                }

                if (c > 2047) {
                  c = 2047;
                } else {
                  if (c < -2048) {
                    c = -2048;
                  }
                }

                b_x = c;
              } else {
                /*  Otherwise, rotate counter clockwise. */
                i2 = (short)(b_y >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_x & 4096) != 0) {
                  x = b_x | -4096;
                } else {
                  x = b_x & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(x - i1);
                if ((i2 & 4096) != 0) {
                  c = (short)(i2 | -4096);
                } else {
                  c = (short)(i2 & 4095);
                }

                i2 = (short)(b_x >> c_i);
                if ((i2 & 2048) != 0) {
                  i2 = (short)(i2 | -2048);
                } else {
                  i2 = (short)(i2 & 2047);
                }

                if ((b_y & 4096) != 0) {
                  y = b_y | -4096;
                } else {
                  y = b_y & 4095;
                }

                if ((i2 & 4096) != 0) {
                  i1 = i2 | -4096;
                } else {
                  i1 = i2 & 4095;
                }

                i2 = (short)(y + i1);
                if ((i2 & 4096) != 0) {
                  b_y = (short)(i2 | -4096);
                } else {
                  b_y = (short)(i2 & 4095);
                }

                if (b_y > 2047) {
                  b_y = 2047;
                } else {
                  if (b_y < -2048) {
                    b_y = -2048;
                  }
                }

                if (c > 2047) {
                  c = 2047;
                } else {
                  if (c < -2048) {
                    c = -2048;
                  }
                }

                b_x = c;
              }
            }

            /*  temp = 0; */
            /*  temp = fi(temp,1,40,20); */
            /*  disp("x * K is"); */
            /*  x*K */
            /*  bin(temp) */
            /*  bin(x*K) */
            /*  Output xn, yn */
            i1 = b_x * 621;
            if ((i1 & 8388608) != 0) {
              i1 |= -8388608;
            } else {
              i1 &= 8388607;
            }

            i1 >>= 10;
            if (i1 > 2047) {
              i1 = 2047;
            } else {
              if (i1 < -2048) {
                i1 = -2048;
              }
            }

            Q[b_x_tmp] = (short)i1;

            /*  bin(x_result); */
            i1 = b_y * 621;
            if ((i1 & 8388608) != 0) {
              i1 |= -8388608;
            } else {
              i1 &= 8388607;
            }

            i1 >>= 10;
            if (i1 > 2047) {
              i1 = 2047;
            } else {
              if (i1 < -2048) {
                i1 = -2048;
              }
            }

            Q[x_tmp] = (short)i1;

            /*  bin(y_result); */
          }

          /*  For Q, after calculation, take its transpose to get the correct Q, same for this portion. */
          /*  [tmp1, tmp2] = cordic_rotation_mode_opt( Q(i-1,j), Q(i,j), d, iters_num,S); */
        }

        b_i++;
      }
    }
  }

  for (i = 0; i < 16; i++) {
    i1 = M_[i] >> 7;
    if (i1 > 2047) {
      i1 = 2047;
    } else {
      if (i1 < -2048) {
        i1 = -2048;
      }
    }

    R[i] = (short)i1;
  }
}

/*
 * File trailer for qr_cordic_opt.c
 *
 * [EOF]
 */
