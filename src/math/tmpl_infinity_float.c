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
 *                             tmpl_infinity_float                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides infinity for single-precision numbers.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_ALWAYS_INLINE and other macros.       *
 *  2.) tmpl_attributes.h:                                                    *
 *          Provides (optional) C23 attributes for optimization.              *
 *  3.) tmpl_ieee754_float.h:                                                 *
 *          Provides tmpl_IEEE754_Float, used for type punning if available.  *
 *  4.) tmpl_math.h:                                                          *
 *          Provides the function prototype.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/12: Ryan Maguire                                                  *
 *      Migrated inf functions to their own directory. Added inline support.  *
 *  2026/07/26: Ryan Maguire                                                  *
 *      Merged inline and non-inline versions, added C23 attributes, using    *
 *      the new IEEE-754 union which fuses the older version and the FloatInt *
 *      type together.                                                        *
 ******************************************************************************/

/*  TMPL_ALWAYS_INLINE and other helper macros found here.                    */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Union used for type-punning floats using a bit-field found here.          */
#include <libtmpl/include/types/tmpl_ieee754_float.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Simplest method uses 32-bit integers for type punning. Check for support. */
#if TMPL_HAS_FLOATINT32 == 1

/******************************************************************************
 *                   IEEE-754 Version with 32-Bit Integers                    *
 ******************************************************************************/

/*  Function for producing single-precision infinity.                         */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float tmpl_Float_Infinity(void)
TMPL_UNSEQUENCED
{
    /*  Union of a float and a 32-bit unsigned integer.                       */
    tmpl_IEEE754_Float u;

    /*  IEEE-754 declares single-precision positive infinity to have zero for *
     *  all mantissa components, 1 for all the exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting float. In    *
     *  binary this is:                                                       *
     *                                                                        *
     *      0 11111111 00000000000000000000000                                *
     *                                                                        *
     *  This number is 2139095040 in decimal, or  0x7f800000 in hexadecimal.  *
     *  Set the integer part of the union to this value.                      */
    u.n = TMPL_UINT32_LITERAL(0x7f800000);

    /*  Return the float part of the word. This is now infinity.              */
    return u.r;
}
/*  End of tmpl_Float_Infinity.                                               */

/*  Lacking 32-bit fixed-width integers, we can try to set the bits of the    *
 *  float using a bit-field. Check for IEEE-754 support.                      */
#elif TMPL_FLOAT_ENDIANNESS != TMPL_UNKNOWN_ENDIAN

/******************************************************************************
 *                  IEEE-754 Version without 32-Bit Integers                  *
 ******************************************************************************/

/*  Function for producing single-precision infinity.                         */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float tmpl_Float_Infinity(void)
TMPL_UNSEQUENCED
{
    /*  Union used for type-punning a float with the bits it represents.      */
    tmpl_IEEE754_Float x;

    /*  IEEE-754 declares single-precision positive infinity to have zero for *
     *  all mantissa components, 1 for the all exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting float.       */
    x.bits.sign = 0x0U;
    x.bits.expo = 0xFFU;
    x.bits.man0 = 0x00U;
    x.bits.man1 = 0x00U;

    /*  Return the float part of the word. This is now infinity.              */
    return x.r;
}
/*  End of tmpl_Float_Infinity.                                               */

#else
/*  Else for #if TMPL_HAS_FLOATINT32 == 1.                                    */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for producing single-precision infinity.                         */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
float tmpl_Float_Infinity(void)
TMPL_UNSEQUENCED
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
    return 1.0E100000F;
}
/*  End of tmpl_Float_Infinity.                                               */

#endif
/*  End of #if TMPL_HAS_FLOATINT32 == 1.                                      */
