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
 *                        tmpl_complex_divide_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex division.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Divide                                                  *
 *  Purpose:                                                                  *
 *      Divides two complex numbers.                                          *
 *                                                                            *
 *          div(z, w) = z / w                                                 *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexLongDouble):                                           *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      quot (tmpl_ComplexLongDouble):                                        *
 *          The quotient z / w.                                               *
 *  Method:                                                                   *
 *      Use the fact that z / w = z * w^-1. The reciprocal formula for w      *
 *      yields:                                                               *
 *                                                                            *
 *           -1           -1    c - i d    c - i d                            *
 *          w   = (c + id)   = --------- = -------                            *
 *                             c^2 + d^2     |w|                              *
 *                                                                            *
 *      The intermediate computation c^2 + d^2 may underflow or overflow. To  *
 *      avoid this we first divide w by the larger of the real and imaginary  *
 *      parts of w. If |c| >= |d|, we have:                                   *
 *                                                                            *
 *           -1    c - i d                                                    *
 *          w   = ---------                                                   *
 *                c^2 + d^2                                                   *
 *                                                                            *
 *                 c - i d  1 / c                                             *
 *              = --------- -----                                             *
 *                c^2 + d^2 1 / c                                             *
 *                                                                            *
 *                1 - i (d / c)                                               *
 *              = -------------                                               *
 *                 c + d^2 / c                                                *
 *                                                                            *
 *      The product with z = a + ib is given by:                              *
 *                                                                            *
 *           z         -1                                                     *
 *          --- = z * w                                                       *
 *           w                                                                *
 *                                                                            *
 *                         1 - i (d / c)                                      *
 *              = (a + ib) -------------                                      *
 *                          c + d^2 / c                                       *
 *                                                                            *
 *                a + b d / c     b - a d / c                                 *
 *              = ----------- + i -----------                                 *
 *                c + d^2 / c     c + d^2 / c                                 *
 *                                                                            *
 *      If |c| < |d|, we do a similar trick and obtain:                       *
 *                                                                            *
 *           -1   a c / d + b     b c / d - a                                 *
 *          w   = ----------- + i -----------                                 *
 *                c^2 / d + d     c^2 / d + d                                 *
 *                                                                            *
 *      We compute these and store them in the output complex number.         *
 *  Notes:                                                                    *
 *      1.) No error check is performed on the inputs. In particular, there   *
 *          are no checks for zero in the denominator, or NaNs or infinities. *
 *      2.) Division is not commutative. tmpl_CLDouble_Divide(z, w) returns   *
 *          z / w, and not w / z. That is, the first entry is divided by the  *
 *          second one.                                                       *
 *      3.) In most realistic applications the precautions taken to prevent   *
 *          underflow and overflow are unnecessary since you would need to    *
 *          work with very small or very large numbers. Use the function      *
 *          tmpl_CLDouble_Quick_Divide instead to get a performance boost if  *
 *          you are not working with such complex numbers.                    *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/complex_number                      *
 *                                                                            *
 *          Fair introduction to complex numbers provided here.               *
 *                                                                            *
 *      2.) Ahfors, L. (1979)                                                 *
 *          "Complex Analysis, Third Edition"                                 *
 *          McGraw-Hill, International Series in Pure and Applied Mathematics *
 *          Chapter 1 "The Algebra of Complex Numbers"                        *
 *          Section 1 "Arithmetic Operations"                                 *
 *                                                                            *
 *          Standard undergraduate textbook on complex analysis.              *
 *                                                                            *
 *      3.) Smith, Robert (1962)                                              *
 *          "Algorithm 116: Complex division"                                 *
 *          Communications of the ACM                                         *
 *          Volume 5, Number 8, Page 435.                                     *
 *                                                                            *
 *          The algorithm implemented is described here.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2025/06/05: Ryan Maguire                                                  *
 *      Inlined functions, moved float and long double versions to their own  *
 *      file, made the algorithm safely handle extreme denominators.          *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_DIVIDE_LDOUBLE_H
