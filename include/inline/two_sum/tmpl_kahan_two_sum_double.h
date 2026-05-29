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
 *                          tmpl_kahan_two_sum_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates the Kahan sum from the Kahan summation algorithm.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Kahan_Two_Sum                                             *
 *  Purpose:                                                                  *
 *      Evaluates sum += summand using Kahan summation.                       *
 *  Arguments:                                                                *
 *      summand (const double):                                               *
 *          A real number.                                                    *
 *      sum (double * TMPL_RESTRICT const):                                   *
 *          The current sum. The higher-order component of the sum will be    *
 *          stored here.                                                      *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error term in the summation. The updated error in the sum     *
 *          will be stored here.                                              *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Kahan summation assumes |*sum| > |summand|, and mimics the Fast2Sum   *
 *      algorithm applied to *sum and summand. We have:                       *
 *                                                                            *
 *          hi_part = *sum + (summand - *err)                                 *
 *          lo_part = (hi_part - *sum) - (summand - *err)                     *
 *                                                                            *
 *      This is computed, and then hi_part is stored in "sum" and lo_part is  *
 *      stored in "err."                                                      *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Kahan sum.                                                   *
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
 *      1.) Kahan, W. (January 1965)                                          *
 *          Further Remarks on Reducing Truncation Errors                     *
 *          Communications of the ACM, Vol 8, Number 1: Page 40.              *
 *                                                                            *
 *          The original summation algorithm is described here.               *
 *                                                                            *
 *      2.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *                                                                            *
 *          Wikipedia article for Kahan summation. The standard Kahan         *
 *          algorithm uses Fast2Sum to improve the accuracy when summing      *
 *          multiple floating-point numbers.                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2025                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/29: Ryan Maguire                                                  *
 *      Added C23 attributes and fixed algorithm.                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KAHAN_TWO_SUM_DOUBLE_H
#define TMPL_KAHAN_TWO_SUM_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE and TMPL_RESTRICT. */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Kahan summation algorithm for accurately evaluating sum += summand.       */
TMPL_NO_ASSOCIATIVE_MATH
TMPL_INLINE_DECL
void
tmpl_Double_Kahan_Two_Sum(const double summand,
                          double * TMPL_RESTRICT const sum,
                          double * TMPL_RESTRICT const err)
{
    /*  Correction term, subtract the error term from the input. This         *
     *  produces the higher order bits for the sum.                           */
    const double diff = summand - *err;

    /*  The "sum" variable contains the higher order parts. Add these in.     */
    TMPL_VOLATILE const double add = *sum + diff;

    /*  Compensation term. Mathematically we have:                            *
     *                                                                        *
     *      add - sum = (sum + diff) - sum                                    *
     *                = diff                                                  *
     *                                                                        *
     *  Since floating-point arithmetic is not associative, this cancellation *
     *  does not occur. Instead, this rounds off the lower order parts of     *
     *  diff.                                                                 */
    TMPL_VOLATILE const double comp = add - *sum;

    /*  Store the higher order parts in sum. If floating-point arithmetic was *
     *  exact, then err = 0 and this is simply *sum += summand.               */
    *sum = add;

    /*  Subtracting gives us:                                                 *
     *                                                                        *
     *      comp - diff = ((sum + diff) - sum) - diff                         *
     *                  = ((sum + (summand - err)) - sum) - (summand - err)   *
     *                                                                        *
     *  sum + (summand - err) is the higher order bits of the sum.            *
     *  Subtracting sum from this produces the higher order bits of           *
     *  summand - err. Subtracting summand - err from this retrieves the      *
     *  lower order bits, which is the error in the sum.                      */
    *err = comp - diff;
}
/*  End of tmpl_Double_Kahan_Two_Sum.                                         */

#endif
/*  End of include guard.                                                     */
