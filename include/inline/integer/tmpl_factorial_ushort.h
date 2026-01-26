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
 *                           tmpl_factorial_ushort                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial function for unsigned short integers.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UShort_Factorial                                                 *
 *  Purpose:                                                                  *
 *      Computes the factorial function, n! = n * (n-1) * ... * 2 * 1.        *
 *  Arguments:                                                                *
 *      n (const unsigned short int):                                         *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (unsigned short int):                                              *
 *          The factorial of n.                                               *
 *  16-bit / 32-bit / 64-bit Version:                                         *
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
 *          Header file containing TMPL_USHORT_BIT.                           *
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
#ifndef TMPL_FACTORIAL_USHORT_H
#define TMPL_FACTORIAL_USHORT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  The TMPL_USHORT_BIT macro is found here.                                  */
#include <libtmpl/include/tmpl_limits.h>

/*  TMPL_ARRAY_SIZE macro provided here.                                      */
#include <libtmpl/include/helper/tmpl_array_size.h>

/*  16-bit unsigned short int has a max value of 65,535.                      */
#if TMPL_USHORT_BIT == 16

/******************************************************************************
 *                               16-Bit Version                               *
 ******************************************************************************/

/*  For n > 8, and for 16-bit unsigned short, n! overflows. Precompute the    *
 *  first 9 values (0 <= n <= 8) and use this as a lookup table.              */
static const unsigned short int tmpl_ushort_factorial_values[9] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U
};

/*  Macro indicating we may use a lookup table, instead of a for-loop.        */
#define TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE 1

/*  32-bit unsigned short has a max value of 4,294,967,295.                   */
#elif TMPL_USHORT_BIT == 32

/******************************************************************************
 *                               32-Bit Version                               *
 ******************************************************************************/

/*  For n > 12, and for 32-bit unsigned short, n! overflows. Precompute the   *
 *  first 13 values (0 <= n <= 12) and use this as a lookup table.            */
static const unsigned short int tmpl_ushort_factorial_values[13] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U, 362880U,
    3628800U, 39916800U, 479001600U
};

/*  Same macro as before, we may use the lookup table instead of a loop.      */
#define TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE 1

/*  64-bit unsigned short has a max value of 18,446,744,073,709,551,615.      */
#elif TMPL_USHORT_BIT == 64

/******************************************************************************
 *                               64-Bit Version                               *
 ******************************************************************************/

/*  For n > 20, and for 64-bit unsigned short, n! overflows. Precompute the   *
 *  first 21 values (0 <= n <= 20) and use this as a lookup table.            */
static const unsigned short int tmpl_ushort_factorial_values[21] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U, 362880U,
    3628800U, 39916800U, 479001600U, 6227020800U, 87178291200U,
    1307674368000U, 20922789888000U, 355687428096000U, 6402373705728000U,
    121645100408832000U, 2432902008176640000U
};

/*  64-bit width is the largest supported size. We may use a lookup table.    */
#define TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE 1

/*  Lastly, a portable version. No assumption on width is made.               */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  For widths other than 16, 32, and 64, use a for-loop.                     */
#define TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE 0

#endif
/*  End of #if TMPL_USHORT_BIT == 16.                                         */

/*  For supported widths, this function is very short. Just use the table.    */
#if TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE == 1

/******************************************************************************
 *                            Lookup Table Version                            *
 ******************************************************************************/

/*  Unsigned short int factorial function.                                    */
TMPL_INLINE_DECL
unsigned short int tmpl_UShort_Factorial(const unsigned short int n)
{
    /*  If n can't index the lookup table, we assume that n! is greater than  *
     *  the maximum value of unsigned short. Return zero in this case. n! is  *
     *  never zero for non-negative integers, so this signals the caller that *
     *  an error has occurred.                                                */
    if (n >= TMPL_ARRAY_SIZE(tmpl_ushort_factorial_values))
        return 0U;

    /*  Otherwise, return n! from the precomputed table.                      */
    return tmpl_ushort_factorial_values[n];
}
/*  End of tmpl_UShort_Factorial.                                             */

/*  Otherwise, use a for-loop with n! = n * (n - 1)!.                         */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Unsigned short int factorial function.                                    */
TMPL_INLINE_DECL
unsigned short int tmpl_UShort_Factorial(const unsigned short int n)
{
    /*  Variable for indexing the for-loop.                                   */
    unsigned short int index;

    /*  Variable for n!. We start at one and iteratively multiply.            */
    unsigned short int factorial = 1U;

    /*  0! = 1! = 1. Return 1 if n < 2.                                       */
    if (n < 2U)
        return factorial;

    /*  Loop through and compute using n! = n * (n - 1)!.                     */
    for (index = 2U; index <= n; ++index)
        factorial *= index;

    return factorial;
}
/*  End of tmpl_UShort_Factorial.                                             */

#endif
/*  End of #if TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE == 1.                   */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_USHORT_FACTORIAL_USE_LOOKUP_TABLE

#endif
/*  End of include guard.                                                     */
