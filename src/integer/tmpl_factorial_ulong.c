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
 *      Computes the factorial function, n! = n*(n-1)* ... * 2 * 1.           *
 *  Arguments:                                                                *
 *      n (unsigned long int):                                                *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (double):                                                          *
 *          The factorial of n.                                               *
 *  32-bit / 64-bit Version:                                                  *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Use a lookup table. Only a few values of n will not cause         *
 *          cause overflow. For 32-bit unsigned long this is 0 <= n <= 12 and *
 *          for 64-bit unsigned long this is 0 <= n <= 20. For larger values  *
 *          return 0. n! is never zero for non-negative integers, so this     *
 *          acts as an error message to the caller.                           *
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
 *  1.) tmpl_integer.h:                                                       *
 *          Header file with the functions prototype.                         *
 *  2.) limits.h:                                                             *
 *          Standard library file containing ULONG_MAX.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/10/18: Ryan Maguire                                                  *
 *      Moved from math/ to integer/.                                         *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_integer.h>

/*  The ULONG_MAX macro is found here.                                        */
#include <limits.h>

/*  32-bit unsigned long has a max value of 4,294,967,295.                    */
#if ULONG_MAX == 0xFFFFFFFFU

/*  For n > 12, and for 32-bit unsigned long, n! overflows. Pre-compute the   *
 *  first 13 values (0 <= n <= 12) and use this as a lookup table.            */
static const unsigned long int tmpl_ulong_factorial_values[13] = {
    1UL, 1UL, 2UL, 6UL, 24UL, 120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL
};

/*  32-bit unsigned long factorial function.                                  */
unsigned long int tmpl_ULong_Factorial(unsigned long int n)
{
    /*  For 32-bit unsigned long n! overflows for n > 12. Return 0 if this is *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 12UL)
        return 0UL;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_ulong_factorial_values[n];
}
/*  End of tmpl_ULong_Factorial.                                              */

/*  64-bit unsigned long has a max value of 18,446,744,073,709,551,615.       */
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFFU

/*  For n > 20, and for 64-bit unsigned long, n! overflows. Pre-compute the   *
 *  first 21 values (0 <= n <= 20) and use this as a lookup table.            */
static const unsigned long int tmpl_ulong_factorial_values[21] = {
    1UL, 1UL, 2UL, 6UL, 24UL, 120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL, 6227020800UL, 87178291200UL,
    1307674368000UL, 20922789888000UL, 355687428096000UL, 6402373705728000UL,
    121645100408832000UL, 2432902008176640000UL
};

/*  64-bit unsigned long factorial function.                                  */
unsigned long int tmpl_ULong_Factorial(unsigned long int n)
{
    /*  For 64-bit unsigned long n! overflows for n > 20. Return 0 if this is *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 20UL)
        return 0UL;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_ulong_factorial_values[n];
}
/*  End of tmpl_ULong_Factorial.                                              */

#else
/*  Portable algorithm for other sizes. long must be at least 32-bit, so we   *
 *  pre-compute a few values.                                                 */

static const unsigned long int tmpl_ulong_factorial_values[13] = {
    1UL, 1UL, 2UL, 6UL, 24UL, 120UL, 720UL, 5040UL, 40320UL, 362880UL,
    3628800UL, 39916800UL, 479001600UL
};

/*  Portable factorial function for unsigned long.                            */
unsigned long int tmpl_ULong_Factorial(unsigned long int n)
{
    /*  Declare necessary variable. C89 requires this at the top.             */
    unsigned long int k, factorial;

    /*  For 0 <= n <= 12 we can use the lookup table above.                   */
    if (n < 13UL)
        return tmpl_ulong_factorial_values[n];

    /*  Otherwise, set factorial to the largest value in the table. We will   *
     *  compute using n! = n*(n-1)*...*12!.                                   */
    factor = tmpl_ulong_factorial_values[12];

    /*  For 13 <= k <= n, multiply the result by k. This method has the       *
     *  unfortunate disadvantage of not detecting overflows.                  */
    for (k = 13UL; k <= n; ++k)
        factorial *= k;

    return factorial;
}
/*  End of tmpl_ULong_Factorial.                                              */

#endif
/*  End of #if ULONG_MAX == 0xFFFFFFFFU.                                      */
