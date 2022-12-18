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
 *                        tmpl_array_min_double_index                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the index of the min of a double array.                      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Array_Min_Index                                           *
 *  Purpose:                                                                  *
 *      Computes n such that arr[n] >= arr[m] for all other m. The index of   *
 *      the min value of the array. NaN's are skipped.                        *
 *  Arguments:                                                                *
 *      arr (double *):                                                       *
 *          An array of doubles.                                              *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      ind (size_t):                                                         *
 *          The index of the minimum of arr.                                  *
 *  Called Functions:                                                         *
 *      tmpl_Double_Is_NaN (tmpl_math.h):                                     *
 *          Determines if a double is Not-a-Number.                           *
 *  Method:                                                                   *
 *      Loop through the array to find the first entry that is not NaN.       *
 *      Set ind to this element. Then loop through the rest of the array      *
 *      and compare the elements with arr[ind], resetting ind if necessary.   *
 *  Notes:                                                                    *
 *      If the array consists entirely of NaN's, 0 is returned.               *
 *      Similarly if the array is NULL or empty (len = 0).                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          size_t found here.                                                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 8, 2022                                              *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function for finding the index of the minimum of a double array.          */
size_t tmpl_Double_Array_Min_Index(double *arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n, ind;

    /*  If the array is NULL or empty, the result is undefined. Return NaN.   */
    if (!arr || !len)
        return (size_t)0;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    ind = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    while (tmpl_Double_Is_NaN(arr[ind]))
    {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return 0.              */
        if (ind == len)
            return (size_t)0;

        ++ind;
    }

    /*  Loop through the remaining elements and find the minimum.             */
    for (n = ind + (size_t)1; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < arr[ind])
            ind = n;
    }

    return ind;
}
/*  End of tmpl_Double_Array_Min_Index.                                       */
