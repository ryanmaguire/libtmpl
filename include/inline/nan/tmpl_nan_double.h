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
 *                              tmpl_nan_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides Not-a-Number for double precision numbers.                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL and other helper macros.  *
 *  2.) tmpl_floatint_double.h:                                               *
 *          Provides the tmpl_IEEE754_FloatInt64 type. Used for type punning. *
 *          Only included if 64-bit unsigned integers are available.          *
 *  3.) tmpl_ieee754_double.h:                                                *
 *          Provides tmpl_IEEE754_Double. Also used for type punning. Used if *
 *          IEEE-754 support is available, but 64-bit integers are not.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/03/23: Ryan Maguire                                                  *
 *      Migrated NaN functions to their own directory. Added inline support.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INLINE_NAN_DOUBLE_H
#define TMPL_INLINE_NAN_DOUBLE_H

/*  Function prototype and IEEE-754 data types defined here.                  */
#include <libtmpl/include/tmpl_config.h>

/*  Simplest method uses 64-bit integers for type punning. Check for support. */
#if TMPL_HAS_FLOATINT64 == 1

/******************************************************************************
 *                   IEEE-754 Version with 64-Bit Integers                    *
 ******************************************************************************/

/*  Union providing type-punning for 64-bit doubles with 64-bit integers.     */
#include <libtmpl/include/types/tmpl_floatint_double.h>

/*  Function for producing a double precision NaN (Not-a-Number).             */
TMPL_INLINE_DECL
double tmpl_Double_NaN(void)
{
    /*  Union of a double and a 64-bit unsigned integer.                      */
    tmpl_IEEE754_FloatInt64 u;

    /*  NaN is given by a zero in the sign bit, all ones in the exponent bits,*
     *  and a one in the least and most significant mantissa bits (zero for   *
     *  the other mantissa bits). In binary this is:                          *
     *      0 11111111111 1000000000000000000000000000000000000000000000000001*
     *  This number is 9221120237041090561 in decimal, or  0x7FF8000000000001 *
     *  in hexidecimal. Set the integer part of the union to this value.      */
    u.n = 0x7FF8000000000001U;

    /*  Return the double part of the word. This is now a NaN.                */
    return u.f;
}
/*  End of tmpl_Double_NaN.                                                   */

/*  Lacking 64-bit fixed-width integers, we can try to set the bits of the    *
 *  double using a bit-field. Check for IEEE-754 support.                     */
#elif TMPL_DOUBLE_ENDIANNESS != TMPL_UNKNOWN_ENDIAN

/******************************************************************************
 *                  IEEE-754 Version without 64-Bit Integers                  *
 ******************************************************************************/

/*  Union used for type-punning doubles using a bit-field found here.         */
#include <libtmpl/include/types/tmpl_ieee754_double.h>

/*  Function for producing a double precision NaN (Not-a-Number).             */
TMPL_INLINE_DECL
double tmpl_Double_NaN(void)
{
    /*  Union used for type-punning a double with the bits it represents.     */
    tmpl_IEEE754_Double x;

    /*  IEEE-754 declares double precision nan to have 1 for first and last   *
     *  bits of the mantissa, 1 for the all exponents bits, and 0 for the     *
     *  sign. Set the bits to this and then return the resulting double.      */
    x.bits.sign = 0x0U;
    x.bits.expo = 0x7FFU;
    x.bits.man0 = 0x8U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x1U;

    /*  The bits are set, return the double part of the union.                */
    return x.r;
}
/*  End of tmpl_Double_NaN.                                                   */

/*  Lacking support for fixed-width integers or IEEE-754 support, returning   *
 *  0 / 0 usually works in practice. This is technically undefined behavior,  *
 *  but works on most systems.                                                */
#else

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for producing a double precision NaN (Not-a-Number).             */
TMPL_INLINE_DECL
double tmpl_Double_NaN(void)
{
    /*  glibc sets the following when IEEE-754 support is unavailable. This   *
     *  may result in compiler warnings, and may also result in undefined     *
     *  behavior, but often works in practice.                                */
    double x = 0.0;
    return x / x;
}
/*  End of tmpl_Double_Infinity.                                              */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

#endif
/*  End of include guard.                                                     */
