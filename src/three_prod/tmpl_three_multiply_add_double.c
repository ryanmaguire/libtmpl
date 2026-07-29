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
 *                       tmpl_three_multiply_add_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the 3FMA algorithm which exactly computes x * y + z.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Three_Multiply_Add                                        *
 *  Purpose:                                                                  *
 *      Performs the fused-multiply-add algorithm, exactly.                   *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *      sum_high (double * TMPL_RESTRICT const):                              *
 *          The high part of x * y + z.                                       *
 *      sum_mid (double * TMPL_RESTRICT const):                               *
 *          The middle part of x * y + z.                                     *
 *      sum_low (double * TMPL_RESTRICT const):                               *
 *          The low part of x * y + z.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/two_prod/                                                         *
 *          tmpl_Double_Two_Prod:                                             *
 *              Computes x * y = prod_high + prod_low, exactly.               *
 *      src/three_sum/                                                        *
 *          tmpl_Double_Three_Sum:                                            *
 *              Performs the 3Sum algorithm, adding x + y + z exactly.        *
 *  Method:                                                                   *
 *      Use 2Prod and 3Sum. Using 2Prod, we may write                         *
 *                                                                            *
 *          x * y = prod_high + prod_low                                      *
 *                                                                            *
 *      If we combine this with 3Sum, we obtain                               *
 *                                                                            *
 *          x * y + z = prod_high + prod_low + z                              *
 *                                                                            *
 *      We pass prod_high, prod_low, and z to 3Sum and return.                *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the restrict keyword, the output          *
 *          variables are declared as restrict pointers. This requires that   *
 *          these variables point to different locations. To properly use the *
 *          various 3Prod functions, this should be true regardless of        *
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
 *  1.) tmpl_two_prod.h:                                                      *
 *          Header file providing the 2Prod algorithm.                        *
 *  2.) tmpl_three_sum.h:                                                     *
 *          3Sum algorithm declared here.                                     *
 *  3.) tmpl_three_prod.h:                                                    *
 *          Function prototype / forward declaration provided here.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 29, 2026                                                 *
 ******************************************************************************/

/*  2Prod function found here, used for exact floating-point multiplication.  */
#include <libtmpl/include/tmpl_two_prod.h>

/*  3Sum declared here, adds three floating-point numbers exactly.            */
#include <libtmpl/include/tmpl_three_sum.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_three_prod.h>

/*  Function for performing fused-multiply-add, x * y + z, exactly.           */
void
tmpl_Double_Three_Multiply_Add(const double x,
                               const double y,
                               const double z,
                               double * TMPL_RESTRICT const sum_high,
                               double * TMPL_RESTRICT const sum_mid,
                               double * TMPL_RESTRICT const sum_low)
{
    /*  Variables for the high and low parts of x * y.                        */
    double prod_high, prod_low;

    /*  We convert this from a multiplication problem to an addition problem  *
     *  using 2Prod. Compute x * y, exactly, splitting it into two parts.     */
    tmpl_Double_Two_Prod(x, y, &prod_high, &prod_low);

    /*  With x * y = prod_high + prod_low, exactly, we can compute x * y + z  *
     *  using 3Sum with prod_high, prod_low, and z.                           */
    tmpl_Double_Three_Sum(prod_high, prod_low, z, sum_high, sum_mid, sum_low);
}
/*  End of tmpl_Double_Three_Multiply_Add.                                    */
