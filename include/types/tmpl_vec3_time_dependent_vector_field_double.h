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
 *                tmpl_vec3_time_dependent_vector_field_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the function type (double vec3, t) -> double vec3.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 28, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_DOUBLE_H
#define TMPL_TYPES_VEC3_TIME_DEPENDENT_VECTOR_FIELD_DOUBLE_H

/*  Double-precision 3D vectors provided here.                                */
#include "tmpl_vec3_double.h"

/*  Function pointer for time-dependent double-precision vector fields.       */
typedef
tmpl_ThreeVectorDouble
(*tmpl_ThreeTimeDependentVectorFieldDouble)(
    const tmpl_ThreeVectorDouble * const, double t
);

#endif
/*  End of include guard.                                                     */
