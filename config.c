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
 *                                 config                                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file is used in both the Makefile and make.sh shell script when  *
 *      libtmpl is built. It creates the following files:                     *
 *          tmpl_config.h:                                                    *
 *              Contains endianness info, signed integer representation,      *
 *              float, double, and long double implementation, and whether    *
 *              or not libtmpl's libm is to be used, and whether functions    *
 *              should be inlined.                                            *
 *          tmpl_inttype.h:                                                   *
 *              Contains typedefs for fixed-width integers of size 8, 16, 32, *
 *              and 64 bits, if available.                                    *
 *          tmpl_limits.h:                                                    *
 *              Contains macros for the maximum values of integer types.      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard C library header file containing the fprintf function    *
 *          which we'll use to create the files mentioned above.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 10, 2021                                                *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/04/26: Ryan Maguire                                                  *
 *      Made the code more portable by allowing CHAR_BIT to be any value.     *
 *  2021/08/24: Ryan Maguire                                                  *
 *      Removed string.h dependency and simplified a bit.                     *
 *  2021/09/3:  Ryan Maguire                                                  *
 *      Added macro for floating-point endianness for IEEE-754 support.       *
 *  2021/09/8:  Ryan Maguire                                                  *
 *      Added test for long double precision.                                 *
 *  2022/01/03: Ryan Maguire                                                  *
 *      Added preprocessor checks for Windows users. The fopen command does   *
 *      not create a file on Windows if the string has forward-slash. Must    *
 *      use back-slash on Windows (which is dumb).                            *
 *      Added _CRT_SECURE_NO_DEPRECATE for Windows users since MSVC           *
 *      deprecated standard library functions (which is dumber).              *
 *  2022/01/11: Ryan Maguire                                                  *
 *      Added support for s390x big endian quadruple precision. This is how   *
 *      GCC implements long double on that architecture.                      *
 *  2022/02/01: Ryan Maguire                                                  *
 *      Added more general support for long double.                           *
 *  2022/12/21: Ryan Maguire                                                  *
 *      Added tmpl_limits.h. Removes limits.h from dependencies.              *
 ******************************************************************************/

/*  Avoid silly warning on Windows for using fopen. GNU/Linux, FreeBSD, and   *
 *  macOS have no such warnings for using standard library functions.         */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif

/*  The long long data type is available starting with C99. MSVC does not set *
 *  the __STDC_VERSION__ macro by default, but does have long long support.   *
 *  If the Makefile set the TMPL_SET_LONGLONG_FALSE macro, long long support  *
 *  is disabled regardless of whether the compiler supports it.               */
#if !defined(TMPL_SET_LONGLONG_FALSE) && \
    ((defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L))
#define TMPL_LONG_LONG_IS_AVAILABLE 1
#endif

/*  Needed for FILE data type and fprintf.                                    */
#include <stdio.h>

#include "config/tmpl_config_do_sqrt.h"
#include "config/tmpl_config_epsilon_float.h"
#include "config/tmpl_config_epsilon_double.h"
#include "config/tmpl_config_epsilon_ldouble.h"
#include "config/tmpl_config_check_widths.h"
#include "config/tmpl_config_make_config_h.h"

static int make_float_h(void)
{
    const long double feps = tmpl_float_epsilon();
    const long double deps = tmpl_double_epsilon();
    const long double leps = tmpl_ldouble_epsilon();

    const long double sqrt_feps = tmpl_do_sqrt(feps);
    const long double sqrt_deps = tmpl_do_sqrt(deps);
    const long double sqrt_leps = tmpl_do_sqrt(leps);

    const long double qurt_feps = tmpl_do_sqrt(sqrt_feps);
    const long double qurt_deps = tmpl_do_sqrt(sqrt_deps);
    const long double qurt_leps = tmpl_do_sqrt(sqrt_leps);

    FILE *fp = fopen("include/tmpl_float.h", "w");

    if (!fp)
        return -1;

    /*  Create the file include/tmpl_config.h and return.                     */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                  LICENSE                                   *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify           *\n");
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
    fprintf(fp, " *                                 tmpl_float                                 *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the config.c file. It provides macros         *\n");
    fprintf(fp, " *      for floating-point types like float, double, and long double.         *\n");
    fprintf(fp, " ******************************************************************************/\n\n");

    fprintf(fp, "#ifndef TMPL_FLOAT_H\n");
    fprintf(fp, "#define TMPL_FLOAT_H\n\n");

    fprintf(fp, "#define TMPL_DBL_EPS (%.24LE)\n", deps);
    fprintf(fp, "#define TMPL_FLT_EPS (%.24LEF)\n", feps);
    fprintf(fp, "#define TMPL_LDBL_EPS (%.24LEL)\n\n", leps);

    fprintf(fp, "#define TMPL_SQRT_DBL_EPS (%.24LE)\n", sqrt_deps);
    fprintf(fp, "#define TMPL_SQRT_FLT_EPS (%.24LEF)\n", sqrt_feps);
    fprintf(fp, "#define TMPL_SQRT_LDBL_EPS (%.24LEL)\n\n", sqrt_leps);

    fprintf(fp, "#define TMPL_QURT_DBL_EPS (%.24LE)\n", qurt_deps);
    fprintf(fp, "#define TMPL_QURT_FLT_EPS (%.24LEF)\n", qurt_feps);
    fprintf(fp, "#define TMPL_QURT_LDBL_EPS (%.24LEL)\n\n", qurt_leps);
    fprintf(fp, "#endif\n");

    fclose(fp);
    return 0;
}

