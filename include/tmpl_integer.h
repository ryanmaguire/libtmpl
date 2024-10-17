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
 *                                tmpl_integer                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for working with integers. This includes prime number  *
 *      functions, GCD algorithms, and more.                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 12, 2022                                                  *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/05/12: Ryan Maguire                                                  *
 *      Added license and descriptions for functions.                         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INTEGER_H
#define TMPL_INTEGER_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  size_t typedef given here.                                                */
#include <stddef.h>

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  TMPL_HAS_LONGLONG macro found here.                                       */
#include <libtmpl/include/tmpl_inttype.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Abs                                                          *
 *  Purpose:                                                                  *
 *      Computes the absolute value of an integer.                            *
 *  Arguments:                                                                *
 *      n (int):                                                              *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      abs_n (int):                                                          *
 *          The absolute value of n.                                          *
 ******************************************************************************/

/*  Small function worth inlining.                                            */
#if TMPL_USE_INLINE == 1

/*  Inline versions found here.                                               */
#include <libtmpl/include/integer/tmpl_abs_char.h>
#include <libtmpl/include/integer/tmpl_abs_int.h>
#include <libtmpl/include/integer/tmpl_abs_long.h>
#include <libtmpl/include/integer/tmpl_abs_short.h>

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
#include <libtmpl/include/integer/tmpl_abs_llong.h>
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the functions in src/integer/.                              */
extern signed char tmpl_Char_Abs(signed char n);
extern signed short int tmpl_Short_Abs(signed short int n);
extern signed int tmpl_Int_Abs(signed int n);
extern signed long int tmpl_Long_Abs(signed long int n);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern signed long long int tmpl_LLong_Abs(signed long long int);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UInt_Factorial                                                   *
 *  Purpose:                                                                  *
 *      Computes the factorial of an integer.                                 *
 *  Arguments:                                                                *
 *      n (unsigned int):                                                     *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      n! (int):                                                             *
 *          The factorial of n.                                               *
 *  Notes:                                                                    *
 *      Returns 0 on overflow. n! is never zero for positive integers, so     *
 *      this can be used for error checking.                                  *
 ******************************************************************************/

/*  The factorial function gets very large very quickly and overflows even    *
 *  for relatively small integers. Because of this we can use a small lookup  *
 *  table for the values, and return zero for integers n such that n! will    *
 *  overflow. Since the entire computation is a lookup table, we can inline.  */
#if TMPL_USE_INLINE == 1

/*  Inline versions found here.                                               */
#include <libtmpl/include/integer/tmpl_factorial_uchar.h>
#include <libtmpl/include/integer/tmpl_factorial_uint.h>
#include <libtmpl/include/integer/tmpl_factorial_ullong.h>
#include <libtmpl/include/integer/tmpl_factorial_ulong.h>
#include <libtmpl/include/integer/tmpl_factorial_ushort.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the functions in src/integer/.                              */
extern unsigned char tmpl_UChar_Factorial(unsigned char n);
extern unsigned short int tmpl_UShort_Factorial(unsigned short int n);
extern unsigned int tmpl_UInt_Factorial(unsigned int n);
extern unsigned long int tmpl_ULong_Factorial(unsigned long int n);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern unsigned long long int tmpl_ULLong_Factorial(unsigned long long int);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UChar_Leading_Zeros                                              *
 *  Purpose:                                                                  *
 *      Computes the number of leading zeros for unsigned integers. Similar   *
 *      functions are provided for short, int, and long. The number zero is a *
 *      special case and zero is returned.                                    *
 *  Arguments:                                                                *
 *      n (unsigned char/short/int/long):                                     *
 *          An unsigned integer.                                              *
 *  Output:                                                                   *
 *      zeros (int):                                                          *
 *          The number of leading zeros in the binary representation of n.    *
 ******************************************************************************/
extern int tmpl_UChar_Leading_Zeros(unsigned char n);
extern int tmpl_UShort_Leading_Zeros(unsigned short int n);
extern int tmpl_UInt_Leading_Zeros(unsigned int n);
extern int tmpl_ULong_Leading_Zeros(unsigned long int n);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern int tmpl_ULLong_Leading_Zeros(unsigned long long int);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Max                                                          *
 *  Purpose:                                                                  *
 *      Compute the maximum of two ints.                                      *
 *  Arguments:                                                                *
 *      int x:                                                                *
 *          An integer.                                                       *
 *      int y:                                                                *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      int max:                                                              *
 *          The maximum of x and y.                                           *
 ******************************************************************************/
