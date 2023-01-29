/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can get a bit of a speed boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A00 (+9.9999999999999999988430264938382617864875775206464E-01)
#define A01 (+1.0000000000000002567155499064945764299110332942888E+00)
#define A02 (+5.0000000000000011303128565037818364883412745825979E-01)
#define A03 (+1.6666666666658450641538834111096804338714833792536E-01)
#define A04 (+4.1666666666648208299845851261960139340509395965848E-02)
#define A05 (+8.3333333406957231917106078391264123789847252849529E-03)
#define A06 (+1.3888888900173203766146657738825963558824828302470E-03)
#define A07 (+1.9841242914202268899999786488562084101590255844480E-04)
#define A08 (+2.4801555544629532354737090416957032661760944182686E-05)
#define A09 (+2.7600400233476040774827464572558357184830459675937E-06)
#define A10 (+2.7599120100813904758992842016718714757809673113599E-07)

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
            return x;
    }

    /*  For |x| < 1/16 the Maclaurin series is accurate to double precision.  */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS - 2U)
    {
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
            return tmpl_Double_Exp_Maclaurin(x);
        return A00+x*(A01+x*(A02+x*(A03+x*(A04+x*(A05+x*(A06+x*(A07+x*(A08+x*(A09+x*A10)))))))));
    }

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
