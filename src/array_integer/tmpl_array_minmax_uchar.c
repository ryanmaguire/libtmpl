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
 *                          tmpl_array_minmax_uchar                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the minimum and maximum of an unsigned char array.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_Array_MinMax                                               *
 *  Purpose:                                                                  *
 *      Computes the minimum and maximum of an unsigned char array.           *
 *  Arguments:                                                                *
 *      arr (const unsigned char * const):                                    *
 *          An unsigned char array.                                           *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *      min (unsigned char *):                                                *
 *          A pointer to an unsigned char. The minimum is stored here.        *
 *      max (unsigned char *):                                                *
 *          A pointer to an unsigned char. The maximum is stored here.        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and compare.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_array_integer.h:                                                 *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 23, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2024/03/06: Ryan Maguire                                                  *
 *      Added function description and updated comments.                      *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Function for finding the min and max of an unsigned char array.           */
void
tmpl_UChar_Array_MinMax(const unsigned char * const arr,
                        size_t len,
                        unsigned char *min,
                        unsigned char *max)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len || !min || !max)
        return;

    /*  Initialize the min and max variables to the first element.            */
    *min = arr[0];
    *max = arr[0];

    /*  Loop through the remaining elements and find the min and max.         */
    for (n = 1; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < *min)
            *min = arr[n];

        /*  If the current array element is larger, reset the max value.      */
        if (arr[n] > *max)
            *max = arr[n];
    }
}
/*  End of tmpl_UChar_Array_MinMax.                                           */
