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
 *                         tmpl_left_difference_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs floating-point subtraction without associative reordering.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Even_High_Split                                           *
 *  Purpose:                                                                  *
 *      Computes (a - b) - c while preventing compilers from reordering.      *
 *  Arguments:                                                                *
 *      a (const double):                                                     *
 *          A real number.                                                    *
 *      b (const double):                                                     *
 *          Another real number.                                              *
 *      c (const double):                                                     *
 *          A third real number.                                              *
 *  Output:                                                                   *
 *      left_diff (double):                                                   *
 *          The floating-point difference (a - b) - c, in that order.         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute (a - b) - c using floating-point barriers to guard against    *
 *      aggressive compiler optimizations.                                    *
 *  Notes:                                                                    *
 *      1.) Depending on compiler, floating-point barriers may produce a      *
 *          no-op, or they may use volatile.                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Contains several configuration macros.                            *
 *  2.) tmpl_float_barrier.h:                                                 *
 *          Provides macros to protect against aggressive optimizations.      *
 *  3.) tmpl_split.h:                                                         *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 11, 2026                                                 *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE found here.                                            */
#include <libtmpl/include/tmpl_config.h>

/*  Macros preventing aggressive compiler optimizations given here.           */
#include <libtmpl/include/tmpl_float_barrier.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_split.h>

/*  Function for performing floating-point subtraction without reordering.    */
TMPL_ALWAYS_INLINE
double
tmpl_Double_Left_Difference(const double a, const double b, const double c)
{
    /*  Declare variables for the intermediate steps.                         */
    double a_val, a_minus_b, result;

    /*  A barrier is needed at the start of the function in case this routine *
     *  is inlined. We need to separate lines in the calling function from    *
     *  the difference performed in this function. Make a copy and create a   *
     *  barrier.                                                              */
    a_val = a;
    TMPL_DOUBLE_BARRIER(a_val);

    /*  Compute the first difference, a - b, and guard it with a barrier.     */
    a_minus_b = a_val - b;
    TMPL_DOUBLE_BARRIER(a_minus_b);

    /*  The previous barrier prevents compilers from reordering operations    *
     *  using associativity. We can now compute the result.                   */
    result = a_minus_b - c;

    /*  A final barrier to separate the end of this function from any calling *
     *  functions. This is necessary since this function will likely be       *
     *  inlined when link-time optimization is enabled.                       */
    TMPL_DOUBLE_BARRIER(result);
    return result;
}
/*  End of tmpl_Double_Left_Difference.                                       */
