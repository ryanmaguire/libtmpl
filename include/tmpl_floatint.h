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
 *                               tmpl_floatint                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for type-punning floating point numbers as integers.   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Location of TMPL_HAS_FLOATINT32 and TMPL_HAS_FLOATINT64.          *
 *  2.) tmpl_inttype.h:                                                       *
 *          Header file containing fixed-width integer data types.            *
 *  3.) tmpl_ieee754_float.h:                                                 *
 *          Header file with a union for IEEE-754 single precision numbers.   *
 *  4.) tmpl_ieee754_double.h:                                                *
 *          Header file with a union for IEEE-754 double precision numbers.   *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2023/08/10                                                        *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FLOATINT_H
#define TMPL_FLOATINT_H

/*  Location of the TMPL_HAS_FLOATINT32 and TMPL_HAS_FLOATINT64 macros.       */
#include <libtmpl/include/tmpl_config.h>

/*  Fixed-width integer data types found here.                                */
#include <libtmpl/include/tmpl_inttype.h>

/*  If float is represented using the 32-bit IEEE-754 format, and if 32-bit   *
 *  unsigned integers are available, provide a union for type-punning.        */
#if TMPL_HAS_FLOATINT32 == 1

/*  32-bit float union found here.                                            */
#include <libtmpl/include/tmpl_ieee754_float.h>

/*  Union for type-punning a 32-bit float with a 32-bit int.                  */
typedef union tmpl_IEEE754_FloatInt32_Def {

    /*  The "word" the data represents. This splits the float into its bits.  */
    tmpl_IEEE754_Float w;

    /*  The integer value the 32-bits for the float represent.                */
    tmpl_UInt32 n;

    /*  The actual floating point number.                                     */
    float f;
} tmpl_IEEE754_FloatInt32;

#endif
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */

/*  If double is represented using the 64-bit IEEE-754 format, and if 64-bit  *
 *  unsigned integers are available, provide a union for type-punning.        */
#if TMPL_HAS_FLOATINT64 == 1

/*  64-bit double union found here.                                           */
#include <libtmpl/include/tmpl_ieee754_double.h>

/*  Union for type-punning a 64-bit double with a 64-bit int.                 */
typedef union tmpl_IEEE754_FloatInt64_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_Double w;

    /*  The integer value the 64-bits for the double represent.               */
    tmpl_UInt64 n;

    /*  The actual floating point number.                                     */
    double f;
} tmpl_IEEE754_FloatInt64;

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

/*  Long double is a lot more complicated with the various types of           *
 *  representations. Check them carefully.                                    */
#if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1

/*  Union of a long double and the bits representing it.                      */
#include <libtmpl/include/tmpl_ieee754_ldouble.h>

/*  Use the same representation as 64-bit double.                             */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                               64-Bit Double                                *
 ******************************************************************************/

/*  Union for type-punning a 64-bit long double with a 64-bit int.            */
typedef union tmpl_IEEE754_FloatIntLongDouble_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_LDouble w;

    /*  The integer value the 64-bits for the long double represent.          */
    tmpl_UInt64 n;

    /*  The actual floating point number.                                     */
    long double f;
} tmpl_IEEE754_FloatIntLongDouble;

/*  80-bit extended has 4 representation. 16 bits of padding vs. 48 bits, and *
 *  little endian vs. big endian. The layout differs for each version.        */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN

/******************************************************************************
 *                       96-Bit Extended (Little Endian)                      *
 ******************************************************************************/

/*  Union for type-punning a 96-bit long double with 64-bit and 32-bit ints.  */
typedef union tmpl_IEEE754_FloatIntLongDouble_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_LDouble w;

    /*  The integer value the 96-bits for the long double represent.          */
    struct {
        tmpl_UInt64 lo;
        tmpl_UInt32 hi;
    } words;

    /*  The actual floating point number.                                     */
    long double f;
} tmpl_IEEE754_FloatIntLongDouble;

/*  96-bits, but with the order reversed.                                     */
#elif TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                        96-Bit Extended (Big Endian)                        *
 ******************************************************************************/

/*  Union for type-punning a 96-bit long double with 64-bit and 32-bit ints.  */
typedef union tmpl_IEEE754_FloatIntLongDouble_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_LDouble w;

    /*  The integer values the 96-bits for the long double represent.         */
    struct {
        tmpl_UInt64 lo;
        tmpl_UInt32 hi;

    } words;

    /*  The actual floating point number.                                     */
    long double f;
} tmpl_IEEE754_FloatIntLongDouble;

/*  All 128-bit types are handles similarly. The endianness differs.          */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *        128-Bit Extended / Quadruple / Double-Double (Little Endian)        *
 ******************************************************************************/

/*  Union for type-punning a 128-bit long double with 64-bit ints.            */
typedef union tmpl_IEEE754_FloatIntLongDouble_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_LDouble w;

    /*  The integer values the 128-bits for the long double represent.        */
    struct {
        tmpl_UInt64 lo;
        tmpl_UInt64 hi;
    } words;

    /*  The actual floating point number.                                     */
    long double f;
} tmpl_IEEE754_FloatIntLongDouble;

#else

/******************************************************************************
 *          128-Bit Extended / Quadruple / Double-Double (Big Endian)         *
 ******************************************************************************/

/*  Union for type-punning a 128-bit long double with 64-bit ints.            */
typedef union tmpl_IEEE754_FloatIntLongDouble_Def {

    /*  The "word" the data represents. This splits the double into its bits. */
    tmpl_IEEE754_LDouble w;

    /*  The integer values the 128-bits for the long double represent.        */
    struct {
        tmpl_UInt64 hi;
        tmpl_UInt64 lo;
    } words;

    /*  The actual floating point number.                                     */
    long double f;
} tmpl_IEEE754_FloatIntLongDouble;

#endif
/*  End of #TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                               */

#endif
/*  End of #if TMPL_HAS_FLOATINT_LONG_DOUBLE == 1.                            */

#endif
/*  End of include guard.                                                     */
