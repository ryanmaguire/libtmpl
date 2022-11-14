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
 *      provided in other implementations, such as glibc or open libm. The    *
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
 *          They way glibc implements infinity for compilers lacking IEEE-754 *
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
 *  1.) stdlib.h:                                                             *
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
#include <stdlib.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Whether or not we're building with inline support is here and whether or  *
 *  not we're using libtmpl's implementation of libm. Endianness macros are   *
 *  also found here.                                                          */
#include <libtmpl/include/tmpl_config.h>

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

/*  Check if TMPL_FLOAT_ENDIANNESS was defined in tmpl_config.h. It           *
 *  should be unless there was a problem when building libtmpl.               */
#if !defined(TMPL_FLOAT_ENDIANNESS)

/*  If not, there is a problem with libtmpl. Abort compiling.                 */
#error "tmpl_math.h: TMPL_FLOAT_ENDIANNESS is undefined."

#elif TMPL_FLOAT_ENDIANNESS == TMPL_BIG_ENDIAN
/*  Else statement for #if !defined(TMPL_FLOAT_ENDIANNESS).                   */

/*  Macro indicating support for IEEE-754 single precision.                   */
#define TMPL_HAS_IEEE754_FLOAT 1

/*  32-bit single precision bias is 127.                                      */
#define TMPL_FLOAT_BIAS (0x7F)
#define TMPL_FLOAT_UBIAS (0x7FU)

/*  The exponent that corresponds to NaN/infinity for 32-bit float.           */
#define TMPL_FLOAT_NANINF_EXP (0xFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_FLOAT_MANTISSA_LENGTH (23)
#define TMPL_FLOAT_MANTISSA_ULENGTH (23U)

/*  The value 2^23, used to normalize subnormal/denormal values.              */
#define TMPL_FLOAT_NORMALIZE (8.388608E+06F)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_FLOAT_IS_NAN_OR_INF(w) ((w).bits.expo == 0xFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_FLOAT_IS_NAN(w) (((w).bits.man0 || (w).bits.man1))

/*  To access the binary representation of a floating point number, we use    *
 *  unions. Unions allow us to have different data types share the same block *
 *  of memory. If we have a union of a floating point and an integer, and then*
 *  set the floating point part to some number, then when we try to access the*
 *  integer part it will already have its bits set (They'll be set by the     *
 *  floating point value). This is known as "type-punning." Note, the C       *
 *  standard says type-punning is undefined behavior. Indeed, it says you can *
 *  only access the member of a union that was most recently written to. In   *
 *  practice, most compilers support type punning and use it to implement the *
 *  IEEE-754 format of floating point arithmetic.                             */
typedef union tmpl_IEEE754_Float_Def {

    /*  Use a bit-field for the binary representation of a float. A bit-field *
     *  allows us to define variables with an exact number of bits (up to 16).*
     *  We'll use this to have a 1-bit variable for the sign, 8-bit variable  *
     *  for the exponent, and 2 variables adding up to 23 bits for the        *
     *  mantissa.                                                             */
    struct {
        /*  The notation x : n; means x will be a variable in the struct with *
         *  exactly n bits reserved. So unsigned int sign : 1; means the      *
         *  variable "sign" will have exactly 1 bit reserved for it.          */
        unsigned int sign : 1;
        unsigned int expo : 8;
        unsigned int man0 : 7;
        unsigned int man1 : 16;
    } bits;

    /*  The above struct holds 32-bits, which the IEEE-754 format specifies   *
     *  as the size of a single-precision float. This is "float" in C.        */
    float r;
} tmpl_IEEE754_Float;

#elif TMPL_FLOAT_ENDIANNESS == TMPL_LITTLE_ENDIAN
/*  Else statement for #if !defined(TMPL_FLOAT_ENDIANNESS).                   */

/*  Macro indicating support for IEEE-754 single precision.                   */
#define TMPL_HAS_IEEE754_FLOAT 1

/*  32-bit single precision bias is 127.                                      */
#define TMPL_FLOAT_BIAS (0x7F)
#define TMPL_FLOAT_UBIAS (0x7FU)

/*  The exponent that corresponds to NaN/infinity for 32-bit float.           */
#define TMPL_FLOAT_NANINF_EXP (0xFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_FLOAT_MANTISSA_LENGTH (23)
#define TMPL_FLOAT_MANTISSA_ULENGTH (23U)

/*  The value 2**23, used to normalize subnormal/denormal values.             */
#define TMPL_FLOAT_NORMALIZE (8.388608E+06F)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_FLOAT_IS_NAN_OR_INF(w) ((w).bits.expo == 0xFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_FLOAT_IS_NAN(w) (((w).bits.man0 || (w).bits.man1))

/*  Same type of union as above, but for little endian. See the above union   *
 *  for comments on this data type. Little endianness simply means we need    *
 *  to swap the order of the bit-field in the union.                          */
typedef union tmpl_IEEE754_Float_Def {
    struct {
        unsigned int man1 : 16;
        unsigned int man0 : 7;
        unsigned int expo : 8;
        unsigned int sign : 1;
    } bits;
    float r;
} tmpl_IEEE754_Float;

#else
/*  Else statement for #if !defined(TMPL_FLOAT_ENDIANNESS).                   */

