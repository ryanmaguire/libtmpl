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
 *                     tmpl_affine_point_intercept_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates an affine transformation from a point and the y-intercept.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 3, 2026                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only used if inline support is not available.                             */
#if TMPL_USE_INLINE != 1

/*  tmpl_AffineDouble typedef provided here.                                  */
#include <libtmpl/include/types/tmpl_affine_double.h>

/*  Function prototype / forward declaration.                                 */
extern tmpl_AffineDouble
tmpl_AffDouble_Point_Intercept(const double x0,
                               const double y0,
                               const double intercept);

/*  Implemented here.                                                         */
#include "../../include/inline/affine/tmpl_affine_point_intercept_double.h"

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
