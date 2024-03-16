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
 *                       tmpl_array_float_average_ulong                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the average of an unsigned long array.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Array_Float_Average                                        *
 *  Purpose:                                                                  *
 *      Computes the average of an unsigned long array.                       *
 *  Arguments:                                                                *
 *      arr (const unsigned long int * const):                                *
 *          An unsigned long array.                                           *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      avg (float):                                                         *
 *          The average of the array.                                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and add. Divide this by the    *
 *      number of elements in the array. If the array is empty return NaN.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_math.h:                                                          *
 *          Header providing the TMPL_NANF macro for "not-a-number."          *
 *  3.) tmpl_array_integer.h:                                                 *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 16, 2024                                                *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  TMPL_NANF macro provided here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Function for averaging the elements of an unsigned long array.            */
float
tmpl_ULong_Array_Float_Average(const unsigned long int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    float sum;

    /*  If the array is NULL or empty we have a divide-by-zero. Return NaN.   */
    if (!arr || !len)
        return TMPL_NANF;

    /*  Initialize the sum variable to the zeroth element.                    */
    sum = (float)arr[0];

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
        sum += (float)arr[n];

    /*  The average is the sum divided by the number of terms.                */
    return sum / (float)len;
}
/*  End of tmpl_ULong_Array_Float_Average.                                    */
