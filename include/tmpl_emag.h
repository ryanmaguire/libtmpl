/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 ******************************************************************************/
#ifndef TMPL_EMAG_H
#define TMPL_EMAG_H

#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/types/tmpl_vec3_double.h>
#include <libtmpl/include/types/tmpl_vec3_float.h>
#include <libtmpl/include/types/tmpl_vec3_ldouble.h>
#include <libtmpl/include/types/tmpl_point_charge_double.h>
#include <libtmpl/include/types/tmpl_point_charge_float.h>
#include <libtmpl/include/types/tmpl_point_charge_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_3DDouble_Coulomb_Field                                           *
 *  Purpose:                                                                  *
 *      Computes the static Coulomb field given by a point charge.            *
 *  Arguments:                                                                *
 *      observer (const tmpl_ThreeVectorDouble * const):                      *
 *          The location of the observer.                                     *
 *      charge (const tmpl_ThreeVectorDouble * const):                        *
 *          The point charge producing the electric field.                    *
 *  Output:                                                                   *
 *      e_field (tmpl_ThreeVectorDouble):                                     *
 *          The electric field from the charge at the observer.               *
 ******************************************************************************/
TMPL_PURE_FUNC
extern tmpl_ThreeVectorDouble
tmpl_3DDouble_Coulomb_Field(const tmpl_ThreeVectorDouble * const observer,
                            const tmpl_PointChargeDouble * const charge)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Coulomb_Field(const tmpl_ThreeVectorFloat * const observer,
                           const tmpl_PointChargeFloat * const charge)
TMPL_UNSEQUENCED;

TMPL_PURE_FUNC
extern tmpl_ThreeVectorLongDouble
tmpl_3DLDouble_Coulomb_Field(const tmpl_ThreeVectorLongDouble * const observer,
                             const tmpl_PointChargeLongDouble * const charge)
TMPL_UNSEQUENCED;

#endif
