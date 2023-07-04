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
 *                              tmpl_interpolate                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for interpolating data.                              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 30, 2020                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INTERPOLATE_H
#define TMPL_INTERPOLATE_H

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sorted_Interp1d                                           *
 *  Purpose:                                                                  *
 *      Interpolate values of (x, y) to (x_new, y_new).                       *
 *  Arguments:                                                                *
 *      x (const double *):                                                   *
 *          A sorted array of real numbers that are monotonically increasing. *
 *      y (const double *):                                                   *
 *          The data points corresponding to x.                               *
 *      len (size_t):                                                         *
 *          The number of elements of x and y.                                *
 *      x_new (const double *):                                               *
 *          The new data points, sorted in increasing order.                  *
 *      y_new (double *):                                                     *
 *          The interpolated data corresponding to x_new.                     *
 *      len_new (size_t):                                                     *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Both x and x_new are assumed to be sorted in increasing order.    *
 *                                                                            *
 *      2.) For values x_new[m] < x[0], this function sets y_new[m] = y[0].   *
 *          Similarly for values x_new[m] > x[len-1] the set value is         *
 *          y_new[m] = y[len-1]. No extrapolating is done.                    *
 ******************************************************************************/
TMPL_EXPORT extern void
tmpl_Float_Sorted_Interp1d(const float *x,
                           const float *y,
                           size_t len,
                           const float *x_new,
                           float *y_new,
                           size_t len_new);

TMPL_EXPORT extern void
tmpl_Double_Sorted_Interp1d(const double *x,
                            const double *y,
                            size_t len,
                            const double *x_new,
                            double *y_new,
                            size_t len_new);

TMPL_EXPORT extern void
tmpl_LDouble_Sorted_Interp1d(const long double *x,
                             const long double *y,
                             size_t len,
                             const long double *x_new,
                             long double *y_new,
                             size_t len_new);

#endif
/*  End of include guard.                                                     */
