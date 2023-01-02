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
 *                    tmpl_two_vector_orthogonal_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a vector orthogonal to a given input.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_2DLDouble_Orthogonal                                             *
 *  Purpose:                                                                  *
 *      Given a point in the plane (x, y), computes a point orthogonal to     *
 *      this with respect to the origin. In particular, it returns (-y, x)    *
 *      since <(x, y) | (-y, x)> = x(-y) + yx = 0, where < | > is the usual   *
 *      Euclidean dot product.                                                *
 *  Arguments:                                                                *
 *      V (const tmpl_TwoVectorLongDouble *):                                 *
 *          A pointer to a point in the plane.                                *
 *  Output:                                                                   *
 *      perpV (tmpl_TwoVectorLongDouble):                                     *
 *          A point orthogonal to V.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Given (x, y), return the vector (-y, x).                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_vec2.h:                                                          *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 29, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Changed      *
 *      function to pass by address instead of by value.                      *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing an orthogonal vector to the given input.           */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Orthogonal(const tmpl_TwoVectorLongDouble *V)
{
    tmpl_TwoVectorLongDouble perpV;

    perpV.dat[0] = -V->dat[1];
    perpV.dat[1] = V->dat[0];
    return perpV;
}
/*  End of tmpl_2DLDouble_Orthogonal.                                         */
