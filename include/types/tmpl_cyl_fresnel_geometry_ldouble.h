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
 *                      tmpl_cyl_fresnel_geometry_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for the geometry of cylindrical Fresnel diffraction.*
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 20, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_CYL_FRESNEL_GEOMETRY_LDOUBLE_H
#define TMPL_TYPES_CYL_FRESNEL_GEOMETRY_LDOUBLE_H

/*  2D vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  3D vector type found here.                                                */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  The geometry for cylindrical Fresnel diffraction.                         */
typedef struct tmpl_CylFresnelGeometryLongDouble_Def {

    /*  Location of the observer, a point in 3D space (not in the xy plane).  */
    tmpl_ThreeVectorLongDouble position;

    /*  The point in the xy plane where the line of sight from the observer   *
     *  intercepts the plane. This is known as the ring-intercept point when  *
     *  working with ring occultations.                                       */
    tmpl_TwoVectorLongDouble intercept;

    /*  The dummy variable of integration, which varies over the xy plane.    */
    tmpl_TwoVectorLongDouble dummy;
} tmpl_CylFresnelGeometryLongDouble;

#endif
/*  End of include guard.                                                     */