/*  The macro TMPL_FLOAT_ENDIANNESS is likely set to unknown endian, meaning  *
 *  we can't assume IEEE-754 support. Set TMPL_HAS_IEEE754_FLOAT to zero.     */
#define TMPL_HAS_IEEE754_FLOAT 0

#endif
/*  End of #if !defined(TMPL_FLOAT_ENDIANNESS).                               */

/*  Same thing for double precision.                                          */
#if !defined(TMPL_DOUBLE_ENDIANNESS)

/*  If TMPL_DOUBLE_ENDIANNESS is undefined, there is a problem with libtmpl.  *
 *  Abort compiling.                                                          */
#error "tmpl_math.h: TMPL_DOUBLE_ENDIANNESS is undefined."

#elif TMPL_DOUBLE_ENDIANNESS == TMPL_BIG_ENDIAN
/*  Else statement for #if !defined(TMPL_DOUBLE_ENDIANNESS).                  */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_DOUBLE 1

/*  64-bit double precision has exponent bias of 1,023.                       */
#define TMPL_DOUBLE_BIAS (0x3FF)
#define TMPL_DOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 64-bit double.          */
#define TMPL_DOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_DOUBLE_MANTISSA_LENGTH (52)
#define TMPL_DOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_DOUBLE_NORMALIZE (4.503599627370496E+15)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_DOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_DOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Same idea as the union used for float, but for a 64-bit double.           */
typedef union tmpl_IEEE754_Double_Def {
    struct {
        unsigned int sign : 1;
        unsigned int expo : 11;
        unsigned int man0 : 4;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;
    } bits;
    double r;
} tmpl_IEEE754_Double;

#elif TMPL_DOUBLE_ENDIANNESS == TMPL_LITTLE_ENDIAN
/*  Else statement for #if !defined(TMPL_DOUBLE_ENDIANNESS).                  */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_DOUBLE 1

/*  64-bit double precision has exponent bias of 1,023.                       */
#define TMPL_DOUBLE_BIAS (0x3FF)
#define TMPL_DOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 64-bit double.          */
#define TMPL_DOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_DOUBLE_MANTISSA_LENGTH (52)
#define TMPL_DOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_DOUBLE_NORMALIZE (4.503599627370496E+15)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_DOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_DOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Same idea as the 32-bit union, but for 64-bit double, and with little     *
 *  endianness. See the above comments for information on this data type.     */
typedef union tmpl_IEEE754_Double_Def {
    struct {
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 4;
        unsigned int expo : 11;
        unsigned int sign : 1;
    } bits;
    double r;
} tmpl_IEEE754_Double;

#else
/*  Else statement for #if !defined(TMPL_DOUBLE_ENDIANNESS).                  */

/*  TMPL_DOUBLE_ENDIANNESS is likely set to unknown. Set this to zero.        */
#define TMPL_HAS_IEEE754_DOUBLE 0

#endif
/*  End of #if !defined(TMPL_DOUBLE_ENDIANNESS).                              */

/*  Same thing for long double. Long double is not as standardized as float   *
 *  and double and there are several ways to implement it. This includes      *
 *  64-bit, 80-bit, 96-bit, and 128-bit implementations, and with big or      *
 *  little endianness. The macro TMPL_LDOUBLE_ENDIANNESS contains this        *
 *  information.                                                              */
#if !defined(TMPL_LDOUBLE_ENDIANNESS)

/*  If TMPL_LDOUBLE_ENDIANNESS is undefined, there is a problem with libtmpl. *
 *  Abort compiling.                                                          */
#error "tmpl_math.h: TMPL_LDOUBLE_ENDIANNESS is undefined."

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  64-bit double precision has exponent bias of 1,023.                       */
#define TMPL_LDOUBLE_BIAS (0x3FF)
#define TMPL_LDOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 64-bit double.          */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (52)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (4.503599627370496E+15L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  MIPS little endian uses the same structure as double, 64 bit. The         *
 *  Microsoft compiler MSVC also uses this for x86_64.                        */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 4;
        unsigned int expo : 11;
        unsigned int sign : 1;
    } bits;
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  64-bit double precision has exponent bias of 1,023.                       */
#define TMPL_LDOUBLE_BIAS (0x3FF)
#define TMPL_LDOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 64-bit double.          */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (52)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (4.503599627370496E+15L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  MIPS for big endian. PowerPC and S390 also implement long double          *
 *  using this style, which is the same as double.                            */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int sign : 1;
        unsigned int expo : 11;
        unsigned int man0 : 4;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;
    } bits;
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  80-bit extended precision has exponent bias of 16,383.                    */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 80-bit long double.     */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (63)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (63U)

/*  The value 2**63, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (9.223372036854775808E+18L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  The i386 architecture uses a 96-bit implementation. This uses the         *
 *  80-bit extended precision with 16 bits of padding.                        */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 15;
        unsigned int intr : 1;
        unsigned int expo : 15;
        unsigned int sign : 1;
        unsigned int pad0 : 16;
    } bits;

    /*  Long double the above struct represents.                              */
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  80-bit extended precision has exponent bias of 16,383.                    */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 80-bit long double.     */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (63)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (63U)

/*  The value 2**63, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (9.223372036854775808E+18L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  Big endian version of i386 method.                                        */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int sign : 1;
        unsigned int expo : 15;
        unsigned int pad0 : 16;
        unsigned int intr : 1;
        unsigned int man0 : 15;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;
    } bits;

    /*  Long double the above struct represents.                              */
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  80-bit extended precision has exponent bias of 16,383.                    */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 80-bit long double.     */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (63)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (63U)

