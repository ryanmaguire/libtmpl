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
 *                            tmpl_array_max_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the max of a float array.                                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Array_Max                                                  *
 *  Purpose:                                                                  *
 *      Computes max(arr), the maximum of the float array arr.                *
 *  Arguments:                                                                *
 *      arr (float *):                                                        *
 *          An array of floats.                                               *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      max (float):                                                          *
 *          The maximum of arr.                                               *
 *  Called Functions:                                                         *
 *      tmpl_Float_Is_NaN (tmpl_math.h):                                      *
 *          Determines if a float is Not-a-Number.                            *
 *  Method:                                                                   *
 *      Loop through the array to find the first entry that is not NaN.       *
 *      Set max to this element. Then loop through the rest of the array      *
 *      and compare the elements with max, resetting max if necessary.        *
 *  Notes:                                                                    *
 *      If the array consists entirely of NaN's, a NaN is returned.           *
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
 *  Date:       November 11, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/07: Ryan Maguire                                                  *
 *      Added license and description.                                        *
 *  2022/12/08: Ryan Maguire                                                  *
 *      Added alternative method that is surprisingly twice as fast.          *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Two methods provided. If this macro isn't set, give the default.          */
#ifndef TMPL_FLOAT_ARRAY_MAX_METHOD
#define TMPL_FLOAT_ARRAY_MAX_METHOD 1
#endif

/*  This method, finding ind and then returning arr[ind], is twice as fast.   *
 *  Quite surprising. Tested on an intel x86_64 machine. This method is about *
 *  the same speed as the other on arm64, oddly enough.                       */
#if TMPL_FLOAT_ARRAY_MAX_METHOD == 1

/*  Function for finding the maximum of a float array.                        */
float tmpl_Float_Array_Max(float *arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n, ind;

    /*  If the array is NULL or empty, the result is undefined. Return NaN.   */
    if (!arr || !len)
        return TMPL_NANF;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    ind = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    while (tmpl_Float_Is_NaN(arr[ind]))
    {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return NaN.            */
        if (ind == len)
            return TMPL_NANF;

        ++ind;
    }

    /*  Loop through the remaining elements and find the maximum.             */
    for (n = ind + (size_t)1; n < len; ++n)
    {
        /*  If the current array element is larger, reset the max value.      */
        if (arr[n] > arr[ind])
            ind = n;
    }

    return arr[ind];
}
/*  End of tmpl_Float_Array_Max.                                              */

#else
/*  Else for #if TMPL_FLOAT_ARRAY_MAX_METHOD == 1.                            */

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
        /*  If the current array element is larger, reset the max value.      */
        if (arr[n] > max)
            max = arr[n];
    }

    return max;
}
/*  End of tmpl_Float_Array_Max.                                              */

#endif
/*  End of #if TMPL_FLOAT_ARRAY_MAX_METHOD == 1.                              */

/*  The rest of libtmpl does not need this, so undef it.                      */
#undef TMPL_FLOAT_ARRAY_MAX_METHOD
