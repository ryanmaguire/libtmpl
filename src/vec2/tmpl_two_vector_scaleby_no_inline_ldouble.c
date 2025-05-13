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
 *                      tmpl_two_vector_scaleby_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      2D scalar multiplication in-place, *= operator.                       *
 *      Source: libtmpl/include/inline/vec2/tmpl_vec2_scaleby_ldouble.h.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2025                                                  *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  2D Vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function prototype / forward declaration.                                 */
extern void
tmpl_2DLDouble_ScaleBy(tmpl_TwoVectorLongDouble * const P, long double r);

/*  Implemented here.                                                         */
#include "../../include/inline/vec2/tmpl_vec2_scaleby_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
