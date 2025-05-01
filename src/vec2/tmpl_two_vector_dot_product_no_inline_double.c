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
 *                     tmpl_two_vector_dot_product_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      2D Euclidean dot product. Source:                                     *
 *      libtmpl/include/inline/vec2/tmpl_two_vector_dot_product_double.h.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************/

/*  Location of the TMPL_USE_MATH_ALGORITHMS macro.                           */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if libtmpl algorithms are requested and inline support is not.  */
#if TMPL_USE_INLINE != 1

/*  2D Vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function prototype / forward declaration.                                 */
extern double
tmpl_2DDouble_Dot_Product(const tmpl_TwoVectorDouble * const P,
                          const tmpl_TwoVectorDouble * const Q);

/*  Implemented here.                                                         */
#include "../../include/inline/vec2/tmpl_two_vector_dot_product_double.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
