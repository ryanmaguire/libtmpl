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
 *                          tmpl_is_nan_or_inf                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Is_NaN_Or_Inf:                                             *
 *      tmpl_Double_Is_NaN_Or_Inf:                                            *
 *      tmpl_LDouble_Is_NaN_Or_Inf:                                           *
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan/inf.                               *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan (tmpl_Bool):                                                   *
 *          Boolean for if x is +/- nan/inf.                                  *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, check if the bits correspond to     *
 *      +/- NaN/Inf. IEEE-754 states NaN or Inf is when all exponent bits are *
 *      1. The mantissa values can be anything, depending on whether the      *
 *      value is NaN, inf, sNaN, or qNaN.                                     *
 *                                                                            *
 *      If IEEE-754 is not available, a portable way to check is by comparing *
 *      x == x. This returns true for numbers, and false for NaN. For inf we  *
 *      check if x != x + x.                                                  *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2022                                              *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototypes here.                                                 */
#include <libtmpl/include/tmpl_math.h>

/*  Function for testing if a float is Not-A-Number.                          */
tmpl_Bool tmpl_Float_Is_NaN_Or_Inf(float x)
{
    /*  Check for IEEE-754. This is the easiest way check for NaN.            */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

    /*  Declare a variable for the IEEE-754 float object.                     */
    tmpl_IEEE754_Float w;

    /*  Set the float part to the input.                                      */
    w.r = x;

    /*  NaN/Inf for IEEE-754 is exponent set to all 1's. The sign can be +/-. */
    if (w.bits.expo == 0xFFU)
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

    /*  If x == y, x is a number. Otherwise, it is NaN. x != y + y is not     *
     *  infinity. x == y + y is infinity. Check this cases.                   */
    if ((x == y) && (x != y + y))
        return tmpl_False;
    else
        return tmpl_True;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

}
/*  End of tmpl_Float_Is_NaN_Or_Inf.                                          */

/*  Function for testing if a double is Not-A-Number.                         */
tmpl_Bool tmpl_Double_Is_NaN_Or_Inf(double x)
{
    /*  Check for IEEE-754 support. This is the easiest way to work with nan. */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part to the input.                                     */
    w.r = x;

    /*  NaN for IEEE-754 is exponent set to all 1's and the mantissa set to   *
     *  zeros and ones . The sign can be 0 or 1 for +/- nan.                  */
    if (w.bits.expo == 0x7FFU)
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

    /*  If x == y, x is a number. Otherwise, it is NaN. x != y + y is not     *
     *  infinity. x == y + y is infinity. Check this cases.                   */
    if ((x == y) && (x != y + y))
        return tmpl_False;
    else
        return tmpl_True;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

}
/*  End of tmpl_Double_Is_NaN.                                                */

/*  Function for testing if a long double is Not-A-Number.                    */
tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x)
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

