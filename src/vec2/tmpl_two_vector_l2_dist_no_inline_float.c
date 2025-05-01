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
 *                       tmpl_two_vector_l2_dist_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      2D Euclidean distance.                                                *
 *      Source: libtmpl/include/inline/vec2/tmpl_two_vector_l2_dist_float.h.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 20, 2020                                            *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  2D Vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function prototype / forward declaration.                                 */
extern float
tmpl_2DFloat_L2_Dist(const tmpl_TwoVectorFloat * const P,
                     const tmpl_TwoVectorFloat * const Q);

/*  Implemented here.                                                         */
#include "../../include/inline/vec2/tmpl_two_vector_l2_dist_float.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