/*  Function for creating include/tmpl_inttype.h.                             */
static int make_integer_h(void)
{
    /*  Open the file include/tmpl_inttype.h using fopen and give the file    *
     *  write permissions. If using Windows, we'll need to use backslashes.   *
     *  Forward slashes fail to create the file.                              */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    FILE *fp = fopen(".\\include\\tmpl_inttype.h", "w");
#else
    FILE *fp = fopen("./include/tmpl_inttype.h", "w");
#endif

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (!fp)
    {
        puts("Error Encountered: libtmpl\n"
             "    config.c\n"
             "fopen returned NULL for FILE *fp. Aborting.\n");
        return -1;
    }

    /*  We need to use the global value tmpl_uchar_width. Check that it has   *
     *  been computed already. If not, compute it.                            */
    if (!tmpl_all_widths_are_known)
        tmpl_check_widths();

    /*  Create the file include/tmpl_config.h and return.                     */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                  LICENSE                                   *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify           *\n");
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
    fprintf(fp, " *                                tmpl_inttype                                *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the config.c file. It provides macros         *\n");
    fprintf(fp, " *      for fixed-width integers for 8, 16, 32, and 64 bits, as well as       *\n");
    fprintf(fp, " *      typedefs, if such data types exist on your platform.                  *\n");
    fprintf(fp, " ******************************************************************************/\n\n");
    fprintf(fp, "#ifndef TMPL_INTTYPE_H\n");
    fprintf(fp, "#define TMPL_INTTYPE_H\n\n");
#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    fprintf(fp, "#define TMPL_HAS_LONGLONG 1\n\n");
#else
    fprintf(fp, "#define TMPL_HAS_LONGLONG 0\n\n");
#endif

#ifdef TMPL_SET_NO_INT
    fprintf(fp, "#define TMPL_HAS_8_BIT_INT 0\n");
    fprintf(fp, "#define TMPL_HAS_16_BIT_INT 0\n");
    fprintf(fp, "#define TMPL_HAS_32_BIT_INT 0\n");
    fprintf(fp, "#define TMPL_HAS_64_BIT_INT 0\n");

#else
/*  Else of #ifdef TMPL_SET_NO_INT.                                           */

    if (tmpl_uchar_width == 8)
    {
        fprintf(fp, "#define TMPL_HAS_8_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned char tmpl_UInt8;\n");
        fprintf(fp, "typedef signed char tmpl_SInt8;\n");
        fprintf(fp, "#define tmpl_UInt8_Trailing_Zeros TMPL_UCHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt8_Trailing_Zeros TMPL_CHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt8_Leading_Zeros TMPL_UCHAR_LEADING_ZEROS\n\n");
    }
    else
        fprintf(fp, "#define TMPL_HAS_8_BIT_INT 0\n\n");

    if (tmpl_uchar_width == 16)
    {
        fprintf(fp, "#define TMPL_HAS_16_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned char tmpl_UInt16;\n");
        fprintf(fp, "typedef signed char tmpl_SInt16;\n");
        fprintf(fp, "#define tmpl_UInt16_Trailing_Zeros TMPL_UCHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt16_Trailing_Zeros TMPL_CHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt16_Leading_Zeros TMPL_UCHAR_LEADING_ZEROS\n\n");
    }
    else if (tmpl_ushort_width == 16 && tmpl_number_of_bits_in_ushort == 16)
    {
        fputs("#define TMPL_HAS_16_BIT_INT 1\n", fp);
        fputs("typedef unsigned short int tmpl_UInt16;\n", fp);
        fputs("typedef signed short int tmpl_SInt16;\n", fp);
        fputs("#define tmpl_UInt16_Trailing_Zeros TMPL_USHORT_TRAILING_ZEROS\n", fp);
        fputs("#define tmpl_SInt16_Trailing_Zeros TMPL_SHORT_TRAILING_ZEROS\n", fp);
        fputs("#define tmpl_UInt16_Leading_Zeros TMPL_USHORT_LEADING_ZEROS\n\n", fp);
    }
    else if (tmpl_uint_width == 16 && tmpl_number_of_bits_in_uint == 16)
    {
        fputs("#define TMPL_HAS_16_BIT_INT 1\n", fp);
        fputs("typedef unsigned int tmpl_UInt16;\n", fp);
        fputs("typedef signed int tmpl_SInt16;\n", fp);
        fputs("#define tmpl_UInt16_Trailing_Zeros TMPL_UINT_TRAILING_ZEROS\n", fp);
        fputs("#define tmpl_SInt16_Trailing_Zeros TMPL_INT_TRAILING_ZEROS\n", fp);
        fputs("#define tmpl_UInt16_Leading_Zeros TMPL_UINT_LEADING_ZEROS\n\n", fp);
    }
    else
        fprintf(fp, "#define TMPL_HAS_16_BIT_INT 0\n\n");

    if (tmpl_uchar_width == 32)
    {
        fprintf(fp, "#define TMPL_HAS_32_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned char tmpl_UInt32;\n");
        fprintf(fp, "typedef signed char tmpl_SInt32;\n");
        fprintf(fp, "#define tmpl_UInt32_Trailing_Zeros TMPL_UCHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt32_Trailing_Zeros TMPL_CHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt32_Leading_Zeros TMPL_UCHAR_LEADING_ZEROS\n\n");
    }
    else if (tmpl_ushort_width == 32 && tmpl_number_of_bits_in_ushort == 32)
    {
        fprintf(fp, "#define TMPL_HAS_32_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned short int tmpl_UInt32;\n");
        fprintf(fp, "typedef signed short int tmpl_SInt32;\n");
        fprintf(fp, "#define tmpl_UInt32_Trailing_Zeros TMPL_USHORT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt32_Trailing_Zeros TMPL_SHORT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt32_Leading_Zeros TMPL_USHORT_LEADING_ZEROS\n\n");
    }
    else if (tmpl_uint_width == 32 && tmpl_number_of_bits_in_uint == 32)
    {
        fprintf(fp, "#define TMPL_HAS_32_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned int tmpl_UInt32;\n");
        fprintf(fp, "typedef signed int tmpl_SInt32;\n");
        fprintf(fp, "#define tmpl_UInt32_Trailing_Zeros TMPL_UINT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt32_Trailing_Zeros TMPL_INT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt32_Leading_Zeros TMPL_UINT_LEADING_ZEROS\n\n");
    }
    else if (tmpl_ulong_width == 32 && tmpl_number_of_bits_in_ulong == 32)
    {
        fprintf(fp, "#define TMPL_HAS_32_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned long int tmpl_UInt32;\n");
        fprintf(fp, "typedef signed long int tmpl_SInt32;\n");
        fprintf(fp, "#define tmpl_UInt32_Trailing_Zeros TMPL_ULONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt32_Trailing_Zeros TMPL_LONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt32_Leading_Zeros TMPL_ULONG_LEADING_ZEROS\n\n");
    }
    else
        fprintf(fp, "#define TMPL_HAS_32_BIT_INT 0\n\n");

    if (tmpl_uchar_width == 64)
    {
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned char tmpl_UInt64;\n");
        fprintf(fp, "typedef signed char tmpl_SInt64;\n");
        fprintf(fp, "#define tmpl_UInt64_Trailing_Zeros TMPL_UCHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt64_Trailing_Zeros TMPL_CHAR_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt64_Leading_Zeros TMPL_UCHAR_LEADING_ZEROS\n\n");
    }
    else if (tmpl_ushort_width == 64 && tmpl_number_of_bits_in_ushort == 64)
    {
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned short int tmpl_UInt64;\n");
        fprintf(fp, "typedef signed short int tmpl_SInt64;\n");
        fprintf(fp, "#define tmpl_UInt64_Trailing_Zeros TMPL_USHORT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt64_Trailing_Zeros TMPL_SHORT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt64_Leading_Zeros TMPL_USHORT_LEADING_ZEROS\n\n");
    }
    else if (tmpl_uint_width == 64 && tmpl_number_of_bits_in_uint == 64)
    {
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned int tmpl_UInt64;\n");
        fprintf(fp, "typedef signed int tmpl_SInt64;\n");
        fprintf(fp, "#define tmpl_UInt64_Trailing_Zeros TMPL_UINT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt64_Trailing_Zeros TMPL_INT_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt64_Leading_Zeros TMPL_UINT_LEADING_ZEROS\n\n");
    }
    else if (tmpl_ulong_width == 64 && tmpl_number_of_bits_in_ulong == 64)
    {
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned long int tmpl_UInt64;\n");
        fprintf(fp, "typedef signed long int tmpl_SInt64;\n");
        fprintf(fp, "#define tmpl_UInt64_Trailing_Zeros TMPL_ULONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt64_Trailing_Zeros TMPL_LONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt64_Leading_Zeros TMPL_ULONG_LEADING_ZEROS\n\n");
    }

#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    else if (tmpl_ullong_width == 64 && tmpl_number_of_bits_in_ullong == 64)
    {
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 1\n");
        fprintf(fp, "typedef unsigned long long int tmpl_UInt64;\n");
        fprintf(fp, "typedef signed long long int tmpl_SInt64;\n");
        fprintf(fp, "#define tmpl_UInt64_Trailing_Zeros TMPL_ULLONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_SInt64_Trailing_Zeros TMPL_LLONG_TRAILING_ZEROS\n");
        fprintf(fp, "#define tmpl_UInt64_Leading_Zeros TMPL_ULLONG_LEADING_ZEROS\n\n");
    }
#endif
    else
        fprintf(fp, "#define TMPL_HAS_64_BIT_INT 0\n\n");

#endif
/*  End of #ifdef TMPL_SET_NO_INT.                                            */

    fprintf(fp, "#endif\n");
    return 0;
}

