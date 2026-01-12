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
 *                           tmpl_add_ldoubledouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs addition for two long-double-word real numbers.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDoubleDouble_Add                                                *
 *  Purpose:                                                                  *
 *      Evaluates the sum of two long-double-doubles.                         *
 *  Arguments:                                                                *
 *      x (const tmpl_LongDoubleDouble * const):                              *
 *          A long-double-double real number.                                 *
 *      y (const tmpl_LongDoubleDouble * const):                              *
 *          Another long-double-double real number.                           *
 *  Output:                                                                   *
 *      sum (tmpl_LongDoubleDouble):                                          *
 *          The double-double sum of x and y.                                 *
 *  Called Functions:                                                         *
 *      tmpl_two_sum.h:                                                       *
 *          tmpl_LDouble_Two_Sum:                                             *
 *              Performs the 2Sum of two numbers: (sum, error) = 2Sum(x, y).  *
 *          tmpl_LDouble_Fast_Two_Sum:                                        *
 *              Performs Fast2Sum: (sum, error) = Fast2Sum(x, y).             *
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
 *      use tmpl_LDoubleDouble_Quick_Add instead. The Dekker method also      *
 *      works if |x| is significantly greater than |y|. If you are sure of    *
 *      this, use tmpl_LDoubleDouble_Quick_Add.                               *
 *  Notes:                                                                    *
 *      1.) Depending on compiler and architecture we may need to declare     *
 *          certain variables as volatile. Failure to do so results in a      *
 *          poor Fast2Sum or a poor 2Sum. The source code for 2Sum and        *
 *          Fast2Sum use the TMPL_VOLATILE macro for this. On default builds  *
 *          this macro is empty, meaning the volatile keyword is not used.    *
 *          If unit tests for double-double arithmetic fail, one should first *
 *          try enabling the TMPL_VOLATILE macro. In the Makefile this is     *
 *          done via make USE_VOLATILE=1 [other options].                     *
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
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 26, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ADD_LDOUBLEDOUBLE_H
#define TMPL_ADD_LDOUBLEDOUBLE_H

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

/*  Performs addition for two long-double-doubles.                            */
TMPL_INLINE_DECL
tmpl_LongDoubleDouble
tmpl_LDoubleDouble_Add(const tmpl_LongDoubleDouble * const x,
                       const tmpl_LongDoubleDouble * const y)
{
    /*  Naive sums and their error terms from the two-sum algorithm.          */
    long double sum_hi, err_hi, sum_lo, err_lo;

    /*  Compensation and correction factors used in the fast-two-sums.        */
    long double corr_hi, corr_lo, comp_hi, comp_lo;

    /*  The output long-double-double word.                                   */
    tmpl_LongDoubleDouble out;

    /*  Perform 2Sum with the high and low parts of x and y.                  */
    tmpl_LDouble_Two_Sum(x->dat[0], y->dat[0], &sum_hi, &err_hi);
    tmpl_LDouble_Two_Sum(x->dat[1], y->dat[1], &sum_lo, &err_lo);

    /*  We cannot attain perfect precision here. To sum together two 256-bit  *
     *  long-double-doubles may require 512 bits, which we do not have.       *
     *  We'll lose a bit of precision, but the the error is on the order of   *
     *  eps^2, where eps is epsilon for long double. For 80-bit exteneded,    *
     *  this means the error is about 10^-38.                                 *
     *                                                                        *
     *  sum_hi + sum_lo is not the most accurate value for x + y. Compute     *
     *  correction terms that take into account lower order bits.             */
    corr_hi = err_hi + sum_lo;

    /*  We can now use Fast2Sum, instead of 2Sum, with the correction terms.  *
     *  This is because sum_hi and corr_hi have exponents that differ enough  *
     *  that cancellation will not occur, and no additional error will be     *
     *  introduced. See Joldas et. al (2017), theorem 3.1 for details. Use    *
     *  Fast2Sum and collect the compensation terms.                          */
    tmpl_LDouble_Fast_Two_Sum(sum_hi, corr_hi, &comp_hi, &comp_lo);

    /*  Add the low order compensation and the low order error to get the     *
     *  low order correction. We will Fast2Sum this with the higher order     *
     *  compensation term.                                                    */
    corr_lo = err_lo + comp_lo;

    /*  We can conlude with a Fast2Sum with the high order compensation and   *
     *  the low order correction. One can show that Fast2Sum introduces no    *
     *  additional error with comp_hi and corr_lo, so we can save a call to   *
     *  2Sum. Again, see theorem 3.1 in Joldas et. al (2017).                 */
    tmpl_LDouble_Fast_Two_Sum(comp_hi, corr_lo, &(out.dat[0]), &(out.dat[1]));

    /*  out now has the long-double-double sum of x and y. Note that we may   *
     *  lose all lower order bits. For example, if x has 128 significant bits,*
     *  and if y is, say, something on the order of 10^-45 * x, then the sums *
     *  will cancel and yield x + y = x. This example assumes long double is  *
     *  represented by 80-bit extended precision. Similar examples can be     *
     *  constructed if long double is represented by quadruple.               *
     *  To attain perfect precision, one would need to use quad-long-double   *
     *  arithmetic, or use the GrowExpansion algorithm. Nevertheless,         *
     *  the error here is given by:                                           *
     *                                                                        *
     *      Err(x + y) < 3*eps^2 + 12*eps^3                                   *
     *                                                                        *
     *  See algorithm 6 in Joldas et. al (2017). For 80-bit long double, this *
     *  is around 10^-38.                                                     */
    return out;
}
/*  End of tmpl_LDoubleDouble_Add.                                            */

#endif
/*  End of include guard.                                                     */
