/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                         tmpl_differentiation_real                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for numerical differentiation of real-valued functions.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 08, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/01/19: Ryan Maguire                                                  *
 *      Changed name from "numerical" to "differentiation_real". Moved        *
 *      complex-valued functions to their own folder.                         *
 ******************************************************************************/

/*  Include guard for this file to prevent including this twice.              */
#ifndef TMPL_DIFFERENTIATION_REAL_H
#define TMPL_DIFFERENTIATION_REAL_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Derivative                                                *
 *  Purpose:                                                                  *
 *      Numerically computes derivatives using a five point stencil.          *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the derivative is to be computed.                 *
 *  Output:                                                                   *
 *      f_prime (double):                                                     *
 *          The derivative f'(x).                                             *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          This function uses the five-point stencil method. The step-size   *
 *          is chosen to be sqrt(epsilon) * |x| for inputs with |x| > 1, and  *
 *          sqrt(epsilon) for smaller inputs.                                 *
 *      2.)                                                                   *
 *          This function simplifies the calling syntax by chosing a          *
 *          step-size for the user. If you'd like to use your own step-size,  *
 *          experiment with the stencil methods provided by this header file. *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_derivative_double.c                                          *
 *          tmpl_derivative_float.c                                           *
 *          tmpl_derivative_ldouble.c                                         *
 ******************************************************************************/
extern float tmpl_Float_Derivative(float (*f)(float), float x);
extern double tmpl_Double_Derivative(double (*f)(double), double x);

extern long double
tmpl_LDouble_Derivative(long double (*f)(long double), long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Second_Derivative                                         *
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a five point stencil.   *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the second derivative is to be computed.          *
 *  Output:                                                                   *
 *      f_double_prime (double):                                              *
 *          The derivative f''(x).                                            *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          This function uses the five-point stencil method. The step-size   *
 *          is chosen to be qurt(epsilon) * |x| for inputs with |x| > 1, and  *
 *          qurt(epsilon) for smaller inputs.                                 *
 *      2.)                                                                   *
 *          This function simplifies the calling syntax by chosing a          *
 *          step-size for the user. If you'd like to use your own step-size,  *
 *          experiment with the stencil methods provided by this header file. *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_second_derivative_double.c                                   *
 *          tmpl_second_derivative_float.c                                    *
 *          tmpl_second_derivative_ldouble.c                                  *
 ******************************************************************************/
extern float tmpl_Float_Second_Derivative(float (*f)(float), float x);
extern double tmpl_Double_Second_Derivative(double (*f)(double), double x);

extern long double
tmpl_LDouble_Second_Derivative(long double (*f)(long double), long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Five_Point_Derivative                                     *
 *  Purpose:                                                                  *
 *      Numerically computes derivatives using a five point stencil.          *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the derivative is to be computed.                 *
 *      h (double):                                                           *
 *          Step size for the numerical derivative.                           *
 *  Output:                                                                   *
 *      f_prime (double):                                                     *
 *          The derivative f'(x).                                             *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires four calls to the input function. If the   *
 *          evaluation of this function is expensive, it may be advisable to  *
 *          use symmetric or secant derivatives (two function calls).         *
 *      3.)                                                                   *
 *          Float and long double equivalents are provided as well.           *
 *      4.)                                                                   *
 *          No checks are made for NaN or infinite inputs.                    *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_five_point_derivative_double.c                               *
 *          tmpl_five_point_derivative_float.c                                *
 *          tmpl_five_point_derivative_ldouble.c                              *
 ******************************************************************************/
extern float
tmpl_Float_Five_Point_Derivative(float (*f)(float), float x, float h);

extern double
tmpl_Double_Five_Point_Derivative(double (*f)(double), double x, double h);

extern long double
tmpl_LDouble_Five_Point_Derivative(long double (*f)(long double),
                                   long double x, long double h);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Five_Point_Second_Derivative                              *
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a five point stencil.   *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the second derivative is to be computed.          *
 *      h (double):                                                           *
 *          Step size for the numerical derivative.                           *
 *  Output:                                                                   *
 *      f_double_prime (double):                                              *
 *          The derivative f''(x).                                            *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires four calls to the input function. If the   *
 *          evaluation of this function is expensive, it may be advisable to  *
 *          use symmetric or secant derivatives (two function calls).         *
 *      3.)                                                                   *
 *          Float and long double equivalents are provided as well.           *
 *      4.)                                                                   *
 *          No checks are made for NaN or infinite inputs.                    *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_five_point_derivative_double.c                               *
 *          tmpl_five_point_derivative_float.c                                *
 *          tmpl_five_point_derivative_ldouble.c                              *
 ******************************************************************************/
