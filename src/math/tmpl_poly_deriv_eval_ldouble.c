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
 *                        tmpl_poly_deriv_eval_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates higher derivatives of a polynomial at a given real number.  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Poly_Deriv_Eval                                          *
 *  Purpose:                                                                  *
 *      Evaluates higher order derivatives of a polynomial at a real number.  *
 *  Arguments:                                                                *
 *      coeffs (const long double * const):                                   *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      dp_x (long double):                                                   *
 *          The "deriv" derivative of the polynomial evaluated at x.          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate at the given point.                   *
 *  Notes:                                                                    *
 *      For very large polynomials with varying sizes for the coefficients,   *
 *      error may accumulate as one performs the sum.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/13: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Evaluates higher order derivatives of a polynomial at a given number.     */
long double
tmpl_LDouble_Poly_Deriv_Eval(const long double * const coeffs,
                             unsigned int degree,
                             unsigned int deriv, long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double dpoly, factor, numer, denom;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as a zero polynomial and   *
     *  return zero if it is NULL.                                            */
    if (!coeffs)
        return 0.0L;

    /*  If the order of the derivative is high enough, the answer is zero.    */
    if (degree < deriv)
        return 0.0L;

    /*  If the order of the derivative matches the degree, the answer is      *
     *  N! a_{N}, where N is the degree.                                      */
    if (degree == deriv)
        return coeffs[degree] * tmpl_LDouble_Factorial(degree);

    /*  Optimized case 1: Zeroth order derivative, simple polynomial eval.    */
    if (deriv == 0U)
        return tmpl_LDouble_Poly_Eval(coeffs, (size_t)degree, x);

    /*  Optimized case 2: First derivative.                                   */
    if (deriv == 1U)
        return tmpl_LDouble_Poly_First_Deriv_Eval(coeffs, (size_t)degree, x);

    /*  For all other orders we need to explicitly evaluate. The derivatives  *
     *  will kill off the first "deriv" terms, set N to the difference.       */
    N = degree - deriv;

    /*  The coefficient is computed using the falling factorial.              */
    factor = tmpl_LDouble_Falling_Factorial(degree, deriv);
    dpoly = factor*coeffs[degree];

    /*  To avoid repeated calls to the falling factorial function, we can     *
     *  compute the next falling factorial from the previous one combined     *
     *  with the following ratio. We'll update this ratio instead of          *
     *  explicitly calling the function.                                      */
    numer = (long double)N;
    denom = (long double)degree;

    /*  Use Horner's method of polynomial evaluation for the rest.            */
    for (n = 1U; n <= N; ++n)
    {
        /*  Compute the next falling factorial.                               */
        factor *= numer / denom;

        /*  Update the evaluation with the next term.                         */
        dpoly = x*dpoly + factor*coeffs[degree - n];

        /*  Increment the ratio.                                              */
        numer -= 1.0L;
        denom -= 1.0L;
    }

    return dpoly;
}
/*  End of tmpl_LDouble_Poly_Deriv_Eval.                                      */
