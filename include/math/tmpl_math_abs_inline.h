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
 *                            tmpl_math_abs_inline                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an inline version of absolute value functions.               *
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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 4, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ABS_INLINE_H
#define TMPL_MATH_ABS_INLINE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  This code is only used if inline code is requested. Check TMPL_USE_INLINE.*/
#if TMPL_USE_INLINE == 1

/*  IEEE-754 data types and macros found here.                                */
#include <libtmpl/include/tmpl_math.h>

/*  If IEEE-754 support is available we can get a slight speed boost by       *
 *  setting the appropriate bit to zero, as opposed to an if-then statement.  */
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision absolute value function (fabsf equivalent).              */
static inline float tmpl_Float_Abs(float x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the word to the input x.                        */
    w.r = x;

    /*  Set the sign bit to zero, indicating positive.                        */
    w.bits.sign = 0x0U;

    /*  Return the float part of the union.                                   */
    return w.r;
}
/*  End of tmpl_Float_Abs.                                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/*  Single precision absolute value function (fabsf equivalent).              */
static inline float tmpl_Float_Abs(float x)
{
    /*  Lacking IEEE-754 support, an if-then statement works.                 */
    if (x < 0.0F)
        return -x;
    else
        return x;
}
/*  End of tmpl_Float_Abs.                                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Same idea for double precision.                                           */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision absolute value function (fabs equivalent).               */
static inline double tmpl_Double_Abs(double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the word to the input x.                       */
    w.r = x;

    /*  Set the sign bit to zero, indicating positive.                        */
    w.bits.sign = 0x0U;

    /*  Return the double part of the union.                                  */
    return w.r;
}
/*  End of tmpl_Double_Abs.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Double precision absolute value function.                                 */
static inline double tmpl_Double_Abs(double x)
{
    /*  Lacking IEEE-754 support, an if-then statement works.                 */
    if (x < 0.0)
        return -x;
    else
        return x;
}
/*  End of tmpl_Double_Abs.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Lastly, long double version.                                              */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Long double precision absolute value function (fabsl equivalent).         */
static inline long double tmpl_LDouble_Abs(long double x)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Set the long double part of w to the input.                           */
    w.r = x;

    /*  64-bit double, 80-bit extended, and 128-bit quadruple implementations *
     *  of long double use the same idea: Set the sign bit to zero. The       *
     *  double-double implementation of long double needs to be more careful. */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN \
    && TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN

    /*  Set the sign bit to 0, indicating positive.                           */
    w.bits.sign = 0x0U;
#else

    /*  For double-double we have x = xhi + xlo. Define                       *
     *  abs_x = |x| = abs_xhi + abs_xlo. If xhi and xlo have the same sign,   *
     *  |x| = |xhi| + |xlo| and so abs_xhi = |xhi| and abs_xlo = |xlo|. If    *
     *  xhi and xlo have different signs, |x| = |xhi| - |xlo| so              *
     *  abs_xhi = |xhi| and abs_xlo = -|xlo|. In both cases abs_xhi = |xhi|.  *
     *  The sign of abs_xlo depends on the signs of xhi and xlo. That is,     *
     *  whether or not they are the same. Indeed, the sign of abs_xlo is the  *
     *  exlusive or, also called XOR, of the signs of xhi and xlo. Use this.  */
    w.bits.signb = w.bits.signa ^ w.bits.signb;
    w.bits.signa = 0x0U;
#endif

    /*  Return the long double part of the word.                              */
    return w.r;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Long double precision absolute value function (fabsl equivalent).         */
static inline long double tmpl_LDouble_Abs(long double x)
{
    /*  Lacking IEEE-754 support, an if-then statement works.                 */
    if (x < 0.0L)
        return -x;
    else
        return x;
}
/*  End of tmpl_LDouble_Abs.                                                  */
#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
