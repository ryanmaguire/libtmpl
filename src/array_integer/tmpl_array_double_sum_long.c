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
 *                         tmpl_array_double_sum_long                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long array.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Long_Array_Double_Sum                                            *
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long array.                              *
 *  Arguments:                                                                *
 *      arr (const signed long int * const):                                  *
 *          A long array.                                                     *
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
 *          Header file with the function prototype.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 13, 2024                                                *
 ******************************************************************************/

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_array_integer.h>

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Neumaier 2Sum found here.                                                 */
#include <libtmpl/include/tmpl_two_sum.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Helper macro for splitting a long into two parts.                         */
#define TMPL_NEG_CAST(n) (-TMPL_CAST(n, unsigned long int)) & 0xFFFFFFFFUL
#define TMPL_NEG_BITS(n) -(TMPL_CAST(TMPL_NEG_CAST(n), signed long int))
#define TMPL_LOW_BITS(n) ((n) < 0 ? TMPL_NEG_BITS(n) : ((n) & 0xFFFFFFFFL))

/*  Function for summing the elements of a signed int array.                  */
double tmpl_Long_Array_Double_Sum(const signed long int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum, err;

    /*  For empty / NULL arrays we follow the numpy convention, return 0.     */
    if (!arr || !len)
        return 0.0;

    /*  Initialize the running sum and error to zero so we may loop over them.*/
    sum = 0.0;
    err = 0.0;

    /*  Loop through the remaining elements and add.                          */
    for (n = 0; n < len; ++n)
    {
        /*  User a 2Sum to preserve accuracy. Split the input into two parts. */
        const signed long int low_ll = TMPL_LOW_BITS(arr[n]);
        const signed long int high_ll = arr[n] - low_ll;
        const double low = TMPL_CAST(low_ll, double);

        /*  Run the Neumaier 2Sum with both the high and low parts.           */
        tmpl_Double_Neumaier_Two_Sum(low, &sum, &err);

        /*  The higher bits are only non-zero if arr[n] is very large,        *
         *  greater than 2^32. Because of this it is likely that these bits   *
         *  are zero. We can skip the second Neumaier 2Sum in this case.      */
        if (high_ll != 0LL)
        {
            /*  The input is a large number and contains higher-order bits.   *
             *  Cast to double and perform another 2Sum.                      */
            const double high = TMPL_CAST(high_ll, double);
            tmpl_Double_Neumaier_Two_Sum(high, &sum, &err);
        }
    }

    /*  With Neumaier 2Sum it is possible for |err| > |sum|, but the correct  *
     *  sum can be obtained by adding the running sum with the error term.    */
    return sum + err;
}
/*  End of tmpl_Long_Array_Double_Sum.                                        */

#undef TMPL_NEG_CAST
#undef TMPL_NEG_BITS
#undef TMPL_LOW_BITS
