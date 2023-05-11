/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_qr_cordic_opt_api.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 11-May-2023 20:41:05
 */

/* Include Files */
#include "_coder_qr_cordic_opt_api.h"
#include "_coder_qr_cordic_opt_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
static const mxArray *eml_mx;
static const mxArray *b_eml_mx;
static const mxArray *c_eml_mx;
static const mxArray *d_eml_mx;
static const mxArray *e_eml_mx;
static const mxArray *f_eml_mx;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131594U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "qr_cordic_opt",                     /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

static emlrtMCInfo emlrtMCI = { -1,    /* lineNo */
  -1,                                  /* colNo */
  "",                                  /* fName */
  ""                                   /* pName */
};

static const char * sv[4] = { "x_partial", "y_partial", "x_output", "y_output" };

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, int8_T y[16]);
static const mxArray *b_emlrt_marshallOut(const int16_T u[16]);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *T, const
  char_T *identifier);
static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp, const int16_T u
  [16]);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *M, const
  char_T *identifier, int8_T y[16]);
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const int16_T u[16]);
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *fimath(const emlrtStack *sp, const char * b, const char
  * c, const char * d, const char * e, const char * f, const char * g, const
  char * h, const char * i, const char * j, const char * k, const char * l,
  const char * m, const char * n, real_T o, const char * p, real_T q, const char
  * r, real_T s, const char * t, real_T u, const char * v, real_T w, const char *
  x, real_T y, const char * ab, real_T bb, const char * cb, real_T db, const
  char * eb, real_T fb, const char * gb, real_T hb, const char * ib, real_T jb,
  const char * kb, real_T lb, const char * mb, boolean_T nb, const char * ob,
  real_T pb, const char * qb, real_T rb, emlrtMCInfo *location);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *S, const
  char_T *identifier);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void j_emlrt_marshallIn(const mxArray *src, int8_T ret[16]);
static void k_emlrt_marshallIn(const mxArray *src);
static const mxArray *numerictype(const emlrtStack *sp, const char * b, real_T c,
  const char * d, real_T e, const char * f, real_T g, const char * h, real_T i,
  const char * j, real_T k, emlrtMCInfo *location);
