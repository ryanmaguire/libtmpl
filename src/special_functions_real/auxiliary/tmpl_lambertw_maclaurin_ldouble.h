/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_LAMBERTW_MACLAURIN_LDOUBLE_H
#define TMPL_LAMBERTW_MACLAURIN_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A1 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A2 (-1.0000000000000000000000000000000000000000000000000E+00L)
#define A3 (+1.5000000000000000000000000000000000000000000000000E+00L)
#define A4 (-2.6666666666666666666666666666666666666666666666667E+00L)
#define A5 (+5.2083333333333333333333333333333333333333333333333E+00L)
#define A6 (-1.0800000000000000000000000000000000000000000000000E+01L)
#define A7 (+2.3343055555555555555555555555555555555555555555556E+01L)
#define A8 (-5.2012698412698412698412698412698412698412698412698E+01L)
#define A9 (+1.1862522321428571428571428571428571428571428571429E+02L)

#define TMPL_POLY_EVAL(z) \
z * (A1 + z*(A2 + z*(A3 + z*(A4 + z*(A5 + z*(A6 + z*(A7 + z*(A8 + z*A9))))))))

/*  128-bit double-double, a few more terms.                                  */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A02 (-1.0000000000000000000000000000000000000000000000000E+00L)
#define A03 (+1.5000000000000000000000000000000000000000000000000E+00L)
#define A04 (-2.6666666666666666666666666666666666666666666666667E+00L)
#define A05 (+5.2083333333333333333333333333333333333333333333333E+00L)
#define A06 (-1.0800000000000000000000000000000000000000000000000E+01L)
#define A07 (+2.3343055555555555555555555555555555555555555555556E+01L)
#define A08 (-5.2012698412698412698412698412698412698412698412698E+01L)
#define A09 (+1.1862522321428571428571428571428571428571428571429E+02L)
#define A10 (-2.7557319223985890652557319223985890652557319223986E+02L)
#define A11 (+6.4978717234347442680776014109347442680776014109347E+02L)
#define A12 (-1.5511605194805194805194805194805194805194805194805E+03L)
#define A13 (+3.7414497029592385495163272941050718828496606274384E+03L)
#define A14 (-9.1045002411580189357967135744913522691300469078247E+03L)
#define A15 (+2.2324308512706601434280005708577137148565719994291E+04L)
#define A16 (-5.5103621972903835337697771560205422639285073147507E+04L)
#define A17 (+1.3680886090394293563342215789305736395683485630576E+05L)
#define A18 (-3.4142205066583836331735491399356945575432970390954E+05L)

#define TMPL_POLY_EVAL(z) \
z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*(\
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*A18\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  128-bit quadruple, even more terms.                                       */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A02 (-1.0000000000000000000000000000000000000000000000000E+00L)
#define A03 (+1.5000000000000000000000000000000000000000000000000E+00L)
#define A04 (-2.6666666666666666666666666666666666666666666666667E+00L)
#define A05 (+5.2083333333333333333333333333333333333333333333333E+00L)
#define A06 (-1.0800000000000000000000000000000000000000000000000E+01L)
#define A07 (+2.3343055555555555555555555555555555555555555555556E+01L)
#define A08 (-5.2012698412698412698412698412698412698412698412698E+01L)
#define A09 (+1.1862522321428571428571428571428571428571428571429E+02L)
#define A10 (-2.7557319223985890652557319223985890652557319223986E+02L)
#define A11 (+6.4978717234347442680776014109347442680776014109347E+02L)
#define A12 (-1.5511605194805194805194805194805194805194805194805E+03L)
#define A13 (+3.7414497029592385495163272941050718828496606274384E+03L)
#define A14 (-9.1045002411580189357967135744913522691300469078247E+03L)
#define A15 (+2.2324308512706601434280005708577137148565719994291E+04L)
#define A16 (-5.5103621972903835337697771560205422639285073147507E+04L)
#define A17 (+1.3680886090394293563342215789305736395683485630576E+05L)
#define A18 (-3.4142205066583836331735491399356945575432970390954E+05L)
#define A19 (+8.5599296599660755146336302506332246623424823099755E+05L)
#define A20 (-2.1549902060910882893217087453586471647237214022733E+06L)

#define TMPL_POLY_EVAL(z) \
z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*(\
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*A20\
                                    )\
                                  )\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#else

/*  Coefficients for the polynomial.                                          */
#define A01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A02 (-1.0000000000000000000000000000000000000000000000000E+00L)
#define A03 (+1.5000000000000000000000000000000000000000000000000E+00L)
#define A04 (-2.6666666666666666666666666666666666666666666666667E+00L)
#define A05 (+5.2083333333333333333333333333333333333333333333333E+00L)
#define A06 (-1.0800000000000000000000000000000000000000000000000E+01L)
#define A07 (+2.3343055555555555555555555555555555555555555555556E+01L)
#define A08 (-5.2012698412698412698412698412698412698412698412698E+01L)
#define A09 (+1.1862522321428571428571428571428571428571428571429E+02L)
#define A10 (-2.7557319223985890652557319223985890652557319223986E+02L)
#define A11 (+6.4978717234347442680776014109347442680776014109347E+02L)

#define TMPL_POLY_EVAL(z) \
z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*A11\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

#endif

/*  Computes the LambertW function via a Maclaurin series for small inputs.   */
TMPL_STATIC_INLINE
long double tmpl_LDouble_LambertW_Maclaurin(long double x)
{
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_LDouble_LambertW_Maclaurin.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
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
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
