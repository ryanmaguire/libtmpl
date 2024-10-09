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
 *                tmpl_normalized_fresnel_cos_maclaurin_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for small values.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Maclaurin                          *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1/4.                                          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_MACLAURIN_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_MACLAURIN_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.4674011002723396547086227499690377838284248518102E-01L)
#define A02 (+2.8185500877894223737395929597426247468092472706217E-02L)
#define A03 (-1.6048831356425354517732028640031047991239608842165E-03L)
#define A04 (+5.4074133814083916484806836575244811935907384032297E-05L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.4674011002723396547086227499690377838284248518102E-01L)
#define A02 (+2.8185500877894223737395929597426247468092472706217E-02L)
#define A03 (-1.6048831356425354517732028640031047991239608842165E-03L)
#define A04 (+5.4074133814083916484806836575244811935907384032297E-05L)
#define A05 (-1.2000972558600288324310962729212634699212444683848E-06L)
#define A06 (+1.8843499115272686014681109020370680079770232568362E-08L)
#define A07 (-2.2022769254454662900309959327905973786515299091400E-10L)
#define A08 (+1.9896857924180219279423678843027396003936259671302E-12L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.4674011002723396547086227499690377838284248518102E-01L)
#define A02 (+2.8185500877894223737395929597426247468092472706217E-02L)
#define A03 (-1.6048831356425354517732028640031047991239608842165E-03L)
#define A04 (+5.4074133814083916484806836575244811935907384032297E-05L)
#define A05 (-1.2000972558600288324310962729212634699212444683848E-06L)
#define A06 (+1.8843499115272686014681109020370680079770232568362E-08L)
#define A07 (-2.2022769254454662900309959327905973786515299091400E-10L)
#define A08 (+1.9896857924180219279423678843027396003936259671302E-12L)
#define A09 (-1.4309189731715199356561699433190725623229133502630E-14L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

#else

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (-2.4674011002723396547086227499690377838284248518102E-01L)
#define A02 (+2.8185500877894223737395929597426247468092472706217E-02L)
#define A03 (-1.6048831356425354517732028640031047991239608842165E-03L)
#define A04 (+5.4074133814083916484806836575244811935907384032297E-05L)
#define A05 (-1.2000972558600288324310962729212634699212444683848E-06L)

/*  Helper macro for evaluating the polynomial using Horner's method.         */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

#endif

/*  Computes the normalized Fresnel cosine for |x| < 1/4.                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Maclaurin(long double x)
{
    /*  The series is in terms of x^4. Compute this.                          */
    const long double xsq = x*x;
    const long double xqt = xsq*xsq;

    /*  Evaluate using Horner's method and return.                            */
    const long double poly = TMPL_POLY_EVAL(xqt);
    return x*poly;
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Cos_Maclaurin.                     */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
