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
 *                            tmpl_ieee754_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a union for type-punning doubles according to IEEE-754.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 12, 2024                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IEEE754_DOUBLE_H
#define TMPL_IEEE754_DOUBLE_H

/*  TMPL_DOUBLE_ENDIANNESS macro is provided here.                            */
#include <libtmpl/include/tmpl_config.h>

/******************************************************************************
 *                          Double Macros and Unions                          *
 ******************************************************************************/

/*  Sanity check. This macro should be defined.                               */
#if !defined(TMPL_DOUBLE_ENDIANNESS)

/*  If TMPL_DOUBLE_ENDIANNESS is undefined, there is a problem with libtmpl.  *
 *  Abort compiling.                                                          */
#error "tmpl_math.h: TMPL_DOUBLE_ENDIANNESS is undefined."

/*  If TMPL_DOUBLE_ENDIANNESS is set to neither big nor little endian it is   *
 *  likely unknown. We will not use IEEE-754 features in this case.           */
#elif TMPL_DOUBLE_ENDIANNESS == TMPL_UNKNOWN_ENDIAN

/*  IEEE-754 support not available. Set this macro to zero.                   */
#define TMPL_HAS_IEEE754_DOUBLE 0

/*  Otherwise we have IEEE-754 support and can provide macros for using this. */
#else

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

/*  Macro for determining if a word is NaN.                                   */
#define TMPL_DOUBLE_IS_NOT_A_NUMBER(w) \
(TMPL_DOUBLE_IS_NAN_OR_INF((w)) && TMPL_DOUBLE_IS_NAN((w)))

/*  Macro for determining if a word is infinite.                              */
#define TMPL_DOUBLE_IS_INFINITY(w) \
(TMPL_DOUBLE_IS_NAN_OR_INF((w)) && !TMPL_DOUBLE_IS_NAN((w)))

/*  Macro for examining the exponent bits of a double.                        */
#define TMPL_DOUBLE_EXPO_BITS(w) ((w).bits.expo)

/*  Macro for examining the sign bit of a double.                             */
#define TMPL_DOUBLE_IS_NEGATIVE(w) ((w).bits.sign)

#endif
/*  End of #if !defined(TMPL_DOUBLE_ENDIANNESS).                              */

/*  Big-Endian 64-bit double.                                                 */
#if TMPL_DOUBLE_ENDIANNESS == TMPL_BIG_ENDIAN

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

/*  Little-Endian 64-bit double.                                              */
#elif TMPL_DOUBLE_ENDIANNESS == TMPL_LITTLE_ENDIAN

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

#endif
/*  End of #if TMPL_DOUBLE_ENDIANNESS == TMPL_BIG_ENDIAN.                     */

#endif
/*  End of include guard.                                                     */
