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
 *                    tmpl_vec2_hadamard_productwith_float                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an in-place Hadamard product for 2D vectors.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_Hadamard_Product                                         *
 *  Purpose:                                                                  *
 *      Multiplies two points in the plane component-wise and in-place.       *
 *  Arguments:                                                                *
 *      P (tmpl_TwoVectorFloat * const):                                      *
 *          A pointer to a point in the Euclidean plane. The product is       *
 *          stored here.                                                      *
 *      Q (const tmpl_TwoVectorFloat * const):                                *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
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
 *      2.) This function acts as the "*=" operator for tmpl_TwoVectorFloat.  *
 *          That is, the function performs P *= Q.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_float.h:                                                    *
 *          The tmpl_TwoVectorFloat typedef is provided here.                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2021                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_HADAMARD_PRODUCTWITH_FLOAT_H
#define TMPL_VEC2_HADAMARD_PRODUCTWITH_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function for multiplying 2 two-dimensional vectors in-place.              */
TMPL_INLINE_DECL
void
tmpl_2DFloat_Hadamard_ProductWith(tmpl_TwoVectorFloat * const P,
                                  const tmpl_TwoVectorFloat * const Q)
{
    /*  The Hadamard product of vectors multiplies their components together. */
    P->dat[0] *= Q->dat[0];
    P->dat[1] *= Q->dat[1];
}
/*  End of tmpl_2DFloat_Hadamard_ProductWith.                                 */

#endif
/*  End of include guard.                                                     */
