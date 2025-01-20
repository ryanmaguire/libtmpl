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
 *                            tmpl_ieee754_ldouble                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a union for type-punning long doubles.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 12, 2024                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to the types directory.                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_IEEE754_LDOUBLE_H
#define TMPL_TYPES_IEEE754_LDOUBLE_H

/*  TMPL_LDOUBLE_ENDIANNESS and TMPL_LDOUBLE_TYPE provided here.              */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *                        Long Double Macros and Unions                       *
 ******************************************************************************/

/*  Sanity check for long double. Long double is not as standardized as float *
 *  and double and there are several ways to implement it. This includes      *
 *  64-bit, 80-bit, 96-bit, and 128-bit implementations, and with big or      *
 *  little endianness. The macro TMPL_LDOUBLE_ENDIANNESS contains this        *
 *  information.                                                              */
#if !defined(TMPL_LDOUBLE_ENDIANNESS)

/*  If TMPL_LDOUBLE_ENDIANNESS is undefined, there is a problem with libtmpl. *
 *  Abort compiling.                                                          */
#error "tmpl_ieee754_ldouble.h: TMPL_LDOUBLE_ENDIANNESS is undefined."

#endif
/*  End of sanity check, #if !defined(TMPL_LDOUBLE_ENDIANNESS).               */

/*  The TMPL_LDOUBLE_TYPE groups the types from TMPL_LDOUBLE_ENDIANNESS, but  *
 *  does not distinguish endianness. For example 128-bit quadruple big-endian *
 *  and 128-bit quadruple little-endian will both be given by                 *
 *  TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT, where TMPL_LDOUBLE_ENDIANNESS  *
 *  will have different values for these two types. This macro should have    *
 *  been created when building libtmpl. Check for this.                       */
#if !defined(TMPL_LDOUBLE_TYPE)

/*  If TMPL_LDOUBLE_TYPE is undefined, there is a problem with libtmpl. Abort.*/
#error "tmpl_ieee754_ldouble.h: TMPL_LDOUBLE_TYPE is undefined."

#endif
/*  End of sanity check, #if !defined(TMPL_LDOUBLE_TYPE).                     */

/*  If TMPL_LDOUBLE_ENDIANNESS is not set to double, extended, quadruple, or  *
 *  double-double, we do not have IEEE-754 support and can not use it.        */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_UNKNOWN

/*  No support for IEEE-754 long double. Set this to zero.                    */
#define TMPL_HAS_IEEE754_LDOUBLE 0

/*  Otherwise we have IEEE-754 support and can define macros for using it.    *
 *  The macros are very sensitive to how long double is represented and we    *
 *  need to examine the TMPL_LDOUBLE_ENDIANNESS macro carefully.              */
#else

/*  Define this macro to 1, indicating IEEE-754 support.                      */
#define TMPL_HAS_IEEE754_LDOUBLE 1

/*  64-bit double and 128-bit double-double have the same macros.             */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT || \
    TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                64-bit Double / 128-bit Double-Double Macros                *
 ******************************************************************************/

/*  64-bit double precision has exponent bias of 1,023.                       */
#define TMPL_LDOUBLE_BIAS (0x3FF)
#define TMPL_LDOUBLE_UBIAS (0x3FFU)

/*  The exponent that corresponds to NaN/infinity for 64-bit double.          */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FF)

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (52)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (52U)

/*  The value 2**52, used to normalize subnormal / denormal values.           */
#define TMPL_LDOUBLE_NORMALIZE (4.503599627370496E+15L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

/*  Some of the macros for 80-bit extended are the same as 128-bit quadruple. */
#else

/******************************************************************************
 *                 80-bit Extended / 128-bit Quadruple Macros                 *
 ******************************************************************************/

/*  80-bit extended precision and 128-bit quadruple have a bias of 16,383.    */
#define TMPL_LDOUBLE_BIAS (0x3FFF)
#define TMPL_LDOUBLE_UBIAS (0x3FFFU)

/*  The exponent that corresponds to NaN/infinity for extended / quadruple.   */
#define TMPL_LDOUBLE_NANINF_EXP (0x7FFF)

/*  The following macros are different for quadruple and extended precisions. */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                          128-bit Quadruple Macros                          *
 ******************************************************************************/

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (112)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (112U)

/*  The value 2**112, used to normalize subnormal / denormal values.          */
#define TMPL_LDOUBLE_NORMALIZE (5.192296858534827628530496329220096E+33L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || \
  (w).bits.man3 || (w).bits.man4 || (w).bits.man5 || (w).bits.man6))

/*  These are the macros for 80-bit extended precision.                       */
#else

/******************************************************************************
 *                           80-bit Extended Macros                           *
 ******************************************************************************/

/*  The number of bits in the mantissa.                                       */
#define TMPL_LDOUBLE_MANTISSA_LENGTH (63)
#define TMPL_LDOUBLE_MANTISSA_ULENGTH (63U)

