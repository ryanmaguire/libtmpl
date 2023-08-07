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
 *                            tmpl_sorted_interp1d                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for linear interpolation of sorted data.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sorted_Interp1d                                           *
 *  Purpose:                                                                  *
 *      Linearly interpolates a sorted data set against another data set.     *
 *  Arguments:                                                                *
 *      x (const double *):                                                   *
 *          A sorted array of real numbers that are monotonically increasing. *
 *      y (const double *):                                                   *
 *          The data points corresponding to x.                               *
 *      len (size_t):                                                         *
 *          The number of elements of x and y.                                *
 *      x_new (const double *):                                               *
 *          The new data points. Assumed sorted in increasing order.          *
 *      y_new (double *):                                                     *
 *          The interpolated data corresponding to x_new, to be computed.     *
 *      len_new (size_t):                                                     *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Method:                                                                   *
 *      Find the least value x[n] such x_new[m] < x[n] and then perform a     *
 *      linear interpolation with x[n-1] and x[n] via the formula:            *
 *                                                                            *
 *                               y[n] - y[n-1]                                *
 *          y_new[m] = y[n-1] + --------------- * (x_new[m] - x[n-1])         *
 *                               x[n] - x[n-1]                                *
 *                                                                            *
 *  Notes:                                                                    *
 *      1.) Both x and x_new are assumed to be sorted in increasing order.    *
 *                                                                            *
 *      2.) For values x_new[m] < x[0], this function sets y_new[m] = y[0].   *
 *          Similarly for values x_new[m] > x[len-1] the set value is         *
 *          y_new[m] = y[len-1]. No extrapolating is done.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library header file where size_t is given.               *
 *  2.) tmpl_interpolate.h:                                                   *
 *          Header where the functions prototype is defined.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 30, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/03: Ryan Maguire                                                  *
 *      Added checks for NULL pointers. Changed behavior to mimic numpy a bit.*
 *      For values of x_new[m] that are less than x[0], y_new[m] = y[0] will  *
 *      be set, and for values x_new[m] that are greater than x[len-1],       *
 *      y_new[m] = y[len-1] is set. No extrapolation is done.                 *
 ******************************************************************************/

/*  size_t data type found here.                                              */
#include <stddef.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_interpolate.h>

/*  Double precision linear interpolation of sorted data.                     */
void
tmpl_Double_Sorted_Interp1d(const double *x, const double *y, size_t len,
                            const double *x_new, double *y_new, size_t len_new)
{
    /*  Constant for zero of type "size_t".                                   */
    const size_t zero = (size_t)0;

    /*  Declare two variables for indexing the interpolated and raw data.     */
    size_t m;
    size_t n = zero;

    /*  And declare a variable for computing the slope for the interpolation. */
    double slope = (y[1] - y[0]) / (x[1] - x[0]);

    /*  Check for NULL pointers, aborting if there is one.                    */
    if (!x || !y || !x_new || !y_new || len == zero || len_new == zero)
        return;

    /*  Loop over the entries of the interpolating arrays and compute.        */
    for (m = zero; m < len_new; ++m)
    {
        /*  For values with x-values less than x[0], set the data to y[0].    */
        if (x_new[m] <= x[0])
            y_new[m] = y[0];

        /*  Similarly for x-values above x[len-1], set the data to y[len-1].  */
        else if (x_new[m] >= x[len - (size_t)1])
            y_new[m] = y[len - (size_t)1];

        /*  And finally, handle the general case.                             */
        else
        {
            /*  Check if we need to increment the raw data index.             */
            if (x[n] <= x_new[m])
            {
                /*  Find the smallest index n such that x[n] > x_new[m].      */
                do {
                    n++;
                } while (x[n] <= x_new[m]);

                /*  Set the slope corresponding to this index.                */
                slope = (y[n] - y[n-1]) / (x[n] - x[n-1]);
            }

            /*  Use this index to compute the linear interpolation.           */
            y_new[m] = y[n-1] + slope * (x_new[m] - x[n-1]);
        }
    }
    /*  End of for loop computing y_new[m].                                   */
}
/*  End of tmpl_Double_Sorted_Interp1d.                                       */
