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

/*  TMPL_USE_MATH_ALGORITHMS macro found here.                                */
#include <libtmpl/include/tmpl_config.h>

/*  Use tmpl algorithms, or use the functions in math.h.                      */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

#define square_rootf tmpl_Float_Sqrt
#define square_root tmpl_Double_Sqrt
#define square_rootl tmpl_LDouble_Sqrt

/*  tmpl algorithms not requested. Use libm functions.                        */
#else

/*  Square root functions found here.                                         */
#include <math.h>

/*  If inline support is available, sqrtf and sqrtl should be as well since   *
 *  these are all C99 extensions.                                             */
#define square_rootf sqrtf
#define square_root sqrt
#define square_rootl sqrtl

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */

static inline float tmpl_CFloat_QuickAbs(tmpl_ComplexFloat z)
{
    return square_rootf(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

static inline double tmpl_CDouble_QuickAbs(tmpl_ComplexDouble z)
{
    return square_root(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

static inline long double tmpl_CLDouble_QuickAbs(tmpl_ComplexLongDouble z)
{
    return square_rootl(z.dat[0]*z.dat[0] + z.dat[1]*z.dat[1]);
}

/*  Undefine these macro in case someone wants to include this file elsewhere.*/
#undef square_rootf
#undef square_root
#undef square_rootl

#endif
/*  End of include guard.                                                     */
