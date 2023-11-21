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
 *                        tmpl_arcsin_maclaurin_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a Maclaurin series for asin(x) at long double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Maclaurin                                         *
 *  Purpose:                                                                  *
 *      Computes a Maclaurin series for asin(x).                              *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          The Maclaurin series of asin(x).                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *      64-bit double:                                                        *
 *          Degree 15 Maclaurin series.                                       *
 *      80-bit extended / portable:                                           *
 *          Degree 19 Maclaurin series.                                       *
 *      128-bit quadruple / 128-bit double-double:                            *
 *          Degree 27 Maclaurin series.                                       *
 *  Notes:                                                                    *
 *      64-bit double:                                                        *
 *          Accurate to double precision for |x| < 0.15. For |x| < 0.5 the    *
 *          approximation is accurate to 7 decimals.                          *
 *      80-bit extended / portable:                                           *
 *          Accurate to extended precision for |x| < 0.15. For |x| < 0.5 the  *
 *          approximation is accurate to 9 decimals.                          *
 *      128-bit quadruple / 128-bit double-double.                            *
 *          Accurate to quadruple precision for |x| < 0.10. For |x| < 0.5 the *
 *          approximation is accurate to 11 decimals.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 1, 2023                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_MACLAURIN_LDOUBLE_H
#define TMPL_ARCSIN_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Only the odd non-constant terms have non-zero coefficients.               */
#define A00 (1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (1.6666666666666666666666666666666666666666666666667E-01L)
#define A02 (7.5000000000000000000000000000000000000000000000000E-02L)
#define A03 (4.4642857142857142857142857142857142857142857142857E-02L)
#define A04 (3.0381944444444444444444444444444444444444444444444E-02L)
#define A05 (2.2372159090909090909090909090909090909090909090909E-02L)
#define A06 (1.7352764423076923076923076923076923076923076923077E-02L)
#define A07 (1.3964843750000000000000000000000000000000000000000E-02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*(A06 + z*A07))))))

/*  128-bit quadruple and double-double, a few more terms.                    */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                 128-bit Quadruple / 128-bit Double-Double                  *
 ******************************************************************************/

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define A02 (+7.5000000000000000000000000000000000000000000000000E-02L)
#define A03 (+4.4642857142857142857142857142857142857142857142857E-02L)
#define A04 (+3.0381944444444444444444444444444444444444444444444E-02L)
#define A05 (+2.2372159090909090909090909090909090909090909090909E-02L)
#define A06 (+1.7352764423076923076923076923076923076923076923077E-02L)
#define A07 (+1.3964843750000000000000000000000000000000000000000E-02L)
#define A08 (+1.1551800896139705882352941176470588235294117647059E-02L)
#define A09 (+9.7616095291940789473684210526315789473684210526316E-03L)
#define A10 (+8.3903358096168154761904761904761904761904761904762E-03L)
#define A11 (+7.3125258735988451086956521739130434782608695652174E-03L)
#define A12 (+6.4472103118896484375000000000000000000000000000000E-03L)
#define A13 (+5.7400376708419234664351851851851851851851851851852E-03L)

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
                                        A10 + z*(\
                                            A11 + z*(\
                                                A12 + z*A13\
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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define A02 (+7.5000000000000000000000000000000000000000000000000E-02L)
#define A03 (+4.4642857142857142857142857142857142857142857142857E-02L)
#define A04 (+3.0381944444444444444444444444444444444444444444444E-02L)
#define A05 (+2.2372159090909090909090909090909090909090909090909E-02L)
#define A06 (+1.7352764423076923076923076923076923076923076923077E-02L)
#define A07 (+1.3964843750000000000000000000000000000000000000000E-02L)
#define A08 (+1.1551800896139705882352941176470588235294117647059E-02L)
#define A09 (+9.7616095291940789473684210526315789473684210526316E-03L)

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
                                A08 + z*A09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

#endif
/*  End of 80-bit extended / portable version.                                */

/*  Computes the Maclaurin polynomial for asin(x).                            */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Arcsin_Maclaurin(long double x)
{
    /*  The non-constant terms are odd, powers are x^{2n+1}.                  */
    const long double x2 = x*x;

    /*  Compute the Maclaurin series of asin(x) / x.                          */
    const long double poly = TMPL_POLY_EVAL(x2);

    /*  Scale by the input to complete the computation.                       */
    return x*poly;
}
/*  End of tmpl_LDouble_Arcsin_Maclaurin.                                     */

/*  Undefine all macros in case someone wants to #include this file.          */
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
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
