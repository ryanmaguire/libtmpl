/******************************************************************************
 *                                 LICENSE                                    *
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
 *                             tmpl_interpolate                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide routines for interpolating data.                              *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       December 30, 2020                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_INTERPOLATE_H__
#define __TMPL_INTERPOLATE_H__

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sorted_Interp1d                                           *
 *  Purpose:                                                                  *
 *      Interpolate values of (x, y) to (x_new, y_new).                       *
 *  Arguments:                                                                *
 *      x (double *):                                                         *
 *          A sorted array of real numbers that are strictly                  *
 *          monotonically increasing.                                         *
 *      y (double *):                                                         *
 *          The data points corresponding to x.                               *
 *      N (unsigned long):                                                    *
 *          The number of elements of x and y.                                *
 *      x_new (double *):                                                     *
 *          The new data points. Must lie between min(x) and max(x).          *
 *      y_new (double *):                                                     *
 *          The interpolated data corresponding to x_new.                     *
 *      N_new (unsigned long):                                                *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  NOTES:                                                                    *
 *      It is assumed the pointer x has it's data sorted and strictly         *
 *      monotonically increasing. That is, x[n] < x[n+1] for all valid n.     *
 ******************************************************************************/
extern void
tmpl_Float_Sorted_Interp1d(float *x, float *y, unsigned long N,
                           float *x_new, float *y_new, unsigned long N_new);

extern void
tmpl_Double_Sorted_Interp1d(double *x, double *y, unsigned long N,
                            double *x_new, double *y_new, unsigned long N_new);

extern void
tmpl_LDouble_Sorted_Interp1d(long double *x, long double *y, unsigned long N,
                             long double *x_new, long double *y_new,
                             unsigned long N_new);

#endif
/*  End of include guard.                                                     */

