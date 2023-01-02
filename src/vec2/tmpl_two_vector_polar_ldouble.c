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
 *      Given two real numbers r and theta, return the vector (x, y) where    *
 *      x = r cos(theta) and y = r sin(theta). That is, return the polar      *
 *      representation of (r, theta) in the plane.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 1, 2022                                               *
 ******************************************************************************/

/*  Trig functions found here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  TODO: Replace Sin and Cos calls with a single SinCos call.                */

/*  Function for returning the the polar representation of (r, theta).        */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Polar(long double r, long double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_TwoVectorLongDouble P;

    /*  Compute the Cartesian coordinates of (r, theta) using cosine and sine.*/
    P.dat[0] = r * tmpl_LDouble_Cos(theta);
    P.dat[1] = r * tmpl_LDouble_Sin(theta);

    return P;
}
/*  End of tmpl_2DFloat_Polar.                                                */
