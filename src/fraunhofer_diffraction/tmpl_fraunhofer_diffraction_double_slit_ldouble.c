/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of rss_ringoccs.                                        *
 *                                                                            *
 *  rss_ringoccs is free software: you can redistribute it and/or modify it   *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  rss_ringoccs is distributed in the hope that it will be useful,           *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with rss_ringoccs.  If not, see <https://www.gnu.org/licenses/>.    *
 ******************************************************************************
 *              rss_ringoccs_two_slit_fraunhofer_diffraction                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the Fraunhofer diffraction modeling of   *
 *      a double slit.                                                        *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/27 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 ******************************************************************************/

/*  Header file which contains aliases for the function in the standard C     *
 *  library math.h. This allows compatibility of C89 and C99 math.h headers.  */
#include <libtmpl/include/tmpl_math.h>

/*  The Fresnel integrals are found here.                                     */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Header file containing the prototypes for the functions.                  */
#include <libtmpl/include/tmpl_fraunhofer_diffraction.h>

long double
tmpl_LDouble_Fraunhofer_Diffraction_Double_Slit(long double x,
                                                long double z,
                                                long double a,
                                                long double d,
                                                long double lambda)
{
    /*  Declare all necessary variables.                                      */
    long double sin_theta, var_1, var_2, var_3, scaled_a, scaled_d, out;

    /*  Compute the length of the point (x, z) in the plane.                  */
    const long double norm = tmpl_LDouble_Hypot(x, z);

    /*  If norm is zero, the result is undefined. Return NaN in this case.    */
    if (norm == 0.0L)
        return TMPL_NANL;

    /*  Using the fact that sin(theta) = x/r, where r is the hypotenus,       *
     *  we can write sin_theta as follows:                                    */
    sin_theta = x / norm;

    /*  Scale the input parameters a and b by the reciprocal of the           *
     *  wavelength lambda.                                                    */
    scaled_a = a/lambda;
    scaled_d = d/lambda;

    /*  The various factors are in terms of the squares sinc function and     *
     *  the ordinary sine function. Since sinc and sine are more              *
     *  expensive than multiplication (computationally) it is better to       *
     *  compute sinc/sine once, and then square this.                         */
    var_1 = tmpl_LDouble_Sinc(scaled_a*sin_theta);
    var_2 = tmpl_LDouble_SinPi(2.0L*scaled_d*sin_theta);
    var_3 = 2.0L*tmpl_LDouble_SinPi(scaled_d*sin_theta);
    out = var_1*var_2/var_3;
    return out * out;
}
