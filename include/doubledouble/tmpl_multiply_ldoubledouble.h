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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MULTIPLY_LDOUBLEDOUBLE_H
#define TMPL_MULTIPLY_LDOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

/*  2Prod and Fast2Sum are short enough that they can be inlined.             */
#if TMPL_USE_INLINE == 1

#include <libtmpl/include/two_prod/tmpl_two_prod_ldouble.h>
#include <libtmpl/include/two_sum/tmpl_fast_two_sum_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about these functions.          */
extern void
tmpl_LDouble_Two_Prod(long double x,
                      long double y,
                      long double * TMPL_RESTRICT const out,
                      long double * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Fast_Two_Sum(long double x,
                          long double y,
                          long double * TMPL_RESTRICT const out,
                          long double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

TMPL_INLINE_DECL
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Multiply(const tmpl_LongDoubleDouble * const x,
                            const tmpl_LongDoubleDouble * const y)
{
    /*  Declare necessary variables. C89 requires declerations at the top.    */
    tmpl_LongDoubleDouble out;

    /*  Given x = xhi + xlo and y = yhi + ylo, we have:                       *
     *      x * y = (xhi + xlo) * (yhi + ylo)                                 *
     *            = xhi*yhi + xhi*ylo + xlo*yhi + xlo*ylo                     *
     *           ~= xhi*yhi + xhi*ylo + xlo*yhi                               *
     *  The xlo*ylo term will not effect the result and can be discarded. We  *
     *  compute xhi*yhi exactly using 2Prod, and then add the middle part of  *
     *  the sum, xhi*ylo + xlo*yhi, to the error term in 2Prod. A call to     *
     *  Fast2Sum will then complete the computation. Declare the required     *
     *  variables for this algorithm.                                         */
    long double prod_hi, err_hi, compensation;
    long double prod_hi_lo, prod_lo_hi, prod_mid;

    /*  xhi * yhi, exact, stored in two doubles.                              */
    tmpl_LDouble_Two_Prod(x->dat[0], y->dat[0], &prod_hi, &err_hi);

    /*  xhi * ylo + xlo * yhi. These values won't effect the higher order     *
     *  bits very much, but they will effect the low word of the output.      */
    prod_hi_lo = x->dat[0] * y->dat[1];
    prod_lo_hi = x->dat[1] * y->dat[0];

    /*  The middle product, xhi*ylo + xlo*yhi, can be on the same order of    *
     *  magnitude as the low word in the 2Prod performed above. The new       *
     *  compensation term is then the sum of these values.                    */
    prod_mid = prod_hi_lo + prod_lo_hi;
    compensation = err_hi + prod_mid;

    /*  prod_hi is large enough that we can do Fast2Sum with compensation,    *
     *  instead of the full 2Sum. This saves us a few arithmetic operations   *
     *  without losing precision.                                             */
    tmpl_LDouble_Fast_Two_Sum(prod_hi, compensation, &out.dat[0], &out.dat[1]);

    /*  The output is accurate to 7*eps^2, where eps is the epsilon value of  *
     *  long double. For 80-bit extended, this is about 8x10^-38.             */
    return out;
}
/*  End of tmpl_LDoubleDouble_Multiply.                                       */

#endif
/*  End of include guard.                                                     */
