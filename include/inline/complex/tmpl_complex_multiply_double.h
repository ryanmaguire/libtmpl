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
 *                        tmpl_complex_multiply_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex multiplication.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Multiply                                                 *
 *  Purpose:                                                                  *
 *      Multiplies two complex numbers:                                       *
 *                                                                            *
 *          z * w = (a + ib) * (c + id)                                       *
 *                = (ac + ibc + iad + i^2bd                                   *
 *                = (ac - bd) + i(bc + ad)                                    *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexDouble):                                               *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      prod (tmpl_ComplexDouble):                                            *
 *          The product of z and w.                                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the product formula, which is given by the distributive law and   *
 *      the property that i^2 = -1.                                           *
 *  Notes:                                                                    *
 *      1.) No checks for NaN or infinity are made.                           *
 *      2.) A lot of the complex number code was originally written for       *
 *          rss_ringoccs, but has since migrated to libtmpl.                  *
 *          librssringoccs is also released under the GPLv3.                  *
 *      3.) This function used to implement the Karastuba-Gauss algorithm:    *
 *                                                                            *
 *              z = a + ib                                                    *
 *              w = c + id                                                    *
 *                                                                            *
 *              f = c * (a + b)                                               *
 *              g = a * (d - c)                                               *
 *              h = b * (c + d)                                               *
 *                                                                            *
 *              z * w = (f - h) + i(f + g)                                    *
 *                                                                            *
 *          This uses 3 multiplications, whereas the naive method uses 4.     *
 *          On every processor tested, the naive method is faster. This makes *
 *          sense since multiplication isn't too much slower than addition,   *
 *          and hence the extra sums needed result in a slower computation.   *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/complex_number                      *
 *      2.) Ahfors, L. (1979)                                                 *
 *          "Complex Analysis, Third Edition"                                 *
 *          McGraw-Hill, International Series in Pure and Applied Mathematics *
 *          Chapter 1 "The Algebra of Complex Numbers"                        *
 *          Section 1 "Arithmetic Operations"                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains the TMPL_INLINE_DECL macro.                              *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 18, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/02/18: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 *  2024/12/16: Ryan Maguire                                                  *
 *      Added references. Removed Karatsuba-Gauss method.                     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_MULTIPLY_DOUBLE_H
#define TMPL_COMPLEX_MULTIPLY_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  In C99, since _Complex is a built-in data type, given double _Complex z1  *
 *  and double _Complex z2, you can just do z1 * z2. Structs cannot be        *
 *  multiplied so we need a function for computing this.                      */

/*  Double precision complex multiplication.                                  */
TMPL_INLINE_DECL
tmpl_ComplexDouble
tmpl_CDouble_Multiply(tmpl_ComplexDouble z0, tmpl_ComplexDouble z1)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble prod;

    /*  The product uses the distributive law in combination with the fact    *
     *  that i^2 = -1. This gives us the following formulas:                  */
    prod.dat[0] = z0.dat[0]*z1.dat[0] - z0.dat[1]*z1.dat[1];
    prod.dat[1] = z0.dat[0]*z1.dat[1] + z0.dat[1]*z1.dat[0];
    return prod;
}
/*  End of tmpl_CDouble_Multiply.                                             */


/*  The following implements the Kahan determinant method described in:       *
 *      More accurate complex multiplication for embedded processors.         *
 *      Claude-Pierre Jeannerod, Christophe Monat, Laurent Thevenoux          *
 *      12th IEEE International Symposium on Industrial Embedded Systems      *
 *      (SIES 2017), Jun 2017, Toulouse, France.                              *
 *  see algorithm D. Without a hardware FMA, this is about 4x slower. With a  *
 *  hardware FMA it runs at roughly the same speed, only slightly slower. But *
 *  it handles extreme cases, such as the examples outlined in the paper.     */
#if 0
extern double fma(double a, double b, double c);

TMPL_INLINE_DECL
tmpl_ComplexDouble
tmpl_CDouble_Multiply(tmpl_ComplexDouble z, tmpl_ComplexDouble w)
{
    tmpl_ComplexDouble prod;

    double p1 = z.dat[0] * w.dat[0];
    double r1 = fma(-z.dat[1], w.dat[1], p1);
    double r2 = fma(z.dat[0], w.dat[0], -p1);

    double p2 = z.dat[0] * w.dat[1];
    double i1 = fma(z.dat[1], w.dat[0], p2);
    double i2 = fma(z.dat[0], w.dat[1], -p2);
    prod.dat[0] = r1 + r2;
    prod.dat[1] = i1 + i2;
    return prod;
}
#endif

#endif
/*  End of include guard.                                                     */
