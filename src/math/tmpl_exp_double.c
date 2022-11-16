/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can get a bit of a speed boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Function for computing e^x at double precision.                           */
double tmpl_Double_Exp(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases, NaN or infinity.                                       */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, so is the output.                            */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  The limit of exp(x) as x tends to -infinity is zero.              */
        else if (w.bits.sign)
            return 0.0;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return tmpl_Double_Abs(x);
    }

    /*  For |x| < 1/16 the Maclaurin series is accurate to double precision.  */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
        return tmpl_Double_Exp_Maclaurin(x);

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS)
        return tmpl_Double_Exp_Pade(x);

    /*  Special cases, if |x| > log(DBL_MAX) we will overflow or underflow.   */
    else if (w.r > tmpl_Max_Double_Base_E)
        return TMPL_INFINITY;

    /*  For large negative numbers, return zero.                              */
    else if (w.r < tmpl_Min_Double_Base_E)
        return 0.0;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (w.bits.sign)
        return tmpl_Double_Exp_Neg_Kernel(x);
    else
        return tmpl_Double_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Double_Exp.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Function for computing e^x at double precision.                           */
double tmpl_Double_Exp(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double abs_x;

    /*  Special cases, Not-a-Number, return NaN.                              */
    if (tmpl_Double_Is_NaN(x))
        return x;

    /*  Next special cases, +/- infinity.                                     */
    else if (tmpl_Double_Is_Inf(x))
    {
        /*  The limit of exp(x) as x tends to -infinity is 0.                 */
        if (x < 0.0)
            return 0.0;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return tmpl_Double_Abs(x);
    }

    /*  Compute |x| to reduce the number of comparisons made. We want to find *
     *  the range |x| lives in and use the appropriate exp function.          */
    abs_x = tmpl_Double_Abs(x);

    /*  For |x| < 1/16 the Maclaurin series is accurate to double precision.  */
    if (abs_x < 0.0625)
        return tmpl_Double_Exp_Maclaurin(x);

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (abs_x < 1.0)
        return tmpl_Double_Exp_Pade(x);

    /*  Special cases, if |x| > log(DBL_MAX) we will overflow or underflow.   */
    else if (abs_x > tmpl_Max_Double_Base_E)
        return TMPL_INFINITY;

    /*  For large negative numbers, return zero.                              */
    else if (abs_x < tmpl_Min_Double_Base_E)
        return 0.0;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (x < 0.0)
        return tmpl_Double_Exp_Neg_Kernel(x);
    else
        return tmpl_Double_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Double_Exp.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
