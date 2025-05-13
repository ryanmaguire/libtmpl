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
 *                          tmpl_vec2_scale_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides scalar multiplication for single precision 2D vectors.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Scale                                                  *
 *  Purpose:                                                                  *
 *      Scales a point in the plane by a real number.                         *
 *  Arguments:                                                                *
 *      r (long double):                                                      *
 *          A real number, the scalar multiplier for P.                       *
 *      P (const tmpl_TwoVectorLongDouble * const):                           *
 *          A point in the Euclidean plane.                                   *
 *  Output:                                                                   *
 *      prod (tmpl_TwoVectorLongDouble):                                      *
 *          The scalar product of r and P, r*P.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Scalar multiplication is done component-wise. That is, if P = (a, b), *
 *      then the product is given by:                                         *
 *                                                                            *
 *          prod = r * P                                                      *
 *               = r * (a, b)                                                 *
 *               = (r*a, r*b)                                                 *
 *                                                                            *
 *      In other words:                                                       *
 *                                                                            *
 *          x = r * a                                                         *
 *          y = r * b                                                         *
 *                                                                            *
 *      We perform these products and return.                                 *
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
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/21: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2023/01/01: Ryan Maguire                                                  *
 *      Changed function to pass by address instead of by value.              *
 *  2025/05/13: Ryan Maguire                                                  *
 *      Inlined the function, added docstring.                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_SCALE_LDOUBLE_H
#define TMPL_VEC2_SCALE_LDOUBLE_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  Two-vector typedef found here.                                            */
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Function for scaling a 2D vector by a real number.                        */
TMPL_INLINE_DECL
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Scale(long double r, const tmpl_TwoVectorLongDouble * const P)
{
    /*  Output variable for the product of r and P.                           */
    tmpl_TwoVectorLongDouble prod;

    /*  The scalar product of r and P scales the components.                  */
    prod.dat[0] = r * P->dat[0];
    prod.dat[1] = r * P->dat[1];
    return prod;
}
/*  End of tmpl_2DLDouble_Scale.                                              */

#endif
/*  End of include guard.                                                     */
