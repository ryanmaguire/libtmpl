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
#include <libtmpl/include/tmpl_integer.h>

/*  Function for finding the maximum of an unsigned int array.                */
unsigned int tmpl_UInt_Array_Max(unsigned int *arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    unsigned int max;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len)
        return 0U;

    /*  Initialize the max variable to the first element.                     */
    max = arr[0];

    /*  Loop through the remaining elements and find the maximum.             */
    for (n = 1; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the max value.     */
        if (arr[n] > max)
            max = arr[n];
    }

    return max;
}
/*  End of tmpl_UInt_Array_Max.                                               */
