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
 *                            tmpl_factorial_uint                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial function for unsigned integers.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_Factorial                                                   *
 *  Purpose:                                                                  *
 *      Computes the factorial function, n! = n * (n-1) * ... * 2 * 1.        *
 *  Arguments:                                                                *
 *      n (unsigned int):                                                     *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (unsigned int):                                                    *
 *          The factorial of n.                                               *
 *  16-bit / 32-bit / 64-bit Version:                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use a lookup table. Only a few values of n will not cause         *
 *          cause overflow. For larger values return 0. n! is never zero for  *
 *          non-negative integers, so this acts as an error for the caller.   *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use the formala n! = n*(n-1)! and iteratively compute.            *
 *  Notes:                                                                    *
 *      The portable method does not return 0 on overflow, and does not       *
 *      detect overflows at all for the caller.                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config:                                                          *
 *          Header file where TMPL_INLINE_DECL is provided.                   *
 *  2.) tmpl_limits.h:                                                        *
 *          Header file containing TMPL_UCHAR_BIT                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/18: Ryan Maguire                                                  *
 *      Moved from math/ to integer/.                                         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FACTORIAL_UINT_H
#define TMPL_FACTORIAL_UINT_H

/*  The TMPL_INLINE_DECL macro is provided here.                              */
#include <libtmpl/include/tmpl_config.h>

/*  The TMPL_UINT_BIT macro is found here.                                    */
#include <libtmpl/include/tmpl_limits.h>

/*  16-bit unsigned int has a max value of 65,535.                            */
#if TMPL_UINT_BIT == 16

/******************************************************************************
 *                               16-Bit Version                               *
 ******************************************************************************/

/*  For n > 8, and for 16-bit unsigned int, n! overflows. Pre-compute the     *
 *  first 9 values (0 <= n <= 8) and use this as a lookup table.              */
static const unsigned int tmpl_uint_factorial_values[9] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U
};

/*  16-bit unsigned int factorial function.                                   */
TMPL_INLINE_DECL
unsigned int tmpl_UInt_Factorial(unsigned int n)
{
    /*  For 16-bit unsigned int n! overflows for n > 8. Return 0 if this is   *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 8U)
        return 0U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uint_factorial_values[n];
}
/*  End of tmpl_UInt_Factorial.                                               */

/*  32-bit unsigned int has a max value of 4,294,967,295.                     */
#elif TMPL_UINT_BIT == 32

/******************************************************************************
 *                               32-Bit Version                               *
 ******************************************************************************/

/*  For n > 12, and for 32-bit unsigned int, n! overflows. Pre-compute the    *
 *  first 13 values (0 <= n <= 12) and use this as a lookup table.            */
static const unsigned int tmpl_uint_factorial_values[13] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U, 362880U,
    3628800U, 39916800U, 479001600U
};

/*  32-bit unsigned int factorial function.                                   */
TMPL_INLINE_DECL
unsigned int tmpl_UInt_Factorial(unsigned int n)
{
    /*  For 32-bit unsigned int n! overflows for n > 12. Return 0 if this is  *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 12U)
        return 0U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uint_factorial_values[n];
}
/*  End of tmpl_UInt_Factorial.                                               */

/*  64-bit unsigned int has a max value of 18,446,744,073,709,551,615.        */
#elif TMPL_UINT_BIT == 64

/******************************************************************************
 *                               64-Bit Version                               *
 ******************************************************************************/

/*  For n > 20, and for 64-bit unsigned int, n! overflows. Pre-compute the    *
 *  first 21 values (0 <= n <= 20) and use this as a lookup table.            */
static const unsigned int tmpl_uint_factorial_values[21] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U, 362880U,
    3628800U, 39916800U, 479001600U, 6227020800U, 87178291200U,
    1307674368000U, 20922789888000U, 355687428096000U, 6402373705728000U,
    121645100408832000U, 2432902008176640000U
};

/*  64-bit unsigned int factorial function.                                   */
TMPL_INLINE_DECL
unsigned int tmpl_UInt_Factorial(unsigned int n)
{
    /*  For 64-bit unsigned int n! overflows for n > 20. Return 0 if this is  *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 20U)
        return 0U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uint_factorial_values[n];
}
/*  End of tmpl_UInt_Factorial.                                               */

/*  Lastly, a portable version. No assumption on width is made.               */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Int must be at least 16 bits wide. Precompute the first 9 values of n!.   */
static const unsigned int tmpl_uint_factorial_values[9] = {
    1U, 1U, 2U, 6U, 24U, 120U, 720U, 5040U, 40320U
};

/*  Portable factorial function for unsigned int.                             */
TMPL_INLINE_DECL
unsigned int tmpl_UInt_Factorial(unsigned int n)
{
    /*  Declare necessary variable. C89 requires this at the top.             */
    unsigned int k, factorial;

    /*  For 0 <= n <= 8 we can use the lookup table above.                    */
    if (n < 9U)
        return tmpl_uint_factorial_values[n];

    /*  Otherwise, set factorial to the largest value in the table. We will   *
     *  compute using n! = n*(n-1)*...*8!.                                    */
    factorial = tmpl_uint_factorial_values[8];

    /*  For 9 <= k <= n, multiply the result by k. This method has the        *
     *  unfortunate disadvantage of not detecting overflows.                  */
    for (k = 9U; k <= n; ++k)
        factorial *= k;

    return factorial;
}
/*  End of tmpl_UInt_Factorial.                                               */

#endif
/*  End of #if TMPL_UINT_BIT == 16.                                           */

#endif
/*  End of include guard.                                                     */
