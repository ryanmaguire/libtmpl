#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments and "doc-string".
 *      Speed this up.
 *          The Halley-based algorithm is now out-dated. Several other
 *          methods exist that avoid evaluation of transcendental functions
 *          like log and exp. This have significant performance boosts.
 */

#if TMPL_HAS_IEEE754_LDOUBLE == 1

#define TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN 0
#define TMPL_LDOUBLE_64_BIT_BIG_ENDIAN 1
#define TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN 2
#define TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN 3
#define TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN 4
#define TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN 5
#define TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN 6
#define TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN 7
#define TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN 8
#define TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN 9

/*  These are roughly 2^{number of expo bits} - {number of mantissa bits} for *
 *  various sizes of long double. This way {expo bits} + TMPL_TOL_OFFSET is   *
 *  evaluated as {expo bits} - {number of mantissa bits} without conversion   *
 *  worries since unsigned arithmetic is computed mod 2^{number of expo bits}.*/
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN            || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN
#define TMPL_TOL_OFFSET (2020U)
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN    || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN   || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN
#define TMPL_TOL_OFFSET (32710U)
#elif \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN
#define TMPL_TOL_OFFSET (1948U)
#else
#define TMPL_TOL_OFFSET (32660U)
#endif

long double tmpl_LDouble_LambertW(long double x)
{
    tmpl_IEEE754_LDouble w;
    long double x0, tol;
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (TMPL_LDOUBLE_IS_NAN(w))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return TMPL_NANL;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS -
                                         TMPL_LDOUBLE_MANTISSA_ULENGTH)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 7U)
        return tmpl_LDouble_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (TMPL_LDOUBLE_IS_NEGATIVE(w))
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 4U)
            return tmpl_LDouble_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        w.r = x + tmpl_Rcpr_Euler_E_L;

        /*  If this sum is negative, return NaN.                              */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return TMPL_NANL;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (w.r == 0.0L)
            return -1.0L;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 10U)
            return tmpl_LDouble_LambertW_Near_Branch(w.r);

        /*  For all other inputs use the Halley method below with initial     *
         *  guess x0 = sqrt(2(1 + e*x)) = sqrt(2*e*w.r)                       */
        x0 = tmpl_LDouble_Sqrt(2.0L*tmpl_Euler_E_L*w.r);
        w.r = x + 1.0L;
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 2U)
        return tmpl_LDouble_LambertW_Pade(x);

    /*  Small argument, use LambertW(x) ~= x as guess.                        */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS + 1U)
    {
        x0 = x;
        w.r = x0 + 1.0L;
    }

    /*  Large argument. Use LamertW(x) ~= log(x / log(x)).                    */
    else
    {
        x0 = tmpl_LDouble_Log(x / tmpl_LDouble_Log(x));
        w.r = x0;
    }

    /*  Set the tolerance.                                                    */
    w.bits.expo += TMPL_TOL_OFFSET;
    tol = w.r;

    /*  Use Halley's method to compute the LambertW function with the given   *
     *  tolerance and initial guess.                                          */
    return tmpl_LDouble_LambertW_Halley(x, x0, tol);
}
/*  End of tmpl_LDouble_LambertW.                                             */

#undef TMPL_TOL_OFFSET

#else

/*  DBL_EPSILON found here.                                                   */
#include <float.h>

double tmpl_Double_LambertW(double x)
{
    double y, x0, tol;
    const double abs_x = tmpl_Double_Abs(x);

    /*  Special case, NaN or Infinity.                                        */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (tmpl_Double_Is_NaN(x))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (x < 0.0)
            return TMPL_NAN;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (abs_x < DBL_EPSILON)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (abs_x < 0.0078125)
        return tmpl_Double_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (x < 0.0)
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (abs_x < 0.0625)
            return tmpl_Double_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        y = x + tmpl_Rcpr_Euler_E;

        /*  If this sum is negative, return NaN.                              */
        if (y < 0.0)
            return TMPL_NAN;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (y == 0.0)
            return -1.0;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (y < 0.0009765625)
            return tmpl_Double_LambertW_Near_Branch(y);

        /*  For all other inputs use the Halley method below with initial     *
         *  guess x0 = sqrt(2(1 + e*x)) = sqrt(2*e*y)                         */
        x0 = tmpl_Double_Sqrt(2.0*tmpl_Euler_E*y);
        y = x + 1.0;
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (abs_x < 0.25)
        return tmpl_Double_LambertW_Pade(x);

    /*  Small argument, use LambertW(x) ~= x as guess.                        */
    if (abs_x < 2.0)
    {
        x0 = x;
        y = x0 + 1.0;
    }

    /*  Large argument. Use LamertW(x) ~= log(x / log(x)).                    */
    else
    {
        x0 = tmpl_Double_Log(x / tmpl_Double_Log(x));
        y = x0;
    }

    /*  Tolerance is y * EPSILON, found in float.h.                           */
    tol = y*DBL_EPSILON;

    /*  Use Halley's method to compute the LambertW function with the given   *
     *  tolerance and initial guess.                                          */
    return tmpl_Double_LambertW_Halley(x, x0, tol);
}
/*  End of tmpl_Double_LambertW.                                              */

#endif
