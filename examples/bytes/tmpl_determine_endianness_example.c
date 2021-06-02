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
 *      gcc tmpl_determine_endianness_example.c -o test -ltmpl                *
 *  You must have libtmpl built prior so that we may link with -ltmpl. The    *
 *  file libtmpl.so must be in your path. It is placed in /usr/local/lib/     *
 *  if libtmpl was built with the make.sh file. /usr/local/lib/ should be in  *
 *  your path by default. This was tested with GCC, TCC, PCC, and LLVM's      *
 *  clang, and this worked as expected, with the exception that PCC did NOT   *
 *  have /usr/local/include/ in the path, so we need to add this via -I:      *
 *      pcc -I/usr/local/include/                                             *
 *          tmpl_determine_endianness_example.c -o test -ltmpl                *
 *  We can then run the executable via:                                       *
 *      ./test                                                                *
 *  Which yielded the following results:                                      *
 *      Little Endian                                                         *
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
 *  Date:       March 29, 2021                                                *
 ******************************************************************************/

/*  The puts function is found here.                                          */
#include <stdio.h>

/*  tmpl_Determine_Endianness is declared here.                               */
#include <libtmpl/include/tmpl_bytes.h>

/*  Function for testing the tmpl_Determine_Endianness function.              */
int main(void)
{
    /*  Declare a tmpl_Endian data type and compute the endianness.           */
    tmpl_Endian end = tmpl_Determine_Endianness();

    /*  Check the value of end and print the corresponding endianness.        */
    if (end == tmpl_LittleEndian)
        puts("Little Endian");
    else if (end == tmpl_MixedEndian)
        puts("Mixed Endian");
    else if (end == tmpl_BigEndian)
        puts("Big Endian");
    else
        puts("Unknown Endian");

    return 0;
}
/*  End of main.                                                              */

