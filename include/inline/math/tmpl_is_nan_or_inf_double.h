/******************************************************************************
 *                                   LICENSE                                  *
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
 *                          tmpl_is_nan_or_inf_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Is_NaN_Or_Inf                                             *
 *  Purpose:                                                                  *
 *      Determines if the input is +/- nan or inf.                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan_or_inf (tmpl_Bool):                                            *
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
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_Bool.h:                                                          *
 *          Header containing Booleans.                                       *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IS_NAN_OR_INF_DOUBLE_H
#define TMPL_IS_NAN_OR_INF_DOUBLE_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Check for IEEE-754 support. This is the easiest way to work with nan/inf. */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number or infinity.             */
TMPL_INLINE_DECL
tmpl_Bool tmpl_Double_Is_NaN_Or_Inf(double x)
{
    /*  Declare a variable for the IEEE-754 double object.                    */
    tmpl_IEEE754_Double w;

    /*  Set the double part to the input.                                     */
    w.r = x;

    /*  NaN / Inf for IEEE-754 has the exponent set to all 1's and the        *
     *  mantissa set to zeros and ones . The sign can be 0 or 1. We can use   *
     *  the macro TMPL_DOUBLE_IS_NAN_OR_INF to check for this.                */
    if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return tmpl_True;

    /*  Otherwise the input is an ordinary real number.                       */
    return tmpl_False;
}
/*  End of tmpl_Double_Is_NaN_Or_Inf.                                         */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for testing if a double is Not-A-Number or inf.                  */
TMPL_INLINE_DECL
tmpl_Bool tmpl_Double_Is_NaN_Or_Inf(double x)
{
    /*  The compiler may optimize this away since it may think x - x = 0 must *
     *  always be true. This is true of real numbers, but for NaN and inf     *
     *  this returns false. Declare y as volatile to prevent agressive        *
     *  optimization.                                                         */
    volatile double y = x;

    /*  If x - x evaluates to NaN for x = infinity and x = NaN. It returns 0  *
     *  for all other doubles.                                                */
    if ((x - y) == 0.0)
        return tmpl_False;

    /*  If the difference is non-zero, the input was not a real number.       */
    return tmpl_True;
}
/*  End of tmpl_Double_Is_NaN_Or_Inf.                                         */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of include guard.                                                     */