static void qr_cordic_opt_once(const emlrtStack *sp);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                int8_T y[16]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, int8_T y[16])
{
  static const int32_T dims[2] = { 4, 4 };

  emlrtCheckFiR2012b(sp, parentId, u, false, 2U, dims, eml_mx, b_eml_mx);
  j_emlrt_marshallIn(emlrtAlias(u), y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const int16_T u[16]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const int16_T u[16])
{
  const mxArray *y;
  const mxArray *m;
  static const int32_T iv[2] = { 4, 4 };

  int16_T *pData;
  int32_T i;
  int32_T b_i;
  int32_T i1;
  y = NULL;
  m = emlrtCreateNumericArray(2, &iv[0], mxINT16_CLASS, mxREAL);
  pData = (int16_T *)emlrtMxGetData(m);
  i = 0;
  for (b_i = 0; b_i < 4; b_i++) {
    i1 = b_i << 2;
    pData[i] = u[i1];
    i++;
    pData[i] = u[i1 + 1];
    i++;
    pData[i] = u[i1 + 2];
    i++;
    pData[i] = u[i1 + 3];
    i++;
  }

  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *T
 *                const char_T *identifier
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *T, const
  char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(T), &thisId);
  emlrtDestroyArray(&T);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const int16_T u[16]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const emlrtStack *sp, const int16_T u
  [16])
{
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateFIR2013b(sp, c_eml_mx, e_eml_mx, "simulinkarray",
    b_emlrt_marshallOut(u), true, false));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  emlrtMsgIdentifier thisId;
  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 4, sv, 0U, &dims);
  thisId.fIdentifier = "x_partial";
  e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0, "x_partial")),
                     &thisId);
  thisId.fIdentifier = "y_partial";
  e_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1, "y_partial")),
                     &thisId);
  thisId.fIdentifier = "x_output";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2, "x_output")),
                     &thisId);
  thisId.fIdentifier = "y_output";
  f_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3, "y_output")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims[2] = { 0, 0 };

  emlrtCheckFiR2012b(sp, parentId, u, false, 2U, dims, c_eml_mx, d_eml_mx);
  k_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *M
 *                const char_T *identifier
 *                int8_T y[16]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *M, const
  char_T *identifier, int8_T y[16])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(M), &thisId, y);
  emlrtDestroyArray(&M);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const int16_T u[16]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const emlrtStack *sp, const int16_T u[16])
{
  const mxArray *y;
  y = NULL;
  emlrtAssign(&y, emlrtCreateFIR2013b(sp, c_eml_mx, f_eml_mx, "simulinkarray",
    b_emlrt_marshallOut(u), true, false));
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims[2] = { 0, 0 };

  emlrtCheckFiR2012b(sp, parentId, u, false, 2U, dims, c_eml_mx, e_eml_mx);
  k_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char * b
 *                const char * c
 *                const char * d
 *                const char * e
 *                const char * f
 *                const char * g
 *                const char * h
 *                const char * i
 *                const char * j
 *                const char * k
 *                const char * l
 *                const char * m
 *                const char * n
 *                real_T o
 *                const char * p
 *                real_T q
 *                const char * r
 *                real_T s
 *                const char * t
 *                real_T u
 *                const char * v
 *                real_T w
 *                const char * x
 *                real_T y
 *                const char * ab
 *                real_T bb
 *                const char * cb
 *                real_T db
 *                const char * eb
 *                real_T fb
 *                const char * gb
 *                real_T hb
 *                const char * ib
 *                real_T jb
 *                const char * kb
 *                real_T lb
 *                const char * mb
 *                boolean_T nb
 *                const char * ob
 *                real_T pb
 *                const char * qb
 *                real_T rb
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *fimath(const emlrtStack *sp, const char * b, const char
  * c, const char * d, const char * e, const char * f, const char * g, const
  char * h, const char * i, const char * j, const char * k, const char * l,
  const char * m, const char * n, real_T o, const char * p, real_T q, const char
  * r, real_T s, const char * t, real_T u, const char * v, real_T w, const char *
  x, real_T y, const char * ab, real_T bb, const char * cb, real_T db, const
  char * eb, real_T fb, const char * gb, real_T hb, const char * ib, real_T jb,
  const char * kb, real_T lb, const char * mb, boolean_T nb, const char * ob,
  real_T pb, const char * qb, real_T rb, emlrtMCInfo *location)
{
  const mxArray *pArrays[42];
  const mxArray *b_m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateString(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateString(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateString(g);
  pArrays[6] = emlrtCreateString(h);
  pArrays[7] = emlrtCreateString(i);
  pArrays[8] = emlrtCreateString(j);
  pArrays[9] = emlrtCreateString(k);
  pArrays[10] = emlrtCreateString(l);
  pArrays[11] = emlrtCreateString(m);
  pArrays[12] = emlrtCreateString(n);
  pArrays[13] = emlrtCreateDoubleScalar(o);
  pArrays[14] = emlrtCreateString(p);
  pArrays[15] = emlrtCreateDoubleScalar(q);
  pArrays[16] = emlrtCreateString(r);
  pArrays[17] = emlrtCreateDoubleScalar(s);
  pArrays[18] = emlrtCreateString(t);
  pArrays[19] = emlrtCreateDoubleScalar(u);
  pArrays[20] = emlrtCreateString(v);
  pArrays[21] = emlrtCreateDoubleScalar(w);
  pArrays[22] = emlrtCreateString(x);
  pArrays[23] = emlrtCreateDoubleScalar(y);
  pArrays[24] = emlrtCreateString(ab);
  pArrays[25] = emlrtCreateDoubleScalar(bb);
  pArrays[26] = emlrtCreateString(cb);
  pArrays[27] = emlrtCreateDoubleScalar(db);
  pArrays[28] = emlrtCreateString(eb);
  pArrays[29] = emlrtCreateDoubleScalar(fb);
  pArrays[30] = emlrtCreateString(gb);
  pArrays[31] = emlrtCreateDoubleScalar(hb);
  pArrays[32] = emlrtCreateString(ib);
  pArrays[33] = emlrtCreateDoubleScalar(jb);
  pArrays[34] = emlrtCreateString(kb);
  pArrays[35] = emlrtCreateDoubleScalar(lb);
  pArrays[36] = emlrtCreateString(mb);
  pArrays[37] = emlrtCreateLogicalScalar(nb);
  pArrays[38] = emlrtCreateString(ob);
  pArrays[39] = emlrtCreateDoubleScalar(pb);
  pArrays[40] = emlrtCreateString(qb);
  pArrays[41] = emlrtCreateDoubleScalar(rb);
  return emlrtCallMATLABR2012b(sp, 1, &b_m, 42, pArrays, "fimath", true,
    location);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *S
 *                const char_T *identifier
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *S, const
  char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  h_emlrt_marshallIn(sp, emlrtAlias(S), &thisId);
  emlrtDestroyArray(&S);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  emlrtMsgIdentifier thisId;
  static const int32_T dims = 0;
  thisId.fParent = parentId;
  thisId.bParentIsCell = false;
  emlrtCheckStructR2012b(sp, parentId, u, 4, sv, 0U, &dims);
  thisId.fIdentifier = "x_partial";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 0, "x_partial")),
                     &thisId);
  thisId.fIdentifier = "y_partial";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 1, "y_partial")),
                     &thisId);
  thisId.fIdentifier = "x_output";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 2, "x_output")),
                     &thisId);
  thisId.fIdentifier = "y_output";
  i_emlrt_marshallIn(sp, emlrtAlias(emlrtGetFieldR2017b(sp, u, 0, 3, "y_output")),
                     &thisId);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : void
 */
