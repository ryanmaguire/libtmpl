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
 *                        tmpl_vec2_dot_product_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Euclidean dot product in the plane.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Dot_Product                                              *
 *  Purpose:                                                                  *
 *      Computes the dot product of two vectors in the plane.                 *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorFloat * const):                                *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorFloat * const):                                *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      dot (float):                                                          *
 *          The dot product of P and Q.                                       *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The dot product is done by summing over the component-wise product.   *
 *      That is, if P = (a, b) and Q = (c, d), then:                          *
 *                                                                            *
 *          dot = P . Q                                                       *
 *              = (a, b) . (c, d)                                             *
 *              = a*c + b*d                                                   *
 *                                                                            *
 *      This final expression is returned.                                    *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P and Q are  *
 *          valid pointers to 2D vectors.                                     *
 *      2.) Benchmarks show it is a bit faster to pass P and Q by address,    *
 *          rather than passing by value. The benefit will vary depending on  *
 *          the machine and compiler used.                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the vector struct by address, rather than value.     *
 *  2025/05/01: Ryan Maguire                                                  *
 *      Inlined the function, added detailed docstring.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_DOT_PRODUCT_FLOAT_H
#define TMPL_VEC2_DOT_PRODUCT_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function for computing the Euclidean dot product of two 2D vectors.       */
TMPL_INLINE_DECL
float
tmpl_2DFloat_Dot_Product(const tmpl_TwoVectorFloat * const P,
                         const tmpl_TwoVectorFloat * const Q)
{
    /*  Use the Euclidean dot product formula and return.                     */
    return P->dat[0] * Q->dat[0] + P->dat[1] * Q->dat[1];
}
/*  End of tmpl_2DFloat_Dot_Product.                                          */

#endif
/*  End of include guard.                                                     */
