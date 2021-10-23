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
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

/*  Function prototype and IEEE-754 data types here.                          */
#include <libtmpl/include/tmpl_math.h>

/*  Single-precision Not-A-Number.                                            */
float tmpl_Float_NaN(void)
{
    /*  Check for IEEE-754. This is the easiest way to define NaN.            */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

    /*  IEEE-754 declares single precision nan to have 1 for first and last   *
     *  bits of the mantissa, 1 for the all exponents bits, and 0 for the     *
     *  sign. Set the bits to this and then return the resulting float.       */
    tmpl_IEEE754_Float x;
    x.bits.sign = 0x0U;
    x.bits.expo = 0xFFU;

    /*  bits.man0 has 7 bits. 1000000 is 0x40 in hex.                         */
    x.bits.man0 = 0x40U;

    /*  man1 has 16 bits. 0000000000000001 is 0x1 in hex.                     */
    x.bits.man1 = 0x1U;
    return x.r;
#else
/*  For #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

    /*  glibc sets the following for compilers lacking IEEE-754 support. This *
     *  may result in compiler warnings, and may also result in undefined     *
     *  behavior, but works often in practice.                                */
    float x = 0.0F;
    return x / x;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1    */

}
/*  End of tmpl_Float_NaN.                                                    */

/*  Double-precision Not-A-Number.                                            */
double tmpl_Double_NaN(void)
{
    /*  Check for IEEE-754. This is the easiest way to define NaN.            */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

    /*  IEEE-754 declares double precision nan to have 1 for first and last   *
     *  bits of the mantissa, 1 for the all exponents bits, and 0 for the     *
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
     *  behavior, but works often in practice.                                */
    double x = 0.0;
    return x / x;
#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1  */

}
/*  End of tmpl_Double_Infinity.                                              */

/*  Long double precision Not-A-Number.                                       */
long double tmpl_LDouble_NaN(void)
{
    /*  Simply cast the double version and return.                            */
    double x = tmpl_Double_NaN();
    long double lx = (long double)x;
    return lx;
}
/*  End of tmpl_LDouble_NaN.                                                  */
