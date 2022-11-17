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
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                             A FRIENDLY WARNING                             *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *                                  EXAMPLES                                  *
 ******************************************************************************
 *  Examples of all of the functions can be found in:                         *
 *      libtmpl/examples/integer_examples/                                    *
 ******************************************************************************
 *                                   TESTS                                    *
 ******************************************************************************
 *  Tests for all of the functions can be found in:                           *
 *      libtmpl/tests/integer_tests/                                          *
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

#include <stdlib.h>
#include <libtmpl/include/tmpl_inttype.h>
#include <libtmpl/include/tmpl_vector.h>

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
#include <libtmpl/include/integer/tmpl_integer_abs_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the functions in src/integer/.                              */
extern signed char tmpl_Char_Abs(signed char n);
extern short int tmpl_Short_Abs(short int n);
extern int tmpl_Int_Abs(int n);
extern long int tmpl_Long_Abs(long int n);

/*  Long long function if support is available.                               */
#if TMPL_HAS_LONGLONG == 1
extern long long int tmpl_LLong_Abs(long long int);
#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Max                                                    *
 *  Purpose:                                                                  *
 *      Compute the maximum of an array of ints.                              *
 *  Arguments:                                                                *
 *      int *arr:                                                             *
 *          An array of ints.                                                 *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      int max:                                                              *
 *          The maximum of arr.                                               *
 ******************************************************************************/
