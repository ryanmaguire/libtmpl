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
 *                       tmpl_positive_difference_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      See include/math/tmpl_positive_difference_float.h for details. This   *
 *      function computes max(x-y, 0). Equivalent to the C99 fdimf function.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2023                                                 *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE and TMPL_USE_MATH_ALGORITHMS macros.      */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if libtmpl algorithms are requested and inline support is not.  */
#if TMPL_USE_INLINE != 1 && TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Implemented in include/math/tmpl_positive_difference_float.h.             */
#include "../../include/inline/math/tmpl_positive_difference_float.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1 && TMPL_USE_MATH_ALGORITHMS == 1.         */
