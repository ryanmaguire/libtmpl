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
 *      tmpl_Double_Legendre                                                  *
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
extern void tmpl_Float_Legendre(float * const evals, float x, size_t order);
extern void tmpl_Double_Legendre(double * const evals, double x, size_t order);

extern void
tmpl_LDouble_Legendre(long double * const evals, long double x, size_t order);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Modified_Legendre                                         *
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
tmpl_Float_Modified_Legendre(float * const evals, float x, size_t order);

extern void
tmpl_Double_Modified_Legendre(double * const evals, double x, size_t order);

extern void
tmpl_LDouble_Modified_Legendre(long double * const evals,
                               long double x, size_t order);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Modified_Legendre_Precompute                              *
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
tmpl_Float_Modified_Legendre_Precompute(
    float * TMPL_RESTRICT const evals,
    const float * TMPL_RESTRICT const legendre,
    size_t order
);

extern void
tmpl_Double_Modified_Legendre_Precompute(
    double * TMPL_RESTRICT const evals,
    const double * TMPL_RESTRICT const legendre,
    size_t order
);

extern void
tmpl_LDouble_Modified_Legendre_Precompute(
    long double * TMPL_RESTRICT const evals,
    const long double * TMPL_RESTRICT const legendre,
    size_t order
);

#endif
/*  End of include guard.                                                     */
