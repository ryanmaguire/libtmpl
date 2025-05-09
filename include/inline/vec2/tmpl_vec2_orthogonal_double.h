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
 *                         tmpl_vec2_orthogonal_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a point orthogonal to the input and of the same magnitude.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_Orthogonal                                              *
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to the input with the same magnitude.    *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      orth (tmpl_TwoVectorDouble):                                          *
 *          A point orthogonal to P, meaning the dot product is zero.         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Given P = (a, b), the vector Q = (-b, a) is orthogonal.               *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 *      2.) The convention (a, b) |-> (-b, a) follows a right-handed          *
 *          orientation. That is: x |-> y |-> -x |-> -y |-> x.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 29, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Changed      *
 *      function to pass by address instead of by value.                      *
 *  2025/05/09: Ryan Maguire                                                  *
 *      Inlined function. Added detailed docstring.                           *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_ORTHOGONAL_DOUBLE_H
#define TMPL_VEC2_ORTHOGONAL_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for computing a vector that is orthogonal to the input.          */
TMPL_INLINE_DECL
tmpl_TwoVectorDouble
tmpl_2DDouble_Orthogonal(const tmpl_TwoVectorDouble * const P)
{
    /*  Output variable for a vector orthogonal to the input.                 */
    tmpl_TwoVectorDouble orth;

    /*  Given P = (a, b), we have Q = (-b, a) is orthogonal to P. That is,    *
     *  P . Q = (a, b) . (-b, a) = -a*b + a*b = 0. Return (-b, a).            */
    orth.dat[0] = -P->dat[1];
    orth.dat[1] = +P->dat[0];
    return orth;
}
/*  End of tmpl_2DDouble_Orthogonal.                                          */

#endif
/*  End of include guard.                                                     */
