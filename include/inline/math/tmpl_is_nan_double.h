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
 *                             tmpl_is_nan_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is Not-a-Number.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Is_NaN                                                    *
 *  Purpose:                                                                  *
 *      Determines if the input is NaN.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan (tmpl_Bool):                                                   *
 *          Boolean for if x is not-a-number.                                 *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Check if the bits correspond to NaN. IEEE-754 states that NaN     *
 *          occurs when all exponent bits are 1 and not all mantissa bits are *
 *          0. The sign can be 0 or 1.                                        *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          If IEEE-754 is not available, a portable way to check is by       *
 *          comparing x == x. NaN evaluates false whenever a comparison is    *
 *          made, so if x == x is false we have a NaN.                        *
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
 *  2023/06/13: Ryan Maguire                                                  *
 *      Added inline support. Changed src/math/tmpl_is_nan_double.c to        *
 *      include this file.                                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IS_NAN_DOUBLE_H
#define TMPL_IS_NAN_DOUBLE_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/tmpl_ieee754_double.h>

/*  Check for IEEE-754 support. This is the easiest way to work with NaN.     */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number (isnan equivalent).      */
TMPL_INLINE_DECL
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  The TMPL_DOUBLE_IS_NOT_A_NUMBER macro checks the bits to see if the   *
     *  word represents a NaN. Use this.                                      */
    if (TMPL_DOUBLE_IS_NOT_A_NUMBER(w))
        return tmpl_True;

    /*  Otherwise we have a regular (possibly infinite) number.               */
    return tmpl_False;
}
/*  End of tmpl_Double_Is_NaN.                                                */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number (isnan equivalent).      */
TMPL_INLINE_DECL
tmpl_Bool tmpl_Double_Is_NaN(double x)
{
    /*  The compiler will see this as x == x, which for normal values will    *
     *  always return true. It may try to optimize this code away. For        *
     *  NaN values, x == x will return false, whereas for all other values    *
     *  it will return true. To prevent the compiler from optimizing          *
     *  out this code, declare y as "volatile".                               */
    const volatile double y = x;

    /*  NaN evaluates false whenever a comparison is made.                    */
    if (x == y)
        return tmpl_False;

    /*  If x == x is false, the input is Not-a-Number. Return true.           */
    return tmpl_True;
}
/*  End of tmpl_Double_Is_NaN.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of include guard.                                                     */
