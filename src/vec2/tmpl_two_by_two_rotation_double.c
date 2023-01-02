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
 *                          tmpl_rotation_matrix_2d                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the 2x2 rotation matrix corresponding to a real number.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

/*  Trig functions found here.                                                */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/* TODO: Replace cos and sin calls with a single sincos call.                 */

/*  Function for computing the rotation matrix corresponding to a real number.*/
tmpl_TwoByTwoMatrixDouble tmpl_2x2Double_Rotation(double theta)
{
    /*  The components of the rotation matrix are determined by cos and sin.  */
    const double cos_theta = tmpl_Double_Cos(theta);
    const double sin_theta = tmpl_Double_Sin(theta);
    tmpl_TwoByTwoMatrixDouble R;

    /*  Compute the rotation matrix from the given trig values.               */
    R.dat[0][0] = cos_theta;
    R.dat[0][1] = -sin_theta;
    R.dat[1][0] = sin_theta;
    R.dat[1][1] = cos_theta;

    return R;
}
/*  End of tmpl_2x2Double_Rotation.                                           */