/*  The value 2**63, used to normalize subnormal / denormal values.           */
#define TMPL_LDOUBLE_NORMALIZE (9.223372036854775808E+18L)

/*  Macro for determining if a word is NaN or Infinity.                       */
#define TMPL_LDOUBLE_IS_NAN_OR_INF(w) ((w).bits.expo == 0x7FFFU)

/*  Macro for determining if a word is NaN. Only use after checking expo.     */
#define TMPL_LDOUBLE_IS_NAN(w) \
(((w).bits.man0 || (w).bits.man1 || (w).bits.man2 || (w).bits.man3))

#endif
/*  End of difference between extended and quadruple precision.               */

#endif
/*  End of quadruple / extended vs. double / double-double.                   */

/*  All types have these macros in common.                                    */

/*  Macro for determining if a word is NaN.                                   */
#define TMPL_LDOUBLE_IS_NOT_A_NUMBER(w) \
(TMPL_LDOUBLE_IS_NAN_OR_INF((w)) && TMPL_LDOUBLE_IS_NAN((w)))

/*  Macro for determining if a word is infinite.                              */
#define TMPL_LDOUBLE_IS_INFINITY(w) \
(TMPL_LDOUBLE_IS_NAN_OR_INF((w)) && !TMPL_LDOUBLE_IS_NAN((w)))

/*  Macro for examining the exponent bits of a long double.                   */
#define TMPL_LDOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a long double.                        */
#define TMPL_LDOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

#endif
/*  End of #if !defined(TMPL_LDOUBLE_ENDIANNESS).                             */

/*  Little-endian 64-bit long double. Same idea as 64-bit double.             */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN

/*  Same union for 64-bit double, little-endian.                              */
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

/*  Big-endian 64-bit long double. Uses the same struct as big-endian double. */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  Same union for 64-bit double, big-endian.                                 */
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

/*  Little-endian, 80-bit extended precision with 16 bits of padding.         */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN

/*  80-bit extended precision union with 16 bits of padding, 96 bits total.   */
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

/*  Big-endian, 80-bit extended precision with 16 bits of padding.            */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN

/*  80-bit extended precision struct with 16 bits of padding, 96 bits total.  */
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

/*  Little-endian, 80-bit extended precision with 48 bits of padding.         */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN

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

/*  Big-endian, 80-bit extended precision with 48 bits of padding.            */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/*  80-bit extended precision union with 48 bits of padding, 128 bits total.  */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        unsigned int pad0 : 16;
        unsigned int pad1 : 16;
        unsigned int sign : 1;
        unsigned int expo : 15;
        unsigned int pad2 : 16;
        unsigned int intr : 1;
        unsigned int man0 : 15;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;
    } bits;

    /*  Long double the above struct represents.                              */
    long double r;
} tmpl_IEEE754_LDouble;

/*  Little-endian, 128-bit quadruple precision long double.                   */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN

/*  128-bit quadruple precision, 15 bit exponent, 112 bit mantissa.           */
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

/*  Big-endian, 128-bit quadruple precision long double.                      */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  128-bit quadruple precision, 15 bit exponent, 112 bit mantissa.           */
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

/*  128-bit double-double, little-endian. Made from two doubles.              */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Double-double representation. Two doubles stacked together.               */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        /*  The most significant double.                                      */
        unsigned int man3 : 16;
        unsigned int man2 : 16;
        unsigned int man1 : 16;
        unsigned int man0 : 4;
        unsigned int expo : 11;
        unsigned int sign : 1;

        /*  The least significant double.                                     */
        unsigned int man3l : 16;
        unsigned int man2l : 16;
        unsigned int man1l : 16;
        unsigned int man0l : 4;
        unsigned int expol : 11;
        unsigned int signl : 1;
    } bits;

    /*  The two doubles making up r. r = d[0] + d[1].                         */
    double d[2];

    /*  The long double the bits represent.                                   */
    long double r;
} tmpl_IEEE754_LDouble;

/*  128-bit double-double, big-endian. Made from two doubles.                 */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN

/*  Big endian version of double-double. Same as little with order flipped.   */
typedef union tmpl_IEEE754_LDouble_Def {
    struct {
        /*  The most significant double.                                      */
        unsigned int sign : 1;
        unsigned int expo : 11;
        unsigned int man0 : 4;
        unsigned int man1 : 16;
        unsigned int man2 : 16;
        unsigned int man3 : 16;

        /*  The least significant double.                                     */
        unsigned int signl : 1;
        unsigned int expol : 11;
        unsigned int man0l : 4;
        unsigned int man1l : 16;
        unsigned int man2l : 16;
        unsigned int man3l : 16;
    } bits;

    /*  The two doubles making up r. r = d[0] + d[1].                         */
    double d[2];

    /*  The long double the bits represent.                                   */
    long double r;
} tmpl_IEEE754_LDouble;

#endif
/*  End of #if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN.  */

#endif
/*  End of include guard.                                                     */
