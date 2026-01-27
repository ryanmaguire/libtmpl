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
 *                              tmpl_erf_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the error function at double precision.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf                                                       *
 *  Purpose:                                                                  *
 *      Computes the error function of a real number.                         *
 *                                                                            *
 *                               x                                            *
 *                               -                                            *
 *                      2       | |                                           *
 *          erf(x) = --------   |   exp(-t^2) dt                              *
 *                   sqrt(pi) | |                                             *
 *                             -                                              *
 *                              0                                             *
 *                                                                            *
 *      The Taylor series always converges and provides another definition:   *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                      2      \        (-1)^n                                *
 *          erf(x) = --------  /      ----------- * x^{2n+1}                  *
 *                   sqrt(pi)  -----  (2n + 1) n!                             *
 *                             n = 0                                          *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for erf(x).                           *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function evaluated at x.                                *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Erf_Asymptotic:                                   *
 *                  Computes erf(x) for positive x >= 2.                      *
 *              tmpl_Double_Erf_Maclaurin:                                    *
 *                  Computes erf(x) via a Maclaurin series.                   *
 *              tmpl_Double_Erf_Rat_Remez_Small:                              *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *              tmpl_Double_Erf_Rat_Remez:                                    *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *      Method:                                                               *
 *          Reduce x to being positive since erf is odd, erf(x) = -erf(-x).   *
 *          Determine the range of the input and use one of several methods.  *
 *                                                                            *
 *              0.000 <= x < 0.125 -> Maclaurin series.                       *
 *              0.125 <= x < 1.000 -> Small Remez approximation.              *
 *              1.000 <= x < 2.000 -> Remez approximation.                    *
 *              2.000 <= x < Infty -> Asymptotic expansion.                   *
 *                                                                            *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Double_Erf_Asymptotic:                                   *
 *                  Computes erf(x) for positive x >= 2.                      *
 *              tmpl_Double_Erf_Maclaurin:                                    *
 *                  Computes erf(x) via a Maclaurin series.                   *
 *              tmpl_Double_Erf_Rat_Remez_Small:                              *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *              tmpl_Double_Erf_Rat_Remez:                                    *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but check that range of x by computing   *
 *          the absolute value and comparing this with 0.125, 1, and 2.       *
 *  Error:                                                                    *
 *      For both methods, based on 1,051,958,476 samples with -6 < x < 6.     *
 *          max relative error: 6.6943042473314486e-16                        *
 *          rms relative error: 1.0656006428956785e-16                        *
 *          max absolute error: 6.6613381477509392e-16                        *
 *          rms absolute error: 9.4395719349921919e-17                        *
 *      Values assume 100% accuracy of glibc. Actual error in glibc is        *
 *      around 1 ULP (~2 x 10^-16). A comparison with arbitrary               *
 *      precision erf routines show the peak relative error to be 1 ULP.      *
 *      For |x| > 6 both glibc and libtmpl return erf(x) = +/- 1.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 20, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/19: Ryan Maguire                                                  *
 *      Changed algorithm. No longer uses libcerf. Improved precision.        *
 *  2024/02/25: Ryan Maguire                                                  *
 *      Changed Chebyshev polynomial to rational Remez approximation.         *
 ******************************************************************************/

/*  Header file where the prototype of the function is given.                 */
#include <libtmpl/include/tmpl_math.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_erf_maclaurin_double.h"

/*  Rational Remez approximations for erf.                                    */
#include "auxiliary/tmpl_erf_small_double.h"

/*  Computes erf(x) for 1 <= x < 2.                                           */
#include "auxiliary/tmpl_erf_medium_double.h"

/*  Error function for large positive values.                                 */
#include "auxiliary/tmpl_erf_large_double.h"

/*  With IEEE-754 support we get a slight speed boost checking the range.     */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing the error function at double precision.            */
double tmpl_Double_Erf(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases, NaN or Infinity.                                       */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, return NaN.                                  */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  Otherwise use the limit. erf(x) -> +/- 1 as x -> +/- infty.       */
        if (TMPL_DOUBLE_IS_NEGATIVE(w))
            return -1.0;

        /*  Positive infinity, the limit is +1.                               */
        return 1.0;
    }

    /*  For small values use various polynomial and rational approximations.  */
    else if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS + 1U)
    {
        /*  For very small, |x| < 0.125, use a Maclaurin series.              */
        if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS - 3U)
            return tmpl_Double_Erf_Maclaurin(x);

        /*  For |x| < 1 use a rational Remez approximation with a few terms.  */
        else if (TMPL_DOUBLE_EXPO_BITS(w) < TMPL_DOUBLE_UBIAS)
            return tmpl_Double_Erf_Small(x);

        /*  For |x| < 2 use a several Remez approximations. Since erf is odd  *
         *  return -erf(-x) for negative inputs.                              */
        if (TMPL_DOUBLE_IS_NEGATIVE(w))
        {
            w.bits.sign = 0x00U;
            return -tmpl_Double_Erf_Medium(w);
        }

        /*  Positive input, use the same Remez polynomials.                   */
        return tmpl_Double_Erf_Medium(w);
    }

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x).                              */
    if (TMPL_DOUBLE_IS_NEGATIVE(w))
        return -tmpl_Double_Erf_Large(-x);

    /*  Compute Erf(x) for x >= 2.                                            */
    return tmpl_Double_Erf_Large(x);
}
/*  End of tmpl_Double_Erf.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing the error function at double precision.            */
double tmpl_Double_Erf(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Special cases, NaN or Infinity.                                       */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
    {
        /*  If the input is NaN, return NaN.                                  */
        if (tmpl_Double_Is_NaN(x))
            return x;

        /*  Otherwise use the limit. erf(x) -> +/- 1 as x -> +/- infty.       */
        if (x > 0.0)
            return 1.0;

        /*  Negative infinity, the limit is -1.                               */
        return -1.0;
    }

    /*  For small values use a Maclaurin series.                              */
    else if (abs_x < 0.125)
        return tmpl_Double_Erf_Maclaurin(x);

    /*  For |x| < 1 use a rational Remez approximation with a few terms.      */
    else if (abs_x < 1.0)
        return tmpl_Double_Erf_Small(x);

    /*  For |x| < 2 use a larger rational Remez approximation.                */
    else if (abs_x < 2.0)
        return tmpl_Double_Erf_Medium(x);

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x).                              */
    else if (x < 0.0)
        return -tmpl_Double_Erf_Large(abs_x);

    /*  For large positive, use the asymptotics.                              */
    return tmpl_Double_Erf_Large(x);
}
/*  End of tmpl_Double_Erf.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
