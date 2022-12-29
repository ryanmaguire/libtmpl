/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE == 1

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define TMPL_BIG_SCALE (1.340780792994259709957402E+154)
#define TMPL_RCPR_BIG_SCALE (7.458340731200206743290965E-155)

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    tmpl_IEEE754_Double w;
    double x = tmpl_Double_Abs(z.dat[0]);
    double y = tmpl_Double_Abs(z.dat[1]);

    if (x < y)
        w.r = y;
    else
        w.r = x;

    if (w.bits.expo < TMPL_DOUBLE_BIAS + 0x200U)
    {
        if (w.bits.expo > TMPL_DOUBLE_BIAS - 0x1E6U)
            return tmpl_Double_Sqrt(x*x + y*y);

        x *= TMPL_BIG_SCALE;
        y *= TMPL_BIG_SCALE;
        return TMPL_RCPR_BIG_SCALE * tmpl_Double_Sqrt(x*x + y*y);
    }

    x *= TMPL_RCPR_BIG_SCALE;
    y *= TMPL_RCPR_BIG_SCALE;
    return TMPL_BIG_SCALE * tmpl_Double_Sqrt(x*x + y*y);
}
/*  End of tmpl_CDouble_Abs.                                                  */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    double rcpr_t;
    double x = tmpl_Double_Abs(z.dat[0]);
    double y = tmpl_Double_Abs(z.dat[1]);
    const double t = (x < y ? y : x);

    if (t == 0.0)
        return 0.0;

    rcpr_t = 1.0 / t;
    x *= rcpr_t;
    y *= rcpr_t;
    return t * tmpl_Double_Sqrt(x*x + y*y);
}
/*  End of tmpl_CDouble_Abs.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  The values 2^64 and 2^-64, to single precision, stored as macros.         */
#define TMPL_BIG_SCALE 1.8446744073709552E+19F
#define TMPL_RCPR_BIG_SCALE 5.4210108624275222E-20F

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    tmpl_IEEE754_Float w;
    float x = tmpl_Float_Abs(z.dat[0]);
    float y = tmpl_Float_Abs(z.dat[1]);

    if (x < y)
        w.r = y;
    else
        w.r = x;

    if (w.bits.expo < TMPL_FLOAT_BIAS + 0x40U)
    {
        if (w.bits.expo > 0x4BU)
            return tmpl_Float_Sqrt(x*x + y*y);

        x *= TMPL_BIG_SCALE;
        y *= TMPL_BIG_SCALE;
        return TMPL_RCPR_BIG_SCALE * tmpl_Float_Sqrt(x*x + y*y);
    }

    x *= TMPL_RCPR_BIG_SCALE;
    y *= TMPL_RCPR_BIG_SCALE;
    return TMPL_BIG_SCALE * tmpl_Float_Sqrt(x*x + y*y);
}
/*  End of tmpl_CFloat_Abs.                                                   */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline float tmpl_CFloat_Abs(tmpl_ComplexFloat z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float rcpr_t;
    float x = tmpl_Float_Abs(z.dat[0]);
    float y = tmpl_Float_Abs(z.dat[1]);
    const float t = (x < y ? y : x);

    if (t == 0.0F)
        return 0.0F;

    rcpr_t = 1.0F / t;
    x *= rcpr_t;
    y *= rcpr_t;
    return t * tmpl_Float_Sqrt(x*x + y*y);
}
/*  End of tmpl_CFloat_Abs.                                                   */

#endif
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1        */

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_LDOUBLE == 1 && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  64-bit long double.                                                       */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN
#define TMPL_BIG_SCALE (1.340780792994259709957402E+154)
#define TMPL_RCPR_BIG_SCALE (7.458340731200206743290965E-155)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x200U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1E6U)

/*  80-bit extended precision long double.                                    */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN    || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN   || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN
#define TMPL_BIG_SCALE (1.090748135619415929462984244733E2466L)
#define TMPL_RCPR_BIG_SCALE (9.16801933777423582810706196024E-2467L)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x2000U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1FE0U)

/*  128-bit quadruple precision long double.                                  */
#else
#define TMPL_BIG_SCALE (1.090748135619415929462984244733E2466L)
#define TMPL_RCPR_BIG_SCALE (9.16801933777423582810706196024E-2467L)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x2000U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1FC8U)
#endif

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline long double tmpl_CLDouble_Abs(tmpl_ComplexLongDouble z)
{
    tmpl_IEEE754_LDouble w;
    long double x = tmpl_LDouble_Abs(z.dat[0]);
    long double y = tmpl_LDouble_Abs(z.dat[1]);

    if (x < y)
        w.r = y;
    else
        w.r = x;

    if (w.bits.expo < TMPL_EXPO_TOO_HIGH)
    {
        if (w.bits.expo > TMPL_EXPO_TOO_LOW)
            return tmpl_LDouble_Sqrt(x*x + y*y);

        x *= TMPL_BIG_SCALE;
        y *= TMPL_BIG_SCALE;
        return TMPL_RCPR_BIG_SCALE * tmpl_LDouble_Sqrt(x*x + y*y);
    }

    x *= TMPL_RCPR_BIG_SCALE;
    y *= TMPL_RCPR_BIG_SCALE;
    return TMPL_BIG_SCALE * tmpl_LDouble_Sqrt(x*x + y*y);
}
/*  End of tmpl_CLDouble_Abs.                                                 */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE
#undef TMPL_EXPO_TOO_HIGH
#undef TMPL_EXPO_TOO_LOW

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Function for computing the magnitude, or modulus, of a complex number.    */
static inline long double tmpl_CLDouble_Abs(tmpl_ComplexLongDouble z)
{
    long double rcpr_t;
    long double x = tmpl_LDouble_Abs(z.dat[0]);
    long double y = tmpl_LDouble_Abs(z.dat[1]);
    const long double t = (x < y ? y : x);

    if (t == 0.0L)
        return 0.0L;

    rcpr_t = 1.0L / t;
    x *= rcpr_t;
    y *= rcpr_t;
    return t * tmpl_LDouble_Sqrt(x*x + y*y);
}
/*  End of tmpl_CDouble_Abs.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */
