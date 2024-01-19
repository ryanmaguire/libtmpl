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
 *                      tmpl_symmetric_derivative_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Numerically computes derivatives using a symmetric difference.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Symmetric_Derivative                                      *
 *  Purpose:                                                                  *
 *      Numerically computes the derivative of a function.                    *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in a double and returns a double.           *
 *      x (double):                                                           *
 *          The point where f' is to be computed.                             *
 *      h (double):                                                           *
 *          Step size for the stencil.                                        *
 *  Output:                                                                   *
 *      f_prime (double):                                                     *
 *          The numerical derivative f'(x).                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the symmetric difference quotient:                                *
 *                                                                            *
 *                    f(x + h) - f(x - h)                                     *
 *          f'(x) ~=  -------------------                                     *
 *                            2 h                                             *
 *                                                                            *
 *      The error goes like O(h^2).                                           *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires two calls to the input function. It is     *
 *          faster than higher-order stencil methods, but the error is worse. *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_differentiation_real.h:                                          *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2024                                              *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_differentiation_real.h>

/*  Computes the numerical first derivative using a symmetric difference.     */
double tmpl_Double_Symmetric_Derivative(double (*f)(double), double x, double h)
{
    /*  Symmetric difference using three stencil points. The formula for the  *
     *  approximation has the middle stencil point cancel, so we need only    *
     *  evaluate the function at the left and right stencil points.           */
    const double x0 = x - h;
    const double x2 = x + h;

    /*  Evaluate the function at the stencil points.                          */
    const double y0 = f(x0);
    const double y2 = f(x2);

    /*  Symmetric stencil has weights 1 and -1, so quite the simple formula.  */
    const double num = y2 - y0;

    /*  The denominator is proportional to the step size.                     */
    const double den = 2.0 * h;
    return num / den;
}
/*  End of tmpl_Double_Symmetric_Derivative.                                  */
