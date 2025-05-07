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
 *                                 tmpl_math                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file attempts to provide a portable, fast, and accurate          *
 *      implementation of libm for anyone to study and use. To avoid naming   *
 *      conflicts, it does not use the names from the C standard library, but *
 *      instead prepends tmpl and the data type in front of names. For        *
 *      example, sine at double precision is the function tmpl_Double_Sin.    *
 *                                                                            *
 *      If your compiler supports the IEEE-754 format, you'll find that the   *
 *      functions provided here are about as fast and as accurate as the ones *
 *      provided in other implementations, such as glibc or openlibm. The     *
 *      ideas used mostly come from standard algorithms found in textbooks,   *
 *      and nothing too fancy is attempted. The main goal is readability. As  *
 *      such, the algorithms are heavily commented.                           *
 *                                                                            *
 *      This file also provides functions that are not part of libm, but are  *
 *      frequently used nonetheless. It also provides many mathematical       *
 *      constants at float, double, and long double precisions.               *
 *                                                                            *
 *      Notes:                                                                *
 *          There is no real portable way to implement infinity in strictly   *
 *          compliant ISO C. Compilers implementing the IEEE-754 format have  *
 *          a way of supporting infinity, but compilers that don't may not.   *
 *          The way glibc implements infinity for compilers lacking IEEE-754  *
 *          support is via the number 1.0E10000, which is guaranteed to       *
 *          overflow. This is undefined behavior, but in practice it works.   *
 *          This implementation uses similar tactics.                         *
 *                                                                            *
 *          A similar problem arises with NAN. IEEE-754 has a means of        *
 *          defining NAN, but compilers lacking this may not. The standard    *
 *          trick is to use 0.0 / 0.0, but this may also be undefined         *
 *          behavior. Again, in practice this usually works fine.             *
 *                                                                            *
 *      This file is a fork of the code I wrote for rss_ringoccs. That        *
 *      library is also released under GPL3. rss_ringoccs no longer contains  *
 *      this file, and all math related tools have migrated to libtmpl.       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stddef.h:                                                             *
 *          Standard C library file with the size_t typedef.                  *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  3.) tmpl_config.h:                                                        *
 *          Header file containing the endianness of your system. This file   *
 *          is built with config.c in libtmpl/. The Makefile automatically    *
 *          runs this, as does the make.sh script. This also contains the     *
 *          TMPL_USE_INLINE and TMPL_USE_MATH_ALGORITHMS macros.              *
 *  4.) math.h:                                                               *
 *          C standard library for math functions. This is only included if   *
 *          TMPL_USE_MATH_ALGORITHMS is not set to one. The Makefile and      *
 *          make.sh file set this macro to one by default.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/09/12: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2021/09/03: Ryan Maguire                                                  *
 *      Rewriting to increase portability.                                    *
 *  2021/09/09: Ryan Maguire                                                  *
 *      Added long double IEEE-754 support.                                   *
 *  2022/01/13: Ryan Maguire                                                  *
 *    Added s390x implementation of long double. Removed the get mantissa and *
 *    exponent functions.                                                     *
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/09/04: Ryan Maguire                                                  *
 *      Moved abs and copysign inline functions to their own files.           *
 ******************************************************************************/

/*  Include guard for this file to prevent including it twice.                */
#ifndef TMPL_MATH_H
#define TMPL_MATH_H

/*  size_t typedef given here.                                                */
#include <stddef.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Whether or not we're building with inline support is here and whether or  *
 *  not we're using libtmpl's implementation of libm. Endianness macros are   *
 *  also found here.                                                          */
#include <libtmpl/include/tmpl_config.h>

/*  Fixed-width integer data types found here, if available.                  */
#include <libtmpl/include/tmpl_inttype.h>

/*  This macro should be defined. If not, abort compiling.                    */
#if !defined(TMPL_USE_INLINE)
#error "tmpl_math.h: TMPL_USE_INLINE is undefined."
#endif

/*  This macro should be defined in tmpl_config.h. If not, there's an error.  */
#if !defined(TMPL_USE_MATH_ALGORITHMS)

/*  Abort compiling.                                                          */
#error "tmpl_math.h: TMPL_USE_MATH_ALGORITHMS is undefined."

/*  Check if libtmpl's implementation of libm is being used, or not.          */
#elif TMPL_USE_MATH_ALGORITHMS != 1

/*  C99 or higher is required if libtmpl algorithms are not used. C89 does    *
 *  not require float or long double versions of various math functions,      *
 *  whereas libtmpl makes frequent use of these. If your implementation does  *
 *  not support C99 or higher, rebuild libtmpl with TMPL_USE_MATH_ALGORITHMS  *
 *  set to 1.                                                                 */
#if !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) && \
    !(defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))
#error "tmpl math algorithms not requested but C99 math functions unavailable."
#endif

/*  If we're not using libtmpl's implementation of libm, include math.h.      */
#include <math.h>
#endif
/*  End of #if !defined(TMPL_USE_MATH_ALGORITHMS).                            */

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  The following comment block explains the IEEE-754 format. Those who know  *
 *  the format can skip it.                                                   */

/******************************************************************************
 *  For a non-negative integer that is less than 2^64, we can store the       *
 *  number in a computer using binary. That is, 64 bits of zeroes and ones    *
 *  which represent our original base-10 integer. With this we can store      *
 *  every integer between 0 and 2^64-1.                                       *
 *                                                                            *
 *    xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx        *
 *    ----------------------------------------------------------------        *
 *                              Integer Part                                  *
 *                                                                            *
 *  If we want to represent a "signed" integer, one that can be negative or   *
 *  positive, or zero, we require more information. One solution is to        *
 *  sacrifice one of the 64 bits and reserve it as the "sign." In doing so we *
 *  we can now store every integer between -(2^63-1) and +(2^63-1). Oddly     *
 *  enough, the difference between these two numbers is 2^64-2, not 2^64-1.   *
 *  In reserving a bit for the sign, we now have two zeroes. A "positive"     *
 *  zero and a "negative" zero, These are called "signed zeroes." When using  *
 *  these, compilers treat them nearly the same, and -0 == +0 returns true.   *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx       *
 *    - ---------------------------------------------------------------       *
 *  Sign                        Integer Part                                  *
 *                                                                            *
 *  Note, the left-most bit does not need to be the signed bit. This will be  *
 *  determined by the "endianness" or your system. Also note, the more        *
 *  common means of representing signed integers is via 2's complement. The   *
 *  signed bit method is mostly a relic of the past.                          *
 *                                                                            *
 *  To store a real number, or to at least approximate, one might guess that  *
 *  we simply insert a point half-way and treat this as a decimal:            *
 *                                                                            *
 *    x xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - -------------------------------- -------------------------------      *
 *  Sign         Integer Part                      Fractional Part            *
 *                                                                            *
 *  This turns out to be a very bad idea since we cannot represent very many  *
 *  numbers with this. The largest number is now 2^32-1, or roughly 4 billion.*
 *  Any larger number would be treated as infinity. On the other hand, we     *
 *  only have about 9 significant digits past the decimal point (in decimal)  *
 *  whereas many applications need up to 16. The solution is the IEEE754      *
 *  Floating Point Format. It represents a real number as follows:            *
 *                                                                            *
 *    s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx      *
 *    - ----------- ----------------------------------------------------      *
 *  Sign  Exponent                     Fraction                               *
 *                                                                            *
 *  The idea is to use scientific notation in binary, writing a number as     *
 *                                                                            *
 *        y = s * 1.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx_2    *
 *              * 2^(eeeeeeeeeee_2 - 1111111111_2)                            *
 *                                                                            *
 *  Where _2 indicates this is all base 2. This "magic number" being          *
 *  subtracted is 1111111111_2 = 2^10-1 = 1023.                               *
 *                                                                            *
 *  Since we know the first digit in scientific notation is always 1, we don't*
 *  need to waste a bit and can store 53 bits worth of the fractional part    *
 *  using just 52 bits. The eeeeeeeeeee - 1023 needs an explanation. We want  *
 *  to store fractional numbers between 0 and 1 and so we need negative       *
 *  exponents. We could reserve a second bit for the sign of the exponent,    *
 *  but the standard is to just subtract 2^10-1 from the exponent. The last   *
 *  thing is to say that all zeroes, or all zeros plus the sign bit,          *
 *  represents zero and not +/- 2^-1023. There are also subnormal numbers,    *
 *  when all exponent bits are zero, but let's not get into that now.         *
 *                                                                            *
 *  Now for some examples:                                                    *
 *    0 00000000001 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1-1023)                                                          *
 *      = 2^-1022                                                             *
 *      ~ 10^-308                                                             *
 *                                                                            *
 *  This is the smallest positive number (that isn't subnormal/denormal).     *
 *                                                                            *
 *    0 11111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^1023                                                              *
 *      ~ 10^308                                                              *
 *      = Infinity (according to the standard).                               *
 *                                                                            *
 *  Setting 2^1023 to infinity means we can reserve a number for              *
 *  Not-a-Number (NaN) as follows:                                            *
 *                                                                            *
 *    0 11111111111 1000000000000000000000000000000000000000000000000001      *
 *      = NaN                                                                 *
 *                                                                            *
 *  This is useful for log(-1) or sqrt(-1) or 0.0/0.0. As a final example,    *
 *  the IEEE 754 64-bit representation of 1.0:                                *
 *                                                                            *
 *    0 01111111111 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1023 - 1023)                                                     *
 *      = 2^0                                                                 *
 *      = 1                                                                   *
 *                                                                            *
 *  Single precision is represented with 32 bits:                             *
 *                                                                            *
 *      s  eeeeeeee xxxxxxxxxxxxxxxxxxxxxxx                                   *
 *      -  -------- -----------------------                                   *
 *    Sign Exponent        Fraction                                           *
 *                                                                            *
 ******************************************************************************/
