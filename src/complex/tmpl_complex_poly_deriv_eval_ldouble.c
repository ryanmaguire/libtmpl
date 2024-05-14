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
 *                    tmpl_complex_poly_deriv_eval_ldouble                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates higher derivatives of a polynomial at a complex number.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Poly_Deriv_Eval_Real_Coeffs                             *
 *  Purpose:                                                                  *
 *      Evaluates higher order derivatives of a polynomial.                   *
 *  Arguments:                                                                *
 *      coeffs (const long double * const):                                   *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      dp_z (tmpl_ComplexLongDouble):                                        *
 *          The "deriv" derivative of the polynomial evaluated at z.          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_Factorial:                                           *
 *              Computes n! for non-negative integers.                        *
 *          tmpl_LDouble_Falling_Factorial:                                   *
 *              Computes n! / (n - k)! for non-negative integers.             *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate at the given point.                   *
 *  Notes:                                                                    *
 *      For very large polynomials with varying sizes for the coefficients,   *
 *      error may accumulate as one performs the sum.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with factorial functions.                             *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/05/13: Ryan Maguire                                                  *
 *      Added license and comments. Moved float and long double to their own  *
 *      files.                                                                *
 ******************************************************************************/

/*  Factorial and falling factorial functions are provided here.              */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

tmpl_ComplexLongDouble
tmpl_CLDouble_Poly_Deriv_Eval(const tmpl_ComplexLongDouble * const coeffs,
                              unsigned int degree,
                              unsigned int deriv,
                              tmpl_ComplexLongDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble dpoly;
    long double factor, numer, denom;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as a zero polynomial and   *
     *  return zero if it is NULL.                                            */
    if (!coeffs)
        return tmpl_CLDouble_Zero;

    /*  If the order of the derivative is high enough, the answer is zero.    */
    if (degree < deriv)
        return tmpl_CLDouble_Zero;

    /*  If the order of the derivative matches the degree, the answer is      *
     *  N! a_{N}, where N is the degree.                                      */
    if (degree == deriv)
    {
        factor = tmpl_LDouble_Factorial(degree);
        dpoly.dat[0] = coeffs[degree].dat[0] * factor;
        dpoly.dat[1] = coeffs[degree].dat[1] * factor;
        return dpoly;
    }

    /*  Optimized case 1: Zeroth order derivative, simple polynomial eval.    */
    if (deriv == 0U)
        return tmpl_CLDouble_Poly_Eval(coeffs, (size_t)degree, z);

    /*  For all other orders we need to explicitly evaluate. The derivatives  *
     *  will kill off the first "deriv" terms, set N to the difference.       */
    N = degree - deriv;

    /*  The coefficient is computed using the falling factorial.              */
    factor = tmpl_LDouble_Falling_Factorial(degree, deriv);
    dpoly.dat[0] = factor*coeffs[degree].dat[0];
    dpoly.dat[1] = factor*coeffs[degree].dat[1];

    /*  To avoid repeated calls to the falling factorial function, we can     *
     *  compute the next falling factorial from the previous one combined     *
     *  with the following ratio. We'll update this ratio instead of          *
     *  explicitly calling the function.                                      */
    numer = (long double)N;
    denom = (long double)degree;

    /*  Use Horner's method of polynomial evaluation for the rest.            */
    for (n = 1U; n <= N; ++n)
    {
        /*  Avoid overwriting, preserve the real part of dpoly.               */
        const long double re = dpoly.dat[0];

        /*  Current index for the coeffs array.                               */
        const unsigned int ind = degree - n;

        /*  Compute the next falling factorial.                               */
        factor *= numer / denom;

        /*  Update the evaluation with the next term.                         */
        dpoly.dat[0] = re*z.dat[0] - dpoly.dat[1]*z.dat[1] +
                       factor*coeffs[ind].dat[0];
        dpoly.dat[1] = re*z.dat[1] + dpoly.dat[1]*z.dat[0] +
                       factor*coeffs[ind].dat[1];

        /*  Increment the ratio.                                              */
        numer -= 1.0L;
        denom -= 1.0L;
    }

    return dpoly;
}
/*  End of tmpl_CLDouble_Poly_Deriv_Eval.                                     */
