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
 *      gcc tmpl_swap_bytes_example.c -o test -ltmpl                          *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/ tmpl_swap_bytes_example.c -o test -ltmpl    *
 *  We can the run the executable via:                                        *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      Before:                                                               *
 *          c0 = 31                                                           *
 *          c1 = 238                                                          *
 *      After:                                                                *
 *          c0 = 238                                                          *
 *          c1 = 31                                                           *
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
 *  Date:       March 10, 2021                                                *
 ******************************************************************************/

/*  The printf function is found here.                                        */
#include <stdio.h>

/*  tmpl_Swap_Bytes is declared here.                                         */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Swap_Bytes function and showing basic use.  */
int main(void)
{
    /*  Declare two unsigned char variables to test.                          */
    unsigned char c0, c1;

    /*  Set the char values to whatever you'd like.                           */
    c0 = 0x1FU;
    c1 = 0xEEU;

    /*  Print the result before the swap.                                     */
    printf("Before:\n\tc0 = %u\n\tc1 = %u\n", c0, c1);

    /*  Swap the bytes. tmpl_Swap_Bytes wants pointers to char values, so we  *
     *  need to grab the addresses of c0 and c1 via &c0 and &c1. Moreover, it *
     *  wants pointers to SIGNED char values, so we need to perform a cast.   *
     *  This is not necessary on most compilers, but with pedantic compiler   *
     *  warnings you may get something like -Wpointer-sign warnings.          *
     *  We cast the unsigned char pointer &c0 to a char pointer via           *
     *  (char *) &c0. Similarly for c1.                                       */
    tmpl_Swap_Bytes((char *)&c0, (char *)&c1);

    /*  Print the new results.                                                */
    printf("After:\n\tc0 = %u\n\tc1 = %u\n", c0, c1);

    return 0;
}
/*  End of main.                                                              */