extern signed char tmpl_Char_Max(signed char x, signed char y);
extern short int tmpl_Short_Max(short int x, short int y);
extern int tmpl_Int_Max(int x, int y);
extern long int tmpl_Long_Max(long int x, long int y);
extern unsigned char tmpl_UChar_Max(unsigned char x, unsigned char y);
extern unsigned short tmpl_UShort_Max(unsigned short x, unsigned short y);
extern unsigned int tmpl_UInt_Max(unsigned int x, unsigned int y);
extern unsigned long tmpl_ULong_Max(unsigned long x, unsigned long y);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern long long int tmpl_LLong_Max(long long int x, long long int y);
extern unsigned long long int
tmpl_ULLong_Max(unsigned long long int x, unsigned long long int y);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Min                                                          *
 *  Purpose:                                                                  *
 *      Compute the minimum of two ints.                                      *
 *  Arguments:                                                                *
 *      int x:                                                                *
 *          An integer.                                                       *
 *      int y:                                                                *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      int max:                                                              *
 *          The minimum of x and y.                                           *
 ******************************************************************************/
extern signed char tmpl_Char_Min(signed char x, signed char y);
extern short int tmpl_Short_Min(short int x, short int y);
extern int tmpl_Int_Min(int x, int y);
extern long int tmpl_Long_Min(long int x, long int y);
extern unsigned char tmpl_UChar_Min(unsigned char x, unsigned char y);
extern unsigned short tmpl_UShort_Min(unsigned short x, unsigned short y);
extern unsigned int tmpl_UInt_Min(unsigned int x, unsigned int y);
extern unsigned long tmpl_ULong_Min(unsigned long x, unsigned long y);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern long long int tmpl_LLong_Min(long long int x, long long int y);
extern unsigned long long int
tmpl_ULLong_Min(unsigned long long int x, unsigned long long int y);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Char_Trailing_Zeros                                              *
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros for signed integers. Similar    *
 *      functions are provided for short, int, and long. The number zero is a *
 *      special case and zero is returned.                                    *
 *  Arguments:                                                                *
 *      n (char/short/int/long):                                              *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      zeros (int):                                                          *
 *          The number of trailing zeros in the binary representation of n.   *
 *  Source Code:                                                              *
 *      libtmpl/src/integer/tmpl_trailing_zeros_char.c                        *
 *      libtmpl/src/integer/tmpl_trailing_zeros_short.c                       *
 *      libtmpl/src/integer/tmpl_trailing_zeros_int.c                         *
 *      libtmpl/src/integer/tmpl_trailing_zeros_long.c                        *
 ******************************************************************************/
