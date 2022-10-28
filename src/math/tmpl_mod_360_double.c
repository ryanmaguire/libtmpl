#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 double.                                                */
#if TMPL_HAS_IEEE754_DOUBLE == 1

static const double my_360_arr[32] = {
    360.0 * 0x1.0p0,
    360.0 * 0x1.0p32,
    360.0 * 0x1.0p64,
    360.0 * 0x1.0p96,
    360.0 * 0x1.0p128,
    360.0 * 0x1.0p160,
    360.0 * 0x1.0p192,
    360.0 * 0x1.0p224,
    360.0 * 0x1.0p256,
    360.0 * 0x1.0p288,
    360.0 * 0x1.0p320,
    360.0 * 0x1.0p352,
    360.0 * 0x1.0p384,
    360.0 * 0x1.0p416,
    360.0 * 0x1.0p448,
    360.0 * 0x1.0p480,
    360.0 * 0x1.0p512,
    360.0 * 0x1.0p544,
    360.0 * 0x1.0p576,
    360.0 * 0x1.0p608,
    360.0 * 0x1.0p640,
    360.0 * 0x1.0p672,
    360.0 * 0x1.0p704,
    360.0 * 0x1.0p736,
    360.0 * 0x1.0p768,
    360.0 * 0x1.0p800,
    360.0 * 0x1.0p832,
    360.0 * 0x1.0p864,
    360.0 * 0x1.0p896,
    360.0 * 0x1.0p928,
    360.0 * 0x1.0p960,
    360.0 * 0x1.0p992,
};

double tmpl_Double_Mod_360(double x)
{
    tmpl_IEEE754_Double w, tmp;
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

    n = (w.bits.expo - TMPL_DOUBLE_UBIAS - 8U)/32U + 1U;

    for (; n != 0U; --n)
        w.r -= my_360_arr[n-1U]*tmpl_Double_Floor(w.r / my_360_arr[n-1U]);

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
