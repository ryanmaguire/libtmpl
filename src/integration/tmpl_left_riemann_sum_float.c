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
 *                        tmpl_left_riemann_sum_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the left-sided Riemann sum of a data set.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Left_Riemann_Sum                                           *
 *  Purpose:                                                                  *
 *      Numerically integrates a data set using a Riemann sum.                *
 *  Arguments:                                                                *
 *      arr (const float *):                                                  *
 *          An array of real numbers.                                         *
 *      dx (float):                                                           *
 *          The distance between points in the data set.                      *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      sum (float):                                                          *
 *          The Riemann sum of the data set.                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Loop over the array and perform the sum:                              *
 *                                                                            *
 *            b                                                               *
 *            -              N - 2                                            *
 *           | |             -----                                            *
 *           |               \                                                *
 *         | |   f(x) dx ~=  /     f(x_n) (x_{n+1} - x_{n})                   *
 *          -                -----                                            *
 *          a                n = 0                                            *
 *                                                                            *
 *      Where f(x_{n}) is the nth element of the input array, and             *
 *      x_{n+1} - x_{n} is assumed to be constant.                            *
 *  Notes:                                                                    *
 *      NULL pointers yield zero. Arrays with NaN or infinity are not treated *
 *      differently and the result will be NaN or infinity.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_integration.h:                                                   *
 *          Header file containing the function prototype.                    *
 *  2.) stddef.h:                                                             *
 *          Standard library header file containing size_t.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 16, 2023                                                 *
 ******************************************************************************/

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_integration.h>

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/*  Function for numerically integrating using a Riemann sum.                 */
float tmpl_Float_Left_Riemann_Sum(const float *arr, float dx, size_t len)
{
    /*  The constant zero casted to type "size_t".                            */
    const size_t zero = (size_t)0;

    /*  Similarly, the constant one cast to "size_t".                         */
    const size_t one = (size_t)1;

    /*  Variable for indexing over the sum.                                   */
    size_t n;

    /*  Number of terms in the summation.                                     */
    const size_t sum_len = len - one;

    /*  Variable for the output, initialized to zero.                         */
    float sum = 0.0F;

    /*  If the input pointer is NULL, return zero. This is treated as         *
     *  equivalent to integrating the zero function.                          */
    if (arr == NULL || len == zero)
        return sum;

    /*  Otherwise loop over the data set and perform the summation.           */
    for (n = zero; n < sum_len; ++n)
        sum += arr[n];

    return sum * dx;
}
/*  End of tmpl_Float_Left_Riemann_Sum.                                       */
