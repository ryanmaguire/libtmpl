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
 *                           tmpl_poly_eval_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates a polynomial at a given real number.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Poly_Eval                                                *
 *  Purpose:                                                                  *
 *      Evaluates a polynomial at a real number using Horner's method.        *
 *  Arguments:                                                                *
 *      coeffs (const long double * const):                                   *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      p_x (long double):                                                    *
 *          The polynomial evaluated at x.                                    *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Factorial:                                           *
 *              Computes n! for non-negative integers.                        *
 *          tmpl_LDouble_Falling_Factorial:                                   *
 *              Computes n! / (n - k)! for non-negative integers.             *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial at the given point.    *
 *  Notes:                                                                    *
 *      For very large polynomials with varying sizes for the coefficients,   *
 *      error may accumulate as one performs the sum.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) stddef.h:                                                             *
 *          Standard library header with the size_t typedef.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/13: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 ******************************************************************************/

/*  size_t typedef is here.                                                   */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for evaluating a polynomial via Horner's method.                 */
long double
tmpl_LDouble_Poly_Eval(const long double * const coeffs,
                       size_t degree, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double poly;
    size_t n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as an empty, or zero,      *
     *  polynomial and return zero.                                           */
    if (!coeffs)
        return 0.0L;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, we'll just return the      *
     *  zeroth coefficient (a constant polynomial).                           */
    if (degree == 0)
        return coeffs[0];

    /*  Otherwise we have an actual polynomial to evaluate. Set poly to       *
     *  a_{N}*z + a_{N-1} where N is the degree.                              */
    poly = coeffs[degree]*x + coeffs[degree - 1];

    /*  Use Horner's method of polynomial computation.                        */
    for (n = 2; n <= degree; ++n)
        poly = x*poly + coeffs[degree - n];

    return poly;
}
/*  End of tmpl_LDouble_Poly_Eval.                                            */