/*  The value 2**63, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (9.223372036854775808E+18L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  The most common type of long double for personal computers is the         *
 *  little endian amd64 format (also the x86_64 format). This uses            *
 *  the IEEE-754 extended precision 80-bit format with 48-bits of padding     *
 *  to create a single 128-bit object. The padding components are junk        *
 *  and can almost always be ignored.                                         */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 15;

        /*  The 80-bit extended format specifies that the 64th bit is the     *
         *  integer part of the mantissa. That is, the value n in the         *
         *  representation x = n.m * 2^e (m is the rest of the mantissa,      *
         *  e is the exponent). It is a single bit and can be 0 or 1.         */
        unsigned int intr : 1;
        unsigned int expo : 15;
        unsigned int sign : 1;
        unsigned int pad2 : 16;
        unsigned int pad1 : 16;
        unsigned int pad0 : 16;
    } bits;

    /*  Long double the above struct represents.                              */
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  80-bit extended precision has exponent bias of 16,383.                    */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 80-bit long double.     */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FFF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (63)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (63U)

/*  The value 2**63, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (9.223372036854775808E+18L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  Big endian version of the amd64 method. GCC uses this for ia64.           */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int pad0 : 16;
        unsigned int pad1 : 16;
        unsigned int sign : 1;
        unsigned int expo : 15;
        unsigned int pad2 : 16;
        unsigned int intr : 1;
        unsigned int man3 : 15;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 16;
    } bits;

    /*  Long double the above struct represents.                              */
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  128-bit quadruple precision has exponent bias of 16,383.                  */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 128-bit long double.    */
#define TMPL_LDOUBLE_NANINF_EXP 0x7FFF

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (112)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (112U)

/*  The value 2**112, used to normalize subnormal/denormal values.            */
#define TMPL_LDOUBLE_NORMALIZE (5.192296858534827628530496329220096E+33L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || \
  (w).bits.man3 || (w).bits.man4 || (w).bits.man5 || (w).bits.man6))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  aarch64 uses the 128-bit quadruple precision for long double.             */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int man6 : 16;
        unsigned int man5 : 16;
        unsigned int man4 : 16;
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 16;
        unsigned int expo : 15;
        unsigned int sign : 1;
    } bits;
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  128-bit quadruple precision has exponent bias of 16,383.                  */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for 128-bit long double.    */
#define TMPL_LDOUBLE_NANINF_EXP 0x7FFF

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (112)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (112U)

/*  The value 2**112, used to normalize subnormal/denormal values.            */
#define TMPL_LDOUBLE_NORMALIZE (5.192296858534827628530496329220096E+33L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || \
  (w).bits.man3 || (w).bits.man4 || (w).bits.man5 || (w).bits.man6))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

/*  Similar to aarch64, but with big endianness.                              */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int sign : 1;
        unsigned int expo : 15;
        unsigned int man0 : 16;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;
        unsigned int man4 : 16;
        unsigned int man5 : 16;
        unsigned int man6 : 16;
    } bits;
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  128-bit double-double has exponent bias of 1,023, same as double.         */
#define TMPL_LDOUBLE_BIAS (0x3FF)
#define TMPL_LDOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 128-bit double-double.  */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (52)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (4.503599627370496E+15L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expoa == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0a || (w).bits.man1a || (w).bits.man2a || (w).bits.man3a))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expoa)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.signa)

/*  Double-double representation. Literally two doubles stacked together.     */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        /*  The most significant double.                                      */
        unsigned int man3a : 16;
        unsigned int man2a : 16;
        unsigned int man1a : 16;
        unsigned int man0a : 4;
        unsigned int expoa : 11;
        unsigned int signa : 1;

        /*  The least significant double.                                     */
        unsigned int man3b : 16;
        unsigned int man2b : 16;
        unsigned int man1b : 16;
        unsigned int man0b : 4;
        unsigned int expob : 11;
        unsigned int signb : 1;
    } bits;

    /*  The two doubles making up r. r = d[0] + d[1].                         */
    double d[2];

    /*  The long double the bits represent.                                   */
    long double r;
} tmpl_IEEE754_LDouble;

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  128-bit double-double has exponent bias of 1,023, same as double.         */
#define TMPL_LDOUBLE_BIAS (0x3FF)
#define TMPL_LDOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 128-bit double-double.  */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (52)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal/denormal values.             */
#define TMPL_LDOUBLE_NORMALIZE (4.503599627370496E+15L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expoa == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0a || (w).bits.man1a || (w).bits.man2a || (w).bits.man3a))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expoa)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.signa)

/*  Big endian version of double-double. Same as little with order flipped.   */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        /*  The most significant double.                                      */
        unsigned int signa : 1;
        unsigned int expoa : 11;
        unsigned int man0a : 4;
        unsigned int man1a : 16;
        unsigned int man2a : 16;
        unsigned int man3a : 16;

        /*  The least significant double.                                     */
        unsigned int signb : 1;
        unsigned int expob : 11;
        unsigned int man0b : 4;
        unsigned int man1b : 16;
        unsigned int man2b : 16;
        unsigned int man3b : 16;
    } bits;

    /*  The two doubles making up r. r = d[0] + d[1].                         */
    double d[2];

    /*  The long double the bits represent.                                   */
    long double r;
} tmpl_IEEE754_LDouble;

