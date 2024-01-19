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
 *                   tmpl_symmetric_second_derivative_float                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a symmetric difference. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Symmetric_Second_Derivative                                *
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
 *      Use the symmetric difference quotient:                                *
 *                                                                            *
 *                    f(x + h) - 2 f(x) + f(x - h)                            *
 *          f''(x) ~= ----------------------------                            *
 *                                h^2                                         *
 *                                                                            *
 *      The error goes like O(h).                                             *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the errors to become very     *
 *          large for small values of h. Because of this it is advised to use *
 *          an h value that is not too big, but not too small. A good choice  *
 *          is sqrt(epsilon) * |f(x)| where epsilon is the precision of       *
 *          float (~10^-7 for 32-bit float).                                  *
 *      2.)                                                                   *
 *          The algorithm requires three calls to the input function. It is   *
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

/*  Computes the numerical second derivative using a symmetric difference.    */
float
tmpl_Float_Symmetric_Second_Derivative(float (*f)(float), float x, float h)
{
    /*  Symmetric difference using three stencil points. The point x1 is      *
     *  equal to x, so we don't need another variable.                        */
    const float x0 = x - h;
    const float x2 = x + h;

    /*  Evaluate the function at the stencil points.                          */
    const float y0 = f(x0);
    const float y1 = f(x);
    const float y2 = f(x2);

    /*  Symmetric stencil has weights 1 and -2 for the second derivative.     */
    const float num = y0 - 2.0F*y1 + y2;

    /*  The denominator is proportional to the square of the step size.       */
    const float den = h * h;
    return num / den;
}
/*  End of tmpl_Float_Symmetric_Second_Derivative.                            */
