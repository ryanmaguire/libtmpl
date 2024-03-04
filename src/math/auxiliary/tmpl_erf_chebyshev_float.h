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
 *                         tmpl_erf_chebyshev_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes erf(x) using a Chebyshev expansion at single precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Erf_Chebyshev                                              *
 *  Purpose:                                                                  *
 *      Computes the Error function erf(x) using a Chebyshev expansion.       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (float):                                                        *
 *          The error function at x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Pre-compute the coefficients for the function:                        *
 *                                                                            *
 *          f(x) = erf(x)                                                     *
 *                                                                            *
 *      We can accurately compute f(x) using a degree 17 Chebyshev expansion: *
 *                                                                            *
 *                  17                                                        *
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
 *                  17        |    n                  |                       *
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
 *                  17                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     a_n x^n                                              *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where the a_n are computed from c_n and t_{k, n} via a Cauchy product.*
 *      This is evaluated by Horner's method, which is faster than Clenshaw's *
 *      algorithm for Chebyshev polynomials in their usual form. The even     *
 *      coefficients vanish, meaning we only need 9 non-zero coefficients.    *
 *  Notes:                                                                    *
 *      Accurate for |x| <= 1 to single precision.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_CHEBYSHEV_FLOAT_H
#define TMPL_ERF_CHEBYSHEV_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the Chebyshev approximation.                             */
#define A00 (+1.1283791670946951024809474862174668105183751824960E+00F)
#define A01 (-3.7612638889869284098755643668473565725785600761236E-01F)
#define A02 (+1.1283791313499398347721128221776189750630201743053E-01F)
#define A03 (-2.6866133625492237775254611171823416553611963113548E-02F)
#define A04 (+5.2237850070906597171947962407091732468823163882248E-03F)
#define A05 (-8.5426705677322353647348336032581653227396925883265E-04F)
#define A06 (+1.1956946823921660991625557778337204567795402349135E-04F)
#define A07 (-1.3911701148502927370695656041773602640771486545003E-05F)
#define A08 (+1.0595275841880362072933312414795383309830002963017E-06F)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Function for computing erf(x) via a Chebyshev expansion.                  */
TMPL_STATIC_INLINE
float tmpl_Float_Erf_Chebyshev(float x)
{
    /*  The expansion is odd, in terms of x^{2n+1}. Compute x^2.              */
    const float x2 = x*x;

    /*  Compute the polynomial using Horner's method and return.              */
    const float poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_Float_Erf_Chebyshev.                                          */

/*  #undef everything in case someone wants to #include this file.            */
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

#endif
/*  End of include guard.                                                     */
