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
 *                      tmpl_filon11_integrand_cldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the integral of f(t) exp(i g(t)) assuming affine f and g,    *
 *      f(t) = at + b (a and b are complex), g(t) = ct + d (c and d are real).*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Filon11_Integrand                                       *
 *  Purpose:                                                                  *
 *      Numerically integrates f(t) exp(i g(t)) assuming f(t) = a t + b       *
 *      (a and b are complex), and g(t) = c t + d (c and d are real).         *
 *  Arguments:                                                                *
 *      left (const tmpl_ComplexLongDouble):                                  *
 *          The value for f at the left end of the bin.                       *
 *      right (const tmpl_ComplexLongDouble):                                 *
 *          The value for f at the right end of the bin.                      *
 *      g_left (const long double):                                           *
 *          The left real value for the phase.                                *
 *      g_right (const long double):                                          *
 *          The right real value for the phase.                               *
 *      width (const long double):                                            *
 *          The width of the bin.                                             *
 *  Output:                                                                   *
 *      integrand (tmpl_ComplexLongDouble):                                   *
 *          The integral of f(t) exp(i g(t)).                                 *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_Abs:                                                 *
 *              Computes the absolute value of a real number.                 *
 *      src/complex/                                                          *
 *          tmpl_CLDouble_Expi:                                               *
 *              Creates a point on the unit circle, z = exp(i theta).         *
 *          tmpl_CLDouble_Midpoint:                                           *
 *              Computes the midpoint of two points in the complex plane.     *
 *          tmpl_CLDouble_Multiply:                                           *
 *              Performs complex multiplication, z = w0 * w1.                 *
 *          tmpl_CLDouble_MultiplyBy:                                         *
 *              Performs z *= w.                                              *
 *          tmpl_CLDouble_Multiply_Imag:                                      *
 *              Perform z = w * i * r where r is real.                        *
 *          tmpl_CLDouble_MultiplyBy_Real:                                    *
 *              Performs z *= r where r is real.                              *
 *          tmpl_CLDouble_Subtract:                                           *
 *              Performs complex subtraction, z - w.                          *
 *          tmpl_CLDouble_SubtractFrom:                                       *
 *              Performs z -= w.                                              *
 *  Method:                                                                   *
 *      We write f(t) = a t + b and g(t) = c t + d, and then obtain:          *
 *                                                                            *
 *             R                     R                                        *
 *             -                     -                                        *
 *            | |                   | |                 -             -       *
 *            |        i g(t)       |   -       -      |    -       -  |      *
 *            |  f(t) e      dt =   |  | a t + b | exp | i | c t + d | | dt   *
 *          | |                   | |   -       -      |    -       -  |      *
 *           -                     -                    -             -       *
 *           L                     L                                          *
 *                                                                            *
 *                      -                                       -             *
 *                     |       R                    R            |            *
 *                     |       -                    -            |            *
 *                     |      | |                  | |           |            *
 *                 i d |      |     i c t          |   i c t     |            *
 *              = e    |  a   |  t e      dt + b   |  e      dt  |            *
 *                     |    | |                  | |             |            *
 *                     |     -                    -              |            *
 *                     |     L                    L              |            *
 *                      -                                       -             *
 *                                                                            *
 *                        -                                        -          *
 *                   i d |   i R c                i L c             |         *
 *              = a e    |  e      (1 - i R c) - e     (1 - i L c)  |         *
 *                        -                                        -          *
 *                                   -                  -                     *
 *                          b   i d |    i R c    i L c  |                    *
 *                       + --- e    |  e       - e       |                    *
 *                         i c       -                  _                     *
 *                                                                            *
 *      By definition, we have c R + d = g(R) and c L + d = g(L). The         *
 *      above simplifies and becomes:                                         *
 *                                                                            *
 *                                                                            *
 *           i g(R)                i g(L)                                     *
 *          e       (1 - i R c) - e       (1 - i L c)                         *
 *                                                                            *
 *                     -                   -                                  *
 *                    |                     |                                 *
 *                 b  |   i g(R)    i g(L)  |                                 *
 *              + --- |  e       - e        |                                 *
 *                i c |                     |                                 *
 *                     -                   -                                  *
 *                                                                            *
 *      Next, we note that 1 / i = -i, and furthermore that, by definition,   *
 *      we have a R + b = f(R) and a L + b = f(L). The previous expression    *
 *      simplifies even further and becomes:                                  *
 *                                                                            *
 *                   -            -             -            -                *
 *                  |  a           |           |  a           |               *
 *           i g(R) |  - - i f(R)  |    i g(L) |  - - i f(L)  |               *
 *          e       |  c           | - e       |  c           |               *
 *                   -            -             -            -                *
 *          ---------------------------------------------------               *
 *                                   c                                        *
 *                                                                            *
 *      This ratio, a / c, is the ratio of the slopes for f and g. The dt     *
 *      term cancels and we have:                                             *
 *                                                                            *
 *          a   f(R) - f(L)                                                   *
 *          - = -----------                                                   *
 *          c   g(R) - g(L)                                                   *
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
 *          Header providing the TMPL_SQRT_LDBL_EPS macro.                    *
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

/*  TMPL_SQRT_LDBL_EPS macro provided here.                                   */
#include <libtmpl/include/tmpl_float.h>

