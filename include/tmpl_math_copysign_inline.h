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
 *                         tmpl_math_copysign_inline                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inline version of copysign functions.                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing IEEE754 types.                             *
 *  2.) tmpl_config.h:                                                        *
 *          Header file containing the endianness of your system. This file   *
 *          is built with config.c in libtmpl/. The Makefile automatically    *
 *          runs this, as does the make.sh script. This also contains the     *
 *          TMPL_USE_INLINE and TMPL_USE_MATH_ALGORITHMS macros.              *
 ******************************************************************************
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 4, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_COPYSIGN_INLINE_H
#define TMPL_MATH_COPYSIGN_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can skip if-then statements.                     */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision copysign function.                                       */
static inline float tmpl_Float_Copysign(float x, float y)
{
    tmpl_IEEE754_Float wx, wy;

    wx.r = x;
    wy.r = y;
    wx.bits.sign = wy.bits.sign;
    return wx.r;
}
/*  End of tmpl_Float_Copysign.                                               */

#else
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1        */

/*  Float precision copysign function.                                        */
static inline float tmpl_Float_Copysign(float x, float y)
{
    x = tmpl_Float_Abs(x);
    return (y < 0.0F ? -x : x);
}
/*  End of tmpl_Float_Copysign.                                               */

#endif
/*  #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.       */

/*  With IEEE-754 support we can skip if-then statements.                     */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision copysign function.                                       */
static inline double tmpl_Double_Copysign(double x, double y)
{
    tmpl_IEEE754_Double wx, wy;

    wx.r = x;
    wy.r = y;
    wx.bits.sign = wy.bits.sign;
    return wx.r;
}
/*  End of tmpl_Double_Copysign.                                              */

#else
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1      */

/*  Double precision copysign function.                                       */
static inline double tmpl_Double_Copysign(double x, double y)
{
    x = tmpl_Double_Abs(x);
    return (y < 0.0 ? -x : x);
}
/*  End of tmpl_Double_Copysign.                                              */

#endif
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1.     */

/*  64-bit double, 80-bit extended, and 128-bit quadruple implementations of  *
 *  long double all have a "sign" bit. We can just copy this from y to x.     *
 *  double-double is a bit more complicated.                                  */
#if \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN            || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN               || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN   || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN     || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  Double precision copysign function.                                       */
static inline long double tmpl_LDouble_Copysign(long double x, long double y)
{
    tmpl_IEEE754_LDouble wx, wy;

    wx.r = x;
    wy.r = y;
    wx.bits.sign = wy.bits.sign;
    return wx.r;
}
/*  End of tmpl_LDouble_Copysign.                                             */

#else
/*  No IEEE-754 support, or double-double implemented. Use portable method.   */

/*  Long double precision copysign function.                                  */
static inline long double tmpl_LDouble_Copysign(long double x, long double y)
{
    x = tmpl_LDouble_Abs(x);
    return (y < 0.0L ? -x : x);
}
/*  End of tmpl_LDouble_Copysign.                                             */

#endif
/*  End of check for TMPL_LDOUBLE_ENDIANNESS.                                 */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
