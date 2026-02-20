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
 *                          tmpl_kbmd20_remez_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) for small x.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_KBMD20_Remez                                             *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      Remez polynomial for very small arguments.                            *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (long double):                                               *
 *          The modified Kaiser-Bessel window (alpha = 2) of x.               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree N Remez polynomial for function f     *
 *      given by:                                                             *
 *                                                                            *
 *                 KBMD20(x) - 1                                              *
 *          f(x) = -------------                                              *
 *                        2                                                   *
 *                       x                                                    *
 *                                                                            *
 *      where KBMD20 is the modified Kaiser-Bessel window (alpha = 2), have   *
 *      been pre-computed on the interval [-1/32, 1/32]. The value of N       *
 *      depends on how long double is implemented:                            *
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
 *  Date:       February 19, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_REMEZ_LDOUBLE_H
#define TMPL_KBMD20_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degree of the polynomial depends on how long double is implemented.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  64-bit long double, same precision as 64-bit double.                      */
#define A00 (-1.1651421693198271652361200948852587214471165723367E+01L)
#define A01 (+5.6570937599305994954980353558804600910078981455050E+01L)
#define A02 (-1.5579729370003565203900166590087485807647921153486E+02L)
#define A03 (+2.7705116556164322602637283132126030991626751129013E+02L)
#define A04 (-3.4279667454271110061935060435601473032453227839005E+02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z * (A01 + z * (A02 + z * (A03 + z * A04)))

/*  128-bit quadruple and 128-bit double-double conveniently need the same    *
 *  number of terms to achieve 1 ULP (~10^-34 and ~10^-32, respectively).     */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT || \
      TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                     128-bit Double-Double / Quadruple                      *
 ******************************************************************************/

/*  Degree 16 Remez polynomial, peak theoretical error ~1.17 x 10^-34.        */
#define A00 (-1.1651421693198272194466941650031585850783419616914E+01L)
#define A01 (+5.6570937599333754558903614460814090927870680000856E+01L)
#define A02 (-1.5579729392747717175244123510767765742276114844825E+02L)
#define A03 (+2.7705181782308301742029787436410114963239248172924E+02L)
#define A04 (-3.4356030922568719458905785024062839154372550480163E+02L)
#define A05 (+3.1314128418975842334352403586376990665111337188969E+02L)
#define A06 (-2.1810772642400529851429328690285671681786070595646E+02L)
#define A07 (+1.1964582953004012333651371396068840273839682994827E+02L)
#define A08 (-5.2871126651955617019356266470828838771372870612598E+01L)

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
#define A00 (-1.1651421693198272194374742575777684476504879741533E+01L)
#define A01 (+5.6570937599333747760640432723908609990960150897230E+01L)
#define A02 (-1.5579729392739594728087800428034274124706895510767E+02L)
#define A03 (+2.7705181746816399752683740519164265610151315652072E+02L)
#define A04 (-3.4355960818057998049534905593038202785390864979640E+02L)
#define A05 (+3.1250295245067092990271257367781810395653169900680E+02L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the modified Kaiser-Bessel window using a Remez polynomial.      */
TMPL_STATIC_INLINE
long double tmpl_LDouble_KBMD20_Remez(const long double x)
{
    /*  The Kaiser-Bessel function is even, the polynomial is in terms of x^2.*/
    const long double x2 = x * x;

    /*  Evaluate the polynomial using Horner's method.                        */
    const long double poly = TMPL_POLY_EVAL(x2);

    /*  The polynomial is for (KBMD20(x) - 1) / x^2. Compute KBMD20 from this.*/
    return 1.0L + x2 * poly;
}
/*  End of tmpl_LDouble_KBMD20_Remez.                                         */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
