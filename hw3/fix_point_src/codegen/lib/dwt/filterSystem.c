/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: filterSystem.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 07-Apr-2023 14:39:31
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
 * Arguments    : const short xn[512]
 *                short b_yn[512]
 * Return Type  : void
 */
void b_filterSystem(const short xn[512], short b_yn[512])
{
  short x[520];
  int i;
  short y_data[520];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 512U * sizeof(short));
  x[516] = xn[510];
  x[517] = xn[509];
  x[518] = xn[508];
  x[519] = xn[507];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(short));
    c = 0;
    for (k = 0; k < 9; k++) {
      b_i = iv1[k] * y_data[k];
      if ((b_i & 1048576) != 0) {
        b_i |= -1048576;
      } else {
        b_i &= 1048575;
      }

      if ((b_i & 16777216) != 0) {
        b_i |= -16777216;
      } else {
        b_i &= 16777215;
      }

      c += b_i;
      if (c > 16777215) {
        c = 16777215;
      } else {
        if (c < -16777216) {
          c = -16777216;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 511) {
      b_i = 511;
    } else {
      if (b_i < -512) {
        b_i = -512;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * Arguments    : const short xn[256]
 *                short b_yn[256]
 * Return Type  : void
 */
void c_filterSystem(const short xn[256], short b_yn[256])
{
  short x[262];
  int i;
  short b0_data[262];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 256U * sizeof(short));
  x[259] = xn[254];
  x[260] = xn[253];
  x[261] = xn[252];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(short));
    c = 0;
    for (k = 0; k < 7; k++) {
      b_i = iv[k] * b0_data[k];
      if ((b_i & 2097152) != 0) {
        b_i |= -2097152;
      } else {
        b_i &= 2097151;
      }

      if ((b_i & 16777216) != 0) {
        b_i |= -16777216;
      } else {
        b_i &= 16777215;
      }

      c += b_i;
      if (c > 16777215) {
        c = 16777215;
      } else {
        if (c < -16777216) {
          c = -16777216;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 1023) {
      b_i = 1023;
    } else {
      if (b_i < -1024) {
        b_i = -1024;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * Arguments    : const short xn[256]
 *                short b_yn[256]
 * Return Type  : void
 */
void d_filterSystem(const short xn[256], short b_yn[256])
{
  short x[264];
  int i;
  short y_data[264];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 256U * sizeof(short));
  x[260] = xn[254];
  x[261] = xn[253];
  x[262] = xn[252];
  x[263] = xn[251];

  /*  Symmetric extension! */
  for (i = 0; i < 256; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(short));
    c = 0;
    for (k = 0; k < 9; k++) {
      b_i = iv1[k] * y_data[k];
      if ((b_i & 2097152) != 0) {
        b_i |= -2097152;
      } else {
        b_i &= 2097151;
      }

      if ((b_i & 33554432) != 0) {
        b_i |= -33554432;
      } else {
        b_i &= 33554431;
      }

      c += b_i;
      if (c > 33554431) {
        c = 33554431;
      } else {
        if (c < -33554432) {
          c = -33554432;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 1023) {
      b_i = 1023;
    } else {
      if (b_i < -1024) {
        b_i = -1024;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * Arguments    : const short xn[128]
 *                short b_yn[128]
 * Return Type  : void
 */
void e_filterSystem(const short xn[128], short b_yn[128])
{
  short x[134];
  int i;
  short b0_data[134];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 128U * sizeof(short));
  x[131] = xn[126];
  x[132] = xn[125];
  x[133] = xn[124];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(short));
    c = 0;
    for (k = 0; k < 7; k++) {
      b_i = iv[k] * b0_data[k];
      if ((b_i & 4194304) != 0) {
        b_i |= -4194304;
      } else {
        b_i &= 4194303;
      }

      if ((b_i & 33554432) != 0) {
        b_i |= -33554432;
      } else {
        b_i &= 33554431;
      }

      c += b_i;
      if (c > 33554431) {
        c = 33554431;
      } else {
        if (c < -33554432) {
          c = -33554432;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 2047) {
      b_i = 2047;
    } else {
      if (b_i < -2048) {
        b_i = -2048;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * Arguments    : const short xn[128]
 *                short b_yn[128]
 * Return Type  : void
 */
void f_filterSystem(const short xn[128], short b_yn[128])
{
  short x[136];
  int i;
  short y_data[136];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[4];
  x[1] = xn[3];
  x[2] = xn[2];
  x[3] = xn[1];
  memcpy(&x[4], &xn[0], 128U * sizeof(short));
  x[132] = xn[126];
  x[133] = xn[125];
  x[134] = xn[124];
  x[135] = xn[123];

  /*  Symmetric extension! */
  for (i = 0; i < 128; i++) {
    memcpy(&y_data[0], &x[i], 9U * sizeof(short));
    c = 0;
    for (k = 0; k < 9; k++) {
      b_i = iv1[k] * y_data[k];
      if ((b_i & 4194304) != 0) {
        b_i |= -4194304;
      } else {
        b_i &= 4194303;
      }

      if ((b_i & 67108864) != 0) {
        b_i |= -67108864;
      } else {
        b_i &= 67108863;
      }

      c += b_i;
      if (c > 67108863) {
        c = 67108863;
      } else {
        if (c < -67108864) {
          c = -67108864;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 2047) {
      b_i = 2047;
    } else {
      if (b_i < -2048) {
        b_i = -2048;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * Arguments    : const short xn[512]
 *                short b_yn[512]
 * Return Type  : void
 */
void filterSystem(const short xn[512], short b_yn[512])
{
  short x[518];
  int i;
  short b0_data[518];
  int c;
  int k;
  int b_i;

  /*  Filter */
  /*  extend size // 2 */
  /*  result */
  x[0] = xn[3];
  x[1] = xn[2];
  x[2] = xn[1];
  memcpy(&x[3], &xn[0], 512U * sizeof(short));
  x[515] = xn[510];
  x[516] = xn[509];
  x[517] = xn[508];

  /*  Symmetric extension! */
  for (i = 0; i < 512; i++) {
    memcpy(&b0_data[0], &x[i], 7U * sizeof(short));
    c = 0;
    for (k = 0; k < 7; k++) {
      b_i = iv[k] * b0_data[k];
      if ((b_i & 1048576) != 0) {
        b_i |= -1048576;
      } else {
        b_i &= 1048575;
      }

      if ((b_i & 8388608) != 0) {
        b_i |= -8388608;
      } else {
        b_i &= 8388607;
      }

      c += b_i;
      if (c > 8388607) {
        c = 8388607;
      } else {
        if (c < -8388608) {
          c = -8388608;
        }
      }
    }

    b_i = (c + 512) >> 10;
    if (b_i > 511) {
      b_i = 511;
    } else {
      if (b_i < -512) {
        b_i = -512;
      }
    }

    b_yn[i] = (short)b_i;
  }
}

/*
 * File trailer for filterSystem.c
 *
 * [EOF]
 */