static void i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  static const int32_T dims[2] = { 0, 0 };

  emlrtCheckFiR2012b(sp, parentId, u, false, 2U, dims, c_eml_mx, f_eml_mx);
  k_emlrt_marshallIn(emlrtAlias(u));
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const mxArray *src
 *                int8_T ret[16]
 * Return Type  : void
 */
static void j_emlrt_marshallIn(const mxArray *src, int8_T ret[16])
{
  const mxArray *mxInt;
  int8_T (*r)[16];
  int32_T i;
  mxInt = emlrtImportFiIntArrayR2008b(src);
  r = (int8_T (*)[16])emlrtMxGetData(mxInt);
  for (i = 0; i < 16; i++) {
    ret[i] = (*r)[i];
  }

  emlrtDestroyArray(&mxInt);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const mxArray *src
 * Return Type  : void
 */
static void k_emlrt_marshallIn(const mxArray *src)
{
  const mxArray *mxInt;
  mxInt = emlrtImportFiIntArrayR2008b(src);
  emlrtMxGetData(mxInt);
  emlrtDestroyArray(&mxInt);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const char * b
 *                real_T c
 *                const char * d
 *                real_T e
 *                const char * f
 *                real_T g
 *                const char * h
 *                real_T i
 *                const char * j
 *                real_T k
 *                emlrtMCInfo *location
 * Return Type  : const mxArray *
 */
static const mxArray *numerictype(const emlrtStack *sp, const char * b, real_T c,
  const char * d, real_T e, const char * f, real_T g, const char * h, real_T i,
  const char * j, real_T k, emlrtMCInfo *location)
{
  const mxArray *pArrays[10];
  const mxArray *m;
  pArrays[0] = emlrtCreateString(b);
  pArrays[1] = emlrtCreateDoubleScalar(c);
  pArrays[2] = emlrtCreateString(d);
  pArrays[3] = emlrtCreateDoubleScalar(e);
  pArrays[4] = emlrtCreateString(f);
  pArrays[5] = emlrtCreateDoubleScalar(g);
  pArrays[6] = emlrtCreateString(h);
  pArrays[7] = emlrtCreateDoubleScalar(i);
  pArrays[8] = emlrtCreateString(j);
  pArrays[9] = emlrtCreateDoubleScalar(k);
  return emlrtCallMATLABR2012b(sp, 1, &m, 10, pArrays, "numerictype", true,
    location);
}

/*
 * Arguments    : const emlrtStack *sp
 * Return Type  : void
 */
static void qr_cordic_opt_once(const emlrtStack *sp)
{
  emlrtAssignP(&f_eml_mx, NULL);
  emlrtAssignP(&e_eml_mx, NULL);
  emlrtAssignP(&d_eml_mx, NULL);
  emlrtAssignP(&c_eml_mx, NULL);
  emlrtAssignP(&b_eml_mx, NULL);
  emlrtAssignP(&eml_mx, NULL);
  emlrtAssignP(&f_eml_mx, numerictype(sp, "WordLength", 12.0, "FractionLength",
    10.0, "BinaryPoint", 10.0, "Slope", 0.0009765625, "FixedExponent", -10.0,
    &emlrtMCI));
  emlrtAssignP(&e_eml_mx, numerictype(sp, "WordLength", 12.0, "FractionLength",
    3.0, "BinaryPoint", 3.0, "Slope", 0.125, "FixedExponent", -3.0, &emlrtMCI));
  emlrtAssignP(&d_eml_mx, numerictype(sp, "WordLength", 20.0, "FractionLength",
    10.0, "BinaryPoint", 10.0, "Slope", 0.0009765625, "FixedExponent", -10.0,
    &emlrtMCI));
  emlrtAssignP(&c_eml_mx, fimath(sp, "RoundMode", "floor", "RoundingMethod",
    "Floor", "OverflowMode", "wrap", "OverflowAction", "Wrap", "ProductMode",
    "KeepMSB", "SumMode", "FullPrecision", "ProductWordLength", 32.0,
    "SumWordLength", 32.0, "MaxProductWordLength", 65535.0, "MaxSumWordLength",
    65535.0, "ProductFractionLength", 30.0, "ProductFixedExponent", -30.0,
    "SumFractionLength", 30.0, "SumFixedExponent", -30.0,
    "SumSlopeAdjustmentFactor", 1.0, "SumBias", 0.0,
    "ProductSlopeAdjustmentFactor", 1.0, "ProductBias", 0.0, "CastBeforeSum",
    true, "SumSlope", 9.3132257461547852E-10, "ProductSlope",
    9.3132257461547852E-10, &emlrtMCI));
  emlrtAssignP(&b_eml_mx, numerictype(sp, "WordLength", 8.0, "FractionLength",
    0.0, "BinaryPoint", 0.0, "Slope", 1.0, "FixedExponent", 0.0, &emlrtMCI));
  emlrtAssignP(&eml_mx, fimath(sp, "RoundMode", "nearest", "RoundingMethod",
    "Nearest", "OverflowMode", "saturate", "OverflowAction", "Saturate",
    "ProductMode", "FullPrecision", "SumMode", "FullPrecision",
    "ProductWordLength", 32.0, "SumWordLength", 32.0, "MaxProductWordLength",
    65535.0, "MaxSumWordLength", 65535.0, "ProductFractionLength", 30.0,
    "ProductFixedExponent", -30.0, "SumFractionLength", 30.0, "SumFixedExponent",
    -30.0, "SumSlopeAdjustmentFactor", 1.0, "SumBias", 0.0,
    "ProductSlopeAdjustmentFactor", 1.0, "ProductBias", 0.0, "CastBeforeSum",
    true, "SumSlope", 9.3132257461547852E-10, "ProductSlope",
    9.3132257461547852E-10, &emlrtMCI));
  emlrtCheckDefaultFimathR2008b(&eml_mx);
}

/*
 * Arguments    : const mxArray * const prhs[3]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void qr_cordic_opt_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[2])
{
  int8_T M[16];
  int16_T Q[16];
  int16_T R[16];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "M", M);
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "T");
  g_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "S");

  /* Invoke the target function */
  qr_cordic_opt(M, Q, R);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(&st, Q);
  if (nlhs > 1) {
    plhs[1] = c_emlrt_marshallOut(&st, R);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void qr_cordic_opt_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  qr_cordic_opt_xil_terminate();
  qr_cordic_opt_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
  emlrtDestroyArray(&eml_mx);
  emlrtDestroyArray(&b_eml_mx);
  emlrtDestroyArray(&c_eml_mx);
  emlrtDestroyArray(&d_eml_mx);
  emlrtDestroyArray(&e_eml_mx);
  emlrtDestroyArray(&f_eml_mx);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void qr_cordic_opt_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 3U, "ForceOff");
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    qr_cordic_opt_once(&st);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void qr_cordic_opt_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_qr_cordic_opt_api.c
 *
 * [EOF]
 */
