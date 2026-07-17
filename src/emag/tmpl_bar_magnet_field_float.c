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

/*  Function prototype provided here.                                         */
#include <libtmpl/include/tmpl_emag.h>

/*  Permeability of vacuum in SI units given here.                            */
#include <libtmpl/include/constants/tmpl_emag_constants.h>

/*  Function for computing the magnetic field from a bar magnet.              */
TMPL_PURE_FUNC
extern tmpl_ThreeVectorFloat
tmpl_3DFloat_Bar_Magnet_Field(
    const tmpl_ThreeVectorFloat * const observer,
    const tmpl_ThreeVectorFloat * const position,
    const tmpl_ThreeVectorFloat * const moment
)
TMPL_UNSEQUENCED
{
    /*  Vector for the relative position vector for the observer. To save on  *
     *  space and computation, we will reuse this variable a few times.       */
    tmpl_ThreeVectorFloat vec;

    /*  Variables for computing the scale factors for the magnetic field.     */
    float dist, dist_cubed, m_dot_r, scale;

    /*  The magnetic field points away from the bar magnet. The relative      *
     *  position vector is the observer minus the position for the dipole.    */
    vec = tmpl_3DFloat_Subtract(observer, position);

    /*  The magnetic field from a bar magnet has a 1 / r^3 law.               */
    dist = tmpl_3DFloat_L2_Norm(&vec);
    dist_cubed = dist * dist * dist;

    /*  The scale factor is mu_0 / (4 pi r^3), compute this.                  */
    scale = tmpl_float_mu_nought_by_four_pi / dist_cubed;

    /*  The relative position vector needs to be normalized for the equation. */
    tmpl_3DFloat_NormalizeSelf(&vec);

    /*  vec has now been normalized, the scale factor for the unit relative   *
     *  position vector is 3 * (m . r_hat), compute the dot product.          */
    m_dot_r = tmpl_3DFloat_Dot_Product(&vec, moment);

    /*  Reuse vec again, compute 3 * (m . r_hat) r_hat.                       */
    tmpl_3DFloat_ScaleBy(&vec, 3.0F * m_dot_r);

    /*  We now have vec = 3 * (m . r_hat) r_hat. Subtract the magnetic        *
     *  moment from this and store it is vec.                                 */
    tmpl_3DFloat_SubtractFrom(&vec, moment);

    /*  The magnetic field is 3 * (m . r_hat) r_hat - m times the scale       *
     *  factor mu_0 / (4 pi r^3). Compute this and return.                    */
    return tmpl_3DFloat_Scale(scale, &vec);
}
/*  End of tmpl_3DFloat_Bar_Magnet_Field.                                     */
