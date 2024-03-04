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
 *                              tmpl_erf_float                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the error function at single precision.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Erf                                                        *
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
 *      x (float):                                                            *
 *          A real number, the argument for erf(x).                           *
 *  Output:                                                                   *
 *      erf_x (float):                                                        *
 *          The error function evaluated at x.                                *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Erf_Asymptotic:                                    *
 *                  Computes erf(x) for positive x >= 2.                      *
 *              tmpl_Float_Erf_Maclaurin:                                     *
 *                  Computes erf(x) via a Maclaurin series.                   *
 *              tmpl_Float_Erf_Chebyshev:                                     *
 *                  Computes erf(x) via a Chebyshev polynomial.               *
 *              tmpl_Float_Erf_Rat_Remez:                                     *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *      Method:                                                               *
 *          Reduce x to being positive since erf is odd, erf(x) = -erf(-x).   *
 *          Determine the range of the input and use one of several methods.  *
 *                                                                            *
 *              0.000 <= x < 0.125 -> Maclaurin series.                       *
 *              0.125 <= x < 1.000 -> Chebyshev polynomial.                   *
 *              1.000 <= x < 2.000 -> Remez approximation.                    *
 *              2.000 <= x < Infty -> Asymptotic expansion.                   *
 *                                                                            *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Float_Erf_Asymptotic:                                    *
 *                  Computes erf(x) for positive x >= 2.                      *
 *              tmpl_Float_Erf_Maclaurin:                                     *
 *                  Computes erf(x) via a Maclaurin series.                   *
 *              tmpl_Float_Erf_Chebyshev:                                     *
 *                  Computes erf(x) via a Chebyshev polynomial.               *
 *              tmpl_Float_Erf_Rat_Remez:                                     *
 *                  Computes erf(x) via a rational minimax approximation.     *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but check that range of x by computing   *
 *          the absolute value and comparing this with 0.125, 1, and 2.       *
 *  Error:                                                                    *
 *      Both methods, based on 1,051,958,476 samples with -4 < x < 4.         *
 *          max relative error: 3.0144434504109086e-07                        *
 *          rms relative error: 6.8706228788198583e-08                        *
 *          max absolute error: 2.9802322387695312e-07                        *
 *          rms absolute error: 6.0286689634333076e-08                        *
 *      Values assume 100% accuracy of glibc. Actual error in glibc is        *
 *      around 1 ULP (~1 x 10^-7).                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 25, 2024                                             *
 ******************************************************************************/

/*  Header file where the prototype of the function is given.                 */
#include <libtmpl/include/tmpl_math.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_erf_maclaurin_float.h"

/*  Error function for large positive values.                                 */
#include "auxiliary/tmpl_erf_asymptotic_float.h"

/*  Rational Remez approximation for erf.                                     */
#include "auxiliary/tmpl_erf_rat_remez_float.h"

/*  Chebyshev expansion for the error function.                               */
#include "auxiliary/tmpl_erf_chebyshev_float.h"

/*  With IEEE-754 support we get a slight speed checking the range.           */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing the error function at single precision.            */
float tmpl_Float_Erf(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w, tmp;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases, NaN or Infinity.                                       */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, return NaN.                                  */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  Otherwise use the limit. erf(x) -> +/- 1 as x -> +/- infty.       */
        if (w.bits.sign)
            return -1.0F;

        /*  Positive infinity, the limit is +1.                               */
        return 1.0F;
    }

    /*  For small values use various polynomial and rational approximations.  */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS + 1U)
    {
        /*  For very small, |x| < 0.125, use a Maclaurin series.              */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 3U)
            return tmpl_Float_Erf_Maclaurin(x);

        /*  For |x| < 1 use a Chebyshev expansion.                            */
        else if (w.bits.expo < TMPL_FLOAT_UBIAS)
            return tmpl_Float_Erf_Chebyshev(x);

        /*  For |x| < 2 use a rational Remez approximation.                   */
        return tmpl_Float_Erf_Rat_Remez(x);
    }

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x). First, save the sign of x.   */
    tmp.bits.sign = w.bits.sign;

    /*  Compute |x| by setting the sign bit to zero.                          */
    w.bits.sign = 0x00U;

    /*  Compute Erf(|x|) for |x| >= 2.                                        */
    w.r = tmpl_Float_Erf_Asymptotic(w.r);

    /*  tmp has the original sign of the input. Restore this to the output.   */
    w.bits.sign = tmp.bits.sign;
    return w.r;
}
/*  End of tmpl_Float_Erf.                                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing the error function at single precision.            */
float tmpl_Float_Erf(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const float abs_x = tmpl_Float_Abs(x);

    /*  Special cases, NaN or Infinity.                                       */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
    {
        /*  If the input is NaN, return NaN.                                  */
        if (tmpl_Float_Is_NaN(x))
            return x;

        /*  Otherwise use the limit. erf(x) -> +/- 1 as x -> +/- infty.       */
        if (x > 0.0F)
            return 1.0F;

        /*  Negative infinity, the limit is -1.                               */
        return -1.0F;
    }

    /*  For small values use a Maclaurin series.                              */
    else if (abs_x < 0.125F)
        return tmpl_Float_Erf_Maclaurin(x);

    /*  For values |x| < 1 use a Chebyshev expansion.                         */
    else if (abs_x < 1.0F)
        return tmpl_Float_Erf_Chebyshev(x);

    /*  For |x| < 2 use a Remez approximation.                                */
    else if (abs_x < 2.0F)
        return tmpl_Float_Erf_Rat_Remez(x);

    /*  Lastly, for large negative values use the fact that erf(x) is odd.    *
     *  Use the asymptotic values with -erf(-x).                              */
    else if (x < 0.0F)
        return -tmpl_Float_Erf_Asymptotic(abs_x);

    /*  For large positive, use the asymptotics.                              */
    return tmpl_Float_Erf_Asymptotic(x);
}
/*  End of tmpl_Float_Erf.                                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
