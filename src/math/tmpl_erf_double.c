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
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function evaluated at x.                                *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Erf_Asymptotic (tmpl_math.h):                         *
 *              Computes erf(x) for positive x >= 2.                          *
 *          tmpl_Double_Erf_Chebyshev (tmpl_math.h):                          *
 *              Computes erf(x) via a Chebyshev expansion.                    *
 *          tmpl_Double_Erf_Maclaurin (tmpl_math.h):                          *
 *              Computes erf(x) via a Maclaurin series.                       *
 *          tmpl_Double_Erf_Pade (tmpl_math.h):                               *
 *              Computes erf(x) via a Pade approximant.                       *
 *      Method:                                                               *
 *          Reduce x to being positive since erf is odd, erf(x) = -erf(-x).   *
 *          Determine the range of the input, and use one of several methods. *
 *                                                                            *
 *              0.000 <= x < 0.125 -> Maclaurin Series.                       *
 *              0.125 <= x < 1.000 -> Chebyshev Expansion.                    *
 *              1.000 <= x < 2.000 -> Pade Approximant.                       *
 *              2.000 <= x < Infty -> Remez polynomial / asymptotic expansion.*
 *                                                                            *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -6 < x < 6.                   *
 *              max relative error: 6.7093746466560391e-16                    *
 *              rms relative error: 8.4931623078551750e-17                    *
 *              max absolute error: 6.6613381477509392e-16                    *
 *              rms absolute error: 7.4700568675692582e-17                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16). A comparison with arbitrary           *
 *          precision erf routines show the peak relative error to be 1 ULP.  *
 *          for this implementation.                                          *
 *                                                                            *
 *          For |x| > 6 both glibc and libtmpl return erf(x) = +/- 1.         *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Is_NaN_Or_Inf (tmpl_math.h):                          *
 *              Function for determining if a number is NaN or inf.           *
 *          tmpl_Double_Is_NaN (tmpl_math.h):                                 *
 *              Function for determining if a number is NaN.                  *
 *          tmpl_Double_Erf_Asymptotic (tmpl_math.h):                         *
 *              Computes erf(x) for positive x >= 2.                          *
 *          tmpl_Double_Erf_Chebyshev (tmpl_math.h):                          *
 *              Computes erf(x) via a Chebyshev expansion.                    *
 *          tmpl_Double_Erf_Maclaurin (tmpl_math.h):                          *
 *              Computes erf(x) via a Maclaurin series.                       *
 *          tmpl_Double_Erf_Pade (tmpl_math.h):                               *
 *              Computes erf(x) via a Pade approximant.                       *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but check that range of x by computing   *
 *          the absolute value and comparing this with 0.125, 1, and 2.       *
 *      Error:                                                                *
 *          Based on 1,051,958,476 samples with -6 < x < 6.                   *
 *              max relative error: 6.7093746466560391e-16                    *
 *              rms relative error: 8.4931623078551750e-17                    *
 *              max absolute error: 6.6613381477509392e-16                    *
 *              rms absolute error: 7.4700568675692582e-17                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16). A comparison with arbitrary           *
 *          precision erf routines show the peak relative error to be 1 ULP.  *
 *          for this implementation.                                          *
 *                                                                            *
 *          For |x| > 6 both glibc and libtmpl return erf(x) = +/- 1.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 20, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/19: Ryan Maguire                                                  *
 *      Changed algorithm. No longer uses libcerf. Improved precision.        *
 ******************************************************************************/

/*  Header file where the prototype of the function is given.                 */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we get a slight speed checking the range.           */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Function for computing the error function at double precision.            */
double tmpl_Double_Erf(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w, tmp;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases, NaN or Infinity.                                       */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, return NaN.                                  */
        if (TMPL_DOUBLE_IS_NAN(w))
            return x;

        /*  Otherwise use the limit. erf(x) -> +/- 1 as x -> +/- infty.       */
        if (w.bits.sign)
            return -1.0;
        else
            return 1.0;
    }

    /*  For small values use various polynomial and rational approximations.  */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS + 1U)
    {
        /*  For very small, |x| < 0.125, use a Maclaurin series.              */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 3U)
            return tmpl_Double_Erf_Maclaurin(x);

        /*  For values |x| < 1 use a Chebyshev expansion.                     */
        else if (w.bits.expo < TMPL_DOUBLE_UBIAS)
            return tmpl_Double_Erf_Chebyshev(x);

        /*  For |x| < 2 use a Pade approximant.                               */
        else
            return tmpl_Double_Erf_Pade(x);
    }

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x). First, save the sign of x.   */
    tmp.bits.sign = w.bits.sign;

    /*  Compute |x| by setting the sign bit to zero.                          */
    w.bits.sign = 0x00U;

    /*  Compute Erf(|x|) for |x| >= 2.                                        */
    w.r = tmpl_Double_Erf_Asymptotic(w.r);

    /*  tmp has the original sign of the input. Restore this to the output.   */
    w.bits.sign = tmp.bits.sign;
    return w.r;
}
/*  End of tmpl_Double_Erf.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

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
        else
            return -1.0;
    }

    /*  For small values use a Maclaurin series.                              */
    else if (abs_x < 0.125)
        return tmpl_Double_Erf_Maclaurin(x);

    /*  For values |x| < 1 use a Chebyshev expansion.                         */
    else if (abs_x < 1.0)
        return tmpl_Double_Erf_Chebyshev(x);

    /*  For |x| < 2 use a Pade approximant.                                   */
    else if (abs_x < 2.0)
        return tmpl_Double_Erf_Pade(x);

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x).                              */
    else if (x < 0.0)
        return -tmpl_Double_Erf_Asymptotic(-x);

    /*  For large positive, use the asymptotics.                              */
    else
        return tmpl_Double_Erf_Asymptotic(x);
}
/*  End of tmpl_Double_Erf.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
