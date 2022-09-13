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
 *                              tmpl_abs_double                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |x| at double precision.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Abs                                                       *
 *  Purpose:                                                                  *
 *      Computes the absolute value of a real number.                         *
 *                   --                                                       *
 *                  |   x,  x >= 0                                            *
 *          |x|  =  |  -x,  else                                              *
 *                   --                                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for |x|.                              *
 *  Output:                                                                   *
 *      abs_x (double):                                                       *
 *          The absolute value of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, set the sign bit of the             *
 *      input to 0. A 64-bit double is represented by:                        *
 *                                                                            *
 *        s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  *
 *        - ----------- ----------------------------------------------------  *
 *      sign exponent                mantissa                                 *
 *                                                                            *
 *      The absolute value can be computed by setting s to 0. Note, this      *
 *      method will work for NaN and inf, and the output will be              *
 *      "positive" NaN and positive infinity, respectively.                   *
 *      If IEEE-754 is not supported, an if-then statement to check if the    *
 *      input is positive, returning x for non-negative and -x otherwise.     *
 *  Notes:                                                                    *
 *      If IEEE-754 is not supported and if the input is NaN one may get      *
 *      +/- NaN (which is still NaN). This is because NaN always              *
 *      evaluates to false when a comparison is made (==, <, >, etc.).        *
 *                                                                            *
 *      Benchmarks can be found at the end of this file.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
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
 *  2022/05/05: Ryan Maguire                                                  *
 *      Adding inline support. This is about 2x faster. It is now the default *
 *      configuration in the Makefile.                                        *
 *  2022/05/31: Ryan Maguire                                                  *
 *      Added benchmarks.                                                     *
 *  2022/09/13: Ryan Maguire                                                  *
 *      Remove math.h version (fabs alias). This version is now a macro for   *
 *      the fabs function in tmpl_math.h (only if TMPL_USE_MATH_ALGORITHMS is *
 *      set to zero).                                                         *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support.                                               */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision absolute value function (fabs equivalent).               */
double tmpl_Double_Abs(double x)
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
/*  Else #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1 *
 *  Lacking IEEE-754 support, an if-then statement works and is is portable.  */

/*  Double precision absolute value function (fabs equivalent).               */
double tmpl_Double_Abs(double x)
{
    /*  If x is positive return it, otherwise return its negative.            */
    if (x >= 0.0)
        return x;
    else
        return -x;
}
/*  End of tmpl_Double_Abs.                                                   */

#endif
/* End of #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1*/

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1    */

#endif
/*  End of #if !defined(TMPL_USE_INLINE) || TMPL_USE_INLINE != 1.             */