/*  Function for determining the max powers of unsigned integer types.        */
static int make_limits_h(void)
{
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    FILE *fp = fopen(".\\include\\tmpl_limits.h", "w");
#else
    FILE *fp = fopen("./include/tmpl_limits.h", "w");
#endif

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (!fp)
    {
        puts("Error Encountered: libtmpl\n"
             "    config.c\n"
             "fopen returned NULL for FILE *fp. Aborting.\n");
        return -1;
    }

    /*  We need to use the global value tmpl_uchar_width. Check that it has   *
     *  been computed already. If not, compute it.                            */
    if (!tmpl_all_widths_are_known)
        tmpl_check_widths();

    /*  Create the file include/tmpl_config.h and return.                     */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                  LICENSE                                   *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify           *\n");
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
    fprintf(fp, " *                                 tmpl_limits                                *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the config.c file. It provides macros         *\n");
    fprintf(fp, " *      for unsigned integers, providing their largest possible values.       *\n");
    fprintf(fp, " ******************************************************************************/\n\n");
    fprintf(fp, "#ifndef TMPL_LIMITS_H\n");
    fprintf(fp, "#define TMPL_LIMITS_H\n\n");

    fprintf(fp, "#define TMPL_UCHAR_BIT %u\n", tmpl_uchar_width);
    fprintf(fp, "#define TMPL_USHORT_BIT %u\n", tmpl_ushort_width);
    fprintf(fp, "#define TMPL_UINT_BIT %u\n", tmpl_uint_width);
    fprintf(fp, "#define TMPL_ULONG_BIT %u\n", tmpl_ulong_width);

#ifdef TMPL_LONG_LONG_IS_AVAILABLE
    fprintf(fp, "#define TMPL_ULLONG_BIT %u\n", tmpl_ullong_width);
#endif

    fprintf(fp, "\n#endif\n");
    return 0;
}

/*  Function for creating tmpl_config.h and tmpl_inttype.h.                   */
int main(void)
{
    if (make_config_h() < 0)
        return -1;
    if (make_integer_h() < 0)
        return -1;
    if (make_limits_h() < 0)
        return -1;
    if (make_float_h() < 0)
        return -1;
    return 0;
}
/*  End of main.                                                              */