extern int tmpl_Char_Trailing_Zeros(signed char n);
extern int tmpl_Short_Trailing_Zeros(short int n);
extern int tmpl_Int_Trailing_Zeros(int n);
extern int tmpl_Long_Trailing_Zeros(long int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UChar_Trailing_Zeros                                             *
 *  Purpose:                                                                  *
 *      Computes the number of trailing zeros for unsigned integers. Similar  *
 *      functions are provided for short, int, and long. The number zero is a *
 *      special case and zero is returned.                                    *
 *  Arguments:                                                                *
 *      n (unsigned char/short/int/long):                                     *
 *          An unsigned integer.                                              *
 *  Output:                                                                   *
 *      zeros (int):                                                          *
 *          The number of trailing zeros in the binary representation of n.   *
 *  Source Code:                                                              *
 *      libtmpl/src/integer/tmpl_trailing_zeros_uchar.c                       *
 *      libtmpl/src/integer/tmpl_trailing_zeros_ushort.c                      *
 *      libtmpl/src/integer/tmpl_trailing_zeros_uint.c                        *
 *      libtmpl/src/integer/tmpl_trailing_zeros_ulong.c                       *
 *  Examples:                                                                 *
 *      libtmpl/examples/integer/tmpl_trailing_zeros_uchar_example.c          *
 *      libtmpl/examples/integer/tmpl_trailing_zeros_ushort_example.c         *
 *      libtmpl/examples/integer/tmpl_trailing_zeros_uint_example.c           *
 *      libtmpl/examples/integer/tmpl_trailing_zeros_ulong_example.c          *
 *  Tests:                                                                    *
 *      libtmpl/tests/integer/time_tests/                                     *
 *          tmpl_trailing_zeros_uchar_time_test.c                             *
 *          tmpl_trailing_zeros_ushort_time_test.c                            *
 *          tmpl_trailing_zeros_uint_time_test.c                              *
 *          tmpl_trailing_zeros_ulong_time_test.c                             *
 ******************************************************************************/
extern int tmpl_UChar_Trailing_Zeros(unsigned char n);
extern int tmpl_UShort_Trailing_Zeros(unsigned short int n);
extern int tmpl_UInt_Trailing_Zeros(unsigned int n);
extern int tmpl_ULong_Trailing_Zeros(unsigned long int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Char_GCD                                                         *
 *  Purpose:                                                                  *
 *      Computes the greatest common denominator of two signed integers. The  *
 *      value is always positive, even for negative inputs. Similar functions *
 *      are provided for short, int, and long.                                *
 *  Arguments:                                                                *
 *      n_pty (unsigned char/short/int/long *):                               *
 *          A pointer to an unsigned integer, the value being modified.       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/integer/tmpl_remove_trailing_zeros_uchar.c                *
 *      libtmpl/src/integer/tmpl_remove_trailing_zeros_ushort.c               *
 *      libtmpl/src/integer/tmpl_remove_trailing_zeros_uint.c                 *
 *      libtmpl/src/integer/tmpl_remove_trailing_zeros_ulong.c                *
 *  Examples:                                                                 *
 *      libtmpl/examples/integer/                                             *
 *          tmpl_remove_trailing_zeros_uchar_example.c                        *
 *          tmpl_remove_trailing_zeros_ushort_example.c                       *
 *          tmpl_remove_trailing_zeros_uint_example.c                         *
 *          tmpl_remove_trailing_zeros_ulong_example.c                        *
 *  Tests:                                                                    *
 *      libtmpl/tests/integer/time_tests/                                     *
 *          tmpl_remove_trailing_zeros_uchar_time_test.c                      *
 *          tmpl_remove_trailing_zeros_ushort_time_test.c                     *
 *          tmpl_remove_trailing_zeros_uint_time_test.c                       *
 *          tmpl_remove_trailing_zeros_ulong_time_test.c                      *
 ******************************************************************************/
extern char tmpl_Char_GCD(signed char m, signed char n);
extern short int tmpl_Short_GCD(short int m, short int n);
extern int tmpl_Int_GCD(int m, int n);
extern long int tmpl_Long_GCD(long int m, long int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UChar_GCD                                                        *
 *  Purpose:                                                                  *
 *      Computes the greatest common denominator of two unsigned integers.    *
 *      Similar functions are provided for short, int, and long.              *
 *  Arguments:                                                                *
 *      m (unsigned char/short/int/long):                                     *
 *          The first integer.                                                *
 *      n (unsigned char/short/int/long):                                     *
 *          The second integer.                                               *
 *  Output:                                                                   *
 *      GCD (unsigned char/short/int/long):                                   *
 *          The greatest common denominator of m and n.                       *
 *  Source Code:                                                              *
 *      libtmpl/src/integer/tmpl_binary_gcd_uchar.c                           *
 *      libtmpl/src/integer/tmpl_binary_gcd_ushort.c                          *
 *      libtmpl/src/integer/tmpl_binary_gcd_uint.c                            *
 *      libtmpl/src/integer/tmpl_binary_gcd_ulong.c                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/integer/                                             *
 *          tmpl_binary_gcd_uchar_example.c                                   *
 *          tmpl_binary_gcd_ushort_example.c                                  *
 *          tmpl_binary_gcd_uint_example.c                                    *
 *          tmpl_binary_gcd_ulong_example.c                                   *
 *  Tests:                                                                    *
 *      libtmpl/tests/integer/time_tests/                                     *
 *          tmpl_binary_gcd_uchar_time_test.c                                 *
 *          tmpl_binary_gcd_ushort_time_test.c                                *
 *          tmpl_binary_gcd_uint_time_test.c                                  *
 *          tmpl_binary_gcd_ulong_time_test.c                                 *
 ******************************************************************************/
extern unsigned char
tmpl_UChar_GCD(unsigned char m, unsigned char n);

extern unsigned short int
tmpl_UShort_GCD(unsigned short int m, unsigned short int n);

extern unsigned int
tmpl_UInt_GCD(unsigned int m, unsigned int n);

extern unsigned long int
tmpl_ULong_GCD(unsigned long int m, unsigned long int n);

/*  Signed Euclidean GCD algorithms.                                          */
extern signed char
tmpl_Char_GCD_Euclidean(signed char m, signed char n);

extern signed int
tmpl_Int_GCD_Euclidean(signed int m, signed int n);

extern signed long int
tmpl_Long_GCD_Euclidean(signed long int m, signed long int n);

extern signed short int
tmpl_Short_GCD_Euclidean(signed short int m, signed short int n);

#if TMPL_HAS_LONGLONG == 1
extern signed long long int
tmpl_LLong_GCD_Euclidean(signed long long int m, signed long long int n);
#endif

/*  Unsigned Euclidean GCD algorithms.                                        */
extern unsigned char
tmpl_UChar_GCD_Euclidean(unsigned char m, unsigned char n);

extern unsigned int
tmpl_UInt_GCD_Euclidean(unsigned int m, unsigned int n);

extern unsigned long int
tmpl_ULong_GCD_Euclidean(unsigned long int m, unsigned long int n);

extern unsigned short int
tmpl_UShort_GCD_Euclidean(unsigned short int m, unsigned short int n);

#if TMPL_HAS_LONGLONG == 1
extern unsigned long long int
tmpl_ULLong_GCD_Euclidean(unsigned long long int m, unsigned long long int n);
#endif

/*  Signed naive GCD algorithms.                                              */
extern signed char
tmpl_Char_GCD_Naive(signed char m, signed char n);

extern signed int
tmpl_Int_GCD_Naive(signed int m, signed int n);

extern signed long int
tmpl_Long_GCD_Naive(signed long int m, signed long int n);

extern signed short int
tmpl_Short_GCD_Naive(signed short int m, signed short int n);

#if TMPL_HAS_LONGLONG == 1
extern signed long long int
tmpl_LLong_GCD_Naive(signed long long int m, signed long long int n);
#endif

/*  Unsigned naive GCD algorithms.                                            */
extern unsigned char
tmpl_UChar_GCD_Naive(unsigned char m, unsigned char n);

extern unsigned int
tmpl_UInt_GCD_Naive(unsigned int m, unsigned int n);

extern unsigned long int
tmpl_ULong_GCD_Naive(unsigned long int m, unsigned long int n);

extern unsigned short int
tmpl_UShort_GCD_Naive(unsigned short int m, unsigned short int n);

#if TMPL_HAS_LONGLONG == 1
extern unsigned long long int
tmpl_ULLong_GCD_Naive(unsigned long long int m, unsigned long long int n);
#endif

/*  Signed mixed binary GCD algorithms.                                       */
extern signed char
tmpl_Char_GCD_Mixed_Binary(signed char m, signed char n);

extern signed int
tmpl_Int_GCD_Mixed_Binary(signed int m, signed int n);

extern signed long int
tmpl_Long_GCD_Mixed_Binary(signed long int m, signed long int n);

extern signed short int
tmpl_Short_GCD_Mixed_Binary(signed short int m, signed short int n);

#if TMPL_HAS_LONGLONG == 1
extern signed long long int
tmpl_LLong_GCD_Mixed_Binary(signed long long int m, signed long long int n);
#endif

/*  Unsigned mixed binary GCD algorithms.                                     */
extern unsigned char
tmpl_UChar_GCD_Mixed_Binary(unsigned char m, unsigned char n);

extern unsigned int
tmpl_UInt_GCD_Mixed_Binary(unsigned int m, unsigned int n);

extern unsigned long int
tmpl_ULong_GCD_Mixed_Binary(unsigned long int m, unsigned long int n);

extern unsigned short int
tmpl_UShort_GCD_Mixed_Binary(unsigned short int m, unsigned short int n);

#if TMPL_HAS_LONGLONG == 1
extern unsigned long long int
tmpl_ULLong_GCD_Mixed_Binary(unsigned long long int m,
                             unsigned long long int n);
#endif

/*  Macros for taking advantage of several builtin's different compilers      *
 *  may have. GCC and clang support __builtin_ctz and more.                   */
#if defined(__has_builtin)

/*  Count-Trailing-Zeros for unsigned int.                                    */
#if __has_builtin(__builtin_ctz)
#define TMPL_UINT_TRAILING_ZEROS(n) ((n) == 0U ? 0 : __builtin_ctz((n)))
#else
#define TMPL_UINT_TRAILING_ZEROS tmpl_UInt_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ctz).                                  */

/*  Count-Trailing-Zeros for unsigned long int.                               */
#if __has_builtin(__builtin_ctzl)
#define TMPL_ULONG_TRAILING_ZEROS(n) ((n) == 0UL ? 0L : __builtin_ctzl((n)))
#else
#define TMPL_ULONG_TRAILING_ZEROS tmpl_ULong_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ctzl).                                 */

/*  Count-Trailing-Zeros for signed int.                                      */
#if __has_builtin(__builtin_ffs)
#define TMPL_INT_TRAILING_ZEROS(n) ((n) == 0 ? 0L : __builtin_ffs((n)) - 1)
#else
#define TMPL_INT_TRAILING_ZEROS tmpl_Int_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ffs).                                  */

/*  Count-Trailing-Zeros for signed long int.                                 */
#if __has_builtin(__builtin_ffsl)
#define TMPL_LONG_TRAILING_ZEROS(n) ((n) == 0L ? 0L : __builtin_ffsl((n)) - 1L)
#else
#define TMPL_LONG_TRAILING_ZEROS tmpl_Long_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ffsl).                                 */

/*  Count-Leading-Zeros for unsigned int.                                     */
#if __has_builtin(__builtin_clz)
#define TMPL_UINT_LEADING_ZEROS(n) ((n) == 0U ? 0 : __builtin_clz((n)))
#else
#define TMPL_UINT_LEADING_ZEROS tmpl_UInt_Leading_Zeros
#endif
/*  End of #if __has_builtin(__builtin_clz).                                  */

/*  Count-Leading-Zeros for unsigned long int.                                */
#if __has_builtin(__builtin_clzl)
#define TMPL_ULONG_LEADING_ZEROS(n) ((n) == 0UL ? 0L : __builtin_clzl((n)))
#else
#define TMPL_ULONG_LEADING_ZEROS tmpl_ULong_Leading_Zeros
#endif
/*  End of #if __has_builtin(__builtin_clzl).                                 */

/*  Macros for long long function if long long is available.                  */
#if TMPL_HAS_LONGLONG == 1

/*  Count-Trailing-Zeros for unsigned long long int.                          */
#if __has_builtin(__builtin_ctzll)
#define TMPL_ULLONG_TRAILING_ZEROS(n) ((n) == 0ULL ? 0LL : __builtin_ctzll((n)))
#else
#define TMPL_ULLONG_TRAILING_ZEROS tmpl_ULLong_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ctzll).                                */

/*  Count-Trailing-Zeros for signed long long int.                            */
#if __has_builtin(__builtin_ffsll)
#define TMPL_LLONG_TRAILING_ZEROS(n) ((n) == 0LL ? 0LL:__builtin_ffsll((n))-1LL)
#else
#define TMPL_LLONG_TRAILING_ZEROS tmpl_LLong_Trailing_Zeros
#endif
/*  End of #if __has_builtin(__builtin_ffsl).                                 */

/*  Count-Leading-Zeros for unsigned long long int.                           */
#if __has_builtin(__builtin_clzll)
#define TMPL_ULLONG_LEADING_ZEROS(n) ((n) == 0ULL ? 0LL : __builtin_clzll((n)))
#else
#define TMPL_ULLONG_LEADING_ZEROS tmpl_ULLong_Leading_Zeros
#endif
/*  End of #if __has_builtin(__builtin_clzll).                                */

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#else
/*  Else for #if defined(__has_builtin).                                      */

/*  Lacking any built-in support, use libtmpl's function.                     */
#define TMPL_UINT_TRAILING_ZEROS tmpl_UInt_Trailing_Zeros
#define TMPL_ULONG_TRAILING_ZEROS tmpl_ULong_Trailing_Zeros
#define TMPL_INT_TRAILING_ZEROS tmpl_Int_Trailing_Zeros
#define TMPL_LONG_TRAILING_ZEROS tmpl_Long_Trailing_Zeros
#define TMPL_UINT_LEADING_ZEROS tmpl_UInt_Leading_Zeros
#define TMPL_ULONG_LEADING_ZEROS tmpl_ULong_Leading_Zeros

/*  Macros for long long function if long long is available.                  */
#if TMPL_HAS_LONGLONG == 1
#define TMPL_LLONG_TRAILING_ZEROS tmpl_LLong_Trailing_Zeros
#define TMPL_ULLONG_TRAILING_ZEROS tmpl_ULLong_Trailing_Zeros
#define TMPL_ULLONG_LEADING_ZEROS tmpl_ULLong_Leading_Zeros
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#endif
/*  End of #if defined(__has_builtin).                                        */

#define TMPL_UCHAR_TRAILING_ZEROS tmpl_UChar_Trailing_Zeros
#define TMPL_USHORT_TRAILING_ZEROS tmpl_UShort_Trailing_Zeros
#define TMPL_CHAR_TRAILING_ZEROS tmpl_Char_Trailing_Zeros
#define TMPL_SHORT_TRAILING_ZEROS tmpl_Short_Trailing_Zeros
#define TMPL_UCHAR_LEADING_ZEROS tmpl_UChar_Leading_Zeros
#define TMPL_USHORT_LEADING_ZEROS tmpl_UShort_Leading_Zeros

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
