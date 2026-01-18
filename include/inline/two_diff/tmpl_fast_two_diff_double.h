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
 *                          tmpl_fast_two_sum_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the Fast2Sum algorithm for summing with error.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Fast_Two_Sum                                              *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two doubles, returning the sum and the error.    *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
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
 *      Use the standard Fast2Sum algorithm. Letting "sum" denote the real    *
 *      sum of x and y, and "+" denote floating-point addition, we have:      *
 *                                                                            *
 *          sum(x, y) = (x + y) + err                                         *
 *                    = (x + y) + (y - ycomp)                                 *
 *                    = (x + y) + (y - ((x + y) - x))                         *
 *                                                                            *
 *      This assumes |x| >= |y|. Note that if floating-point addition were    *
 *      associative, the error term would be zero and we'd have               *
 *      sum(x, y) = x + y. Since floating-point arithmetic is not associative *
 *      it is often the case that the error is non-zero. We compute the sum   *
 *      and the error by reversing the above equations. We have:              *
 *                                                                            *
 *          sum   = x + y                                                     *
 *          ycomp = sum - x                                                   *
 *          err   = y - ycomp                                                 *
 *                                                                            *
 *      The values "sum" and "err" are returned.                              *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum.                                                    *
 *                                                                            *
 *      2.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *                                                                            *
 *      3.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      4.) There are no checks for NaN or Infinity.                          *
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
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FAST_TWO_SUM_DOUBLE_H
#define TMPL_FAST_TWO_SUM_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Standard Fast2Sum algorithm at double precision.                          */
TMPL_INLINE_DECL
void
tmpl_Double_Fast_Two_Diff(const double x,
                          const double y,
                          double * TMPL_RESTRICT const out,
                          double * TMPL_RESTRICT const err)
{
    /*  The difference, to whatever rounding mode is being used.              */
    TMPL_VOLATILE const double diff = x - y;

    /*  The compensated y term, i.e. the bits lost from summing with x.       */
    TMPL_VOLATILE const double ycomp = x - diff;

    /*  The output is the floating-point sum, the error can be computed by    *
     *  summing together the error terms for x and y.                         */
    *out = sum;
    *err = ycomp - y;
}
/*  End of tmpl_Double_Fast_Two_Sum.                                          */

#endif
/*  End of include guard.                                                     */
