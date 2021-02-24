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
 *                               tmpl_integer                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Typedefs fixed-width integer data types in an attempt to provide      *
 *      portability for C89/C90 compliant compilers, but also C99, C11, and   *
 *      C18 compilers.                                                        *
 *  NOTES:                                                                    *
 *      If the __TMPL_USE_C99_STDINT_H__ macro, defined in tmpl_config.h, is  *
 *      set to 1, then it is assumed your compiler supports stdint.h and      *
 *      libtmpl will typedef the data types found there. Setting this macro   *
 *      to 1 without stdint.h support will result in the compiler aborting    *
 *      with error.                                                           *
 *                                                                            *
 *      If __TMPL_USE_C99_STDINT_H__ is set to 0, the code attempts to parse  *
 *      some of the macros defined in limits.h to see if any integer data     *
 *      types are 32 or 64 bit. While this is likely the case, it is not      *
 *      required by the C89/C90 standard. If the compiler fails, you may need *
 *      to adjust the settings in tmpl_config.h or use a compiler that        *
 *      supports the C99 standard (GCC, clang, and MSVC do).                  *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 17, 2021                                             *
 ******************************************************************************/

/*  include guard to prevent including this file twice.                       */
#ifndef __TMPL_INTEGER_H__
#define __TMPL_INTEGER_H__

/*  __TMPL_USING_C99_STDINT_H__ macro is defined here.                        */
#include <libtmpl/include/tmpl_config.h>

/*  Macros for determining the size of integer data types found here.         */
#include <limits.h>

/*  This macro is defined in tmpl_config.h. It is used for deciding if we     *
 *  should use the C99 stdint.h header file, which is required to contain     *
 *  fixed-width 32-bit and 64-bit integer data types, or if we should try to  *
 *  use strict C89/C90 compliant code to typedef 32 and 64 bit integers.      */
#if __TMPL_USING_C99_STDINT_H__ == 1

/*  The user requested the use of stdint.h, but this only exists in C99 and   *
 *  higher standards of the language. Check that the __STDC_VERSION__ macro   *
 *  has been defined (introduced in the 1995 extension of the language), and  *
 *  check that the value is at least 199901L (The C99 value of the macro).    */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <stdint.h>

/*  If we get here, we have support for the library stdint.h. This header     *
 *  file is required to define fixed-width unsigned integer data types of     *
 *  both 32-bits and 64-bits. Typedef these for later use in libtmpl.         */
typedef uint32_t tmpl_uint32;
typedef int32_t tmpl_int32;
typedef uint64_t tmpl_uint64;
typedef int64_t tmpl_int64;

#else
/*  Else for #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.    *
 *  If we get here, the user requested stdint.h, but __STDC_VERSION__ macro   *
 *  indicates their compiler likely doesn't support this. Abort the           *
 *  compiling process and raise an error.                                     */

#error "User requested stdint.h (C99) but compiler version less than 199901L."

#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

#else
/*  Else statement for __TMPL_USE_C99_STDINT_H__ == 1. If we get here, the    *
 *  user has opted for strict C89/C90 compliant code (commonly called ANSI C).*
 *  Unfortunately, the C89/C90 standard does not required fixed-width data    *
 *  types, but instead only defined what the minimum sizes must be. For       *
 *  example, and int must be at least 16-bits, and a long must be at least 32.*
 *  However, for most unix-like systems, short is 16 bits, int is 32, and     *
 *  long is 64. On Microsoft computers we usually see short is 16, and both   *
 *  int and long are 32. We can check the size of these data types using the  *
 *  macros found in limits.h. We'll check short, int, and long and see if any *
 *  are 32 or 64 bit. We'll also check long long, if it is supported by the   *
 *  compiler (C89/C90 does not define long long as it was introduced in C99). *
 *  If all of these options fail, which is incredibly unlikely, you may need  *
 *  to resort to a different compiler such as GCC or clang which support C99. */

/*  We'll use the macros defined in limits.h to see if your compiler supports *
 *  a 32-bit integer. This is usually a regular int. The C standard requires  *
 *  long int to be 'at least' 32-bits. In most implementations it is 64-bits, *
 *  except with Microsoft's compiler which implements it as a 32-bit integer. */
#if USHRT_MAX == 0xFFFFFFFF
typedef short unsigned int tmpl_uint32;
typedef short int tmpl_int32;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int tmpl_uint32;
typedef int tmpl_int32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef long unsigned int tmpl_uint32;
typedef long int tmpl_int32;
#elif define(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFF
typedef long long unsigned int tmpl_uint32;
typedef long long int tmpl_int32;
#else
#error "libtmpl: No 32-bit integer type found."
#endif

#if USHRT_MAX == 0xFFFFFFFFFFFFFFFF
typedef short unsigned int tmpl_uint64;
typedef short int tmpl_int64;
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned int tmpl_uint64;
typedef int tmpl_int64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long unsigned int tmpl_uint64;
typedef long int tmpl_int64;
#elif defined(ULLONG_MAX) && ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long long unsigned int tmpl_uint64;
typedef long long int tmpl_int64;
#else
#error "libtmpl: No 64-bit integer type found."
#endif

#endif


#endif
/*  End of include guard.                                                     */

