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
 *  Purpose:                                                                  *
 *      Returns the square of the Euclidean norm of a vector (x, y) using the *
 *      Pythagorean formula:                                                  *
 *          ||(x, y)||^2 = x^2 + y^2                                          *
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
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the vector struct by address, rather than value.     *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the length of the vector (x, y) in the plane.      */
float tmpl_2DFloat_L2_Norm_Squared(const tmpl_TwoVectorFloat *P)
{
    return P->dat[0]*P->dat[0] + P->dat[1]*P->dat[1];
}
/*  End of tmpl_2DFloat_L2_Norm_Squared.                                      */
