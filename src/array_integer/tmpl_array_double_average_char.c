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
 *                       tmpl_array_double_average_char                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the average of a signed char array.                          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_Array_Double_Average                                        *
 *  Purpose:                                                                  *
 *      Computes the average of a signed char array, as a double.             *
 *  Arguments:                                                                *
 *      arr (const signed char * const):                                      *
 *          A signed char array.                                              *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      avg (double):                                                         *
 *          The average of the array.                                         *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The average is defined as follows. Given a finite sequence "a",       *
 *      the average "a bar" is:                                               *
 *                                                                            *
 *                   N - 1                                                    *
 *                   -----                                                    *
 *          _    1   \                                                        *
 *          a = ---  /      a                                                 *
 *               N   -----   n                                                *
 *                   n = 0                                                    *
 *                                                                            *
 *      We compute the sum iteratively.                                       *
 *  Notes:                                                                    *
 *      1.) If the array is NULL, or if len is zero, NaN will return.         *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/Arithmetic_mean                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_math.h:                                                          *
 *          Header providing the TMPL_NAN macro for "not-a-number."           *
 *  3.) tmpl_array_integer.h:                                                 *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 16, 2024                                                *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  TMPL_NAN macro provided here.                                             */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Function for averaging the elements of a signed char array.               */
double tmpl_Char_Array_Double_Average(const signed char * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum;

    /*  If the array is NULL or empty we have a divide-by-zero. Return NaN.   */
    if (!arr || !len)
        return TMPL_NAN;

    /*  Initialize the sum variable to the zeroth element.                    */
    sum = (double)arr[0];

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
        sum += (double)arr[n];

    /*  The average is the sum divided by the number of terms.                */
    return sum / (double)len;
}
/*  End of tmpl_Char_Array_Double_Average.                                    */