#define TMPL_COMPLEX_DIVIDE_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  We need the absolute value function. This is small enough to inline.      */
#if TMPL_USE_INLINE == 1

/*  Inline version found here.                                                */
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, provide the forward declaration for the compiler. */
extern long double tmpl_LDouble_Abs(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  In C99, since _Complex is a built-in data type, given long double         *
 *  _Complex z and long double _Complex w, you can just do z / w. Structs     *
 *  cannot be divided so we need a function for computing this.               */

/*  Long double precision complex division.                                   */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble
tmpl_CLDouble_Divide(tmpl_ComplexLongDouble z, tmpl_ComplexLongDouble w)
{
    /*  Variable for the output, the quotient z / w.                          */
    tmpl_ComplexLongDouble quot;

    /*  We divide w by the component with the larger magnitude.               *
     *  Compute the absolute value of both the real and imaginary parts.      */
    const long double abs_w_real = tmpl_LDouble_Abs(w.dat[0]);
    const long double abs_w_imag = tmpl_LDouble_Abs(w.dat[1]);

    /*  Writing w = c + id, if |c| > |d|, we scale the numerator and          *
     *  denominator of z / w by 1 / c. Check for this.                        */
    if (abs_w_real > abs_w_imag)
    {
        /*  We have:                                                          *
         *                                                                    *
         *       -1    c - i d    1 - i (d / c)                               *
         *      w   = --------- = -------------                               *
         *            c^2 + d^2    c + d^2 / c                                *
         *                                                                    *
         *  Save the expressions d / c and c + d^2 / c.                       */
        const long double ratio = w.dat[1] / w.dat[0];
        const long double denom = w.dat[0] + w.dat[1] * ratio;

        /*  The quotient z / w is given by:                                   *
         *                                                                    *
         *       z             1 - i (d / c)   a + b d / c     b - a d / c    *
         *      --- = (a + ib) ------------- = ----------- + i -----------    *
         *       w              c + d^2 / c    c + d^2 / c     c + d^2 / c    *
         *                                                                    *
         *  That is, the real part is (a + b d / c) / (c + d^2 / c) and the   *
         *  imaginary part is (b - a d / c) / (c + d^2 / c). Compute this.    */
        quot.dat[0] = (z.dat[0] + z.dat[1] * ratio) / denom;
        quot.dat[1] = (z.dat[1] - z.dat[0] * ratio) / denom;
    }

    /*  Here we have |d| >= |c|, or the input contains a NaN.                 */
    else
    {
        /*  Since |d| >= |c|, we scale the numerator and denominator by 1 / d.*
         *  Our expression becomes:                                           *
         *                                                                    *
         *       -1    c - i d     c / d - i                                  *
         *      w   = --------- = -----------                                 *
         *            c^2 + d^2   c^2 / d + d                                 *
         *                                                                    *
         *  Save the expressions c / d and c^2 / d + d.                       */
        const long double ratio = w.dat[0] / w.dat[1];
        const long double denom = w.dat[0] * ratio + w.dat[1];

        /*  The quotient z / w is given by:                                   *
         *                                                                    *
         *       z              c / d - i    a c / d + b     b c / d - a      *
         *      --- = (a + ib) ----------- = ----------- + i -----------      *
         *       w             c^2 / d + d   c^2 / d + d     c^2 / d + d      *
         *                                                                    *
         *  That is, the real part is (a c / d + b) / (c^2 / d + d) and the   *
         *  imaginary part is (b c / d - a) / (c^2 / d + d). Compute this.    */
        quot.dat[0] = (z.dat[0] * ratio + z.dat[1]) / denom;
        quot.dat[1] = (z.dat[1] * ratio - z.dat[0]) / denom;
    }

    return quot;
}
/*  End of tmpl_CLDouble_Divide.                                              */

#endif
/*  End of include guard.                                                     */
