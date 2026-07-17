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
 *                         tmpl_point_charge_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the definition of a point charge at long double precision.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 17, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_POINT_CHARGE_LDOUBLE_H
#define TMPL_TYPES_POINT_CHARGE_LDOUBLE_H

/*  Vec3's are used for the position and velocity vectors of the charge.      */
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>

/*  Struct for a long double precision point-charge in three space.           */
typedef struct tmpl_PointChargeLongDouble_Type {

    /*  The position in three space for the point charge.                     */
    tmpl_ThreeVectorLongDouble pos;

    /*  The velocity vector for the charge.                                   */
    tmpl_ThreeVectorLongDouble vel;

    /*  The electric charge, in Coulombs, the particle carries.               */
    long double charge;

    /*  The true time of the particle when it is at (pos, vel) in phase space.*/
    long double true_time;

    /*  The retarded time of the particle relative to some observer. This is  *
     *  only used if one is taking relativistic effects into account.         */
    long double retarded_time;
} tmpl_PointChargeLongDouble;

#endif
/*  End of include guard.                                                     */
