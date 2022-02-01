/******************************************************************************
 *                                 LICENSE                                    *
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
 *                                tmpl_math                                   *
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
 *      NOTE:                                                                 *
 *          There is no real portable way to implement infinity in strictly   *
 *          compliant ISO C. Compilers implementing the IEEE-754 format have  *
 *          a way of supporting infinity, but compilers that don't may not.   *
 *          They way glibc implements infinity for compiler lacking IEEE-754  *
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
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_endianness.h:                                                    *
 *          Header file containing the endianness of your system. This file   *
 *          is built with det_end.c in libtmpl/. The Makefile automatically   *
 *          runs this, as does the make.sh script.                            *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
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
 ******************************************************************************/

/*  Include guard for this file to prevent including it twice.                */
#ifndef TMPL_MATH_H
#define TMPL_MATH_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Endianness macros are here.                                               */
#include <libtmpl/include/tmpl_endianness.h>

/*  Set this to 1 to use libtmpl's version of libm. Set this to zero to have  *
 *  math.h included, using standard library functions instead. libtmpl's      *
 *  libm functions are quite fast and efficient, but most would prefer to use *
 *  the libm provided by the implementation of the C standard library they    *
 *  are using, so this is set to 0 by default.                                */
#define TMPL_USE_MATH_ALGORITHMS 1

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
 *  positive, or zero, we require more information. The solution is to        *
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
 *  determined by the "endianness" or your system. To store a real number, or *
 *  to at least approximate, one might guess that we simply insert a point    *
 *  half-way and treat this as a decimal:                                     *
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
 *  represents zero and not +/- 2^-1023.                                      *
 *                                                                            *
 *  Now for some examples:                                                    *
 *    0 00000000001 0000000000000000000000000000000000000000000000000000      *
 *      = 2^(1-1023)                                                          *
 *      = 2^-1022                                                             *
 *      ~ 10^-308                                                             *
 *                                                                            *
 *  This is the smallest positive number.                                     *
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

/*  Check if TMPL_FLOAT_ENDIANNESS was defined in tmpl_endianness.h. It       *
 *  should be unless there was a problem when building libtmpl.               */
#if !defined(TMPL_FLOAT_ENDIANNESS)

/*  If not, there is a problem with libtmpl. Abort compiling.                 */
#error "tmpl_math.h: TMPL_FLOAT_ENDIANNESS is undefined."

#elif TMPL_FLOAT_ENDIANNESS == TMPL_BIG_ENDIAN
/*  Else statement for #if !defined(TMPL_FLOAT_ENDIANNESS).                   */

/*  Macro indicating support for IEEE-754 single precision.                   */
#define TMPL_HAS_IEEE754_FLOAT 1

/*  32-bit single precision bias is 127.                                      */
#define TMPL_FLOAT_BIAS 0x7F

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
#define TMPL_FLOAT_BIAS 0x7F

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
#define TMPL_DOUBLE_BIAS 0x3FF

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
#define TMPL_DOUBLE_BIAS 0x3FF

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
#define TMPL_LDOUBLE_BIAS 0x3FF

/*  MIPS little endian uses the same structure as double, 64 bit. The         *
 *  Windows compiler MSVC also uses this for x86_64.                          */
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
#define TMPL_LDOUBLE_BIAS 0x3FF

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
#define TMPL_LDOUBLE_BIAS 0x3FFF

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

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  80-bit extended precision has exponent bias of 16,383.                    */
#define TMPL_LDOUBLE_BIAS 0x3FFF

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

#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  128-bit quadruple precision has exponent bias of 16,383.                  */
#define TMPL_LDOUBLE_BIAS 0x3FFF

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
#define TMPL_LDOUBLE_BIAS 0x3FFF

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

#else
/*  Else for #if !defined(TMPL_LDOUBLE_ENDIANNESS).                           */

/*  No support for IEEE-754 long double. Set this to zero.                    */
#define TMPL_HAS_IEEE754_LDOUBLE 0

#endif
/*  End of #if !defined(TMPL_LDOUBLE_ENDIANNESS).                             */

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
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Compute the absolute value of a real number (fabs alias).             *
 *  Arguments:                                                                *
 *      double x:                                                             *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      double abs_x:                                                         *
 *          The absolute value of x, |x|.                                     *
 ******************************************************************************/
