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
 *                              tmpl_is_inf                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is +/- infinity.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Is_Inf:                                                    *
 *      tmpl_Double_Is_Inf:                                                   *
 *      tmpl_LDouble_Is_Inf:                                                  *
 *  Purpose:                                                                  *
 *      Determines if the input is +/- infinity.                              *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_inf (tmpl_Bool):                                                   *
 *          Boolean for if x is +/- infinity.                                 *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, check if the bits correspond to     *
 *      +/- infinity. IEEE-754 states infinity is when all exponent bits are  *
 *      1 and all mantissa bits are 0. The sign can be zero or 1.             *
 *                                                                            *
 *      If IEEE-754 is not available, a portable way to check is by comparing *
 *      x + x == x. This will return True in 3 cases: x = 0, x = +infinity,   *
 *      and x = -infinity. Checking if x + x == x and if x != 0 suffices.     *
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

/*  Function for testing if a float is +/- infinity.                          */
tmpl_Bool tmpl_Float_Is_Inf(float x)
{
    /*  Check for IEEE-754. This is the easiest way check for infinity.       */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

    /*  Declare a variable for the IEEE-754 float object.                     */
    tmpl_IEEE754_Float w;

    /*  Set the float part to the input.                                      */
    w.r = x;

    /*  Infinity for IEEE-754 is exponent set to all 1's and the mantissa set *
     *  to all zeros. The sign can be 0 or 1 for +/- infinity.                */
    if (w.bits.expo == 0xFFU && w.bits.man0 == 0x0U && w.bits.man1 == 0x0U)
        return tmpl_True;
    else
        return tmpl_False;
#else
/*  Else #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1   */

    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for float. x == x + x avoids this      *
     *  problem. To avoid the compiler trying to optimize this code away,     *
     *  declare y as volatile.                                                */
    volatile float y = x + x;

    /*  If x == x + x, then either x = 0 or x = +/- infinity.                 */
    if (x == y && x != 0.0F)
        return tmpl_True;
    else
        return tmpl_False;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

}
/*  End of tmpl_Float_Is_Inf.                                                 */

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_Double_Is_Inf(double x)
{
    /*  Check for IEEE-754 support. This is the easiest way to work with inf. */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part to the input.                                     */
    w.r = x;

    /*  Infinity for IEEE-754 is exponent set to all 1's and the mantissa set *
     *  to all zeros. The sign can be 0 or 1 for +/- infinity.                */
    if (w.bits.expo == 0x7FFU &&
        w.bits.man0 == 0x00U &&
        w.bits.man1 == 0x00U &&
        w.bits.man2 == 0x00U &&
        w.bits.man3 == 0x00U)
        return tmpl_True;
    else
        return tmpl_False;
#else
/*  For #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for float. x == x + x avoids this      *
     *  problem. To avoid the compiler trying to optimize this code away,     *
     *  declare y as volatile.                                                */
    volatile double y = x + x;

    /*  If x == x + x, then either x = 0 or x = +/- infinity.                 */
    if (x == y && x != 0.0)
        return tmpl_True;
    else
        return tmpl_False;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

}
/*  End of tmpl_Double_Is_Inf.                                                */

/*  Function for testing if a long double is +/- infinity.                    */
tmpl_Bool tmpl_LDouble_Is_Inf(long double x)
{
    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for long double. x == x + x avoids     *
     *  this. To avoid the compiler trying to optimize this code away,        *
     *  declare y as volatile.                                                */
    volatile long double y = x + x;

    /*  If x == x + x, then either x = 0 or x = +/- infinity.                 */
    if (x == y && x != 0.0L)
        return tmpl_True;
    else
        return tmpl_False;
}
/*  End of tmpl_LDouble_Is_Inf.                                               */
