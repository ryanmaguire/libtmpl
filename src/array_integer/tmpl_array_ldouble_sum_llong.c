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
 *                       tmpl_array_ldouble_total_llong                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long long array.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LLong_Array_LDouble_Sum                                          *
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long long array.                         *
 *  Arguments:                                                                *
 *      arr (const signed long long int * const):                             *
 *          A long long array.                                                *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      sum (long double):                                                    *
 *          The sum of the array.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop through the elements of the array and add.                       *
 *  Notes:                                                                    *
 *      This file is only compiled if long long support is available.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file with the TMPL_HAS_LONGLONG macro.                     *
 *  3.) tmpl_array_integer.h:                                                 *
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 13, 2024                                                *
 ******************************************************************************/

/*  The TMPL_HAS_LONGLONG macro is found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this if long long support is available / requested.          */
#if TMPL_HAS_LONGLONG == 1

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  Function for summing the elements of a long long array.                   */
long double
tmpl_LLong_Array_LDouble_Sum(const signed long long int * const arr,
                             size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    long double sum;

    /*  If the array is NULL or empty, the result is undefined.               */
    if (!arr || !len)
        return 0.0L;

    /*  Initialize the sum variable to the zeroth element.                    */
    sum = (long double)arr[0];

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
        sum += (long double)arr[n];

    return sum;
}
/*  End of tmpl_LLong_Array_LDouble_Sum.                                      */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
