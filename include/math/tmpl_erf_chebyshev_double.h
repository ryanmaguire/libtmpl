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
 *                         tmpl_erf_chebyshev_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes erf(x) using a Chebyshev expansion at double precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Chebyshev                                             *
 *  Purpose:                                                                  *
 *      Computes the Error function erf(x) using a Chebyshev expansion.       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function at x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Pre-compute the coefficients for the function:                        *
 *                                                                            *
 *          f(x) = erf(x)                                                     *
 *                                                                            *
 *      We can accurately compute f(x) using a degree 23 Chebyshev expansion: *
 *                                                                            *
 *                  23                                                        *
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
 *                  23        |    n                  |                       *
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
 *                  23                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     a_n x^n                                              *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where the a_n are computed from c_n and t_{k, n} via a Cauchy product.*
 *      This is evaluated by Horner's method, which is faster than Clenshaw's *
 *      algorithm for Chebyshev polynomials in their usual form. The even     *
 *      coefficients vanish, meaning we only need 12 non-zero coefficients.   *
 *  Notes:                                                                    *
 *      Accurate for |x| <= 1 to double precision.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_CHEBYSHEV_DOUBLE_H
#define TMPL_ERF_CHEBYSHEV_DOUBLE_H

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is requested.                             */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955124849729221417042495062358233113712E+00)
#define A01 (-3.7612638903182824648843587122717143708717045801919E-01)
#define A02 (+1.1283791670926438759054471783181517556718393172443E-01)
#define A03 (-2.6866170641014075567916794166599359503695991092998E-02)
#define A04 (+5.2239775923171535274264124244005143458729940975559E-03)
#define A05 (-8.5483253735567970597848575977068696543670423761656E-04)
#define A06 (+1.2055279185329653458904604295658345862349757918905E-04)
#define A07 (-1.4924467745308758735274997777339385676647640149219E-05)
#define A08 (+1.6444419566296082937771157879511635103139152729031E-06)
#define A09 (-1.6187414949452059587524584529136346487576728041821E-07)
#define A10 (+1.3635860776918529656875941020687253644059118429705E-08)
#define A11 (-7.6495705819715733731829201232902172942240572385993E-10)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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
                                        A10 + z*A11\
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

/*  Function for computing erf(x) via a Chebyshev expansion.                  */
TMPL_INLINE_DECL
double tmpl_Double_Erf_Chebyshev(double x)
{
    /*  The expansion is odd, in terms of x^{2n+1}. Compute x^2.              */
    const double x2 = x*x;

    /*  Compute the polynomial using Horner's method and return.              */
    const double poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_Double_Erf_Chebyshev.                                         */

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
#undef A09
#undef A10
#undef A11

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
