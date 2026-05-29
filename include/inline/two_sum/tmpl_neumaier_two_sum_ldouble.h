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
 *                       tmpl_neumaier_two_sum_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates the Neumaier sum from the Neumaier summation algorithm.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Neumaier_Two_Sum                                         *
 *  Purpose:                                                                  *
 *      Evaluates sum += summand using Neumaier summation.                    *
 *  Arguments:                                                                *
 *      summand (const long double):                                          *
 *          A real number.                                                    *
 *      sum (long double * TMPL_RESTRICT const):                              *
 *          The current sum. The higher-order component of the sum will be    *
 *          stored here.                                                      *
 *      err (long double * TMPL_RESTRICT const):                              *
 *          The error term in the summation. The updated error in the sum     *
 *          will be stored here.                                              *
 *  Output:                                                                   *
 *      src/math/                                                             *
 *          tmpl_LDouble_Abs:                                                 *
 *              Computes the absolute value of a real number.                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The Neumaier sum is similar to the Kahan sum, but does not assume     *
 *      |sum| > |summand|. If |sum| > |summand|, then the usual Kahan sum is  *
 *      performed, otherwise the roles of sum and summand are swapped. That   *
 *      is, we compute:                                                       *
 *                                                                            *
 *          hi_part = sum + summand                                           *
 *                                                                            *
 *          if |sum| > |summand|                                              *
 *              lo_part = (sum - add) + summand                               *
 *          else                                                              *
 *              lo_part = (summand - add) + sum                               *
 *                                                                            *
 *      This is computed, and we then set *sum = hi_part and *err = lo_part.  *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Neumaier sum.                                                *
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
 *      2.) Neumaier, A. (1974)                                               *
 *          Rundungsfehleranalyse einiger Verfahren zur Summation             *
 *          endlicher Summen                                                  *
 *          Zeitschrift fur Angewandte Mathematik und Mechanik, Vol 54,       *
 *          Number 1: Pages 39-51.                                            *
 *                                                                            *
 *          Original paper describing the algorithm (in German).              *
 *                                                                            *
 *      3.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
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
 *  3.) tmpl_abs_ldouble.h:                                                   *
 *          Header file providing long-double-precision absolute value.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/29: Ryan Maguire                                                  *
 *      Added C23 attributes to prevent aggressive optimizations.             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NEUMAIER_TWO_SUM_LDOUBLE_H
#define TMPL_NEUMAIER_TWO_SUM_LDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Absolute value function found here.                                       */
#include <libtmpl/include/abs/tmpl_abs_ldouble.h>

/*  Neumaier summation algorithm for accurately evaluating sum += summand.    */
TMPL_NO_ASSOCIATIVE_MATH
TMPL_INLINE_DECL
void
tmpl_LDouble_Neumaier_Two_Sum(const long double summand,
                              long double * TMPL_RESTRICT const sum,
                              long double * TMPL_RESTRICT const err)
{
    /*  The sum, to whatever rounding mode is being used (likely to-nearest). */
    TMPL_VOLATILE const long double add = summand + *sum;

    /*  If |sum| > |summand|, then this becomes the usual Kahan sum.          */
    if (tmpl_LDouble_Abs(*sum) > tmpl_LDouble_Abs(summand))
    {
        TMPL_VOLATILE const long double correction = *sum - add;
        *err += correction + summand;
    }

    /*  Otherwise we swap the roles of sum and summand and apply Fast2Sum.    */
    else
    {
        TMPL_VOLATILE const long double correction = summand - add;
        *err += correction + *sum;
    }

    /*  The higher order bits are independent of |sum| and |summand|.         */
    *sum = add;
}
/*  End of tmpl_LDouble_Neumaier_Two_Sum.                                     */

#endif
/*  End of include guard.                                                     */
