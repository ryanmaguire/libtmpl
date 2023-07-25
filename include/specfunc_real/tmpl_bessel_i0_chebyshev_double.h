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
 *                      tmpl_bessel_i0_chebyshev_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Chebyshev expansion of I0(x) at double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_I0_Asymptotic                                      *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) for large positive x.      *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (double):                                                        *
 *          The asymptotic expansion of x.                                    *
 *  Called Functions:                                                         *
 *      tmpl_Double_Exp_Pos_Kernel (tmpl_math.h):                             *
 *          Computes exp(x) for x > 1.                                        *
 *      tmpl_Double_Sqrt (tmpl_math.h):                                       *
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
 *      We can accurately compute f(x) using a degree 20 Chebyshev expansion: *
 *                                                                            *
 *                  20                                                        *
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
 *                  20        |    n                  |                       *
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
 *                  20                                                        *
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
 *      Accurate to double precision for x >= 8.                              *
 *      For x < 8 use the Maclaurin series.                                   *
 *      For large x (x > 64) this function is accurate to double precision,   *
 *      but slower than the asymptotic expansion. It is better to use that    *
 *      function if you know your input is big.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing exp and sqrt functions.                    *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_CHEBYSHEV_DOUBLE_H
#define TMPL_BESSEL_I0_CHEBYSHEV_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here.                                        */
#include <libtmpl/include/tmpl_config.h>

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+4.0217650944500812912412062682554015864758708641122E-01)
#define A01 (+3.3605519836670235954708677573057674903333246992903E-03)
#define A02 (+1.3621607437904054799841758982479293811131516929561E-04)
#define A03 (+1.1143033854011811083558679211638434062764248318695E-05)
#define A04 (+1.4838480973971800609046361672889019897024382546250E-06)
#define A05 (+2.9735845331509646125662538478643653991903153361183E-07)
#define A06 (+8.8713600387547075477658297578709122469344322090695E-08)
#define A07 (+3.9340297511352998278016448937536069448254634984065E-08)
#define A08 (+2.1620199017859248534590406397671142859637435618941E-08)
#define A09 (+7.4722687049004145531137867656084079636040012667167E-09)
#define A10 (-7.1010934904762743075955916676338088713004980913523E-09)
#define A11 (-1.3122900132993169208905971014542520951427694412370E-08)
#define A12 (-4.3057274269883615152914097212223008069764561812301E-09)
#define A13 (+6.9191599461531431879847335005129655312558821369738E-09)
#define A14 (+5.1919580836693996439994143159719873913638489213162E-09)
#define A15 (-2.5947610525034173704628552617722105818086735464970E-09)
#define A16 (-2.9337366286377845325039494204330159462216768587498E-09)
#define A17 (+6.7633829293190930605818684065514625993663001150591E-10)
#define A18 (+9.7357766250852428722851597292198387294250385367379E-10)
#define A19 (-8.9797050228466493282562812742470450345111126838963E-11)
#define A20 (-1.4824893214970785221533004978797389957959905477607E-10)

/*  Helper macro for evaluating a polynomial using Horner's method.           */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*(\
                  A09 + z*(\
                    A10 + z*(\
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*A20\
                                    )\
                                  )\
                                )\
                              )\
                            )\
                          )\
                        )\
                      )\
                    )\
                  )\
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Function for computing I0(x) using a Chebyshev expansion for x >= 8.      */
TMPL_INLINE_DECL
double tmpl_Double_Bessel_I0_Chebyshev(double x)
{
    /*  y = 16/x - 1 transforms [8, infty] to [-1, 1], the domain of the      *
     *  Chebyshev polynomials. The polynomial is in terms of y.               */
    const double y = 16.0/x - 1.0;

    /*  Evaluate the polynomial using Horner's method.                        */
    const double poly = TMPL_POLY_EVAL(y);

    /*  The Chebyshev expansion is for exp(-x) I0(x) * sqrt(x). Compute I0(x) *
     *  by scaling the polynomial by exp(x) / sqrt(x).                        */
    const double sqrt_x = tmpl_Double_Sqrt(x);
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    return exp_x * poly / sqrt_x;
}
/*  End of tmpl_Double_Bessel_I0_Chebyshev.                                   */

/*  Undef everything in case someone wants to #include this file.             */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20

#endif
/*  End of include guard.                                                     */
