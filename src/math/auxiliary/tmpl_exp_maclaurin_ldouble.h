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
 *                         tmpl_exp_maclaurin_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp(x).                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Exp_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of exp for small values of x.           *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (long double):                                                  *
 *          The Maclaurin series of exp.                                      *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \        1   n                                      *
 *           exp(x)   =   /       --- x                                       *
 *                        -----    n!                                         *
 *                        n = 0                                               *
 *                                                                            *
 *      64-bit double:                                                        *
 *          Use the first 9 terms (0 <= n <= 8).                              *
 *      80-bit extended / portable:                                           *
 *          Use the first 11 terms (0 <= n <= 10).                            *
 *      128-bit double-double:                                                *
 *          Use the first 16 terms (0 <= n <= 15).                            *
 *      128-bit quadruple:                                                    *
 *          Use the first 17 terms (0 <= n <= 16).                            *
 *  Notes:                                                                    *
 *      Only accurate for values near 0.                                      *
 *      Precisions listed in the comments assume |x| < 1/16.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_MACLAURIN_LDOUBLE_H
#define TMPL_EXP_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the polynomial. They are 1 / n!.                         */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A01 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define A02 (+5.0000000000000000000000000000000000000000000000000E-01L)
#define A03 (+1.6666666666666666666666666666666666666666666666667E-01L)
#define A04 (+4.1666666666666666666666666666666666666666666666667E-02L)
#define A05 (+8.3333333333333333333333333333333333333333333333333E-03L)
#define A06 (+1.3888888888888888888888888888888888888888888888889E-03L)
#define A07 (+1.9841269841269841269841269841269841269841269841270E-04L)
#define A08 (+2.4801587301587301587301587301587301587301587301587E-05L)
#define A09 (+2.7557319223985890652557319223985890652557319223986E-06L)
#define A10 (+2.7557319223985890652557319223985890652557319223986E-07L)
#define A11 (+2.5052108385441718775052108385441718775052108385442E-08L)
#define A12 (+2.0876756987868098979210090321201432312543423654535E-09L)
#define A13 (+1.6059043836821614599392377170154947932725710503488E-10L)
#define A14 (+1.1470745597729724713851697978682105666232650359634E-11L)
#define A15 (+7.6471637318198164759011319857880704441551002397563E-13L)
#define A16 (+4.7794773323873852974382074911175440275969376498477E-14L)

/*  64-bit long double. Uses the same number of terms as 64-bit double.       */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                               64-bit double                                *
 ******************************************************************************/

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  128-bit double-double. More terms to get ~5 x 10^-32 peak error.          */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                           128-bit double-double                            *
 ******************************************************************************/

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
                                                A12 + z*(\
                                                    A13 + z*(\
                                                        A14 + z*A15\
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
        )\
    )\
)

/*  128-bit quadruple. Even more terms to get ~1 x 10^-34 peak error.         */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN || \
      TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN

/******************************************************************************
 *                             128-bit quadruple                              *
 ******************************************************************************/

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
                                                A12 + z*(\
                                                    A13 + z*(\
                                                        A14 + z*(\
                                                            A15 + z*A16\
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
            )\
        )\
    )\
)

/*  Lastly, portable and 80-bit extended. Peak error ~1 x 10^-19.             */
#else

/******************************************************************************
 *                         80-bit extended / portable                         *
 ******************************************************************************/

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00+\
z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*(A09+z*A10)))))))))

#endif
/*  End of double vs. extended / portable vs. double-double vs. quadruple.    */

/*  Maclaurin series of exp for long double.                                  */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Exp_Maclaurin(long double x)
{
    /*  Compute the polynomial via Horner's method and return.                */
    return TMPL_POLY_EVAL(x);
}
/*  End of tmpl_LDouble_Exp_Maclaurin.                                        */

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
#undef A14
#undef A15
#undef A16
#undef TMPL_POLY_EVAL

#endif
/*  End of include guard.                                                     */
