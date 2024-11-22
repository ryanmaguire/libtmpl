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
 *                          tmpl_fast_two_sum_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the Fast2Sum algorithm for summing with error.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Fast_Two_Sum                                             *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two long doubles returning the sum and error.    *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *      y (long double):                                                      *
 *          Another real number.                                              *
 *      out (long double * const):                                            *
 *          The rounded sum x + y will be stored here.                        *
 *      err (long double * const):                                            *
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
 *      Depending on compiler and architecture we may need to declare certain *
 *      variables as volatile. Failure to do so results in a poor Fast2Sum.   *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/2Sum                                *
 *      2.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *      3.) Dekker, T.J. (June 1971).                                         *
 *          A floating-point technique for extending the available precision. *
 *          Numerische Mathematik. Volume 18, Number 3: Pages 224–242.        *
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
#ifndef TMPL_FAST_TWO_SUM_LDOUBLE_H
#define TMPL_FAST_TWO_SUM_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Standard Fast2Sum algorithm at long double precision.                     */
TMPL_INLINE_DECL
void
tmpl_LDouble_Fast_Two_Sum(long double x,
                          long double y,
                          long double * const out,
                          long double * const err)
{
    /*  The sum, to whatever rounding mode is being used (likely to-nearest). */
    TMPL_VOLATILE const long double sum = x + y;

    /*  The compensated y term, i.e. the bits lost from summing with x.       */
    TMPL_VOLATILE const long double ycomp = sum - x;

    /*  The output is the floating point sum, the error can be computed by    *
     *  summing together the error terms for x and y.                         */
    *out = sum;
    *err = y - ycomp;
}
/*  End of tmpl_LDouble_Fast_Two_Sum.                                         */

#endif
/*  End of include guard.                                                     */
