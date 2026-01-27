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
 *                            tmpl_factorial_ullong                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial function for unsigned long long integers.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULLong_Factorial                                                 *
 *  Purpose:                                                                  *
 *      Computes the factorial function, n! = n * (n-1) * ... * 2 * 1.        *
 *  Arguments:                                                                *
 *      n (const unsigned long long int):                                     *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (unsigned long long int):                                          *
 *          The factorial of n.                                               *
 *  64-bit Version:                                                           *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use a lookup table. Only a few values of n will not cause         *
 *          overflow. For larger values return 0. n! is never zero for        *
 *          non-negative integers, so this acts as an error for the caller.   *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use the formula n! = n*(n-1)! and iteratively compute.            *
 *  Notes:                                                                    *
 *      The portable method does not return 0 on overflow, and does not       *
 *      detect overflows at all for the caller.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file containing TMPL_HAS_LONGLONG.                         *
 *  2.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is provided.                   *
 *  3.) tmpl_limits.h:                                                        *
 *          Header file containing TMPL_ULLONG_BIT.                           *
 *  4.) tmpl_array_size.h:                                                    *
 *          Header file providing the TMPL_ARRAY_SIZE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/18: Ryan Maguire                                                  *
 *      Moved from math/ to integer/.                                         *
 *  2024/05/24: Ryan Maguire                                                  *
 *      Inlined the function, moved to include/inline/integer/.               *
 *  2026/01/26: Ryan Maguire                                                  *
 *      Cleaned up, made it so only two functions are implemented. A macro    *
 *      now exists indicating if a lookup table can be used, and a for-loop   *
 *      is used otherwise.                                                    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FACTORIAL_ULLONG_H
#define TMPL_FACTORIAL_ULLONG_H

/*  The TMPL_HAS_LONGLONG macro is found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  Only compile this is long long support is available / requested.          */
#if TMPL_HAS_LONGLONG == 1

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  The TMPL_ULLONG_BIT macro is found here.                                  */
#include <libtmpl/include/tmpl_limits.h>

/*  TMPL_ARRAY_SIZE macro provided here.                                      */
#include <libtmpl/include/helper/tmpl_array_size.h>

/*  For n > 20, and for 64-bit unsigned long long, n! overflows. Precompute   *
 *  the first 21 values (0 <= n <= 20) and use this as a lookup table.        */
static const unsigned long long int tmpl_ullong_factorial_values[21] = {
    1ULL, 1ULL, 2ULL, 6ULL, 24ULL, 120ULL, 720ULL, 5040ULL, 40320ULL, 362880ULL,
    3628800ULL, 39916800ULL, 479001600ULL, 6227020800ULL, 87178291200ULL,
    1307674368000ULL, 20922789888000ULL, 355687428096000ULL,
    6402373705728000ULL, 121645100408832000ULL, 2432902008176640000ULL
};

/*  64-bit unsigned long long has a max value of 18,446,744,073,709,551,615.  */
#if TMPL_ULLONG_BIT == 64

/******************************************************************************
 *                               64-Bit Version                               *
 ******************************************************************************/

/*  64-bit unsigned long long factorial function.                             */
TMPL_INLINE_DECL
unsigned long long int tmpl_ULLong_Factorial(const unsigned long long int n)
{
    /*  For 64-bit unsigned long n! overflows for n > 20. Return 0 if this is *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n >= TMPL_ARRAY_SIZE(tmpl_ullong_factorial_values))
        return 0ULL;

    /*  Otherwise, return n! from the precomputed table above.                */
    return tmpl_ullong_factorial_values[n];
}
/*  End of tmpl_ULLong_Factorial.                                             */

#else
/*  Portable algorithm for other sizes.                                       */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Portable factorial function for unsigned long long.                       */
TMPL_INLINE_DECL
unsigned long long int tmpl_ULLong_Factorial(const unsigned long long int n)
{
    /*  Declare necessary variable. C89 requires this at the top.             */
    unsigned long long int k, factorial;

    /*  For 0 <= n <= 20 we can use the lookup table above.                   */
    if (n < TMPL_ARRAY_SIZE(tmpl_ullong_factorial_values))
        return tmpl_ullong_factorial_values[n];

    /*  Otherwise, set factorial to the largest value in the table. We will   *
     *  compute using n! = n*(n-1)*...*20!.                                   */
    factorial = tmpl_ullong_factorial_values[20];

    /*  For 21 <= k <= n, multiply the result by k. This method has the       *
     *  unfortunate disadvantage of not detecting overflows.                  */
    for (k = TMPL_ARRAY_SIZE(tmpl_ullong_factorial_values); k <= n; ++k)
        factorial *= k;

    return factorial;
}
/*  End of tmpl_ULLong_Factorial.                                             */

#endif
/*  End of #if TMPL_ULLONG_BIT == 64.                                         */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#endif
/*  End of include guard.                                                     */
