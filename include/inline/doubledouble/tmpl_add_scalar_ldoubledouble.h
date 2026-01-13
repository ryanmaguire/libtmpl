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
 *                       tmpl_add_scalar_ldoubledouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs addition for double-word with single-word real numbers.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDoubleDouble_Add_Scalar                                         *
 *  Purpose:                                                                  *
 *      Evaluates the sum of a long-double-double and a long double.          *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A long double precision real number.                              *
 *      y (const tmpl_LongDoubleDouble * const):                              *
 *          A long-double-double real number.                                 *
 *  Output:                                                                   *
 *      sum (tmpl_LongDoubleDouble):                                          *
 *          The sum of x and y.                                               *
 *  Called Functions:                                                         *
 *      tmpl_two_sum.h:                                                       *
 *          tmpl_LDouble_Two_Sum:                                             *
 *              Performs the 2Sum of two numbers: (sum, error) = 2Sum(x, y).  *
 *          tmpl_LDouble_Fast_Two_Sum:                                        *
 *              Performs Fast2Sum: (sum, error) = Fast2Sum(x, y).             *
 *  Method:                                                                   *
 *      Use 2Sum and Fast2Sum together to sum the double-word with the        *
 *      single-word real number. We have:                                     *
 *                                                                            *
 *              (s_hi, s_low) = 2Sum(x, y_high)                               *
 *                        low = s_low + y_low                                 *
 *          (sum_hi, sum_low) = Fast2Sum(s_hi, low)                           *
 *                                                                            *
 *      This is much shorter than summing two double-words.                   *
 *  References:                                                               *
 *      1.) Joldas, M., Muller, J., Popescu, V. (October 2017).               *
 *          "Tight and rigorous error bounds for basic                        *
 *              building blocks of double-word arithmetic."                   *
 *          ACM Transactions on Mathematical Software, Vol. 44, No. 2.        *
 *      2.) Li, X., Demmel, J., Bailey, D., Henry, G., Hida, Y.,              *
 *              Iskandar, J., Kahan, W., Kapur, A., Martin, M.,               *
 *              Tung, T., Yoo, D. (2002).                                     *
 *          "Design, implementation and testing of extended                   *
 *              and mixed precision BLAS."                                    *
 *          ACM Trans. Math. Software Vol. 28, No. 2: Pages 152-205           *
 *      3.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      4.) Dekker, T.J. (June 1971).                                         *
 *          "A floating-point technique for                                   *
 *              extending the available precision."                           *
 *          Numerische Mathematik. Vol. 18, No. 3: Pages 224-242.             *
 *      5.) Shewchuk, J. (October 1997).                                      *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol. 18, No. 3: Pages 305-363   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_doubledouble_ldouble.h:                                          *
 *          Header providing the tmpl_LongDoubleDouble typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 12, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ADD_SCALAR_LDOUBLEDOUBLE_H
#define TMPL_ADD_SCALAR_LDOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_LongDoubleDouble typedef provided here.                              */
#include <libtmpl/include/types/tmpl_doubledouble_ldouble.h>

/*  2Sum and Fast2Sum are small enough that they can be inlined.              */
#if TMPL_USE_INLINE == 1

/*  Both functions are provided in the include/inline/two_sum/ directory.     */
#include <libtmpl/include/inline/two_sum/tmpl_two_sum_ldouble.h>
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about these functions.          */
extern void
tmpl_LDouble_Two_Sum(const long double x,
                     const long double y,
                     long double * TMPL_RESTRICT const out,
                     long double * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Fast_Two_Sum(const long double x,
                          const long double y,
                          long double * TMPL_RESTRICT const out,
                          long double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Performs addition for a double-double with a double.                      */
TMPL_INLINE_DECL
tmpl_DoubleDouble
tmpl_LDoubleDouble_Add_Scalar(const long double x,
                              const tmpl_LongDoubleDouble * const y)
{
    /*  Variable for the output, the sum of x and y.                          */
    tmpl_LongDoubleDouble sum;

    /*  Error term for the sum of the low parts of y and the 2Sum of x and y. */
    long double low_sum;

    /*  The rough guess is the sum of the high part of y with x.              */
    tmpl_LDouble_Two_Sum(x, y.dat[0], &sum.dat[0], &sum.dat[1]);

    /*  Recover the bits from the low part of y, add these to the low part of *
     *  the current sum. Note, |low_sum| < |sum_high|.                        */
    low_sum = y.dat[1] + sum.dat[1];

    /*  Since |low_sum| < |sum_high|, we can do Fast2Sum to compute the sum   *
     *  of these terms. The Fast2Sum of these values produces the final       *
     *  double-double word.                                                   */
    tmpl_LDouble_Fast_Two_Sum(sum.dat[0], low_sum, &sum.dat[0], &sum.dat[1]);

    return sum;
}
/*  End of tmpl_LDoubleDouble_Add_Scalar.                                     */

#endif
/*  End of include guard.                                                     */
