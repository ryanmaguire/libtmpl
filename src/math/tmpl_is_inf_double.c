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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 21, 2021                                              *
 ******************************************************************************/

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Function prototypes here.                                                 */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This is the easiest way to work with inf.     */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_Double_Is_Inf(double x)
{
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
}
/*  End of tmpl_Double_Is_Inf.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for testing if a double is +/- infinity.                         */
tmpl_Bool tmpl_Double_Is_Inf(double x)
{
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
}
/*  End of tmpl_Double_Is_Inf.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */
