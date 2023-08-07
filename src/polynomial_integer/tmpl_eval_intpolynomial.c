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
 *                          tmpl_eval_intpolynomial                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Evaluates a polynomial at an integer.                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_IntPolynomial_Eval                                               *
 *  Purpose:                                                                  *
 *      Evaluates a polynomial with integer coefficients at an integer.       *
 *  Arguments:                                                                *
 *      poly (const tmpl_IntPolynomial *):                                    *
 *          A pointer to a polynomial.                                        *
 *      val (int):                                                            *
 *          The integer at which we're evaluating the polynomial.             *
 *  Outputs:                                                                  *
 *      eval (int):                                                           *
 *          The value of poly at the integer val.                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to loop over the coefficients of the polynomial.  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library file where size_t is provided.                   *
 *  2.) tmpl_polynomial_integer.h:                                            *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 27, 2023                                                *
 ******************************************************************************/

/*  size_t date type provided here.                                           */
#include <stddef.h>

/*  Function prototype provided here.                                         */
#include <libtmpl/include/tmpl_polynomial_integer.h>

/*  Function for evaluating a polynomial at an integer.                       */
int tmpl_IntPolynomial_Eval(const tmpl_IntPolynomial *poly, int val)
{
    /*  Variable for indexing over the coefficients of poly.                  */
    size_t n;

    /*  Variable for the output, computed via Horner's method.                */
    int eval;

    /*  If the input polynomial is NULL consider it to be the zero polynomial.*/
    if (!poly)
        return 0;

    /*  Handle flawed polynomials in a similar manner. Return zero.           */
    if (poly->error_occurred)
        return 0;

    /*  The empty polynomial can also be considered the zero polynomial.      */
    if (!poly->coeffs)
        return 0;

    /*  Final special case. For a constant polynomial return the constant.    */
    if (poly->degree == (size_t)0)
        return poly->coeffs[0];

    /*  Initialize the output to the coefficient of the highest term.         */
    eval = poly->coeffs[poly->degree];

    /*  Loop over the remaining terms using Horner's method.                  */
    for (n = (size_t)1; n <= poly->degree; ++n)
        eval = poly->coeffs[poly->degree - n] + val*eval;

    return eval;
}
/*  End of tmpl_IntPolynomial_Eval.                                           */
