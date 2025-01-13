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
 ******************************************************************************
 *                        tmpl_vec3_dot_product_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for the Euclidean dot product at single precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_3DFloat_Dot_Product                                              *
 *  Purpose:                                                                  *
 *      Computes the dot product of two vectors at single precision.          *
 *  Arguments:                                                                *
 *      P (const tmpl_ThreeVectorFloat * const):                              *
 *          A pointer to a vector in R^3.                                     *
 *      Q (const tmpl_ThreeVectorFloat * const):                              *
 *          Another pointer to a vector in R^3.                               *
 *  Output:                                                                   *
 *      dot (float):                                                          *
 *          The dot product P . Q.                                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the definition of the dot product. If P = (Px, Py, Pz) and        *
 *      Q = (Qx, Qy, Qz), then the dot product is:                            *
 *          dot = PxQx + PyQy + PzQz                                          *
 *  Notes:                                                                    *
 *      No checks for Infs or NaNs are performed.                             *
 *      No checks for Null pointers are performed.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec3_float.h:                                                    *
 *          The tmpl_ThreeVectorFloat typedef is provided here.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/02: Ryan Maguire                                                  *
 *      Removed function calls, added doc-string.                             *
 *  2022/03/21: Ryan Maguire                                                  *
 *      Changed function to pass by reference instead of by value.            *
 *  2024/06/07: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC3_DOT_PRODUCT_FLOAT_H
#define TMPL_VEC3_DOT_PRODUCT_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Three-vector typedef found here.                                          */
#include <libtmpl/include/tmpl_vec3_float.h>

/*  Function for computing the dot product of 2 three-vectors.                */
TMPL_INLINE_DECL
float
tmpl_3DFloat_Dot_Product(const tmpl_ThreeVectorFloat * const P,
                         const tmpl_ThreeVectorFloat * const Q)
{
    /*  Use the Euclidean dot product formula and return.                     */
    return P->dat[0]*Q->dat[0] + P->dat[1]*Q->dat[1] + P->dat[2]*Q->dat[2];
}
/*  End of tmpl_3DFloat_Dot_Product.                                          */

#endif
/*  End of include guard.                                                     */
