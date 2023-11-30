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
 *                       tmpl_array_minmax_index_float                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the indices of the min and max of a float array.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Array_MinMax_Index                                         *
 *  Purpose:                                                                  *
 *      Computes the indices of min(arr) and max(arr).                        *
 *  Arguments:                                                                *
 *      arr (float *):                                                        *
 *          An array of floats.                                               *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *      minind (size_t *):                                                    *
 *          A pointer to a size_t. The index of the min of the array.         *
 *      maxind (size_t *):                                                    *
 *          A pointer to a size_t. The index of the min of the array.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_Float_Is_NaN (tmpl_math.h):                                      *
 *          Determines if a float is Not-a-Number.                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          size_t found here.                                                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 13, 2022                                             *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for finding the indices of the min and max of a float array.     */
void
tmpl_Float_Array_MinMax_Index(float *arr, size_t len,
                              size_t *minind, size_t *maxind)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  If the array is NULL or empty, the result is undefined. Similarly if  *
     *  either or the max or min pointers or NULL. Simply return to caller.   */
    if (!arr || !len || !maxind || !minind)
        return;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    n = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    while (tmpl_Float_Is_NaN(arr[n]))
    {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return NaN.            */
        if (n == len)
        {
            *minind = (size_t)0;
            *maxind = (size_t)0;
            return;
        }

        ++n;
    }

    /*  n is the index of the first non-NaN in the array. Start here.         */
    *minind = n;
    *maxind = n;

    /*  Loop through the remaining elements and find the min and max.         */
    for (; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < arr[*minind])
            *minind = n;

        /*  Similarly, if this element is larger reset the max value.         */
        if (arr[n] > arr[*maxind])
            *maxind = n;
    }

    return;
}
/*  End of tmpl_Float_Array_MinMax_Index.                                     */
