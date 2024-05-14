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
 *              tmpl_complex_poly_deriv_eval_real_coeffs_double               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates higher derivatives of a polynomial at a complex number.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Poly_Deriv_Eval_Real_Coeffs                              *
 *  Purpose:                                                                  *
 *      Evaluates higher order derivatives of a polynomial.                   *
 *  Arguments:                                                                *
 *      coeffs (const double * const):                                        *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      dp_z (double):                                                        *
 *          The "deriv" derivative of the polynomial evaluated at z.          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Factorial:                                            *
 *              Computes n! for non-negative integers.                        *
 *          tmpl_Double_Falling_Factorial:                                    *
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

tmpl_ComplexDouble
tmpl_CDouble_Poly_Deriv_Eval_Real_Coeffs(const double * const coeffs,
                                         unsigned int degree,
                                         unsigned int deriv,
                                         tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble dpoly;
    double factor, numer, denom;
    unsigned int n, N;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as a zero polynomial and   *
     *  return zero if it is NULL.                                            */
    if (!coeffs)
        return tmpl_CDouble_Zero;

    /*  If the order of the derivative is high enough, the answer is zero.    */
    if (degree < deriv)
        return tmpl_CDouble_Zero;

    /*  If the order of the derivative matches the degree, the answer is      *
     *  N! a_{N}, where N is the degree.                                      */
    if (degree == deriv)
    {
        dpoly.dat[0] = coeffs[degree] * tmpl_Double_Factorial(degree);
        dpoly.dat[1] = 0.0;
        return dpoly;
    }

    /*  Optimized case 1: Zeroth order derivative, simple polynomial eval.    */
    if (deriv == 0U)
        return tmpl_CDouble_Poly_Eval_Real_Coeffs(coeffs, (size_t)degree, z);

    /*  For all other orders we need to explicitly evaluate. The derivatives  *
     *  will kill off the first "deriv" terms, set N to the difference.       */
    N = degree - deriv;

    /*  The coefficient is computed using the falling factorial.              */
    factor = tmpl_Double_Falling_Factorial(degree, deriv);
    dpoly.dat[0] = factor*coeffs[degree];
    dpoly.dat[1] = 0.0;

    /*  To avoid repeated calls to the falling factorial function, we can     *
     *  compute the next falling factorial from the previous one combined     *
     *  with the following ratio. We'll update this ratio instead of          *
     *  explicitly calling the function.                                      */
    numer = (double)N;
    denom = (double)degree;

    /*  Use Horner's method of polynomial evaluation for the rest.            */
    for (n = 1U; n <= N; ++n)
    {
        /*  Avoid overwriting, preserve the real part of dpoly.               */
        const double re = dpoly.dat[0];

        /*  Compute the next falling factorial.                               */
        factor *= numer / denom;

        /*  Update the evaluation with the next term.                         */
        dpoly.dat[0] = re*z.dat[0] - dpoly.dat[1]*z.dat[1] + coeffs[degree - n];
        dpoly.dat[1] = re*z.dat[1] + dpoly.dat[1]*z.dat[0];

        /*  Increment the ratio.                                              */
        numer -= 1.0;
        denom -= 1.0;
    }

    return dpoly;
}
/*  End of tmpl_CDouble_Poly_Deriv_Eval_Real_Coeffs.                          */
