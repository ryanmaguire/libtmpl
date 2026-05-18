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
 *                            tmpl_infinity_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides infinity for long double precision numbers.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Infinity                                                 *
 *  Purpose:                                                                  *
 *      Returns long double precision infinity.                               *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      inf (long double):                                                    *
 *          Infinity.                                                         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Set the bits to represent long double infinity. For 64-bit double,*
 *          80-bit extended, and 128-bit quadruple implementations of long    *
 *          double, this can be achieved by setting the bit-field in a        *
 *          tmpl_IEEE754_LDouble object. For 128-bit double-double, we set    *
 *          the high double to double-precision infinity using a similar      *
 *          bit-field trick, and set the low double to zero.                  *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Mimic glibc's method, return the literal 1.0E100000L. This value  *
 *          is too large to fit into any realistic implementation of long     *
 *          double, including 256-bit octuple precision. Use of such a large  *
 *          literal may invoke compiler warnings, but this works in practice. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL and other helper macros.  *
 *  2.) tmpl_ieee754_ldouble.h:                                               *
 *          Provides tmpl_IEEE754_LDouble, used for type punning.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/12: Ryan Maguire                                                  *
 *      Migrated inf functions to their own directory. Added inline support.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_INLINE_INFINITY_LDOUBLE_H
#define TMPL_INLINE_INFINITY_LDOUBLE_H

/*  TMPL_INLINE_DECL and other helper macros found here.                      */
#include <libtmpl/include/tmpl_config.h>

/*  With IEEE-754 support we can set the value of infinity bit-by-bit.        */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_UNKNOWN

/*  tmpl_IEEE754_LDouble type provided here.                                  */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  64-bit long double is implemented the same as 64-bit double.              */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Long double precision real positive infinity.                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Infinity(void)
{
    /*  Union used for type-punning a long double with the bits it represents.*/
    tmpl_IEEE754_LDouble x;

    /*  IEEE-754 declares double precision positive infinity to have zero for *
     *  all mantissa components, 1 for all the exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting long double. */
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x00U;
    x.bits.man1 = 0x00U;
    x.bits.man2 = 0x00U;
    x.bits.man3 = 0x00U;

    /*  Return the long double part of the word. This is now infinity.        */
    return x.r;
}
/*  End of tmpl_LDouble_Infinity.                                             */

/*  Extended precision. This is the only precision with a bit for the integer *
 *  part of the number. Long doubles are written x = s * n.m * 2^e.           */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

/******************************************************************************
 *                          80-Bit Extended Version                           *
 ******************************************************************************/

/*  Long double precision real positive infinity.                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Infinity(void)
{
    /*  Union used for type-punning a long double with the bits it represents.*/
    tmpl_IEEE754_LDouble x;

    /*  80-bit extended. Similar to double but we need to set the integer bit *
     *  to 1. 32-bit float and 64-bit double do not have an integer bit.      */
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.intr = 0x1U;
    x.bits.man0 = 0x00U;
    x.bits.man1 = 0x00U;
    x.bits.man2 = 0x00U;
    x.bits.man3 = 0x00U;

    /*  Return the long double part of the word. This is now infinity.        */
    return x.r;
}
/*  End of tmpl_LDouble_Infinity.                                            */

/*  Quadruple precision. Similar to 64-bit double, but with more bits.        */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Long double precision real positive infinity.                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Infinity(void)
{
    /*  Union used for type-punning a long double with the bits it represents.*/
    tmpl_IEEE754_LDouble x;

    /*  128-bit quadruple. Similar to double but with more mantissa parts.    */
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x00U;
    x.bits.man1 = 0x00U;
    x.bits.man2 = 0x00U;
    x.bits.man3 = 0x00U;
    x.bits.man4 = 0x00U;
    x.bits.man5 = 0x00U;
    x.bits.man6 = 0x00U;

    /*  Return the long double part of the word. This is now infinity.        */
    return x.r;
}
/*  End of tmpl_LDouble_Infinity.                                             */

/*  Double-double precision. Similar to 64-bit double but with an extra zero. */
#else

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Long double precision real positive infinity.                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Infinity(void)
{
    /*  Declare necessary variables.                                          */
    tmpl_IEEE754_LDouble x;

    /*  Set the high double to infinity, bit-by-bit.                          */
    x.bits.sign = 0x0U;
    x.bits.expo = TMPL_LDOUBLE_NANINF_EXP;
    x.bits.man0 = 0x00U;
    x.bits.man1 = 0x00U;
    x.bits.man2 = 0x00U;
    x.bits.man3 = 0x00U;

    /*  Set the low double to zero and return.                                */
    x.d[1] = 0.0;
    return x.r;
}
/*  End of tmpl_LDouble_Infinity.                                             */

#endif
/*  End of double-double version.                                             */

#else
/*  Else for #if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_UNKNOWN.             */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Long double precision real positive infinity.                             */
TMPL_INLINE_DECL
long double tmpl_LDouble_Infinity(void)
{
    /*  glibc sets HUGE_VAL to 1.0E10000 for compilers lacking IEEE support.  *
     *  This works in practice, but is undefined behavior and may result in   *
     *  compiler warnings. Because of this, a compiler diagnostic may be      *
     *  issued when using the portable version of this function. On compilers *
     *  like GCC or Clang, use -Wno-overflow to disable this warning. glibc   *
     *  contains the following note:                                          *
     *      This may provoke compiler warnings, and may not be rounded to     *
     *      +Infinity in all IEEE 754 rounding modes, but is the best that    *
     *      can be done in ISO C while remaining a constant expression.       *
     *      10,000 is greater than the maximum (decimal) exponent for all     *
     *      supported floating-point formats and widths.                      *
     *  256-bit octuple precision does indeed have a width large enough to    *
     *  fit 1.0E10000, but as of 2026 there is no hardware support for this   *
     *  type of floating-point number. Adding an extra zero to the exponent   *
     *  (1.0E100000 instead of 1.0E10000) means 256-bit octuple-precision     *
     *  floating-point numbers cannot fit this value either.                  */
    return 1.0E100000L;
}
/*  End of tmpl_LDouble_Infinity.                                             */

#endif
/*  End of #if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_UNKNOWN.               */

#endif
/*  End of include guard.                                                     */
