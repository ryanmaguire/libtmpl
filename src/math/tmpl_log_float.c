/******************************************************************************
 *                                 LICENSE                                    *
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
 *                              tmpl_log_float                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at single precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Log                                                        *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (float):                                                        *
 *          The natural log of x at single precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. logf from math.h otherwise.                           *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, and if libtmpl algorithms have      *
 *      been requested, log(x) is computed as follows:                        *
 *                                                                            *
 *          Check if x < 0, return Not-A-Number if so.                        *
 *                                                                            *
 *          Check if x = 0.0, return -infinity if so.                         *
 *                                                                            *
 *          Check if x is a subnormal (all exponent bits set to zero) number, *
 *          normalize by 2^23 if so, and then pass to the main part of the    *
 *          algorithm.                                                        *
 *                                                                            *
 *          For values not in the range 0.99 < x < 1.0, compute log(x) as     *
 *          follows:                                                          *
 *                                                                            *
 *              log(x) = log(1.m * 2^b)                                       *
 *                     = log(1.m) + log(2^b)                                  *
 *                     = log(1.m) + b*log(2)                                  *
 *                     = log(u) + b*log(2)      with u = 1.m                  *
 *                     = log(ut/t) + b*log(2)   with t = 1 + k/128 for some k.*
 *                     = log(u/t) + log(t) + b*log(2)                         *
 *                                                                            *
 *          Precompute log(t) in a table. Precompute 1/t in a table so that   *
 *          u/t can be computed as u * (1/t). Also precompute log(2). The     *
 *          value k is chosen to be the largest value such that               *
 *          t = 1 + k/128 <= u. This value k can be obtained directly from    *
 *          the mantissa. By looking at the most significant 7 bits of the    *
 *          mantissa, the value k is simply these 7 bits read in binary.      *
 *                                                                            *
 *          The value s = u/t is such that 1 <= s < 1 + 1/128. Compute log(s) *
 *          via the following sum:                                            *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(s) =  \      2     2n+1                                   *
 *                        /    ------ A             A = (s - 1) / (s + 1)     *
 *                        ---- 2n + 1                                         *
 *                        n = 0                                               *
 *                                                                            *
 *          For single precision, only the first term is needed. The          *
 *          standard Taylor series for ln(1 + x) with x small has             *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values slightly less than 1, the computation of (s-1) / (s+1) *
 *          leads to large relative error (about ~10^-3) since log(1) = 0     *
 *          (the absolute error is still around 10^-8). We can achieve much   *
 *          better relative error using the standard Taylor series to 4       *
 *          terms. This is slower than the series above, but more accurate in *
 *          this range. That is, for 0.99 < x < 1.0 we use:                   *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(x) =  \    -1   n                                         *
 *                        /    --- s             s = 1 - x                    *
 *                        ----  n                                             *
 *                        n = 1                                               *
 *                                                                            *
 *      If the user has not requested libtmpl algorithms, or if IEEE-754      *
 *      support is not available (highly unlikely), then #include <math.h>    *
 *      is called and tmpl_Float_Log returns logf(x) from math.h              *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of floats with 0.0F). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *      A time and accuracy test against glibc yields the following:          *
 *                                                                            *
 *          start:   9.9999997473787516e-05                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 5220285568                                               *
 *          libtmpl: 17.070764 seconds                                        *
 *          glibc:   15.557277 seconds                                        *
 *          max abs error: 9.5367431640625000e-07                             *
 *          max rel error: 8.5725469034514390e-06                             *
 *          rms abs error: 1.5724722349494647e-08                             *
 *          rms rel error: 2.3073108488104276e-09                             *
 *                                                                            *
 *      Not quite as fast, but the rms error is less the FLT_EPSILON. You     *
 *      win some, you lose some. The function handles denormal values well.   *
 *                                                                            *
 *          start:   1.4012984643248171e-45                                   *
 *          end:     1.1663469547068680e-38                                   *
 *          samples: 10000000                                                 *
 *          libtmpl: 0.051760 seconds                                         *
 *          glibc:   0.062876 seconds                                         *
 *          max abs error: 1.5258789062500000e-05                             *
 *          max rel error: 1.6292271709517081e-07                             *
 *          rms abs error: 4.1573249165892662e-06                             *
 *          rms rel error: 4.7154503634772946e-08                             *
 *                                                                            *
 *      For larger values, we have:                                           *
 *                                                                            *
 *          start:   1.0000000000000000e+02                                   *
 *          end:     1.0000000000000000e+08                                   *
 *          samples: 5220285568                                               *
 *          libtmpl: 17.439378 seconds                                        *
 *          glibc:   15.840557 seconds                                        *
 *          max abs error: 1.9073486328125000e-06                             *
 *          max rel error: 2.1024642649081215e-07                             *
 *          rms abs error: 3.8128065862738070e-08                             *
 *          rms rel error: 3.2184329775011985e-09                             *
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
 *      All tests were ran using the following options:                       *
 *                                                                            *
 *          gcc -O3 -flto tmpl_log_float_huge_time_test.c -o test -lm -ltmpl  *
 *                                                                            *
 *      -O3 is optimization level, and -flto is link-time optimization.       *
 *      tmpl_log_float_huge_time_test.c can be found in                       *
 *          libtmpl/tests/math_tests/time_tests/                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Float typedef and the         *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_FLOAT == 0 or if                *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_Float_Log is identical to the standard library logf function.*
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 4, 2022                                              *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1 && \
    defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Macros for 1/n for n = 2, 3, and 4. These make the code look cleaner.     */
