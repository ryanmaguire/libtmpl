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
 *                             tmpl_arccos_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at double precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos                                                    *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Arccos_Maclaurin:                                 *
 *                  Computes acos via a Maclaurin series for |x| < 0.125.     *
 *              tmpl_Double_Arccos_Rat_Remez:                                 *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Double_Arccos_Tail_End:                                  *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          For very small x, |x| < 2^-57, return pi / 2. For slightly larger *
 *          x, |x| < 0.125, use a Maclaurin series. For 0.125 <= |x| < 0.5    *
 *          use a minimax approximation. For 0.5 <= x < 1 use the             *
 *          reflection formula:                                               *
 *                                                                            *
 *              acos(x) = 2*asin(sqrt((1-x)/2))                               *
 *                                                                            *
 *          Compute this using a minimax approximation. For values            *
 *          -1 < x <= -0.5 use the negation formula:                          *
 *                                                                            *
 *              acos(x) = pi - acos(-x)                                       *
 *                                                                            *
 *          Use this and compute acos(-x) via the tail-end function.          *
 *          For |x| > 1 return NaN, and lastly the special cases of x = +/- 1 *
 *          return acos(-1) = pi and acos(1) = 0.                             *
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917e-16                    *
 *              rms relative error: 8.3796804351081161e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.4737238548161158e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Double_Abs:                                              *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Double_Arccos_Maclaurin:                                 *
 *                  Computes acos via a Maclaurin series for |x| < 0.125.     *
 *              tmpl_Double_Arccos_Rat_Remez:                                 *
 *                  Computes acos via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Double_Arccos_Tail_End:                                  *
 *                  Computes acos(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 0.5 and 1.0.                                       *
 *      Error:                                                                *
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917e-16                    *
 *              rms relative error: 8.3796804351081161e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.4737238548161158e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *  Notes:                                                                    *
 *      The only distinction between the IEEE-754 method and the portable one *
 *      is how the size of the input x is determined. The IEEE-754 method     *
 *      examines the exponent of the input, the portable method computes the  *
 *      absolute value and compares the size of x directly with the numbers   *
 *      0.5 and 1.0. The IEEE-754 method is hence slightly faster on most     *
 *      computers.                                                            *
 *                                                                            *
 *      Both methods detect if the input is NaN or infinity. The IEEE-754     *
 *      detects NaN and Inf since the exponents of NaN and Inf are large, and *
 *      the portable method detects NaN since NaN should always evaluate      *
 *      false when a comparison is made (==, <, >, etc.).                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 03, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/13: Ryan Maguire                                                  *
 *      Added comments, algorithm description, and fixed error values.        *
 *  2023/05/31: Ryan Maguire                                                  *
 *      Added optimizations for small x, |x| < 0.125, and denormal values.    *
 *  2024/10/28: Ryan Maguire                                                  *
 *      Replacing use of const variables with macros for multiples of pi.     *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/******************************************************************************
 *                         Static / Inlined Functions                         *
 ******************************************************************************/

/*  Maclaurin expansion provided here.                                        */
#include "auxiliary/tmpl_arccos_maclaurin_double.h"

/*  Rational Remez minimax approximation for arccos.                          */
#include "auxiliary/tmpl_arccos_rat_remez_double.h"

/*  Tail-end arccos function that uses the reflection formula with arcsin.    */
#include "auxiliary/tmpl_arccos_tail_end_double.h"

/******************************************************************************
 *                              Constant Values                               *
 ******************************************************************************/

/*  The limit at zero is pi / 2, and the negation formula needs pi as well.   */
#define TMPL_ONE_PI (+3.14159265358979323846264338327950288419716939937511E+00)
#define TMPL_PI_BY_TWO (+1.57079632679489661923132169163975144209858469969E+00)

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  double rather than checking the entire double. This gives the IEEE-754    *
 *  method a slight performance boost over the portable one below.            */

/*  Double precision inverse cosine (acos equivalent).                        */
double tmpl_Double_Arccos(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Small inputs, |x| < 0.5.                                              */
    if (w.bits.expo < TMPL_DOUBLE_UBIAS - 1U)
    {
        /*  For |x| < 2^-57, acos(x) = pi / 2 to double precision.            */
        if (w.bits.expo < TMPL_DOUBLE_UBIAS - 57U)
            return TMPL_PI_BY_TWO;

        /*  For small x, |x| < 2^-3, the Maclaurin series is sufficient.      */
        else if (w.bits.expo < TMPL_DOUBLE_UBIAS - 3U)
            return tmpl_Double_Arccos_Maclaurin(x);

        /*  For 0.125 <= |x| < 0.5 use the minimax approximation.             */
        return tmpl_Double_Arccos_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (w.bits.expo < TMPL_DOUBLE_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (w.bits.sign)
            return TMPL_ONE_PI - tmpl_Double_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Double_Arccos_Tail_End(x);
    }

    /*  acos(-1) = pi and acos(1) = 0. Use this.                              */
    if (x == -1.0)
        return TMPL_ONE_PI;
    else if (x == 1.0)
        return 0.0;

    /*  For a real input, acos(x) is undefined with |x| > 1. Return NaN. Note *
     *  this catches NaN and infinity since we are checking the exponent of   *
     *  the input, not the input. For x = NaN or Inf, the exponent is greater *
     *  than TMPL_DOUBLE_UBIAS, hence NaN will return.                        */
    return TMPL_NAN;
}
/*  End of tmpl_Double_Arccos.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Double precision inverse cosine (acos equivalent).                        */
double tmpl_Double_Arccos(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const double abs_x = tmpl_Double_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5)
    {
        /*  For very small inputs return pi / 2.                              */
        if (abs_x < 6.938893903907228E-18)
            return TMPL_PI_BY_TWO;

        /*  Small inputs, |x| < 0.125, use the Maclaurin series.              */
        else if (abs_x < 0.125)
            return tmpl_Double_Arccos_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_Double_Arccos_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (abs_x < 1.0)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0)
            return TMPL_ONE_PI - tmpl_Double_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Double_Arccos_Tail_End(abs_x);
    }

    /*  acos(-1) = pi and acos(1) = 0. Use this.                              */
    if (x == -1.0)
        return TMPL_ONE_PI;
    else if (x == 1.0)
        return 0.0;

    /*  For |x| > 1 the function is undefined. Return NaN.                    */
    return TMPL_NAN;
}
/*  End of tmpl_Double_Arccos.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_ONE_PI
#undef TMPL_PI_BY_TWO

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
