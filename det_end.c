/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                                det_end                                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file is used in both the Makefile and make.sh shell script when  *
 *      libtmpl is built. It determines the endianness of your platform and   *
 *      creates the file include/tmpl_endianness.h in the process. This file  *
 *      is NOT directly part of libtmpl.                                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) limits.h:                                                             *
 *          Standard C library header file containing the macro CHAR_BITS,    *
 *          which stores the number of bits in a byte.                        *
 *  2.) stdio.h:                                                              *
 *          Standard C library header file containing the fprintf function    *
 *          which we'll use to create the file include/tmpl_endianness.h.     *
 *  3.) string.h:                                                             *
 *          Standard C library header file containing strcpy which allows us  *
 *          to copy strings into char arrays.                                 *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/04/26: Ryan Maguire                                                  *
 *      Made the code more portable by allowing CHAR_BIT to be any value.     *
 ******************************************************************************/

/*  Macros for determining the size of integer data types found here. In      *
 *  particular, the macro CHAR_BIT is here telling us how many bits in a byte.*/
#include <limits.h>

/*  Needed for FILE data type and fprintf.                                    */
#include <stdio.h>

/*  Needed for strcpy.                                                        */
#include <string.h>

/*  Function for creating include/tmpl_endianness.h.                          */
int main(void)
{
    /*  We'll use a union between an unsigned long int and an unsigned char   *
     *  array with as many elements as there are bytes in an unsigned long    *
     *  int. This is usually either 8 (unix-based, i.e. GNU, Linux, FreeBSD,  *
     *  macOS), or 4 (Microsoft Windows), but the value is not specified in   *
     *  the C standard.                                                       */
    union {
        unsigned long int n;
        unsigned char arr[sizeof(unsigned long int)];
    } e;

    /*  n is for indexing and pow keeps track of the power of an integer.     */
    unsigned long int n, pow;

    /*  We're printing the results to include/tmpl_endianness.h, so we'll     *
     *  need a char array to store the string.                                */
    char end_str[48];

    /*  And lastly, open the file include/tmpl_endianness.h using fopen and   *
     *  give the file write permissions.                                      */
    FILE *fp = fopen("./include/tmpl_endianness.h", "w");

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (fp == NULL)
    {
        puts("Error Encountered: libtmpl\n"
             "    det_end.c\n"
             "fopen returned NULL for FILE *fp. Aborting.\n");
        return -1;
    }

    /*  The idea is as follows. Create the integer 76543210, store this in the*
     *  unsigned long int part of our union, and then check the array part to *
     *  see which element is 0. This would work if computers are base 10, but *
     *  they usually use base 2, base 8, or base 16. Letting N be the base,   *
     *  we'll store the number 7*N^7 + 6*N^6 + ... + 2*N^2 + 1*N + 0. The     *
     *  array will then be:                                                   *
     *      ---------------------------------                                 *
     *      | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |                                 *
     *      ---------------------------------                                 *
     *  This is assuming sizeof(unsigned long int) = 8. If it is some other   *
     *  value, the array will be 0 up to that number. We'll start by          *
     *  initializing the unsigned long int part of the union to 0.            */
    e.n = 0UL;

    /*  We need to set pow to 2^(number of bits in a byte). This number is    *
     *  found in limits.h as CHAR_BIT. We're going to write out number as     *
     *  7 * pow^7 + 6 * pow^6 + ... + 2 * pow^2 + pow + 0. If we somehow had  *
     *  a base-10 computer, this would be                                     *
     *  7*10^7 + 6*10^6 + ... + 2*10^2 + 1*10 + 0 = 76543210.                 *
     *  We want this in base 2^CHAR_BIT. We can compute 2^CHAR_BIT quickly    *
     *  using bitwise operators. 1 << N is the number 1000...000 in binary    *
     *  with N 0's. This would be the number 2^N in decimal, which is what    *
     *  we want. We compute 2^CHAR_BIT via 1UL << CHAR_BIT. UL means unsigned *
     *  long, which is the data type of pow.                                  */
    pow = 1UL << CHAR_BIT;

    /*  Write out 76543210 in base 2^CHAR_BIT by adding. That is:             *
     *  76543210 = 7*pow^7 + ... + 2*pow^2 + 1*pow + 0. Loop through and add. */
    for (n = 1; n < sizeof(unsigned long int); ++n)
    {
        e.n += n * pow;

        /*  From pow^k we can get pow^(k+1) by shifting the "decimal" point   *
         *  CHAR_BIT to the right. In decimal, if we had 100 and want 1000,   *
         *  we'd write 100.00, shift the decimal to the right, and get 1000.0.*
         *  Writing pow = pow << CHAR_BIT is the base 2^CHAR_BIT equivalent.  */
        pow = pow << CHAR_BIT;
    }

    /*  We now have 76543210 in the array part of the union (or n-1...210 if  *
     *  sizeof(unsigned long int) = n). If the zeroth entry of the array is   *
     *  0, we have little endian. If it is n-1, we have big endian. Anything  *
     *  between 0 and n-1 is mixed endian, and any other result is unknown.   *
     *  There is one very rare case that needs to be handled. If              *
     *  sizeof(unsigned long int) = 1, the we can't parse the array. If this  *
     *  is true, your computer is very strange, and we'll return unknown. We  *
     *  use the strcpy function from string.h to copy the string into our     *
     *  end_str char array.                                                   */
    if (sizeof(unsigned long int) == 1)
        strcpy(end_str, "__TMPL_UNKNOWN_ENDIAN__");
    else if (e.arr[0] == 0)
        strcpy(end_str, "__TMPL_LITTLE_ENDIAN__");
    else if (e.arr[0] == (sizeof(unsigned long int) - 1))
        strcpy(end_str, "__TMPL_BIG_ENDIAN__");
    else if ((0 < e.arr[0]) && (e.arr[0] < (sizeof(unsigned long int) - 1)))
        strcpy(end_str, "__TMPL_MIXED_ENDIAN__");
    else
        strcpy(end_str, "__TMPL_UNKNOWN_ENDIAN__");

    /*  Create the file include/tmpl_endianness.h and return.                 */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                 LICENSE                                    *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify it        *\n");
    fprintf(fp, " *  it under the terms of the GNU General Public License as published by      *\n");
    fprintf(fp, " *  the Free Software Foundation, either version 3 of the License, or         *\n");
    fprintf(fp, " *  (at your option) any later version.                                       *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is distributed in the hope that it will be useful,                *\n");
    fprintf(fp, " *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *\n");
    fprintf(fp, " *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *\n");
    fprintf(fp, " *  GNU General Public License for more details.                              *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  You should have received a copy of the GNU General Public License         *\n");
    fprintf(fp, " *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *                              tmpl_endianness                               *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the det_enc.c file. It provides the macro     *\n");
    fprintf(fp, " *      __TMPL_ENDIANNESS__ which is used in various functions where the code *\n");
    fprintf(fp, " *      is endian specific.                                                   *\n");
    fprintf(fp, " ******************************************************************************/\n");
    fprintf(fp, "#ifndef TMPL_ENDIANNESS_H\n");
    fprintf(fp, "#define TMPL_ENDIANNESS_H\n\n");
    fprintf(fp, "#define TMPL_BIG_ENDIAN 0\n");
    fprintf(fp, "#define TMPL_LITTLE_ENDIAN 1\n");
    fprintf(fp, "#define TMPL_MIXED_ENDIAN 2\n");
    fprintf(fp, "#define TMPL_UNKNOWN_ENDIAN 3\n\n");
    fprintf(fp, "#define TMPL_ENDIAN %s\n\n", end_str);
    fprintf(fp, "#endif\n");
    return 0;
}
/*  End of main.                                                              */

