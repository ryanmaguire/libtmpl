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
 *      src/two_sum/                                                          *
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
 *  3.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  4.) tmpl_cast.h:                                                          *
 *          Header providing TMPL_CAST with C vs. C++ compatibility.          *
 *  5.) tmpl_neumaier_two_sum_double.h:                                       *
 *          Provides an inlined Neumaier 2Sum if inline support is available. *
 *  6.) stddef.h:                                                             *
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

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  TMPL_CAST macro found here, providing C vs. C++ compatibility.            */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  Neumaier 2Sum found here.                                                 */
#include <libtmpl/include/tmpl_two_sum.h>

/*  size_t typedef found here.                                                */
#include <stddef.h>

/*  Helper macro for splitting a long long into two parts.                    */
#define TMPL_NEG_CAST(n) (-TMPL_CAST(n, unsigned long long int)) & 0xFFFFFFFFULL
#define TMPL_NEG_BITS(n) -(TMPL_CAST(TMPL_NEG_CAST(n), signed long long int))
#define TMPL_LOW_BITS(n) ((n) < 0 ? TMPL_NEG_BITS(n) : ((n) & 0xFFFFFFFFLL))

/*  Forward declaration / function prototype, found in tmpl_array_integer.h.  */
extern double
tmpl_LLong_Array_Double_Sum(const signed long long int * const arr, size_t len);

/*  Function for summing the elements of a signed int array.                  */
TMPL_NO_ASSOCIATIVE_MATH
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
         *  has a 53-bit mantissa. On most platforms long long is exactly 64  *
         *  bits, meaning long long has 11 bits too many to perform the sum   *
         *  using double. We mitigate using double-double splitting the input *
         *  input into a low and a high part, and then using Neumaier 2Sum on *
         *  the running sum with the low part, and then again with the high   *
         *  part. That is, we have:                                           *
         *                                                                    *
         *      low = lower_32_bits(arr[n])                                   *
         *      high = arr[n] - low                                           *
         *      (sum, error) = neumaier_two_sum(low, sum, error)              *
         *      (sum, error) = neumaier_two_sum(high, sum, error)             *
         *                                                                    *
         *  This avoids the full double-double addition (which requires twice *
         *  as many arithmetic operations) but still handles the sum to       *
         *  double precision.                                                 *
         *                                                                    *
         *  Note:                                                             *
         *      An alternative method of retrieving the high and low parts    *
         *      involves casting. We could write:                             *
         *                                                                    *
         *          high = cast_to_double(arr[n])                             *
         *          low = arr[n] - high                                       *
         *          (sum, error) = neumaier_two_sum(low, sum, error)          *
         *          (sum, error) = neumaier_two_sum(high, sum, error)         *
         *                                                                    *
         *      This works when arr[n] is not very large. In the case where   *
         *      arr[n] is roughly LLONG_MAX, the cast to double may round up  *
         *      to LLONG_MAX + 1, which is not representable as a long long.  *
         *      The computation arr[n] - high is thus undefined. To avoid     *
         *      this, use the bit-by-bit splitting method instead.            *
         *                                                                    *
         *  Retrieve the lower 32 bits of the input.                          */
        const signed long long int low_ll = TMPL_LOW_BITS(arr[n]);
        const signed long long int high_ll = arr[n] - low_ll;
        const double low = TMPL_CAST(low_ll, double);

        /*  Run the Neumaier 2Sum with both the high and low parts.           */
        tmpl_Double_Neumaier_Two_Sum(low, &sum, &err);

        /*  The higher bits are only non-zero if arr[n] is very large,        *
         *  greater than 2^32. Because of this it is likely that these bits   *
         *  are zero. We can skip the second Neumaier 2Sum in this case.      */
        if (high_ll != 0LL)
        {
            /*  The input is a large number and contains higher-order bits.   *
             *  Cast to double. Note, if long long is more than 32 + 53 bits  *
             *  wide (85 bits total), then this cast will lose precision and  *
             *  the sum will be inaccurate. It is universal across compilers  *
             *  and architectures to set long long to be 64 bits, so this is  *
             *  likely not an issue.                                          */
            const double high = TMPL_CAST(high_ll, double);
            tmpl_Double_Neumaier_Two_Sum(high, &sum, &err);
        }
    }

    /*  With Neumaier 2Sum it is possible for |err| > |sum|, but the correct  *
     *  sum can be obtained by adding the running sum with the error term.    */
    return sum + err;
}
/*  End of tmpl_LLong_Array_Double_Sum.                                       */

#undef TMPL_NEG_CAST
#undef TMPL_NEG_BITS
#undef TMPL_LOW_BITS

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */
