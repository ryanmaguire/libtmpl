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
 *                             tmpl_arcsin_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-sine function at single precision.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arcsin                                                     *
 *  Purpose:                                                                  *
 *      Computes asin(x), the inverse sine function.                          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (float):                                                       *
 *          The arc-sine of x.                                                *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Arcsin_Maclaurin:                                  *
 *                  Computes asin(x) via a Maclaurin series.                  *
 *              tmpl_Float_Arcsin_Rat_Remez:                                  *
 *                  Computes asin via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Float_Arcsin_Tail_End:                                   *
 *                  Computes asin(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          For very small x, |x| < 2^-26, return x. For slightly larger x,   *
 *          |x| < 0.125, use a Maclaurin series. For 0.125 <= |x| < 0.5 use a *
 *          minimax approximation. For 0.5 <= x < 1 use the reflection        *
 *          formula:                                                          *
 *                                                                            *
 *              asin(x) = pi/2 - 2*asin(sqrt((1-x)/2))                        *
 *                                                                            *
 *          Compute this using a minimax approximation. For values            *
 *          -1 < x <= -0.5 use the negation formula:                          *
 *                                                                            *
 *              asin(x) = -asin(-x)                                           *
 *                                                                            *
 *          Use this and compute asin(-x) via the tail-end function.          *
 *          For |x| > 1 return NaN, and lastly the special cases of x = +/- 1 *
 *          return asin(-1) = -pi/2 and asin(1) = pi/2.                       *
 *      Error:                                                                *
 *          Based on 4,495,446,834 samples with -1 < x < 1.                   *
 *              max relative error: 2.2767265761558519e-07                    *
 *              rms relative error: 4.2472893065347384e-08                    *
 *              max absolute error: 1.1920928955078125e-07                    *
 *              rms absolute error: 4.2472893065347384e-08                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a real number.             *
 *              tmpl_Float_Arcsin_Maclaurin:                                  *
 *                  Computes asin(x) via a Maclaurin series.                  *
 *              tmpl_Float_Arcsin_Rat_Remez:                                  *
 *                  Computes asin via a minimax approximation for |x| < 0.5.  *
 *              tmpl_Float_Arcsin_Tail_End:                                   *
 *                  Computes asin(x) for 0.5 <= x < 1.0.                      *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 0.5 and 1.0.                                       *
 *      Error:                                                                *
 *          Based on 4,495,446,834 samples with -1 < x < 1.                   *
 *              max relative error: 2.2767265761558519e-07                    *
 *              rms relative error: 4.2472893065347384e-08                    *
 *              max absolute error: 1.1920928955078125e-07                    *
 *              rms absolute error: 4.2472893065347384e-08                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
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
 *  Date:       May 9, 2023                                                   *
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
#include <libtmpl/include/math/tmpl_arcsin_maclaurin_float.h>

/*  Rational remez minimax approximation for arcsin.                          */
#include <libtmpl/include/math/tmpl_arcsin_rat_remez_float.h>

/*  Tail-end arcsin function that uses the reflection formula with arccos.    */
#include <libtmpl/include/math/tmpl_arcsin_tail_end_float.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  float rather than checking the entire float. This gives the IEEE-754      *
 *  method a slight performance boost over the portable one below.            */

/*  Single precision inverse sine (asinf equivalent).                         */
float tmpl_Float_Arcsin(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  Small inputs, |x| < 0.5.                                              */
    if (w.bits.expo < TMPL_FLOAT_UBIAS - 1U)
    {
        /*  For |x| < 2^-26, asin(x) = x to single precision.                 */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 26U)
            return x;

        /*  For small x, |x| < 2^-3, the Maclaurin series is sufficient.      */
        else if (w.bits.expo < TMPL_FLOAT_UBIAS - 3U)
            return tmpl_Float_Arcsin_Maclaurin(x);

        /*  For 0.125 <= |x| < 0.5 use the minimax approximation.             */
        return tmpl_Float_Arcsin_Rat_Remez(x);
    }

    /*  For |x| < 1 use the tail formula asin(x) = pi/2 - 2asin(sqrt(1-x)/2). */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS)
    {
        /*  For negative inputs use the formula asin(x) = -asin(-x).          */
        if (w.bits.sign)
            return -tmpl_Float_Arcsin_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Float_Arcsin_Tail_End(x);
    }

    /*  asin(-1) = -pi/2 and asin(1) = pi/2. Use this.                        */
    if (x == -1.0F)
        return -tmpl_Pi_By_Two_F;
    else if (x == 1.0F)
        return tmpl_Pi_By_Two_F;

    /*  For a real input, asin(x) is undefined with |x| > 1. Return NaN. Note *
     *  this catches NaN and infinity since we are checking the exponent of   *
     *  the input, not the input. For x = NaN or Inf, the exponent is greater *
     *  than TMPL_FLOAT_UBIAS, hence NaN will return.                         */
    return TMPL_NANF;
}
/*  End of tmpl_Float_Arcsin.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision inverse sine (asinf equivalent).                         */
float tmpl_Float_Arcsin(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const float abs_x = tmpl_Float_Abs(x);

    /*  Small inputs, |x| < 0.5.                                              */
    if (abs_x < 0.5F)
    {
        /*  For very small inputs return x, asin(x) = x + O(x^3).             */
        if (abs_x < 1.4901161193847656E-08F)
            return x;

        /*  Small inputs, |x| < 0.125, use the Maclaurin series.              */
        else if (abs_x < 0.125F)
            return tmpl_Float_Arcsin_Maclaurin(x);

        /*  Otherwise use the Remez rational minimax function.                */
        return tmpl_Float_Arcsin_Rat_Remez(x);
    }

    /*  For |x| < 1 use the formula asin(x) = pi/2 - 2asin(sqrt(1-x)/2).      */
    else if (abs_x < 1.0F)
    {
        /*  For negative inputs use the formula asin(x) = -asin(-x).          */
        if (x < 0.0F)
            return -tmpl_Float_Arcsin_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        return tmpl_Float_Arcsin_Tail_End(abs_x);
    }

    /*  asin(-1) = -pi/2 and asin(1) = pi/2. Use this.                        */
    if (x == -1.0F)
        return -tmpl_Pi_By_Two_F;
    else if (x == 1.0F)
        return tmpl_Pi_By_Two_F;

    /*  For |x| > 1 the function is undefined. Return NaN.                    */
    return TMPL_NANF;
}
/*  End of tmpl_Float_Arcsin.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
