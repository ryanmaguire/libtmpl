/******************************************************************************
 *                                 LICENSE                                    *
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
 ******************************************************************************
 *                         tmpl_vec3_component_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the component of one vector along another.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Component                                                *
 *  Purpose:                                                                  *
 *      Computes the component of a vector along another.                     *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A vector in R^3.                                                  *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          The vector P is projected along.                                  *
 *  Output:                                                                   *
 *      comp_QP (tmpl_ThreeVectorFloat):                                      *
 *          The component of P along Q.                                       *
 *  Method:                                                                   *
 *      By normalizing Q to unit length, the component can be computed using  *
 *      the dot product. We have:                                             *
 *                                                                            *
 *                     P . Q                                                  *
 *          comp (P) = -----  Q                                               *
 *              Q      ||Q||^2                                                *
 *                                                                            *
 *  Called Functions:                                                         *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DFloat_Normalize:                                           *
 *              Normalizes a vector to unit length.                           *
 *          tmpl_3DFloat_Dot_Product:                                         *
 *              Computes the dot product of two vectors.                      *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for NULL pointers are performed.                        *
 *      3.) If the second vector is zero, the output is NaN.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the component of one vector along another.         */
tmpl_ThreeVectorFloat
tmpl_3DFloat_Component(const tmpl_ThreeVectorFloat * const P,
                       const tmpl_ThreeVectorFloat * const Q)
{
    /*  Variable for the output.                                              */
    tmpl_ThreeVectorFloat component;

    /*  Normalize Q to unit length. Makes the computation simpler and avoids  *
     *  possible overflows or underflows.                                     */
    const tmpl_ThreeVectorFloat Qn = tmpl_3DFloat_Normalize(Q);

    /*  Since Qn is unit magnitude, the scale factor is just P . Qn.          */
    const float factor = tmpl_3DFloat_Dot_Product(P, &Qn);

    /*  The component is (P . Qn) * Qn.                                       */
    component.dat[0] = Qn.dat[0] * factor;
    component.dat[1] = Qn.dat[1] * factor;
    component.dat[2] = Qn.dat[2] * factor;
    return component;
}
/*  End of tmpl_3DFloat_Component.                                            */
