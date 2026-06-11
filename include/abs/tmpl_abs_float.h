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
 *                               tmpl_abs_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined abs function, or a forward declaration if inline  *
 *      support is not available.                                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_MATH_ALGORITHMS and TMPL_USE_INLINE macros. *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides optional C23 attributes for optimization.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 24, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ABS_ABS_FLOAT_H
#define TMPL_ABS_ABS_FLOAT_H

/*  The TMPL_USE_MATH_ALGORITHMS and TMPL_USE_INLINE macros are found here.   */
#include <libtmpl/include/tmpl_config.h>

/*  Only provided if the user requested libtmpl's libm implementation.        */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  abs function is small enough that it can be inlined. Check for support.   */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/math/tmpl_abs_impl_float.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function for computing the absolute value at single precision.            */
TMPL_CONST_FUNC
extern float tmpl_Float_Abs(const float x)
TMPL_UNSEQUENCED;

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS == 1.                               */

/*  If the user wants to use their system's libm, simply create a macro.      */
#include <math.h>

#define tmpl_Float_Abs fabsf

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

#endif
/*  End of include guard.                                                     */
