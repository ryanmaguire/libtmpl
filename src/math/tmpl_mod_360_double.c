#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 double.                                                */
#if TMPL_HAS_IEEE754_DOUBLE == 1

double tmpl_Double_Mod_360(double x)
{
    tmpl_IEEE754_Double w, tmp, pow2_360, invpow2_360;
    unsigned int n;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special case, Infinity and NaN.                                       */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return TMPL_NAN;

    /*  Save the sign of x for later.                                         */
    tmp.bits.sign = w.bits.sign;

    /*  Compute the absolute value of the input.                              */
    w.bits.sign = 0x00U;

    /*  For inputs with magnitude less than 360, no modulo is computed.       */
    if (w.r < 360.0)
        return x;

    pow2_360.r = 3.60E2;
    invpow2_360.r = 2.777777777777777777777777777777777777778E-03;
    n = (w.bits.expo - TMPL_DOUBLE_UBIAS - 8U)/32U;

    pow2_360.bits.expo += (32*n & 0x7FF);
    invpow2_360.bits.expo -= (32*n & 0x7FF);

    for (; (n+1U) != 0U; n--)
    {
        w.r -= pow2_360.r*tmpl_Double_Floor(w.r * invpow2_360.r);
        pow2_360.bits.expo -= 32U;
        invpow2_360.bits.expo += 0x20U;
    }

    if (tmp.bits.sign)
        return -w.r;
    else
        return w.r;
}

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  This function is not valid for very very large inputs.                    */
double tmpl_Double_Mod_360(double x)
{
    if (x < 0.0)
        return x + 360.0*tmpl_Double_Floor(-x/360.0);
    else
        return x - 360.0*tmpl_Double_Floor(x/360.0);
}
/*  End of tmpl_Double_Mod_360.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
