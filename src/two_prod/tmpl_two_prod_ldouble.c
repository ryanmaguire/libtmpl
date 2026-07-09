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
 *                           tmpl_two_prod_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the 2Prod algorithm for multiplying with error.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Two_Prod                                                 *
 *  Purpose:                                                                  *
 *      Evaluates the product of two long doubles, with the rounding error.   *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *      y (ong double):                                                       *
 *          Another real number.                                              *
 *      out (long double * TMPL_RESTRICT const):                              *
 *          The rounded product x * y will be stored here.                    *
 *      err (long double * TMPL_RESTRICT const):                              *
 *          The error term, prod(x, y) - (x * y), is stored here.             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      split/                                                                *
 *          tmpl_LDouble_Even_High_Split:                                     *
 *              Splits an input into two parts, xhi and xlo, so that xhi and  *
 *              xlo have half the number of bits of x. This function returns  *
 *              xhi. xlo is computed via xlo = x - hi.                        *
 *  Method:                                                                   *
 *      This is the standard 2Prod algorithm. Split x and y into two parts:   *
 *                                                                            *
 *          x = xhi + xlo                                                     *
 *          y = yhi + ylo                                                     *
 *                                                                            *
 *      The product is then:                                                  *
 *                                                                            *
 *          x * y = (xhi + xlo) * (yhi + ylo)                                 *
 *                = xhi*yhi + xhi*ylo + xlo*yhi + xlo*ylo                     *
 *                                                                            *
 *      xhi*yhi has the highest order bits of the product. Let prod be the    *
 *      product of x and y, with rounding. The error is then:                 *
 *                                                                            *
 *          err = ((xhi*yhi - prod) + xhi*ylo + yhi*xlo) + xlo*ylo            *
 *                                                                            *
 *      We store prod in "out" and err in "err", and return.                  *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_split.h:                                                         *
 *          Provides a function for splitting an input into two parts.        *
 *  4.) tmpl_two_prod.h:                                                      *
 *          Function prototype / forward declaration found here.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 24, 2024                                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Splitting functions provided here.                                        */
#include <libtmpl/include/tmpl_split.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_two_prod.h>

/*  Standard 2Prod algorithm at long double precision.                        */
TMPL_ALWAYS_INLINE
void
tmpl_LDouble_Two_Prod(long double x,
                      long double y,
                      long double * TMPL_RESTRICT const out,
                      long double * TMPL_RESTRICT const err)
{
    /*  Split the inputs into two parts with half the bits stored in each.    */
    const long double xhi = tmpl_LDouble_Even_High_Split(x);
    const long double yhi = tmpl_LDouble_Even_High_Split(y);

    /*  The low parts can be computed from the difference.                    */
    const long double xlo = x - xhi;
    const long double ylo = y - yhi;

    /*  The cross terms from the product.                                     */
    const long double prod_mid = xhi * ylo + xlo * yhi;
    const long double prod_lo = xlo * ylo;

    /*  Remaining variables need to be guarded using a barrier.               */
    long double prod, err_hi, err_hi_sum, error;

    /*  Perform the two-product. We have:                                     *
     *      x * y = (xhi + xlo) * (yhi + ylo)                                 *
     *            = xhi * yhi + xhi * ylo + xlo * yhi + xlo * ylo.            *
     *  We perform this sum, and keep track of the error term from rounding.  */
    prod = x * y;

    /*  The expression xhi * yhi - prod may be reduced to a single FMA which  *
     *  ruins the 2Prod algorithm. Prevent this with a barrier.               */
    TMPL_LDOUBLE_BARRIER(prod);

    /*  We can now perform the difference safely.                             */
    err_hi = xhi * yhi - prod;

    /*  Prevent aggressive compiler optimizations from reordering the         *
     *  arithmetic using associativity. Apply a barrier.                      */
    TMPL_LDOUBLE_BARRIER(err_hi);

    /*  The sum of the error and the middle part of the product also needs a  *
     *  barrier to prevent aggressive optimizations.                          */
    err_hi_sum = err_hi + prod_mid;
    TMPL_LDOUBLE_BARRIER(err_hi_sum);

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    error = err_hi_sum + prod_lo;
    TMPL_LDOUBLE_BARRIER(error);

    /*  Store the results using the provided pointers to conclude.            */
    *out = prod;
    *err = error;
}
/*  End of tmpl_LDouble_Two_Prod.                                             */
