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
 *                              tmpl_integration                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides routines for numerical integration of data.                  *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *      Standard library header file containing size_t typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 16, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INTEGRATION_H
#define TMPL_INTEGRATION_H

/*  Complex numbers found here.                                               */
#include <libtmpl/include/types/tmpl_complex_double.h>
#include <libtmpl/include/types/tmpl_complex_float.h>
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_CDouble_Filon01_Integrand                                        *
 *  Purpose:                                                                  *
 *      Numerically evaluates f(t) exp(i g(t)) dt across a small bin where    *
 *      f(t) is assumed complex and constant, and g(t) = a t + b.             *
 *  Arguments:                                                                *
 *      value (const tmpl_ComplexDouble):                                     *
 *          The approximate value for the complex function across the bin.    *
 *      g_left (const double):                                                *
 *          The left real value for the phase.                                *
 *      g_right (const double):                                               *
 *          The right real value for the phase.                               *
 *      dx (const double):                                                    *
 *          The width of the bin.                                             *
 *  Output:                                                                   *
 *      integrand (tmpl_ComplexDouble):                                       *
 *          The integral of midpoint(left, right) * exp(i g(x)) across the    *
 *          bin of width "dx", assuming g(x) = ax + b for constants a and b.  *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern tmpl_ComplexDouble
tmpl_CDouble_Filon01_Integrand(const tmpl_ComplexDouble value,
                               const double g_left,
                               const double g_right,
                               const double dx);

extern tmpl_ComplexFloat
tmpl_CFloat_Filon01_Integrand(const tmpl_ComplexFloat value,
                              const float g_left,
                              const float g_right,
                              const float dx);

extern tmpl_ComplexLongDouble
tmpl_CLDouble_Filon01_Integrand(const tmpl_ComplexLongDouble value,
                                const long double g_left,
                                const long double g_right,
                                const long double dx);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Left_Riemann_Sum                                          *
 *  Purpose:                                                                  *
 *      Compute the left-sided Riemann sum of an evenly spaced data set       *
 *  Arguments:                                                                *
 *      const double *arr:                                                    *
 *          An array of real numbers that is to be integrated over.           *
 *      double dx:                                                            *
 *          The spacing between points in the array.                          *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double sum:                                                           *
 *          The left-sided Riemann sum of the data set.                       *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float
tmpl_Float_Left_Riemann_Sum(const float *arr, float dx, size_t len);

extern double
tmpl_Double_Left_Riemann_Sum(const double *arr, double dx, size_t len);

extern long double
tmpl_LDouble_Left_Riemann_Sum(const long double *arr,
                              long double dx, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Right_Riemann_Sum                                         *
 *  Purpose:                                                                  *
 *      Compute the right-sided Riemann sum of an evenly spaced data set.     *
 *  Arguments:                                                                *
 *      const double *arr:                                                    *
 *          An array of real numbers that is to be integrated over.           *
 *      double dx:                                                            *
 *          The spacing between points in the array.                          *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double sum:                                                           *
 *          The right-sided Riemann sum of the data set.                      *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float
tmpl_Float_Right_Riemann_Sum(const float *arr, float dx, size_t len);

extern double
tmpl_Double_Right_Riemann_Sum(const double *arr, double dx, size_t len);

extern long double
tmpl_LDouble_Right_Riemann_Sum(const long double *arr,
                               long double dx, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Trapezoid_Sum                                             *
 *  Purpose:                                                                  *
 *      Compute the trapezoidal sum of a data set that is evenly spaced.      *
 *  Arguments:                                                                *
 *      const double *arr:                                                    *
 *          An array of real numbers that is to be integrated over.           *
 *      double dx:                                                            *
 *          The spacing between points in the array.                          *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double sum:                                                           *
 *          The trapezoid sum of the data set.                                *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/
extern float
tmpl_Float_Trapezoid_Sum(const float *arr, float dx, size_t len);

extern double
tmpl_Double_Trapezoid_Sum(const double *arr, double dx, size_t len);

extern long double
tmpl_LDouble_Trapezoid_Sum(const long double *arr, long double dx, size_t len);

#endif
/*  End of include guard.                                                     */
