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
 *                          tmpl_complex_abs_double                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex modulus (absolute value).        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Abs:                                                     *
 *  Purpose:                                                                  *
 *      Computes the absolute value, or modulus, of a complex number:         *
 *                                                                            *
 *          |z| = |x + iy| = sqrt(x^2 + y^2)                                  *
 *                                                                            *
 *      Because x^2 and y^2 are computed as intermediate steps, this method   *
 *      will overflow for values greater than sqrt(DBL_MAX). The safe way to  *
 *      do this is via:                                                       *
 *                                                                            *
 *          |z| = |x| sqrt(1+(y/x)^2)                                         *
 *                                                                            *
 *      if |x| > |y|, and:                                                    *
 *                                                                            *
 *          |z| = |y| sqrt(1 + (x/y)^2)                                       *
 *                                                                            *
 *      otherwise. This is about 1.3-1.5x slower. If IEEE-754 support is      *
 *      available, we need only check of max(|x|, |y|) is in the range        *
 *      (2^-512, 2^512), scaling by a constant if not. This is about as fast  *
 *      as the naive method.                                                  *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *  Output:                                                                   *
 *      abs_z (double):                                                       *
 *          The absolute value of z.                                          *
 *  Called Functions:                                                         *
 *      tmpl_Double_Abs     (tmpl_math.h)                                     *
 *          Computes the absolute value of a real number.                     *
 *      tmpl_Double_Sqrt    (tmpl_math.h)                                     *
 *          Computes the square root of a float/double/long double.           *
 *      fabs                (math.h)                                          *
 *          Only if tmpl math algorithms are not requested. Computes the      *
 *          absolute values of a real number.                                 *
 *      sqrt                (math.h)                                          *
 *          Only if tmpl math algorithms are not requested. Computes the      *
 *          square root of a real number.                                     *
 *  Notes:                                                                    *
 *      This code is a fork of the code I wrote for rss_ringoccs.             *
 *      librssringoccs is also released under GPL3.                           *
 *                                                                            *
 *  Performance and Accuracy:                                                 *
 *      A time and accuracy test against glibc produced the following:        *
 *                                                                            *
 *          With IEEE-754 Support                                             *
 *                                                                            *
 *          tmpl_CDouble_Abs vs. cabs                                         *
 *          samples: 100000000                                                *
 *          libtmpl: 0.351518 seconds                                         *
 *          C:       1.515546 seconds                                         *
 *          max err: 2.220446e-16                                             *
 *          rel err: 4.237899e-17                                             *
 *                                                                            *
 *          Without IEEE-754 Support                                          *
 *                                                                            *
 *          tmpl_CDouble_Abs vs. cabs                                         *
 *          samples: 100000000                                                *
 *          libtmpl: 0.461252 seconds                                         *
 *          C:       1.537644 seconds                                         *
 *          max err: 4.440892e-16                                             *
 *          rel err: 8.648669e-17                                             *
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
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing basic math functions.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  3.) math.h:                                                               *
 *          Only if tmpl math algorithms are not requested. Contains fabs and *
 *          sqrt functions.                                                   *
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

/*  Where the prototypes are given and where complex types are defined.       */
#include <libtmpl/include/tmpl_complex.h>

/*  If the user has not requested tmpl algorithms, use functions from math.h. */
#if TMPL_USE_MATH_ALGORITHMS != 1
#include <math.h>

/*  Set macros for the square root and absolute value functions for later.    *
 *  this avoids more checks for TMPL_USE_MATH_ALGORITHMS in the code.         */
#define square_root sqrt
#define absolute_value fabs

#else
/*  Else for #if TMPL_USE_MATH_ALGORITHMS != 1                                */

/*  If the user requested tmpl algorithms, alias the appropriate functions.   */
#define square_root tmpl_Double_Sqrt
#define absolute_value tmpl_Double_Abs

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS != 1.                                 */

/*  We can get a significant speed boost if IEEE-754 support is available.    */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values 2^512 and 2^-512, to double precision, stored as macros.       */
#define BIG_SCALE 1.340780792994259709957402E+154
#define RCPR_BIG_SCALE 7.458340731200206743290965E-155

