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
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stdlib.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for finding the min and max of a double array.                   */
void tmpl_Double_Array_MinMax(double *arr, size_t len, double *min, double *max)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double start;

    /*  If the array is NULL or empty, the result is undefined. Similarly if  *
     *  either or the max or min pointers or NULL. Simply return to caller.   */
    if (!arr || !len || !max || !min)
        return;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    n = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    do {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return NaN.            */
        if (n == len)
        {
            *min = TMPL_NAN;
            *max = *min;
            return;
        }

        start = arr[n];
        ++n;
    } while (tmpl_Double_Is_NaN(start));

    /*  start is the first non-NaN in the array. Set min and max to this.     */
    *min = start;
    *max = start;

    /*  Loop through the remaining elements and find the min and max.         */
    for (; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < *min)
            *min = arr[n];

        /*  Similarly, if this element is larger reset the max value.         */
        if (arr[n] > *max)
            *max = arr[n];
    }

    return;
}
/*  End of tmpl_Double_Array_MinMax.                                          */
