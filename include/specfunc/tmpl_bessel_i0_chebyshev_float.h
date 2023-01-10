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
 *                      tmpl_bessel_i0_chebyshev_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Chebyshev expansion of I0(x) at single precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Bessel_I0_Asymptotic                                       *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) for large positive x.      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (float):                                                         *
 *          The asymptotic expansion of x.                                    *
 *  Called Functions:                                                         *
 *      tmpl_Float_Exp_Pos_Kernel (tmpl_math.h):                              *
 *          Computes exp(x) for x > 1.                                        *
 *      tmpl_Float_Sqrt (tmpl_math.h):                                        *
 *          Computes the square root of a real number.                        *
 *  Method:                                                                   *
 *      Compute using a Chebyshev approximation on the interval [8, infty].   *
 *      The function:                                                         *
 *                                                                            *
 *               16                                                           *
 *          y = ---- - 1                                                      *
 *                x                                                           *
 *                                                                            *
 *      Transforms the interval [8, infty] to [-1, 1]. We then compute the    *
 *      Chebyshev coefficients for the function:                              *
 *                                                                            *
 *          f(x) = exp(-x) I0(y) sqrt(x)                                      *
 *                                                                            *
 *      We can accurately compute f(x) using a degree 4 Chebyshev expansion:  *
 *                                                                            *
 *                   4                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     c_n T_n(x)                                           *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where c_n are the coefficients and T_n is the nth Chebyshev           *
 *      polynomial. We further simplify this into a proper polynomial form    *
 *      by expanding the Chebyshev polynomials.                               *
 *                                                                            *
 *                             --                   --                        *
 *                   4        |    n                  |                       *
 *                 -----      |  -----                |                       *
 *                 \          |  \                    |                       *
 *          f(x) = /      c_n |  /      t_{k, n} x^k  |                       *
 *                 -----      |  -----                |                       *
 *                 n = 0      |  k = 0                |                       *
 *                             --                   --                        *
 *                                                                            *
 *      where t_{k, n} is the kth coefficients of the nth Chebyshev           *
 *      polynomial. By collecting all of the terms together we get:           *
 *                                                                            *
 *                   4                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     a_n x^n                                              *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where the a_n are computed from c_n and t_{k, n} via a Cauchy product.*
 *      This is evaluated by Horner's method, which is faster than Clenshaw's *
 *      algorithm for Chebyshev polynomials in their usual form.              *
 *                                                                            *
 *      Labelling this final sum as P(x), we can compute I0(x) via:           *
 *                                                                            *
 *          I0(x) = exp(x) P(x) / sqrt(x)                                     *
 *                                                                            *
 *  Notes:                                                                    *
 *      Accurate to single precision for x >= 8.                              *
 *      For x < 8 use the Maclaurin series.                                   *
 *      For large x (x > 32) this function is accurate to single precision,   *
 *      but slower than the asymptotic expansion. It is better to use that    *
 *      function if you know your input is big.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing exp and sqrt functions.                    *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_CHEBYSHEV_FLOAT_H
#define TMPL_BESSEL_I0_CHEBYSHEV_FLOAT_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support not requested.                            */
#if TMPL_USE_INLINE == 1

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+4.0217651281544419447047960448250442909482335336723E-01F)
#define A01 (+3.3604423666931898204489558577302695335866457257916E-03F)
#define A02 (+1.3615603206676122869179069858747689293009803916936E-04F)
#define A03 (+1.1565482083339025931867696092931785527714979765842E-05F)
#define A04 (+1.6391348715752509934620842727450528126917919506391E-06F)

/*  Helper macro for computing the polynomial via Horner's method.            */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Function for computing I0(x) using a Chebyshev expansion for x >= 8.      */
TMPL_INLINE_DECL
float tmpl_Float_Bessel_I0_Chebyshev(float x)
{
    /*  y = 16/x - 1 transforms [8, infty] to [-1, 1], the domain of the      *
     *  Chebyshev polynomials. The polynomial is in terms of y.               */
    const float y = 16.0F/x - 1.0F;

    /*  Evaluate the polynomial using Horner's method.                        */
    const float poly = TMPL_POLY_EVAL(y);

    /*  The Chebyshev expansion is for exp(-x) I0(x) * sqrt(x). Compute I0(x) *
     *  by scaling the polynomial by exp(x) / sqrt(x).                        */
    const float sqrt_x = tmpl_Float_Sqrt(x);
    const float exp_x = tmpl_Float_Exp_Pos_Kernel(x);
    return exp_x * poly / sqrt_x;
}
/*  End of tmpl_Float_Bessel_I0_Chebyshev.                                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
