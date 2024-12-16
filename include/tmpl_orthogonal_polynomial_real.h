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
 *                      tmpl_orthogonal_polynomial_real                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide functions for working with common families of orthogonal      *
 *      polynomials, such as the Legendre polynomials, or the Chebyshev ones. *
 *      Some of these were originally grouped together with the functions     *
 *      found in special_functions_real, but have been reorganized into their *
 *      own directory.                                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard C library file with the size_t typedef.                  *
 *  3.) tmpl_config.h:                                                        *
 *          Header file containing the helper macros like TMPL_RESTRICT.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 11, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/12/11: Ryan Maguire                                                  *
 *      Moved Legendre polynomials from special_functions_real to here.       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ORTHOGONAL_POLYNOMIAL_REAL_H
#define TMPL_ORTHOGONAL_POLYNOMIAL_REAL_H

/*  Header file providing TMPL_RESTRICT and other helper macros.              */
#include <libtmpl/include/tmpl_config.h>

/*  Standard library header file providing the size_t data type.              */
#include <stddef.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Chebyshev_T                                               *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Chebyshev T polynomials at the input.    *
 *      These are also called the Chebyshev polynomials of the first kind.    *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value T_n(x).                              *
 *      x (double):                                                           *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, x can    *
 *          technically be any real number.                                   *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 ******************************************************************************/
extern void
tmpl_Float_Chebyshev_T(float * const evals, float x, size_t length);

extern void
tmpl_Double_Chebyshev_T(double * const evals, double x, size_t length);

extern void
tmpl_LDouble_Chebyshev_T(long double * const evals,
                         long double x, size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Chebyshev_U                                               *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Chebyshev U polynomials at the input.    *
 *      These are also called the Chebyshev polynomials of the second kind.   *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value U_n(x).                              *
 *      x (double):                                                           *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, x can    *
 *          technically be any real number.                                   *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 ******************************************************************************/
extern void
tmpl_Float_Chebyshev_U(float * const evals, float x, size_t length);

extern void
tmpl_Double_Chebyshev_U(double * const evals, double x, size_t length);

extern void
tmpl_LDouble_Chebyshev_U(long double * const evals,
                         long double x, size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fresnel_Legendre_L                                        *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Fresnel-Legendre polynomials at the      *
 *      input.                                                                *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value L_n(alpha, beta).                    *
 *      alpha (double):                                                       *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, alpha    *
 *          can technically be any real number.                               *
 *      beta (double):                                                        *
 *          A real number, the second parameter for L_n(alpha, beta).         *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 ******************************************************************************/
extern void
tmpl_Float_Fresnel_Legendre_L(float * const evals,
                              float alpha,
                              float beta,
                              size_t length);

extern void
tmpl_Double_Fresnel_Legendre_L(double * const evals,
                               double alpha,
                               double beta,
                               size_t length);

extern void
tmpl_LDouble_Fresnel_Legendre_L(long double * const evals,
                                long double alpha,
                                long double beta,
                                size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Legendre_P                                                *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Legendre polynomials at the input.       *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value P_n(x).                              *
 *      x (double):                                                           *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, x can    *
 *          technically be any real number.                                   *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 ******************************************************************************/
extern void
tmpl_Float_Legendre_P(float * const evals, float x, size_t length);

extern void
tmpl_Double_Legendre_P(double * const evals, double x, size_t length);

extern void
tmpl_LDouble_Legendre_P(long double * const evals,
                        long double x, size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Modified_Legendre_P                                       *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Modified Legendre polynomials.           *
 *  Arguments:                                                                *
 *      evals (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value P_n(x) - xP_{n+1}(x).                *
 *      x (double):                                                           *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, x can    *
 *          technically be any real number.                                   *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 ******************************************************************************/
extern void
tmpl_Float_Modified_Legendre_P(float * const evals, float x, size_t order);

extern void
tmpl_Double_Modified_Legendre_P(double * const evals, double x, size_t order);

extern void
tmpl_LDouble_Modified_Legendre_P(long double * const evals,
                                 long double x, size_t order);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Modified_Legendre_P_Precompute                            *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Modified Legendre polynomials, given     *
 *      that the Legendre polynomials have already been precomputed.          *
 *  Arguments:                                                                *
 *      evals (double * TMPL_RESTRICT const):                                 *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will store the value P_n(x) - xP_{n+1}(x).                *
 *      legendre (const double * TMPL_RESTRICT const):                        *
 *          The Legendre polynomial evaluated at x, P_n(x).                   *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) evals must have "length" elements allocated to it.                *
 *      3.) legendre must have "length + 1" elements allocated to it, and the *
 *          values must be initialized to the Legendre polynomials.           *
 *      4.) On compilers supporting the restrict keyword (C99 or higher),     *
 *          TMPL_RESTRICT expands to restrict. To properly use this function, *
 *          the evals and legendre coefficients should be different. If you   *
 *          only want the modified Legendre polynomials, and do not care      *
 *          P_n(x), use tmpl_Double_Modified_Legendre instead.                *
 ******************************************************************************/
extern void
tmpl_Float_Modified_Legendre_P_Precompute(
    float * TMPL_RESTRICT const evals,
    const float * TMPL_RESTRICT const legendre,
    size_t order
);

extern void
tmpl_Double_Modified_Legendre_P_Precompute(
    double * TMPL_RESTRICT const evals,
    const double * TMPL_RESTRICT const legendre,
    size_t order
);

extern void
tmpl_LDouble_Modified_Legendre_P_Precompute(
    long double * TMPL_RESTRICT const evals,
    const long double * TMPL_RESTRICT const legendre,
    size_t order
);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Split_Fresnel_Legendre_L                                  *
 *  Purpose:                                                                  *
 *      Evaluates the first "length" Fresnel-Legendre polynomials at the      *
 *      input, splitting the result into two parts.                           *
 *  Arguments:                                                                *
 *      left (double * const):                                                *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will contain (P_n(alpha) - alpha P_{n+1}(alpha))/(n + 2). *
 *      right (double * const):                                               *
 *          An array of real numbers, the output of the function. The nth     *
 *          element will contain U_{n+2}(alpha) - 2 P_{n+2}(alpha).           *
 *      alpha (double):                                                       *
 *          A real number. For most uses, this should be between -1 and 1.    *
 *          This is the domain for the Legendre polynomial. However, alpha    *
 *          can technically be any real number.                               *
 *      length (size_t):                                                      *
 *          The number of elements in the evals array.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Float and long double equivalents are provided as well.           *
 *      2.) left and right must have "length" elements allocated to it.       *
 ******************************************************************************/
extern void
tmpl_Float_Split_Fresnel_Legendre_L(float * const left,
                                    float * const right,
                                    float alpha,
                                    size_t length);

extern void
tmpl_Double_Split_Fresnel_Legendre_L(double * const left,
                                     double * const right,
                                     double alpha,
                                     size_t length);

extern void
tmpl_LDouble_Split_Fresnel_Legendre_L(long double * const left,
                                      long double * const right,
                                      long double alpha,
                                      size_t length);

#endif
/*  End of include guard.                                                     */
