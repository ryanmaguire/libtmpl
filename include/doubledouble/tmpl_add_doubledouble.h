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
 *                            tmpl_add_doubledouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs addition for two double-word real numbers.                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_DoubleDouble_Add                                                 *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two double-doubles.                              *
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
 *          tmpl_Double_Two_Sum:                                              *
 *              Performs the 2Sum of two numbers: (sum, error) = 2Sum(x, y).  *
 *  Method:                                                                   *
 *      We use the corrected algorithm presented in Li et al. 2002, and       *
 *      follow the implementation in Joldas et al. 2017 near verbatim. That   *
 *      is, we do:                                                            *
 *                                                                            *
 *          (sum_hi, err_hi) = 2Sum(xhi, yhi)                                 *
 *          (sum_lo, err_lo) = 2Sum(xlo, ylo)                                 *
 *                correction = err_hi + sum_lo                                *
 *        (comp_hi, comp_lo) = Fast2Sum(sum_hi, correction)                   *
 *                correction = err_lo + comp_lo                               *
 *          (out_hi, out_lo) = Fast2Sum(comp_hi, correction)                  *
 *                                                                            *
 *      The output double-double is out_hi + out_lo. The shorter (and faster) *
 *      Dekker algorithm is:                                                  *
 *                                                                            *
 *          (sum_hi, sum_lo) = 2Sum(xhi, yhi)                                 *
 *                   comp_lo = xlo + ylo                                      *
 *                   comp_hi = sum_lo + comp_lo                               *
 *          (out_hi, out_lo) = Fast2Sum(sum_hi, comp_hi)                      *
 *                                                                            *
 *      Half the number of 2Sum and Fast2Sum calls, but this requires x and   *
 *      y have the same sign. That is, either x and y are both positive, or   *
 *      x and y are both negative. If you are sure this is true, you should   *
 *      use tmpl_DoubleDouble_Quick_Add instead.                              *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum.                                                    *
 *      2.) If both x and y have the same sign, it is faster (and about as    *
 *          accurate) to use tmpl_DoubleDouble_Quick_Add. If x and y have     *
 *          differing signs, you should use this function.                    *
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
#ifndef TMPL_ADD_DOUBLEDOUBLE_H
#define TMPL_ADD_DOUBLEDOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/two_sum/tmpl_two_sum_double.h>
#include <libtmpl/include/two_sum/tmpl_fast_two_sum_double.h>

#else

extern void
tmpl_Double_Two_Sum(double x,
                    double y,
                    double * TMPL_RESTRICT const out,
                    double * TMPL_RESTRICT const err);

extern void
tmpl_Double_Fast_Two_Sum(double x,
                         double y,
                         double * TMPL_RESTRICT const out,
                         double * TMPL_RESTRICT const err);

#endif

/*  Standard 2Sum algorithm at double precision.                              */
TMPL_INLINE_DECL
tmpl_DoubleDouble
tmpl_DoubleDouble_Add(const tmpl_DoubleDouble * const x,
                      const tmpl_DoubleDouble * const y)
{
    /*  Naive sums and their error terms from the two-sum algorithm.          */
    double sum_hi, err_hi, sum_lo, err_lo;

    /*  Compensation and correction factors used in the fast-two-sums.        */
    double corr_hi, corr_lo, comp_hi, comp_lo;

    /*  The output double-double word.                                        */
    tmpl_DoubleDouble out;

    tmpl_Double_Two_Sum(x->dat[0], y->dat[0], &sum_hi, &err_hi);
    tmpl_Double_Two_Sum(x->dat[1], y->dat[1], &sum_lo, &err_lo);
    corr_hi = err_hi + sum_lo;
    tmpl_Double_Fast_Two_Sum(sum_hi, corr_hi, &comp_hi, &comp_lo);
    corr_lo = err_lo + comp_lo;
    tmpl_Double_Fast_Two_Sum(comp_hi, corr_lo, &(out.dat[0]), &(out.dat[1]));

    return out;
}
/*  End of tmpl_DoubleDouble_Add.                                             */

#endif
/*  End of include guard.                                                     */
