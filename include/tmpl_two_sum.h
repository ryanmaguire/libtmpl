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
 *          The error, sum(x, y) - (x + y), is stored here.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Fast2Sum assumes |x| >= |y|.                                      *
 *                                                                            *
 *      2.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum.                                                    *
 *                                                                            *
 *      3.) Compilers supporting the C23 standard and providing support for   *
 *          the gnu::optimize attribute may not need to use the volatile      *
 *          keyword. The gnu::optimize("no-associative-math") attribute is    *
 *          applied to ensure correct behavior.                               *
 *                                                                            *
 *      4.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *                                                                            *
 *      5.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      6.) There are no checks for NaN or Infinity.                          *
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
 *          The error, sum(x, y) - (x + y), is stored here.                   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
#include <libtmpl/include/two_sum/tmpl_two_sum_float.h>
#include <libtmpl/include/two_sum/tmpl_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_two_sum_ldouble.h>

#endif
/*  End of include guard.                                                     */
