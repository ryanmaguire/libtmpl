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
 *                        tmpl_neumaier_two_sum_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates the Neumaier sum from the Neumaier summation algorithm.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Neumaier_Two_Sum                                          *
 *  Purpose:                                                                  *
 *      Evaluates sum += summand using Neumaier summation.                    *
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
 *      src/math/                                                             *
 *          tmpl_Double_Abs:                                                  *
 *              Computes the absolute value of a real number.                 *
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
 *      This is computed, and we then set *sum = hi_part and *err += lo_part. *
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
 *          Header file providing the TMPL_ALWAYS_INLINE macro.               *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_two_sum.h:                                                       *
 *          Function prototype / forward declaration provided here.           *
 *  4.) tmpl_math.h:                                                          *
 *          Absolute value function provided here.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/29: Ryan Maguire                                                  *
 *      Added C23 attributes to prevent aggressive optimizations.             *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_two_sum.h>

/*  Absolute value function declared here.                                    */
#include <libtmpl/include/tmpl_math.h>

/*  Neumaier summation algorithm for accurately evaluating sum += summand.    */
TMPL_ALWAYS_INLINE
void
tmpl_Double_Neumaier_Two_Sum(const double summand,
                             double * TMPL_RESTRICT const sum,
                             double * TMPL_RESTRICT const err)
{
    /*  Variables for the sum and correction term.                            */
    double add, correction;

    /*  The normal floating-point sum with whatever rounding mode is used.    */
    add = summand + *sum;

    /*  Prevent the compiler from using aggressive optimizations.             */
    TMPL_DOUBLE_BARRIER(add);

    /*  If |sum| > |summand|, then this becomes the usual Kahan sum.          */
    if (tmpl_Double_Abs(*sum) > tmpl_Double_Abs(summand))
    {
        correction = *sum - add;

        /*  Compilers may contract the error term is associative arithmetic   *
         *  is allowed. Prevent this.                                         */
        TMPL_DOUBLE_BARRIER(correction);

        /*  Update the error term in the sum.                                 */
        *err += correction + summand;
    }

    /*  Otherwise we swap the roles of sum and summand and apply Fast2Sum.    */
    else
    {
        correction = summand - add;

        /*  Same protection from before.                                      */
        TMPL_DOUBLE_BARRIER(correction);

        /*  Update the error term in the sum.                                 */
        *err += correction + *sum;
    }

    /*  The higher order bits are independent of |sum| and |summand|.         */
    *sum = add;
}
/*  End of tmpl_Double_Neumaier_Two_Sum.                                      */

