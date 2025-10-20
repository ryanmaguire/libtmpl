/******************************************************************************
 *                                 LICENSE                                    *
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
 *                 tmpl_cyl_fresnel_observer_geometry_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for the geometry of cylindrical Fresnel diffraction.*
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 20, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_CYL_FRESNEL_OBSERVER_GEOMETRY_DOUBLE_H
#define TMPL_TYPES_CYL_FRESNEL_OBSERVER_GEOMETRY_DOUBLE_H

/*  2D vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  3D vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec3_double.h>

/*  The geometry is defined by the observers location (in 3D space), the      *
 *  point of interest in the plane, and the dummy variable of integration.    */
typedef struct tmpl_CylFresnelObserverGeometryDouble_Def {
    tmpl_ThreeVectorDouble position;
    tmpl_TwoVectorDouble dummy;
    tmpl_TwoVectorDouble intercept;
} tmpl_CylFresnelObserverGeometryDouble;

#endif
/*  End of include guard.                                                     */
