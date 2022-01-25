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
 *  To compile, simply run:                                                   *
 *      gcc tmpl_swap_most_significant_bit_4_example.c -o test -ltmpl         *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/                                             *
 *          tmpl_swap_most_significant_bit_4_example.c -o test -ltmpl         *
 *  We can then run the executable via:                                       *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      Before: 4278190080                                                    *
 *      After: 255                                                            *
 *  This was tested on Debian 10 (Buster) GNU/Linux with gcc, tcc, pcc, and   *
 *  clang from the Debian 10 main repository. Version numbers are:            *
 *      gcc: Debian 8.3.0-6                                                   *
 *      pcc: Portable C Compiler 1.2.0.DEVEL 20181216 for x86_64-pc-linux-gnu *
 *      tcc: version 0.9.27 (x86_64 Linux)                                    *
 *      clang: version 7.0.1-8+deb10u2 (tags/RELEASE_701/final)               *
 *  This was also tested on Debian 11 alpha-3 (Bullseye) with the following:  *
 *      gcc: Debian 10.2.1-6                                                  *
 *      pcc: Portable C Compiler 1.2.0.DEVEL 20200630 for x86_64-pc-linux-gnu *
 *      tcc: tcc version 0.9.27 (x86_64 Linux)                                *
 *      clang: Debian clang version 11.0.1-2                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 12, 2021                                                *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Most_Significant_Bit_4 is declared here.                        */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Swap_Most_Significant_Bit_4 function and    *
 *  showing basic use.                                                        */
int main(void)
{
    /*  We need to probe the various data types and try and find one that has *
     *  sizeof(type) = 4. This is usually an int, but can vary on other       *
     *  platforms, and may not exist at all on some. If we can't find an      *
     *  integer data type with sizeof equal to 4, we'll print this out.       */
    if (sizeof(unsigned int) == 4)
    {
        union {
            unsigned int x;
            char c[4];
        } u = { 0xFF000000 };

        /*  Print the result before the swap.                                 */
        printf("Before: %u\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_4(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %u\n", u.x);
    }
    else if (sizeof(unsigned long int) == 4)
    {
        union {
            unsigned long int x;
            char c[4];
        } u = { 0xFF000000 };

        /*  Print the result before the swap.                                 */
        printf("Before: %lu\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_4(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %lu\n", u.x);
    }

    /*  The long long data type is only defined in C99 and higher. We should  *
     *  check for compliance with the C99 standard before trying to examine   *
     *  the long long data type, otherwise we may get a compiler error.       */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    else if (sizeof(unsigned long long int) == 4)
    {
        union {
            unsigned long long int x;
            char c[4];
        } u = { 0xFF000000 };

        /*  Print the result before the swap.                                 */
        printf("Before: %llu\n", u.x);

        /*  Swap the most significant bit using the char array in the union.  */
        tmpl_Swap_Most_Significant_Bit_4(u.c);

        /*  Print the result after the swap.                                  */
        printf("After: %llu\n", u.x);
    }
#endif

    /*  If we get here, there is no integer data type that is 4 char's wide.  *
     *  Print this and exit the function.                                     */
    else
        puts("Could not find integer type with sizeof = 4");

    return 0;
}
/*  End of main.                                                              */

