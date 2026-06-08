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
 *                                tmpl_two_sum                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides 2Sum, Fast2Sum, and other 2Sum-like algorithms.              *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture, local variables may       *
 *          require the volatile keyword to prevent aggressive optimizations. *
 *          To enable this requires the USE_VOLATILE option to be set to true *
 *          when compiling libtmpl. Each function uses the TMPL_VOLATILE      *
 *          macro for the necessary variables, which expands to "volatile"    *
 *          if USE_VOLATILE was set at build time, and nothing otherwise.     *
 *                                                                            *
 *      2.) Compilers that support the C23 standard and implement the         *
 *          gnu::optimize attribute may not need to use the volatile keyword. *
 *          The gnu::optimize("no-associative-math") attribute is applied to  *
 *          each function to ensure correct behavior.                         *
 *                                                                            *
 *      3.) On compilers supporting the restrict keyword, the output          *
 *          variables (sum, out, err) are declared as restrict pointers.      *
 *          This requires that these variables point to different locations.  *
 *          To properly use the various 2Sum functions, this should be true   *
 *          regardless of whether or not restrict is supported.               *
 *                                                                            *
 *      4.) None of the 2Sum functions check for NULL pointers.               *
 *                                                                            *
 *      5.) None of the 2Sum functions check for NaN or infinity.             *
 *                                                                            *
 *      6.) Float, double, and long double versions are provided.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing the TMPL_RESTRICT macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SUM_H
#define TMPL_TWO_SUM_H

/*  TMPL_RESTRICT macro provided here.                                        */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fast_Two_Sum                                              *
 *  Purpose:                                                                  *
 *      Performs the standard Fast2Sum algorithm for floating-point addition. *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The floating-point sum x + y is stored here.                      *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error, sum(x, y) - (x + y), is stored here, where "sum"       *
 *          denotes exact addition, and "+" denotes floating-point addition.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Fast2Sum assumes |x| >= |y|.                                      *
 ******************************************************************************/
#include <libtmpl/include/two_sum/tmpl_fast_two_sum_float.h>
#include <libtmpl/include/two_sum/tmpl_fast_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_fast_two_sum_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Kahan_Two_Sum                                             *
 *  Purpose:                                                                  *
 *      Evaluates the Kahan sum from the Kahan summation algorithm.           *
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
 *  Notes:                                                                    *
 *      1.) The Kahan summation algorithm assumes the running sum is greater  *
 *          in magnitude than the summand.                                    *
 ******************************************************************************/
#include <libtmpl/include/two_sum/tmpl_kahan_two_sum_float.h>
#include <libtmpl/include/two_sum/tmpl_kahan_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_kahan_two_sum_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Neumaier_Two_Sum                                          *
 *  Purpose:                                                                  *
 *      Evaluates the Neumaier sum from the Neumaier summation algorithm.     *
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
 *  Notes:                                                                    *
 *      1.) The Neumaier summation algorithm does not assume the sum is       *
 *          greater than the summand, but this comes at the cost of a branch. *
 ******************************************************************************/
#include <libtmpl/include/two_sum/tmpl_neumaier_two_sum_float.h>
#include <libtmpl/include/two_sum/tmpl_neumaier_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_neumaier_two_sum_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Two_Sum                                                   *
 *  Purpose:                                                                  *
 *      Performs the standard 2Sum algorithm for floating-point addition.     *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The floating-point sum x + y is stored here.                      *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error, sum(x, y) - (x + y), is stored here, where "sum"       *
 *          denotes exact addition, and "+" denotes floating-point addition.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) 2Sum does not require |x| >= |y|, but it requires twice as many   *
 *          artithmetic operations as Fast2Sum.                               *
 ******************************************************************************/
#include <libtmpl/include/two_sum/tmpl_two_sum_float.h>
#include <libtmpl/include/two_sum/tmpl_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_two_sum_ldouble.h>

#endif
/*  End of include guard.                                                     */
