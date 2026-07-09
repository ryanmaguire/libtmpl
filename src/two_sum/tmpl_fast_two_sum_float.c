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
 *                          tmpl_fast_two_sum_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the Fast2Sum algorithm for summing with error.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Fast_Two_Sum                                               *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two floats, computing the sum and error.         *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *      y (const float):                                                      *
 *          Another real number.                                              *
 *      out (float * TMPL_RESTRICT const):                                    *
 *          The rounded sum fl(x + y) will be stored here.                    *
 *      err (float * TMPL_RESTRICT const):                                    *
 *          The error term (exact sum minus rounded sum) is stored here.      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the standard Fast2Sum algorithm. Let "+" denote real addition     *
 *      with infinite precision, and let fl denote the floating-point round   *
 *      function. We have:                                                    *
 *                                                                            *
 *          x + y = fl(x + y) + err                                           *
 *                = fl(x + y) + fl(y - ycomp)                                 *
 *                = fl(x + y) + fl(y - fl(fl(x + y) - x))                     *
 *                                                                            *
 *      This assumes |x| >= |y|. Note that if floating-point arithmetic were  *
 *      exact (that is, if fl(x) = x), then the error term would be zero and  *
 *      we'd have x + y = fl(x + y). Since floating-point arithmetic is not   *
 *      exact, it is often the case that the error is non-zero. We compute    *
 *      the sum and the error by reversing the above equations. We have:      *
 *                                                                            *
 *          sum   = fl(x + y)                                                 *
 *          ycomp = fl(sum - x)                                               *
 *          err   = fl(y - ycomp)                                             *
 *                                                                            *
 *      The values "sum" and "err" are stored using the input pointers.       *
 *  Notes:                                                                    *
 *      1.) Fast2Sum assumes |x| >= |y|.                                      *
 *                                                                            *
 *      2.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum.                                                    *
 *                                                                            *
 *      3.) Compilers supporting the C23 standard and implementing the        *
 *          gnu::optimize attribute may not need to use the volatile keyword. *
 *          The gnu::optimize("no-associative-math") attribute is applied to  *
 *          ensure correct behavior.                                          *
 *                                                                            *
 *      4.) On compilers supporting the restrict keyword, out and err are     *
 *          declared as restrict pointers. This requires that out and err     *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *                                                                            *
 *      5.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      6.) There are no checks for NaN or infinity.                          *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/2Sum                                *
 *                                                                            *
 *          Wikipedia article on the 2Sum algorithm, which is the more        *
 *          general version of Fast2Sum. Unlike Fast2Sum, 2Sum does not       *
 *          assume |x| >= |y|, but 2Sum requires 6 operations, and Fast2Sum   *
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
 *          Classic paper on double-double arithmetic. Dekker's analysis of   *
 *          the Fast2Sum algorithm is provided here.                          *
 *                                                                            *
 *      4.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          Library for Double-Double and Quad-Double Arithmetic.             *
 *                                                                            *
 *          Paper detailing the implementation of double-double and           *
 *          quad-double arithmetic. The 2Sum and Fast2Sum algorithms are      *
 *          described here, as is the 2Prod algorithm.                        *
 *                                                                            *
 *      5.) Shewchuk, J. (October 1997).                                      *
 *          Adaptive Precision Floating-Point Arithmetic and                  *
 *          Fast Robust Geometric Predicates.                                 *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 *                                                                            *
 *          Detailed analysis of 2Sum, Fast2Sum, and 2Prod, allowing for      *
 *          arbitrarily sized floating-point types. This paper is useful for  *
 *          extending these algorithms to the various long double types such  *
 *          as 80-bit extended and 128-bit quadruple. Proofs are included     *
 *          along with the algorithms.                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing TMPL_INLINE_DECL and other macros.          *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/29: Ryan Maguire                                                  *
 *      Added C23 attributes and fixed algorithm.                             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_two_sum.h>

/*  Standard Fast2Sum algorithm at single precision.                          */
TMPL_ALWAYS_INLINE
void
tmpl_Float_Fast_Two_Sum(const float x,
                        const float y,
                        float * TMPL_RESTRICT const out,
                        float * TMPL_RESTRICT const err)
{
    /*  Variables for the sum, compensation, and difference, respectively.    */
    float sum, ycomp, diff;

    /*  The rounded floating-point sum.                                       */
    sum = x + y;

    /*  Protect the sum variable for being collapsed by optimizations.        */
    TMPL_FLOAT_BARRIER(sum);

    /*  The compensated y term, the bits that remain after summing with x.    */
    ycomp = sum - x;

    /*  The compensation term also needs to be protected from optimizations.  */
    TMPL_FLOAT_BARRIER(ycomp);

    /*  The error can be computed by removing the compensation term from the  *
     *  smaller value. Note, this assumes |x| >= |y|.                         */
    diff = y - ycomp;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_FLOAT_BARRIER(diff);

    /*  Store the results using the provided pointers to conclude.            */
    *out = sum;
    *err = diff;
}
/*  End of tmpl_Float_Fast_Two_Sum.                                           */
