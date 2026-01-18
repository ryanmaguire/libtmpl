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
 *      Splits a number into two parts and returns the high word. See         *
 *      include/split/tmpl_high_split_ldouble.h for details.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 28, 2024                                               *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  Function prototype / forward declaration. Double-double is implemented    *
 *  differently than the other representations and has a different signature. */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

extern long double
tmpl_LDouble_High_Split(const long double x, const double splitter);

/*  All other versions are treated in a similar manner to float and double.   */
#else

extern long double
tmpl_LDouble_High_Split(const long double x, const long double splitter);

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE.                */

/*  Implemented in include/split/tmpl_high_split_ldouble.h.                   */
#include "../../include/inline/split/tmpl_high_split_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