#else
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  No support for IEEE-754 long double. Set this to zero.                    */
#define TMPL_HAS_IEEE754_LDOUBLE 0

#endif
/*  End of #if !defined(TMPL_LDOUBLE_ENDIANNESS).                             */

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

#ifndef TMPL_LDOUBLE_EXPO_BITS
#error "tmpl_math.h: TMPL_LDOUBLE_EXPO_BITS undefined."
#endif

#ifndef TMPL_LDOUBLE_IS_NEGATIVE
#error "tmpl_math.h: TMPL_LDOUBLE_IS_NEGATIVE undefined."
#endif

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

/* Declare Miscellaneous Constants.                                           */

/*  sqrt( 1 / (2pi) )                                                         */
extern const float tmpl_Sqrt_One_By_Two_Pi_F;
extern const double tmpl_Sqrt_One_By_Two_Pi;
extern const long double tmpl_Sqrt_One_By_Two_Pi_L;

/*  sqrt( pi / 8 )                                                            */
extern const float tmpl_Sqrt_Pi_By_Eight_F;
extern const double tmpl_Sqrt_Pi_By_Eight;
extern const long double tmpl_Sqrt_Pi_By_Eight_L;

/*  sqrt( pi / 2 )                                                            */
extern const float tmpl_Sqrt_Pi_By_Two_F;
extern const double tmpl_Sqrt_Pi_By_Two;
extern const long double tmpl_Sqrt_Pi_By_Two_L;

/*  sqrt( 1 / pi )                                                            */
extern const float tmpl_Sqrt_One_By_Pi_F;
extern const double tmpl_Sqrt_One_By_Pi;
extern const long double tmpl_Sqrt_One_By_Pi_L;

/*  sqrt( 2 / pi )                                                            */
extern const float tmpl_Sqrt_Two_By_Pi_F;
extern const double tmpl_Sqrt_Two_By_Pi;
extern const long double tmpl_Sqrt_Two_By_Pi_L;

/*  1 / pi.                                                                   */
extern const float tmpl_One_By_Pi_F;
extern const double tmpl_One_By_Pi;
extern const long double tmpl_One_By_Pi_L;

/*  2 / sqrt( pi )                                                            */
extern const float tmpl_Two_By_Sqrt_Pi_F;
extern const double tmpl_Two_By_Sqrt_Pi;
extern const long double tmpl_Two_By_Sqrt_Pi_L;

/*  pi / 2                                                                    */
extern const float tmpl_Pi_By_Two_F;
extern const double tmpl_Pi_By_Two;
extern const long double tmpl_Pi_By_Two_L;

/*  3 pi / 4                                                                  */
extern const float tmpl_Three_Pi_By_Four_F;
extern const double tmpl_Three_Pi_By_Four;
extern const long double tmpl_Three_Pi_By_Four_L;

/*  pi / 4                                                                    */
extern const float tmpl_Pi_By_Four_F;
extern const double tmpl_Pi_By_Four;
extern const long double tmpl_Pi_By_Four_L;

/*  pi                                                                        */
extern const float tmpl_One_Pi_F;
extern const double tmpl_One_Pi;
extern const long double tmpl_One_Pi_L;

/*  2 pi                                                                      */
extern const float tmpl_Two_Pi_F;
extern const double tmpl_Two_Pi;
extern const long double tmpl_Two_Pi_L;

/*  sqrt( 2 )                                                                 */
extern const float tmpl_Sqrt_Two_F;
extern const double tmpl_Sqrt_Two;
extern const long double tmpl_Sqrt_Two_L;

/*  e = exp( 1 )                                                              */
extern const float tmpl_Euler_E_F;
extern const double tmpl_Euler_E;
extern const long double tmpl_Euler_E_L;

/*  1 / e = exp( -1 )                                                         */
extern const float tmpl_Rcpr_Euler_E_F;
extern const double tmpl_Rcpr_Euler_E;
extern const long double tmpl_Rcpr_Euler_E_L;

/*  log_e( 2 ) = ln( 2 )                                                      */
extern const float tmpl_Natural_Log_of_Two_F;
extern const double tmpl_Natural_Log_of_Two;
extern const long double tmpl_Natural_Log_of_Two_L;

/*  log_e( 10 ) = ln( 10 )                                                    */
extern const float tmpl_Natural_Log_of_Ten_F;
extern const double tmpl_Natural_Log_of_Ten;
extern const long double tmpl_Natural_Log_of_Ten_L;

/*  pi / 180                                                                  */
extern const float tmpl_Deg_to_Rad_F;
extern const double tmpl_Deg_to_Rad;
extern const long double tmpl_Deg_to_Rad_L;

/*  180 / pi                                                                  */
extern const float tmpl_Rad_to_Deg_F;
extern const double tmpl_Rad_to_Deg;
extern const long double tmpl_Rad_to_Deg_L;

/*  Largest value such that exp(x) will not return infinity.                  */
extern const float tmpl_Max_Float_Base_E;
extern const double tmpl_Max_Double_Base_E;
extern const long double tmpl_Max_LDouble_Base_E;

