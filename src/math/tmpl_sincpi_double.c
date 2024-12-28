/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_DOUBLE == 1

#include "auxiliary/tmpl_sincpi_remez_double.h"
#include "auxiliary/tmpl_sincpi_rat_remez_double.h"

double tmpl_Double_SincPi(double x)
{
    tmpl_IEEE754_Double w;
    w.r = x;

    /*  Special case, NaN or infinity.                                        */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  For NaN, simply return the input.                                 */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  Otherwise, the limit for sinc(pi x) at +/- infinity is zero.      */
        return 0.0;
    }

    /*  For small x, |x| < 0.5, we use Remez expansions to speed things up.   */
    if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x01U)
    {
        /*  For very small inputs, |x| < 2^-27, use the limit at zero, 1.     */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x1BU)
            return 1.0;

        /*  For |x| < 2^-4 we can use a Remez polynomial. The odd degree      *
         *  terms of the polynomial are zero, so the degree 10 Remez          *
         *  approximation needs only 6 terms.                                 */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 0x04U)
            return tmpl_Double_SincPi_Remez(x);

        /*  For |x| < 0.5, a rational Remez approximation is used. Again, we  *
         *  need only half the number of terms since sinc(pi x) is even. The  *
         *  degree (8, 8) rational Remez approximations uses 5 terms in the   *
         *  numerator and 5 terms in the denominator.                         */
        return tmpl_Double_SincPi_Rat_Remez(x);
    }

    return tmpl_Double_SinPi(x) / (tmpl_Double_Pi * x);
}

#else

double tmpl_Double_SincPi(double x)
{
    if (x == 0.0)
        return 1.0;

    return tmpl_Double_SinPi(x) / (tmpl_Double_Pi * x);
}

#endif
