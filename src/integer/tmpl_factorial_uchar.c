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
 *                            tmpl_factorial_uchar                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the factorial function for unsigned char integers.           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UChar_Factorial                                                  *
 *  Purpose:                                                                  *
 *      Computes the factorial function, n! = n * (n-1) * ... * 2 * 1.        *
 *  Arguments:                                                                *
 *      n (unsigned char):                                                    *
 *          An integer, the independent variable for n!.                      *
 *  Output:                                                                   *
 *      n! (unsigned char):                                                   *
 *          The factorial of n.                                               *
 *  8-bit / 16-bit / 32-bit / 64-bit Version:                                 *
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
 *  1.) tmpl_integer.h:                                                       *
 *          Header file with the functions prototype.                         *
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

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_integer.h>

/*  The TMPL_UCHAR_BIT macro is found here.                                   */
#include <libtmpl/include/tmpl_limits.h>

/*  8-bit unsigned char has a max value of 255.                               */
#if TMPL_UCHAR_BIT == 8

/*  For n > 5, 8-bit char, n! overflows. Create lookup table of a few values. */
static const unsigned char tmpl_uchar_factorial_values[6] = {
    0x01U, 0x01U, 0x02U, 0x06U, 0x18U, 0x78U
};

/*  8-bit unsigned char factorial function.                                   */
unsigned char tmpl_UChar_Factorial(unsigned char n)
{
    /*  For 8-bit unsigned char n! overflows for n > 5. Return 0 if this is   *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 0x05U)
        return 0x00U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uchar_factorial_values[n];
}
/*  End of tmpl_UChar_Factorial.                                              */

/*  16-bit unsigned char has a max value of 65,535.                           */
#elif TMPL_UCHAR_BIT == 16

/******************************************************************************
 *                               16-Bit Version                               *
 ******************************************************************************/

/*  For n > 8, and for 16-bit unsigned char, n! overflows. Pre-compute the   *
 *  first 9 values (0 <= n <= 8) and use this as a lookup table.              */
static const unsigned char tmpl_uchar_factorial_values[9] = {
    0x0001U, 0x0001U, 0x0002U, 0x0006U,
    0x0018U, 0x0078U, 0x02D0U, 0x13B0U, 0x9D80U
};

/*  16-bit unsigned char factorial function.                                  */
unsigned char tmpl_UChar_Factorial(unsigned char n)
{
    /*  For 16-bit unsigned char n! overflows for n > 8. Return 0 if this is  *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 0x08U)
        return 0x00U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uchar_factorial_values[n];
}
/*  End of tmpl_UChar_Factorial.                                              */

/*  32-bit unsigned char has a max value of 4,294,967,295.                    */
#elif TMPL_UCHAR_BIT == 32

/******************************************************************************
 *                               32-Bit Version                               *
 ******************************************************************************/

/*  For n > 12, and for 32-bit unsigned char, n! overflows. Pre-compute the   *
 *  first 9 values (0 <= n <= 8) and use this as a lookup table.              */
static const unsigned char tmpl_uchar_factorial_values[13] = {
    0x00000001U, 0x00000001U, 0x00000002U, 0x00000006U,
    0x00000018U, 0x00000078U, 0x000002D0U, 0x000013B0U,
    0x00009D80U, 0x00058980U, 0x00375F00U, 0x02611500U, 0x1C8CFC00U
};

/*  32-bit unsigned char factorial function.                                  */
unsigned char tmpl_UChar_Factorial(unsigned char n)
{
    /*  For 32-bit unsigned char n! overflows for n > 12. Return 0 if this is  *
     *  the case. n! is never zero for non-negative integers, so this         *
     *  indicates an error to the caller.                                     */
    if (n > 0x0CU)
        return 0x00U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uchar_factorial_values[n];
}
/*  End of tmpl_UChar_Factorial.                                              */

/*  64-bit unsigned char has a max value of 18,446,744,073,709,551,615.       */
#elif TMPL_UCHAR_BIT == 64

/******************************************************************************
 *                               64-Bit Version                               *
 ******************************************************************************/

/*  For n > 20, and for 64-bit unsigned char, n! overflows. Pre-compute the   *
 *  first 21 values (0 <= n <= 20) and use this as a lookup table.            */
static const unsigned char tmpl_uchar_factorial_values[21] = {
    0x0000000000000001U, 0x0000000000000001U, 0x0000000000000002U,
    0x0000000000000006U, 0x0000000000000018U, 0x0000000000000078U,
    0x00000000000002D0U, 0x00000000000013B0U, 0x0000000000009D80U,
    0x0000000000058980U, 0x0000000000375F00U, 0x0000000002611500U,
    0x000000001C8CFC00U, 0x000000017328CC00U, 0x000000144C3B2800U,
    0x0000013077775800U, 0x0000130777758000U, 0x0001437EEECD8000U,
    0x0016BEECCA730000U, 0x01B02B9306890000U, 0x21C3677C82B40000U,
};

/*  64-bit unsigned char factorial function.                                  */
unsigned char tmpl_UChat_Factorial(unsigned char n)
{
    /*  For 64-bit unsigned char n! overflows for n > 20. Return 0 if this    *
     *  is the case. n! is never zero for non-negative integers, so this      *
     *  indicates an error to the caller.                                     */
    if (n > 0x14U)
        return 0x00U;

    /*  Otherwise, return n! from the precomputed table above.                */
    else
        return tmpl_uchar_factorial_values[n];
}
/*  End of tmpl_UChar_Factorial.                                              */

/*  Lastly, a portable version. No assumption on width is made.               */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Char must be at least 8 bits wide. Precompute the first 6 values of n!.   */
static const unsigned char tmpl_uchar_factorial_values[6] = {
    0x01U, 0x01U, 0x02U, 0x06U, 0x18U, 0x78U
};

/*  Portable factorial function for unsigned char.                            */
unsigned char tmpl_UChart_Factorial(unsigned char n)
{
    /*  Declare necessary variable. C89 requires this at the top.             */
    unsigned char k, factorial;

    /*  For 0 <= n <= 5 we can use the lookup table above.                    */
    if (n < 0x06U)
        return tmpl_uchar_factorial_values[n];

    /*  Otherwise, set factorial to the largest value in the table. We will   *
     *  compute using n! = n*(n-1)*...*5!.                                    */
    factorial = tmpl_uchar_factorial_values[5];

    /*  For 6 <= k <= n, multiply the result by k. This method has the        *
     *  unfortunate disadvantage of not detecting overflows.                  */
    for (k = 0x06U; k <= n; ++k)
        factorial *= k;

    return factorial;
}
/*  End of tmpl_UChar_Factorial.                                              */

#endif
/*  End of #if TMPL_UCHAR_BIT == 8.                                           */
