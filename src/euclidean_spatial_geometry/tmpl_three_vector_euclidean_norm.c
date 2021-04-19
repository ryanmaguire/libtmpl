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
 *      Computes the Euclidean norm of a three dimensional vector using the   *
 *      Pythagorean formula:                                                  *
 *          ||(x, y, z)|| = sqrt(x^2 + y^2 + z^2)                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  Square root function found here.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  Function for computing the length of three dimensional vectors.           */
double tmpl_ThreeVector_Euclidean_Norm(tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double x, y, z, norm;

    /*  Extract the x, y, and z components from P.                            */
    x = tmpl_ThreeVector_X(P);
    y = tmpl_ThreeVector_Y(P);
    z = tmpl_ThreeVector_Z(P);

    /*  Use the Pythagorean formula to compute the norm and return.           */
    norm = tmpl_Double_Sqrt(x*x + y*y + z*z);
    return norm;
}
/*  End of tmpl_ThreeVector_Euclidean_Norm.                                   */

