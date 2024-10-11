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
 *                                tmpl_config                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      This file is created by the config.c file. It provides the macros     *
 *      TMPL_ENDIANNESS, TMPL_FLOAT_ENDIANNESS, TMPL_DOUBLE_ENDIANNESS, and   *
 *      TMPL_LDOUBLE_ENDIANNESS which are used by functions where the code is *
 *      endian specific and to check if IEEE-754 is supported. It also        *
 *      provides the macros TMPL_USE_INLINE and TMPL_USE_MATH_ALGORITHMS      *
 *      determine if inline functions should be used, and if libtmpl's        *
 *      implementation of libm should be used.                                *
 ******************************************************************************/

#ifndef TMPL_CONFIG_H
#define TMPL_CONFIG_H

#define TMPL_BIG_ENDIAN 0
#define TMPL_LITTLE_ENDIAN 1
#define TMPL_MIXED_ENDIAN 2
#define TMPL_UNKNOWN_ENDIAN 3

#define TMPL_ONES_COMPLEMENT 0
#define TMPL_TWOS_COMPLEMENT 1
#define TMPL_SIGN_AND_MAGNITUDE 2
#define TMPL_UNKNOWN_SIGNED_REP 3

#define TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN 0
#define TMPL_LDOUBLE_64_BIT_BIG_ENDIAN 1
#define TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN 2
#define TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN 3
#define TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN 4
#define TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN 5
#define TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN 6
#define TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN 7
#define TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN 8
#define TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN 9
#define TMPL_LDOUBLE_UNKNOWN 10

#define TMPL_LDOUBLE_64_BIT 0
#define TMPL_LDOUBLE_80_BIT 1
#define TMPL_LDOUBLE_128_BIT 2
#define TMPL_LDOUBLE_DOUBLEDOUBLE 3

#define TMPL_ENDIANNESS TMPL_LITTLE_ENDIAN
#define TMPL_SIGNED_REP TMPL_TWOS_COMPLEMENT
#define TMPL_FLOAT_ENDIANNESS TMPL_LITTLE_ENDIAN
#define TMPL_DOUBLE_ENDIANNESS TMPL_LITTLE_ENDIAN
#define TMPL_LDOUBLE_ENDIANNESS TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
#define TMPL_LDOUBLE_TYPE TMPL_LDOUBLE_64_BIT

#define TMPL_USE_INLINE 1
#define TMPL_INLINE_DECL static inline
#define TMPL_STATIC_INLINE static inline
#define TMPL_USE_MATH_ALGORITHMS 1
#define TMPL_USE_MEMCPY 0

#define TMPL_HAS_ASCII 1

#define TMPL_HAS_FLOATINT32 1
#define TMPL_HAS_FLOATINT64 1
#define TMPL_HAS_FLOATINT_LONG_DOUBLE 1
#define TMPL_DOUBLE_VOLATILE_SPLIT
#endif
