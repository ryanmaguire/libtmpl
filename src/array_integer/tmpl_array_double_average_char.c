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
 *      If signed char is small and double is 64-bits (very likely), we use   *
 *      this sum directly. Otherwise, we use the Kahan summation algorithm to *
 *      avoid precision loss.                                                 *
 *  Notes:                                                                    *
 *      1.) If the array is NULL, or if len is zero, NaN will return.         *
 *  References:                                                               *
 *      1.) https://en.wikipedia.org/wiki/Arithmetic_mean                     *
 *      2.) Kahan, William (January 1965),                                    *
 *          "Further remarks on reducing truncation errors",                  *
 *          Communications of the ACM, volume 8, number 1: 40                 *
 *      3.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *      4.) https://en.wikipedia.org/wiki/2Sum                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_nan_double.h:                                                    *
 *          Header providing the TMPL_NAN macro for "not-a-number."           *
 *  3.) tmpl_cast.h:                                                          *
 *          Header providing TMPL_CAST with C vs. C++ compatibility.          *
 *  4.) tmpl_limits.h:                                                        *
 *          Header file providing the TMPL_UCHAR_BIT macro.                   *
 *  5.) tmpl_ieee754_double.h:                                                *
 *          Provides TMPL_HAS_IEEE754_DOUBLE indicating 64-bit double support.*
 *  6.) tmpl_fast_two_sum_double.h:                                           *
 *          Provides an inlined Fast2Sum (if inline support is available).    *
 *  7.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 16, 2024                                                *
 ******************************************************************************/

/*  TMPL_NAN macro provided here.                                             */
#include <libtmpl/include/nan/tmpl_nan_double.h>

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype, found in tmpl_array_integer.h.  */
extern double
tmpl_Char_Array_Double_Average(const signed char * const arr, size_t len);

extern double
tmpl_Char_Array_Double_Sum(const signed char * const arr, size_t len);

/*  Function for averaging the elements of a signed char array.               */
double tmpl_Char_Array_Double_Average(const signed char * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double sum;

    /*  If the array is NULL or empty we have a divide-by-zero. Return NaN.   */
    if (!arr || !len)
        return TMPL_NAN;

    /*  The average is the sum divided by the number of terms.                */
    sum = tmpl_Char_Array_Double_Sum(arr, len);
    return sum / TMPL_CAST(len, double);
}
/*  End of tmpl_Char_Array_Double_Average.                                    */
