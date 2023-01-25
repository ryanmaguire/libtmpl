#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments.
 *      Add license, "doc-string".
 *      Clean this up.
 *      Implement fast rational approximation for negative values.
 *      Implement fast rational approximation for large positive values.
 */

#if 1

double tmpl_Double_LambertW(double x)
{
    tmpl_IEEE754_Double w;
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (w.bits.sign)
            return TMPL_NAN;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 52U)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 7U)
        return tmpl_Double_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (w.bits.sign)
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
            return tmpl_Double_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        w.r = x + tmpl_Rcpr_Euler_E;

        /*  If this sum is negative, return NaN.                              */
        if (w.bits.sign)
            return TMPL_NAN;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (w.r == 0.0)
            return -1.0;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 10U)
            return tmpl_Double_LambertW_Near_Branch(w.r);

        else
        {
            /*  Pade approximant is good to around 10^-8 for -1/e < x < 0.    */
            const double x0 = tmpl_Double_LambertW_Pade(x);

            /*  Set tolerance to double precision.                            */
            const double tol = 2.220446049250313080847263336181640625e-16;

            /*  Use Halley's method. Only 1 or 2 iterations needed.           */
            return tmpl_Double_LambertW_Halley(x, x0, tol);
        }
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 2U)
        return tmpl_Double_LambertW_Pade(x);

    else
        return tmpl_Double_LambertW_Positive(x);
}

#else
#if TMPL_HAS_IEEE754_DOUBLE == 1

double tmpl_Double_LambertW(double x)
{
    tmpl_IEEE754_Double w;
    double x0, tol;
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (w.bits.sign)
            return TMPL_NAN;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 52U)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 7U)
        return tmpl_Double_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (w.bits.sign)
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
            return tmpl_Double_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        w.r = x + tmpl_Rcpr_Euler_E;

        /*  If this sum is negative, return NaN.                              */
        if (w.bits.sign)
            return TMPL_NAN;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (w.r == 0.0)
            return -1.0;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 10U)
            return tmpl_Double_LambertW_Near_Branch(w.r);

        /*  For all other inputs use the Halley method below with initial     *
         *  guess x0 = sqrt(2(1 + e*x)) = sqrt(2*e*w.r)                       */
        x0 = tmpl_Double_Sqrt(2.0*tmpl_Euler_E*w.r);
        w.r = x + 1.0;
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 2U)
        return tmpl_Double_LambertW_Pade(x);

    /*  Small argument, use LambertW(x) ~= x as guess.                        */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS + 1U)
    {
        x0 = x;
        w.r = x0 + 1.0;
    }

    /*  Large argument. Use LamertW(x) ~= log(x / log(x)).                    */
    else
    {
        x0 = tmpl_Double_Log(x / tmpl_Double_Log(x));
        w.r = x0;
    }

    /*  Set the tolerance to 2^-28 * w.r. w.bits.expo is 11 bits, so the max  *
     *  value is 2048. We can compute w.bits.expo - 28 without worrying about *
     *  sign conversions by w.bits.expo + 2020, since 2020 = -28 mod 2048.    */
    w.bits.expo += 2020;
    tol = w.r;

    /*  Use Halley's method to compute the LambertW function with the given   *
     *  tolerance and initial guess.                                          */
    return tmpl_Double_LambertW_Halley(x, x0, tol);
}
/*  End of tmpl_Double_LambertW.                                              */

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
#endif
