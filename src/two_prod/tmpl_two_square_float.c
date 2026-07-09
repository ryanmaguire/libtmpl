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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 25, 2024                                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Splitting functions provided here.                                        */
#include <libtmpl/include/tmpl_split.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_two_prod.h>

/*  Standard 2Prod algorithm for squaring at single precision.                */
TMPL_ALWAYS_INLINE
void
tmpl_Float_Two_Square(const float x,
                      float * TMPL_RESTRICT const out,
                      float * TMPL_RESTRICT const err)
{
    /*  Split the input into two parts with half the bits stored in each.     */
    const float xhi = tmpl_Float_Even_High_Split(x);

    /*  The low part can be computed from the difference.                     */
    const float xlo = x - xhi;

    /*  The cross terms from the product (xhi + xlo) * (xhi + xlo).           */
    const float prod_mid = 2.0F * xlo * xhi;
    const float prod_lo = xlo * xlo;

    /*  The remaining variables need to be guarded using a barrier.           */
    float prod, err_hi, err_hi_sum, error;

    /*  Perform the two-product. We have:                                     *
     *      x * x = (xhi + xlo) * (xhi + xlo)                                 *
     *            = xhi * xhi + 2 * xhi * xlo + xlo * xlo                     *
     *  We perform this sum, and keep track of the error term from rounding.  */
    prod = x * x;

    /*  The expression xhi * xhi - prod may be reduced to a single FMA which  *
     *  ruins the 2Prod algorithm. Prevent this with a barrier.               */
    TMPL_FLOAT_BARRIER(prod);

    /*  We can now perform the difference safely.                             */
    err_hi = xhi * xhi - prod;

    /*  Prevent aggressive compiler optimizations from reordering the         *
     *  arithmetic using associativity. Apply a barrier.                      */
    TMPL_FLOAT_BARRIER(err_hi);

    /*  The sum of the error and the middle part of the product also needs a  *
     *  barrier to prevent aggressive optimizations.                          */
    err_hi_sum = err_hi + prod_mid;
    TMPL_FLOAT_BARRIER(err_hi_sum);

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    error = err_hi_sum + prod_lo;
    TMPL_FLOAT_BARRIER(error);

    /*  Store the results using the provided pointers to conclude.            */
    *out = prod;
    *err = error;
}
/*  End of tmpl_Float_Two_Square.                                             */
