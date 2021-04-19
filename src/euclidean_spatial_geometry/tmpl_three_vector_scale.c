/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *      Function for multiplying a three vector by a real number.             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Multiply a three vector by a real number.                                 */
tmpl_ThreeVector tmpl_ThreeVector_Scale(double a, tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double Px, Py, Pz, x, y, z;
    tmpl_ThreeVector scale;

    /*  Extract the x, y, and z components from P.                            */
    Px = tmpl_ThreeVector_X(P);
    Py = tmpl_ThreeVector_Y(P);
    Pz = tmpl_ThreeVector_Z(P);

    /*  Scalar multiplication is done component-wise, so compute this.        */
    x = a*Px;
    y = a*Py;
    z = a*Pz;

    /*  Use tmpl_ThreeVector_Rect to create the output and return.            */
    scale = tmpl_ThreeVector_Rect(x, y, z);
    return scale;
}
/*  End of tmpl_ThreeVector_Scale.                                            */

