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
 *                             tmpl_two_sum_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the (non-fast) 2Sum algorithm for summing with error.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Two_Sum                                                   *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two doubles, returning the sum and the error.    *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The rounded sum x + y will be stored here.                        *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error term, sum(x, y) - (x + y), is stored here.              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      We use the standard 2Sum algorithm. In most cases it is far more      *
 *      beneficial to use the Fast2Sum algorithm, tmpl_Double_Fast_Two_Sum,   *
 *      since this uses only three floating point operations, but this has    *
 *      the caveat of requiring before-hand knowledge that |x| >= |y| is true.*
 *      The standard 2Sum goes as follows. Let "+" denote floating-point      *
 *      addition, and "sum" denote real addition. Let "xerr" and "yerr"       *
 *      denote the error from the x and y terms, respectively, and "xcomp"    *
 *      and "ycomp" denote the compensation factor from x and y, respectively.*
 *      Using this, we have:                                                  *
 *                                                                            *
 *          sum(x, y) = (x + y) + err                                         *
 *                    = (x + y) + (xerr + yerr)                               *
 *                    = (x + y) + ((x - xcomp) + (y - ycomp))                 *
 *                    = (x + y) + ((x - ((x + y) - y)) + (y - ((x + y) - x))) *
 *                                                                            *
 *      If floating-point addition were associative, this error term would    *
 *      simplify to zero, and we would have sum(x, y) = x + y. Since          *
 *      floating-point addition rounds the result, it is not associative, and *
 *      the error term is often non-zero. We compute err by reversing this    *
 *      set of equations. That is:                                            *
 *                                                                            *
 *          sum   = x + y                                                     *
 *          xcomp = sum - y                                                   *
 *          ycomp = sum - x                                                   *
 *          xerr  = x - xcomp                                                 *
 *          yerr  = y - ycomp                                                 *
 *          err   = xerr + yerr                                               *
 *                                                                            *
 *      The values "sum" and "err" are returned.                              *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor 2Sum.                                                        *
 *                                                                            *
 *      2.) Compilers supporting the C23 standard and providing support for   *
 *          the gnu::optimize attribute may not need to use the volatile      *
 *          keyword. The gnu::optimize("no-associative-math") attribute is    *
 *          applied to ensure correct behavior.                               *
 *                                                                            *
 *      3.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *                                                                            *
 *      4.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      5.) There are no checks for NaN or Infinity.                          *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/2Sum                                *
 *                                                                            *
 *          Wikipedia article on the 2Sum algorithm, which is the more        *
 *          accurate version of Fast2Sum. Unlike Fast2Sum, 2Sum does not      *
 *          assume |x| >= |y|, but 2Sum requires 5 additions, and Fast2Sum    *
 *          only needs 3.                                                     *
 *                                                                            *
 *      2.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *                                                                            *
 *          Wikipedia article for Kahan summation. The standard Kahan         *
 *          algorithm uses Fast2Sum to improve the accuracy when summing      *
 *          multiple floating-point numbers.                                  *
 *                                                                            *
 *      3.) Dekker, T.J. (June 1971).                                         *
 *          A floating-point technique for extending the available precision. *
 *          Numerische Mathematik. Volume 18, Number 3: Pages 224-242.        *
 *                                                                            *
 *          Classic paper on double-double arithmetic. The original Fast2Sum  *
 *          algorithm is described here.                                      *
 *                                                                            *
 *      4.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          Library for Double-Double and Quad-Double Arithmetic.             *
 *                                                                            *
 *          Paper detailing the implementation of double-double and           *
 *          quad-double arithmetic. The 2Sum and Fast2Sum algorithms are      *
 *          described here, as is the 2Prod algorithm.                        *
 *                                                                            *
 *      5.) Schewchuk, J. (October 1997).                                     *
 *          Adaptive Precision Floating-Point Arithmetic and                  *
 *          Fast Robust Geometric Predicates.                                 *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 *                                                                            *
 *          Detailed analysis of 2Sum, Fast2Sum, and 2Prod, allowing for      *
 *          arbitrarily sized floating-point types. This paper is useful for  *
 *          extending 2Prod to the various long double types such as 80-bit   *
 *          extended and 128-bit quadruple. Proofs are included along with    *
 *          the algorithms.                                                   *
 *                                                                            *
 *      6.) Moller, Ole (March 1965).                                         *
 *          Quasi double-precision in floating point addition.                *
 *          BIT Numerical Mathematics. Volume 5: Pages 37-50.                 *
 *                                                                            *
 *          The original paper describing 2Sum and Fast2Sum.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SUM_DOUBLE_H
#define TMPL_TWO_SUM_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Standard 2Sum algorithm at double precision.                              */
TMPL_NO_ASSOCIATIVE_MATH
TMPL_INLINE_DECL
void
tmpl_Double_Two_Sum(const double x,
                    const double y,
                    double * TMPL_RESTRICT const out,
                    double * TMPL_RESTRICT const err)
{
    /*  The sum, to whatever rounding mode is being used (likely to-nearest). */
    TMPL_VOLATILE const double sum = x + y;

    /*  Compensated values for x and y.                                       */
    TMPL_VOLATILE const double xc = sum - y;
    TMPL_VOLATILE const double yc = sum - xc;

    /*  The error terms for x and y from the compensated values.              */
    TMPL_VOLATILE const double xerr = x - xc;
    TMPL_VOLATILE const double yerr = y - yc;
    TMPL_VOLATILE const double err_sum = xerr + yerr;

    /*  The output is the floating point sum, the error can be computed by    *
     *  summing together the error terms for x and y.                         */
    *out = sum;
    *err = err_sum;
}
/*  End of tmpl_Double_Two_Sum.                                               */

#endif
/*  End of include guard.                                                     */
