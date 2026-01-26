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
 *                            tmpl_factorial_ulong                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial function for unsigned long integers.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_ULong_Factorial                                                  *
 *  Purpose:                                                                  *
 *      Computes the factorial function, n! = n * (n-1) * ... * 2 * 1.        *
 *  Arguments:                                                                *
 *      n (const unsigned long int):                                          *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (unsigned long int):                                               *
 *          The factorial of n.                                               *
 *  32-bit / 64-bit Version:                                                  *
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
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is provided.                   *
 *  2.) tmpl_limits.h:                                                        *
 *          Header file containing TMPL_ULONG_BIT.                            *
 *  3.) tmpl_array_size.h:                                                    *
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
#ifndef TMPL_FACTORIAL_ULONG_H
#define TMPL_FACTORIAL_ULONG_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  The TMPL_ULONG_BIT macro is found here.                                   */
#include <libtmpl/include/tmpl_limits.h>

/*  TMPL_ARRAY_SIZE macro provided here.                                      */
#include <libtmpl/include/helper/tmpl_array_size.h>

/*  32-bit unsigned long has a max value of 4,294,967,295.                    */
#if TMPL_ULONG_BIT == 32

/******************************************************************************
 *                               32-Bit Version                               *
 ******************************************************************************/

/*  For n > 12, and for 32-bit unsigned long, n! overflows. Precompute the    *
 *  first 13 values (0 <= n <= 12) and use this as a lookup table.            */
static const unsigned long int tmpl_ulong_factorial_values[13] = {
    1UL, 1UL, 2UL, 6UL, 24UL, 120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL
};

/*  Macro indicating we may use a lookup table, instead of a for-loop.        */
#define TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE 1

/*  64-bit unsigned long has a max value of 18,446,744,073,709,551,615.       */
#elif TMPL_ULONG_BIT == 64

/******************************************************************************
 *                               64-Bit Version                               *
 ******************************************************************************/

/*  For n > 20, and for 64-bit unsigned long, n! overflows. Precompute the    *
 *  first 21 values (0 <= n <= 20) and use this as a lookup table.            */
static const unsigned long int tmpl_ulong_factorial_values[21] = {
    1UL, 1UL, 2UL, 6UL, 24UL, 120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL, 6227020800UL, 87178291200UL,
    1307674368000UL, 20922789888000UL, 355687428096000UL, 6402373705728000UL,
    121645100408832000UL, 2432902008176640000UL
};

/*  Same macro as before, we may use the lookup table instead of a loop.      */
#define TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE 1

/*  Lastly, a portable version. No assumption on width is made.               */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  For widths other than  32 and 64 use a for-loop.                          */
#define TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE 0

#endif
/*  End of #if TMPL_ULONG_BIT == 32.                                          */

/*  For supported widths, this function is very short. Just use the table.    */
#if TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE == 1

/******************************************************************************
 *                            Lookup Table Version                            *
 ******************************************************************************/

/*  Unsigned long int factorial function.                                     */
TMPL_INLINE_DECL
unsigned long int tmpl_ULong_Factorial(const unsigned long int n)
{
    /*  If n can't index the lookup table, we assume that n! is greater than  *
     *  the maximum value of unsigned long. Return zero in this case. n! is   *
     *  never zero for non-negative integers, so this signals the caller that *
     *  an error has occurred.                                                */
    if (n >= TMPL_ARRAY_SIZE(tmpl_ulong_factorial_values))
        return 0U;

    /*  Otherwise, return n! from the precomputed table.                      */
    return tmpl_ulong_factorial_values[n];
}
/*  End of tmpl_ULong_Factorial.                                              */

/*  Otherwise, use a for-loop with n! = n * (n - 1)!.                         */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Unsigned long int factorial function.                                     */
TMPL_INLINE_DECL
unsigned long int tmpl_ULong_Factorial(const unsigned long int n)
{
    /*  Variable for indexing the for-loop.                                   */
    unsigned long int index;

    /*  Variable for n!. We start at one and iteratively multiply.            */
    unsigned long int factorial = 1UL;

    /*  0! = 1! = 1. Return 1 if n < 2.                                       */
    if (n < 2UL)
        return factorial;

    /*  Loop through and compute using n! = n * (n - 1)!.                     */
    for (index = 2UL; index <= n; ++index)
        factorial *= index;

    return factorial;
}
/*  End of tmpl_ULong_Factorial.                                              */

#endif
/*  End of #if TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE == 1.                    */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_ULONG_FACTORIAL_USE_LOOKUP_TABLE

#endif
/*  End of include guard.                                                     */
