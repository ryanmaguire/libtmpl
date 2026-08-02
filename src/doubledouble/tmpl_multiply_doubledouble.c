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
 *                         tmpl_multiply_doubledouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Performs multiplication for two double-word real numbers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_DoubleDouble_Multiply                                            *
 *  Purpose:                                                                  *
 *      Evaluates the product of two double-doubles.                          *
 *  Arguments:                                                                *
 *      x (const tmpl_DoubleDouble * const):                                  *
 *          A double-double real number.                                      *
 *      y (const tmpl_DoubleDouble * const):                                  *
 *          Another double-double real number.                                *
 *  Output:                                                                   *
 *      product (tmpl_DoubleDouble):                                          *
 *          The double-double product of x and y.                             *
 *  Called Functions:                                                         *
 *      src/two_sum/                                                          *
 *          tmpl_Double_Fast_Two_Sum:                                         *
 *              Performs Fast2Sum: (sum, error) = Fast2Sum(x, y).             *
 *      src/two_prod/                                                         *
 *          tmpl_Double_Two_Prod:                                             *
 *              Performs 2Prod for two numbers: (prod, error) = 2Prod(x, y).  *
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
 *  4.) tmpl_two_prod.h:                                                      *
 *          Provides the 2Prod function.                                      *
 *  5.) tmpl_doubledouble.h:                                                  *
 *          Function prototype and double-double typedefs provided here.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 12, 2026                                                  *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Optional C23 attributes for optimization provided here.                   */
#include <libtmpl/include/tmpl_attributes.h>

/*  2Sum and 2Prod are needed for double-double multiplication.               */
#include <libtmpl/include/tmpl_two_sum.h>
#include <libtmpl/include/tmpl_two_prod.h>

/*  Function prototytpe / forward declaration found here.                     */
#include <libtmpl/include/tmpl_doubledouble.h>

/*  Performs multiplication for two double-doubles.                           */
TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_DoubleDouble
tmpl_DoubleDouble_Multiply(const tmpl_DoubleDouble * const x,
                           const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED
{
    /*  Declare necessary variables. C89 requires declerations at the top.    */
    tmpl_DoubleDouble out;

    /*  Given x = xhi + xlo and y = yhi + ylo, we have:                       *
     *      x * y = (xhi + xlo) * (yhi + ylo)                                 *
     *            = xhi*yhi + xhi*ylo + xlo*yhi + xlo*ylo                     *
     *           ~= xhi*yhi + xhi*ylo + xlo*yhi                               *
     *  The xlo*ylo term will not effect the result and can be discarded. We  *
     *  compute xhi*yhi exactly using 2Prod, and then add the middle part of  *
     *  the sum, xhi*ylo + xlo*yhi, to the error term in 2Prod. A call to     *
     *  Fast2Sum will then complete the computation. Declare the required     *
     *  variables for this algorithm.                                         */
    double prod_hi, err_hi, compensation;
    double prod_hi_lo, prod_lo_hi, prod_mid;

    /*  xhi * yhi, exact, stored in two doubles.                              */
    tmpl_Double_Two_Prod(x->dat[0], y->dat[0], &prod_hi, &err_hi);

    /*  xhi * ylo + xlo * yhi. These values won't effect the higher order     *
     *  bits very much, but they will effect the low word of the output.      */
    prod_hi_lo = x->dat[0] * y->dat[1];
    prod_lo_hi = x->dat[1] * y->dat[0];

    /*  The middle product, xhi*ylo + xlo*yhi, can be on the same order of    *
     *  magnitude as the low word in the 2Prod performed above. The new       *
     *  compensation term is then the sum of these values.                    */
    prod_mid = prod_hi_lo + prod_lo_hi;
    compensation = err_hi + prod_mid;

    /*  prod_hi is large enough that we can do Fast2Sum with compensation,    *
     *  instead of the full 2Sum. This saves us a few arithmetic operations   *
     *  without losing precision.                                             */
    tmpl_Double_Fast_Two_Sum(prod_hi, compensation, &out.dat[0], &out.dat[1]);

    /*  The output is accurate to 7*eps^2, where eps is the epsilon value of  *
     *  double. For 64-bit double, this is about 9x10^-32.                    */
    return out;
}
/*  End of tmpl_DoubleDouble_Multiply.                                        */
