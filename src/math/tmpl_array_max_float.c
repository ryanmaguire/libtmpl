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

/*  Function for finding the maximum of a float array.                        */
float tmpl_Float_Array_Max(float *arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    float max;

    /*  If the array is NULL or empty, the result is undefined. Return NaN.   */
    if (!arr || !len)
        return TMPL_NANF;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    n = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    do {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return NaN.            */
        if (n == len)
            return TMPL_NANF;

        max = arr[n];
        ++n;
    } while (tmpl_Float_Is_NaN(max));

    /*  Loop through the remaining elements and find the maximum.             */
    for (; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the max value.     */
        if (arr[n] > max)
            max = arr[n];
    }

    return max;
}
/*  End of tmpl_Float_Array_Max.                                              */
