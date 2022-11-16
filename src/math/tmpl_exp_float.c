/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can get a bit of a speed boost.                  */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Function for computing e^x at single precision.                           */
float tmpl_Float_Exp(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases, NaN or infinity.                                       */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, so is the output.                            */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  The limit of exp(x) as x tends to -infinity is zero.              */
        else if (w.bits.sign)
            return 0.0F;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return tmpl_Float_Abs(x);
    }

    /*  For |x| < 1/16 the Maclaurin series is accurate to single precision.  */
    if (w.bits.expo < TMPL_FLOAT_UBIAS - 3U)
        return tmpl_Float_Exp_Maclaurin(x);

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS)
        return tmpl_Float_Exp_Pade(x);

    /*  Special cases, if |x| > log(DBL_MAX) we will overflow or underflow.   */
    else if (w.r > tmpl_Max_Float_Base_E)
        return TMPL_INFINITYF;

    /*  For large negative numbers, return zero.                              */
    else if (w.r < tmpl_Min_Float_Base_E)
        return 0.0F;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (w.bits.sign)
        return tmpl_Float_Exp_Neg_Kernel(x);
    else
        return tmpl_Float_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Float_Exp.                                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Function for computing e^x at float precision.                            */
float tmpl_Float_Exp(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float abs_x;

    /*  Special cases, Not-a-Number, return NaN.                              */
    if (tmpl_Float_Is_NaN(x))
        return x;

    /*  Next special cases, +/- infinity.                                     */
    else if (tmpl_Float_Is_Inf(x))
    {
        /*  The limit of exp(x) as x tends to -infinity is 0.                 */
        if (x < 0.0F)
            return 0.0F;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return tmpl_Float_Abs(x);
    }

    /*  Compute |x| to reduce the number of comparisons made. We want to find *
     *  the range |x| lives in and use the appropriate exp function.          */
    abs_x = tmpl_Float_Abs(x);

    /*  For |x| < 1/16 the Maclaurin series is accurate to single precision.  */
    if (abs_x < 0.0625F)
        return tmpl_Float_Exp_Maclaurin(x);

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (abs_x < 1.0F)
        return tmpl_Float_Exp_Pade(x);

    /*  Special cases, if |x| > log(FLT_MAX) we will overflow or underflow.   */
    else if (x > tmpl_Max_Float_Base_E)
        return TMPL_INFINITYF;

    /*  For large negative numbers, return zero.                              */
    else if (x < tmpl_Min_Float_Base_E)
        return 0.0F;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (x < 0.0F)
        return tmpl_Float_Exp_Neg_Kernel(x);
    else
        return tmpl_Float_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Float_Exp.                                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
