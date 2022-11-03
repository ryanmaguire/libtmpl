/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                              tmpl_cosh_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes hyperbolic cosine at double precision.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cosh                                                      *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic cosine of a number.                           *
 *                                                                            *
 *                     exp(x) + exp(-x)                                       *
 *          cosh(x) =  ----------------                                       *
 *                            2                                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for cosh(x).                          *
 *  Output:                                                                   *
 *      cosh_x (double):                                                      *
 *          The hyperbolic cosine of x.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Abs (tmpl_math.h):                                    *
 *              Computes the absolute value of a double.                      *
 *      Method:                                                               *
 *      Error:                                                                *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Exp (tmpl_math.h):                                    *
 *              Computes the exponential of a double.                         *
 *      Method:                                                               *
 *          Compute t = exp(x) and return (t + 1/t)/2.                        *
 *      Error:                                                                *
 *  Notes:                                                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 10, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/10 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 *  2022/11/03 (Ryan Maguire):                                                *
 *      Migrated to libtmpl from rss_ringoccs. Updated with IEEE-754 method.  *
 ******************************************************************************/

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support. Bit of a speed boost this way.                */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Coefficients for the polynomial approximation of x(exp(x)+1)/(exp(x)-1).  */
#define A1 (1.666666666666666666666666666666666666667E-01)
#define A2 (-2.777777777777777777777777777777777777778E-03)
#define A3 (6.613756613756613756613756613756613756614E-05)
#define A4 (-1.653439153439153439153439153439153439153E-06)
#define A5 (4.175351397573619795842018064240286462509E-08)

/*  Double precision hyperbolic cosine (cosh equivalent).                     */
double tmpl_Double_Cosh(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w, exp_w;
    double t, t2, r, hi, lo;
    unsigned int k;

    /*  Set the double part of the union to the input.                        */
    w.r = tmpl_Double_Abs(x);

    /*  +/- NaN returns NaN, for +/- infinity the limit is + infinity.        */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return w.r;

    /*  For |x| > log(DBL_MAX) ~= 709, exp will overflow. Return infinity.    */
    else if (w.r > 709.0895657128241)
        return TMPL_INFINITY;

    /*  For small x, |x| < 1/32, the Maclaurin series is sufficient.          */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 5U)
        return tmpl_Double_Cosh_Maclaurin(w.r);

    /*  For slightly larger x, |x| < 1, use the Pade approximant.             */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS)
        return tmpl_Double_Cosh_Pade(w.r);

    /*  Normal value, not too small, not too big. Compute exp(x).             */
    else
    {
        /*  log(2) split into two components for extra precision.             */
        static const double ln_2_hi = 6.93147180369123816490e-01;
        static const double ln_2_lo = 1.90821492927058770002e-10;

        /*  Reciprocal of log(2). Low part not needed.                        */
        static const double rcpr_ln_2 = 1.44269504088896338700e+00;

        /*  Compute the correctly rounded down integer part of |x|/log(2).    */
        k = (unsigned int)(rcpr_ln_2*w.r + 0.5);
        t = (double)k;

        /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).        *
         *  exp(r) is computed via a Taylor series for the function           *
         *  f(r) = r*(exp(r) + 1)/(exp(r) - 1) and solving for exp(r) in      *
         *  terms of f(r).                                                    */
        hi = w.r - ln_2_hi*t;
        lo = t*ln_2_lo;
        t = hi - lo;
        t2 = t*t;

        /*  Rational approximation of exp(t) for small t.                     */
        r = t - t2*(A1 + t2*(A2 + t2*(A3 + t2*(A4 + t2*A5))));
        t = 1.0 - ((lo - (t*r)/(2.0 - r)) - hi);

        /*  Compute exp(x) via 2^k * exp(t).                                  */
        exp_w.r = t;
        exp_w.bits.expo += k & 0x7FF;

        /*  For large x only the e^x term is significant. e^-x is negligible. */
        if (w.bits.expo > TMPL_DOUBLE_UBIAS + 5U)
            return 0.5*exp_w.r;

        /*  Otherwise, compute cosh(x) via (exp(x) + exp(-x))/2.             */
        else
            return 0.5*(exp_w.r + 1.0/exp_w.r);
    }
}
/*  End of tmpl_Double_Cosh.                                                  */

/*  Undefine all coefficients in case someone wants to #include this file.    */
#undef A1
#undef A2
#undef A3
#undef A4

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Double precision hyperbolic cosine (cosh equivalent).                     */
double tmpl_Double_Cosh(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double exp_x, exp_minus_x;

    /*  The definition of cosh(x) is [exp(x) + exp(-x)]/2, so return this. It *
     *  is computationally faster to compute exp(x) and then exp(-x) via the  *
     *  formula exp(-x) = 1/exp(x). This saves us from computing two          *
     *  exponentials at the cost of an extra division.                        */
    exp_x = tmpl_Double_Exp(x);
    exp_minus_x = 1.0/exp_x;

    /*  Compute cosh from the two exponentials and return.                    */
    return 0.5*(exp_x + exp_minus_x);
}
/*  End of tmpl_Double_Cosh.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
