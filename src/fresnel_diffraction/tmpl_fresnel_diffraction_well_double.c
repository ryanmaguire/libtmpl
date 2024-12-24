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
 *                rss_ringoccs_ringlet_fresnel_diffraction                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the Fresnel diffraction of a ringlet.    *
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

/*  Constants involving pi found here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Definition of tmpl_ComplexDouble found here.                              */
#include <libtmpl/include/tmpl_complex_double.h>

/*  The Fresnel integrals are found here.                                     */
#include <libtmpl/include/tmpl_special_functions_complex.h>

/*  Header file containing the prototypes for the functions.                  */
#include <libtmpl/include/tmpl_fresnel_diffraction.h>

/******************************************************************************
 *  Function:                                                                 *
 *      Inverted_Square_Well_Diffraction_Float                                *
 *  Purpose:                                                                  *
 *      Compute the diffraction pattern from a plane wave incident on a       *
 *      square well, assuming the Fresnel approximation is valid.             *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          The location on the x-axis for the point being computed.          *
 *      a (float):                                                            *
 *          The left-most endpoint of the square well.                        *
 *      b (float):                                                            *
 *          The right-most endpoint of the square well.                       *
 *      F (float):                                                            *
 *          The Fresnel scale.                                                *
 *  Notes:                                                                    *
 *      1.) This function relies on the C99 standard, or higher.              *
 ******************************************************************************/

tmpl_ComplexDouble
tmpl_CDouble_Fresnel_Diffraction_Well(double x,
                                      double left_edge,
                                      double right_edge,
                                      double fresnel_scale)
{
    tmpl_ComplexDouble out;

    /*  The bounds of the integral are sqrt(pi/2)(a-x)/F and                  *
     *  sqrt(pi/2)(b-x)/F, and the output is computed in terms of this.       */
    const double scale_factor = tmpl_Double_Sqrt_Pi_By_Two / fresnel_scale;
    const double arg1 = scale_factor * (left_edge - x);
    const double arg2 = scale_factor * (right_edge - x);

    /*  Compute the Fresnel integrals of the two arguments.                   */
    const tmpl_ComplexDouble z1 = tmpl_CDouble_Fresnel_Integral_Real(arg1);
    const tmpl_ComplexDouble z2 = tmpl_CDouble_Fresnel_Integral_Real(arg2);

    /*  The output is the difference of z2 and z1 scaled by the factor        *
     *  sqrt(1/2 pi) * (1 - i), so compute this.                              */
    out.dat[0] = (z2.dat[0] + z2.dat[1]) - (z1.dat[0] + z1.dat[1]);
    out.dat[1] = (z2.dat[1] - z2.dat[0]) - (z1.dat[1] - z1.dat[0]);

    out.dat[0] = 1.0 - tmpl_Double_Rcpr_Sqrt_Two_Pi*out.dat[0];
    out.dat[1] *= -tmpl_Double_Rcpr_Sqrt_Two_Pi;
    return out;
}
