
/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                               64-bit Double                                *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01L)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02L)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02L)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01L)
#define A05 (+2.2710800170898437500000000000000000000000000000000E-01L)

/*  128-bit double-double, a few more terms.                                  */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                           128-bit Double-Double                            *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01L)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02L)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02L)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01L)
#define A05 (+2.2710800170898437500000000000000000000000000000000E-01L)
#define A06 (+5.7250142097473144531250000000000000000000000000000E-01L)
#define A07 (+1.7277275025844573974609375000000000000000000000000E+00L)
#define A08 (+6.0740420012734830379486083984375000000000000000000E+00L)
#define A09 (+2.4380529699556063860654830932617187500000000000000E+01L)
#define A10 (+1.1001714026924673817120492458343505859375000000000E+02L)
#define A11 (+5.5133589612202058560797013342380523681640625000000E+02L)
#define A12 (+3.0380905109223842686105854227207601070404052734375E+03L)
#define A13 (+1.8257755474293174691169383550004567950963973999023E+0

/*  128-bit quadruple, and a few more terms.                                  */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/******************************************************************************
 *                             128-bit Quadruple                              *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01L)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02L)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02L)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01L)
#define A05 (+2.2710800170898437500000000000000000000000000000000E-01L)
#define A06 (+5.7250142097473144531250000000000000000000000000000E-01L)
#define A07 (+1.7277275025844573974609375000000000000000000000000E+00L)
#define A08 (+6.0740420012734830379486083984375000000000000000000E+00L)
#define A09 (+2.4380529699556063860654830932617187500000000000000E+01L)
#define A10 (+1.1001714026924673817120492458343505859375000000000E+02L)
#define A11 (+5.5133589612202058560797013342380523681640625000000E+02L)
#define A12 (+3.0380905109223842686105854227207601070404052734375E+03L)
#define A13 (+1.8257755474293174691169383550004567950963973999023E+04L)
#define A14 (+1.1883842625678325312377214828529758960939943790436E+05L)

/*  80-bit extended and portable version.                                     */
#else

/******************************************************************************
 *                         80-bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01L)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02L)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02L)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01L)
#define A05 (+2.2710800170898437500000000000000000000000000000000E-01L)
#define A06 (+5.7250142097473144531250000000000000000000000000000E-01L)
#define A07 (+1.7277275025844573974609375000000000000000000000000E+00L)

#endif
/*  End of double vs. extended vs. quadruple vs. double-double.               */

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
