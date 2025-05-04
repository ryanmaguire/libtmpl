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
 *                       tmpl_two_vector_l2_norm_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Square of the 2D Euclidean norm. Source:                              *
 *      libtmpl/include/inline/vec2/tmpl_vec2_l2_norm_squared_ldouble.h.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  2D Vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function prototype / forward declaration.                                 */
extern long double
tmpl_2DLDouble_L2_Norm_Squared(const tmpl_TwoVectorLongDouble * const P);

/*  Implemented here.                                                         */
#include "../../include/inline/vec2/tmpl_vec2_l2_norm_squared_ldouble.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
