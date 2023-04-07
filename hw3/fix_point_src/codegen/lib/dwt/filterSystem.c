/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 12:06:50
 */

/* Include Files */
#include "filterSystem.h"
#include "dwt.h"
#include <string.h>

/* Variable Definitions */
static const short iv[7] = { -66, 42, 428, -807, 428, 42, -66 };

static const short iv1[9] = { 39, -24, -113, 386, 873, 386, -113, -24, 39 };

/* Function Definitions */

/*
 * Arguments    : const int xn[512]
 *                int b_yn[512]
 * Return Type  : void
 */
void b_filterSystem(const int xn[512], int b_yn[512])
{
  int x[520];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 512U * sizeof(int));
  x[516] = xn[510];
  x[517] = xn[509];
  x[518] = xn[508];
  x[519] = xn[507];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      b_i = (long long)iv1[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 140737488355328LL) != 0LL) {
        b_i |= -140737488355328LL;
      } else {
        b_i &= 140737488355327LL;
      }

      c += b_i;
      if (c > 140737488355327LL) {
        c = 140737488355327LL;
      } else {
        if (c < -140737488355328LL) {
          c = -140737488355328LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * Arguments    : const int xn[256]
 *                int b_yn[256]
 * Return Type  : void
 */
void c_filterSystem(const int xn[256], int b_yn[256])
{
  int x[262];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 256U * sizeof(int));
  x[259] = xn[254];
  x[260] = xn[253];
  x[261] = xn[252];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&y_data[0], &x[i], 7U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      b_i = (long long)iv[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 70368744177664LL) != 0LL) {
        b_i |= -70368744177664LL;
      } else {
        b_i &= 70368744177663LL;
      }

      c += b_i;
      if (c > 70368744177663LL) {
        c = 70368744177663LL;
      } else {
        if (c < -70368744177664LL) {
          c = -70368744177664LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * Arguments    : const int xn[256]
 *                int b_yn[256]
 * Return Type  : void
 */
void d_filterSystem(const int xn[256], int b_yn[256])
{
  int x[264];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 256U * sizeof(int));
  x[260] = xn[254];
  x[261] = xn[253];
  x[262] = xn[252];
  x[263] = xn[251];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      b_i = (long long)iv1[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 140737488355328LL) != 0LL) {
        b_i |= -140737488355328LL;
      } else {
        b_i &= 140737488355327LL;
      }

      c += b_i;
      if (c > 140737488355327LL) {
        c = 140737488355327LL;
      } else {
        if (c < -140737488355328LL) {
          c = -140737488355328LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * Arguments    : const int xn[128]
 *                int b_yn[128]
 * Return Type  : void
 */
void e_filterSystem(const int xn[128], int b_yn[128])
{
  int x[134];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 128U * sizeof(int));
  x[131] = xn[126];
  x[132] = xn[125];
  x[133] = xn[124];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&y_data[0], &x[i], 7U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      b_i = (long long)iv[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 70368744177664LL) != 0LL) {
        b_i |= -70368744177664LL;
      } else {
        b_i &= 70368744177663LL;
      }

      c += b_i;
      if (c > 70368744177663LL) {
        c = 70368744177663LL;
      } else {
        if (c < -70368744177664LL) {
          c = -70368744177664LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * Arguments    : const int xn[128]
 *                int b_yn[128]
 * Return Type  : void
 */
void f_filterSystem(const int xn[128], int b_yn[128])
{
  int x[136];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 128U * sizeof(int));
  x[132] = xn[126];
  x[133] = xn[125];
  x[134] = xn[124];
  x[135] = xn[123];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 9; loop_ub++) {
      b_i = (long long)iv1[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 140737488355328LL) != 0LL) {
        b_i |= -140737488355328LL;
      } else {
        b_i &= 140737488355327LL;
      }

      c += b_i;
      if (c > 140737488355327LL) {
        c = 140737488355327LL;
      } else {
        if (c < -140737488355328LL) {
          c = -140737488355328LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * Arguments    : const int xn[512]
 *                int b_yn[512]
 * Return Type  : void
 */
void filterSystem(const int xn[512], int b_yn[512])
{
  int x[518];
  int i;
  int y_data[520];
  long long c;
  int loop_ub;
  long long b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 512U * sizeof(int));
  x[515] = xn[510];
  x[516] = xn[509];
  x[517] = xn[508];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&y_data[0], &x[i], 7U * sizeof(int));
    c = 0LL;
    for (loop_ub = 0; loop_ub < 7; loop_ub++) {
      b_i = (long long)iv[loop_ub] * y_data[loop_ub];
      if ((b_i & 8796093022208LL) != 0LL) {
        b_i |= -8796093022208LL;
      } else {
        b_i &= 8796093022207LL;
      }

      if ((b_i & 70368744177664LL) != 0LL) {
        b_i |= -70368744177664LL;
      } else {
        b_i &= 70368744177663LL;
      }

      c += b_i;
      if (c > 70368744177663LL) {
        c = 70368744177663LL;
      } else {
        if (c < -70368744177664LL) {
          c = -70368744177664LL;
        }
      }
    }

    b_i = (c >> 10) + ((c & 512LL) != 0LL);
    if (b_i > 2097151LL) {
      b_i = 2097151LL;
    } else {
      if (b_i < -2097152LL) {
        b_i = -2097152LL;
      }
    }

    b_yn[i] = (int)b_i;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
