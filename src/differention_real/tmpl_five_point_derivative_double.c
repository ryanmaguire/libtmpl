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
 *                     tmpl_five_point_derivative_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Numerically computes derivatives using a five-point stencil.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Five_Point_Derivative                                     *
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
 *      Use a five-point stencil to numerically compute the derivative. By    *
 *      using either Taylor series or Lagrange interpolation, one obtains a   *
 *      numerical formula for the derivative:                                 *
 *                                                                            *
 *                    f(x - 2h) - 8 f(x - h) + 8 f(x + h) - f(x + 2h)         *
 *          f'(x) ~=  -----------------------------------------------         *
 *                                         12 h                               *
 *                                                                            *
 *      The error goes like O(h^4).                                           *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires four calls to the input function. If the   *
 *          evaluation of this function is expensive it may be advisable to   *
 *          use symmetric or secant derivatives (two function calls).         *
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
 *  Date:       April 08, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/01/19: Ryan Maguire                                                  *
 *      Moved float and long double to their own files. Added license.        *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_differentiation_real.h>

/*  Computes the numerical first derivative using a five point stencil.       */
double
tmpl_Double_Five_Point_Derivative(double (*f)(double), double x, double h)
{
    /*  The points for the five-point stencil. x2 is just the input x, the    *
     *  center of the stencil. The formula for the numerical first derivative *
     *  does not need x2 nor f(x2), so we can skip this computation.          */
    const double x0 = x - 2.0*h;
    const double x1 = x - 1.0*h;
    const double x3 = x + 1.0*h;
    const double x4 = x + 2.0*h;

    /*  The evaluation of the function at the points of the stencil. As       *
     *  mentioned in the previous comment, the center of the stencil cancels  *
     *  in the formula for the first derivative. We do not need y2.           */
    const double y0 = f(x0);
    const double y1 = f(x1);
    const double y3 = f(x3);
    const double y4 = f(x4);

    /*  The numerator is the weighted sum of the evaluation of the stencil    *
     *  points. These weights can be derived using Lagrange interpolation.    */
    const double num = y0 - 8.0*y1 + 8.0*y3 - y4;

    /*  The denominator is proportional to the step size.                     */
    const double den = 12.0 * h;
    return num / den;
}
/*  End of tmpl_Double_Five_Point_Derivative.                                 */
