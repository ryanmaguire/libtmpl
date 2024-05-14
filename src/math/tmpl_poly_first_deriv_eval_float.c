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
 *                      tmpl_poly_first_deriv_eval_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates the derivative of a polynomial at a given real number.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Poly_First_Deriv_Eval                                      *
 *  Purpose:                                                                  *
 *      Evaluates the derivative of a polynomial at a real number.            *
 *  Arguments:                                                                *
 *      coeffs (const float * const):                                         *
 *          The coefficients array for the polynomial.                        *
 *      degree (size_t):                                                      *
 *          The degree of the polynomial. There must be at least degree + 1   *
 *          elements in the coeffs array.                                     *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      dp_x (float):                                                         *
 *          The derivative of the polynomial evaluated at x.                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the derivative at the given point.    *
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
 *  Date:       May 14, 2024                                                  *
 ******************************************************************************/

/*  size_t typedef is here.                                                   */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for evaluating the derivative of a polynomial by Horner's method.*/
float
tmpl_Float_Poly_First_Deriv_Eval(const float * const coeffs,
                                 size_t degree, float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    float dpoly, factor;
    size_t n;

    /*  If the input coefficient pointer is NULL, trying to access it will    *
     *  result in a segmentation fault. Treat this as an empty, or zero,      *
     *  polynomial and return zero.                                           */
    if (!coeffs)
        return 0.0F;

    /*  Degree should be at least one, otherwise this is not a polynomial but *
     *  a constant. Check this. If degree is zero, the derivative is zero.    */
    if (degree == 0)
        return 0.0F;

    /*  If the degree is one, the derivative is constant. Return this value.  */
    if (degree == 1)
        return coeffs[1];

    /*  Otherwise we have an actual polynomial to evaluate. Set dpoly to      *
     *  Na_{N}*z + (N-1)a_{N-1} where N is the degree.                        */
    factor = (float)degree;
    dpoly = factor*(coeffs[degree]*x + coeffs[degree - 1]) - coeffs[degree - 1];

    /*  The Nth and (N-1)th degree terms are done, decrement the factor.      */
    factor -= 2.0F;

    /*  Use Horner's method of polynomial computation.                        */
    for (n = 2; n < degree; ++n)
    {
        dpoly = x*dpoly + factor*coeffs[degree - n];
        factor -= 1.0F;
    }

    return dpoly;
}
/*  End of tmpl_Float_Poly_First_Deriv_Eval.                                  */