#include <libtmpl/include/types/tmpl_ieee754_double.h>
#include <libtmpl/include/types/tmpl_ieee754_float.h>
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Sanity check for all of the above code. The following macros should be    *
 *  defined. Abort compiling if not.                                          */
#ifndef TMPL_HAS_IEEE754_FLOAT
#error "tmpl_math.h: TMPL_HAS_IEEE754_FLOAT undefined."
#endif

#ifndef TMPL_HAS_IEEE754_DOUBLE
#error "tmpl_math.h: TMPL_HAS_IEEE754_DOUBLE undefined."
#endif

#ifndef TMPL_HAS_IEEE754_LDOUBLE
#error "tmpl_math.h: TMPL_HAS_IEEE754_LDOUBLE undefined."
#endif

/*  If IEEE-754 support for float does exist, the following macros should be  *
 *  set. Another sanity check, make sure they are.                            */
#if TMPL_HAS_IEEE754_FLOAT == 1

#ifndef TMPL_FLOAT_BIAS
#error "tmpl_math.h: TMPL_FLOAT_BIAS undefined."
#endif

#ifndef TMPL_FLOAT_UBIAS
#error "tmpl_math.h: TMPL_FLOAT_UBIAS undefined."
#endif

#ifndef TMPL_FLOAT_NANINF_EXP
#error "tmpl_math.h: TMPL_FLOAT_NANINF_EXP undefined."
#endif

#ifndef TMPL_FLOAT_MANTISSA_LENGTH
#error "tmpl_math.h: TMPL_FLOAT_MANTISSA_LENGTH undefined."
#endif

#ifndef TMPL_FLOAT_MANTISSA_ULENGTH
#error "tmpl_math.h: TMPL_FLOAT_MANTISSA_ULENGTH undefined."
#endif

#ifndef TMPL_FLOAT_NORMALIZE
#error "tmpl_math.h: TMPL_FLOAT_NORMALIZE undefined."
#endif

#ifndef TMPL_FLOAT_IS_NAN_OR_INF
#error "tmpl_math.h: TMPL_FLOAT_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_FLOAT_IS_NAN
#error "tmpl_math.h: TMPL_FLOAT_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_FLOAT_IS_NOT_A_NUMBER
#error "tmpl_math.h: TMPL_FLOAT_IS_NOT_A_NUMBER undefined."
#endif

#ifndef TMPL_FLOAT_IS_INFINITY
#error "tmpl_math.h: TMPL_FLOAT_IS_INFINITY undefined."
#endif

#ifndef TMPL_FLOAT_EXPO_BITS
#error "tmpl_math.h: TMPL_FLOAT_EXPO_BITS undefined."
#endif

#ifndef TMPL_FLOAT_IS_NEGATIVE
#error "tmpl_math.h: TMPL_FLOAT_IS_NEGATIVE undefined."
#endif

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Same sanity check for double precision macros.                            */
#if TMPL_HAS_IEEE754_DOUBLE == 1

#ifndef TMPL_DOUBLE_BIAS
#error "tmpl_math.h: TMPL_DOUBLE_BIAS undefined."
#endif

#ifndef TMPL_DOUBLE_UBIAS
#error "tmpl_math.h: TMPL_DOUBLE_UBIAS undefined."
#endif

#ifndef TMPL_DOUBLE_NANINF_EXP
#error "tmpl_math.h: TMPL_DOUBLE_NANINF_EXP undefined."
#endif

#ifndef TMPL_DOUBLE_MANTISSA_LENGTH
#error "tmpl_math.h: TMPL_DOUBLE_MANTISSA_LENGTH undefined."
#endif

#ifndef TMPL_DOUBLE_MANTISSA_ULENGTH
#error "tmpl_math.h: TMPL_DOUBLE_MANTISSA_ULENGTH undefined."
#endif

#ifndef TMPL_DOUBLE_NORMALIZE
#error "tmpl_math.h: TMPL_DOUBLE_NORMALIZE undefined."
#endif

#ifndef TMPL_DOUBLE_IS_NAN_OR_INF
#error "tmpl_math.h: TMPL_DOUBLE_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_DOUBLE_IS_NAN
#error "tmpl_math.h: TMPL_DOUBLE_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_DOUBLE_IS_NOT_A_NUMBER
#error "tmpl_math.h: TMPL_DOUBLE_IS_NOT_A_NUMBER undefined."
#endif

#ifndef TMPL_DOUBLE_IS_INFINITY
#error "tmpl_math.h: TMPL_DOUBLE_IS_INFINITY undefined."
#endif

#ifndef TMPL_DOUBLE_EXPO_BITS
#error "tmpl_math.h: TMPL_DOUBLE_EXPO_BITS undefined."
#endif

#ifndef TMPL_DOUBLE_IS_NEGATIVE
#error "tmpl_math.h: TMPL_DOUBLE_IS_NEGATIVE undefined."
#endif

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Lastly, sanity check for long double versions of these macros.            */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

#ifndef TMPL_LDOUBLE_BIAS
#error "tmpl_math.h: TMPL_LDOUBLE_BIAS undefined."
#endif

#ifndef TMPL_LDOUBLE_UBIAS
#error "tmpl_math.h: TMPL_LDOUBLE_UBIAS undefined."
#endif

#ifndef TMPL_LDOUBLE_NANINF_EXP
#error "tmpl_math.h: TMPL_LDOUBLE_NANINF_EXP undefined."
#endif

#ifndef TMPL_LDOUBLE_MANTISSA_LENGTH
#error "tmpl_math.h: TMPL_LDOUBLE_MANTISSA_LENGTH undefined."
#endif

#ifndef TMPL_LDOUBLE_MANTISSA_ULENGTH
#error "tmpl_math.h: TMPL_LDOUBLE_MANTISSA_ULENGTH undefined."
#endif

#ifndef TMPL_LDOUBLE_NORMALIZE
#error "tmpl_math.h: TMPL_LDOUBLE_NORMALIZE undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_NAN_OR_INF
#error "tmpl_math.h: TMPL_LDOUBLE_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_NAN
#error "tmpl_math.h: TMPL_LDOUBLE_IS_NAN_OR_INF undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_NOT_A_NUMBER
#error "tmpl_math.h: TMPL_LDOUBLE_IS_NOT_A_NUMBER undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_INFINITY
#error "tmpl_math.h: TMPL_LDOUBLE_IS_INFINITY undefined."
#endif

#ifndef TMPL_LDOUBLE_EXPO_BITS
#error "tmpl_math.h: TMPL_LDOUBLE_EXPO_BITS undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_NEGATIVE
#error "tmpl_math.h: TMPL_LDOUBLE_IS_NEGATIVE undefined."
#endif

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/*  Largest value such that exp(x) will not return infinity.                  */
extern const float tmpl_Max_Float_Base_E;
extern const double tmpl_Max_Double_Base_E;
extern const long double tmpl_Max_LDouble_Base_E;

