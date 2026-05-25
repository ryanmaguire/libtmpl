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
 *                              tmpl_abs_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined abs function, or a forward declaration if inline  *
 *      support is not available.                                             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 24, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ABS_ABS_DOUBLE_H
#define TMPL_ABS_ABS_DOUBLE_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  abs function is small enough that it can be inlined. Check for support.   */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/math/tmpl_abs_double.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*   Attributes to improve optimization on C23-compatible compilers.          */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
[[nodiscard]] [[reproducible]] [[unsequenced]] [[gnu::const]]
#endif

/*  Function for computing the absolute value at double precision.            */
extern double tmpl_Double_Abs(const double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
