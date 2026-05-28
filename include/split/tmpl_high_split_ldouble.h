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
 *                           tmpl_high_split_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inlined splitting function, or a forward declaration if   *
 *      inline support is not available.                                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 28, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SPLIT_HIGH_SPLIT_LDOUBLE_H
#define TMPL_SPLIT_HIGH_SPLIT_LDOUBLE_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Split is small enough that it should be inlined. Check for support.       */
#if TMPL_USE_INLINE == 1

/*  Implemented in the inline directory.                                      */
#include <libtmpl/include/inline/split/tmpl_high_split_ldouble.h>

/*  Lacking inline support, provide the forward declaration to the compiler.  */
#else

/*  Double-Double is split differently than the other implementations. Since  *
 *  double-double is literally two doubles together, the splitting factor is  *
 *  of type "double" instead of "long double."                                */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Function for splitting a double-double into two parts using a             *
 *  double-precision splitter. The high part is returned.                     */
TMPL_CONST_FUNC
extern long double
tmpl_LDouble_High_Split(const long double x, const double splitter)
TMPL_UNSEQUENCED;

/*  All other versions are treated in a similar manner to float and double.   */
#else

/*  Function for splitting a long double into two parts. The high part        *
 *  is returned.                                                              */
TMPL_CONST_FUNC
extern long double
tmpl_LDouble_High_Split(const long double x, const long double splitter)
TMPL_UNSEQUENCED;

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE.                */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
