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
 *                         tmpl_array_double_rms_long                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the root-mean-square of a signed long array.                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Long_Array_Double_RMS                                            *
 *  Purpose:                                                                  *
 *      Computes the root-mean-square of a signed long array.                 *
 *  Arguments:                                                                *
 *      arr (const signed long int * const):                                  *
 *          A signed long int array.                                          *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      rms (double):                                                         *
 *          The root-mean-square of the array.                                *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a real number.                    *
 *  Method:                                                                   *
 *      Compute using the definition. Given numbers a_n we have:              *
 *                                                                            *
 *                      ------------------                                    *
 *                      |      N - 1                                          *
 *                      |      -----                                          *
 *                      |   1  \       2                                      *
 *          rms(a) = \  |  --- /     a                                        *
 *                    \ |   N  -----  n                                       *
 *                     \|      n = 0                                          *
 *                                                                            *
 *      The sum is computed and the result is passed to the sqrt function.    *
 *  Notes:                                                                    *
 *      If the input array is empty a NaN (not-a-number) is returned.         *
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
 *  Date:       March 18, 2024                                                *
 ******************************************************************************/

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  sqrt function and TMPL_NAN macro provided here.                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype given here.                                            */
#include <libtmpl/include/tmpl_array_integer.h>

/*  It is common for long to be 64-bits wide, which is larger than the        *
 *  mantissa of a double allows for. To avoid precision loss we'll use a      *
 *  double-double trick for the intermediate computations.                    */

/*  Computes the root-mean-square of a signed long array.                     */
double tmpl_Long_Array_Double_RMS(const signed long int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum_hi, sum_lo, sum;

    /*  If the array is NULL or empty we have a divide-by-zero. Return NaN.   */
    if (!arr || !len)
        return TMPL_NAN;

    /*  Initialize the sum variable to zero so we can sum over it.            */
    sum_hi = 0.0;
    sum_lo = 0.0;

    /*  Loop through the remaining elements and add.                          */
    for (n = 0; n < len; ++n)
    {
        /*  To avoid overflow with integer multiplication, cast the value     *
         *  to a double and square with this.                                 */
        const double an_hi = (double)arr[n];
        const signed long int an_rounded = (signed long int)an_hi;
        const double an_lo = (double)(arr[n] - an_rounded);

        /*  Add the square of the nth term to the sum.                        */
        const double summand_hi = an_hi * an_hi;
        const double summand_lo = an_lo * (2.0 * an_hi + an_lo);

        /*  Double-Double or "dd" addition for sum + summand.                 */
        const double dd0 = sum_hi + summand_hi;         /*  Sum of high terms.*/
        const double dd1 = sum_hi - dd0;                /*  Sum error.        */
        const double dd2 = sum_lo + summand_lo;         /*  Sum of low terms. */
        const double dd3 = sum_lo - dd2;                /*  Sum error.        */
        const double dd4a = sum_hi - (dd0 + dd1);       /*  High correction.  */
        const double dd4b = dd2 + (dd1 + summand_hi);   /*  High correction.  */
        const double dd4 = dd4a + dd4b;                 /*  Sum corrections.  */
        const double dd5 = dd0 + dd4;                   /*  New summand.      */
        const double dd6a = sum_lo - (dd2 + dd3);       /*  Low correction.   */
        const double dd6b = dd3 + summand_lo;           /*  Low correction.   */
        const double dd6c = dd4 + (dd0 - dd5);          /*  Low correction.   */
        const double dd6 = dd6a + dd6b + dd6c;          /*  Sum corrections.  */

        /*  High part of the sum.                                             */
        sum_hi = dd5 + dd6;

        /*  Low part of the sum.                                              */
        sum_lo = dd6 + (dd5 - sum_hi);
    }

    /*  Convert back to double and finish the computation.                    */
    sum = sum_hi + sum_lo;

    /*  The rms is obtained from the square root of the weighted sum.         */
    return tmpl_Double_Sqrt(sum / (double)len);
}
/*  End of tmpl_Long_Array_Double_RMS.                                        */
