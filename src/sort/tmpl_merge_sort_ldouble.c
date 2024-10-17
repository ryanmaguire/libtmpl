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

/*  malloc and size_t found here.                                             */
#include <stdlib.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_sort.h>

/*  Iterative merge-sort algorithm for an array arr of length len.            */
int tmpl_LDouble_Merge_Sort(long double *arr, size_t len)
{
    /*  Declare all necessary variables.                                      */
    size_t width, left, right, end, ind, k, m, n;

    /*  Temporary array used in the merge sort algorithm. malloc'd later.     */
    long double *unsorted;

    /*  If the input array is NULL, abort the algorithm. Nothing to sort.     */
    if (!arr)
        return 0;

    /*  Allocate memory for the tempory array. We'll copy the input into this.*/
    unsorted = malloc(sizeof(*unsorted) * len);

    /*  Check if malloc failed. Return 0 to the caller indicating error.      */
    if (unsorted == NULL)
        return 0;

    /*  Set unsorted to the same values as arr.                               */
    for (ind = 0; ind < len; ++ind)
        unsorted[ind] = arr[ind];

    /*  We're splitting the array into smaller powers of two. This iterative  *
     *  scheme is equivalent to the recursive one.                            */
    for (width = 1; width < len; width = 2 * width)
    {
        for (left = 0; left < len; left = left + 2 * width)
        {
            /*  Ensure that right hasn't gone beyond the size of the array.   *
             *  This can happen if the array size isn't a power of two.       */
            if ((left + width) < len)
                right = left + width;
            else
                right = len;

            /*  Similarly, ensure that end isn't beyond the array size.       */
            if (left + 2*width < len)
                end = left + 2*width;
            else
                end = len;

            /*  Sort the current window we're looking at.                     */
            m = left;
            n = right;

            /*  Loop over all of the values in the window we're merging.      */
            for (k = left; k < end; ++k)
            {
                if ((m < right) && ((n >= end) || (arr[m] <= arr[n])))
                {
                    unsorted[k] = arr[m];
                    ++m;
                }
                else
                {
                    unsorted[k] = arr[n];
                    ++n;
                }
            }
        }

        /*  Merge sorted the sorted data into unsorted. Copy this into sorted.*/
        for (ind = 0; ind < len; ++ind)
            arr[ind] = unsorted[ind];
    }

    /*  Free the malloc'd pointer unsorted and return sorted.                 */
    free(unsorted);
    return 1;
}
/*  End of tmpl_LDouble_Merge_Sort.                                           */
