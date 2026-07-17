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

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  3D vector functions found here.                                           */
#include <libtmpl/include/tmpl_vec3.h>

/*  Point-charge typedef and function prototype provided here.                */
#include <libtmpl/include/tmpl_emag.h>

/*  Coulomb's constant in SI units given here.                                */
#include <libtmpl/include/constants/tmpl_emag_constants.h>

/*  Function for computing the static Coulomb field from a point charge.      */
TMPL_PURE_FUNC
tmpl_ThreeVectorFloat
tmpl_3DFloat_Coulomb_Field(const tmpl_ThreeVectorFloat * const observer,
                           const tmpl_PointChargeFloat * const charge)
TMPL_UNSEQUENCED
{
    /*  Vector for the relative position vector for the observer.             */
    tmpl_ThreeVectorFloat diff;

    /*  Variables for computing the scale factor for the Coulomb field.       */
    float dist, dist_cubed, scale;

    /*  The electric field points away from a positively charged object.      *
     *  The relative position vector is observer minus charge position.       */
    diff = tmpl_3DFloat_Subtract(observer, &charge->pos);

    /*  Coulomb's law is a 1 / r^2 law, but we need another 1 / r to turn the *
     *  relative position vector into a unit vector. Compute the length of    *
     *  the vector from the charge to the observer, and the cube of this.     */
    dist = tmpl_3DFloat_L2_Norm(&diff);
    dist_cubed = dist * dist * dist;

    /*  From Coulomb's law the scale is k * q / r^3.                          */
    scale = tmpl_float_coulomb_constant * charge->charge / dist_cubed;

    /*  The field is                                                          *
     *                                                                        *
     *               ^          ->                                            *
     *           k q r      k q r                                             *
     *      E = -------- = --------                                           *
     *                 2          3                                           *
     *          || r ||    || r ||                                            *
     *                                                                        *
     *  where the "hat" indicates the vector is a unit vector, and where r is *
     *  the relative position vector from the charge to the observer          *
     *                                                                        *
     *      r = observer - charge_position                                    *
     *                                                                        *
     *  The electric field can be computed using scalar multiplication with   *
     *  the scale factor and the difference vector.                           */
    return tmpl_3DFloat_Scale(scale, &diff);
}
/*  End of tmpl_3DFloat_Coulomb_Field.                                        */
