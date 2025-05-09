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
 *                       tmpl_vec2_cross_product_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides 2D cross product, which outputs a scalar (real number).      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_Cross_Product                                           *
 *  Purpose:                                                                  *
 *      Computes the cross product of two points in the plane. Output is a    *
 *      scalar value, or a real number.                                       *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      cross (double):                                                       *
 *          The cross product of P and Q.                                     *
 *  Called Functions:                                                         *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      There are several ways of thinking about cross products in two        *
 *      dimensions, but perhaps the easiest is by embedding (a, b) into three *
 *      dimensional space via (a, b) |-> (a, b, 0). The cross product of      *
 *      P = (a, b) with Q = (c, d) is then the z-component of the cross       *
 *      product of (a, b, 0) and (c, d, 0). To be explicit, we compute the    *
 *      determinant of the following matrix:                                  *
 *                                                                            *
 *                                                                            *
 *                       -      -                                             *
 *                      |  a  b  |                                            *
 *          cross = det |        |                                            *
 *                      |  c  d  |                                            *
 *                       -      -                                             *
 *                                                                            *
 *                = ad - bc                                                   *
 *                                                                            *
 *      We compute this expression and return. The output is hence a real     *
 *      number, not a vector.                                                 *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 *      2.) The cross product is anti-commutative: PxQ = -QxP.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2025                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_CROSS_PRODUCT_DOUBLE_H
#define TMPL_VEC2_CROSS_PRODUCT_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for computing the cross product of two 2D points.                */
TMPL_INLINE_DECL
double
tmpl_2DDouble_Cross_Product(const tmpl_TwoVectorDouble * const P,
                            const tmpl_TwoVectorDouble * const Q)
{
    /*  Use the determinant formula: (a, b) x (c, d) = ad - bc.               */
    return P->dat[0]*Q->dat[1] - P->dat[1]*Q->dat[0];
}
/*  End of tmpl_2DDouble_Cross_Product.                                       */

#endif
/*  End of include guard.                                                     */