extern signed char tmpl_Char_Array_Max(signed char *arr, size_t len);
extern unsigned char tmpl_UChar_Array_Max(unsigned char *arr, size_t len);
extern short int tmpl_Short_Array_Max(short int *arr, size_t len);
extern unsigned short tmpl_UShort_Array_Max(unsigned short *arr, size_t len);
extern int tmpl_Int_Array_Max(int *arr, size_t len);
extern unsigned int tmpl_UInt_Array_Max(unsigned int *arr, size_t len);
extern long int tmpl_Long_Array_Max(long int *arr, size_t len);
extern unsigned long tmpl_ULong_Array_Max(unsigned long *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Min                                                    *
 *  Purpose:                                                                  *
 *      Compute the minimum of an array of ints.                              *
 *  Arguments:                                                                *
 *      int *arr:                                                             *
 *          An array of ints.                                                 *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      int min:                                                              *
 *          The minimum of arr.                                               *
 ******************************************************************************/
extern signed char tmpl_Char_Array_Min(signed char *arr, size_t len);
extern unsigned char tmpl_UChar_Array_Min(unsigned char *arr, size_t len);
extern short int tmpl_Short_Array_Min(short int *arr, size_t len);
extern unsigned short tmpl_UShort_Array_Min(unsigned short *arr, size_t len);
extern int tmpl_Int_Array_Min(int *arr, size_t len);
extern unsigned int tmpl_UInt_Array_Min(unsigned int *arr, size_t len);
extern long int tmpl_Long_Array_Min(long int *arr, size_t len);
extern unsigned long tmpl_ULong_Array_Min(unsigned long *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_MinMax                                                 *
 *  Purpose:                                                                  *
 *      Compute the min and max of an array of ints.                          *
 *  Arguments:                                                                *
 *      int *arr:                                                             *
 *          An array of ints.                                                 *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *      int *min:                                                             *
 *          A pointer to an int, the min is stored here.                      *
 *      int *max:                                                             *
 *          A pointer to an int, the max is stored here.                      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Char_Array_MinMax(signed char *arr, size_t len,
                       signed char *min, signed char *max);

extern void
tmpl_UChar_Array_MinMax(unsigned char *arr, size_t len,
                        unsigned char *min, unsigned char *max);

extern void
tmpl_Short_Array_MinMax(short int *arr, size_t len,
                        short int *min, short int *max);

extern void
tmpl_UShort_Array_MinMax(unsigned short *arr, size_t len,
                         unsigned short int *min, unsigned short int *max);

extern void
tmpl_Int_Array_MinMax(int *arr, size_t len,
                      int *min, int *max);

extern void
tmpl_UInt_Array_MinMax(unsigned int *arr, size_t len,
                       unsigned int *min, unsigned int *max);

extern void
tmpl_Long_Array_MinMax(long int *arr, size_t len,
                       long int *min, long int *max);

extern void
tmpl_ULong_Array_MinMax(unsigned long *arr, size_t len,
                        unsigned long int *min, unsigned long int *max);

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
extern unsigned char tmpl_UChar_Factorial(unsigned char n);
extern unsigned short int tmpl_UShort_Factorial(unsigned short int n);
extern unsigned int tmpl_UInt_Factorial(unsigned int n);
extern unsigned long int tmpl_ULong_Factorial(unsigned long int n);

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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntVector_GCD                                                   *
 *  Purpose:                                                                  *
 *      Computes the multi-variable GCD of a vector of integers.              *
 *  Arguments:                                                                *
 *      arr (tmpl_UIntVector *):                                              *
 *          An array of unsigned integer.                                     *
 *  Output:                                                                   *
 *      GCD (unsigned int):                                                   *
 *          The greatest common denominator of the array.                     *
 ******************************************************************************/
extern unsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Sieve_of_Eratosthenes                                            *
 *  Purpose:                                                                  *
 *      Computes the first N prime numbers using the Sieve of Eratosthenes.   *
 *  Arguments:                                                                *
 *      N (unsigned long int):                                                *
 *          The number of primes to compute.                                  *
 *  Output:                                                                   *
 *      arr (tmpl_ULongVector *):                                             *
 *          The first N primes in order.                                      *
 ******************************************************************************/
extern tmpl_ULongVector *tmpl_Sieve_of_Eratosthenes(unsigned long int N);

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

#elif defined(_MSC_VER)
/*  Else for #if defined(__has_builtin).                                      */

/*  _BitScanForward64 and _BitScanReverse64 found here.                       */
#include <intrin.h>

/*  Microsoft's compiler has _BitScanForward, equivalent to trailing zeros.   */
unsigned int __inline TMPL_UINT_TRAILING_ZEROS(unsigned int n)
{
    unsigned int trailing_zeros = 0U;
    _BitScanForward(&trailing_zeros, n);
    return trailing_zeros;
}

/*  long and int are the same on Windows.                                     */
unsigned long int __inline TMPL_ULONG_TRAILING_ZEROS(unsigned long int n)
{
    unsigned long int trailing_zeros = 0UL;
    _BitScanForward(&trailing_zeros, n);
    return trailing_zeros;
}

/*  long long is 64-bits on Windows.                                          */
unsigned long int __inline TMPL_ULLONG_TRAILING_ZEROS(unsigned long long int n)
{
    unsigned long int trailing_zeros = 0UL;
    _BitScanForward64(&trailing_zeros, n);
    return trailing_zeros;
}

/*  Microsoft's compiler has _BitScanReverse, equivalent to leading zeros.    */
unsigned int __inline TMPL_UINT_LEADING_ZEROS(unsigned int n)
{
    unsigned int leading_zeros = 0U;
    _BitScanReverse(&leading_zeros, n);
    return leading_zeros;
}

/*  long and int are the same on Windows.                                     */
unsigned long int __inline TMPL_ULONG_LEADING_ZEROS(unsigned long int n)
{
    unsigned long int leading_zeros = 0UL;
    _BitScanReverse(&leading_zeros, n);
    return leading_zeros;
}

/*  long long is 64-bits on Windows.                                          */
unsigned long int __inline TMPL_ULLONG_LEADING_ZEROS(unsigned long long int n)
{
    unsigned long int trailing_zeros = 0UL;
    _BitScanReverse64(&trailing_zeros, n);
    return trailing_zeros;
}

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

#endif
/*  End of include guard.                                                     */
