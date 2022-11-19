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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2022                                              *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototypes here.                                                 */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This is the easiest way to work with nan/inf. */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Function for testing if a long double is Not-A-Number or inf.             */
tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x)
{
    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part to the input.                                */
    w.r = x;

    /*  NaN for IEEE-754 is exponent set to all 1's and the mantissa set to   *
     *  zeros and ones . The sign can be 0 or 1 for +/- nan.                  */
    if (TMPL_LDOUBLE_IS_NAN_OR_INF(w))
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_LDouble_Is_NaN_Or_Inf.                                        */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Function for testing if a long double is Not-A-Number or inf.             */
tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return true. To prevent the compiler from optimizing          *
     *  out this code, declare y as "volatile".                               */
    volatile long double y = x;

    /*  If x - x evaluates to NaN for x = infinity and x = NaN. It returns 0  *
     *  for all other long doubles.                                           */
    if ((x - y) == 0.0L)
        return tmpl_False;
    else
        return tmpl_True;
}
/*  End of tmpl_LDouble_Is_NaN.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */
