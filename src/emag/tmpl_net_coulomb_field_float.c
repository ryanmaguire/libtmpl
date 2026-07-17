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

/*  Function for computing the Coulomb field using superposition.             */
TMPL_PURE_FUNC
tmpl_ThreeVectorFloat
tmpl_3DFloat_Net_Coulomb_Field(const tmpl_ThreeVectorFloat * const observer,
                               const tmpl_PointChargeFloat * const charges,
                               const size_t number_of_charges)
TMPL_UNSEQUENCED
{
    /*  To carefully compute the electric field we use a Neumaier 2Sum that   *
     *  tracks the error / compensation term. Initialize these to zero.       */
    tmpl_ThreeVectorFloat field = tmpl_3DFloat_Zero;
    tmpl_ThreeVectorFloat error = tmpl_3DFloat_Zero;

    /*  Variable for indexing the sum.                                        */
    size_t n;

    /*  Use superposition to compute the electric field by summing over all   *
     *  of the individual charges.                                            */
    for (n = 0; n < number_of_charges; ++n)
    {
        /*  Calculate the contribution to the electric field from the current *
         *  point charge.                                                     */
        const tmpl_ThreeVectorFloat point_charge_e_field =
            tmpl_3DFloat_Coulomb_Field(observer, &charges[n]);

        /*  Add this contribution to the running sum.                         */
        tmpl_3DFloat_Neumaier_Two_Sum(&point_charge_e_field, &field, &error);
    }

    /*  With Neumaier 2Sum it is possible for || error || > || field ||. The  *
     *  correct summation is given by summing together the running sum with   *
     *  the error term.                                                       */
    return tmpl_3DFloat_Add(&field, &error);
}
/*  End of tmpl_3DFloat_Net_Coulomb_Field.                                    */
