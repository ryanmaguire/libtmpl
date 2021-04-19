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
 *      Normalize a non-zero vector to have length 1.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 21, 2020                                             *
 ******************************************************************************/

/*  Function prototype and three-vector typedef found here.                   */
#include <libtmpl/include/tmpl_euclidean_spatial_geometry.h>

/*  NaN is defined here.                                                      */
#include <libtmpl/include/tmpl_math.h>

/*  Function that normalizes non-zero three dimensional vectors.              */
tmpl_ThreeVector tmpl_ThreeVector_Normalize(tmpl_ThreeVector P)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double norm, rcpr_norm, x, y, z, x_hat, y_hat, z_hat;
    tmpl_ThreeVector P_normalized;

    /*  Get the norm of the input vector P.                                   */
    norm = tmpl_ThreeVector_Euclidean_Norm(P);

    /*  If the norm is zero we cannot normalize. Return NaN in this case.     */
    if (norm == 0.0)
    {
        x_hat = tmpl_NaN;
        y_hat = tmpl_NaN;
        z_hat = tmpl_NaN;
    }
    else
    {
        /*  Extract the x, y, and z components from P.                        */
        x = tmpl_ThreeVector_X(P);
        y = tmpl_ThreeVector_Y(P);
        z = tmpl_ThreeVector_Z(P);

        /*  Compute the reciprocal of the norm. Precomputing a division and   *
         *  using multiplication later is faster than repeated division.      */
        rcpr_norm = 1.0/norm;

        /*  Compute the components of the normalized vector.                  */
        x_hat = x*rcpr_norm;
        y_hat = y*rcpr_norm;
        z_hat = z*rcpr_norm;
    }
    /*  End of if (norm == 0.0).                                              */

    P_normalized = tmpl_ThreeVector_Rect(x_hat, y_hat, z_hat);
    return P_normalized;
}
/*  End of tmpl_ThreeVector_Normalize.                                        */
