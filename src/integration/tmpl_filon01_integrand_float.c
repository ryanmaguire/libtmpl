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
 *                        tmpl_filon01_integrand_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the integral of f(t) exp(i g(t)) assuming constant f and     *
 *      affine g, g(t) = a t + b.                                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Filon01_Integrand                                          *
 *  Purpose:                                                                  *
 *      Numerically integrates f(t) exp(i g(t)) assuming constant f and       *
 *      affine g, where f is real-valued and g is real-valued as well.        *
 *  Arguments:                                                                *
 *      value (const float):                                                  *
 *          The approximate value for the real function across the bin.       *
 *      g_left (const float):                                                 *
 *          The left real value for the phase.                                *
 *      g_right (const float):                                                *
 *          The right real value for the phase.                               *
 *      width (const float):                                                  *
 *          The width of the bin.                                             *
 *  Output:                                                                   *
 *      integrand (tmpl_ComplexFloat):                                        *
 *          The integral of f(t) exp(i g(t)).                                 *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Float_Abs:                                                   *
 *              Computes the absolute value of a real number.                 *
 *      src/complex/                                                          *
 *          tmpl_CFloat_Expi:                                                 *
 *              Creates a point on the unit circle, z = exp(i theta).         *
 *          tmpl_CFloat_MultiplyBy_Real:                                      *
 *              Performs z *= r where r is real.                              *
 *          tmpl_CFloat_MultiplyBy_Imag:                                      *
 *              Performs z *= i*r where r is real.                            *
 *          tmpl_CFloat_Polar:                                                *
 *              Creates a complex number using polar form, z = r exp(i theta).*
 *          tmpl_CFloat_Subtract:                                             *
 *              Performs complex subtraction, z - w.                          *
 *  Method:                                                                   *
 *      We integrate f(t) exp(i g(t)) by assuming f(t) = constant and         *
 *      g(t) = a t + b. Given g(L) and g(R), we have:                         *
 *                                                                            *
 *             R                       R                                      *
 *             -                       -                                      *
 *            | |                     | |                                     *
 *            |         i g(t)    =   |      i (a t + b)                      *
 *          | |   f(t) e       dt   | |   c e            dt                   *
 *           -                       -                                        *
 *           L                       L                                        *
 *                                                                            *
 *                                            R                               *
 *                                            -                               *
 *                                           | |                              *
 *                                =    i b   |    i a t                       *
 *                                  c e    | |   e      dt                    *
 *                                          -                                 *
 *                                          L                                 *
 *                                                                            *
 *                                            -                 -             *
 *                                   c   i b |   i a R    i a L  |            *
 *                                = --- e    |  e      - e       |            *
 *                                  i a      |                   |            *
 *                                            -                 -             *
 *                                                                            *
 *                                       -                   -                *
 *                                   c  |   i g(R)    i g(L)  |               *
 *                                = --- |  e       - e        |               *
 *                                  i a |                     |               *
 *                                       -                   -                *
 *                                                                            *
 *                                                    -                   -   *
 *                                         R  -  L   |   i g(R)    i g(L)  |  *
 *                                = -i c ----------- |  e       - e        |  *
 *                                       g(R) - g(L) |                     |  *
 *                                                    -                   -   *
 *                                                                            *
 *      This expression is returned, except for when |g(R) - g(L)| is small.  *
 *      In this case the trapezoid rule is used to integrate across the bin.  *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_integration.h:                                                   *
 *          Header file containing the function prototype.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header providing the absolute value function.                     *
 *  3.) tmpl_complex.h:                                                       *
 *          Header providing complex numbers and complex arithmetic.          *
 *  4.) tmpl_float.h:                                                         *
 *          Header providing the TMPL_SQRT_FLT_EPS macro.                     *
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

/*  TMPL_SQRT_FLT_EPS macro provided here.                                    */
#include <libtmpl/include/tmpl_float.h>

/*  Function for numerically integrating using a Filon-like quadrature.       */
tmpl_ComplexFloat
tmpl_Float_Filon01_Integrand(const float value,
                             const float g_left,
                             const float g_right,
                             const float width)
{
    /*  Variable for the output, the integral of f(t) exp(i g(t)) across the  *
     *  current bin [L, R], with R - L = width.                               */
    tmpl_ComplexFloat integrand;

    /*  Threshold for swapping between Filon integral and trapezoidal rule.   */
    const float threshold = 4.0F * TMPL_SQRT_FLT_EPS;

    /*  Both methods need exp(i g(t)) evaluated at the two endpoints.         */
    const tmpl_ComplexFloat left_exp = tmpl_CFloat_Expi(g_left);
    const tmpl_ComplexFloat right_exp = tmpl_CFloat_Expi(g_right);

    /*  Lastly, the value g(R) - g(L) has two uses. First, it is used for     *
     *  determining if we should use the trapezoidal rule or the Filon method.*
     *  Second, it occurs in the scale factor for the Filon integral.         */
    const float g_diff = g_right - g_left;

    /*  Check if |g(R) - g(L)| is small since this may be a source of         *
     *  catastrophic cancellation when the difference is tiny. We use the     *
     *  trapezoidal rule in this case.                                        */
    if (tmpl_Float_Abs(g_diff) < threshold)
    {
        /*  The trapezoid rule averages the left and right endpoints. This is *
         *  the midpoint in the complex plane of exp(i g(R)) and exp(i g(L)). */
        integrand = tmpl_CFloat_Midpoint(left_exp, right_exp);

        /*  The output is then scaled by the width of the bin, similar to how *
         *  the Riemann sum of a function involves a "Delta t" factor.        */
        tmpl_CFloat_MultiplyBy_Real(&integrand, width);
    }

    /*  If |g(R) - g(L)| is large enough, we may safely use the Filon method. *
     *  Indeed, if |g(R) - g(L)| is very large, then the trapezoid rule will  *
     *  produce a poor numerical integral since it is not suited for rapidly  *
     *  oscillating functions, such as exp(i g(t)).                           */
    else
    {
        /*  The integral is:                                                  *
         *                                                                    *
         *         R                                                          *
         *         -                                      -                -  *
         *        | |                          R  -  L   |  i g(R)   i g(L) | *
         *        |         i g(t)    = -i c ----------- | e      - e       | *
         *      | |   f(t) e       dt        g(R) - g(L) |                  | *
         *       -                                        -                -  *
         *       L                                                            *
         *                                                                    *
         *  where we assume f(t) = c, a constant across the entire bin. The   *
         *  real scale factor is the width divided by g(R) - g(L).            */
        const float rcpr_slope = width / g_diff;

        /*  Compute the difference that appears inside the parentheses.       */
        integrand = tmpl_CFloat_Subtract(right_exp, left_exp);

        /*  Next, scale by the factor width / (g(R) - g(L)). The product with *
         *  "c" is computed outside of this branch, it is common to both the  *
         *  trapezoidal method and the Filon integral.                        */
        tmpl_CFloat_MultiplyBy_Imag(&integrand, -rcpr_slope);
    }

    /*  We treat f(t) as constant across the window. Scale the integral by    *
     *  this factor to complete the calculation.                              */
    tmpl_CFloat_MultiplyBy_Real(&integrand, value);
    return integrand;
}
/*  End of tmpl_Float_Filon01_Integrand.                                      */
