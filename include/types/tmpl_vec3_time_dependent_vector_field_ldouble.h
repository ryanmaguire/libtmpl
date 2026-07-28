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
 *               tmpl_vec3_time_dependent_vector_field_ldouble                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the function type (long double vec3, t) -> long double vec3. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 28, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_LDOUBLE_H
#define TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_LDOUBLE_H

/*  Single-precision 3D vectors provided here.                                */
#include "tmpl_vec3_ldouble.h"

/*  Function pointer for time-dependent single-precision vector fields.       */
typedef
tmpl_ThreeVectorLongDouble
(*tmpl_ThreeTimeDependentVectorFieldLongDouble)(
    const tmpl_ThreeVectorLongDouble * const, long double t
);

#endif
/*  End of include guard.                                                     */
