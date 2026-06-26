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
 *                         tmpl_vec3_component_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the component of one vector along another.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Component                                               *
 *  Purpose:                                                                  *
 *      Computes the component of a vector along another.                     *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorDouble * const):                             *
 *          A vector in R^3.                                                  *
 *      Q (const tmpl_ThreeVectorDouble * const):                             *
 *          The vector P is projected along.                                  *
 *  Output:                                                                   *
 *      comp_QP (tmpl_ThreeVectorDouble):                                     *
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
 *      src/vec3/                                                             *
 *          tmpl_3DDouble_Normalize:                                          *
 *              Normalizes a vector to unit length.                           *
 *          tmpl_3DDouble_Dot_Product:                                        *
 *              Computes the dot product of two vectors.                      *
 *          tmpl_3DDouble_Scale:                                              *
 *              Multiplies a 3D vector by a scalar.                           *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *                                                                            *
 *      2.) No checks for Null pointers are performed.                        *
 *                                                                            *
 *      3.) The result is undefined if Q is the zero vector.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_attributes.h:                                                    *
 *          Provides C23 attributes for optimization.                         *
 *  2.) tmpl_vec3.h:                                                          *
 *          tmpl_ThreeVectorDouble and function prototype provided here.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the component of one vector along another.         */
TMPL_PURE_FUNC
tmpl_ThreeVectorDouble
tmpl_3DDouble_Component(const tmpl_ThreeVectorDouble * const p,
                        const tmpl_ThreeVectorDouble * const q)
TMPL_UNSEQUENCED
{
    /*  Normalize q to unit length. This makes the computation simpler and    *
     *  avoids possible overflows and underflows.                             */
    const tmpl_ThreeVectorDouble qn = tmpl_3DDouble_Normalize(q);

    /*  Since qn is unit magnitude, the scale factor is just p . qn.          */
    const double factor = tmpl_3DDouble_Dot_Product(p, &qn);

    /*  The component is (P . Qn) * Qn.                                       */
    return tmpl_3DDouble_Scale(factor, &qn);
}
/*  End of tmpl_3DDouble_Component.                                           */
