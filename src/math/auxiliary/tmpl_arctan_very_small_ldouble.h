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
 *                   tmpl_arctan_very_small_ldouble_inline                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of atan(x) at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arctan_Very_Small                                        *
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
 *      Use the first 6 terms (0 <= n <= 5) of this expansion to compute.     *
 *  80-Bit Extended / 128-Bit Quadruple / 128-Bit Double-Double / Portable:   *
 *      Use the first 8 terms (0 <= n <= 7) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      Only accurate for small values. For |x| < 1/32 this function is       *
 *      accurate to extended precision (10^-19 relative error) (for the       *
 *      64-bit version it is accurate to double precision, 10^-16, for        *
 *      |x| < 1/32). The larger the input is, the worse the error. By the     *
 *      alternating series theorem, the absolute error is bounded by          *
 *      (1/19)*|x|^19, or (1/13)*|x|^13 for the 64-bit version.               *
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
#ifndef TMPL_ARCTAN_VERY_SMALL_LDOUBLE_H
#define TMPL_ARCTAN_VERY_SMALL_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at double precision.                */
#define A0 (+1.00000000000000000000000000000E+00L)
#define A1 (-3.33333333333333333333333333333E-01L)
#define A2 (+2.00000000000000000000000000000E-01L)
#define A3 (-1.42857142857142857142857142857E-01L)
#define A4 (+1.11111111111111111111111111111E-01L)
#define A5 (-9.09090909090909090909090909090E-02L)

/*  Maclaurin series for arctan, double precision, to 6 terms.                */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arctan_Very_Small(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*A5)))));
}
/*  End of tmpl_LDouble_Arctan_Very_Small.                                    */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-Bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A0 (+1.00000000000000000000000000000000000E+00L)
#define A1 (-3.33333333333333333333333333333333333E-01L)
#define A2 (+2.00000000000000000000000000000000000E-01L)
#define A3 (-1.42857142857142857142857142857142857E-01L)
#define A4 (+1.11111111111111111111111111111111111E-01L)
#define A5 (-9.09090909090909090909090909090909091E-02L)
#define A6 (+7.69230769230769230769230769230769231E-02L)
#define A7 (-6.66666666666666666666666666666666667E-02L)

/*  Taylor series centered at x0 = 0 for atan(x).                             */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arctan_Very_Small(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*A7)))))));
}
/*  End of tmpl_LDouble_Arctan_Very_Small.                                    */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7

#endif
/*  End difference between 64-bit long double and higher precisions.          */

#endif
/*  End of include guard.                                                     */
