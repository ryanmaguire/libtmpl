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
 *                    tmpl_sorted_linear_interp1d_ldouble                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for linear interpolation of sorted data.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sorted_Linear_Interp1d                                   *
 *  Purpose:                                                                  *
 *      Linearly interpolates a sorted data set against another data set.     *
 *  Arguments:                                                                *
 *      x (const long double * const):                                        *
 *          A sorted array of real numbers that are monotonically increasing. *
 *      y (const long double * const):                                        *
 *          The data points corresponding to x.                               *
 *      len (const size_t):                                                   *
 *          The number of elements of x and y.                                *
 *      x_new (const long double * const):                                    *
 *          The new data points. Assumed sorted in increasing order.          *
 *      y_new (long double * const):                                          *
 *          The interpolated data corresponding to x_new, to be computed.     *
 *      len_new (const size_t):                                               *
 *          The number of elements of x_new and y_new.                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Find the least value x[n] such x_new[m] < x[n] and then perform a     *
 *      linear interpolation with x[n - 1] and x[n] via the formula:          *
 *                                                                            *
 *                                y[n] - y[n - 1]                             *
 *          y_new[m] = y[n - 1] + --------------- * (x_new[m] - x[n - 1])     *
 *                                x[n] - x[n - 1]                             *
 *                                                                            *
 *      For points with x_new[m] <= x[0], we set y_new[m] = y[0], and for     *
 *      points x_new[m] >= x[len - 1], we set y_new[m] = y[len - 1]. That is, *
 *      we clamp the data rather than extrapolate.                            *
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
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard library header file where size_t is given.               *
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
 *  2026/02/13: Ryan Maguire                                                  *
 *      Fixed error checks, allowed len to be one, added const qualifier.     *
 ******************************************************************************/

/*  size_t data type found here.                                              */
#include <stddef.h>

/*  Function prototype / forward declaration.                                 */
extern void
tmpl_LDouble_Sorted_Linear_Interp1d(const long double * const x,
                                    const long double * const y,
                                    const size_t len,
                                    const long double * const x_new,
                                    long double * const y_new,
                                    const size_t len_new);

/*  Long double precision linear interpolation of sorted data.                */
void
tmpl_LDouble_Sorted_Linear_Interp1d(const long double * const x,
                                    const long double * const y,
                                    const size_t len,
                                    const long double * const x_new,
                                    long double * const y_new,
                                    const size_t len_new)
{
    /*  Declare two variables for indexing the interpolated and raw data.     */
    size_t m;
    size_t n = 1;

    /*  And declare a variable for computing the slope for the interpolation. */
    long double slope;

    /*  Check for NULL pointers, aborting if there is one.                    */
    if (!x || !y || !x_new || !y_new || len_new == 0)
        return;

    /*  The input data set needs at least two points to compute the slope.    */
    if (len < 2)
    {
        /*  If there are no points in the x and y arrays, nothing can be done.*/
        if (len == 0)
            return;

        /*  With a single data point, all we can do is set the new data equal *
         *  to this value. Perform this copy.                                 */
        for (m = 0; m < len_new; ++m)
            y_new[m] = y[0];

        return;
    }

    /*  Compute the initial slope for the start of the interpolation scheme.  */
    slope = (y[1] - y[0]) / (x[1] - x[0]);

    /*  Loop over the entries of the interpolating arrays and compute.        */
    for (m = 0; m < len_new; ++m)
    {
        /*  For values with x-values less than x[0], set the data to y[0].    */
        if (x_new[m] <= x[0])
            y_new[m] = y[0];

        /*  Similarly for x-values above x[len-1], set the data to y[len-1].  */
        else if (x_new[m] >= x[len - 1])
            y_new[m] = y[len - 1];

        /*  And finally, handle the general case.                             */
        else
        {
            /*  Check if we need to increment the raw data index.             */
            if (x[n] <= x_new[m])
            {
                /*  Find the smallest index n such that x[n] > x_new[m].      */
                do {
                    ++n;
                } while (x[n] <= x_new[m]);

                /*  Set the slope corresponding to this index.                */
                slope = (y[n] - y[n - 1]) / (x[n] - x[n - 1]);
            }

            /*  Use this index to compute the linear interpolation.           */
            y_new[m] = y[n - 1] + slope * (x_new[m] - x[n - 1]);
        }
    }
    /*  End of for loop computing y_new[m].                                   */
}
/*  End of tmpl_LDouble_Sorted_Linear_Interp1d.                               */
