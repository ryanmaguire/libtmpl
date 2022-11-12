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
 *                              tmpl_infinity                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide infinity for libtmpl.                                         *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing the function prototype.                    *
 *  3.) float.h:                                                              *
 *          C standard library header file containing FLT_MAX, DBL_MAX, and   *
 *          LDBL_MAX. Only included if IEEE-754 support is unavailable.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 7, 2021                                                   *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Function prototype and IEEE-754 data types here.                          */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can set the value of infinity bit-by-bit.        */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Single-precision real positive infinity.                                  */
float tmpl_Float_Infinity(void)
{
    /*  IEEE-754 declares single precision positive infinity to have zero for *
     *  all mantissa components, 1 for the all exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting float.       */
    tmpl_IEEE754_Float x;
    x.bits.sign = 0x0U;
    x.bits.expo = 0xFFU;
    x.bits.man0 = 0x0U;
    x.bits.man1 = 0x0U;
    return x.r;
}
/*  End of tmpl_Float_Infinity.                                               */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  FLT_MAX macro found here.                                                 */
#include <float.h>

/*  Single-precision real positive infinity.                                  */
float tmpl_Float_Infinity(void)
{
    /*  glibc sets the following for compilers lacking IEEE-754 support. This *
     *  may result in compiler warnings, and may also result in undefined     *
     *  behavior, but this is guaranteed to overflow and for the most part    *
     *  it should work in practice.                                           */
    const float x = FLT_MAX;
    return x*x;
}
/*  End of tmpl_Float_Infinity.                                               */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
