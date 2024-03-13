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
 *                       tmpl_array_double_total_ulong                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the sum of an unsigned long array.                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Array_Double_Total                                         *
 *  Purpose:                                                                  *
 *      Computes the sum of an unsigned long array.                           *
 *  Arguments:                                                                *
 *      arr (const unsigned long int * const):                                *
 *          An unsigned long array.                                           *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      sum (double):                                                         *
 *          The sum of the array.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and add.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_array_integer.h:                                                 *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 13, 2024                                                *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Function for summing the elements of an unsigned long array.              */
double
tmpl_ULong_Array_Double_Total(const unsigned long int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len)
        return 0.0;

    /*  Initialize the sum variable to the zeroth element.                    */
    sum = (double)arr[0];

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
        sum += (double)arr[n];

    return sum;
}
/*  End of tmpl_ULong_Array_Double_Total.                                     */
