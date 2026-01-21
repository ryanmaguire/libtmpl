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
 *                       tmpl_filon02_integrand_cdouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the integral of f(t) exp(i g(t)) assuming constant f and     *
 *      quadratic g, g(t) = a t^2 + b t + c.                                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Filon02_Integrand                                        *
 *  Purpose:                                                                  *
 *      Numerically integrates f(t) exp(i g(t)) assuming constant f and       *
 *      quadratic g, where f is complex-valued and g is real-valued.          *
 *  Arguments:                                                                *
 *      left (const tmpl_ComplexDouble):                                      *
 *          The approximate value for f(t) across the left bin.               *
 *      right (const tmpl_ComplexDouble):                                     *
 *          The approximate value for f(t) across the right bin.              *
 *      g_left (const double):                                                *
 *          The left real value for the phase.                                *
 *      g_middle (const double):                                              *
 *          The central real value for the phase.                             *
 *      g_right (const double):                                               *
 *          The right real value for the phase.                               *
 *      width (const double):                                                 *
 *          The width of a single bin.                                        *
 *  Output:                                                                   *
 *      integrand (tmpl_ComplexDouble):                                       *
 *          The integral of f(t) exp(i g(t)) across the two bins.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_integration.h:                                                   *
 *          Header file containing the function prototype.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header providing the absolute value function.                     *
 *  3.) tmpl_complex.h:                                                       *
 *          Header providing complex numbers and complex arithmetic.          *
 *  4.) tmpl_special_functions_real.h:                                        *
 *          Header providing the Fresnel functions, C(x) and S(x).            *
 *  5.) tmpl_float.h:                                                         *
 *          Header providing the TMPL_SQRT_DBL_EPS macro.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 15, 2026                                              *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_integration.h>

/*  Absolute value function provided here.                                    */
#include <libtmpl/include/tmpl_math.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/tmpl_complex.h>

/*  Fresnel functions provided here.                                          */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TMPL_SQRT_DBL_EPS macro provided here.                                    */
#include <libtmpl/include/tmpl_float.h>

/*  Function for numerically integrating using a Filon-like quadrature.       */
tmpl_ComplexDouble
tmpl_CDouble_Filon02_Integrand(const tmpl_ComplexDouble left,
                               const tmpl_ComplexDouble right,
                               const double g_left,
                               const double g_middle,
                               const double g_right,
                               const double width)
{
    /*  Variable for the output, the integral of f(t) exp(i g(t)) across the  *
     *  current bin [L, R], with R - L = 2 * width.                           */
    tmpl_ComplexDouble integrand;

    /*  Threshold for swapping between quadratic and linear methods.          */
    const double threshold = 4.0 * TMPL_SQRT_DBL_EPS;

    /*  The function g is written in the form A (t - B)^2 + C. We use the     *
     *  magnitude of A to determine whether we use a quadratic or a linear    *
     *  interpolation across the two bins for the integral.                   */
    const double rcpr_width = 1.0 / width;
    const double half_rcpr_width_squared = 0.5 * rcpr_width * rcpr_width;
    const double scaled_curvature = g_right - 2.0 * g_middle + g_left;
    const double curvature = scaled_curvature * half_rcpr_width_squared;

    /*  If the curvature is very small, then the parabola essentially becomes *
     *  a line and we may use a linear interpolation for the integral.        */
    if (tmpl_Double_Abs(curvature) < threshold)
    {
        const tmpl_ComplexDouble left_integral =
            tmpl_CDouble_Filon01_Integrand(left, g_left, g_middle, width);

        const tmpl_ComplexDouble right_integral =
            tmpl_CDouble_Filon01_Integrand(right, g_middle, g_right, width);

        integrand = tmpl_CDouble_Add(left_integral, right_integral);
    }

    /*  If the curvature is large enough, way may safely use the quadratic    *
     *  interpolation to integrate across the two bins.                       */
    else
    {
        const double scale_factor = 0.5 / scaled_curvature;
        const double g_diff = g_left - g_right;

        const double p0 = g_middle - 0.25 * g_diff * g_diff * scale_factor;
        const double p1 = g_diff * width * scale_factor;
        const double p2 = tmpl_Double_Sqrt(curvature);

        const tmpl_ComplexDouble scale = tmpl_CDouble_Polar(1.0 / p2, p0);

        const double s_left = tmpl_Double_Fresnel_Sin(p2 * (p1 + width));
        const double s_middle = tmpl_Double_Fresnel_Sin(p2 * p1);
        const double s_right = tmpl_Double_Fresnel_Sin(p2 * (p1 - width));

        const double c_left = tmpl_Double_Fresnel_Cos(p2 * (p1 + width));
        const double c_middle = tmpl_Double_Fresnel_Cos(p2 * p1);
        const double c_right = tmpl_Double_Fresnel_Cos(p2 * (p1 - width));

        const double s_left_scale = s_left - s_middle;
        const double s_right_scale = s_middle - s_right;
        const double c_left_scale = c_left - c_middle;
        const double c_right_scale = c_middle - c_right;

        tmpl_ComplexDouble left_integral =
            tmpl_CDouble_Rect(c_left_scale, s_left_scale);

        tmpl_ComplexDouble right_integral =
            tmpl_CDouble_Rect(c_right_scale, s_right_scale);

        tmpl_CDouble_MultiplyBy(&left_integral, &left);
        tmpl_CDouble_MultiplyBy(&right_integral, &right);

        integrand = tmpl_CDouble_Add(left_integral, right_integral);
        tmpl_CDouble_MultiplyBy(&integrand, &scale);
    }

    return integrand;
}
/*  End of tmpl_CDouble_Filon02_Integrand.                                    */
