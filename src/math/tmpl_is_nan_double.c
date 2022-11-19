/******************************************************************************
 *                                 LICENSE                                    *
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
 *                              tmpl_is_nan                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Is_NaN:                                                    *
 *      tmpl_Double_Is_NaN:                                                   *
 *      tmpl_LDouble_Is_NaN:                                                  *
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan.                                   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan (tmpl_Bool):                                                   *
 *          Boolean for if x is +/- nan.                                      *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, check if the bits correspond to     *
 *      +/- NaN. IEEE-754 states NaN is when all exponent bits are            *
 *      1 and some of the mantissa bits are 1. The sign can be zero or 1.     *
 *                                                                            *
 *      If IEEE-754 is not available, a portable way to check is by comparing *
 *      x == x. This returns true for numbers, and false for NaN.             *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_Bool.h:                                                          *
 *          Header containing Booleans.                                       *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 21, 2021                                              *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototypes here.                                                 */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This is the easiest way to work with nan.     */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number.                         */
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part to the input.                                     */
    w.r = x;

    /*  NaN for IEEE-754 is exponent set to all 1's and the mantissa set to   *
     *  zeros and ones . The sign can be 0 or 1 for +/- nan.                  */
    if (w.bits.expo == 0x7FFU &&
        (w.bits.man0 != 0x00U ||
         w.bits.man1 != 0x00U ||
         w.bits.man2 != 0x00U ||
         w.bits.man3 != 0x00U))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_Double_Is_NaN.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number.                         */
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return true. To prevent the compiler from optimizing          *
     *  out this code, declare y as "volatile".                               */
    volatile double y = x;

    /*  If x == y, x is a number. Otherwise, it is NaN.                       */
    if (x == y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_Double_Is_NaN.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
