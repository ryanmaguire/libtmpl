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
 *                   tmpl_arctan_asymptotic_ldouble_inline                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) at long double precision.*
 *      This is the inline version of the one found in src/math.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arctan_Asymptotic                                        *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of atan(x) for large positive x.    *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (long double):                                                 *
 *          The asymptotic expansion of x.                                    *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the reciprocal of x, and the square of this, and use Horner's *
 *      method to efficiently evaluate the polynomial.                        *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                    pi       \         (-1)^n        1                      *
 *          atan(x) ~ ---  -   /       --------- * ---------     x --> infty  *
 *                     2       -----    (2n + 1)    x^{2n+1}                  *
 *                             n = 0                                          *
 *                                                                            *
 *  64-Bit Double Version:                                                    *
 *      Use the first 6 terms (0 <= n <= 5) of this expansion to compute.     *
 *  80-Bit Extended / 128-Bit Quadruple / 128-Bit Double-Double / Portable:   *
 *      Use the first 7 terms (0 <= n <= 6) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      Only accurate for large POSITIVE values. For x > 16, this function    *
 *      is accurate to extended precision (10^-19 relative error) (the        *
 *      64-bit version is accurate to double precision, 10^-16 relative error,*
 *      for x > 16). The closer the input is to zero, the worse the error.    *
 *                                                                            *
 *      This function can be used for large negative values via:              *
 *          atan(x) ~= -tmpl_Double_Arctan_Asymptotic(-x).                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 20, 2022                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/07: Ryan Maguire                                                  *
 *      Added license.                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_ASYMPTOTIC_LDOUBLE_H
#define TMPL_ARCTAN_ASYMPTOTIC_LDOUBLE_H

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion. The expansion is a polynomial  *
 *  of degree 11 in terms of 1/x^{2n+1}. The coefficients are (-1)^n / (2n+1).*/
#define A0 (1.00000000000000000000000000000E+00L)
#define A1 (-3.33333333333333333333333333333E-01L)
#define A2 (2.00000000000000000000000000000E-01L)
#define A3 (-1.42857142857142857142857142857E-01L)
#define A4 (1.11111111111111111111111111111E-01L)
#define A5 (-9.09090909090909090909090909090E-02L)

/*  Long double precision asymptotic expansion for the arctangent function.   */
TMPL_INLINE_DECL
long double tmpl_LDouble_Arctan_Asymptotic(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double z = 1.0L / x;
    const long double z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return tmpl_Pi_By_Two_L -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*A5)))));
}
/*  End of tmpl_LDouble_Arctan_Asymptotic.                                    */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the asymptotic expansion. The expansion is a polynomial  *
 *  of degree 13 in terms of 1/x^{2n+1}. The coefficients are (-1)^n / (2n+1).*/
#define A0 (1.0000000000000000000000000000000000000E+00L)
#define A1 (-3.333333333333333333333333333333333333E-01L)
#define A2 (2.0000000000000000000000000000000000000E-01L)
#define A3 (-1.428571428571428571428571428571428571E-01L)
#define A4 (1.1111111111111111111111111111111111111E-01L)
#define A5 (-9.090909090909090909090909090909090909E-02L)
#define A6 (7.6923076923076923076923076923076923076E-02L)

/*  Asymptotic expansion for atan(x). This works well for large values.       */
TMPL_INLINE_DECL
long double tmpl_LDouble_Arctan_Asymptotic(long double x)
{
    const long double z = 1.0L / x;
    const long double z2 = z*z;

    /*  Use Horner's method to compute the polynomial.                        */
    return tmpl_Pi_By_Two_L -
           z*(A0 + z2*(A1 + z2*(A2 + z2*(A3 + z2*(A4 + z2*(A5 + z2*A6))))));
}
/*  End of tmpl_LDouble_Arctan_Asymptotic.                                    */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6

#endif
/*  End of non-64-bit long double version.                                    */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
