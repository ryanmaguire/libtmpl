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
 *      Provides the 2FMA algorithm which accurately computes x * y + z.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Two_Multiply_Add                                          *
 *  Purpose:                                                                  *
 *      Performs the fused-multiply-add algorithm with a split output.        *
 *  Arguments:                                                                *
 *      x (const double):                                                     *
 *          A real number.                                                    *
 *      y (const double):                                                     *
 *          Another real number.                                              *
 *      z (const double):                                                     *
 *          A third real number.                                              *
 *      sum_high (double * TMPL_RESTRICT const):                              *
 *          The high part of x * y + z.                                       *
 *      sum_low (double * TMPL_RESTRICT const):                               *
 *          The low part of x * y + z.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      src/two_prod/                                                         *
 *          tmpl_Double_Two_Prod:                                             *
 *              Computes x * y = prod_high + prod_low, exactly.               *
 *      src/three_sum/                                                        *
 *          tmpl_Double_Fast_Three_Sum:                                       *
 *              Performs the Fast3Sum algorithm, adding x + y + z accurately. *
 *  Method:                                                                   *
 *      Use 2Prod and Fast3Sum. Using 2Prod, we may write                     *
 *                                                                            *
 *          x * y = prod_high + prod_low                                      *
 *                                                                            *
 *      If we combine this with Fast3Sum, we obtain                           *
 *                                                                            *
 *          x * y + z = prod_high + prod_low + z                              *
 *                                                                            *
 *      We pass prod_high, prod_low, and z to Fast3Sum and return.            *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the restrict keyword, the output          *
 *          variables are declared as restrict pointers. This requires that   *
 *          these variables point to different locations. To properly use the *
 *          various 2Prod functions, this should be true regardless of        *
 *          whether or not restrict is supported.                             *
 *                                                                            *
 *      2.) There are no checks for NULL pointers.                            *
 *                                                                            *
 *      3.) There are no checks for NaN or infinity.                          *
 *                                                                            *
 *      4.) Unlike 3FMA, 2FMA does not exactly compute x * y + z. It splits   *
 *          the result into two floating-point values, meaning it is more     *
 *          accurate than FMA, but less accurate than 3FMA. 3FMA is exact,    *
 *          2FMA is accurate to twice the floating-point precision, and FMA   *
 *          is accurate to floating-point precision.                          *
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
 *          Header file providing the 2Prod algorithm and function prototype. *
 *  2.) tmpl_three_sum.h:                                                     *
 *          Fast3Sum algorithm declared here.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 29, 2026                                                 *
 ******************************************************************************/

/*  2Prod function found here, used for exact floating-point multiplication.  */
#include <libtmpl/include/tmpl_two_prod.h>

/*  Fast3Sum declared here, adds three floating-point numbers accurately.     */
#include <libtmpl/include/tmpl_three_sum.h>

/*  Function for accurately performing fused-multiply-add, x * y + z.         */
void
tmpl_Double_Two_Multiply_Add(const double x,
                             const double y,
                             const double z,
                             double * TMPL_RESTRICT const sum_high,
                             double * TMPL_RESTRICT const sum_low)
{
    /*  Variables for the high and low parts of x * y.                        */
    double prod_high, prod_low;

    /*  We convert this from a multiplication problem to an addition problem  *
     *  using 2Prod. Compute x * y, exactly, splitting it into two parts.     */
    tmpl_Double_Two_Prod(x, y, &prod_high, &prod_low);

    /*  With x * y = prod_high + prod_low, exactly, we can compute x * y + z  *
     *  using Fast3Sum with prod_high, prod_low, and z.                       */
    tmpl_Double_Fast_Three_Sum(prod_high, prod_low, z, sum_high, sum_low);
}
/*  End of tmpl_Double_Two_Multiply_Add.                                      */
