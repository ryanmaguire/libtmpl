/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. sqrt from math.h otherwise.                           *
 *  Method:                                                                   *
 *      Use a combination of square root rules, Taylor series, and Newton's   *
 *      method. That is, sqrt(x) is computed as follows:                      *
 *                                                                            *
 *          If x < 0, return Not-A-Number.                                    *
 *          If x = +/- NaN, +Inf, or +/- 0, return x.                         *
 *          If x is subnormal (denormal), normalize by 2^52.                  *
 *                                                                            *
 *          sqrt(x) = sqrt(1.m * 2^b)                                         *
 *                  = sqrt(1.m) * sqrt(2^b)                                   *
 *                  = sqrt(1.m) * 2^{b/2}                                     *
 *                  = sqrt(u) * 2^{b/2}     with u = 1.m                      *
 *                  = sqrt(ut/t) * 2^{b/2}  with t = 1 + k/128 for some k.    *
 *                  = sqrt(u/t) * sqrt(t) * 2^{b/2}                           *
 *                                                                            *
 *      Choose t = 1 + k/128 by choosing k to be the largest integer such     *
 *      that 1 + k/128 <= u. Precompute sqrt(t) and 1/t in a table. The       *
 *      value u/t is now between 1 and 1 + 1/128. Compute sqrt(u/t) by:       *
 *                                                                            *
 *                                                                            *
 *          y = sqrt(u/t)                                                     *
 *            = sqrt(1 + s)             with s = u/t - 1.                     *
 *            ~ 1 + 0.5x - 0.125x^2                                           *
 *                                                                            *
 *      y is now accurate to at least 8 decimals. We can double this to at    *
 *      least 16 decimals using 1 iteration of Newton's method. We have:      *
 *                                                                            *
 *                y ~ sqrt(x)                                                 *
 *          y^2 - x ~ 0                                                       *
 *             f(y) = y^2 - x                                                 *
 *            f'(y) = 2y                                                      *
 *                                                                            *
 *      Apply Newton's method for 1 iteration:                                *
 *                                                                            *
 *              out = y - f(y)/f'(y)                                          *
 *                  = y - (y^{2} - x)/(2y)                                    *
 *                  = (2y^{2} - y^{2} + x)/(2y)                               *
 *                  = (y^{2} + x)/(2y)                                        *
 *                  = 0.5*(y + x/y)                                           *
 *                                                                            *
 *      Lastly, since 2^{b/2} is not an integer for odd valued b, use the     *
 *      fact that for odd b we have b = 2k+1, so b/2 = k+1/2, and thus:       *
 *                                                                            *
 *          2^{b/2} = 2^{k + 1/2}                                             *
 *                  = 2^{k} * 2^{1/2}                                         *
 *                  = sqrt(2) * 2^{k}                                         *
 *                                                                            *
 *      Precompute sqrt(2) and multiply the result by this if b is odd.       *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of doubles with 0.0). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *      sqrt is usually implemented in hardware, and the built-in square root *
 *      function is much faster than anything done in software. Comparing     *
 *      this routine againt the __builtin_sqrt from glibc on x86_64, we find: *
 *                                                                            *
 *          tmpl_Double_Sqrt vs. sqrt                                         *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+04                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231732353846026e-06                                   *
 *          libtmpl: 13.819011 seconds                                        *
 *          C:       8.283464 seconds                                         *
 *          max abs error: 1.4210854715202004e-14                             *
 *          max rel error: 2.2204460464058961e-16                             *
 *          rms abs error: 5.8261746077544000e-15                             *
 *          rms rel error: 8.2703094539573963e-17                             *
 *                                                                            *
 *      The rms and max relative errors are below DBL_EPSILON but the time is *
 *      much worse (about 66% worse). It may be fairer to compare this        *
 *      function against another implementation in software. The openlibm     *
 *      implementation uses a bit-by-bit algorithm to ensure the value is     *
 *      accurate to all 52 bits in a double, and correctly rounded. This      *
 *      is a lot slower, as the test below reveals.                           *
 *                                                                            *
 *          tmpl_Double_Sqrt vs. sqrt                                         *
 *          start:    1.0000000000000000e-04                                  *
 *          end:      1.0000000000000000e+04                                  *
 *          samples:  2615628245                                              *
 *          dx:       3.8231732353846026e-06                                  *
 *          libtmpl:  13.816768 seconds                                       *
 *          openlibm: 420.931444 seconds                                      *
 *          max abs error: 5.6843418860808015e-14                             *
 *          max rel error: 6.6359741442268620e-16                             *
 *          rms abs error: 6.7487215520428957e-15                             *
 *          rms rel error: 9.4046566544817157e-17                             *
 *                                                                            *
 *      So, there's a bit of a trade off. The algorithm is not accurate to    *
 *      all bits, but it is 30x faster. Note, openlibm also implements        *
 *      sqrt in hardware, the bit-by-bit method is only used if a built-in    *
 *      square root function is not available.                                *
 *                                                                            *
 *      The value 2615628245 was chosen since 3 double arrays of that size    *
 *      take up 62 GB of memory, and there was 64 GB available.               *
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
 *      The glibc tests were ran using the following options:                 *
 *                                                                            *
 *          gcc -O3 -flto tmpl_sqrt_double_huge_time_test.c -o test -lm -ltmpl*
 *                                                                            *
 *      -O3 is optimization level, and -flto is link-time optimization.       *
 *      tmpl_sqrt_double_huge_time_test.c can be found in                     *
 *          libtmpl/tests/math_tests/time_tests/                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support. This is significantly faster.                 */
#if TMPL_HAS_IEEE754_DOUBLE == 1

#include <libtmpl/include/math/tmpl_sqrt_table_double.h>
#include <libtmpl/include/math/tmpl_sqrt_remez_double.h>

static const double tmpl_double_sqrt_data[2] = {
    1.0, 1.4142135623730950488016887242097
};

/*  Function for computing square roots at double precision.                  */
double tmpl_Double_Sqrt(double x)
{
    /*  Union of a double and the bits representing a double.                 */
    tmpl_IEEE754_Double w;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the output.                                      */
    unsigned int exponent;

    /*  Variable for storing the exponent mod 2.                              */
    unsigned int parity;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (w.bits.sign)
        return TMPL_NAN;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0)
            return x;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^52,      *
         *  which is 4.503599627370496 x 10^15.                               */
        w.r *= TMPL_DOUBLE_NORMALIZE;

        /*  Compute the exponent. Since we normalized by a power of two we    *
         *  need to subtract this from the value. To compute the correctly    *
         *  rounded exponent after division by 2, subtract 1 more before      *
         *  dividing. The total is 53. Finally, shift by the bias.            */
        exponent = TMPL_DOUBLE_UBIAS - ((TMPL_DOUBLE_UBIAS-w.bits.expo)+53U)/2U;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    else if (TMPL_DOUBLE_IS_NAN_OR_INF(w))
        return x;

    /*  Normal number. Compute the exponent. This is the exponent of the      *
     *  original number divided by 2 since we are taking the square root. A   *
     *  little care is needed to account for the bias. The exponent is        *
     *                                                                        *
     *      e = E - B                                                         *
     *                                                                        *
     *  where B is the bias and E is the number stored in w.bits.expo. We     *
     *  want to solve for the exponent of the new number. We want:            *
     *                                                                        *
     *      e / 2 = E' - B = (E - B) / 2                                      *
     *                                                                        *
     *  where E' is the resulting number stored in the expo bits of the       *
     *  output. We compute:                                                   *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *                                                                        *
     *  The bias for 64-bit double is 1023, which is not even. However, 1024  *
     *  is, so we write:                                                      *
     *                                                                        *
     *      E' = (E + B) / 2                                                  *
     *         = ((E - 1) + (B + 1)) / 2                                      *
     *         = ((E - 1) + 1024) / 2                                         *
     *         = (E - 1) / 2 + 512                                            *
     *                                                                        *
     *  Note that we've already checked that E != 0, so E - 1 will not        *
     *  wrap around. That is, E - 1 >= 0. The number 512 is 0x200 in hex.     */
    else
        exponent = ((w.bits.expo - 1U) >> 1U) + 0x200U;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = (w.bits.expo + 1U) & 1U;
    w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  power series in the variable 1 + (u/t - 1).                           *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat the abcdefg as an integer in binary, this is the number k *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = w.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    w.r = w.r*tmpl_double_rcpr_table[ind];

    /*  Compute the Remez minimax approximation for sqrt. Peak error 10^-9.   */
    w.r = tmpl_Double_Sqrt_Remez(w.r);

    /*  Get the correctly rounded down integer exponent/2.                    */
    w.bits.expo = exponent & 0x7FFU;

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    w.r *= tmpl_double_sqrt_data[parity]*tmpl_double_sqrt_table[ind];

    /*  Apply 1 iteration of Newton's method and return.                      */
    return 0.5*(w.r + x/w.r);
}
/*  End of tmpl_Double_Sqrt.                                                  */

#else
/*  Else for TMPL_HAS_IEEE754_DOUBLE.                                         */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */

#endif
/*  End of #if for TMPL_USE_MATH_ALGORITHMS.                                  */
