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
 *                             tmpl_arcsin_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-sine function at long double precision.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin                                                   *
 *  Purpose:                                                                  *
 *      Computes asin(x), the inverse sine function.                          *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          The arc-sine of x.                                                *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Arcsin_Pade (tmpl_math.h):                           *
 *              Computes asin(x) via a Pade approximant for |x| < 0.5.        *
 *          tmpl_LDouble_Arcsin_Tail_End (tmpl_math.h):                       *
 *              Computes asin(x) for 0.5 <= x < 1.0.                          *
 *      Method:                                                               *
 *          For small x, |x| < 0.5, use a Pade approximant. For 0.5 <= x < 1  *
 *          use the reflection formula:                                       *
 *                                                                            *
 *              asin(x) = pi/2 - 2*asin(sqrt((1-x)/2))                        *
 *                                                                            *
 *          Compute this using a Pade approximant. For values -1 < x <= -0.5  *
 *          use the negation formula:                                         *
 *                                                                            *
 *              asin(x) = -acos(-x)                                           *
 *                                                                            *
 *          Use this and compute asin(-x) via the tail-end function.          *
 *          For |x| > 1 return NaN, and lastly the special cases of x = +/- 1 *
 *          return asin(-1) = -pi/2 and acos(1) = pi/2.                       *
 *      Error (64-bit Double):                                                *
 *          Based on 788,968,857 samples with -1 < x < 1.                     *
 *              max relative error: 2.2204459059627917e-16                    *
 *              rms relative error: 8.3796804351081161e-17                    *
 *              max absolute error: 4.4408920985006262e-16                    *
 *              rms absolute error: 1.4737238548161158e-16                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-16).                                    *
 *      Error (80-bit Extended):                                              *
 *          Based on 394,484,428 samples with -1 < x < 1.                     *
 *              max relative error: 2.1646973539415815e-19                    *
 *              rms relative error: 4.0762969454067788e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 6.9155008767105195e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
 *      Error (128-bit Quadruple):                                            *
 *          Based on 10,000,000 samples with -1 < x < 1.                      *
 *              max relative error: 2.1493423806776799e-34                    *
 *              rms relative error: 7.1883692991558038e-35                    *
 *              max absolute error: 1.9259299443872359e-34                    *
 *              rms absolute error: 5.3481009953614647e-35                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~2 x 10^-34).                                    *
 *      Error (128-bit Double-Double):                                        *
 *          Based on 10,000,000 samples with -1 < x < 1.                      *
 *              max relative error: 4.8287083179936863e-32                    *
 *              rms relative error: 5.8808472000117189e-33                    *
 *              max absolute error: 7.0874221953450279e-32                    *
 *              rms absolute error: 9.0797583993958255e-33                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~5 x 10^-32).                                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_LDouble_Abs (tmpl_math.h):                                   *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_LDouble_Arcsin_Pade (tmpl_math.h):                           *
 *              Computes asin(x) via a Pade approximant for |x| < 0.5.        *
 *          tmpl_LDouble_Arcsin_Tail_End (tmpl_math.h):                       *
 *              Computes asin(x) for 0.5 <= x < 1.0.                          *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 0.5 and 1.0.                                       *
 *      Error:                                                                *
 *          Based on 394,484,428 samples with -1 < x < 1.                     *
 *              max relative error: 2.1646973539415815e-19                    *
 *              rms relative error: 4.0762969454067788e-20                    *
 *              max absolute error: 2.1684043449710089e-19                    *
 *              rms absolute error: 6.9155008767105195e-20                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-19).                                    *
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

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  long double rather than checking the entire input. This gives the         *
 *  IEEE-754 method a slight performance boost over the portable one below.   */

/*  Long double precision inverse sine (asinl equivalent).                    */
long double tmpl_LDouble_Arcsin(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS - 1U)
        return tmpl_LDouble_Arcsin_Pade(x);

    /*  For |x| < 1 use the tail formula asin(x) = pi/2 - 2asin(sqrt(1-x)/2). */
    else if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_LDOUBLE_UBIAS)
    {
        /*  For negative inputs use the formula asin(x) = -asin(-x).          */
        if (TMPL_LDOUBLE_IS_NEGATIVE(w))
            return -tmpl_LDouble_Arcsin_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        else
            return tmpl_LDouble_Arcsin_Tail_End(x);
    }

    /*  Special cases, |x| >= 1 or x = NaN.                                   */
    else
    {
        /*  asin(-1) = -pi/2 and asin(1) = pi/2. Use this.                    */
        if (x == -1.0L)
            return -tmpl_Pi_By_Two_L;
        else if (x == 1.0L)
            return tmpl_Pi_By_Two_L;

        /*  For a real input, asin(x) is undefined with |x| > 1. Return NaN.  *
         *  Note, this catches NaN and infinity since we are checking the     *
         *  exponent of the input, not the input. For x = NaN or Inf, the     *
         *  exponent is greater than TMPL_LDOUBLE_UBIAS, so NaN will return.  */
        else
            return TMPL_NANL;
    }
}
/*  End of tmpl_LDouble_Arcsin.                                               */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision inverse sine (asinl equivalent).                    */
long double tmpl_LDouble_Arcsin(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const long double abs_x = tmpl_LDouble_Abs(x);

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (abs_x < 0.5L)
        return tmpl_LDouble_Arcsin_Pade(x);

    /*  Otherwise use the tail formula asin(x) = pi/2 - 2asin(sqrt(1-x)/2).   */
    else if (abs_x < 1.0L)
    {
        /*  For negative inputs use the formula asin(x) = -acos(-x).          */
        if (x < 0.0L)
            return -tmpl_LDouble_Arcsin_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        else
            return tmpl_LDouble_Arcsin_Tail_End(abs_x);
    }

    /*  Special cases, |x| >= 1 or x = NaN. Note, since comparison with       *
     *  NaN always returns false, an input of NaN will end up on this branch. */
    else
    {
        /*  asin(-1) = -pi/2 and asin(1) = pi/2. Use this.                    */
        if (x == -1.0L)
            return -tmpl_Pi_By_Two_L;
        else if (x == 1.0L)
            return tmpl_Pi_By_Two_L;

        /*  For |x| > 1 the function is undefined. Return NaN.                */
        else
            return TMPL_NANL;
    }
}
/*  End of tmpl_LDouble_Arcsin.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