/*  Function for numerically integrating using a Filon-like quadrature.       */
tmpl_ComplexLongDouble
tmpl_CLDouble_Filon11_Integrand(const tmpl_ComplexLongDouble left,
                                const tmpl_ComplexLongDouble right,
                                const long double g_left,
                                const long double g_right,
                                const long double width)
{
    /*  Variable for the output, the integral of f(t) exp(i g(t)) across the  *
     *  current bin [L, R], with R - L = width.                               */
    tmpl_ComplexLongDouble integrand;

    /*  Various factors for the Filon-like integral.                          */
    tmpl_ComplexLongDouble z_left, z_right, factor;

    /*  Threshold for swapping between Filon integral and trapezoidal rule.   */
    const long double threshold = 4.0L * TMPL_SQRT_LDBL_EPS;

    /*  Both methods need exp(i g(t)) evaluated at the two endpoints.         */
    const tmpl_ComplexLongDouble exp_left = tmpl_CLDouble_Expi(g_left);
    const tmpl_ComplexLongDouble exp_right = tmpl_CLDouble_Expi(g_right);

    /*  Lastly, the value g(R) - g(L) has two uses. First, it is used for     *
     *  determining if we should use the trapezoidal rule or the Filon method.*
     *  Second, it occurs in the scale factor for the Filon integral.         */
    const long double g_diff = g_right - g_left;

    /*  Check if |g(R) - g(L)| is small since this may be a source of         *
     *  catastrophic cancellation when the difference is tiny. We use the     *
     *  trapezoidal rule in this case.                                        */
    if (tmpl_LDouble_Abs(g_diff) < threshold)
    {
        /*  The trapezoidal rule needs f(t) exp(i g(t)) evaluated at both     *
         *  enpoints. Compute these values.                                   */
        z_left = tmpl_CLDouble_Multiply(left, exp_left);
        z_right = tmpl_CLDouble_Multiply(right, exp_right);

        /*  The trapezoid rule averages the left and right endpoints. This is *
         *  the midpoint in the complex plane of the previous values.         */
        integrand = tmpl_CLDouble_Midpoint(z_left, z_right);

        /*  The output is then scaled by the width of the bin, similar to how *
         *  the Riemann sum of a function involves a "Delta t" factor.        */
        tmpl_CLDouble_MultiplyBy_Real(&integrand, width);
    }

    /*  If |g(R) - g(L)| is large enough, we may safely use the Filon method. *
     *  Indeed, if |g(R) - g(L)| is very large, then the trapezoid rule will  *
     *  produce a poor numerical integral since it is not suited for rapidly  *
     *  oscillating functions, such as exp(i g(t)).                           */
    else
    {
        /*  The integral is:                                                  *
         *                                                                    *
         *                                    -       -            -       -  *
         *         R                         |a        |          |a        | *
         *         -                   ig(R) |- - if(R)|    ig(L) |- - if(L)| *
         *        | |                 e      |c        | - e      |c        | *
         *        |        ig(t)              -       -            -       -  *
         *      | |  f(t) e     dt  = --------------------------------------- *
         *       -                                       c                    *
         *       L                                                            *
         *                                                                    *
         *  a / c is given by the ratio (f(R) - f(L)) / (g(R) - g(L)), and c  *
         *  is the difference g(R) - g(L) divided by the width. Compute these.*/
        const long double rcpr_slope = width / g_diff;

        /*  Next, compute (f(R) - f(L)) / (g(R) - g(L)).                      */
        factor = tmpl_CLDouble_Subtract(right, left);
        tmpl_CLDouble_MultiplyBy_Real(&factor, 1.0L / g_diff);

        /*  Next, compute exp(i g(L)) (i f(L) - a / c).                       */
        z_left = tmpl_CLDouble_Multiply_Imag(1.0L, left);
        tmpl_CLDouble_SubtractFrom(&z_left, &factor);
        tmpl_CLDouble_MultiplyBy(&z_left, &exp_left);

        /*  Now compute exp(i g(R)) (i f(R) - a / c).                         */
        z_right = tmpl_CLDouble_Multiply_Imag(1.0L, right);
        tmpl_CLDouble_SubtractFrom(&z_right, &factor);
        tmpl_CLDouble_MultiplyBy(&z_right, &exp_right);

        /*  We have computed the expressions exp(i g(L)) (i f(L) - a / c) and *
         *  exp(i g(R)) (i f(R) - a / c), and we need:                        *
         *                                                                    *
         *               -           -             -           -              *
         *              |  a          |           |  a          |             *
         *       i g(R) |  - - if(R)  |    i g(L) |  - - if(L)  |             *
         *      e       |  c          | - e       |  c          |             *
         *               -           -             -           -              *
         *      -------------------------------------------------             *
         *                              c                                     *
         *                                                                    *
         *  We can get this by factoring the minus sign, giving us the        *
         *  difference z_left - z_right.                                      */
        integrand = tmpl_CLDouble_Subtract(z_left, z_right);

        /*  Finally, divide the current expression by "c".                    */
        tmpl_CLDouble_MultiplyBy_Real(&integrand, rcpr_slope);
    }

    return integrand;
}
/*  End of tmpl_CLDouble_Filon11_Integrand.                                   */