#define ONE_HALF 0.5F
#define ONE_THIRD 0.3333333333333333333333333333F
#define ONE_FOURTH 0.25F

/*  Function for computing natural log at single precision.                   */
float tmpl_Float_Log(float x)
{
    /*  Declare all necessary variables.                                      */
    float s, A;

    /*  Variable for the exponent of the float x. x is written as             *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 8 bit       *
     *  unsigned exponent in a float.                                         */
    signed int exponent;

    /*  Variable for the union of a float and the bits representing it.       */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NANF;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0F)
            return -TMPL_INFINITYF;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^23,      *
         *  which is 8.388608 x 10^6.                                         */
        w.r *= 8.388608E6F;

        /*  Compute the exponent. Since we multiplied by 2^23, subtract 23    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_FLOAT_BIAS - 23;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    else if (w.bits.expo == 0xFFU)
        return x;

    /*  For values close to but less than 1, the computation of the division  *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-8 absolute error since log(1) = 0). To       *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.99F < w.r && w.r < 1.0F)
    {
        s = 1.0F - x;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
        return -s * (
            1.0F + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * ONE_FOURTH
                )
            )
        );
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_FLOAT_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_FLOAT_BIAS;

    /*  We compute log(x) via:                                                *
     *                                                                        *
     *      log(x) = log(1.m * 2^b)                                           *
     *             = log(1.m) + log(2^b)                                      *
     *             = log(1.m) + b*log(2)                                      *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. We precompute log(t) in a table *
     *  and then have:                                                        *
     *                                                                        *
     *      log(x) = log(u) + b*log(2)                                        *
     *             = log(ut/t) + b*log(2)                                     *
     *             = log(u/t) + log(t) + b*log(2)                             *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute log(u/t) via a   *
     *  power series in the variable (s - 1) / (s + 1) with s = u/t.          *
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
     *  array. man0 is 7 bits wide, so we just need this number.              */

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    s = w.r*tmpl_float_rcpr_table[w.bits.man0];

    /*  The Taylor series of log(1+x) for small x has very poor convergence.  *
     *  Using the alternating series test, the error is like 1/N where N is   *
     *  the number of terms in the series. log(x) has a different expansion:  *
     *                                                                        *
     *                inf                                                     *
     *                ----                                                    *
     *      log(x) =  \      2     2n+1                                       *
     *                /    ------ A             A = (x - 1) / (x + 1)         *
     *                ---- 2n + 1                                             *
     *                 n                                                      *
     *                                                                        *
     *  With x close to 1, q is close to zero, and the sum is in terms of the *
     *  square of q. This has great convergence.                              */
    A = 2.0F*(s - 1.0F) / (s + 1.0F);

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_F*(float)exponent + A +
        tmpl_float_log_table[w.bits.man0];
}
/*  End of tmpl_Float_Log.                                                    */

/*  undef all the macros in case someone wants to #include this file.         */
#undef ONE_HALF
#undef ONE_THIRD
#undef ONE_FOURTH

#else
/*  IEEE754 support not available, or libtmpl algorithms not requested.       */

/*  Standard library file containing log and logf.                            */
#include <math.h>

/*  C99 and higher have logf defined. C89 compilers may not.                  */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/*  Function for computing log at single precision.                           */
float tmpl_Float_Log(float x)
{
    return logf(x);
}
/*  End of tmpl_Float_Log.                                                    */

#else
/*  Else for #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.    */

/*  Function for computing log at single precision.                           */
float tmpl_Float_Log(float x)
{
    double logx = log((double)x);
    return (float)logx;
}
/*  End of tmpl_Float_Log.                                                    */

#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

#endif
/*  End of if for TMPL_HAS_IEEE754_FLOAT and TMPL_USE_MATH_ALGORITHMS.        */

