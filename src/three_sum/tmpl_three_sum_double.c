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
 *                            tmpl_three_sum_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the 3Sum algorithm for summing with error.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Three_Sum                                                 *
 *  Purpose:                                                                  *
 *      Evaluates the sum of three doubles, computing the sum and error.      *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *      sum_high (double * TMPL_RESTRICT const):                              *
 *          The high part of x + y + z.                                       *
 *      sum_mid (double * TMPL_RESTRICT const):                               *
 *          The middle part of x + y + z.                                     *
 *      sum_low (double * TMPL_RESTRICT const):                               *
 *          The low part of x + y + z.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/two_sum/                                                          *
 *          tmpl_Double_Two_Sum:                                              *
 *              Performs the 2Sum algorithm, adding x + y exactly.            *
 *  Method:                                                                   *
 *      Repeatedly use 2Sum on the inputs. We have                            *
 *                                                                            *
 *            xy_high + xy_low = x + y                                        *
 *          sum_high + sum_err = xy_high + z                                  *
 *           sum_mid + sum_low = sum_err + xy_low                             *
 *                                                                            *
 *      This requires three 2Sum calls.                                       *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the restrict keyword, the output          *
 *          variables are declared as restrict pointers. This requires that   *
 *          these variables point to different locations. To properly use the *
 *          various 3Sum functions, this should be true regardless of         *
 *          whether or not restrict is supported.                             *
 *                                                                            *
 *      2.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      3.) There are no checks for NaN or infinity.                          *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          Library for Double-Double and Quad-Double Arithmetic.             *
 *                                                                            *
 *          Paper detailing the implementation of double-double and           *
 *          quad-double arithmetic. The various 3Sum algorithms are described *
 *          here, and how they are used to implement quad-double arithmetic.  *
 *                                                                            *
 *      2.) Shewchuk, J. (October 1997).                                      *
 *          Adaptive Precision Floating-Point Arithmetic and                  *
 *          Fast Robust Geometric Predicates.                                 *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 *                                                                            *
 *          Detailed analysis and description of Fast2Sum, 2Sum, and 2Prod.   *
 *          The 3Sum-like functions make regular use of these algorithms.     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing the TMPL_RESTRICT macro.                    *
 *  2.) tmpl_two_sum.h:                                                       *
 *          2Sum algorithm declared here.                                     *
 *  3.) tmpl_three_sum.h:                                                     *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 29, 2026                                                 *
 ******************************************************************************/

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  2Sum declared here, adds two floating-point numbers exactly.              */
#include <libtmpl/include/tmpl_two_sum.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_three_sum.h>

/*  Function for performing 3Sum, adding three floating-point numbers exactly.*/
void
tmpl_Double_Three_Sum(const double x,
                      const double y,
                      const double z,
                      double * TMPL_RESTRICT const sum_high,
                      double * TMPL_RESTRICT const sum_mid,
                      double * TMPL_RESTRICT const sum_low)
{
    /*  3Sum is performed using three 2Sums. Declared variables for the       *
     *  intermediate sums.                                                    */
    double xy_high, xy_low, sum_err;

    /*  Split x + y + z into three floating-point values so that their sums   *
     *  are identical: x + y + z = sum_high + sum_mid + sum_low.              */
    tmpl_Double_Two_Sum(x, y, &xy_high, &xy_low);
    tmpl_Double_Two_Sum(xy_high, z, sum_high, &sum_err);
    tmpl_Double_Two_Sum(xy_low, sum_err, sum_mid, sum_low);
}
/*  End of tmpl_Double_Three_Sum.                                             */