/*  Smallest value such that exp(x) will not return zero.                     */
extern const float tmpl_Min_Float_Base_E;
extern const double tmpl_Min_Double_Base_E;
extern const long double tmpl_Min_LDouble_Base_E;

/*  Commonly used constants (pi, e, etc.) found here.                         */
#include <libtmpl/include/constants/tmpl_math_constants.h>

/*  Float, double, and long double precision NaN found here.                  */
#include <libtmpl/include/tmpl_nan.h>

/******************************************************************************
 *                              Tables and Data                               *
 ******************************************************************************/

/*  The atan tables are only needed if libtmpl math algorithms are used.      */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  The values v and atan(v) used in atan and atan2 routines.                 */
extern const float tmpl_float_atan_v[8];
extern const float tmpl_float_atan_of_v[8];
extern const double tmpl_double_atan_v[8];
extern const double tmpl_double_atan_of_v[8];

/*  The long double version of these tables depends on how long double is     *
 *  implemented. 80-bit extended and 64-bit double implementations, as well   *
 *  as the "portable" version, use the same idea as double and float. 128-bit *
 *  quadruple and double-double use a much larger table to speed up the       *
 *  computation while still achieving 10^-32 or 10^-34 peak relative error.   */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE  || \
    TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
extern const long double tmpl_ldouble_atan_n_by_8[129];
#else
extern const long double tmpl_ldouble_atan_v[8];
extern const long double tmpl_ldouble_atan_of_v[8];
#endif

extern const double tmpl_Double_SinCos_Table[440];
extern const float tmpl_Float_SinCos_Table[440];

/*  If type-punning is available, use a table of 64-bit ints representing     *
 *  various values of exp(x). This speeds up the computation considerably.    */
#if TMPL_HAS_FLOATINT64 == 1
extern const tmpl_UInt64 tmpl_double_exp_table[256];

/*  Lacking this, fall back to the original algorithm. Provide a table of the *
 *  values exp(k/128) for k = -89, -88, ..., 0, 1, ..., 88, 89.               */
#else
extern const double tmpl_double_exp_table[179];

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

/*  The values exp(k/128) for k = -89, -88, ..., 0, 1, ..., 88, 89.           */
extern const float tmpl_float_exp_table[179];
extern const long double tmpl_ldouble_exp_table[179];

/*  The values log(1 + k/128) for k = 0, 1, ..., 126, 127.                    */
extern const double tmpl_double_log_table[128];
extern const float tmpl_float_log_table[128];
extern const long double tmpl_ldouble_log_table[128];

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

/*  The values cos((pi/180)*k) for k = 0, 1, ..., 179.                        */
extern const double tmpl_double_cosd_table[180];
extern const float tmpl_float_cosd_table[180];
extern const long double tmpl_ldouble_cosd_table[180];

/*  The values cos(pi*k/128) for k = 0, 1, ..., 127.                          */
extern const double tmpl_double_cospi_table[128];
extern const float tmpl_float_cospi_table[128];
extern const long double tmpl_ldouble_cospi_table[128];

/*  Factorial tables.                                                         */
extern const float tmpl_float_factorial_table[34];

#if TMPL_HAS_IEEE754_DOUBLE == 1
extern const double tmpl_double_factorial_table[171];
#else
extern const double tmpl_double_factorial_table[34];
#endif

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT || \
    TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
extern const long double tmpl_ldouble_factorial_table[171];
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT || \
      TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT
extern const long double tmpl_ldouble_factorial_table[1755];
#else
extern const long double tmpl_ldouble_factorial_table[34];
#endif

/*  The values 1 / (1 + k/128) = 128 / (128 + k) for k = 0, 1, .., 126, 127.  */
extern const double tmpl_double_rcpr_table[128];
extern const float tmpl_float_rcpr_table[128];
extern const long double tmpl_ldouble_rcpr_table[128];

/*  The values sin((pi/180)*k) for k = 0, 1, ..., 179.                        */
extern const double tmpl_double_sind_table[180];
extern const float tmpl_float_sind_table[180];
extern const long double tmpl_ldouble_sind_table[180];

/*  The values sin(pi*k/128) for k = 0, 1, ..., 127.                          */
extern const double tmpl_double_sinpi_table[128];
extern const float tmpl_float_sinpi_table[128];
extern const long double tmpl_ldouble_sinpi_table[128];

/*  The powers 2^n for n = 0, 1, ..., 64, at different precisions.            */
extern const double tmpl_double_pow_2_table[65];
extern const float tmpl_float_pow_2_table[65];
extern const long double tmpl_ldouble_pow_2_table[65];

/******************************************************************************
 *                           Non-Inlined Functions                            *
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arccos                                                    *
 *  Purpose:                                                                  *
 *      Compute the arccos (inverse cosine) of a real number.                 *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double acos_x:                                                        *
 *          The inverse cosine of x, cos^-1(x).                               *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *  Source Code:                                                              *
 *      libtmpl/src/math/                                                     *
 *          tmpl_arccos_math_double.c                                         *
 *          tmpl_arccos_math_float.c                                          *
 *          tmpl_arccos_math_ldouble.c                                        *
 ******************************************************************************/

/*  Alias functions to acos from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Arccos acosf
#define tmpl_Double_Arccos acos
#define tmpl_LDouble_Arccos acosl

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1.                               */

