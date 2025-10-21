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
 *                         tmpl_array_double_sum_char                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the sum of a signed char array.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Char_Array_Double_Sum                                            *
 *  Purpose:                                                                  *
 *      Computes the sum of a signed char array, as a double.                 *
 *  Arguments:                                                                *
 *      arr (const signed char * const):                                      *
 *          A signed char array.                                              *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      sum (double):                                                         *
 *          The sum of the array.                                             *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If double is 64 bits and char is less than 32 bits (very likely),     *
 *      simply loop through the array and add. Otherwise, use the Kahan       *
 *      summation algorithm to avoid precision loss.                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 *  2.) tmpl_cast.h:                                                          *
 *          Header providing TMPL_CAST with C vs. C++ compatibility.          *
 *  3.) tmpl_limits.h:                                                        *
 *          Header file providing the TMPL_UCHAR_BIT macro.                   *
 *  4.) tmpl_ieee754_double.h:                                                *
 *          Provides TMPL_HAS_IEEE754_DOUBLE indicating 64-bit double support.*
 *  5.) tmpl_fast_two_sum_double.h:                                           *
 *          Provides an inlined Fast2Sum (if inline support is available).    *
 *  6.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 13, 2024                                                *
 ******************************************************************************/

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  TMPL_UCHAR_BIT found here, with the number of numerical bits in uchar.    */
#include <libtmpl/include/tmpl_limits.h>

/*  TMPL_HAS_IEEE754_DOUBLE found here, indicating if we have 64-bit doubles. */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype, found in tmpl_array_integer.h.  */
extern double
tmpl_Char_Array_Double_Sum(const signed char * const arr, size_t len);

/*  If char is very big (unlikely) or double is not 64-bits (also unlikely),  *
 *  use the Kahan summation algorithm to prevent precision loss.              */
#if (TMPL_UCHAR_BIT > 32) || (TMPL_HAS_IEEE754_DOUBLE == 0)

/*  Check for inline support for Fast2Sum. Fast2Sum is a short routine.       */
#if TMPL_USE_INLINE == 1

/*  Fast2Sum found here.                                                      */
#include <libtmpl/include/inline/two_sum/tmpl_fast_two_sum_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern void
tmpl_Double_Fast_Two_Sum(double x,
                         double y,
                         double * TMPL_RESTRICT const out,
                         double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for summing the elements of a signed char array.                 */
double tmpl_Char_Array_Double_Sum(const signed char * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum, err;

    /*  For empty / NULL arrays we follow the numpy convention, return 0.     */
    if (!arr || !len)
        return 0.0;

    /*  Initialize the sum variable to the zeroth element. Error starts at 0. */
    sum = TMPL_CAST(arr[0], double);
    err = 0.0;

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
    {
        /*  Fast2Sum does the following:                                      *
         *                                                                    *
         *      s = sum + (arr[n] + err)                                      *
         *      e = err - (s - sum)                                           *
         *      sum = s                                                       *
         *      err = e                                                       *
         *                                                                    *
         *  We need the current element of the array as a double, and the sum *
         *  of this entry with the current error.                             */
        const double val = TMPL_CAST(arr[n], double);
        const double tmp = val + err;

        /*  Perform Fast2Sum and update the summation and the error.          */
        tmpl_Double_Fast_Two_Sum(sum, tmp, &sum, &err);
    }

    return sum;
}
/*  End of tmpl_Char_Array_Double_Sum.                                        */

#else
/*  Else for #if (TMPL_UCHAR_BIT > 32) || (TMPL_HAS_IEEE754_DOUBLE == 0).     */

/*  What is more likely is that signed char is 8 bits, and double is 64.      *
 *  There is no need for the Kahan algorithm, double has plenty of precision. */

/*  Function for averaging the elements of a signed char array.               */
double tmpl_Char_Array_Double_Sum(const signed char * const arr, size_t len)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    size_t n;
    double sum;

    /*  For empty / NULL arrays we follow the numpy convention, return 0.     */
    if (!arr || !len)
        return 0.0;

    /*  Initialize the sum variable to the zeroth element.                    */
    sum = TMPL_CAST(arr[0], double);

    /*  Loop through the remaining elements and add.                          */
    for (n = 1; n < len; ++n)
        sum += TMPL_CAST(arr[n], double);

    return sum;
}
/*  End of tmpl_Char_Array_Double_Sum.                                        */

#endif
/*  End of #if (TMPL_UCHAR_BIT > 32) || (TMPL_HAS_IEEE754_DOUBLE == 0).       */
