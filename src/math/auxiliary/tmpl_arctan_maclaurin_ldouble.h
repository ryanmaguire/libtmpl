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
 *                        tmpl_arctan_maclaurin_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arctan_Maclaurin                                         *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) for small values x.          *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (long double):                                                 *
 *          The Maclaurin series of atan(x).                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                      infty                                                 *
 *                      -----                                                 *
 *                      \         (-1)^n                                      *
 *          atan(x) =   /        -------- * x^{2n+1}                          *
 *                      -----    (2n + 1)                                     *
 *                      n = 0                                                 *
 *                                                                            *
 *  64-Bit Double Version:                                                    *
 *      Use the first 9 terms (0 <= n <= 8) of this expansion to compute.     *
 *  80-Bit Extended / 128-Bit Quadruple / 128-Bit Double-Double / Portable:   *
 *      Use the first 12 terms (0 <= n <= 11) of this expansion to compute.   *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 0.15 this function is       *
 *      accurate to extended precision (10^-19 relative error) (for the       *
 *      64-bit version it is accurate to double precision, 10^-16, for        *
 *      |x| < 0.15). The larger the input is, the worse the error. By the     *
 *      alternating series theorem, the absolute error is bounded by          *
 *      (1/25)*|x|^25, or (1/19)*|x|^19 for the 64-bit version.               *
 *                                                                            *
 *      If you need quadruple precision, use the Pade approximation. The      *
 *      Maclaurin series needs a lot of terms to get 10^-34 relative error.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_MACLAURIN_LDOUBLE_H
#define TMPL_ARCTAN_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at double precision.                */
#define A00 (+1.00000000000000000000000000000E+00L)
#define A01 (-3.33333333333333333333333333333E-01L)
#define A02 (+2.00000000000000000000000000000E-01L)
#define A03 (-1.42857142857142857142857142857E-01L)
#define A04 (+1.11111111111111111111111111111E-01L)
#define A05 (-9.09090909090909090909090909090E-02L)
#define A06 (+7.69230769230769230769230769231E-02L)
#define A07 (-6.66666666666666666666666666667E-02L)
#define A08 (+5.88235294117647058823529411765E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-Bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A00 (+1.00000000000000000000000000000000000E+00L)
#define A01 (-3.33333333333333333333333333333333333E-01L)
#define A02 (+2.00000000000000000000000000000000000E-01L)
#define A03 (-1.42857142857142857142857142857142857E-01L)
#define A04 (+1.11111111111111111111111111111111111E-01L)
#define A05 (-9.09090909090909090909090909090909091E-02L)
#define A06 (+7.69230769230769230769230769230769231E-02L)
#define A07 (-6.66666666666666666666666666666666667E-02L)
#define A08 (+5.88235294117647058823529411764705882E-02L)
#define A09 (-5.26315789473684210526315789473684211E-02L)
#define A10 (+4.76190476190476190476190476190476190E-02L)
#define A11 (-4.34782608695652173913043478260869565E-02L)

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

#endif
/*  End difference between 64-bit long double and higher precisions.          */

/*  Taylor series centered at x0 = 0 for atan(x).                             */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arctan_Maclaurin(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    const long double poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_LDouble_Arctan_Maclaurin.                                     */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
