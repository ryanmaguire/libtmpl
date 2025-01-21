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
 *                            tmpl_is_inf_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is +/- infinity.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Is_Inf                                                   *
 *  Purpose:                                                                  *
 *      Determines if the input is +/- infinity.                              *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_inf (tmpl_Bool):                                                   *
 *          Boolean for if x is +/- infinity.                                 *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Check if the bits correspond to +/- infinity. IEEE-754 states     *
 *          infinity occurs when all exponent bits are 1 and all mantissa     *
 *          bits are 0. The sign can be 0 or 1, corresponding to positive     *
 *          and negative infinity, respectively.                              *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          If IEEE-754 is not available, a portable way to check is by       *
 *          comparing x + x == x. This will return True in 3 cases: x = 0,    *
 *          x = +infinity, and x = -infinity. Checking if x + x == x and if   *
 *          x != 0 suffices.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header containing Booleans.                                       *
 *  2.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL.                          *
 *  3.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 21, 2021                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/06/12: Ryan Maguire                                                  *
 *      Added inline support. Changed src/math/tmpl_is_inf_ldouble.c to       *
 *      include this file.                                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IS_INF_LDOUBLE_H
#define TMPL_IS_INF_LDOUBLE_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Check for IEEE-754 support. This is the easiest way to work with inf.     */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for testing if a long double is +/- infinity (isinfl equivalent).*/
TMPL_INLINE_DECL
tmpl_Bool tmpl_LDouble_Is_Inf(long double x)
{
    /*  Declare a variable for the IEEE-754 long double object.               */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  The TMPL_LDOUBLE_IS_INFINITY macro checks the bits to see if they     *
     *  correspond to infinity. Use this.                                     */
    if (TMPL_LDOUBLE_IS_INFINITY(w))
        return tmpl_True;

    /*  Otherwise we have a long double that is finite or NaN. Return false.  */
    return tmpl_False;
}
/*  End of tmpl_LDouble_Is_Inf.                                               */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for testing if a long double is +/- infinity (isinf equivalent). */
TMPL_INLINE_DECL
tmpl_Bool tmpl_LDouble_Is_Inf(long double x)
{
    /*  A portable way to check (without IEEE-754 support) is to see if       *
     *  x = x + x, and x is not zero. x == x + 1 is another way to check, but *
     *  this can return true for finite numbers if x is greater in magnitude  *
     *  than the precision implemented for long double. x == x + x avoids     *
     *  this problem. To avoid the compiler trying to optimize this code away,*
     *  declare y as volatile.                                                */
    const volatile long double y = x + x;

    /*  If x == x + x, then either x = 0 or x = +/- infinity.                 */
    if (x == y && x != 0.0L)
        return tmpl_True;

    /*  Otherwise we have a double that is finite or NaN. Return false.       */
    return tmpl_False;
}
/*  End of tmpl_LDouble_Is_Inf.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of include guard.                                                     */