extern float
tmpl_Float_Five_Point_Second_Derivative(float (*f)(float), float x, float h);

extern double
tmpl_Double_Five_Point_Second_Derivative(double (*f)(double),
                                         double x, double h);

extern long double
tmpl_LDouble_Five_Point_Second_Derivative(long double (*f)(long double),
                                          long double x, long double h);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Symmetric_Derivative                                      *
 *  Purpose:                                                                  *
 *      Numerically computes derivatives using a symmetric difference.        *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the derivative is to be computed.                 *
 *      h (double):                                                           *
 *          Step size for the numerical derivative.                           *
 *  Output:                                                                   *
 *      f_prime (double):                                                     *
 *          The derivative f'(x).                                             *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires two calls to the input function. It is     *
 *          hence faster than the higher-order stencil methods, but has worse *
 *          error. The error goes like O(h^2).                                *
 *      3.)                                                                   *
 *          Float and long double equivalents are provided as well.           *
 *      4.)                                                                   *
 *          No checks are made for NaN or infinite inputs.                    *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_symmetric_derivative_double.c                                *
 *          tmpl_symmetric_derivative_float.c                                 *
 *          tmpl_symmetric_derivative_ldouble.c                               *
 ******************************************************************************/
extern float
tmpl_Float_Symmetric_Derivative(float (*f)(float), float x, float h);

extern double
tmpl_Double_Symmetric_Derivative(double (*f)(double), double x, double h);

extern long double
tmpl_LDouble_Symmetric_Derivative(long double (*f)(long double),
                                  long double x, long double h);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Symmetric_Second_Derivative                               *
 *  Purpose:                                                                  *
 *      Numerically computes second derivatives using a symmetric difference. *
 *  Arguments:                                                                *
 *      f (function):                                                         *
 *          A function that takes in and returns a double.                    *
 *      x (double):                                                           *
 *          The point where the second derivative is to be computed.          *
 *      h (double):                                                           *
 *          Step size for the numerical derivative.                           *
 *  Output:                                                                   *
 *      f_double_prime (double):                                              *
 *          The second derivative f''(x).                                     *
 *  Notes:                                                                    *
 *      1.)                                                                   *
 *          Floating-point round-off will cause the error in the derivative   *
 *          to become very large for small values of h. Because of this it is *
 *          advised to use an h value that is not too big, but not too small. *
 *          A good choice is sqrt(epsilon) * |f(x)| where epsilon is the      *
 *          precision of double (~10^-16 for 64-bit double).                  *
 *      2.)                                                                   *
 *          The algorithm requires two calls to the input function. It is     *
 *          hence faster than the higher-order stencil methods, but has worse *
 *          error. The error goes like O(h).                                  *
 *      3.)                                                                   *
 *          Float and long double equivalents are provided as well.           *
 *      4.)                                                                   *
 *          No checks are made for NaN or infinite inputs.                    *
 *  References:                                                               *
 *      1.) Ambramowitz, Stegun, 1970                                         *
 *          Handbook of Mathematical Functions                                *
 *              Chapter 25, Section 3.                                        *
 *  Source:                                                                   *
 *      libtmpl/src/numerical_real/                                           *
 *          tmpl_symmetric_second_derivative_double.c                         *
 *          tmpl_symmetric_second_derivative_float.c                          *
 *          tmpl_symmetric_second_derivative_ldouble.c                        *
 ******************************************************************************/
extern float
tmpl_Float_Symmetric_Second_Derivative(float (*f)(float), float x, float h);

extern double
tmpl_Double_Symmetric_Second_Derivative(double (*f)(double),
                                        double x, double h);

extern long double
tmpl_LDouble_Symmetric_Second_Derivative(long double (*f)(long double),
                                         long double x, long double h);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
