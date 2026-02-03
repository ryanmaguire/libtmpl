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
 *                          tmpl_array_minmax_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the min and max of a double array.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Array_MinMax                                              *
 *  Purpose:                                                                  *
 *      Computes min(arr) and max(arr), the minimum and maximum of an array.  *
 *  Arguments:                                                                *
 *      arr (double *):                                                       *
 *          An array of doubles.                                              *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      min (double *):                                                       *
 *          A pointer to a double. The min of the array will be stored here.  *
 *      max (double *):                                                       *
 *          A pointer to a double. The max of the array will be stored here.  *
 *  Called Functions:                                                         *
 *      tmpl_Double_Is_NaN (tmpl_math.h):                                     *
 *          Determines if a double is Not-a-Number.                           *
 *  Method:                                                                   *
 *      Loop through the array to find the first entry that is not NaN.       *
 *      Set min and max to this element. Then loop through the array and      *
 *      compare the elements with min and max, resetting if necessary.        *
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
 *  2022/12/12: Ryan Maguire                                                  *
 *      Added license and description.                                        *
 *  2022/12/13: Ryan Maguire                                                  *
 *      Added alternative method, similar to min and max routines.            *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Two methods provided. If this macro isn't set, give the default.          */
#ifndef TMPL_DOUBLE_ARRAY_MINMAX_METHOD
#define TMPL_DOUBLE_ARRAY_MINMAX_METHOD 1
#endif

/*  Alternate method where the indices are found. Slightly faster.            */
#if TMPL_DOUBLE_ARRAY_MINMAX_METHOD == 1

/*  Function for finding the min and max of a double array.                   */
void
tmpl_Double_Array_MinMax(const double * const arr,
                         const size_t len,
                         double * const min,
                         double * const max)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n, minind, maxind;

    /*  If the array is NULL or empty, the result is undefined. Similarly if  *
     *  either or the max or min pointers or NULL. Simply return to caller.   */
    if (!arr || !len || !max || !min)
        return;

    /*  Starting at the zeroth element, we'll increment through the array     *
     *  until we find a non-NaN.                                              */
    n = (size_t)0;

    /*  Find the first non-nan in the array. This is likely the zeroth one.   */
    while (tmpl_Double_Is_NaN(arr[n]))
    {
        /*  If the array consists only of NaN's (unlikely), stop this loop    *
         *  from going beyond the bounds of the array. Return NaN.            */
        if (n == len)
        {
            *min = TMPL_NAN;
            *max = *min;
            return;
        }

        ++n;
    }

    /*  n is the index of the first non-NaN in the array. Start here.         */
    minind = n;
    maxind = n;

    /*  Loop through the remaining elements and find the min and max.         */
    for (; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < arr[minind])
            minind = n;

        /*  Similarly, if this element is larger reset the max value.         */
        if (arr[n] > arr[maxind])
            maxind = n;
    }

    *min = arr[minind];
    *max = arr[maxind];
    return;
}
/*  End of tmpl_Double_Array_MinMax.                                          */

#else
/*  Else for #if TMPL_DOUBLE_ARRAY_MINMAX_METHOD == 1.                        */

/*  Function for finding the min and max of a double array.                   */
void
tmpl_Double_Array_MinMax(const double * const arr,
                         const size_t len,
                         double * const min,
                         double * const max)
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

#endif
/*  End of #if TMPL_DOUBLE_ARRAY_MINMAX_METHOD == 1.                          */

/*  The rest of libtmpl does not need this, so undef it.                      */
#undef TMPL_DOUBLE_ARRAY_MINMAX_METHOD