/*  Function for computing the magnitude, or modulus, of a complex number.    */
double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_IEEE754_Double w;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    double x = absolute_value(z.dat[0]);
    double y = absolute_value(z.dat[1]);

    /*  Compute the maximum of |x| and |y| and store it in the double         *
     *  part of the tmpl_IEEE754_Double union w. This syntax from the C       *
     *  language is a bit strange. a = (b < c ? c : b) says if b is less than *
     *  c, set a to c, otherwise set a to b.                                  */
    w.r = (x < y ? y : x);

    /*  We want to check if the exponent is less than 512, which is 0x200 in  *
     *  hexidecimal. The exponent of a double is offset by a bias. To check   *
     *  if the exponent is less than 512, check if the exponent part of the   *
     *  double is less than 512 plus the bias.                                */
    if (w.bits.expo < TMPL_DOUBLE_BIAS + 0x200U)
    {
        /*  If both exponents are greater than -512, then both |x| and        *
         *  |y| lie between 2^-512 and 2^512 meaning neither of the           *
         *  values x^2 or y^2 overflow or underflow. It is possible           *
         *  the maximum of |x| and |y| has exponent slightly greater than     *
         *  -512, but the other value has exponent slightly less. To ensure   *
         *  accuracy to 16 decimals, check if the exponent is greater than    *
         *  -502. If the difference in the exponents of |x| and |y| is        *
         *  greater than 10, then to at least 16 decimals we have             *
         *  |z| = max(|x|, |y|).                                              */
        if (w.bits.expo > 0x20AU)
            return square_root(x*x + y*y);

        /*  Both |x| and |y| are small. To avoid underflow scale by 2^512.    */
        x *= BIG_SCALE;
        y *= BIG_SCALE;

        /*  |z| can now be computed as 2^-512 * sqrt(x^2 + y^2)               *
         *  without the risk of underflow. Return this.                       */
        return RCPR_BIG_SCALE * square_root(x*x + y*y);
    }

    /*  Both |x| and |y| are large. To avoid overflow scale by 2^-512.        */
    x *= RCPR_BIG_SCALE;
    y *= RCPR_BIG_SCALE;

    /*  |z| can now be computed as |z| = 2^512 * sqrt(x^2 + y^2) without      *
     *  the risk of overflow. Return this.                                    */
    return BIG_SCALE * square_root(x*x + y*y);
}
/*  End of tmpl_CDouble_Abs.                                                  */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef BIG_SCALE
#undef RCPR_BIG_SCALE

#else
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1      */

/*  Lacking IEEE-754 support, we can use the standard trick to avoid          *
 *  underflows and overflows that is used in the hypot (hypotenuse) functions.*
 *  This is about 1.4x slower than the method above, but is portable. The     *
 *  reason for the slowness is above we multiply by constants, whereas this   *
 *  algorithm requires divisions and multiplications by non-constants.        */

/*  Function for computing the magnitude, or modulus, of a complex number.    */
double tmpl_CDouble_Abs(tmpl_ComplexDouble z)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    double rcpr_t;

    /*  Given z = x + iy = (x, y), compute |x| and |y|.                       */
    double x = absolute_value(z.dat[0]);
    double y = absolute_value(z.dat[1]);

    /*  Compute the maximum of |x| and |y|. This syntax from the C language   *
     *  is a bit strange. a = (b < c ? c : b) says if b is less than c, set a *
     *  to c, otherwise set a to b.                                           */
    const double t = (x < y ? y : x);

    /*  Division by zero is generally viewed as bad. If the max of |x| and    *
     *  |z| is zero, |z| = 0. Return this.                                    */
    if (t == 0.0)
        return 0.0;

    /*  Precompute 1/t to turn 2 divisions into 1 division and 2 products.    */
    rcpr_t = 1.0 / t;

    /*  Scale x and y by 1/t.                                                 */
    x *= rcpr_t;
    y *= rcpr_t;

    /*  |z| can safely be computed as |z| = t * sqrt((x/t)^2 + (y/t)^2)       *
     *  without risk of underflow or overflow.                                */
    return t * square_root(x*x + y*y);
}
/*  End of tmpl_CDouble_Abs.                                                  */

#endif
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1      */

/*  Undefine these macros in case someone wants to #include this file.        */
#undef square_root
#undef absolute_value