/******************************************************************************
 *                                 BENCHMARKS                                 *
 ******************************************************************************
 *  Test Parameters:                                                          *
 *      tmpl_Double_Abs vs. fabs                                              *
 *      start:   -1.0000000000000000e+06                                      *
 *      end:      1.0000000000000000e+06                                      *
 *      samples:  2248155955                                                  *
 *      dx:       8.8961799805387608e-04                                      *
 *  Test Results:                                                             *
 *      max abs error: 0.0000000000000000e+00                                 *
 *      max rel error: 0.0000000000000000e+00                                 *
 *      rms abs error: 0.0000000000000000e+00                                 *
 *      rms rel error: 0.0000000000000000e+00                                 *
 ******************************************************************************
 *  Specs:                                                                    *
 *      CPU:  AMD Ryzen 9 3900X 12-Core Processor                             *
 *      MIN:  2200.0000 MHz                                                   *
 *      MAX:  4672.0698 MHz                                                   *
 *      RAM:  Ripjaw DDR4-3600 16GBx4                                         *
 *      MB:   Gigabyte Aorus x570 Elite WiFi                                  *
 *      ARCH: x86_64                                                          *
 *      OS:   Debian 11 (Bullseye) GNU/LINUX                                  *
 *  Compilers:                                                                *
 *      Debian clang version 11.0.1-2                                         *
 *      gcc (Debian 10.2.1-6) 10.2.1 20210110                                 *
 *      tcc version 0.9.27 (x86_64 Linux)                                     *
 *      Portable C Compiler 1.2.0.DEVEL 20200630 for x86_64-pc-linux-gnu      *
 ******************************************************************************
 *  IEEE-754 method             not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  4.963484 seconds | 2.506179 seconds           *
 *      clang:                  2.536102 seconds | 2.525563 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (gcc build):    5.422638 seconds | 2.726815 seconds           *
 *      gcc:                    2.632450 seconds | 2.625470 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (pcc build):    15.24091 seconds | 15.50274 seconds           *
 *      pcc:                     5.02499 seconds |  5.46952 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (tcc build):    17.28096 seconds | 16.79033 seconds           *
 *      tcc:                     7.19646 seconds |  6.95061 seconds           *
 *  ------------------------------------------------------------------------  *
 *  If-Then method              not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  4.990012 seconds | 2.688390 seconds           *
 *      clang:                  2.526875 seconds | 2.531980 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (gcc build):    5.378256 seconds | 2.733715 seconds           *
 *      gcc:                    2.659658 seconds | 2.642936 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (pcc build):    5.708692 seconds | 3.214009 seconds           *
 *      pcc:                    5.009721 seconds | 5.510774 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (tcc build):    8.084143 seconds | 7.593651 seconds           *
 *      tcc:                    7.203836 seconds | 7.081540 seconds           *
 *  ------------------------------------------------------------------------  *
 ******************************************************************************
 *  Test Parameters:                                                          *
 *      tmpl_Double_Abs vs. fabs                                              *
 *      start:   -1.0000000000000000e+06                                      *
 *      end:      1.0000000000000000e+06                                      *
 *      samples:  572882306                                                   *
 *      dx:       3.4911184706758946e-03                                      *
 *  Test Results:                                                             *
 *      max abs error: 0.0000000000000000e+00                                 *
 *      max rel error: 0.0000000000000000e+00                                 *
 *      rms abs error: 0.0000000000000000e+00                                 *
 *      rms rel error: 0.0000000000000000e+00                                 *
 ******************************************************************************
 *  Specs:                                                                    *
 *      Apple MacBook Air, 2020                                               *
 *      CPU:  Apple M1                                                        *
 *      RAM:  LPDDR4, 16GB                                                    *
 *      ARCH: arm64                                                           *
 *      OS:   macOS Monterey, 12.3                                            *
 *  Compilers:                                                                *
 *      Apple clang version 12.0.5 (clang-1205.0.22.9)                        *
 ******************************************************************************
 *  IEEE-754 method             not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  1.034541 seconds | 0.433286 seconds           *
 *      clang:                  0.537182 seconds | 0.595746 seconds           *
 *  ------------------------------------------------------------------------  *
 *  If-Then method              not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  1.034140 seconds | 0.437655 seconds           *
 *      clang:                  0.522405 seconds | 0.509519 seconds           *
 *  ------------------------------------------------------------------------  *
 ******************************************************************************
 *  Test Parameters:                                                          *
 *      tmpl_Double_Abs vs. fabs                                              *
 *      start:   -1.0000000000000000e+06                                      *
 *      end:      1.0000000000000000e+06                                      *
 *      samples:  572882306                                                   *
 *      dx:       3.4911184706758946e-03                                      *
 *  Test Results:                                                             *
 *      max abs error: 0.0000000000000000e+00                                 *
 *      max rel error: 0.0000000000000000e+00                                 *
 *      rms abs error: 0.0000000000000000e+00                                 *
 *      rms rel error: 0.0000000000000000e+00                                 *
 ******************************************************************************
 *  Specs:                                                                    *
 *      Apple MacBook Pro Retina, 2015                                        *
 *      CPU:  2.2 GHz Quad-Core Intel Core i7                                 *
 *      RAM:  16GB 1600MHz DDR3                                               *
 *      ARCH: x86_64                                                          *
 *      OS:   macOS Big Sur, 11.6.5                                           *
 *  Compilers:                                                                *
 *      Apple clang version 13.0.0 (clang-1300.0.29.30)                       *
 ******************************************************************************
 *  IEEE-754 method             not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  2.960274 seconds | 2.076615 seconds           *
 *      clang:                  2.307846 seconds | 2.516832 seconds           *
 *  ------------------------------------------------------------------------  *
 *  If-Then method              not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  3.086965 seconds | 2.225832 seconds           *
 *      clang:                  2.119420 seconds | 2.125722 seconds           *
 *  ------------------------------------------------------------------------  *
 ******************************************************************************
 *  Test Parameters:                                                          *
 *      tmpl_Double_Abs vs. fabs                                              *
 *      start:   -1.0000000000000000e+06                                      *
 *      end:      1.0000000000000000e+06                                      *
 *      samples:  1146459067                                                  *
 *      dx:       1.7445018819847670e-03                                      *
 *  Test Results:                                                             *
 *      max abs error: 0.0000000000000000e+00                                 *
 *      max rel error: 0.0000000000000000e+00                                 *
 *      rms abs error: 0.0000000000000000e+00                                 *
 *      rms rel error: 0.0000000000000000e+00                                 *
 ******************************************************************************
 *  Specs:                                                                    *
 *      CPU:  AMD Ryzen 9 3900X 12-Core Processor                             *
 *      MIN:  2200.0000 MHz                                                   *
 *      MAX:  4672.0698 MHz                                                   *
 *      RAM:  Ripjaw DDR4-3600 16GBx2                                         *
 *      MB:   Gigabyte Aorus x570 Elite WiFi                                  *
 *      ARCH: x86_64                                                          *
 *      OS:   Windows 10 (GNOME Boxes Virtual Machine)                        *
 *  Compilers:                                                                *
 *      Microsoft (R) C/C++ Optimizing Compiler Version 19.32.31329 for x64   *
 *      clang version 13.0.1 x86_64-pc-windows-msvc                           *
 ******************************************************************************
 *  IEEE-754 method             not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (MSVC build):   3.120000 seconds | 7.963000 seconds           *
 *      MSVC:                   2.536000 seconds | 2.461000 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  3.349000 seconds | 1.995000 seconds           *
 *      clang:                  2.764000 seconds | 3.132000 seconds           *
 *  ------------------------------------------------------------------------  *
 *  If-Then method              not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (MSVC build):   3.283000 seconds | 2.253000 seconds           *
 *      MSVC:                   3.040000 seconds | 2.911000 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  2.404000 seconds | 2.266000 seconds           *
 *      clang:                  3.020000 seconds | 3.331000 seconds           *
 *  ------------------------------------------------------------------------  *
 ******************************************************************************
 *  Test Parameters:                                                          *
 *      tmpl_Double_Abs vs. fabs                                              *
 *      start:   -1.0000000000000000e+06                                      *
 *      end:      1.0000000000000000e+06                                      *
 *      samples:  1145026150                                                  *
 *      dx:       1.7466849992901908e-03                                      *
 *  Test Results:                                                             *
 *      max abs error: 0.0000000000000000e+00                                 *
 *      max rel error: 0.0000000000000000e+00                                 *
 *      rms abs error: 0.0000000000000000e+00                                 *
 *      rms rel error: 0.0000000000000000e+00                                 *
 ******************************************************************************
 *  Specs:                                                                    *
 *      CPU:  AMD Ryzen 9 3900X 12-Core Processor                             *
 *      MIN:  2200.0000 MHz                                                   *
 *      MAX:  4672.0698 MHz                                                   *
 *      RAM:  Ripjaw DDR4-3600 16GBx2                                         *
 *      MB:   Gigabyte Aorus x570 Elite WiFi                                  *
 *      ARCH: x86_64                                                          *
 *      OS:   FreeBSD 13.1 (GNOME Boxes Virtual Machine)                      *
 *  Compilers:                                                                *
 *      FreeBSD clang version 13.0.0                                          *
 *      gcc FreeBSD Ports Collection 10.3.0                                   *
 ******************************************************************************
 *  IEEE-754 method             not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  3.531250 seconds | 2.007812 seconds           *
 *      clang:                  2.015625 seconds | 2.046875 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (gcc build):    3.718750 seconds | 2.234375 seconds           *
 *      gcc:                    2.023438 seconds | 2.007812 seconds           *
 *  ------------------------------------------------------------------------  *
 *  If-Then method              not inlined      | inlined                    *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (clang build):  3.757812 seconds | 2.281250 seconds           *
 *      clang:                  2.031260 seconds | 2.046875 seconds           *
 *  ------------------------------------------------------------------------  *
 *      libtmpl (gcc build):    3.914620 seconds | 2.156250 seconds           *
 *      gcc:                    2.078125 seconds | 2.085938 seconds           *
 *  ------------------------------------------------------------------------  *
 ******************************************************************************/
