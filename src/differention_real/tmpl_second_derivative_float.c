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
 *                        tmpl_second_derivative_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a five-point stencil.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Second_Derivative                                          *
 *  Purpose:                                                                  *
 *      Numerically computes the second derivative of a function.             *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in a float and returns a float.             *
 *      x (float):                                                            *
 *          The point where f'' is to be computed.                            *
 *  Output:                                                                   *
 *      f_double_prime (float):                                               *
 *          The numerical second derivative f''(x).                           *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Abs:                                                   *
 *              Computes the absolute value of a number.                      *
 *      tmpl_differentiation_real.h:                                          *
 *          tmpl_Float_Five_Point_Second_Derivative:                          *
 *              Computes the second derivative using a five-point stencil.    *
 *  Method:                                                                   *
 *      Use a five-point stencil to numerically compute the second derivative.*
 *      The step size h is chosen to be qurt(epsilon) * |x| for |x| > 1, and  *
 *      qurt(epsilon) for smaller values. The theoretical error is O(h^4).    *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *      2.) Press, Teukolsky, Vetterling, Flannery, 1986                      *
 *          Numerical Recipes                                                 *
 *              Chapter 5, Section 7.                                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_differentiation_real.h:                                          *
 *          Header file containing the function prototype.                    *
 *  2.) tmpl_float.h:                                                         *
 *          Header file providing details about machine epsilon.              *
 *  3.) tmpl_math.h:                                                          *
 *          Header file where the absolute value function is declared.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2024                                              *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_differentiation_real.h>

/*  Macros for machine epsilon are provided here.                             */
#include <libtmpl/include/tmpl_float.h>

/*  Absolute value function given here.                                       */
#include <libtmpl/include/tmpl_math.h>

/*  Computes the numerical second derivative using a five point stencil.      */
float tmpl_Float_Second_Derivative(float (*f)(float), float x)
{
    /*  The step size is given by machine precision and the size of the input.*/
    const float abs_x = tmpl_Float_Abs(x);
    const float eps = TMPL_QURT_FLT_EPS;
    const float h = (abs_x > 1.0F ? abs_x * eps : eps);

    /*  The bulk of the work is done by the five-point stencil function.      */
    return tmpl_Float_Five_Point_Second_Derivative(f, x, h);
}
/*  End of tmpl_Float_Derivative.                                             */
