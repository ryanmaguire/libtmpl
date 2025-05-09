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
 *                   tmpl_two_vector_hadamard_divide_double                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      2D Hadamard component-wise division. Source:                          *
 *      libtmpl/include/inline/vec2/tmpl_vec2_hadamard_divide_double.h.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2025                                                   *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  2D Vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_TwoVectorDouble
tmpl_2DDouble_Hadamard_Divide(const tmpl_TwoVectorDouble * const P,
                              const tmpl_TwoVectorDouble * const Q);

/*  Implemented here.                                                         */
#include "../../include/inline/vec2/tmpl_vec2_hadamard_divide_double.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
