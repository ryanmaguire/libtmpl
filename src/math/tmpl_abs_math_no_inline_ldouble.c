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
 *                              tmpl_abs_ldouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes |x|. Source: libtmpl/include/inline/math/tmpl_abs_ldouble.h. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************/

/*  Location of the TMPL_USE_MATH_ALGORITHMS macro.                           */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if libtmpl algorithms are requested and inline support is not.  */
#if TMPL_USE_INLINE != 1 && TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype / forward declaration.                                 */
extern long double tmpl_LDouble_Abs(long double x);

/*  Implemented here.                                                         */
#include "../../include/inline/math/tmpl_abs_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1 && TMPL_USE_MATH_ALGORITHMS == 1.         */
