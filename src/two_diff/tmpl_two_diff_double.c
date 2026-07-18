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
 *                            tmpl_two_diff_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the (non-fast) 2Diff algorithm for subtracting with error.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Two_Diff                                                  *
 *  Purpose:                                                                  *
 *      Evaluates the difference of two doubles with compensation error.      *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The rounded difference x - y will be stored here.                 *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error term is stored here.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      We use the standard 2Diff algorithm. In many cases it is far more     *
 *      beneficial to use the Fast2Diff algorithm, tmpl_Double_Fast_Two_Diff, *
 *      since this uses only three floating-point operations, but this has    *
 *      the caveat of requiring beforehand knowledge that |x| >= |y| is true. *
 *      The standard 2diff goes as follows. Let "-" denote floating-point     *
 *      subtraction, and fl denote the floating-point round operation. Let    *
 *      "xerr" and "yerr" denote the error from the x and y terms,            *
 *      respectively, and "xcomp" and "ycomp" denote the compensation factor  *
 *      from x and y, respectively. Using this, we have:                      *
 *                                                                            *
 *          x - y = fl(x - y) + err                                           *
 *                = fl(x - y) + fl(xerr + yerr)                               *
 *                = fl(x - y) + fl(fl(x - xcomp) + fl(ycomp - y))             *
 *                                                                            *
 *      If floating-point arithmetic were exact, this error term would        *
 *      simplify to zero, and we would have x - y = fl(x - y). Since          *
 *      floating-point subtraction rounds the result, it is not associative,  *
 *      and the error term is often non-zero. We compute err by reversing     *
 *      this set of equations. That is:                                       *
 *                                                                            *
 *          diff  = x - y                                                     *
 *          xcomp = diff + y                                                  *
 *          ycomp = xcomp - diff                                              *
 *          xerr  = x - xcomp                                                 *
 *          yerr  = ycomp - y                                                 *
 *          err   = xerr + yerr                                               *
 *                                                                            *
 *      The values "diff" and "err" are stored using the input pointers.      *
 *  Notes:                                                                    *
 *      1.) 2diff does not require |x| >= |y|, but it requires twice as many  *
 *          arithmetic operations as Fast2Diff.                               *
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
 *          Header file providing the TMPL_ALWAYS_INLINE macro.               *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_two_sum.h:                                                       *
 *          Function prototype / forward declaration provided here.           *
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
#include <libtmpl/include/tmpl_two_diff.h>

/*  Standard 2Diff algorithm at double precision.                             */
TMPL_ALWAYS_INLINE
void
tmpl_Double_Two_Diff(const double x,
                     const double y,
                     double * TMPL_RESTRICT const out,
                     double * TMPL_RESTRICT const err)
{
    /*  Variables for the differences, compensations, and errors.             */
    double diff, err_sum, xc, yc, xerr, yerr;

    /*  The floating-point rounded difference.                                */
    diff = x - y;

    /*  Protect the difference from optimizations using a barrier.            */
    TMPL_DOUBLE_BARRIER(diff);

    /*  Compensated value for x, the bits remaining after subtracting y.      */
    xc = diff + y;
    TMPL_DOUBLE_BARRIER(xc);

    /*  The compensated term for y.                                           */
    yc = xc - diff;
    TMPL_DOUBLE_BARRIER(yc);

    /*  Compute the error term for x from the compensated value.              */
    xerr = x - xc;
    TMPL_DOUBLE_BARRIER(xerr);

    /*  Similarly, compute the error term for y from the compensated value.   */
    yerr = yc - y;
    TMPL_DOUBLE_BARRIER(yerr);

    /*  The sum of the errors, which is the final error term in 2Diff.        */
    err_sum = xerr + yerr;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_DOUBLE_BARRIER(err_sum);

    /*  Store the results using the provided pointers to conclude.            */
    *out = diff;
    *err = err_sum;
}
/*  End of tmpl_Double_Two_Diff.                                              */
