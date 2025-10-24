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
 *                         tmpl_array_double_sum_llong                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long long array.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LLong_Array_Double_Sum                                           *
 *  Purpose:                                                                  *
 *      Computes the sum of a signed long long array, as a double.            *
 *  Arguments:                                                                *
 *      arr (const signed long long int * const):                             *
 *          A long long array.                                                *
 *      len (size_t):                                                         *
 *          The length of the array.                                          *
 *  Output:                                                                   *
 *      sum (double):                                                         *
 *          The sum of the array.                                             *
 *  Called Functions:                                                         *
 *      include/inline/two_sum/                                               *
 *          tmpl_Double_Neumaier_Two_Sum:                                     *
 *              Performs the Neumaier version of the 2Sum algorithm.          *
 *  Method:                                                                   *
 *      In C, double usually has a 52-bit mantissa, whereas long long is      *
 *      required to be at least 64 bits long. Casting long long to double     *
 *      will cause rounding error to accumulate if the array has large        *
 *      numbers. Even if the values of the array are representable as doubles,*
 *      floating point round-off may accumulate as the sum is carried out.    *
 *      We get rid of these two issues by using a double-double-like trick,   *
 *      combining this with the Neumaier-Kahan summation algorithm.           *
 *                                                                            *
 *          high = truncate_to_double(arr[n])                                 *
 *          low = arr[n] - high                                               *
 *          (sum, error) = neumaier_two_sum(high, sum, error)                 *
 *          (sum, error) = neumaier_two_sum(low, sum, error)                  *
 *                                                                            *
 *      The final error in (sum, err) is O(length(arr) * eps^2), where eps is *
 *      double precision epsilon (usually 2^-52). The value sum + err is      *
 *      returned, which has error O(eps).                                     *
 *  References:                                                               *
 *      1.) Kahan, William (January 1965),                                    *
 *          "Further remarks on reducing truncation errors",                  *
 *          Communications of the ACM, volume 8, number 1: 40                 *
 *                                                                            *
 *              This short paper (about half a page) details the original     *
 *              Kahan summation algorithm in Fortran. It is adequate for most *
 *              cases but may produce the wrong value if arr[n] is greater in *
 *              magnitude than arr[0] + arr[1] + ... + arr[n - 1], for some   *
 *              0 < n < length(arr). The Neumaier algorithm is a modification *
 *              of the Kahan summation algorithm that allows for the nth term *
 *              in the array to be larger than the running sum.               *
 *                                                                            *
 *      2.) Neumaier, A. (1974)                                               *
 *          "Rundungsfehleranalyse einiger Verfahren zur                      *
 *              Summation endlicher Summen."                                  *
 *          Z. angew. Math. Mech., 54: 39-51.                                 *
 *                                                                            *
 *              The Neumaier modification to the Kahan algorithm is found     *
 *              here. German only, I have not found an English translation.   *
 *              Fortunately the algorithm is pretty easy to decipher for      *
 *              English readers, see (IV, 1) on page 40 ("wenn" = "if", and   *
 *              this is sufficient to read the formula).                      *
 *                                                                            *
 *      3.) Dekker, T.J. (June 1971).                                         *
 *          "A floating-point technique for                                   *
 *              extending the available precision."                           *
 *          Numerische Mathematik. Vol. 18, No. 3: Pages 224-242.             *
 *                                                                            *
 *              Fast2Sum algorithm is described here. The Neumaier sum uses   *
 *              a modification of Fast2Sum in combination with the Kahan      *
 *              summation algorithm.                                          *
 *                                                                            *
 *      4.) https://en.wikipedia.org/wiki/Kahan_summation_algorithm           *
 *      5.) https://en.wikipedia.org/wiki/2Sum                                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          TMPL_HAS_LONGLONG found here. This file is compiled if this is 1. *
 *  2.) tmpl_config.h:                                                        *
 *          Provides the TMPL_USE_INLINE macro.                               *
 *  3.) tmpl_cast.h:                                                          *
 *          Header providing TMPL_CAST with C vs. C++ compatibility.          *
 *  4.) tmpl_neumaier_two_sum_double.h:                                       *
 *          Provides an inlined Neumaier 2Sum if inline support is available. *
 *  5.) stddef.h:                                                             *
 *          Standard header file containing the size_t typedef.               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 13, 2024                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/10/22: Ryan Maguire                                                  *
 *      Changed name to Sum. Implemented Neumaier-Kahan summation and a       *
 *      double-double trick to avoid precision loss with 64-bit long long.    *
 ******************************************************************************/

/*  The TMPL_HAS_LONGLONG macro is found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this if long long support is available / requested.          */
#if TMPL_HAS_LONGLONG == 1

/*  TMPL_USE_INLINE macro found here, indicating inline support.              */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Forward declaration / function prototype, found in tmpl_array_integer.h.  */
extern double
tmpl_LLong_Array_Double_Sum(const signed long long int * const arr, size_t len);

/*  Check for inline support for Neumaier 2Sum. This is a short routine.      */
#if TMPL_USE_INLINE == 1

/*  Neumaier 2Sum found here.                                                 */
#include <libtmpl/include/inline/two_sum/tmpl_neumaier_two_sum_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, tell the compiler about the function.             */
extern void
tmpl_Double_Neumaier_Two_Sum(double input,
                             double * TMPL_RESTRICT const sum,
                             double * TMPL_RESTRICT const err);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Function for summing the elements of a signed int array.                  */
double
tmpl_LLong_Array_Double_Sum(const signed long long int * const arr, size_t len)
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
        /*  long long is required to be at least 64 bits, and double usually  *
         *  has a 53 bit mantissa. On most platforms long long is exactly 64  *
         *  bits, meaning long long has 11 bits too many to perform the sum   *
         *  using double. We mitigate using double-double splitting the input *
         *  input into a low and a high part, and then using Neumaier 2Sum on *
         *  the running sum with the high part, and then again with the low   *
         *  part. That is, we have:                                           *
         *                                                                    *
         *      high = truncate_to_double(arr[n])                             *
         *      low = arr[n] - high                                           *
         *      (sum, error) = neumaier_two_sum(high, sum, error)             *
         *      (sum, error) = neumaier_two_sum(low, sum, error)              *
         *                                                                    *
         *  This avoids the full double-double addition (which requires twice *
         *  as many arithmetic operations) but still handles the sum to       *
         *  double precision. Extract the high and low parts of the input.    */
        const double high = TMPL_CAST(arr[n], double);
        const signed long long high_ll = TMPL_CAST(high, signed long long int);
        const signed long long low_ll = arr[n] - high_ll;
        const double low = TMPL_CAST(low_ll, double);

        /*  Run the Neumaier 2Sum with both the high and low parts.           */
        tmpl_Double_Neumaier_Two_Sum(high, &sum, &err);

        /*  The lower part is only non-zero if arr[n] is very large, greater  *
         *  than the largest integer that double can represent perfectly.     *
         *  This is around 2^52, meaning it is quite likely that low is zero. *
         *  We can skip the second Neumaier 2Sum in this case.                */
        if (low != 0.0)
            tmpl_Double_Neumaier_Two_Sum(low, &sum, &err);
    }

    /*  With Neumaier 2Sum it is possible for |err| > |sum|, but the correct  *
     *  sum can be obtained by adding the running sum with the error term.    */
    return sum + err;
}
/*  End of tmpl_LLong_Array_Double_Sum.                                       */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
