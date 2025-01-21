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
 *                         tmpl_quick_add_doubledouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs (non-safe) addition for two double-word real numbers.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_DoubleDouble_Quick_Add                                           *
 *  Purpose:                                                                  *
 *      Evaluates the Dekker-sum of two double-doubles.                       *
 *  Arguments:                                                                *
 *      x (const tmpl_DoubleDouble * const):                                  *
 *          A double-double real number.                                      *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          Another double-double real number.                                *
 *  Output:                                                                   *
 *      x (tmpl_DoubleDouble):                                                *
 *          The double-double sum of x and y.                                 *
 *  Called Functions:                                                         *
 *      tmpl_two_sum.h:                                                       *
 *          tmpl_Double_Fast_Two_Sum:                                         *
 *              Performs Fast2Sum: (sum, error) = Fast2Sum(x, y).             *
 *  Method:                                                                   *
 *      We perform the Dekker algorithm for adding double-doubles:            *
 *                                                                            *
 *          (sum_hi, sum_lo) = 2Sum(xhi, yhi)                                 *
 *                   comp_lo = xlo + ylo                                      *
 *                   comp_hi = sum_lo + comp_lo                               *
 *          (out_hi, out_lo) = Fast2Sum(sum_hi, comp_hi)                      *
 *                                                                            *
 *      This requires half the number of calls to 2Sum and Fast2Sum as the    *
 *      tmpl_DoubleDouble_Add function.                                       *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum.                                                    *
 *      2.) If x and y have a different sign (one is negative and one is      *
 *          positive), this function is not safe to use since the relative    *
 *          error may be massive (greater than or equal to one). In this case *
 *          you should use tmpl_DoubleDouble_Add.                             *
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
 *          ACM Trans. Math. Software Vol. 28, No. 2: Pages 152–205           *
 *      3.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      4.) Dekker, T.J. (June 1971).                                         *
 *          "A floating-point technique for                                   *
 *              extending the available precision."                           *
 *          Numerische Mathematik. Vol. 18, No. 3: Pages 224–242.             *
 *      5.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol. 18, No. 3: Pages 305–363   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 26, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_QUICK_ADD_LDOUBLEDOUBLE_H
#define TMPL_QUICK_ADD_LDOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/inline/two_sum/tmpl_two_sum_ldouble.h>
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_ldouble.h>

#else

extern void
tmpl_LDouble_Two_Sum(long double x,
                     long double y,
                     long double * TMPL_RESTRICT const out,
                     long double * TMPL_RESTRICT const err);

extern void
tmpl_LDouble_Fast_Two_Sum(long double x,
                          long double y,
                          long double * TMPL_RESTRICT const out,
                          long double * TMPL_RESTRICT const err);

#endif

/*  Standard 2Sum algorithm at double precision.                              */
TMPL_INLINE_DECL
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Quick_Add(const tmpl_LongDoubleDouble * const x,
                             const tmpl_LongDoubleDouble * const y)
{

    /*  The output double-double word.                                        */
    tmpl_LongDoubleDouble out;

    tmpl_LDouble_Two_Sum(x->dat[0], y->dat[0], &out.dat[0], &out.dat[1]);
    out.dat[1] += x->dat[1] + y->dat[1];
    tmpl_LDouble_Fast_Two_Sum(out.dat[0], out.dat[1], &out.dat[0], &out.dat[1]);
    return out;
}
/*  End of tmpl_LDoubleDouble_Quick_Add.                                      */

#endif
/*  End of include guard.                                                     */
