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
 *                tmpl_normalized_fresnel_sin_maclaurin_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin_Maclaurin                          *
 *  Purpose:                                                                  *
 *      Computes S(x) for |x| < 1/4.                                          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the Maclaurin series for |x| < 1 / 4 using the first 5 terms  *
 *      (0 <= n <= 4). The series is defined by:                              *
 *                                                                            *
 *                 infty                                                      *
 *                 -----       n  4n+1  -   -  2n                             *
 *                 \       (-1)  x     | pi  |                                *
 *          C(x) = /       ----------- | --- |                                *
 *                 -----   (4n+1)(2n)!  - 2 -                                 *
 *                 n = 0                                                      *
 *                                                                            *
 *      The sum is performed using Horner's method.                           *
 *  Notes:                                                                    *
 *      This function assumes the input is bounded by 1/4.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_MACLAURIN_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_SIN_MACLAURIN_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the polynomial.                                          */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-9.2280585358035179093679509128277961911384787398468E-02L)
#define A02 (+7.2447842041970041018641408627707293200828765773692E-03L)
#define A03 (-3.1211694235457920671236426226356252396633520123340E-04L)
#define A04 (+8.4442728835452537827716247454459647212003968747690E-06L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the polynomial.                                          */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-9.2280585358035179093679509128277961911384787398468E-02L)
#define A02 (+7.2447842041970041018641408627707293200828765773692E-03L)
#define A03 (-3.1211694235457920671236426226356252396633520123340E-04L)
#define A04 (+8.4442728835452537827716247454459647212003968747690E-06L)
#define A05 (-1.5647144500922110175906695731340823499515196662748E-07L)
#define A06 (+2.1082121933214543747315760383674756936677147244647E-09L)
#define A07 (-2.1574306805843442685413633341235931257923454792594E-11L)
#define A08 (+1.7334102088874844763146987615220400200474866460371E-13L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the polynomial.                                          */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-9.2280585358035179093679509128277961911384787398468E-02L)
#define A02 (+7.2447842041970041018641408627707293200828765773692E-03L)
#define A03 (-3.1211694235457920671236426226356252396633520123340E-04L)
#define A04 (+8.4442728835452537827716247454459647212003968747690E-06L)
#define A05 (-1.5647144500922110175906695731340823499515196662748E-07L)
#define A06 (+2.1082121933214543747315760383674756936677147244647E-09L)
#define A07 (-2.1574306805843442685413633341235931257923454792594E-11L)
#define A08 (+1.7334102088874844763146987615220400200474866460371E-13L)
#define A09 (-1.1223244787983954556882746958400818191956146230985E-15L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

#else

/*  Coefficients for the polynomial.                                          */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-9.2280585358035179093679509128277961911384787398468E-02L)
#define A02 (+7.2447842041970041018641408627707293200828765773692E-03L)
#define A03 (-3.1211694235457920671236426226356252396633520123340E-04L)
#define A04 (+8.4442728835452537827716247454459647212003968747690E-06L)
#define A05 (-1.5647144500922110175906695731340823499515196662748E-07L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

#endif

/*  Computes the normalized Fresnel sine for |x| < 1/4.                       */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Sin_Maclaurin(long double x)
{
    /*  The series is in terms of x^4. Compute this.                          */
    const long double xsq = x*x;
    const long double xqt = xsq*xsq;

    /*  Evaluate using Horner's method and return.                            */
    const long double poly = TMPL_POLY_EVAL(xqt);
    return x * xsq * poly;
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Sin_Maclaurin.                     */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
