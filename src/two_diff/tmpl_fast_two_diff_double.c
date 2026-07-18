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
 *                          tmpl_fast_two_diff_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the Fast2Diff algorithm for subtracting with error.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Fast_Two_Diff                                             *
 *  Purpose:                                                                  *
 *      Evaluates the difference of two doubles with compensation error.      *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The rounded difference fl(x - y) will be stored here.             *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error term (exact difference minus out) is stored here.       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the standard Fast2Diff algorithm. Let "-" denote real subtraction *
 *      with infinite precision, and let fl denote the floating-point round   *
 *      function. We have:                                                    *
 *                                                                            *
 *          x + y = fl(x - y) + err                                           *
 *                = fl(x - y) + fl(ycomp - y)                                 *
 *                = fl(x - y) + fl(fl(x - fl(x - y)) - y)                     *
 *                                                                            *
 *      This assumes |x| >= |y|. Note that if floating-point arithmetic were  *
 *      exact (that is, if fl(x) = x), then the error term would be zero and  *
 *      we'd have x - y = fl(x - y). Since floating-point arithmetic is not   *
 *      exact, it is often the case that the error is non-zero. We compute    *
 *      the sum and the error by reversing the above equations. We have:      *
 *                                                                            *
 *          diff  = fl(x - y)                                                 *
 *          ycomp = fl(x - diff)                                              *
 *          err   = fl(ycomp - y)                                             *
 *                                                                            *
 *      The values "diff" and "err" are stored using the input pointers.      *
 *  Notes:                                                                    *
 *      1.) Fast2Diff assumes |x| >= |y|.                                     *
 *                                                                            *
 *      2.) Depending on compiler, floating-point barriers may produce a      *
 *          no-op, or they may use volatile.                                  *
 *                                                                            *
 *      3.) On compilers supporting the restrict keyword, out and err are     *
 *          declared as restrict pointers. This requires that out and err     *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *                                                                            *
 *      4.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      5.) There are no checks for NaN or infinity.                          *
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
 *          Header file providing the TMPL_ALWAYS_INLINE macro.               *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_two_diff.h:                                                      *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 17, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_two_diff.h>

/*  Standard Fast2Diff algorithm at double precision.                         */
TMPL_ALWAYS_INLINE
void
tmpl_Double_Fast_Two_Diff(const double x,
                          const double y,
                          double * TMPL_RESTRICT const out,
                          double * TMPL_RESTRICT const err)
{
    /*  Variables for the difference, compensation, and error, respectively.  */
    double diff, ycomp, error;

    /*  The rounded floating-point difference.                                */
    diff = x - y;

    /*  Protect the difference from being collapsed by optimizations.         */
    TMPL_DOUBLE_BARRIER(diff);

    /*  The compensated y term, the bits that remain after subtracting.       */
    ycomp = x - diff;

    /*  The compensation term also needs to be protected from optimizations.  */
    TMPL_DOUBLE_BARRIER(ycomp);

    /*  The error can be computed by removing the compensation term from the  *
     *  smaller value. Note, this assumes |x| >= |y|.                         */
    error = ycomp - y;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_DOUBLE_BARRIER(diff);

    /*  Store the results using the provided pointers to conclude.            */
    *out = diff;
    *err = error;
}
/*  End of tmpl_Double_Fast_Two_Diff.                                         */
