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
 *                            tmpl_array_min_ulong                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the minimum of an unsigned long array.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Array_Min                                                  *
 *  Purpose:                                                                  *
 *      Computes the minimum of an unsigned long array.                       *
 *  Arguments:                                                                *
 *      arr (const unsigned long int * const):                                *
 *          An unsigned long int array.                                       *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      min (unsigned long int):                                              *
 *          The minimum of the array.                                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and compare to find the min.   *
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

/*  Function for finding the minimum of an unsigned long array.               */
unsigned long int
tmpl_ULong_Array_Min(const unsigned long int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    unsigned long int min;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len)
        return 0UL;

    /*  Initialize the min variable to the zeroth element.                    */
    min = arr[0];

    /*  Loop through the remaining elements and find the minimum.             */
    for (n = 1; n < len; ++n)
    {
        /*  If the current array element is smaller, reset the min value.     */
        if (arr[n] < min)
            min = arr[n];
    }

    return min;
}
/*  End of tmpl_ULong_Array_Min.                                              */