extern float tmpl_Float_Abs(float x);
extern double tmpl_Double_Abs(double x);
extern long double tmpl_LDouble_Abs(long double x);

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
 ******************************************************************************/
extern float tmpl_Float_Arctan(float x);
extern double tmpl_Double_Arctan(double x);
extern long double tmpl_LDouble_Arctan(long double x);

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
extern float tmpl_Float_Arctan2(float y, float x);
extern double tmpl_Double_Arctan2(double y, double x);
extern long double tmpl_LDouble_Arctan2(long double y, long double x);

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
extern float tmpl_Float_Copysign(float x, float y);
extern double tmpl_Double_Copysign(double x, double y);
extern long double tmpl_LDouble_Copysign(long double x, long double y);

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
extern float tmpl_Float_Cos(float x);
extern double tmpl_Double_Cos(double x);
extern long double tmpl_LDouble_Cos(long double x);

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
extern float tmpl_Float_Cosh(float x);
extern double tmpl_Double_Cosh(double x);
extern long double tmpl_LDouble_Cosh(long double x);

/*  Aliases for the sine trig function found in math.h.                       */
extern float tmpl_Float_Sin(float x);
extern double tmpl_Double_Sin(double x);
extern long double tmpl_LDouble_Sin(long double x);

/*  Aliases for the cosine tan function found in math.h.                      */
extern float tmpl_Float_Tan(float x);
extern double tmpl_Double_Tan(double x);
extern long double tmpl_LDouble_Tan(long double x);

/*  Aliases for the square root function found in math.h.                     */
extern float tmpl_Float_Sqrt(float x);
extern double tmpl_Double_Sqrt(double x);
extern long double tmpl_LDouble_Sqrt(long double x);

/*  Aliases for the exponential function found in math.h.                     */
extern float tmpl_Float_Exp(float x);
extern double tmpl_Double_Exp(double x);
extern long double tmpl_LDouble_Exp(long double x);

/*  Aliases for the exponential function found in math.h.                     */
extern float tmpl_Float_Log(float x);
extern double tmpl_Double_Log(double x);
extern long double tmpl_LDouble_Log(long double x);

extern float tmpl_Float_Floor(float x);
extern double tmpl_Double_Floor(double x);
extern long double tmpl_LDouble_Floor(long double x);

extern float tmpl_Float_Sinc(float x);
extern double tmpl_Double_Sinc(double x);
extern long double tmpl_LDouble_Sinc(long double x);

extern float tmpl_Float_Sinh(float x);
extern double tmpl_Double_Sinh(double x);
extern long double tmpl_LDouble_Sinh(long double x);

extern float tmpl_Float_Tanh(float x);
extern double tmpl_Double_Tanh(double x);
extern long double tmpl_LDouble_Tanh(long double x);

extern float tmpl_Float_Erf(float x);
extern double tmpl_Double_Erf(double x);
extern long double tmpl_LDouble_Erf(long double x);

extern float tmpl_Float_Erfc(float x);
extern double tmpl_Double_Erfc(double x);
extern long double tmpl_LDouble_Erfc(long double x);

extern float tmpl_Float_Erfcx(float x);
extern double tmpl_Double_Erfcx(double x);
extern long double tmpl_LDouble_Erfcx(long double x);

extern float tmpl_Float_Faddeeva_Im(float x);
extern double tmpl_Double_Faddeeva_Im(double x);
extern long double tmpl_LDouble_Faddeeva_Im(long double x);

extern unsigned long tmpl_Factorial(unsigned int n);

extern float tmpl_Factor_As_Float(unsigned int n);
extern double tmpl_Factorial_As_Double(unsigned int n);

extern unsigned long
tmpl_Falling_Factorial(unsigned int x, unsigned int N);

extern float
tmpl_Real_Poly_Float_Coeffs(float *coeffs, unsigned int degree, float x);

extern double
tmpl_Real_Poly_Double_Coeffs(double *coeffs,
                                    unsigned int degree,
                                    double x);

