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
 *                             tmpl_ieee754_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a union for type-punning floats according to IEEE-754.       *
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
#ifndef TMPL_TYPES_IEEE754_FLOAT_H
#define TMPL_TYPES_IEEE754_FLOAT_H

/*  TMPL_FLOAT_ENDIANNESS macro is provided here.                             */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *                          Float Macros and Unions                           *
 ******************************************************************************/

/*  Check if TMPL_FLOAT_ENDIANNESS was defined in tmpl_config.h. It           *
 *  should be unless there was a problem when building libtmpl.               */
#if !defined(TMPL_FLOAT_ENDIANNESS)

/*  If not, there is a problem with libtmpl. Abort compiling.                 */
#error "tmpl_ieee754_float.h: TMPL_FLOAT_ENDIANNESS is undefined."

/*  If TMPL_FLOAT_ENDIANNESS is neither big nor little endian it is likely    *
 *  unknown. We will not use IEEE-754 features in this case.                  */
#elif TMPL_FLOAT_ENDIANNESS == TMPL_UNKNOWN_ENDIAN

/*  No IEEE-754 support. Set TMPL_HAS_IEEE754_FLOAT to zero.                  */
#define TMPL_HAS_IEEE754_FLOAT 0

/*  Otherwise we have IEEE-754 support and can define macros for using it.    */
#else

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

/*  Macro for determining if a word is NaN.                                   */
#define TMPL_FLOAT_IS_NOT_A_NUMBER(w) \
(TMPL_FLOAT_IS_NAN_OR_INF((w)) && TMPL_FLOAT_IS_NAN((w)))

/*  Macro for determining if a word is infinite.                              */
#define TMPL_FLOAT_IS_INFINITY(w) \
(TMPL_FLOAT_IS_NAN_OR_INF((w)) && !TMPL_FLOAT_IS_NAN((w)))

/*  Macro for examining the exponent bits of a float.                         */
#define TMPL_FLOAT_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a float.                              */
#define TMPL_FLOAT_IS_NEGATIVE(w) ((w).bits.sign)

#endif
/*  End of #if !defined(TMPL_FLOAT_ENDIANNESS).                               */

/*  Big-endian 32-bit float.                                                  */
#if TMPL_FLOAT_ENDIANNESS == TMPL_BIG_ENDIAN

/*  To access the binary representation of a floating point number, we use    *
 *  unions. Unions allow us to have different data types share the same block *
 *  of memory. If we have a union of a floating point and an integer and then *
 *  set the floating point part to some number, then when we access the       *
 *  integer part it will already have its bits set (they'll be set by the     *
 *  floating point value). This is known as "type-punning." Note, the C       *
 *  standard says type-punning is undefined behavior. Indeed, it says you can *
 *  only access the member of a union that was most recently written to. In   *
 *  practice, most compilers support type punning and this practice is very   *
 *  common in implementations of libm, the C mathematical library.            */
typedef union tmpl_IEEE754_Float_Def {

    /*  Use a bit-field for the binary representation of a float. A bit-field *
     *  allows us to define variables with an exact number of bits (up to 16).*
     *  We'll use this to have a 1-bit variable for the sign, 8-bit variable  *
     *  for the exponent, and 2 variables adding up to 23 bits for the        *
     *  mantissa.                                                             */
    struct {

        /*  The notation x : n; means x will be a variable in the struct with *
         *  exactly n bits reserved. So unsigned int sign : 1; means the      *
         *  variable "sign" will have exactly 1 bit reserved for it. sign = 0 *
         *  indicates a positive number, sign = 1 means negative.             *
         *                                                                    *
         *  Note, it is crucial that we avoid padding in the struct. If the   *
         *  compiler pads additional bits, type punning will not work. To     *
         *  avoid this, the order of the bits is crucial. By making man0 into *
         *  a 7-bit object, the combination sign-expo-man0 creates a 16-bit   *
         *  block. Using this ordering avoids padding on all compilers tested.*/
        unsigned int sign : 1;
        unsigned int expo : 8;
        unsigned int man0 : 7;
        unsigned int man1 : 16;
    } bits;

    /*  The above struct holds 32-bits, which the IEEE-754 format specifies   *
     *  as the size of a single-precision float. This is "float" in C.        */
    float r;
} tmpl_IEEE754_Float;

/*  Little-endian 32-bit float.                                               */
#elif TMPL_FLOAT_ENDIANNESS == TMPL_LITTLE_ENDIAN

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

#endif
/*  End of #if TMPL_FLOAT_ENDIANNESS == TMPL_BIG_ENDIAN.                      */

#endif
/*  End of include guard.                                                     */
