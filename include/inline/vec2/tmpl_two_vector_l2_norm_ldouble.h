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
 *                      tmpl_two_vector_l2_norm_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the Euclidean norm (length) of the point (x, y) using the     *
 *      Pythagorean formula:                                                  *
 *          ||(x, y)|| = sqrt(x^2 + y^2)                                      *
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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_VECTOR_L2_NORM_LDOUBLE_H
#define TMPL_TWO_VECTOR_L2_NORM_LDOUBLE_H

/*  The TMPL_USE_INLINE macro is found here.                                  */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is requested.                             */
#if TMPL_USE_INLINE == 1

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are given and where vector types are defined.        */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the magnitude, or L2 norm, of a vector.            */
TMPL_INLINE_DECL
long double tmpl_2DLDouble_L2_Norm(const tmpl_TwoVectorLongDouble *P)
{
    return tmpl_LDouble_Hypot(P->dat[0], P->dat[1]);
}
/*  End of tmpl_2DLDouble_L2_Norm.                                            */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
