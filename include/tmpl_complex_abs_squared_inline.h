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
 *                    tmpl_math_complex_abs_squared_inline                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inline version of the complex absolute value squared.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header file containing complex types.                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_COMPLEX_ABS_SQUARED_INLINE_H
#define TMPL_MATH_COMPLEX_ABS_SQUARED_INLINE_H

/*  Complex data types declared here.                                         */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision abs squared function.                                    */
static inline float tmpl_CFloat_Abs_Squared(tmpl_ComplexFloat z)
{
    /*  Use the Pythagorean formula |z|^2 = x^2 + y^2 and return.             */
    return z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1];
}
/*  End of tmpl_CFloat_Abs_Squared.                                           */

/*  Double precision abs squared function.                                    */
static inline double tmpl_CDouble_Abs_Squared(tmpl_ComplexDouble z)
{
    /*  Use the Pythagorean formula |z|^2 = x^2 + y^2 and return.             */
    return z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1];
}
/*  End of tmpl_CDouble_Abs_Squared.                                          */

/*  Long double precision abs squared function.                               */
static inline long double tmpl_CLDouble_Abs_Squared(tmpl_ComplexLongDouble z)
{
    /*  Use the Pythagorean formula |z|^2 = x^2 + y^2 and return.             */
    return z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1];
}
/*  End of tmpl_CLDouble_Abs_Squared.                                         */

#endif
/*  End of include guard.                                                     */
