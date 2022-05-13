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
 *                             tmpl_number_theory                             *
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
 *      libtmpl/examples/number_theory_examples/                              *
 ******************************************************************************
 *                                   TESTS                                    *
 ******************************************************************************
 *  Tests for all of the functions can be found in:                           *
 *      libtmpl/tests/number_theory_tests/                                    *
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
#ifndef TMPL_NUMBER_THEORY_H
#define TMPL_NUMBER_THEORY_H

#include <libtmpl/include/tmpl_vector.h>

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
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_char.c                  *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_short.c                 *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_int.c                   *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_long.c                  *
 ******************************************************************************/
extern int tmpl_Char_Trailing_Zeros(char n);
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
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_uchar.c                 *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_ushort.c                *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_uint.c                  *
 *      libtmpl/src/number_theory/tmpl_trailing_zeros_ulong.c                 *
 *  Examples:                                                                 *
 *      libtmpl/examples/number_theory/tmpl_trailing_zeros_uchar_example.c    *
 *      libtmpl/examples/number_theory/tmpl_trailing_zeros_ushort_example.c   *
 *      libtmpl/examples/number_theory/tmpl_trailing_zeros_uint_example.c     *
 *      libtmpl/examples/number_theory/tmpl_trailing_zeros_ulong_example.c    *
 *  Tests:                                                                    *
 *      libtmpl/tests/number_theory/time_tests/                               *
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
 *      libtmpl/src/number_theory/tmpl_remove_trailing_zeros_uchar.c          *
 *      libtmpl/src/number_theory/tmpl_remove_trailing_zeros_ushort.c         *
 *      libtmpl/src/number_theory/tmpl_remove_trailing_zeros_uint.c           *
 *      libtmpl/src/number_theory/tmpl_remove_trailing_zeros_ulong.c          *
 *  Examples:                                                                 *
 *      libtmpl/examples/number_theory/                                       *
 *          tmpl_remove_trailing_zeros_uchar_example.c                        *
 *          tmpl_remove_trailing_zeros_ushort_example.c                       *
 *          tmpl_remove_trailing_zeros_uint_example.c                         *
 *          tmpl_remove_trailing_zeros_ulong_example.c                        *
 *  Tests:                                                                    *
 *      libtmpl/tests/number_theory/time_tests/                               *
 *          tmpl_remove_trailing_zeros_uchar_time_test.c                      *
 *          tmpl_remove_trailing_zeros_ushort_time_test.c                     *
 *          tmpl_remove_trailing_zeros_uint_time_test.c                       *
 *          tmpl_remove_trailing_zeros_ulong_time_test.c                      *
 ******************************************************************************/
extern char tmpl_Char_GCD(char m, char n);
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
 *      libtmpl/src/number_theory/tmpl_binary_gcd_uchar.c                     *
 *      libtmpl/src/number_theory/tmpl_binary_gcd_ushort.c                    *
 *      libtmpl/src/number_theory/tmpl_binary_gcd_uint.c                      *
 *      libtmpl/src/number_theory/tmpl_binary_gcd_ulong.c                     *
 *  Examples:                                                                 *
 *      libtmpl/examples/number_theory/                                       *
 *          tmpl_binary_gcd_uchar_example.c                                   *
 *          tmpl_binary_gcd_ushort_example.c                                  *
 *          tmpl_binary_gcd_uint_example.c                                    *
 *          tmpl_binary_gcd_ulong_example.c                                   *
 *  Tests:                                                                    *
 *      libtmpl/tests/number_theory/time_tests/                               *
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

extern unsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr);

extern tmpl_ULongVector *
tmpl_Sieve_of_Eratosthenes(unsigned long N);

#endif
