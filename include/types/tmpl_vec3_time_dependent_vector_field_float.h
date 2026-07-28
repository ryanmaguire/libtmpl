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
 *                tmpl_vec3_time_dependent_vector_field_float                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the function type (float vec3, t) -> float vec3.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 28, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_FLOAT_H
#define TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_FLOAT_H

/*  Single-precision 3D vectors provided here.                                */
#include "tmpl_vec3_float.h"

/*  Function pointer for time-dependent single-precision vector fields.       */
typedef
tmpl_ThreeVectorFloat
(*tmpl_ThreeTimeDependentVectorFieldFloat)(
    const tmpl_ThreeVectorFloat * const, float t
);

#endif
/*  End of include guard.                                                     */
