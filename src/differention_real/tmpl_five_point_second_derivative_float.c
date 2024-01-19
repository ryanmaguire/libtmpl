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
 *                  tmpl_five_point_second_derivative_float                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a five-point stencil.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Five_Point_Second_Derivative                               *
 *  Purpose:                                                                  *
 *      Numerically computes the second derivative of a function.             *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in a float and returns a float.             *
 *      x (float):                                                            *
 *          The point where f'' is to be computed.                            *
 *      h (float):                                                            *
 *          Step size for the stencil.                                        *
 *  Output:                                                                   *
 *      f_double_prime (float):                                               *
 *          The numerical second derivative f''(x).                           *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a five-point stencil to numerically compute the second derivative.*
 *      Using Taylor series or Lagrange interpolation, one obtains a          *
 *      numerical formula for the second derivative:                          *
 *                                                                            *
 *                    -f(x-2h) + 16 f(x-h) - 30 f(x) + 16 f(x+h) - f(x+2h)    *
 *          f''(x) ~= ----------------------------------------------------    *
 *                                           12 h^2                           *
 *                                                                            *
 *      The error goes like O(h^4).                                           *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off causes error in the second derivative    *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of float (~10^-7 for 32-bit float).                     *
 *      2.)                                                                   *
 *          The algorithm requires five calls to the input function. If the   *
 *          evaluation of this function is expensive it may be advisable to   *
 *          use symmetric second derivatives (three function calls).          *
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

/*  Computes the numerical second derivative using a five point stencil.      */
float
tmpl_Float_Five_Point_Second_Derivative(float (*f)(float), float x, float h)
{
    /*  The points for the five-point stencil. x2 is just the input x.        */
    const float x0 = x - 2.0F*h;
    const float x1 = x - 1.0F*h;
    const float x3 = x + 1.0F*h;
    const float x4 = x + 2.0F*h;

    /*  The evaluation of the function at the points of the stencil           */
    const float y0 = f(x0);
    const float y1 = f(x1);
    const float y2 = f(x);
    const float y3 = f(x3);
    const float y4 = f(x4);

    /*  The numerator is the weighted sum of the evaluation of the stencil    *
     *  points. These weights can be derived using Lagrange interpolation.    */
    const float num = -y0 + 16.0F*y1 - 30.0F*y2 + 16.0F*y3 - y4;

    /*  The denominator is proportional to the square of the step size.       */
    const float den = 12.0F * h * h;
    return num / den;
}
/*  End of tmpl_Float_Five_Point_Second_Derivative.                           */
