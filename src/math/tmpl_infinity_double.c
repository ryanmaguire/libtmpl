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

/*  With IEEE-754 support we can set the double bit-by-bit.                   */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Double-precision real positive infinity.                                  */
double tmpl_Double_Infinity(void)
{
    /*  IEEE-754 declares double precision positive infinity to have zero for *
     *  all mantissa components, 1 for the all exponents bits, and 0 for the  *
     *  sign. Set the bits to this and then return the resulting double.      */
    tmpl_IEEE754_Double x;
    x.bits.sign = 0x0U;
    x.bits.expo = 0x7FFU;
    x.bits.man0 = 0x0U;
    x.bits.man1 = 0x0U;
    x.bits.man2 = 0x0U;
    x.bits.man3 = 0x0U;
    return x.r;
}
/*  End of tmpl_Double_Infinity.                                              */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  DBL_MAX macro found here.                                                 */
#include <float.h>

/*  Double-precision real positive infinity.                                  */
double tmpl_Double_Infinity(void)
{
    /*  glibc sets the infinity to 1.0E10000 for compilers lacking IEEE       *
     *  support. This works, in practice, but is undefined behavior and       *
     *  results in compiler warnings. Instead, use DBL_MAX from float.h,      *
     *  is roughly the largest value possible for double, and return the      *
     *  square of this. This may still be undefined behavior, but works in    *
     *  practice and avoids compiler warnings.                                */
    const double x = DBL_MAX;
    return x*x;
}
/*  End of tmpl_Double_Infinity.                                              */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
