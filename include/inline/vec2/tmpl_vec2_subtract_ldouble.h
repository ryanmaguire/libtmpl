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
 *                         tmpl_vec2_subtract_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides vector subtraction for single precision 2D vectors.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Subtract                                               *
 *  Purpose:                                                                  *
 *      Subtracts two points in the plane component-wise.                     *
 *  Arguments:                                                                *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A pointer to a point in the Euclidean plane.                      *
 *      Q (const tmpl_TwoVectorLongDouble * const):                           *
 *          Another point in the Euclidean plane.                             *
 *  Output:                                                                   *
 *      diff (tmpl_TwoVectorLongDouble):                                      *
 *          The vector difference of P and Q.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Vector subtraction is done component-wise. That is, if P = (a, b) and *
 *      Q = (c, d), then the vector difference is given by:                   *
 *                                                                            *
 *          diff = P - Q                                                      *
 *               = (a, b) - (c, d)                                            *
 *               = (a - c, b - d)                                             *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = a - c                                                         *
 *          y = b - d                                                         *
 *                                                                            *
 *      We perform these differences and return.                              *
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
 *  2.) tmpl_vec2_ldouble.h:                                                  *
 *          The tmpl_TwoVectorLongDouble typedef is provided here.            *
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
 *  2025/05/13: Ryan Maguire                                                  *
 *      Inlined the function, added detailed docstring.                       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_SUBTRACT_LDOUBLE_H
#define TMPL_VEC2_SUBTRACT_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function for subtracting 2 two-dimensional vectors.                       */
TMPL_INLINE_DECL
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Subtract(const tmpl_TwoVectorLongDouble * const P,
                        const tmpl_TwoVectorLongDouble * const Q)
{
    /*  Output variable for the difference of P and Q.                        */
    tmpl_TwoVectorLongDouble diff;

    /*  The difference of two vectors simply subtracts their components.      */
    diff.dat[0] = P->dat[0] - Q->dat[0];
    diff.dat[1] = P->dat[1] - Q->dat[1];
    return diff;
}
/*  End of tmpl_2DLDouble_Subtract.                                           */

#endif
/*  End of include guard.                                                     */
