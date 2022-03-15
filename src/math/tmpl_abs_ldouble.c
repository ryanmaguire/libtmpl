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
 *                              tmpl_abs_ldouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at long double precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Abs                                                      *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (long double):                                                  *
 *          The absolute value of x.                                          *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and/or libtmpl algorithms have  *
 *      been requested. fabsl or fabs from math.h otherwise.                  *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, simply set the sign bit of the      *
 *      input to 0.                                                           *
 *                                                                            *
 *      If IEEE-754 is not supported, an if-then statement to check if the    *
 *      input is positive, returning x for non-negative and -x otherwise.     *
 *                                                                            *
 *  Notes:                                                                    *
 *      If IEEE-754 is not supported and if the input is NaN one may get      *
 *      +/- NaN (which is still NaN). This is because NaN always              *
 *      evaluates to false when a comparison is made (==, <, >, etc.).        *
 *                                                                            *
 *      A time and accuracy test against glibc yields the following:          *
 *                                                                            *
 *          Using IEEE-754 method:                                            *
 *                                                                            *
 *          tmpl_LDouble_Abs vs. fabsl                                        *
 *          start:   -1.0000000000000000e+06                                  *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 1305052789                                               *
 *          dx:      1.5325050579237527e-03                                   *
 *          libtmpl: 10.063154 seconds                                        *
 *          C:       11.074599 seconds                                        *
 *          max abs error: 0.0000000000000000e+00                             *
 *          max rel error: 0.0000000000000000e+00                             *
 *          rms abs error: 0.0000000000000000e+00                             *
 *          rms rel error: 0.0000000000000000e+00                             *
 *                                                                            *
 *          Using if-then method:                                             *
 *                                                                            *
 *          tmpl_LDouble_Abs vs. fabsl                                        *
 *          start:   -1.0000000000000000e+06                                  *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 1305052789                                               *
 *          dx:      1.5325050579237527e-03                                   *
 *          libtmpl: 11.209910 seconds                                        *
 *          C:       11.037735 seconds                                        *
 *          max abs error: 0.0000000000000000e+00                             *
 *          max rel error: 0.0000000000000000e+00                             *
 *          rms abs error: 0.0000000000000000e+00                             *
 *          rms rel error: 0.0000000000000000e+00                             *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MIN:  2200.0000 MHz                                               *
 *          MAX:  4672.0698 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 *  2.) math.h:                                                               *
 *          Only included if libtmpl algorithms have not been requested. This *
 *          file contains the fabs function.                                  *
 ******************************************************************************
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                             A FRIENDLY WARNING                             *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/08: Ryan Maguire                                                  *
 *      Frozen for v1.3 of librssringoccs.                                    *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied file from rss_ringoccs.                                        *
 *  2021/02/24: Ryan Maguire                                                  *
 *      Added IEEE 754 code for computing the absolute value function.        *
 *  2021/09/10: Ryan Maguire                                                  *
 *      Moved float and long double to their own files.                       *
 *  2022/03/01: Ryan Maguire                                                  *
 *      Added check for TMPL_USE_MATH_ALGORITHMS macro. This function will    *
 *      use fabs from math.h if TMPL_USE_MATH_ALGORITHMS is not 1.            *
 ******************************************************************************/

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 long double support.                                   */
#if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
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

    /*  Return the long double part of the union.                             */
    return w.r;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#else
/*  For #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1*
 *  Lacking IEEE-754 support, an if-then statement works and is portable.     */

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0L)
        return x;
    else
        return -x;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1*/

#else
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */

/*  math.h provides the fabsl function in C99 and higher.                     */
#include <math.h>

/*  C99 and higher have fabsl defined. C89 compilers may not. Microsoft has   *
 *  fabsl but does not define the __STDC_VERSION__ macro by default.          */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || \
    (defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    return fabsl(x);
}
/*  End of tmpl_LDouble_Abs.                                                  */

#else
/*  C89 implementations are not required to provide fabsl.                    */

/*  Long double precision absolute value function (fabsl equivalent).         */
long double tmpl_LDouble_Abs(long double x)
{
    double abs_x = fabs((double)x);
    return (long double)abs_x;
}
/*  End of tmpl_LDouble_Abs.                                                  */

#endif
/*  #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L              */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */
