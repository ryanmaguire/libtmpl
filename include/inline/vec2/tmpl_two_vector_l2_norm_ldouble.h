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
 *                         tmpl_vec2_l2_norm_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the L2 (Euclidean) norm function in the Euclidean plane.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_L2_Norm                                                *
 *  Purpose:                                                                  *
 *      Computes the Euclidean norm of a point in the plane.                  *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      norm (long double):                                                   *
 *          The Euclidean norm of the point P.                                *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Hypot:                                               *
 *              Computes the length of the line from (0, 0) to (x, y).        *
 *  Method:                                                                   *
 *      The Euclidean norm of a point is given by the Pythagorean formula.    *
 *      That is, if P = (a, b), then the norm is:                             *
 *                                                                            *
 *          norm(P) = || P ||                                                 *
 *                  = || (a, b) ||                                            *
 *                  = sqrt(a^2 + b^2)                                         *
 *                                                                            *
 *      This is computed using the tmpl_LDouble_Hypot function.               *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2022/12/30: Ryan Maguire                                                  *
 *      Changed function to pass vector by address. Function now passes the   *
 *      x and y components to tmpl_LDouble_Hypot.                             *
 *  2023/01/19: Ryan Maguire                                                  *
 *      Added inline version into include/vec2/.                              *
 *  2025/05/01: Ryan Maguire                                                  *
 *      Removed tmpl_math.h include, added detailed docstring.                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_L2_NORM_LDOUBLE_H
#define TMPL_VEC2_L2_NORM_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Tell the compiler about the hypotenuse function.                          */
extern long double tmpl_LDouble_Hypot(long double x, long double y);

/*  Function for computing the magnitude, or L2 norm, of a vector.            */
TMPL_INLINE_DECL
long double tmpl_2DLDouble_L2_Norm(const tmpl_TwoVectorLongDouble * const P)
{
    return tmpl_LDouble_Hypot(P->dat[0], P->dat[1]);
}
/*  End of tmpl_2DLDouble_L2_Norm.                                            */

#endif
/*  End of include guard.                                                     */
