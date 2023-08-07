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
 *              rss_ringoccs_square_wave_fresnel_diffraction                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the Fresnel diffraction of a square wave.*
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) rss_ringoccs_math.h:                                                  *
 *          This file provides compatibility between the two standard math.h  *
 *          header files (C89 vs C99 math.h). If C99 math.h exists, it simply *
 *          provides aliases for the functions, and if C89 math.h is used     *
 *          it defines the functions missing in the earlier version.          *
 *  2.) rss_ringoccs_complex.h:                                               *
 *          Header file where rssringoccs_ComplexDouble is defined, as well   *
 *          as the prototype for rssringoccs_Complex_Cos.                     *
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

/*  Definition of rssringoccs_ComplexDouble found here.                       */
#include <libtmpl/include/tmpl_complex.h>

/*  The Fresnel integrals are found here.                                     */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Header file containing the prototypes for the functions.                  */
#include <libtmpl/include/tmpl_fresnel_diffraction.h>

tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Square_Wave(double x,
                                             double well_width,
                                             double fresnel_scale,
                                             unsigned int number_of_wells)
{
    unsigned int n;
    tmpl_ComplexDouble T_hat, summand;

    const unsigned int n_waves = 2U*number_of_wells;
    const double wave_start = tmpl_Double_Floor(0.5* x * well_width);
    double a = 2.0*well_width*wave_start - (double)number_of_wells;
    double b = a + well_width;
    const double shift = 2.0 * well_width;

    T_hat = tmpl_CDouble_Fresnel_Diffraction_Gap(x, a, b, fresnel_scale);

    for (n = 0U; n < n_waves; ++n)
    {
        a += shift;
        b += shift;

        summand = tmpl_CDouble_Fresnel_Diffraction_Gap(x, a, b, fresnel_scale);
        tmpl_CDouble_AddTo(&T_hat, &summand);
    }

    return T_hat;
}
