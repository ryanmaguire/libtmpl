#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add comments.
 *      Add license, "doc-string".
 *      Clean this up.
 *      Implement fast rational approximation for negative values.
 *      Implement fast rational approximation for large positive values.
 */

#if TMPL_HAS_IEEE754_FLOAT == 1

float tmpl_Float_LambertW(float x)
{
    tmpl_IEEE754_Float w;
    float x0, tol;
    w.r = x;

    /*  Special case, NaN or Infinity.                                        */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (w.bits.sign)
            return TMPL_NANF;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS - 23U)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS - 7U)
        return tmpl_Float_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (w.bits.sign)
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 4U)
            return tmpl_Float_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        w.r = x + tmpl_Rcpr_Euler_E_F;

        /*  If this sum is negative, return NaN.                              */
        if (w.bits.sign)
            return TMPL_NANF;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (w.r == 0.0F)
            return -1.0F;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (w.bits.expo < TMPL_FLOAT_UBIAS - 10U)
            return tmpl_Float_LambertW_Near_Branch(w.r);

        /*  For all other inputs use the Halley method below with initial     *
         *  guess x0 = sqrt(2(1 + e*x)) = sqrt(2*e*w.r)                       */
        x0 = tmpl_Float_Sqrt(2.0F*tmpl_Euler_E_F*w.r);
        w.r = x + 1.0F;
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS - 2U)
        return tmpl_Float_LambertW_Pade(x);

    /*  Small argument, use LambertW(x) ~= x as guess.                        */
    if (w.bits.expo < TMPL_FLOAT_UBIAS + 1U)
    {
        x0 = x;
        w.r = x0 + 1.0F;
    }

    /*  Large argument. Use LamertW(x) ~= log(x / log(x)).                    */
    else
    {
        x0 = tmpl_Float_Log(x / tmpl_Float_Log(x));
        w.r = x0;
    }

    /*  Set the tolerance to 2^-14 * w.r. w.bits.expo is 8 bits, so the max   *
     *  value is 256. We can compute w.bits.expo - 14 without worrying about  *
     *  sign conversions by w.bits.expo + 242, since 242 = -14 mod 256.       */
    w.bits.expo += 242;
    tol = w.r;

    /*  Use Halley's method to compute the LambertW function with the given   *
     *  tolerance and initial guess.                                          */
    return tmpl_Float_LambertW_Halley(x, x0, tol);
}
/*  End of tmpl_Float_LambertW.                                               */

#else

/*  FLT_EPSILON found here.                                                   */
#include <float.h>

float tmpl_Float_LambertW(float x)
{
    float y, x0, tol;
    const float abs_x = tmpl_Float_Abs(x);

    /*  Special case, NaN or Infinity.                                        */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
    {
        /*  For NaN, simply return the input. Infinity is handled separately. */
        if (tmpl_Float_Is_NaN(x))
            return x;

        /*  Second case, x is infinity. Use asymptotic. LambertW(-inf) = NaN  *
         *  and LambertW(inf) = inf.                                          */
        if (x < 0.0F)
            return TMPL_NANF;
        else
            return x;
    }

    /*  Avoid underflow. LambertW(x) ~= x for small values.                   */
    else if (abs_x < FLT_EPSILON)
        return x;

    /*  Small inputs, use the Maclaurin series.                               */
    else if (abs_x < 0.0078125F)
        return tmpl_Float_LambertW_Maclaurin(x);

    /*  Handle negative values carefully.                                     */
    else if (x < 0.0F)
    {
        /*  For values close the zero, the Pade approximant works. It doesn't *
         *  work as well as it does for positive values, so we need to        *
         *  restrict to a smaller range.                                      */
        if (abs_x < 0.0625F)
            return tmpl_Float_LambertW_Pade(x);

        /*  The function is undefined for x < -1/e. Compute x + 1/e.          */
        y = x + tmpl_Rcpr_Euler_E_F;

        /*  If this sum is negative, return NaN.                              */
        if (y < 0.0F)
            return TMPL_NANF;

        /*  Handle the case x == -1/e precisely. Return -1. This solves       *
         *  Lambert(x) exp(LambertW(x)) = -1/e.                               */
        else if (y == 0.0F)
            return -1.0F;

        /*  For values close to the branch cut, use a series expansion.       */
        else if (y < 0.0009765625F)
            return tmpl_Float_LambertW_Near_Branch(y);

        /*  For all other inputs use the Halley method below with initial     *
         *  guess x0 = sqrt(2(1 + e*x)) = sqrt(2*e*y)                         */
        x0 = tmpl_Float_Sqrt(2.0F*tmpl_Euler_E_F*y);
        y = x + 1.0F;
    }

    /*  For slightly larger inputs we can use a Pade approximant, which is    *
     *  still significantly faster than iteratively applying Halley's method. */
    else if (abs_x < 0.25F)
        return tmpl_Float_LambertW_Pade(x);

    /*  Small argument, use LambertW(x) ~= x as guess.                        */
    if (abs_x < 2.0F)
    {
        x0 = x;
        y = x0 + 1.0F;
    }

    /*  Large argument. Use LamertW(x) ~= log(x / log(x)).                    */
    else
    {
        x0 = tmpl_Float_Log(x / tmpl_Float_Log(x));
        y = x0;
    }

    /*  Tolerance is y * EPSILON, found in float.h.                           */
    tol = y*FLT_EPSILON;

    /*  Use Halley's method to compute the LambertW function with the given   *
     *  tolerance and initial guess.                                          */
    return tmpl_Float_LambertW_Halley(x, x0, tol);
}
/*  End of tmpl_Float_LambertW.                                               */

#endif