/*  Otherwise use the functions in src/math/.                                 */
extern float tmpl_Float_Arccos(float x);
extern double tmpl_Double_Arccos(double x);
extern long double tmpl_LDouble_Arccos(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arcsin                                                    *
 *  Purpose:                                                                  *
 *      Compute the arcsin (inverse sine) of a real number.                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double asin_x:                                                        *
 *          The inverse sine of x, sin^-1(x).                                 *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *  Source Code:                                                              *
 *      libtmpl/src/math/                                                     *
 *          tmpl_arcsin_double.c                                              *
 *          tmpl_arcsin_float.c                                               *
 *          tmpl_arcsin_ldouble.c                                             *
 ******************************************************************************/

/*  Alias functions to asin from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Arcsin asinf
#define tmpl_Double_Arcsin asin
#define tmpl_LDouble_Arcsin asinl

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1.                               */

/*  Otherwise use the functions in src/math/.                                 */
extern float tmpl_Float_Arcsin(float x);
extern double tmpl_Double_Arcsin(double x);
extern long double tmpl_LDouble_Arcsin(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan2                                                   *
 *  Purpose:                                                                  *
 *      Compute the 2-dimensional arctan (inverse tangent) of a point in the  *
 *      Cartesian plane. This is the angle the point makes with the positive  *
 *      x-axis.                                                               *
 *  Arguments:                                                                *
 *      double y:                                                             *
 *          A real number.                                                    *
 *      double x:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double atan:                                                          *
 *          The angle the point (x,y) makes with (1,0) in the plane.          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *                                                                            *
 *      By convention dating back to (at least) the 1970s, Arctan2 takes the  *
 *      input as (y,x), not (x,y). i.e. the first argument is the y           *
 *      component and the second argument is the x component. This is contrary*
 *      to most 2 dimensional functions that want their inputs as (x,y).      *
 *      This is probably because we are trying to compute tan^-1(y/x) but     *
 *      need to be careful about the signs of y and x, so we write            *
 *      arctan(y,x).                                                          *
 *                                                                            *
 *      This returns a number between -pi and pi, so there is a "branch cut"  *
 *      along the negative x axis. Because of this, use of this function      *
 *      in complex routines results in actual branch cuts.                    *
 ******************************************************************************/

/*  If libtmpl math algorithms are not requested, alias functions to atan2.   */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Arctan2 atan2f
#define tmpl_Double_Arctan2 atan2
#define tmpl_LDouble_Arctan2 atan2l

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Inline not requested, use the external functions in src/math.             */
extern float tmpl_Float_Arctan2(float y, float x);
extern double tmpl_Double_Arctan2(double y, double x);
extern long double tmpl_LDouble_Arctan2(long double y, long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan                                                    *
 *  Purpose:                                                                  *
 *      Compute the arctan (inverse tangent) of a real number.                *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *  Source Code:                                                              *
 *      libtmpl/src/math/                                                     *
 *          tmpl_arctan_float.c                                               *
 *          tmpl_arctan_double.c                                              *
 *          tmpl_arctan_ldouble.c                                             *
 ******************************************************************************/

/*  Alias functions to atan from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Arctan atanf
#define tmpl_Double_Arctan atan
#define tmpl_LDouble_Arctan atanl

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Inline not requested, use the external functions in src/math.             */
extern float tmpl_Float_Arctan(float x);
extern double tmpl_Double_Arctan(double x);
extern long double tmpl_LDouble_Arctan(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_Max                                                 *
 *  Purpose:                                                                  *
 *      Compute the maximum of an array of doubles.                           *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double max:                                                           *
 *          The maximum of arr. NaN's in the array are skipped.               *
 ******************************************************************************/
extern float tmpl_Float_Array_Max(float *arr, size_t len);
extern double tmpl_Double_Array_Max(double *arr, size_t len);
extern long double tmpl_LDouble_Array_Max(long double *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_Max_Index                                           *
 *  Purpose:                                                                  *
 *      Compute the index of the maximum of an array of doubles.              *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      size_t ind:                                                           *
 *          The index of the maximum of arr. NaN's in the array are skipped.  *
 ******************************************************************************/
extern size_t tmpl_Float_Array_Max_Index(float *arr, size_t len);
extern size_t tmpl_Double_Array_Max_Index(double *arr, size_t len);
extern size_t tmpl_LDouble_Array_Max_Index(long double *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_Min                                                 *
 *  Purpose:                                                                  *
 *      Compute the minimum of an array of doubles.                           *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double min:                                                           *
 *          The minimum of arr. NaN's in the array are skipped.               *
 ******************************************************************************/
extern float tmpl_Float_Array_Min(float *arr, size_t len);
extern double tmpl_Double_Array_Min(double *arr, size_t len);
extern long double tmpl_LDouble_Array_Min(long double *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_Min_Index                                           *
 *  Purpose:                                                                  *
 *      Compute the index of the maximum of an array of doubles.              *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      size_t ind:                                                           *
 *          The index of the maximum of arr. NaN's in the array are skipped.  *
 ******************************************************************************/
extern size_t tmpl_Float_Array_Min_Index(float *arr, size_t len);
extern size_t tmpl_Double_Array_Min_Index(double *arr, size_t len);
extern size_t tmpl_LDouble_Array_Min_Index(long double *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_MinMax                                              *
 *  Purpose:                                                                  *
 *      Compute the min and max of an array of doubles.                       *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *      double *min:                                                          *
 *          A pointer to a double. The minimum will be stored here.           *
 *      double *max:                                                          *
 *          A pointer to a double. The max is stored here.                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Float_Array_MinMax(float *arr, size_t len,
                        float *min, float *max);

extern void
tmpl_Double_Array_MinMax(double *arr, size_t len,
                         double *min, double *max);

extern void
tmpl_LDouble_Array_MinMax(long double *arr, size_t len,
                          long double *min, long double *max);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_MinMax_Index                                        *
 *  Purpose:                                                                  *
 *      Compute the indices of the min and max of an array of doubles.        *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          An array of doubles.                                              *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *      size_t *minind:                                                       *
 *          A pointer to a double. The index of the min will be stored here.  *
 *      size_t *maxind:                                                       *
 *          A pointer to a double. The index of the max will be stored here.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Float_Array_MinMax_Index(float *arr, size_t len,
                              size_t *minind, size_t *maxind);

extern void
tmpl_Double_Array_MinMax_Index(double *arr, size_t len,
                               size_t *minind, size_t *maxind);

extern void
tmpl_LDouble_Array_MinMax_Index(long double *arr, size_t len,
                                size_t *minind, size_t *maxind);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Array_Reverse                                             *
 *  Purpose:                                                                  *
 *      Reverses the order of a pointer to an array of real numbers.          *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          A pointer to an array.                                            *
 *      size_t len:                                                           *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      None (void):                                                          *
 ******************************************************************************/
extern void tmpl_Float_Array_Reverse(float *arr, size_t len);
extern void tmpl_Double_Array_Reverse(double *arr, size_t len);
extern void tmpl_LDouble_Array_Reverse(long double *arr, size_t len);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Base2_Mant_and_Exp                                        *
 *  Purpose:                                                                  *
 *      Given a real number x, compute the numbers m and e such that          *
 *      x = +/- m * 2^e with 1 < m < 2. If x = 0, m = 0 and e = 0 is returned.*
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double *mant:                                                         *
 *          Pointer to a double. The mantissa of x is stored here.            *
 *      signed int *expo:                                                     *
 *          A pointer to a signed integer. The exponent is stored here.       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Float_Base2_Mant_and_Exp(float x, float *mant, signed int *expo);

extern void
tmpl_Double_Base2_Mant_and_Exp(double x, double *mant, signed int *expo);

extern void
tmpl_LDouble_Base2_Mant_and_Exp(long double x,
                                long double *mant,
                                signed int *expo);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cbrt                                                      *
 *  Purpose:                                                                  *
 *      Compute the cube root of a real number.                               *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cbrt_x:                                                        *
 *          The cube root of x, x^{1/3}.                                      *
 ******************************************************************************/
extern float tmpl_Float_Cbrt(float x);
extern double tmpl_Double_Cbrt(double x);
extern long double tmpl_LDouble_Cbrt(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Ceil                                                      *
 *  Purpose:                                                                  *
 *      Computes the ceiling, the smallest integer greater than the input.    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double ceil_x:                                                        *
 *          The ceiling function evaluated at x.                              *
 ******************************************************************************/
#if TMPL_USE_MATH_ALGORITHMS != 1
#define tmpl_Float_Ceil ceilf
#define tmpl_Double_Ceil ceil
#define tmpl_LDouble_Ceil ceill
#else
extern float tmpl_Float_Ceil(float x);
extern double tmpl_Double_Ceil(double x);
extern long double tmpl_LDouble_Ceil(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cos                                                       *
 *  Purpose:                                                                  *
 *      Computes the cosine of a real number.                                 *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The cosine of x, cos(x).                                          *
 ******************************************************************************/
#if TMPL_USE_MATH_ALGORITHMS == 1
extern float tmpl_Float_Cos(float x);
extern double tmpl_Double_Cos(double x);
extern long double tmpl_LDouble_Cos(long double x);
#else
#define tmpl_Float_Cos cosf
#define tmpl_Double_Cos cos
#define tmpl_LDouble_Cos cosl
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cosd                                                      *
 *  Purpose:                                                                  *
 *      Computes the cosine of a number in degrees.                           *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cosd_x:                                                        *
 *          The cosine of x in degrees.                                       *
 ******************************************************************************/
extern float tmpl_Float_Cosd(float x);
extern double tmpl_Double_Cosd(double x);
extern long double tmpl_LDouble_Cosd(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_CosPi                                                     *
 *  Purpose:                                                                  *
 *      Computes the normalized cosine of a real number, f(x) = cos(pi x).    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_pix:                                                       *
 *          The normalized cosine of x, cos(pi x).                            *
 ******************************************************************************/
extern float tmpl_Float_CosPi(float x);
extern double tmpl_Double_CosPi(double x);
extern long double tmpl_LDouble_CosPi(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cosh                                                      *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic cosine of a real number.                      *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The hyperbolic cosine of x, cosh(x).                              *
 ******************************************************************************/
#if TMPL_USE_MATH_ALGORITHMS == 1
extern float tmpl_Float_Cosh(float x);
extern double tmpl_Double_Cosh(double x);
extern long double tmpl_LDouble_Cosh(long double x);
#else
#define tmpl_Float_Cosh coshf
#define tmpl_Double_Cosh cosh
#define tmpl_LDouble_Cosh coshl
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Erf                                                       *
 *  Purpose:                                                                  *
 *      Computes the error function of a real number.                         *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double erf_x:                                                         *
 *          The error function of x, Erf(x).                                  *
 ******************************************************************************/
extern float tmpl_Float_Erf(float x);
extern double tmpl_Double_Erf(double x);
extern long double tmpl_LDouble_Erf(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Erfc                                                      *
 *  Purpose:                                                                  *
 *      Computes the complementary error function of a real number.           *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double erfc_x:                                                        *
 *          The complementary error function of x, Erfc(x).                   *
 ******************************************************************************/
extern float tmpl_Float_Erfc(float x);
extern double tmpl_Double_Erfc(double x);
extern long double tmpl_LDouble_Erfc(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Erfc                                                      *
 *  Purpose:                                                                  *
 *      Computes the scaled error function of a real number.                  *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double erfcx_x:                                                       *
 *          The scaled error function of x, Erfc(x).                          *
 ******************************************************************************/
extern float tmpl_Float_Erfcx(float x);
extern double tmpl_Double_Erfcx(double x);
extern long double tmpl_LDouble_Erfcx(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp                                                       *
 *  Purpose:                                                                  *
 *      Computes the base e exponential of a real number.                     *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double exp_x:                                                         *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/
extern float tmpl_Float_Exp(float x);
extern double tmpl_Double_Exp(double x);
extern long double tmpl_LDouble_Exp(long double x);

/*  TODO:
 *      For long double, all implementations (extended, quadruple, and
 *      double-double), libtmpl has better performance than glibc and openlibm
 *      for large and small inputs.
 *
 *      For float and double, libtmpl has better performance when |x| < 1.
 *      For |x| >= 1, glibc is about 1.6x faster. libtmpl had better
 *      performance than openlibm in this range as well.
 *      Read through and understand glibc's implementation and try to improve
 *      the exponential functions for float and double precision for |x| >= 1.
 *
 *  TODO:
 *      Fix the neg kernel functions for denormal / subnormal outputs.
 */

/*  TODO:
 *      Exp is well optimized for small arguments.
 *      For |x| < 1 the combination or Pade, Remez, and Maclaurin series does *
 *      very well. The tmpl_Double_Exp_Pos_Kernel function has better         *
 *      performance than openlibm (about 1.4x faster, woohoo!), but worse     *
 *      then glibc (about 0.75x as fast). Try to improve this.                */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Pos_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double exp_x:                                                         *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/

/*  Several functions (exp, cosh, sinh, etc.) benefit from inlining this.     */
#if TMPL_USE_INLINE == 1

/*  Inline support for dist functions found here.                             */
#include <libtmpl/include/inline/math/tmpl_exp_pos_kernel_double.h>
#include <libtmpl/include/inline/math/tmpl_exp_pos_kernel_float.h>
#include <libtmpl/include/inline/math/tmpl_exp_pos_kernel_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support requested.                                              */
extern float tmpl_Float_Exp_Pos_Kernel(float x);
extern double tmpl_Double_Exp_Pos_Kernel(double x);
extern long double tmpl_LDouble_Exp_Pos_Kernel(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Neg_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double exp_x:                                                         *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/

/*  Several functions (exp, cosh, sinh, etc.) benefit from inlining this.     */
#if TMPL_USE_INLINE == 1

/*  Inline support for dist functions found here.                             */
#include <libtmpl/include/inline/math/tmpl_exp_neg_kernel_double.h>
#include <libtmpl/include/inline/math/tmpl_exp_neg_kernel_float.h>
#include <libtmpl/include/inline/math/tmpl_exp_neg_kernel_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support requested.                                              */
extern double tmpl_Double_Exp_Neg_Kernel(double x);
extern float tmpl_Float_Exp_Neg_Kernel(float x);
extern long double tmpl_LDouble_Exp_Neg_Kernel(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Factorial                                                 *
 *  Purpose:                                                                  *
 *      Computes the factorial of an integer, stored as a double.             *
 *  Arguments:                                                                *
 *      unsigned int n:                                                       *
 *          An integer.                                                       *
 *  Output:                                                                   *
 *      double n!:                                                            *
 *          The factorial of n.                                               *
 *  Notes:                                                                    *
 *      Returns +Inf on overflow.                                             *
 ******************************************************************************/
extern float tmpl_Float_Factorial(unsigned int n);
extern double tmpl_Double_Factorial(unsigned int n);
extern long double tmpl_LDouble_Factorial(unsigned int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Faddeeva_Im                                               *
 *  Purpose:                                                                  *
 *      Computes the imaginary part of the Faddeeva function.                 *
 *      Given w(x) = re(x) + i * im(x), this returns im(x).                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double fa_im_x:                                                       *
 *          The imaginary part of the Faddeeva function of x.                 *
 ******************************************************************************/
extern float tmpl_Float_Faddeeva_Im(float x);
extern double tmpl_Double_Faddeeva_Im(double x);
extern long double tmpl_LDouble_Faddeeva_Im(long double x);

extern float
tmpl_Float_Falling_Factorial(unsigned int x, unsigned int N);

extern double
tmpl_Double_Falling_Factorial(unsigned int x, unsigned int N);

extern long double
tmpl_LDouble_Falling_Factorial(unsigned int x, unsigned int N);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Floor                                                     *
 *  Purpose:                                                                  *
 *      Computes the floor function, the largest integer less than the input. *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double floor_x:                                                       *
 *          The floor function evaluated at x.                                *
 ******************************************************************************/
#if TMPL_USE_MATH_ALGORITHMS != 1
#define tmpl_Float_Floor floorf
#define tmpl_Double_Floor floor
#define tmpl_LDouble_Floor floorl
#else
extern float tmpl_Float_Floor(float x);
extern double tmpl_Double_Floor(double x);
extern long double tmpl_LDouble_Floor(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Fractional_Part                                           *
 *  Purpose:                                                                  *
 *      Computes the fractional part of the input.                            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double frac_x:                                                        *
 *          The fractional part of x.                                         *
 ******************************************************************************/
extern float tmpl_Float_Fractional_Part(float x);
extern double tmpl_Double_Fractional_Part(double x);
extern long double tmpl_LDouble_Fractional_Part(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Float_Infinity                                                   *
 *  Purpose:                                                                  *
 *      Returns positive infinity.                                            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      inf (float):                                                          *
 *          Positive infinity.                                                *
 *  NOTE:                                                                     *
 *      Double and long double equivalents are also provided.                 *
 *      If IEEE-754 support is available, this code creates infinity using    *
 *      the format. If not, the function mimics glibc's method, returning     *
 *      the number 1.0E10000 which is guaranteed to overflow.                 *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_infinity.c                                      *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_infinity_example.c                *
 ******************************************************************************/
extern float tmpl_Float_Infinity(void);
extern double tmpl_Double_Infinity(void);
extern long double tmpl_LDouble_Infinity(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Hypot                                                     *
 *  Purpose:                                                                  *
 *      Computes the length of the vector (x, y).                             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double mag:                                                           *
 *          The magnitude of (x, y).                                          *
 ******************************************************************************/
extern float tmpl_Float_Hypot(float x, float y);
extern double tmpl_Double_Hypot(double x, double y);
extern long double tmpl_LDouble_Hypot(long double x, long double y);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Hypot3                                                    *
 *  Purpose:                                                                  *
 *      Computes the length of the vector (x, y, z).                          *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          The x component of the vector.                                    *
 *      double y:                                                             *
 *          The y component of the vector.                                    *
 *      double z:                                                             *
 *          The z component of the vector.                                    *
 *  Output:                                                                   *
 *      double mag:                                                           *
 *          The magnitude of (x, y, z).                                       *
 ******************************************************************************/
extern float tmpl_Float_Hypot3(float x, float y, float z);
extern double tmpl_Double_Hypot3(double x, double y, double z);

extern long double
tmpl_LDouble_Hypot3(long double x, long double y, long double z);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Log                                                       *
 *  Purpose:                                                                  *
 *      Computes the natural log function of the input.                       *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double log_x:                                                         *
 *          The natural log function evaluated at x.                          *
 ******************************************************************************/
extern float tmpl_Float_Log(float x);
extern double tmpl_Double_Log(double x);
extern long double tmpl_LDouble_Log(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Max                                                       *
 *  Purpose:                                                                  *
 *      Compute the maximum of two doubles.                                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double max:                                                           *
 *          The maximum of x and y.                                           *
 ******************************************************************************/
extern float tmpl_Float_Max(float x, float y);
extern double tmpl_Double_Max(double x, double y);
extern long double tmpl_LDouble_Max(long double x, long double y);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Min                                                       *
 *  Purpose:                                                                  *
 *      Compute the minimum of two doubles.                                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double max:                                                           *
 *          The minimum of x and y.                                           *
 ******************************************************************************/
extern float tmpl_Float_Min(float x, float y);
extern double tmpl_Double_Min(double x, double y);
extern long double tmpl_LDouble_Min(long double x, long double y);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Mod_2                                                     *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 2 of the input.              *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double x_mod_2:                                                       *
 *          The value x mod 2.                                                *
 ******************************************************************************/
extern float tmpl_Float_Mod_2(float x);
extern double tmpl_Double_Mod_2(double n);
extern long double tmpl_LDouble_Mod_2(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Mod_360                                                   *
 *  Purpose:                                                                  *
 *      Computes the remainder after division by 360 of the input.            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double x_mod_360:                                                     *
 *          The value x mod 360.                                              *
 ******************************************************************************/
extern float tmpl_Float_Mod_360(float x);
extern double tmpl_Double_Mod_360(double n);
extern long double tmpl_LDouble_Mod_360(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Poly_Eval                                                 *
 *  Purpose:                                                                  *
 *      Given an array of coefficients and a real number, evaluates the       *
 *      the polynomial with the given coefficient at that point.              *
 *  Arguments:                                                                *
 *      double *coeffs:                                                       *
 *          The coefficients. There must be degree + 1 elements in the array. *
 *      size_t degree:                                                        *
 *          The degree of the polynomial.                                     *
 *      double x:                                                             *
 *          The point where the polynomial is being evaluated.                *
 *  Output:                                                                   *
 *      double poly:                                                          *
 *          The polynomial evaluated at x.                                    *
 ******************************************************************************/
extern float
tmpl_Float_Poly_Eval(const float * const coeffs, size_t degree, float x);
extern double

tmpl_Double_Poly_Eval(const double * const coeffs, size_t degree, double x);

extern long double
tmpl_LDouble_Poly_Eval(const long double * const coeffs,
                       size_t degree, long double x);

/*
 *  TODO:
 *    "Safe" eval using double-double arithmetic to avoid precision loss.
 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Poly_First_Deriv_Eval                                     *
 *  Purpose:                                                                  *
 *      Given an array of coefficients and a real number, evaluates the       *
 *      the polynomial with the given coefficient at that point.              *
 *  Arguments:                                                                *
 *      double *coeffs:                                                       *
 *          The coefficients. There must be degree + 1 elements in the array. *
 *      size_t degree:                                                        *
 *          The degree of the polynomial.                                     *
 *      double x:                                                             *
 *          The point where the polynomial is being evaluated.                *
 *  Output:                                                                   *
 *      double poly:                                                          *
 *          The polynomial evaluated at x.                                    *
 ******************************************************************************/
extern float
tmpl_Float_Poly_First_Deriv_Eval(const float * const coeffs,
                                 size_t degree, float x);
extern double

tmpl_Double_Poly_First_Deriv_Eval(const double * const coeffs,
                                  size_t degree, double x);

extern long double
tmpl_LDouble_Poly_First_Deriv_Eval(const long double * const coeffs,
                                   size_t degree, long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Poly_Deriv_Eval                                           *
 *  Purpose:                                                                  *
 *      Given an array of coefficients and a real number, evaluates the nth   *
 *      derivative of the the polynomial at that point.                       *
 *  Arguments:                                                                *
 *      double *coeffs:                                                       *
 *          The coefficients. There must be degree + 1 elements in the array. *
 *      unsigned int degree:                                                  *
 *          The degree of the polynomial.                                     *
 *      unsigned int deriv:                                                   *
 *          The order of the derivative being applied to the polynomial.      *
 *      double x:                                                             *
 *          The point where the polynomial is being evaluated.                *
 *  Output:                                                                   *
 *      double dpoly:                                                         *
 *          The nth derivative of the polynomial evaluated at x.              *
 ******************************************************************************/
extern float
tmpl_Float_Poly_Deriv_Eval(const float * const coeffs,
                           unsigned int degree,
                           unsigned int deriv, float x);

extern double
tmpl_Double_Poly_Deriv_Eval(const double * const coeffs,
                            unsigned int degree,
                            unsigned int deriv, double x);

extern long double
tmpl_LDouble_Poly_Deriv_Eval(const long double *const coeffs,
                             unsigned int degree,
                             unsigned int deriv, long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Pow2                                                      *
 *  Purpose:                                                                  *
 *      Computes an integer power of 2.                                       *
 *  Arguments:                                                                *
 *      signed int expo:                                                      *
 *          An, the power of 2.                                               *
 *  Output:                                                                   *
 *      double pow2_expo:                                                     *
 *          The value 2^expo.                                                 *
 ******************************************************************************/
extern float tmpl_Float_Pow2(signed int expo);
extern double tmpl_Double_Pow2(signed int expo);
extern long double tmpl_LDouble_Pow2(signed int expo);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sinc                                                      *
 *  Purpose:                                                                  *
 *      Computes the sinc function sinc(x) = sin(x)/x (with limit 1 at x = 0).*
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sinc_x:                                                        *
 *          The sinc of x.                                                    *
 ******************************************************************************/
extern float tmpl_Float_Sinc(float x);
extern double tmpl_Double_Sinc(double x);
extern long double tmpl_LDouble_Sinc(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SincPi                                                    *
 *  Purpose:                                                                  *
 *      Computes the normalized sinc function sinc(x) = sin(pi x)/(pi x).     *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sincpi_x:                                                      *
 *          The normalized sinc of x.                                         *
 ******************************************************************************/
extern float tmpl_Float_SincPi(float x);
extern double tmpl_Double_SincPi(double x);
extern long double tmpl_LDouble_SincPi(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sin                                                       *
 *  Purpose:                                                                  *
 *      Computes the sine function sin(x).                                    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_x:                                                         *
 *          The sine of x.                                                    *
 ******************************************************************************/
#if TMPL_USE_MATH_ALGORITHMS == 1
extern float tmpl_Float_Sin(float x);
extern double tmpl_Double_Sin(double x);
extern long double tmpl_LDouble_Sin(long double x);
#else
#define tmpl_Float_Sin sinf
#define tmpl_Double_Sin sin
#define tmpl_LDouble_Sin sinl
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinCos                                                    *
 *  Purpose:                                                                  *
 *      Computes the point on a circle corresponding to a given angle.        *
 *  Arguments:                                                                *
 *      double t:                                                             *
 *          A real number.                                                    *
 *      double *sin_t:                                                        *
 *          A pointer to the y-coordinate of the point on the circle.         *
 *      double *cos_t:                                                        *
 *          A pointer to the x-coordinate of the point on the circle.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Float_SinCos(float t, float *sin_t, float *cos_t);
extern void tmpl_Double_SinCos(double t, double *sin_t, double *cos_t);

extern void
tmpl_LDouble_SinCos(long double t, long double *sin_t, long double *cos_t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinCosd                                                   *
 *  Purpose:                                                                  *
 *      Computes the point on a circle from an angle given in degrees.        *
 *  Arguments:                                                                *
 *      double t:                                                             *
 *          The angle in degrees.                                             *
 *      double *sind_t:                                                       *
 *          A pointer to the y-coordinate of the point on the circle.         *
 *      double *cosd_t:                                                       *
 *          A pointer to the x-coordinate of the point on the circle.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Float_SinCosd(float t, float *sind_t, float *cosd_t);
extern void tmpl_Double_SinCosd(double t, double *sind_t, double *cosd_t);

extern void
tmpl_LDouble_SinCosd(long double t, long double *sind_t, long double *cosd_t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinCosPi                                                  *
 *  Purpose:                                                                  *
 *      Computes the point on a circle from a given normalized angle.         *
 *  Arguments:                                                                *
 *      double t:                                                             *
 *          A real number.                                                    *
 *      double *sinpi_t:                                                      *
 *          A pointer to the y-coordinate of the point on the circle.         *
 *      double *cospi_t:                                                      *
 *          A pointer to the x-coordinate of the point on the circle.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Float_SinCosPi(float t, float *sinpi_t, float *cospi_t);
extern void tmpl_Double_SinCosPi(double t, double *sinpi_t, double *cospi_t);

extern void
tmpl_LDouble_SinCosPi(long double t,
                      long double *sinpi_t,
                      long double *cospi_t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sind                                                      *
 *  Purpose:                                                                  *
 *      Computes the sine of a number in degrees.                             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sind_x:                                                        *
 *          The sine of x in degrees.                                         *
 ******************************************************************************/
extern float tmpl_Float_Sind(float x);
extern double tmpl_Double_Sind(double x);
extern long double tmpl_LDouble_Sind(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sinh                                                      *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic sine function sinh(x).                        *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sinh_x:                                                        *
 *          The hyperbolic sine of x.                                         *
 ******************************************************************************/
extern float tmpl_Float_Sinh(float x);
extern double tmpl_Double_Sinh(double x);
extern long double tmpl_LDouble_Sinh(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinhCosh                                                  *
 *  Purpose:                                                                  *
 *      Computes the point on a "hyperblic" circle corresponding to angle t.  *
 *  Arguments:                                                                *
 *      double t:                                                             *
 *          A real number.                                                    *
 *      double *sinh_t:                                                       *
 *          A pointer to a double. sinh(t) is stored here.                    *
 *      double *cosh_t:                                                       *
 *          A pointer to a double. cosh(t) is stored here.                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Float_SinhCosh(float t, float *sinh_t, float *cosh_t);
extern void tmpl_Double_SinhCosh(double t, double *sinh_t, double *cosh_t);

extern void
tmpl_LDouble_SinhCosh(long double t, long double *sinh_t, long double *cosh_t);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinPi                                                     *
 *  Purpose:                                                                  *
 *      Computes the normalized sine of a real number, f(x) = sin(pi x).      *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_pix:                                                       *
 *          The normalized sine of x, sin(pi x).                              *
 ******************************************************************************/
extern float tmpl_Float_SinPi(float x);
extern double tmpl_Double_SinPi(double x);
extern long double tmpl_LDouble_SinPi(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes the square root function sqrt(x).                            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sqrt_x:                                                        *
 *          The square root of x.                                             *
 ******************************************************************************/
extern float tmpl_Float_Sqrt(float x);
extern double tmpl_Double_Sqrt(double x);
extern long double tmpl_LDouble_Sqrt(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Tan                                                       *
 *  Purpose:                                                                  *
 *      Computes the tangent function tan(x).                                 *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double tan_x:                                                         *
 *          The tangent of x.                                                 *
 ******************************************************************************/
extern float tmpl_Float_Tan(float x);
extern double tmpl_Double_Tan(double x);
extern long double tmpl_LDouble_Tan(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Tanh                                                      *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic tangent function tanh(x).                     *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double tanh_x:                                                        *
 *          The hyperbolic tangent of x.                                      *
 ******************************************************************************/
extern float tmpl_Float_Tanh(float x);
extern double tmpl_Double_Tanh(double x);
extern long double tmpl_LDouble_Tanh(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Truncate                                                  *
 *  Purpose:                                                                  *
 *      Computes the truncation (round to zero) of the input.                 *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double trunc_x:                                                       *
 *          The truncation of x.                                              *
 ******************************************************************************/
extern float tmpl_Float_Truncate(float x);
extern double tmpl_Double_Truncate(double x);
extern long double tmpl_LDouble_Truncate(long double x);

/*  Macro for positive infinity                                               */
#define TMPL_INFINITYF (tmpl_Float_Infinity())
#define TMPL_INFINITY (tmpl_Double_Infinity())
#define TMPL_INFINITYL (tmpl_LDouble_Infinity())

/******************************************************************************
 *                       Independent Inlined Functions                        *
 ******************************************************************************/

/*  These functions make no calls to external routines and are completely     *
 *  self-contained. They are also small enough that they should be inlined.   */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Compute the absolute value of a real number (fabs equivalent).        *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double abs_x:                                                         *
 *          The absolute value of x, |x|.                                     *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *  Source Code:                                                              *
 *      libtmpl/src/math/                                                     *
 *          tmpl_abs_float.c                                                  *
 *          tmpl_abs_double.c                                                 *
 *          tmpl_abs_ldouble.c                                                *
 *      libtmpl/include/inline/math/ (inline version)                         *
 *          tmpl_abs_double.h                                                 *
 *          tmpl_abs_float.h                                                  *
 *          tmpl_abs_ldouble.h                                                *
 ******************************************************************************/

/*  Alias functions to fabs from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Abs fabsf
#define tmpl_Double_Abs fabs
#define tmpl_LDouble_Abs fabsl

/*  The absolute value function is small enough that a user may want to       *
 *  inline it. The result of inlining gives a surprising 2x speed boost. The  *
 *  absolute value function is not computationally expensive regardless.      */
#elif TMPL_USE_INLINE == 1

/*  Inline support for absolute value functions are found here.               */
#include <libtmpl/include/inline/math/tmpl_abs_float.h>
#include <libtmpl/include/inline/math/tmpl_abs_double.h>
#include <libtmpl/include/inline/math/tmpl_abs_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Inline not requested, use the external functions in src/math.             */
extern float tmpl_Float_Abs(float x);
extern double tmpl_Double_Abs(double x);
extern long double tmpl_LDouble_Abs(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Clamp                                                     *
 *  Purpose:                                                                  *
 *      Clamps a real number to fall with a given range [min, max].           *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      min (double):                                                         *
 *          The minimum allowed value for x.                                  *
 *      max (double):                                                         *
 *          The maximum allowed value for x.                                  *
 *  Output:                                                                   *
 *      clamped_x (double):                                                   *
 *          The clamped value of x. If x is less than min, min is returned.   *
 *          If x is greater than max, max is returned. Otherwise, return x.   *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/inline/math/tmpl_clamp_float.h>
#include <libtmpl/include/inline/math/tmpl_clamp_double.h>
#include <libtmpl/include/inline/math/tmpl_clamp_ldouble.h>

#else

extern double tmpl_Double_Clamp(double x, double min, double max);
extern float tmpl_Float_Clamp(float x, float min, float max);

extern long double
tmpl_LDouble_Clamp(long double x, long double min, long double max);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Unit_Clamp                                                *
 *  Purpose:                                                                  *
 *      Clamps a real number to fall within the range [0, 1].                 *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      clamped_x (double):                                                   *
 *          The clamped value of x. The output falls in the unit interval.    *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 ******************************************************************************/

#if TMPL_USE_INLINE == 1

#include <libtmpl/include/inline/math/tmpl_unit_clamp_float.h>
#include <libtmpl/include/inline/math/tmpl_unit_clamp_double.h>
#include <libtmpl/include/inline/math/tmpl_unit_clamp_ldouble.h>

#else

extern double tmpl_Double_Unit_Clamp(double x);
extern float tmpl_Float_Unit_Clamp(float x);
extern long double tmpl_LDouble_Unit_Clamp(long double x);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Copysign                                                  *
 *  Purpose:                                                                  *
 *      Given two numbers x and y, returns a value that has the magnitude of  *
 *      x and the sign of y.                                                  *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double z:                                                             *
 *          The value sgn(y) * |x|.                                           *
 ******************************************************************************/

/*  Alias functions to copysign if libtmpl algorithms not requested.          */
#if TMPL_USE_MATH_ALGORITHMS != 1
#define tmpl_Float_Copysign copysignf
#define tmpl_Double_Copysign copysign
#define tmpl_LDouble_Copysign copysignl

/*  These functions are small enough that it's worth-while inlining them.     */
#elif TMPL_USE_INLINE == 1

/*  Inline support to copysign found here.                                    */
#include <libtmpl/include/inline/math/tmpl_copysign_double.h>
#include <libtmpl/include/inline/math/tmpl_copysign_float.h>
#include <libtmpl/include/inline/math/tmpl_copysign_ldouble.h>

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1.                               */

/*  No inline support requested.                                              */
extern float tmpl_Float_Copysign(float x, float y);
extern double tmpl_Double_Copysign(double x, double y);
extern long double tmpl_LDouble_Copysign(long double x, long double y);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_CosPi_Pade                                                *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of the normalized cosine, cos(pi x).    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_pix:                                                       *
 *          The normalized cosine of x, cos(pi x).                            *
 ******************************************************************************/
extern float tmpl_Float_CosPi_Pade(float x);
extern double tmpl_Double_CosPi_Pade(double x);
extern long double tmpl_LDouble_CosPi_Pade(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Dist                                                      *
 *  Purpose:                                                                  *
 *      Compute the distance between two numbers on the real line.            *
 *  Arguments:                                                                *
 *      double y:                                                             *
 *          A real number.                                                    *
 *      double x:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double dist:                                                          *
 *          The distance |x - y|.                                             *
 ******************************************************************************/

/*  These functions should be inlined.                                        */
#if TMPL_USE_INLINE == 1

/*  Inline support for dist functions found here.                             */
#include <libtmpl/include/inline/math/tmpl_dist_double.h>
#include <libtmpl/include/inline/math/tmpl_dist_float.h>
#include <libtmpl/include/inline/math/tmpl_dist_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support requested.                                              */
extern float tmpl_Float_Dist(float x, float y);
extern double tmpl_Double_Dist(double x, double y);
extern long double tmpl_LDouble_Dist(long double x, long double y);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Is_Inf                                                    *
 *  Purpose:                                                                  *
 *      This function tests if a number is positive or negative infinity.     *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_inf (tmpl_Bool):                                                   *
 *          A Boolean indicating if x is +/- infinity or not.                 *
 *  Notes:                                                                    *
 *      Float and long double equivalents are also provided.                  *
 *  Source Code:                                                              *
 *      libtmpl/include/inline/math/                                          *
 *          tmpl_is_inf_double.h                                              *
 *          tmpl_is_inf_float.h                                               *
 *          tmpl_is_inf_ldouble.h                                             *
 ******************************************************************************/

/*  Alias functions to isinf from math.h if libtmpl algorithms not requested. */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Is_Inf isinff
#define tmpl_Double_Is_Inf isinf
#define tmpl_LDouble_Is_Inf isinfl

/*  These functions are small enough that they should be inlined.             */
#elif TMPL_USE_INLINE == 1

/*  Inline support for is_inf functions are found here.                       */
#include <libtmpl/include/inline/math/tmpl_is_inf_float.h>
#include <libtmpl/include/inline/math/tmpl_is_inf_double.h>
#include <libtmpl/include/inline/math/tmpl_is_inf_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Inline not requested, use the external functions in src/math.             */
extern tmpl_Bool tmpl_Float_Is_Inf(float x);
extern tmpl_Bool tmpl_Double_Is_Inf(double x);
extern tmpl_Bool tmpl_LDouble_Is_Inf(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Is_NaN                                                    *
 *  Purpose:                                                                  *
 *      This function tests if a number is Not-a-Number.                      *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan (tmpl_Bool):                                                   *
 *          A Boolean indicating if x is NaN or not.                          *
 *  NOTE:                                                                     *
 *      Float and long double equivalents are also provided.                  *
 *  Source Code:                                                              *
 *      libtmpl/include/inline/math/                                          *
 *          tmpl_is_nan_double.h                                              *
 *          tmpl_is_nan_float.h                                               *
 *          tmpl_is_nan_ldouble.h                                             *
 ******************************************************************************/

/*  Alias functions to isnan from math.h if libtmpl algorithms not requested. */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Is_NaN isnan
#define tmpl_Double_Is_NaN isnan
#define tmpl_LDouble_Is_NaN isnan

/*  These functions are small enough that they should be inlined.             */
#elif TMPL_USE_INLINE == 1

/*  Inline support for is_nan functions are found here.                       */
#include <libtmpl/include/inline/math/tmpl_is_nan_float.h>
#include <libtmpl/include/inline/math/tmpl_is_nan_double.h>
#include <libtmpl/include/inline/math/tmpl_is_nan_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Inline not requested, use the external functions in src/math.             */
extern tmpl_Bool tmpl_Float_Is_NaN(float x);
extern tmpl_Bool tmpl_Double_Is_NaN(double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN(long double x);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Float_Is_NaN_Or_Inf                                              *
 *  Purpose:                                                                  *
 *      This function tests if a number is Not-a-Number or infinity.          *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan_or_inf (tmpl_Bool):                                            *
 *          A Boolean indicating if x is +/- nan/inf or not.                  *
 *  NOTE:                                                                     *
 *      Double and long double equivalents are also provided.                 *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_is_nan_or_inf.c                                 *
 ******************************************************************************/

/*  These functions are small enough that they should be inlined.             */
#if TMPL_USE_INLINE == 1

/*  Inline support for these functions are found here.                        */
#include <libtmpl/include/inline/math/tmpl_is_nan_or_inf_float.h>
#include <libtmpl/include/inline/math/tmpl_is_nan_or_inf_double.h>
#include <libtmpl/include/inline/math/tmpl_is_nan_or_inf_ldouble.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Inline not requested, use the external functions in src/math.             */
extern tmpl_Bool tmpl_Float_Is_NaN_Or_Inf(float x);
extern tmpl_Bool tmpl_Double_Is_NaN_Or_Inf(double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *                        Dependent Inlined Functions                         *
 ******************************************************************************/

/*  Either the IEEE-754 version or the portable version (or both) of these    *
 *  functions make calls to external routines.                                */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Positive_Arctan2                                          *
 *  Purpose:                                                                  *
 *      Computes the positive angle the point (y, x) makes with the x axis.   *
 *  Arguments:                                                                *
 *      y (double):                                                           *
 *          A real number.                                                    *
 *      x (double):                                                           *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      angle (double):                                                       *
 *          The positive angle the point (x, y) makes with the x axis.        *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1

#include <libtmpl/include/inline/math/tmpl_positive_arctan2_float.h>
#include <libtmpl/include/inline/math/tmpl_positive_arctan2_double.h>
#include <libtmpl/include/inline/math/tmpl_positive_arctan2_ldouble.h>

#else

extern float tmpl_Float_Positive_Arctan2(float y, float x);
extern double tmpl_Double_Positive_Arctan2(double y, double x);
extern long double tmpl_LDouble_Positive_Arctan2(long double y, long double x);

#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Positive_Difference                                       *
 *  Purpose:                                                                  *
 *      Computes the "positive difference" of two real numbers. Equivalent to *
 *      the C99 function "fdim". Returns max(x-y, 0).                         *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *      double y:                                                             *
 *          Another real number.                                              *
 *  Output:                                                                   *
 *      double fdim:                                                          *
 *          The positive difference of x with respect to y, max(x-y, 0).      *
 ******************************************************************************/

/*  Alias functions to fdim from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1

#define tmpl_Float_Positive_Difference fdimf
#define tmpl_Double_Positive_Difference fdim
#define tmpl_LDouble_Positive_Difference fdiml

/*  These functions are small enough that they can be inlined.                */
#elif TMPL_USE_INLINE == 1

/*  Inline support for positive difference functions are found here.          */
#include <libtmpl/include/inline/math/tmpl_positive_difference_float.h>
#include <libtmpl/include/inline/math/tmpl_positive_difference_double.h>
#include <libtmpl/include/inline/math/tmpl_positive_difference_ldouble.h>

#else
/*  Else for #elif TMPL_USE_INLINE == 1.                                      */

/*  Otherwise use the functions in src/math/                                  */
extern float tmpl_Float_Positive_Difference(float x, float y);
extern double tmpl_Double_Positive_Difference(double x, double y);

extern long double
tmpl_LDouble_Positive_Difference(long double x, long double y);

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Quick_Hypot                                               *
 *  Purpose:                                                                  *
 *      Computes the length of a vector in the plane.                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x component of the vector.                                    *
 *      y (double):                                                           *
 *          The y component of the vector.                                    *
 *  Output:                                                                   *
 *      mag (double):                                                         *
 *          The magnitude of (x, y).                                          *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *      This function does not prevent overflow or underflow. If very large   *
 *      or very small inputs, use tmpl_Double_Hypot.                          *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/inline/math/tmpl_quick_hypot_float.h>
#include <libtmpl/include/inline/math/tmpl_quick_hypot_double.h>
#include <libtmpl/include/inline/math/tmpl_quick_hypot_ldouble.h>
#else
extern double tmpl_Double_Quick_Hypot(double x, double y);
extern float tmpl_Float_Quick_Hypot(float x, float y);
extern long double tmpl_LDouble_Quick_Hypot(long double x, long double y);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Quick_Hypot3                                              *
 *  Purpose:                                                                  *
 *      Computes the length of a vector in space.                             *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          The x component of the vector.                                    *
 *      y (double):                                                           *
 *          The y component of the vector.                                    *
 *      z (double):                                                           *
 *          The z component of the vector.                                    *
 *  Output:                                                                   *
 *      mag (double):                                                         *
 *          The magnitude of (x, y, z).                                       *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *      This function does not prevent overflow or underflow. If very large   *
 *      or very small inputs, use tmpl_Double_Hypot3.                         *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/inline/math/tmpl_quick_hypot3_float.h>
#include <libtmpl/include/inline/math/tmpl_quick_hypot3_double.h>
#include <libtmpl/include/inline/math/tmpl_quick_hypot3_ldouble.h>
#else
extern double tmpl_Double_Quick_Hypot3(double x, double y, double z);
extern float tmpl_Float_Quick_Hypot3(float x, float y, float z);

extern long double
tmpl_LDouble_Quick_Hypot3(long double x, long double y, long double z);
#endif

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
