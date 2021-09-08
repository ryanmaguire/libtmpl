/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *      Header file where all of these constants are declared.                *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       September 8, 2021                                             *
 ******************************************************************************/

#include <libtmpl/include/tmpl_endianness.h>
#include <libtmpl/include/tmpl_math.h>

/*  Single-precision Not-A-Number.                                            */
float tmpl_Float_NaN(void)
{
    /*  Check for IEEE-754. This is the easiest way to define infinity.       */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1
    /*  IEEE-754 declares single precision positive infinity to have zero for *
     *  all mantissa components, 1 for the all exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting float.       */
    tmpl_IEEE754_Float x;
    x.bits.sign = 0x0U;
    x.bits.expo = 0xFFU;
    x.bits.man0 = 0x40U;
    x.bits.man1 = 0x1U;
    return x.r;
#else
/*  For #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

    /*  glibc sets the following for compilers lacking IEEE-754 support. This *
     *  may result in compiler warnings, and may also result in undefined     *
     *  behavior, but this is guaranteed to overflow and for the most part    *
     *  it should work in practice.                                           */
    float x = 0.0F / 0.0F;
    return x;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */
}
/*  End of tmpl_Float_Infinity.                                               */

/*  Double-precision real positive infinity.                                  */
double tmpl_Double_NaN(void)
{
    /*  Check for IEEE-754. This is the easiest way to define infinity.       */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1
    /*  IEEE-754 declares double precision positive infinity to have zero for *
     *  all mantissa components, 1 for the all exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting float.       */
    tmpl_IEEE754_Double x;
    x.bits.sign = 0x0U;
    x.bits.expo = 0x7FFU;
    x.bits.man0 = 0x8U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x1U;
    return x.r;
#else
/*  For #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

    /*  glibc sets the following for compilers lacking IEEE-754 support. This *
     *  may result in compiler warnings, and may also result in undefined     *
     *  behavior, but this is guaranteed to overflow and for the most part    *
     *  it should work in practice.                                           */
    double x = 0.0 / 0.0;
    return x;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */
}
/*  End of tmpl_Double_Infinity.                                              */

/*  Long double precision real positive infinity.                             */
long double tmpl_LDouble_NaN(void)
{
    /*  Simply cast the double version and return.                            */
    double x = tmpl_Double_NaN();
    long double lx = (long double)x;
    return lx;
}
/*  End of tmpl_LDouble_Infinity.                                             */
