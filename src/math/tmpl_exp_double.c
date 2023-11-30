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
 *                              tmpl_exp_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = e^x at double precision.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp                                                       *
 *  Purpose:                                                                  *
 *      Computes the base e exponential of a real number.                     *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential of x.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Exp_Maclaurin:                                    *
 *                  Computes exp(x) via a Maclaurin series for |x| < 1/16.    *
 *              tmpl_Double_Exp_Remez:                                        *
 *                  Computes exp(x) via a Remez polynomial for |x| < 1/4.     *
 *              tmpl_Double_Exp_Pade:                                         *
 *                  Computes exp(x) with a Pade approximant for |x| < 1.      *
 *              tmpl_Double_Exp_Neg_Kernel:                                   *
 *                  Computes exp(x) for negative x with x <= -1.              *
 *              tmpl_Double_Exp_Pos_Kernel:                                   *
 *                  Computes exp(x) for positive x with x >= 1.               *
 *      Method:                                                               *
 *          For very small x, |x| < 1/16, use a Maclaurin series.             *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \      1   n                                        *
 *              exp(x) =  /     --- x                                         *
 *                        -----  n!                                           *
 *                        n = 0                                               *
 *                                                                            *
 *          For slightly larger x, |x| < 1/4, use a Minimax polynomial on     *
 *          the interval [-1/4, 1/4]. The coefficients were computed using    *
 *          the Remez exchange algorithm.                                     *
 *                                                                            *
 *          For |x| < 1 use a Pade approximant.                               *
 *                                                                            *
 *                        a0 + a1 x + ... + an x^n                            *
 *              exp(x) ~= ------------------------                            *
 *                         1 + b1 x + ... + bm x^m                            *
 *                                                                            *
 *          For |x| > log(DBL_MAX) ~= 709, use the limit.                     *
 *                                                                            *
 *              exp(+inf) = +inf                                              *
 *              exp(-inf) = 0                                                 *
 *                                                                            *
 *          For x = +/- NaN, return x. Lastly, for 1 <= |x| <= log(DBL_MAX)   *
 *          perform the following:                                            *
 *                                                                            *
 *              exp(x) = exp(k*ln(2) + r)           k integer, |r| < ln(2)/2  *
 *                     = exp(k*ln(2)) * exp(r)                                *
 *                     = 2^k * exp(r)                                         *
 *                     = 2^k * exp(n/128 + t)       n integer, |t| < 1/128    *
 *                     = 2^k * exp(n/128) * exp(t)                            *
 *                                                                            *
 *          2^k can be computed by setting the exponent bit to k, exp(n/128)  *
 *          is computed with a lookup table, and exp(t) is computed using a   *
 *          minimax polynomial on the interval [-1/128, 1/128]. The           *
 *          coefficients were again computed using the Remez exchange         *
 *          algorithm. Note the coefficients for the minimax polynomial for   *
 *          exp on [-1/128, 1/128] differ from the ones on [-1/4, 1/4].       *
 *      Error:                                                                *
 *          Based on 2,244,604,859 samples with -700 < x < 700.               *
 *              max relative error: 6.0259536545328452e-16                    *
 *              rms relative error: 9.7044236080734406e-17                    *
 *              max absolute error: 2.4363285028499998e+288                   *
 *              rms absolute error: 1.8029986755465275e+286                   *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16).                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Is_NaN:                                           *
 *                  Determines if a real number is NaN.                       *
 *              tmpl_Double_Is_Inf:                                           *
 *                  Determines if a real number is infinity.                  *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Double_Exp_Maclaurin:                                    *
 *                  Computes exp(x) via a Maclaurin series for |x| < 1/16.    *
 *              tmpl_Double_Exp_Remez:                                        *
 *                  Computes exp(x) via a Remez polynomial for |x| < 1/4.     *
 *              tmpl_Double_Exp_Pade:                                         *
 *                  Computes exp(x) with a Pade approximant for |x| < 1.      *
 *              tmpl_Double_Exp_Neg_Kernel:                                   *
 *                  Computes exp(x) for negative x with x <= -1.              *
 *              tmpl_Double_Exp_Pos_Kernel:                                   *
 *                  Computes exp(x) for positive x with x >= 1.               *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but determine the range of x by          *
 *          computing |x| and comparing this value with 1/16, 1/4, etc.       *
 *      Error:                                                                *
 *          Based on 2,244,604,859 samples with -700 < x < 700.               *
 *              max relative error: 6.0259536545328452e-16                    *
 *              rms relative error: 9.7044236080734406e-17                    *
 *              max absolute error: 2.4363285028499998e+288                   *
 *              rms absolute error: 1.8029986755465275e+286                   *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16).                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 30, 2023                                              *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_exp_maclaurin_double.h"

/*  Remez minimax polynomial found here.                                      */
#include "auxiliary/tmpl_exp_remez_double.h"

/*  Pade approximation for exp for |x| < 1.                                   */
#include "auxiliary/tmpl_exp_pade_double.h"

/*  With IEEE-754 support we can get a bit of a speed boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing e^x at double precision (exp equivalent).          */
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
        return x;
    }

    /*  For |x| < 1/4 use one of two polynomial approximations.               */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS - 2U)
    {
        /*  For very small x, the Maclaurin series uses less terms.           */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 4U)
            return tmpl_Double_Exp_Maclaurin(x);

        /*  Otherwise, for |x| < 1/4 the minimax polynomial is accurate.      */
        return tmpl_Double_Exp_Remez(x);
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

    return tmpl_Double_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Double_Exp.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing e^x at double precision (exp equivalent).          */
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
            return x;
    }

    /*  Compute |x| to reduce the number of comparisons made. We want to find *
     *  the range |x| lives in and use the appropriate exp function.          */
    abs_x = tmpl_Double_Abs(x);

    /*  For |x| < 1/16 the Maclaurin series is accurate to double precision.  */
    if (abs_x < 0.0625)
        return tmpl_Double_Exp_Maclaurin(x);

    /*  For |x| < 1/4 the Remez minimax polynomial is fast and accurate.      */
    else if (abs_x < 0.25)
        return tmpl_Double_Exp_Remez(x);

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
