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
 *                               tmpl_config                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide macros describing how to build libtmpl.                       *
 *  NOTES:                                                                    *
 *      This file was originally in rss_ringoccs but has been moved here.     *
 *      rss_ringoccs is also released under GPL 3.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       February 2, 2021                                              *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/12/2 (Ryan Maguire):                                                 *
 *      Created file.                                                         *
 *  2021/02/02 (Ryan Maguire):                                                *
 *      Copied from rss_ringoccs.                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef __TMPL_CONFIG_H__
#define __TMPL_CONFIG_H__

/******************************************************************************
 *  rss_ringoccs allowed the user to build the complex library in one of two  *
 *  ways: Using rss_ringoccs, or using C99 complex.h (if available). No time  *
 *  difference was found after testing across various systems running         *
 *  macOS (Mojave and Catalina) and GNU/Linux (Debian 10 Buster, Ubuntu 20.04,*
 *  and ElementaryOS 5). Because of this, libtmpl does NOT provide the C99    *
 *  routines and only provides the C89/C90 compatible library. Of course, the *
 *  library IS FORWARD COMPATIBILE and has been tested on C99 and C11         *
 *  compilers (LLVM's clang and GNU's gcc). The complex data type defined by  *
 *  libtmpl copies the method in GNU's Scientific Library (GSL) which is a    *
 *  struct consisting of a double array with two elements. Similar types are  *
 *  defined for float and long double precision. You can mix libtmpl code with*
 *  with C99 code with a simple union:                                        *
 *                                                                            *
 *      typedef union my_complex {                                            *
 *          complex double     c99_complex;                                   *
 *          tmpl_ComplexDouble tmpl_complex;                                  *
 *      } my_complex;                                                         *
 *                                                                            *
 *  You can then pass a variable my_complex z; to a C99 function by:          *
 *      complex double w = ccos(z.c99_complex);                               *
 *  And you can pass it to a libtmpl function by:                             *
 *      tmpl_ComplexDouble w = tmpl_CDouble_Cos(z.tmpl_complex);              *
 ******************************************************************************/

/*  The following comment block was originally part of rss_ringoccs and has   *
 *  been included here for completeness of documentation. The times mentioned *
 *  did not use linking optimization. With this, the times are identical.     *
 *  Without linking optimization, the times are still similar.                */

/*  C99 requires complex.h, but C11 makes it optional. If you have C99        *
 *  support and would like to use built-in complex numbers, change the setup  *
 *  script config_librssringoccs.sh. See that file for details.               *
 *  When tested against something simple like the complex exponential         *
 *  function, the cexp provided by glibc (GNU C library) for complex.h is     *
 *  slightly faster than rss_ringoccs. This was tested on an array of one     *
 *  million points in the complex plane, the times are as follows:            *
 *  (iMac 2017 running MacOS)                                                 *
 *      C89 Time: 0.026958                                                    *
 *      C99 Time: 0.022602                                                    *
 *  This is not to say one can't achieve better times with C89 compliant code.*
 *  rss_ringoccs uses simple, but effective algorithms, not necessary the     *
 *  fastest. Still, ~0.027 seconds for a very large array isn't bad. The code *
 *  was compiled using gcc 10 with -O3 optimization. For 10 million points    *
 *  the times were:                                                           *
 *      C89 Time: 0.267769                                                    *
 *      C99 Time: 0.231087                                                    *
 *  Which seems linear.                                                       */

/*  There are subtle differences between the C89/C90 and C99 math.h header    *
 *  files. The C99 math.h is a superset of the C89 one. libtmpl provides      *
 *  supports C99 math.h, then setting this macro to 1 will make libtmpl alias *
 *  the functions that are missing in tmpl_math.h. If you have a compiler that*
 *  those functions rather than providing new algorithms. By default we do not*
 *  assume C99 compliance.                                                    */
#define __TMPL_USING_C99_MATH_H__ 0

/*  For compilers supporting IEEE754 floating point arithmetic, there is a    *
 *  fast and simple method of computing logarithms and square roots. These    *
 *  functions are provided by libtmpl for two reason. The first is learning,  *
 *  the algorithms help one understand how IEEE754 works. Second is because   *
 *  some compilers offer single/long double precision, but do not provide     *
 *  functions that actually compute to the correct accuracy. For example, log *
 *  and logl, defined in the C99 standard of math.h, may have the same        *
 *  precision. The log algorithms provided are as fast as those provided in   *
 *  C standard, tested on Linux and macOS systems, and have the correct       *
 *  precisions for the various data types.                                    */
#define __TMPL_USE_LOG_ALGORITHM__ 0

/*  If long double precision (80, 96, or 128 bit format, 24 decimal accuracy) *
 *  is needed for calculations but your platform lacks sinl or is strictly    *
 *  C89 compliant, libtmpl provides simple yet accurate code for              *
 *  computing the various trig functions. When tested against sinl on a       *
 *  massive array of 10^8 points evenly distributed throughout -10 to 10 we   *
 *  get the following times (in seconds):                                     *
 *      C99:     4.586321                                                     *
 *      libtmpl: 5.659821                                                     *
 *  Both outputs had long double precision and the maximum absolute           *
 *  difference was ~ 10^-16. By default we assume you want the standard       *
 *  library functions. If you do not have sinl, libtmpl creates a sinl        *
 *  function via:                                                             *
 *      sinl(x) = (long double)sin((double)x)                                 *
 *  That is, we simply cast the input and use the standard sin function. This *
 *  will lose precision, but is faster. If you would like to implement our    *
 *  algorithms, set __TMPL_USE_TRIG_ALGORITHMS__ to 1. The algorithms use     *
 *  lookup tables in combination with Taylor series and a few trig            *
 *  identities. sin(x) is computed as follows:                                *
 *                                                                            *
 *      sin(x) = sin(y + 2pi k)                                               *
 *             = sin(y)                                                       *
 *             = sin(y' + dy)                                                 *
 *             = sin(y')cos(dy) + cos(y')sin(dy)                              *
 *                                                                            *
 *  So we get x into the range [-pi, pi] and write y = y'+dy where            *
 *  y' = 0.01*floor(100*y) and dy = y-y'. So the y' take on a small amount of *
 *  possible values and cos(y') and sin(y') are computed via lookup tables.   *
 *  dy is small and can be accurately computed via a Taylor series using very *
 *  few terms. Cosine is defined similarly.                                   */
#define __TMPL_USE_TRIG_ALGORITHMS__ 0

#endif
/*  End of include guard.                                                     */

