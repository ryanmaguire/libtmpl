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
 *                             tmpl_vec2_y_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the y scalar component of a 2D vector.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DDouble_Y                                                       *
 *  Purpose:                                                                  *
 *      Computes the scalar component in the y direction. That is, given      *
 *      P = (a, b), return a.                                                 *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorDouble * const):                               *
 *          A pointer to a point in the Euclidean plane.                      *
 *  Output:                                                                   *
 *      y_val (double):                                                       *
 *          The y coordinate of P.                                            *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      A vector is represented by an array with two real numbers. The y      *
 *      coordinate is given by the first element. This value is returned.     *
 *  Notes:                                                                    *
 *      1.) There are no checks for NULL pointers. It is assumed P is a valid *
 *          pointer to a 2D vector.                                           *
 *      2.) Benchmarks show it is faster to pass by address than by value.    *
 *          The true benefit varies between compilers.                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of the TMPL_INLINE_DECL macro.                           *
 *  2.) tmpl_vec2_double.h:                                                   *
 *          The tmpl_TwoVectorDouble typedef is provided here.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2021/09/15: Ryan Maguire                                                  *
 *      Edited license and added float and long double support.               *
 *  2023/01/01: Ryan Maguire                                                  *
 *      Changed function to pass by address. Moved float and long double to   *
 *      their own files.                                                      *
 *  2025/05/10: Ryan Maguire                                                  *
 *      Inlined the function.                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_Y_DOUBLE_H
#define TMPL_VEC2_Y_DOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Function for returning the y coordinate of a two dimensional vector.      */
TMPL_INLINE_DECL
double tmpl_2DDouble_Y(const tmpl_TwoVectorDouble * const P)
{
    /*  The tmpl_TwoVectorDouble mimics the method used by GSL for complex    *
     *  numbers, using a struct containing a double array with 2 elements.    *
     *  The y coordinate is the first element. Return this.                   */
    return P->dat[1];
}
/*  End of tmpl_2DDouble_Y.                                                   */

#endif
/*  End of include guard.                                                     */