/*  Smallest value such that exp(x) will not return zero.                     */
extern const float tmpl_Min_Float_Base_E;
extern const double tmpl_Min_Double_Base_E;
extern const long double tmpl_Min_LDouble_Base_E;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Compute the absolute value of a real number (fabs alias).             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double abs_x:                                                         *
 *          The absolute value of x, |x|.                                     *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_abs_float.c                                     *
 *      libtmpl/src/math/tmpl_abs_double.c                                    *
 *      libtmpl/src/math/tmpl_abs_ldouble.c                                   *
 *      libtmpl/include/math/tmpl_math_abs_inline.h (inline version)          *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_abs_float_example.c               *
 *      libtmpl/examples/math_examples/tmpl_abs_double_example.c              *
 *      libtmpl/examples/math_examples/tmpl_abs_ldouble_example.c             *
 *  Tests:                                                                    *
 *      libtmpl/tests/math_tests/unit_tests/                                  *
 *          tmpl_abs_float_unit_test_001.c                                    *
 *          tmpl_abs_double_unit_test_001.c                                   *
 *          tmpl_abs_ldouble_unit_test_001.c                                  *
 *      libtmpl/tests/math_tests/time_tests/                                  *
 *          tmpl_abs_float_time_test.c                                        *
 *          tmpl_abs_double_time_test.c                                       *
 *          tmpl_abs_ldouble_time_test.c                                      *
 *      libtmpl/tests/math_tests/accuracy_tests/                              *
 *          tmpl_abs_float_accuracy_test.c                                    *
 *          tmpl_abs_double_accuracy_test.c                                   *
 *          tmpl_abs_ldouble_accuracy_test.c                                  *
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
#include <libtmpl/include/math/tmpl_math_abs_float_inline.h>
#include <libtmpl/include/math/tmpl_math_abs_double_inline.h>
#include <libtmpl/include/math/tmpl_math_abs_ldouble_inline.h>

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
 *  NOTES:                                                                    *
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
#if TMPL_USE_MATH_ALGORITHMS != 1
#define tmpl_Float_Arctan2 atan2f
#define tmpl_Double_Arctan2 atan2
#define tmpl_LDouble_Arctan2 atan2l
#else
extern float tmpl_Float_Arctan2(float y, float x);
extern double tmpl_Double_Arctan2(double y, double x);
extern long double tmpl_LDouble_Arctan2(long double y, long double x);
#endif

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
 *      libtmpl/src/math/tmpl_arctan_float.c                                  *
 *      libtmpl/src/math/tmpl_arctan_double.c                                 *
 *      libtmpl/src/math/tmpl_arctan_ldouble.c                                *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_arctan_float_example.c            *
 *      libtmpl/examples/math_examples/tmpl_arctan_double_example.c           *
 *      libtmpl/examples/math_examples/tmpl_arctan_ldouble_example.c          *
 *  Tests:                                                                    *
 *      libtmpl/tests/math_tests/time_tests/                                  *
 *          tmpl_arctan_float_time_test.c                                     *
 *          tmpl_arctan_double_time_test.c                                    *
 *          tmpl_arctan_ldouble_time_test.c                                   *
 *      libtmpl/tests/math_tests/accuracy_tests/                              *
 *          tmpl_arctan_float_accuracy_test.c                                 *
 *          tmpl_arctan_double_accuracy_test.c                                *
 *          tmpl_arctan_ldouble_accuracy_test.c                               *
 ******************************************************************************/

