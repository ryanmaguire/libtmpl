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
 *                     tmpl_math_complex_quick_abs_inline                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a faster version of the complex modulus function. This       *
 *      does not check if the inputs have very large or very small magnitudes *
 *      and may result in overflow or underflow. For reasonably sized complex *
 *      numbers this works well and fast.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file containing complex types.                             *
 *  3.) tmpl_math.h:                                                          *
 *          Header file containing square root functions. Only included if    *
 *          libtmpl math algorithms requested.                                *
 *  4.) math.h:                                                               *
 *          Standard library header file. This contains square root functions.*
 *          Only included if libtmpl math algorithms are not requested.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 8, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_COMPLEX_QUICK_ABS_INLINE_H
#define TMPL_MATH_COMPLEX_QUICK_ABS_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  Complex data types and function prototypes found here.                    */
#include <libtmpl/include/tmpl_complex.h>

static inline float tmpl_CFloat_QuickAbs(tmpl_ComplexFloat z)
{
    return tmpl_Float_Sqrt(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

static inline double tmpl_CDouble_QuickAbs(tmpl_ComplexDouble z)
{
    return tmpl_Double_Sqrt(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

static inline long double tmpl_CLDouble_QuickAbs(tmpl_ComplexLongDouble z)
{
    return tmpl_LDouble_Sqrt(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
