/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *  This alternate example of tmpl_Swap_Most_Significant_Bit_2 should work on *
 *  any platform/implementation, regardless of the size of CHAR_BIT, so long  *
 *  as an integer data type is provided that has sizeof(type) = 2. This is    *
 *  usually a short, but on exotic platforms (such as 36-bit char and 72-bit  *
 *  long) this need not be the case. If no integer data type is 2 char's long *
 *  this example will simply print this fact out and exit.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       April 6, 2021                                                 *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Most_Significant_Bit_2 is declared here.                        */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Swap_Most_Significant_Bit_2 function and    *
 *  showing basic use.                                                        */
int main(void)
{
    /*  We need to probe the various data types and try and find one that has *
     *  sizeof(type) = 2. This is usually a short int, but can vary on other  *
     *  platforms, and may not exist at all on some. If we can't find an      *
     *  integer data type with sizeof equal to 2, we'll print this out.       */
    if (sizeof(unsigned short int) == 2)
    {
        union {
            unsigned short int x;
            char c[2];
        } u = { 0xFF00 };

        /*  Print the result before the swap.                                 */
        printf("Before: %u\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_2(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %u\n", u.x);
    }
    else if (sizeof(unsigned int) == 2)
    {
        union {
            unsigned int x;
            char c[2];
        } u = { 0xFF00 };

        /*  Print the result before the swap.                                 */
        printf("Before: %u\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_2(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %u\n", u.x);
    }
    else if (sizeof(unsigned long int) == 2)
    {
        union {
            unsigned long int x;
            char c[2];
        } u = { 0xFF00 };

        /*  Print the result before the swap.                                 */
        printf("Before: %lu\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_2(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %lu\n", u.x);
    }

    /*  The long long data type is only defined in C99 and higher. We should  *
     *  check for compliance with the C99 standard before trying to examine   *
     *  the long long data type, otherwise we may get a compiler error.       */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    else if (sizeof(unsigned long long int) == 2)
    {
        union {
            unsigned long long int x;
            char c[2];
        } u = { 0xFF00 };

        /*  Print the result before the swap.                                 */
        printf("Before: %Lu\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_2(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %Lu\n", u.x);
    }
#endif

    /*  If we get here, there is no integer data type that is 2 char's wide.  *
     *  Print this and exit the function.                                     */
    else
        puts("Could not find integer type with sizeof = 4");

    return 0;
}
/*  End of main.                                                              */

