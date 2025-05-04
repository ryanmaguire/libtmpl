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
 *                      tmpl_vec2_l2_norm_squared_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the square of the L2 (Euclidean) norm in the plane.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DFloat_L2_Norm_Squared                                          *
 *  Purpose:                                                                  *
 *      Computes the square of the Euclidean norm of a point in the plane.    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorFloat * const):                                *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      norm_squared (float):                                                 *
 *          The square of the L2 norm of P.                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The norm of a point is given by the Pythagorean formula. That is, if  *
 *      P = (a, b), then the square of the norm is:                           *
 *                                                                            *
 *          || P ||^2 = || (a, b) ||^2                                        *
 *                    = a^2 + b^2                                             *
 *                                                                            *
 *      This final expression is returned.                                    *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 *      2.) For vectors with very large components, the square of the         *
 *          norm may overflow. This will occur if || P || >= sqrt(MAX),       *
 *          where MAX is the largest representable float.                     *
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
 *                             Revision History                               *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the vector struct by address, rather than value.     *
 *  2025/05/04: Ryan Maguire                                                  *
 *      Inlined the function, added detailed docstring.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_L2_NORM_SQUARED_FLOAT_H
#define TMPL_VEC2_L2_NORM_SQUARED_FLOAT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Function for computing the square of the L2 norm of a 2D point.           */
TMPL_INLINE_DECL
float
tmpl_2DFloat_L2_Norm_Squared(const tmpl_TwoVectorFloat * const P)
{
    /*  Use the Pythagorean formula on the vector P.                          */
    return P->dat[0]*P->dat[0] + P->dat[1]*P->dat[1];
}
/*  End of tmpl_2DFloat_L2_Norm_Squared.                                      */

#endif
/*  End of include guard.                                                     */
