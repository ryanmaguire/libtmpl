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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************/

/*  Macros for determining the size of integer data types found here.         */
#include <limits.h>

/*  Needed for FILE data type and fprintf.                                    */
#include <stdio.h>

/*  Needed for strcpy.                                                        */
#include <string.h>

/*  Check for C99 support with stdint.h to typedef fixed-width integers.      */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <stdint.h>

typedef uint32_t det_end_uint32;
typedef uint64_t det_end_uint64;

#else

/*  Without stdint.h support we need to probe various integer types to see if *
 *  there exist 32 and 64 bit integers. This is NOT required in C89/C90.      *
 *  When tested on macOS, GNU/Linux, and FreeBSD, int and long int gave       *
 *  32-bit and 64-bit integers, respectively. On Microsoft Windows, using     *
 *  MSVC, int and long long int corresponded to 32-bit and 64-bit,            *
 *  respectively. In all compilers tested (clang, gcc, pcc, tcc, MSVC) this   *
 *  file was able to create include/tmpl_endianness.h successfully.           */

#if USHRT_MAX == 0xFFFFFFFF
typedef short unsigned int det_end_uint32;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int det_end_uint32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef long unsigned int det_end_uint32;
#elif define(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFF
typedef long long unsigned int det_end_uint32;
#else
#error "libtmpl: No 32-bit integer type found."
#endif

#if USHRT_MAX == 0xFFFFFFFFFFFFFFFF
typedef short unsigned int det_end_uint64;
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned int det_end_uint64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long unsigned int det_end_uint64;
#elif defined(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long long unsigned int det_end_uint64;
#else
#error "libtmpl: No 64-bit integer type found."
#endif

#endif


int main(void)
{
    enum end_type {
        __tmpl_little_end,
        __tmpl_big_end,
        __tmpl_mixed_end,
        __tmpl_unknown_end
    } end;

    FILE *fp = fopen("./include/tmpl_endianness.h", "w");
    char end_str[48];

    if (fp == NULL)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "\tdet_end.c\n"
            "fopen returned NULL for FILE *fp. Aborting.\n"
        );
        return -1;
    }

    if (CHAR_BIT == 8)
    {
        union {
            det_end_uint32 i;
            char c[4];
        } e = { 0x01020304 };

        if (e.c[0] == 0x01)
            end = __tmpl_big_end;
        else if (e.c[0] == 0x04)
            end = __tmpl_little_end;
        else if ((e.c[0] == 0x02) || (e.c[0] = 0x03))
            end = __tmpl_mixed_end;
        else
            end = __tmpl_unknown_end;
    }
    else if (CHAR_BIT == 16)
    {
        union {
            det_end_uint64 i;
            char c[4];
        } e = { 0x0001000200030004 };

        if (e.c[0] == 0x0001)
            end = __tmpl_big_end;
        else if (e.c[0] == 0x0004)
            end = __tmpl_little_end;
        else if ((e.c[0] == 0x0002) || (e.c[0] = 0x0003))
            end = __tmpl_mixed_end;
        else
            end = __tmpl_unknown_end;
    }
    else
        end = __tmpl_unknown_end;

    if (end == __tmpl_little_end)
        strcpy(end_str, "__TMPL_LITTLE_ENDIAN__");
    else if (end == __tmpl_big_end)
        strcpy(end_str, "__TMPL_BIG_ENDIAN__");
    else if (end == __tmpl_mixed_end)
        strcpy(end_str, "__TMPL_MIXED_ENDIAN__");
    else
        strcpy(end_str, "__TMPL_UNKNOWN_ENDIAN__");

    fprintf(fp,"/******************************************************************************\n");
    fprintf(fp," *                                 LICENSE                                    *\n");
    fprintf(fp," ******************************************************************************\n");
    fprintf(fp," *  This file is part of libtmpl.                                             *\n");
    fprintf(fp," *                                                                            *\n");
    fprintf(fp," *  libtmpl is free software: you can redistribute it and/or modify it        *\n");
    fprintf(fp," *  it under the terms of the GNU General Public License as published by      *\n");
    fprintf(fp," *  the Free Software Foundation, either version 3 of the License, or         *\n");
    fprintf(fp," *  (at your option) any later version.                                       *\n");
    fprintf(fp," *                                                                            *\n");
    fprintf(fp," *  libtmpl is distributed in the hope that it will be useful,                *\n");
    fprintf(fp," *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *\n");
    fprintf(fp," *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *\n");
    fprintf(fp," *  GNU General Public License for more details.                              *\n");
    fprintf(fp," *                                                                            *\n");
    fprintf(fp," *  You should have received a copy of the GNU General Public License         *\n");
    fprintf(fp," *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *\n");
    fprintf(fp," ******************************************************************************\n");
    fprintf(fp," *                              tmpl_endianness                               *\n");
    fprintf(fp," ******************************************************************************\n");
    fprintf(fp," *  Purpose:                                                                  *\n");
    fprintf(fp," *      This file is created by the det_enc.c file. It provides the macro     *\n");
    fprintf(fp," *      __TMPL_ENDIANNESS__ which is used in various functions where the code *\n");
    fprintf(fp," *      is endian specific.                                                   *\n");
    fprintf(fp," ******************************************************************************/\n");
    fprintf(fp,"#ifndef __TMPL_ENDIANNESS_H__\n");
    fprintf(fp,"#define __TMPL_ENDIANNESS_H__\n\n");
    fprintf(fp,"#define __TMPL_BIG_ENDIAN__ 0\n");
    fprintf(fp,"#define __TMPL_LITTLE_ENDIAN__ 1\n");
    fprintf(fp,"#define __TMPL_MIXED_ENDIAN__ 2\n");
    fprintf(fp,"#define __TMPL_UNKNOWN_ENDIAN__ 3\n\n");
    fprintf(fp,"#define __TMPL_ENDIAN__ %s\n\n", end_str);
    fprintf(fp,"#endif\n");
    return 0;
}

