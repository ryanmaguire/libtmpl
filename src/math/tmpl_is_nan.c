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
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       October 21, 2021                                              *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototypes here.                                                 */
#include <libtmpl/include/tmpl_math.h>

/*  Function for testing if a float is Not-A-Number.                          */
tmpl_Bool tmpl_Float_Is_NaN(float x)
{
    /*  Check for IEEE-754. This is the easiest way check for NaN.            */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

    /*  Declare a variable for the IEEE-754 float object.                     */
    tmpl_IEEE754_Float w;

    /*  Set the float part to the input.                                      */
    w.r = x;

    /*  NaN for IEEE-754 is exponent set to all 1's and the mantissa set to   *
     *  zeros and ones . The sign can be 0 or 1 for +/- nan.                  */
    if (w.bits.expo == 0xFFU && (w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
        return tmpl_True;
    else
        return tmpl_False;
#else
/*  Else #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1   */

    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return true. To prevent the compiler from optimizing          *
     *  out this code, declare y as "volatile".                               */
    volatile float y = x;

    /*  If x == y, x is a number. Otherwise, it is NaN.                       */
    if (x == y)
        return tmpl_False;
    else
        return tmpl_True;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

}
/*  End of tmpl_Float_Is_NaN.                                                 */

/*  Function for testing if a double is Not-A-Number.                         */
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  Check for IEEE-754 support. This is the easiest way to work with nan. */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

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
#else

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
#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

}
/*  End of tmpl_Double_Is_NaN.                                                */

/*  Function for testing if a long double is Not-A-Number.                    */
tmpl_Bool tmpl_LDouble_Is_NaN(long double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return true. To prevent the compiler from optimizing          *
     *  out this code, declare y as "volatile".                               */
    volatile long double y = x;

    /*  If x == y, x is a number. Otherwise, it is NaN.                       */
    if (x == y)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_LDouble_Is_NaN.                                               */