extern long double
tmpl_Real_Poly_LDouble_Coeffs(long double *coeffs,
                                     unsigned int degree,
                                     long double x);

extern float
tmpl_Real_Poly_Deriv_Float_Coeffs(float *coeffs, unsigned int degree,
                                         unsigned int deriv, float x);

extern double
tmpl_Real_Poly_Deriv_Double_Coeffs(double *coeffs, unsigned int degree,
                                          unsigned int deriv, double x);

extern long double
tmpl_Real_Poly_Deriv_LDouble_Coeffs(long double *coeffs,
                                           unsigned int degree,
                                           unsigned int deriv,
                                           long double x);

extern void
tmpl_Reverse_Float_Array(float *arr, unsigned long arrsize);

extern void
tmpl_Reverse_Double_Array(double *arr, unsigned long arrsize);

extern void
tmpl_Reverse_LDouble_Array(long double *arr, unsigned long arrsize);

extern float tmpl_Float_Mod_2(float x);
extern double tmpl_Double_Mod_2(double n);
extern long double tmpl_LDouble_Mod_2(long double x);

extern float tmpl_Float_Dist(float x, float y);
extern double tmpl_Double_Dist(double x, double y);
extern long double tmpl_LDouble_Dist(long double x, long double y);

extern const float tmpl_Float_Cos_Lookup_Table[100];
extern const double tmpl_Double_Cos_Lookup_Table[100];
extern const long double tmpl_LDouble_Cos_Lookup_Table[100];

extern const float tmpl_Float_Sin_Lookup_Table[100];
extern const double tmpl_Double_Sin_Lookup_Table[100];
extern const long double tmpl_LDouble_Sin_Lookup_Table[100];

extern float
tmpl_Max_Float(float *arr, unsigned long n_elements);

extern double
tmpl_Max_Double(double *arr, unsigned long n_elements);

extern long double
tmpl_Max_LDouble(long double *arr, unsigned long n_elements);

extern char
tmpl_Max_Char(char *arr, unsigned long n_elements);

extern unsigned char
tmpl_Max_UChar(unsigned char *arr, unsigned long n_elements);

extern short
tmpl_Max_Short(short *arr, unsigned long n_elements);

extern unsigned short
tmpl_Max_UShort(unsigned short *arr, unsigned long n_elements);

extern int
tmpl_Max_Int(int *arr, unsigned long n_elements);

extern unsigned int
tmpl_Max_UInt(unsigned int *arr, unsigned long n_elements);

extern long
tmpl_Max_Long(long *arr, unsigned long n_elements);

extern unsigned long
tmpl_Max_ULong(unsigned long *arr, unsigned long n_elements);

extern float
tmpl_Min_Float(float *arr, unsigned long n_elements);

extern double
tmpl_Min_Double(double *arr, unsigned long n_elements);

extern long double
tmpl_Min_LDouble(long double *arr, unsigned long n_elements);

extern char
tmpl_Min_Char(char *arr, unsigned long n_elements);

extern unsigned char
tmpl_Min_UChar(unsigned char *arr, unsigned long n_elements);

extern short
tmpl_Min_Short(short *arr, unsigned long n_elements);

extern unsigned short
tmpl_Min_UShort(unsigned short *arr, unsigned long n_elements);

extern int
tmpl_Min_Int(int *arr, unsigned long n_elements);

extern unsigned int
tmpl_Min_UInt(unsigned int *arr, unsigned long n_elements);

extern long
tmpl_Min_Long(long *arr, unsigned long n_elements);

extern unsigned long
tmpl_Min_ULong(unsigned long *arr, unsigned long n_elements);

/*  Macro for positive infinity                                               */
#define TMPL_INFINITYF (tmpl_Float_Infinity())
#define TMPL_INFINITY (tmpl_Double_Infinity())
#define TMPL_INFINITYL (tmpl_LDouble_Infinity())

/*  Macro for Not-A-Number.                                                   */
#define TMPL_NANF (tmpl_Float_NaN())
#define TMPL_NAN (tmpl_Double_NaN())
#define TMPL_NANL (tmpl_LDouble_NaN())

#endif
/*  End of include guard.                                                     */
