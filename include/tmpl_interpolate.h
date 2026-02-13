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
 *      tmpl_Double_Sorted_Linear_Interp1d                                    *
 *  Purpose:                                                                  *
 *      Interpolate values of (x, y) to (x_new, y_new).                       *
 *  Arguments:                                                                *
 *      x (const double * const):                                             *
 *          A sorted array of real numbers that are monotonically increasing. *
 *      y (const double * const):                                             *
 *          The data points corresponding to x.                               *
 *      len (const size_t):                                                   *
 *          The number of elements of x and y.                                *
 *      x_new (const double * const):                                         *
 *          The new data points. Assumed sorted in increasing order.          *
 *      y_new (double * const):                                               *
 *          The interpolated data corresponding to x_new, to be computed.     *
 *      len_new (const size_t):                                               *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      1.) Both x and x_new are assumed to be sorted in increasing order.    *
 *                                                                            *
 *      2.) For values x_new[m] <= x[0], this function sets y_new[m] = y[0].  *
 *          Similarly for values x_new[m] >= x[len - 1] the set value is      *
 *          y_new[m] = y[len - 1]. No extrapolating is done.                  *
 *                                                                            *
 *      3.) If any of the inputs are NULL, or if len_new = 0, nothing is done.*
 *                                                                            *
 *      4.) If len = 1, then we set y_new[m] = y[0] for all m.                *
 ******************************************************************************/
extern void
tmpl_Float_Sorted_Linear_Interp1d(const float * const x,
                                  const float * const y,
                                  const size_t len,
                                  const float * const x_new,
                                  float * const y_new,
                                  const size_t len_new);

extern void
tmpl_Double_Sorted_Linear_Interp1d(const double * const x,
                                   const double * const y,
                                   const size_t len,
                                   const double * const x_new,
                                   double * const y_new,
                                   const size_t len_new);

extern void
tmpl_LDouble_Sorted_Linear_Interp1d(const long double * const x,
                                    const long double * const y,
                                    const size_t len,
                                    const long double * const x_new,
                                    long double * const y_new,
                                    const size_t len_new);

#endif
/*  End of include guard.                                                     */
