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
 *                      tmpl_vec3_quick_component_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the component of one vector along another.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DDouble_Quick_Component                                         *
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
 *      Use the component formula directly.                                   *
 *                                                                            *
 *                     P . Q                                                  *
 *          comp (P) = -----  Q                                               *
 *              Q      ||Q||^2                                                *
 *                                                                            *
 *      Since we do not normalize Q in the quick version of this function,    *
 *      this is susceptible to overflow and underflow.                        *
 *  Called Functions:                                                         *
 *      tmpl_vec3.h:                                                          *
 *          tmpl_3DDouble_L2_Norm_Squared:                                    *
 *              Computes the square of the norm of a vector.                  *
 *          tmpl_3DDouble_Dot_Product:                                        *
 *              Computes the dot product of two vectors.                      *
 *  Notes:                                                                    *
 *      1.) No checks for Infs or NaNs are performed.                         *
 *      2.) No checks for NULL pointers are performed.                        *
 *      3.) If the second vector is zero, the output is NaN.                  *
 *      4.) This version does not prevent overflow or underflow. If you are   *
 *          working with vectors that have very large components, use         *
 *          tmpl_3DDouble_Component. That function safely handles overflow,   *
 *          but is much slower.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef and the function prototype. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 12, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_QUICK_COMPONENT_DOUBLE_H
#define TMPL_VEC3_QUICK_COMPONENT_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef and function prototype given here.                   */
#include <libtmpl/include/tmpl_vec3.h>

/*  Function for computing the component of one vector along another.         */
TMPL_INLINE_DECL
tmpl_ThreeVectorDouble
tmpl_3DDouble_Quick_Component(const tmpl_ThreeVectorDouble * const P,
                              const tmpl_ThreeVectorDouble * const Q)
{
    /*  Variable for the output.                                              */
    tmpl_ThreeVectorDouble component;

    /*  The scale factor is (P . Q) / ||Q||^2.                                */
    const double factor = tmpl_3DDouble_Dot_Product(P, Q) /
                          tmpl_3DDouble_L2_Norm_Squared(Q);

    /*  The component is (P . Q) * Q / ||Q||^2.                               */
    component.dat[0] = Q->dat[0] * factor;
    component.dat[1] = Q->dat[1] * factor;
    component.dat[2] = Q->dat[2] * factor;
    return component;
}
/*  End of tmpl_3DDouble_Quick_Component.                                     */

#endif
/*  End of include guard.                                                     */
