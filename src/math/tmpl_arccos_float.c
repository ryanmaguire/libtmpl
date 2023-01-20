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
 *                             tmpl_arccos_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-cosine function at single precision.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos                                                     *
 *  Purpose:                                                                  *
 *      Computes acos(x), the inverse cosine function.                        *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The arc-cosine of x.                                              *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Arccos_Pade (tmpl_math.h):                             *
 *              Computes acos(x) via a Pade approximant for |x| < 0.5.        *
 *          tmpl_Float_Arccos_Tail_End (tmpl_math.h):                         *
 *              Computes acos(x) for 0.5 <= x < 1.0.                          *
 *      Method:                                                               *
 *          For small x, |x| < 0.5, use a Pade approximant. For 0.5 <= x < 1  *
 *          use the reflection formula:                                       *
 *                                                                            *
 *              acos(x) = 2*asin(sqrt((1-x)/2))                               *
 *                                                                            *
 *          Compute this using a Pade approximant. For values -1 < x <= -0.5  *
 *          use the negation formula:                                         *
 *                                                                            *
 *              acos(x) = pi - acos(-x)                                       *
 *                                                                            *
 *          Use this and compute acos(-x) via the tail-end function.          *
 *          For |x| > 1 return NaN, and lastly the special cases of x = +/- 1 *
 *          return acos(-1) = pi and acos(1) = 0.                             *
 *      Error:                                                                *
 *          Based on 1,577,937,714 samples with -1 < x < 1.                   *
 *              max relative error: 1.1920928955078125e-07                    *
 *              rms relative error: 5.0596198794068018e-08                    *
 *              max absolute error: 2.3841857910156250e-07                    *
 *              rms absolute error: 9.1275731819690602e-08                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          less than 1 ULP (~1 x 10^-7).                                     *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Abs (tmpl_math.h):                                     *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_Float_Arccos_Pade (tmpl_math.h):                             *
 *              Computes acos(x) via a Pade approximant for |x| < 0.5.        *
 *          tmpl_Float_Arccos_Tail_End (tmpl_math.h):                         *
 *              Computes acos(x) for 0.5 <= x < 1.0.                          *
 *      Method:                                                               *
 *          Similar to the IEEE-754 version, but determine the size of the    *
 *          input using the absolute value function and comparing the output  *
 *          to the numbers 0.5 and 1.0.                                       *
 *      Error:                                                                *
 *          Based on 1,577,937,714 samples with -1 < x < 1.                   *
 *              max relative error: 1.1920928955078125e-07                    *
 *              rms relative error: 5.0596198794068018e-08                    *
 *              max absolute error: 2.3841857910156250e-07                    *
 *              rms absolute error: 9.1275731819690602e-08                    *
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
 *  Date:       January 03, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/13: Ryan Maguire                                                  *
 *      Added comments, algorithm description, and fixed error values.        *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support.                                               */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  On most computers it is faster to check the value of the exponent of a    *
 *  float rather than checking the entire float. This gives the IEEE-754      *
 *  method a slight performance boost over the portable one below.            */

/*  Single precision inverse cosine (acosf equivalent).                       */
float tmpl_Float_Arccos(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input.                          */
    w.r = x;

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (w.bits.expo < TMPL_FLOAT_UBIAS - 1U)
        return tmpl_Float_Arccos_Pade(x);

    /*  For |x| < 1 use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).    */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (w.bits.sign)
            return tmpl_One_Pi_F - tmpl_Float_Arccos_Tail_End(-x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        else
            return tmpl_Float_Arccos_Tail_End(x);
    }

    /*  Special cases, |x| >= 1 or x = NaN.                                   */
    else
    {
        /*  acos(-1) = pi and acos(1) = 0. Use this.                          */
        if (x == -1.0F)
            return tmpl_One_Pi_F;
        else if (x == 1.0F)
            return 0.0F;

        /*  For a real input, acos(x) is undefined with |x| > 1. Return NaN.  *
         *  Note, this catches NaN and infinity since we are checking the     *
         *  exponent of the input, not the input. For x = NaN or Inf, the     *
         *  exponent is greater than TMPL_FLOAT_UBIAS, hence NaN will return. */
        else
            return TMPL_NANF;
    }
}
/*  End of tmpl_Float_Arccos.                                                 */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision inverse cosine (acosf equivalent).                       */
float tmpl_Float_Arccos(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    const float abs_x = tmpl_Float_Abs(x);

    /*  For |x| < 0.5 use the Pade approximant.                               */
    if (abs_x < 0.5F)
        return tmpl_Float_Arccos_Pade(x);

    /*  Otherwise use the tail end formula acos(x) = 2asin(sqrt(1-x)/2).      */
    else if (abs_x < 1.0F)
    {
        /*  For negative inputs use the formula acos(x) = pi - acos(-x).      */
        if (x < 0.0F)
            return tmpl_One_Pi_F - tmpl_Float_Arccos_Tail_End(abs_x);

        /*  Otherwise use the tail-end function for 0.5 <= x < 1.             */
        else
            return tmpl_Float_Arccos_Tail_End(abs_x);
    }

    /*  Special cases, |x| >= 1 or x = NaN. Note, since comparison with       *
     *  NaN always returns false, an input of NaN will end up on this branch. */
    else
    {
        /*  acos(-1) = pi and acos(1) = 0. Use this.                          */
        if (x == -1.0F)
            return tmpl_One_Pi_F;
        else if (x == 1.0F)
            return 0.0F;

        /*  For |x| > 1 the function is undefined. Return NaN.                */
        else
            return TMPL_NANF;
    }
}
/*  End of tmpl_Float_Arccos.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
