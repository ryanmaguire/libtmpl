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
 *                     tmpl_vec2_hadamard_product_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the Hadamard product for double precision 2D vectors.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_Hadamard_Product                                        *
 *  Purpose:                                                                  *
 *      Multiplies two points in the plane component-wise.                    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorDouble * const):                               *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      prod (tmpl_TwoVectorDouble):                                          *
 *          The Hadamard product of P and Q.                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The Hadamard product is done component-wise. That is, if P = (a, b)   *
 *      and Q = (c, d), then the Hadamard product is given by:                *
 *                                                                            *
 *          prod = P * Q                                                      *
 *               = (a, b) * (c, d)                                            *
 *               = (a * c, b * d)                                             *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = a * c                                                         *
 *          y = b * d                                                         *
 *                                                                            *
 *      We perform these products and return.                                 *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2021                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_HADAMARD_PRODUCT_DOUBLE_H
#define TMPL_VEC2_HADAMARD_PRODUCT_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for multiplying 2 two-dimensional vectors.                       */
TMPL_INLINE_DECL
tmpl_TwoVectorDouble
tmpl_2DDouble_Hadamard_Product(const tmpl_TwoVectorDouble * const P,
                               const tmpl_TwoVectorDouble * const Q)
{
    /*  Output variable for the product of P and Q.                           */
    tmpl_TwoVectorDouble prod;

    /*  The Hadamard product of vectors multiplies their components together. */
    prod.dat[0] = P->dat[0] * Q->dat[0];
    prod.dat[1] = P->dat[1] * Q->dat[1];
    return prod;
}
/*  End of tmpl_2DDouble_Hadamard_Product.                                    */

#endif
/*  End of include guard.                                                     */
