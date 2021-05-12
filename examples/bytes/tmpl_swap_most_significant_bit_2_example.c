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
 *      gcc tmpl_swap_most_significant_bit_2_example.c -o test -ltmpl         *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/                                             *
 *          tmpl_swap_most_significant_bit_2_example.c -o test -ltmpl         *
 *  We can the run the executable via:                                        *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      Before: 65280                                                         *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       March 12, 2021                                                *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Most_Significant_Bit_2 is declared here.                        */
#include <libtmpl/include/tmpl_bytes.h>

/*  16-bit and 32-bit fixed-width integer data types typedef'd here.          */
#include <libtmpl/include/tmpl_integer.h>

/*  We'll need the macro CHAR_BIT from limits.h to see how big a char is.     *
 *  This is almost universally always 8 bits, but it can be 16 bits on        *
 *  handheld calculators, and 12-bits on other strange devices. For           *
 *  portability it never hurts to check.                                      */
#include <limits.h>

/*  Function for testing the tmpl_Swap_Most_Significant_Bit_2 function and    *
 *  showing basic use.                                                        */
int main(void)
{
    /*  Based on the size of a char, create a union with a char array and     *
     *  either a 16-bit integer, or a 32-bit integer. If CHAR_BIT is neither  *
     *  8 nor 16, abort the program.                                          */
#if CHAR_BIT == 8
    union {
        tmpl_uint16 x;
        char c[2];
    } u = { 0xFF00 };
#elif CHAR_BIT == 16
    union {
        tmpl_uint32 x;
        char c[2];
    } u = { 0xFFFF0000 };
#else
    puts("CHAR_BIT is neither 8 nor 16. Aborting.");
    return 0;
#endif

    /*  Print the result before the swap.                                     */
    printf("Before: %u\n", u.x);

    /*  Swap the most significant bit using the char array inside the union.  */
    tmpl_Swap_Most_Significant_Bit_2(u.c);

    /*  Print the result after the swap.                                      */
    printf("After: %u\n", u.x);

    return 0;
}
/*  End of main.                                                              */

