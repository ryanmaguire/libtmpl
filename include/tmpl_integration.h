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

/*  size_t typedef provided here.                                             */
#include <stddef.h>

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
