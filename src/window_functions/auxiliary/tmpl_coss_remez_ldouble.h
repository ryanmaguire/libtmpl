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
 *                           tmpl_coss_remez_ldouble                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for small x.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Coss_Remez                                               *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a Remez polynomial for very  *
 *      small arguments.                                                      *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (long double):                                                 *
 *          The squared cosine window of x.                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree N Remez polynomial for the function f *
 *      given by:                                                             *
 *                                                                            *
 *                 Coss(x) - 1                                                *
 *          f(x) = -----------                                                *
 *                      2                                                     *
 *                     x                                                      *
 *                                                                            *
 *      where Coss is the squared cosine function, have been pre-computed on  *
 *      the interval [-1/32, 1/32]. The value of N depends on how long double *
 *      is implemented:                                                       *
 *                                                                            *
 *          Implementation        | Degree                                    *
 *          ------------------------------                                    *
 *          64-bit double         |      8                                    *
 *          80-bit extended       |     10                                    *
 *          128-bit double-double |     16                                    *
 *          128-bit quadruple     |     16                                    *
 *                                                                            *
 *      Since this function is even, only (N / 2) + 1 of the terms in this    *
 *      polynomial are non-zero. We compute this polynomial using Horner's    *
 *      method and then return the expression 1 + x^2 P(x), where P is the    *
 *      Remez polynomial for f.                                               *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for |x| < 0.03125.              *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 7, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSS_REMEZ_LDOUBLE_H
#define TMPL_COSS_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degree of the polynomial depends on how long double is implemented.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  64-bit long double, same precision as 64-bit double.                      */
#define A00 (-9.8696044010893586119836260840774741547271037159709E+00L)
#define A01 (+3.2469697011333794966195903621248838725905850741607E+01L)
#define A02 (-4.2728408600473142670686338279929914223019474160613E+01L)
#define A03 (+3.0122312445849250846578813021034951028609016100578E+01L)
#define A04 (-1.3203483943106073019872003713083216380928644648296E+01L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  128-bit quadruple and 128-bit double-double conveniently need the same    *
 *  number of terms to achieve 1 ULP (~10^-34 and ~10^-32, respectively).     */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT || \
      TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                     128-bit Double-Double / Quadruple                      *
 ******************************************************************************/

/*  Degree 16 Remez polynomial, peak theoretical error ~1.16 x 10^-35.        */
#define A00 (-9.8696044010893586188344909998761511236828201067713E+00L)
#define A01 (+3.2469697011334145745480110896233107413043878847932E+01L)
#define A02 (-4.2728408603346863868009752998519352486310447598217E+01L)
#define A03 (+3.0122320685938330181360003055964377609285204419685E+01L)
#define A04 (-1.3213128391687198723531918192563805288844800102804E+01L)
#define A05 (+3.9517681856592257676985570720923016790956800944606E+00L)
#define A06 (-8.5719535552933002071480580058191590794512161380408E-01L)
#define A07 (+1.4100296902832470515203371406498414172062725837509E-01L)
#define A08 (-1.8183118034174543575060699112190315001321480228559E-02L)

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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  A degree 10 Remez polynomial is needed for ~10^-19 relative error.        */
#define A00 (-9.8696044010893586188341281679904729448023263077518E+00L)
#define A01 (+3.2469697011334145718728513652028567347298716657861E+01L)
#define A02 (-4.2728408603346544266260173552410134395222943882057E+01L)
#define A03 (+3.0122320684541916923464717086626241449019780618039E+01L)
#define A04 (-1.3213125633816009275982492960655505177476422507006E+01L)
#define A05 (+3.9492576445308184817804711194238581314141607578836E+00L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the squared cosine window using a Remez polynomial.              */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Coss_Remez(const long double x)
{
    /*  The coss function is even, the polynomial is in terms of x^2.         */
    const long double x2 = x * x;

    /*  Evaluate the polynomial using Horner's method.                        */
    const long double poly = TMPL_POLY_EVAL(x2);

    /*  The polynomial is for (Coss(x) - 1) / x^2. Compute Coss from this.    */
    return 1.0L + x2 * poly;
}
/*  End of tmpl_LDouble_Coss_Remez.                                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