/*  Alias functions to atan from math.h if libtmpl algorithms not requested.  */
#if TMPL_USE_MATH_ALGORITHMS != 1
#define tmpl_Float_Arctan atanf
#define tmpl_Double_Arctan atan
#define tmpl_LDouble_Arctan atanl
#else
extern float tmpl_Float_Arctan(float x);
extern double tmpl_Double_Arctan(double x);
extern long double tmpl_LDouble_Arctan(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan_Asymptotic                                         *
 *  Purpose:                                                                  *
 *      Compute the asymptotic expansion of arctan for large positive values. *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well. Only accurate *
 *      for large positive values. Use tmpl_Double_Arctan if you are unsure.  *
 ******************************************************************************/

/*  This function is small enough that it is definitely worth inlining.       */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_arctan_asymptotic_double_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_asymptotic_float_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_asymptotic_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Otherwise use the external ones in src/math.                              */
extern float tmpl_Float_Arctan_Asymptotic(float x);
extern double tmpl_Double_Arctan_Asymptotic(double x);
extern long double tmpl_LDouble_Arctan_Asymptotic(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan_Maclaurin                                          *
 *  Purpose:                                                                  *
 *      Compute the Maclaurin series for arctan for small real numbers.       *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well. Only accurate *
 *      for small values. Use tmpl_Double_Arctan if you are unsure.           *
 *      The absolute error goes like x^19 / 19. For |x| < 0.1 this is bounded *
 *      by 10^-17. For |x| < 0.5 this is bounded by 10^-7. For |x| < 1 this   *
 *      bounded by 3 x 10^-2. Do not use for larger values.                   *
 ******************************************************************************/

/*  This function is small enough that it is definitely worth inlining.       */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_arctan_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

extern float tmpl_Float_Arctan_Maclaurin(float x);
extern double tmpl_Double_Arctan_Maclaurin(double x);
extern long double tmpl_LDouble_Arctan_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan_Pade                                               *
 *  Purpose:                                                                  *
 *      Compute the Pade approximation of order (11, 11) for arctan.          *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well.               *
 *      Very good for |x| < 1 (relative error bounded by 10^-9). For |x| < 6  *
 *      the relative error is bounded by 3 x 10^-2. This approximation is     *
 *      significantly faster than atan (math.h) and tmpl_Double_Arctan.       *
 ******************************************************************************/

/*  This function is small enough to inline.                                  */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_arctan_pade_double_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_pade_float_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_pade_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

extern float tmpl_Float_Arctan_Pade(float x);
extern double tmpl_Double_Arctan_Pade(double x);
extern long double tmpl_LDouble_Arctan_Pade(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Arctan_Very_Small                                         *
 *  Purpose:                                                                  *
 *      Compute the Maclaurin series of arctan for very small |x|. Used for   *
 *      avoiding underflow when computing atan(x).                            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double atan_x:                                                        *
 *          The inverse tangent of x, tan^-1(x).                              *
 *  Notes:                                                                    *
 *      Float and long double equivalents are provided as well. Only good for *
 *      small values. tmpl_Double_Arctan uses this function for |x| < 1/8. It *
 *      is accurate to 2 x 10^-16 relative error in this range.               *
 ******************************************************************************/

/*  This function should be inlined if possible.                              */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_arctan_very_small_double_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_very_small_float_inline.h>
#include <libtmpl/include/math/tmpl_math_arctan_very_small_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

extern float tmpl_Float_Arctan_Very_Small(float x);
extern double tmpl_Double_Arctan_Very_Small(double x);
extern long double tmpl_LDouble_Arctan_Very_Small(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
 *      tmpl_Double_Cbrt_Pade                                                 *
 *  Purpose:                                                                  *
 *      Compute the (7, 7) Pade approximant of cbrt(x) at x = 1.              *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cbrt_x:                                                        *
 *          The cube root of x, x^{1/3}.                                      *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_cbrt_pade_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cbrt_pade_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cbrt_pade_ldouble_inline.h>
#else
extern float tmpl_Float_Cbrt_Pade(float x);
extern double tmpl_Double_Cbrt_Pade(double x);
extern long double tmpl_LDouble_Cbrt_Pade(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cbrt_Taylor                                               *
 *  Purpose:                                                                  *
 *      Compute the Taylor series of cbrt(x) at x = 1.                        *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cbrt_x:                                                        *
 *          The cube root of x, x^{1/3}.                                      *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_cbrt_taylor_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cbrt_taylor_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cbrt_taylor_ldouble_inline.h>
#else
extern float tmpl_Float_Cbrt_Taylor(float x);
extern double tmpl_Double_Cbrt_Taylor(double x);
extern long double tmpl_LDouble_Cbrt_Taylor(long double x);
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
#include <libtmpl/include/math/tmpl_math_copysign_double_inline.h>
#include <libtmpl/include/math/tmpl_math_copysign_float_inline.h>
#include <libtmpl/include/math/tmpl_math_copysign_ldouble_inline.h>

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
 *      tmpl_Double_Cosd_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of cosine in degrees.                   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cosd_x:                                                        *
 *          The cosine of x in degrees.                                       *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_cosd_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cosd_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cosd_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support, use external functions in src/math.                    */
extern float tmpl_Float_Cosd_Maclaurin(float x);
extern double tmpl_Double_Cosd_Maclaurin(double x);
extern long double tmpl_LDouble_Cosd_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
 *      tmpl_Double_CosPi_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of the normalized cosine, cos(pi x).    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_pix:                                                       *
 *          The normalized cosine of x, cos(pi x).                            *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_cospi_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cospi_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cospi_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support, use external functions in src/math.                    */
extern float tmpl_Float_CosPi_Maclaurin(float x);
extern double tmpl_Double_CosPi_Maclaurin(double x);
extern long double tmpl_LDouble_CosPi_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
 *      tmpl_Double_Cosh_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Compute hyperbolic cosine of a small value with a Maclaurin series.   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The hyperbolic cosine of x, cosh(x).                              *
 ******************************************************************************/

/*  This function is small enough that it should be inlined.                  */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_cosh_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cosh_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cosh_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Inline support not requested, use functions in src/math.                  */
extern float tmpl_Float_Cosh_Maclaurin(float x);
extern double tmpl_Double_Cosh_Maclaurin(double x);
extern long double tmpl_LDouble_Cosh_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Cosh_Pade                                                 *
 *  Purpose:                                                                  *
 *      Compute hyperbolic cosine of a small value with a Pade approximant.   *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double cos_x:                                                         *
 *          The hyperbolic cosine of x, cosh(x).                              *
 ******************************************************************************/

/*  These functions should be inlined.                                        */
#if TMPL_USE_INLINE == 1

/*  inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_cosh_pade_float_inline.h>
#include <libtmpl/include/math/tmpl_math_cosh_pade_double_inline.h>
#include <libtmpl/include/math/tmpl_math_cosh_pade_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Inline support not requested, use functions in src/math.                  */
extern float tmpl_Float_Cosh_Pade(float x);
extern double tmpl_Double_Cosh_Pade(double x);
extern long double tmpl_LDouble_Cosh_Pade(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
#include <libtmpl/include/math/tmpl_math_dist_double_inline.h>
#include <libtmpl/include/math/tmpl_math_dist_float_inline.h>
#include <libtmpl/include/math/tmpl_math_dist_ldouble_inline.h>

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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Maclaurin                                             *
 *  Purpose:                                                                  *
 *      Computes the base e exponential of a small real number.               *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double exp_x:                                                         *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/

/*  Small functions, worth inlining.                                          */
#if TMPL_USE_INLINE == 1

/*  Inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_exp_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_exp_maclaurin_float_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support requested, use functions in src/math.                   */
extern float tmpl_Float_Exp_Maclaurin(float x);
extern double tmpl_Double_Exp_Maclaurin(double x);
extern long double tmpl_LDouble_Exp_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Exp_Pade                                                  *
 *  Purpose:                                                                  *
 *      Computes the base e exponential of a small real number.               *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double exp_x:                                                         *
 *          The exponential function of x, exp(x).                            *
 ******************************************************************************/

/*  Small functions, worth inlining.                                          */
#if TMPL_USE_INLINE == 1

/*  Inline versions found here.                                               */
#include <libtmpl/include/math/tmpl_math_exp_pade_double_inline.h>
#include <libtmpl/include/math/tmpl_math_exp_pade_float_inline.h>
#include <libtmpl/include/math/tmpl_math_exp_pade_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support requested, use functions in src/math.                   */
extern float tmpl_Float_Exp_Pade(float x);
extern double tmpl_Double_Exp_Pade(double x);
extern long double tmpl_LDouble_Exp_Pade(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
#include <libtmpl/include/math/tmpl_math_exp_pos_kernel_double_inline.h>
#include <libtmpl/include/math/tmpl_math_exp_pos_kernel_float_inline.h>

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

extern unsigned long
tmpl_Falling_Factorial(unsigned int x, unsigned int N);

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
 *      tmpl_Float_Is_Inf                                                     *
 *  Purpose:                                                                  *
 *      This function tests if a number is positive or negative infinity.     *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_inf (tmpl_Bool):                                                   *
 *          A Boolean indicating if x is +/- infinity or not.                 *
 *  NOTE:                                                                     *
 *      Double and long double equivalents are also provided.                 *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_is_inf.c                                        *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_is_inf_float_example.c            *
 *      libtmpl/examples/math_examples/tmpl_is_inf_double_example.c           *
 *      libtmpl/examples/math_examples/tmpl_is_inf_ldouble_example.c          *
 ******************************************************************************/
extern tmpl_Bool tmpl_Float_Is_Inf(float x);
extern tmpl_Bool tmpl_Double_Is_Inf(double x);
extern tmpl_Bool tmpl_LDouble_Is_Inf(long double x);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Float_Is_NaN                                                     *
 *  Purpose:                                                                  *
 *      This function tests if a number is Not-a-Number.                      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      is_nan (tmpl_Bool):                                                   *
 *          A Boolean indicating if x is +/- nan or not.                      *
 *  NOTE:                                                                     *
 *      Double and long double equivalents are also provided.                 *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_is_nan.c                                        *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_is_nan_float_example.c            *
 *      libtmpl/examples/math_examples/tmpl_is_nan_double_example.c           *
 *      libtmpl/examples/math_examples/tmpl_is_nan_ldouble_example.c          *
 ******************************************************************************/
extern tmpl_Bool tmpl_Float_Is_NaN(float x);
extern tmpl_Bool tmpl_Double_Is_NaN(double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN(long double x);

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
extern tmpl_Bool tmpl_Float_Is_NaN_Or_Inf(float x);
extern tmpl_Bool tmpl_Double_Is_NaN_Or_Inf(double x);
extern tmpl_Bool tmpl_LDouble_Is_NaN_Or_Inf(long double x);

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
 *      tmpl_Float_NaN                                                        *
 *  Purpose:                                                                  *
 *      Returns Not-A-Number.                                                 *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      nan (float):                                                          *
 *          Not-a-Number.                                                     *
 *  NOTE:                                                                     *
 *      Double and long double equivalents are also provided.                 *
 *      If IEEE-754 support is available, this code creates NaN using         *
 *      the format. If not, the function mimics glibc's method, returning     *
 *      the number 0.0 / 0.0 which should be NaN.                             *
 *  Source Code:                                                              *
 *      libtmpl/src/math/tmpl_nan.c                                           *
 *  Examples:                                                                 *
 *      libtmpl/examples/math_examples/tmpl_nan_example.c                     *
 ******************************************************************************/
extern float tmpl_Float_NaN(void);
extern double tmpl_Double_NaN(void);
extern long double tmpl_LDouble_NaN(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Reverse_Double_Array                                             *
 *  Purpose:                                                                  *
 *      Reverses the order of a pointer to an array of real numbers.          *
 *  Arguments:                                                                *
 *      double *arr:                                                          *
 *          A pointer to an array.                                            *
 *      unsigned long int arrsize:                                            *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      double sinc_x:                                                        *
 *          The sinc of x.                                                    *
 ******************************************************************************/
extern void tmpl_Reverse_Float_Array(float *arr, unsigned long arrsize);
extern void tmpl_Reverse_Double_Array(double *arr, unsigned long arrsize);
extern void tmpl_Reverse_LDouble_Array(long double *arr, unsigned long arrsize);

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
 *      tmpl_Double_Sin_Very_Small                                            *
 *  Purpose:                                                                  *
 *      Computes the sine function sin(x) using the Maclaurin series for      *
 *      very small inputs.                                                    *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_x:                                                         *
 *          The sine of x.                                                    *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_sin_very_small_inline.h>
#else
extern double tmpl_Double_Sin_Very_Small(double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sin_Pade                                                  *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of the sine function sin(x).            *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_x:                                                         *
 *          The sine of x.                                                    *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_sin_pade_inline.h>
#else
extern float tmpl_Float_Sin_Pade(float x);
extern double tmpl_Double_Sin_Pade(double x);
extern long double tmpl_LDouble_Sin_Pade(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Sin_Pade_Pi                                               *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of the sine centered at pi.             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_x:                                                         *
 *          The sine of x.                                                    *
 ******************************************************************************/
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_sin_pade_pi_inline.h>
#else
extern float tmpl_Float_Sin_Pade_Pi(float x);
extern double tmpl_Double_Sin_Pade_Pi(double x);
extern long double tmpl_LDouble_Sin_Pade_Pi(long double x);
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_SinCos                                                    *
 *  Purpose:                                                                  *
 *      Computes the point on a circle corresponding to a given angle.        *
 *  Arguments:                                                                *
 *      double t:                                                             *
 *          A real number.                                                    *
 *      double *x_ptr;                                                        *
 *          A pointer to the x-coordinate of the point on the circle.         *
 *      double *y_ptr;                                                        *
 *          A pointer to the y-coordinate of the point on the circle.         *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Float_SinCos(float t, float *sin_t, float *cos_t);
extern void tmpl_Double_SinCos(double t, double *sin_t, double *cos_t);

extern void
tmpl_LDouble_SinCos(long double t, long double *sin_t, long double *cos_t);

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
 *      tmpl_Double_Sind_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of sine in degrees.                     *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sind_x:                                                        *
 *          The sine of x in degrees.                                         *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_sind_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_sind_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_sind_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support, use external functions in src/math.                    */
extern float tmpl_Float_Sind_Maclaurin(float x);
extern double tmpl_Double_Sind_Maclaurin(double x);
extern long double tmpl_LDouble_Sind_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
 *      tmpl_Double_SinPi_Maclaurin                                           *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of the normalized sine, sin(pi x).      *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double sin_pix:                                                       *
 *          The normalized sine of x, sin(pi x).                              *
 ******************************************************************************/

/*  These functions are small enough to inline.                               */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/math/tmpl_math_sinpi_maclaurin_double_inline.h>
#include <libtmpl/include/math/tmpl_math_sinpi_maclaurin_float_inline.h>
#include <libtmpl/include/math/tmpl_math_sinpi_maclaurin_ldouble_inline.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  No inline support, use external functions in src/math.                    */
extern float tmpl_Float_SinPi_Maclaurin(float x);
extern double tmpl_Double_SinPi_Maclaurin(double x);
extern long double tmpl_LDouble_SinPi_Maclaurin(long double x);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

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
extern float tmpl_Float_Poly_Eval(float *coeffs, size_t degree, float x);
extern double tmpl_Double_Poly_Eval(double *coeffs, size_t degree, double x);
extern long double
tmpl_LDouble_Poly_Eval(long double *coeffs, size_t degree, long double x);

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
tmpl_Float_Poly_Deriv_Eval(float *coeffs, unsigned int degree,
                           unsigned int deriv, float x);

extern double
tmpl_Double_Poly_Deriv_Eval(double *coeffs, unsigned int degree,
                            unsigned int deriv, double x);

extern long double
tmpl_LDouble_Poly_Deriv_Eval(long double *coeffs, unsigned int degree,
                             unsigned int deriv, long double x);

/*  Macro for positive infinity                                               */
#define TMPL_INFINITYF (tmpl_Float_Infinity())
#define TMPL_INFINITY (tmpl_Double_Infinity())
#define TMPL_INFINITYL (tmpl_LDouble_Infinity())

/*  Macro for Not-A-Number.                                                   */
#define TMPL_NANF (tmpl_Float_NaN())
#define TMPL_NAN (tmpl_Double_NaN())
#define TMPL_NANL (tmpl_LDouble_NaN())

/******************************************************************************
 *                              Tables and Data                               *
 ******************************************************************************/

/*  The values cbrt(1 + k/128) for k = 0, 1, ..., 126, 127.                   */
extern const double tmpl_double_cbrt_table[128];
extern const float tmpl_float_cbrt_table[128];
extern const long double tmpl_ldouble_cbrt_table[128];

/*  The values cos((pi/180)*k) for k = 0, 1, ..., 179.                        */
extern const double tmpl_double_cosd_table[180];
extern const float tmpl_float_cosd_table[180];
extern const long double tmpl_ldouble_cosd_table[180];

/*  The values cos(pi*k/128) for k = 0, 1, ..., 127.                          */
extern const double tmpl_double_cospi_table[128];
extern const float tmpl_float_cospi_table[128];
extern const long double tmpl_ldouble_cospi_table[128];

/*  The values log(1 + k/128) for k = 0, 1, ..., 126, 127.                    */
extern const double tmpl_double_log_table[128];
extern const float tmpl_float_log_table[128];
extern const long double tmpl_ldouble_log_table[128];

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

#endif
/*  End of include guard.                                                     */
