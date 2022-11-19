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
 *                                 tmpl_nan                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide Not-A-Number for libtmpl.                                     *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype and IEEE-754 data types here.                          */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can set the value of NaN bit-by-bit.             */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  64-bit long double is implemented the same as 64-bit double.              */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Long double precision real positive NaN.                                  */
long double tmpl_LDouble_NaN(void)
{
    /*  This is the same as 64-bit double precision. IEEE-754 declares double *
     *  precision positive NaN to have 1 in the first and last mantissa bits, *
     *  1 for the all exponents bits, and 0 for the sign. Set the bits to     *
     *  this and then return the resulting double.                            */
    tmpl_IEEE754_LDouble x;
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x8U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x1U;
    return x.r;
}
/*  End of tmpl_LDouble_NaN.                                                  */

/*  Extended precision. This is the only precision with a bit for the integer *
 *  part of the number. Long doubles are written x = s * n.m * 2^e.           */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN   || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                          80-Bit Extended Version                           *
 ******************************************************************************/

/*  Long double precision real positive NaN.                                  */
long double tmpl_LDouble_NaN(void)
{
    /*  80-bit extended. Similar to double but need to set the integer bit to *
     *  1. 32-bit float and 64-bit double do not have an integer bit.         */
    tmpl_IEEE754_LDouble x;
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x4000U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x1U;
    x.bits.intr = 0x1U;
    return x.r;
}
/*  End of tmpl_LDouble_NaN.                                                  */

/*  Quadruple precision. Similar to 64-bit double, but with more bits.        */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN    || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Long double precision real positive NaN.                                  */
long double tmpl_LDouble_NaN(void)
{
    /*  128-bit quadruple. Similar to double but with more mantissa parts.    */
    tmpl_IEEE754_LDouble x;
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x8000U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x0U;
    x.bits.man4 = 0x0U;
    x.bits.man5 = 0x0U;
    x.bits.man6 = 0x1U;
    return x.r;
}
/*  End of tmpl_LDouble_NaN.                                                  */

/*  Double-double precision. Similar to 64-bit double but with an extra zero. */
#else

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Long double precision real positive NaN.                                  */
long double tmpl_LDouble_NaN(void)
{
    /*  Declare necessary variables.                                          */
    tmpl_IEEE754_LDouble x;

    /*  Set the high double to NaN, bit-by-bit.                               */
    x.bits.signa = 0x0U;
    x.bits.expoa = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0a = 0x8U;
    x.bits.man1a = 0x0U;
    x.bits.man2a = 0x0U;
    x.bits.man3a = 0x1U;

    /*  Set the low double to zero and return.                                */
    x.d[1] = 0.0;
    return x.r;
}
/*  End of tmpl_LDouble_NaN.                                                  */

#endif
/*  End of double-double version.                                             */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision Not-A-Number.                                       */
long double tmpl_LDouble_NaN(void)
{
    /*  Simply cast the double version and return.                            */
    long double x = 0.0L;
    return x / x;
}
/*  End of tmpl_LDouble_NaN.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */
