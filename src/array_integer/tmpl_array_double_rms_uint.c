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
 *                         tmpl_array_double_rms_uint                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the root-mean-square of an unsigned int array.               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_Array_Double_RMS                                            *
 *  Purpose:                                                                  *
 *      Computes the root-mean-square of an unsigned int array.               *
 *  Arguments:                                                                *
 *      arr (const unsigned int * const):                                     *
 *          An unsigned int array.                                            *
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

/*  Computes the root-mean-square of an unsigned int array.                   */
double tmpl_UInt_Array_Double_RMS(const unsigned int * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum;

    /*  If the array is NULL or empty we have a divide-by-zero. Return NaN.   */
    if (!arr || !len)
        return TMPL_NAN;

    /*  Initialize the sum variable to zero so we can sum over it.            */
    sum = 0.0;

    /*  Loop through the remaining elements and add.                          */
    for (n = 0; n < len; ++n)
    {
        /*  To avoid overflow with integer multiplication, cast the value     *
         *  to a double and square with this.                                 */
        const double an = (double)arr[n];

        /*  Add the square of the nth term to the sum.                        */
        sum += an * an;
    }

    /*  The rms is obtained from the square root of the weighted sum.         */
    return tmpl_Double_Sqrt(sum / (double)len);
}
/*  End of tmpl_UInt_Array_Double_RMS.                                        */
