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
 *      src/two_sum/                                                          *
 *          tmpl_Double_Two_Sum:                                              *
 *              Performs the 2Sum of two numbers: (sum, error) = 2Sum(x, y).  *
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
 *      1.) This function calls libtmpl's 2Sum and Fast2Sum routines. Those   *
 *          routines use floating-point barriers to protect against           *
 *          optimizations like -ffast-math. On GCC and Clang this results in  *
 *          a no-op and the generated machine code is both correct and        *
 *          optimal. On other compilers these barriers may use the volatile   *
 *          keyword which significantly slows things down. Clang-like         *
 *          compilers such as ICX, Open XL, and AOCC are able to use the      *
 *          no-op barriers, as is MSVC. Compilers like TCC and PCC are not.   *
 *                                                                            *
 *      2.) If x and y have a different sign (one is negative and one is      *
 *          positive), this function is not safe to use since the relative    *
 *          error may be massive (greater than or equal to one). In this case *
 *          you should use tmpl_DoubleDouble_Add.                             *
 *  References:                                                               *
 *      1.) Joldes, M., Muller, J., Popescu, V. (October 2017).               *
 *          Tight and rigorous error bounds for basic                         *
 *          building blocks of double-word arithmetic.                        *
 *          ACM Transactions on Mathematical Software, Vol. 44, No. 2.        *
 *                                                                            *
 *          Detailed description of double-double algorithms are provided     *
 *          here. libtmpl uses many of the ideas from this paper in it's      *
 *          implementation of double-double arithmetic.                       *
 *                                                                            *
 *      2.) Li, X., Demmel, J., Bailey, D., Henry, G., Hida, Y.,              *
 *          Iskandar, J., Kahan, W., Kapur, A., Martin, M.,                   *
 *          Tung, T., Yoo, D. (2002).                                         *
 *          Design, implementation and testing of extended and mixed          *
 *          precision BLAS.                                                   *
 *          ACM Trans. Math. Software Vol. 28, No. 2: Pages 152-205           *
 *                                                                            *
 *          Lengthy paper on the details of double-double arithmetic with     *
 *          applications to linear algebra routines.                          *
 *                                                                            *
 *      3.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          Library for Double-Double and Quad-Double Arithmetic.             *
 *                                                                            *
 *          Paper detailing the implementation of double-double and           *
 *          quad-double arithmetic. The 2Sum and Fast2Sum algorithms are      *
 *          described here, as is the 2Prod algorithm.                        *
 *                                                                            *
 *      4.) Dekker, T.J. (June 1971).                                         *
 *          A floating-point technique for extending the available precision. *
 *          Numerische Mathematik. Volume 18, Number 3: Pages 224-242.        *
 *                                                                            *
 *          Classic paper on double-double arithmetic. Dekker's analysis of   *
 *          the Fast2Sum algorithm is provided here.                          *
 *                                                                            *
 *      5.) Shewchuk, J. (October 1997).                                      *
 *          Adaptive Precision Floating-Point Arithmetic and                  *
 *          Fast Robust Geometric Predicates.                                 *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 *                                                                            *
 *          Detailed analysis of 2Sum, Fast2Sum, and 2Prod, allowing for      *
 *          arbitrarily sized floating-point types. This paper is useful for  *
 *          extending these algorithms to the various long double types such  *
 *          as 80-bit extended and 128-bit quadruple. Proofs are included     *
 *          along with the algorithms.                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing the TMPL_ALWAYS_INLINE macro.               *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_two_sum.h:                                                       *
 *          Provides 2Sum, Fast2Sum, and other 2Sum-like routines.            *
 *  4.) tmpl_doubledouble.h:                                                  *
 *          Function prototype and double-double typedefs provided here.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 26, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/07/29: Ryan Maguire                                                  *
 *      Added C23 attributes, merged inline vs. non-inline.                   *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  2Sum and Fast2Sum are needed for double-double addition.                  */
#include <libtmpl/include/tmpl_two_sum.h>

/*  Function prototytpe / forward declaration found here.                     */
#include <libtmpl/include/tmpl_doubledouble.h>

/*  Performs fast addition for two double-doubles.                            */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_DoubleDouble
tmpl_DoubleDouble_Quick_Add(const tmpl_DoubleDouble * const x,
                            const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED
{

    /*  The output double-double word, the fast sum of x and y.               */
    tmpl_DoubleDouble sum;

    /*  The high order part of the sum is the floating-point sum of the high  *
     *  parts of the inputs. The error can be tracked using 2Sum.             */
    tmpl_Double_Two_Sum(x->dat[0], y->dat[0], &sum.dat[0], &sum.dat[1]);

    /*  The low parts of the components contribute to the error in the sum.   */
    sum.dat[1] += x->dat[1] + y->dat[1];

    /*  Under the assumption that x and y have the same sign, or |x| >> |y|,  *
     *  we may conclude with a Fast2Sum. The error bound for this is          *
     *                                                                        *
     *      err < 4 eps^2 (|x| + |y|)                                         *
     *                                                                        *
     *  The absolute value signs here mean that the relative error may be     *
     *  very large, see Joldes et. al (2017) algorithm 5 for details. In the  *
     *  case where sign(x) = sign(y) or |x| >> |y|, this error bound is fine. */
    tmpl_Double_Fast_Two_Sum(sum.dat[0], sum.dat[1], &sum.dat[0], &sum.dat[1]);
    return sum;
}
/*  End of tmpl_DoubleDouble_Quick_Add.                                       */
