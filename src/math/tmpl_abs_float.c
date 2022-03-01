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
 *                             tmpl_abs_float                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at single precision.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Abs                                                        *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (float/double/long double):                                     *
 *          The absolute value of x.                                          *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and/or libtmpl algorithms have  *
 *      been requested. fabsf from math.h if available. fabs otherwise.       *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, set the sign bit of the             *
 *      input to 0. A 32-bit float is represented by:                         *
 *                                                                            *
 *          s   eeeeeeee    xxxxxxxxxxxxxxxxxxxxxxx                           *
 *          -   --------    -----------------------                           *
 *        sign  exponent           mantissa                                   *
 *                                                                            *
 *      The absolute value can be computed by setting s to 0. Note, this      *
 *      method will work for NaN and inf, and the output will be              *
 *      "positive" NaN and positive infinity, respectively.                   *
 *                                                                            *
 *      If Ieee-754 is not supported, a simple if-then statement to check if  *
 *      the input is positive or not, returning x for non-negative and -x     *
 *      otherwise.                                                            *
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
 *          tmpl_Float_Abs vs. fabsf                                          *
 *          start:   -1.0000000000000000e+06                                  *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 5220285568                                               *
 *          dx:      3.8312081596814096e-04                                   *
 *          libtmpl: 13.610260 seconds                                        *
 *          C:       10.325856 seconds                                        *
 *          max abs error: 0.0000000000000000e+00                             *
 *          max rel error: 0.0000000000000000e+00                             *
 *          rms abs error: 0.0000000000000000e+00                             *
 *          rms rel error: 0.0000000000000000e+00                             *
 *                                                                            *
 *          Using if-then method:                                             *
 *                                                                            *
 *          tmpl_Float_Abs vs. fabsf                                          *
 *          start:   -1.0000000000000000e+06                                  *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 5220285568                                               *
 *          dx:      3.8312081596814096e-04                                   *
 *          libtmpl: 14.481908 seconds                                        *
 *          C:       10.715710 seconds                                        *
 *          max abs error: 0.0000000000000000e+00                             *
 *          max rel error: 0.0000000000000000e+00                             *
 *          rms abs error: 0.0000000000000000e+00                             *
 *          rms rel error: 0.0000000000000000e+00                             *
 *                                                                            *
 *      fabsf is a built-in function, so I doubt software will be able to get *
 *      better performance.                                                   *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MAX:  4672.0698 MHz                                               *
 *          MIN:  2200.0000 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
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
 *                             Revision History                               *
 ******************************************************************************
 *  2020/11/01: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2020/12/08: Ryan Maguire                                                  *
 *      Frozen for v1.3 of librssringoccs.                                    *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied file from rss_ringoccs.                                        *
 *  2021/02/24: Ryan Maguire                                                  *
 *      Added IEEE 754 code for computing the absolute value function.        *
 *  2022/03/01: Ryan Maguire                                                  *
 *      Added check for TMPL_USE_MATH_ALGORITHMS macro. This function will    *
 *      simply use fabs from math.h if TMPL_USE_MATH_ALGORITHMS is not 1.     *
 ******************************************************************************/

/*  Header file where the prototypes for the function is defined.             */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  If your compiler supports the IEEE 754 format, we simply set the sign bit *
 *  to zero to compute the absolute value of the input.                       */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
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
/*  Else statement for #if TMPL_HAS_IEEE754_FLOAT == 1.                       */

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
{
    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0F)
        return x;
    else
        return -x;
}
/*  End of tmpl_Float_Abs.                                                    */

#endif
/*  End of #if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1.*/

#else
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */

/*  math.h provides the fabsf function in C99 and higher.                     */
#include <math.h>

/*  C99 and higher have fabsf defined. C89 compilers may not. Microsoft has   *
 *  fabsf but does not define the __STDC_VERSION__ macro by default.          */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || \
    (defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
{
    return fabsf(x);
}
/*  End of tmpl_Float_Abs.                                                    */

#else
/*  C89 implementations are not required to provide fabsf.                    */

/*  Single precision absolute value function (fabsf equivalent).              */
float tmpl_Float_Abs(float x)
{
    double abs_x = fabs((double)x);
    return (float)abs_x;
}
/*  End of tmpl_Float_Abs.                                                    */

#endif
/*  #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L              */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */
