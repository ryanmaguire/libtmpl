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
 *                         tmpl_complex_abs_ldouble                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Abs:                                                    *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *      Because x^2 and y^2 are computed as intermediate steps, this method   *
 *      will overflow for values greater than sqrt(LDBL_MAX). The safe way to *
 *      do this is via:                                                       *
 *                                                                            *
 *          |z| = |x| sqrt(1+(y/x)^2)                                         *
 *                                                                            *
 *      if |x| > |y|, and:                                                    *
 *                                                                            *
 *          |z| = |y| sqrt(1 + (x/y)^2)                                       *
 *                                                                            *
 *      otherwise. This is about 1.3-1.5x slower. If IEEE-754 support is      *
 *      available, we need only check if max(|x|, |y|) is in the range        *
 *      (2^-512, 2^512), scaling by a constant if not. This is about as fast  *
 *      as the naive method.                                                  *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (long double):                                                  *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_LDouble_Abs     (tmpl_math.h)                                    *
 *          Computes the absolute value of a real number.                     *
 *      tmpl_LDouble_Sqrt    (tmpl_math.h)                                    *
 *          Computes the square root of a real number.                        *
 *  Notes:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_USE_INLINE macro found here.                                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  3.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley college for librssringoccs).                  *
 *  2020/12/01: Ryan Maguire                                                  *
 *      Added abs squared functions.                                          *
 *  2020/12/02: Ryan Maguire                                                  *
 *      Moved abs squared functions to their own file.                        *
 *      Frozen for rss_ringoccs v1.3.                                         *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from librssringoccs to libtmpl.                                *
 *      Edited code, made it compatibile with the rest of libtmpl. Removed    *
 *      "C99" mode. Removed complex.h as a dependency.                        *
 *      Soft freeze for alpha version of libtmpl.                             *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited license.                                                       *
 *  2021/05/11: Ryan Maguire                                                  *
 *      Hard freeze for alpha release of libtmpl. Reviewed code and comments. *
 *      No more changes unless something breaks.                              *
 *  2021/10/19: Ryan Maguire                                                  *
 *      Changed the algorithm to prevent certain numbers from overflowing.    *
 *      Complex numbers with a magnitude greater than sqrt(DBL_MAX) will      *
 *      overflow, even though they shouldn't for a proper implementation.     *
 *      This has been fixed, albeit at the expense of speed.                  *
 *  2022/04/28: Ryan Maguire                                                  *
 *      Changed algorithm to incorporate IEEE-754 tricks. 1.4x speed up.      *
 ******************************************************************************/

/*  Header file containing basic math functions.                              */
#include <libtmpl/include/tmpl_math.h>

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN            || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN               || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/******************************************************************************
 *                   64-Bit Double / 128-Bit Double-Double                    *
 ******************************************************************************/

#define TMPL_BIG_SCALE (1.340780792994259709957402E+154L)
#define TMPL_RCPR_BIG_SCALE (7.458340731200206743290965E-155L)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x200U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1E6U)

#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN   || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_BIG_ENDIAN

/******************************************************************************
 *                               80-Bit Extended                              *
 ******************************************************************************/

#define TMPL_BIG_SCALE (1.090748135619415929462984244733E2466L)
#define TMPL_RCPR_BIG_SCALE (9.16801933777423582810706196024E-2467L)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x2000U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1FE0U)

#else

/******************************************************************************
 *                             128-Bit Quadruple                              *
 ******************************************************************************/

#define TMPL_BIG_SCALE (1.090748135619415929462984244733E2466L)
#define TMPL_RCPR_BIG_SCALE (9.16801933777423582810706196024E-2467L)
#define TMPL_EXPO_TOO_HIGH (TMPL_LDOUBLE_BIAS + 0x2000U)
#define TMPL_EXPO_TOO_LOW (TMPL_LDOUBLE_BIAS - 0x1FC8U)
#endif

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
long double tmpl_LDouble_Hypot(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_LDouble w;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    long double abs_x = tmpl_LDouble_Abs(x);
    long double abs_y = tmpl_LDouble_Abs(y);

    if (x < y)
        w.r = abs_y;
    else
        w.r = abs_x;

    if (TMPL_LDOUBLE_EXPO_BITS(w) < TMPL_EXPO_TOO_HIGH)
    {
        if (TMPL_LDOUBLE_EXPO_BITS(w) > TMPL_EXPO_TOO_LOW)
            return tmpl_LDouble_Sqrt(abs_x*abs_x + abs_y*abs_y);

        abs_x *= TMPL_BIG_SCALE;
        abs_y *= TMPL_BIG_SCALE;
        return TMPL_RCPR_BIG_SCALE*tmpl_LDouble_Sqrt(abs_x*abs_x + abs_y*abs_y);
    }

    abs_x *= TMPL_RCPR_BIG_SCALE;
    abs_y *= TMPL_RCPR_BIG_SCALE;
    return TMPL_BIG_SCALE * tmpl_LDouble_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_LDouble_Hypot.                                                */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef TMPL_BIG_SCALE
#undef TMPL_RCPR_BIG_SCALE
#undef TMPL_EXPO_TOO_HIGH
#undef TMPL_EXPO_TOO_LOW

#else
/*  Else for #if TMPL_HAS_IEEE754_LDOUBLE == 1.                               */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the magnitude of the vector (x, y) in the plane.   */
long double tmpl_LDouble_Hypot(long double x, long double y)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    long double rcpr_t;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    long double abs_x = tmpl_LDouble_Abs(x);
    long double abs_y = tmpl_LDouble_Abs(y);

    /*  Compute the maximum of |x| and |y|. This syntax from the C language   *
     *  is a bit strange. a = (b < c ? c : b) says if b is less than c, set a *
     *  to c, otherwise set a to b.                                           */
    const long double t = (abs_x < abs_y ? abs_y : abs_x);

    /*  Division by zero is generally viewed as bad. If the max of |x| and    *
     *  |z| is zero, |z| = 0. Return this.                                    */
    if (t == 0.0L)
        return 0.0L;

    /*  Precompute 1/t to turn 2 divisions into 1 division and 2 products.    */
    rcpr_t = 1.0L / t;

    /*  Scale x and y by 1/t.                                                 */
    abs_x *= rcpr_t;
    abs_y *= rcpr_t;

    /*  |z| can safely be computed as |z| = t * sqrt((x/t)^2 + (y/t)^2)       *
     *  without risk of underflow or overflow.                                */
    return t * tmpl_LDouble_Sqrt(abs_x*abs_x + abs_y*abs_y);
}
/*  End of tmpl_LDouble_Hypot.                                                */

#endif
/*  End of #if TMPL_HAS_IEEE754_LDOUBLE == 1.                                 */
