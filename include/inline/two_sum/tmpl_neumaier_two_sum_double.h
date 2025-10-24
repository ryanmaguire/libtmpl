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
 *          poor Fast2Sum.                                                    *
 *      2.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/2Sum                                *
 *      2.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *      3.) Moller, Ole (March 1965).                                         *
 *          "Quasi double-precision in floating point addition."              *
 *          BIT Numerical Mathematics. Volume 5: Pages 37-50.                 *
 *      4.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      5.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
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
#ifndef TMPL_NEUMAIER_ADDTO_DOUBLE_H
#define TMPL_NEUMAIER_ADDTO_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1
#include <libtmpl/include/inline/math/tmpl_abs_double.h>
#else
extern double tmpl_Double_Abs(double x);
#endif

/*  Standard 2Sum algorithm at double precision.                              */
TMPL_INLINE_DECL
void
tmpl_Double_Neumaier_Two_Sum(double input,
                             double * TMPL_RESTRICT const sum,
                             double * TMPL_RESTRICT const err)
{
    /*  The sum, to whatever rounding mode is being used (likely to-nearest). */
    const double add = input + *sum;

    if (tmpl_Double_Abs(*sum) > tmpl_Double_Abs(input))
    {
        const TMPL_VOLATILE double correction = *sum - add;
        *err += correction + input;
    }

    else
    {
        const TMPL_VOLATILE double correction = input - add;
        *err += correction + *sum;
    }

    *sum = add;
}
/*  End of tmpl_Double_Neumaier_AddTo.                                        */

#endif
/*  End of include guard.                                                     */
