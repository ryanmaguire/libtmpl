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
 *                    tmpl_arctan_maclaurin_ldouble_inline                    *
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
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_MACLAURIN_LDOUBLE_INLINE_H
#define TMPL_MATH_ARCTAN_MACLAURIN_LDOUBLE_INLINE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at double precision.                */
#define A0 (1.00000000000000000000000000000E+00L)
#define A1 (-3.33333333333333333333333333333E-01L)
#define A2 (2.00000000000000000000000000000E-01L)
#define A3 (-1.42857142857142857142857142857E-01L)
#define A4 (1.11111111111111111111111111111E-01L)
#define A5 (-9.09090909090909090909090909090E-02L)
#define A6 (7.69230769230769230769230769231E-02L)
#define A7 (-6.66666666666666666666666666667E-02L)
#define A8 (5.88235294117647058823529411765E-02L)

/*  Maclaurin series for arctan, double precision, to 9 terms.                */
TMPL_INLINE_DECL
long double tmpl_LDouble_Arctan_Maclaurin(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x2 = x*x;

    /*  Use Horner's method to compute the polynomial.                        */
    return x*(A0+x2*(A1+x2*(A2+x2*(A3+x2*(A4+x2*(A5+x2*(A6+x2*(A7+x2*A8))))))));
}
/*  End of tmpl_LDouble_Arctan_Maclaurin.                                     */

/*  Undefine the coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef A6
#undef A7
#undef A8

#else
/*  Else for 64-bit long double version.                                      */

/******************************************************************************
 *   80-Bit Extended / 128-bit Quadruple / 128-bit Double-Double / Portable   *
 ******************************************************************************/

/*  Coefficients for the Maclaurin series at long double precision.           */
#define A00 (1.00000000000000000000000000000000000E+00L)
#define A01 (-3.33333333333333333333333333333333333E-01L)
#define A02 (2.00000000000000000000000000000000000E-01L)
#define A03 (-1.42857142857142857142857142857142857E-01L)
#define A04 (1.11111111111111111111111111111111111E-01L)
#define A05 (-9.09090909090909090909090909090909091E-02L)
#define A06 (7.69230769230769230769230769230769231E-02L)
#define A07 (-6.66666666666666666666666666666666667E-02L)
#define A08 (5.88235294117647058823529411764705882E-02L)
#define A09 (-5.26315789473684210526315789473684211E-02L)
#define A10 (4.7619047619047619047619047619047619E-02L)
#define A11 (-4.34782608695652173913043478260869565E-02L)

/*  Taylor series centered at x0 = 0 for atan(x).                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Arctan_Maclaurin(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x2 = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    return x*(
        A00 + x2*(
            A01 + x2*(
                A02 + x2*(
                    A03 + x2*(
                        A04 + x2*(
                            A05 + x2*(
                                A06 + x2*(
                                    A07 + x2*(
                                        A08 + x2*(
                                            A09 + x2*(
                                                A10 + x2*A11
                                            )
                                        )
                                    )
                                )
                            )
                        )
                    )
                )
            )
        )
    );
}
/*  End of tmpl_LDouble_Arctan_Maclaurin.                                     */

/*  Undefine the coefficients in case someone wants to #include this file.    */
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
/*  End difference between 64-bit long double and higher precisions.          */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
