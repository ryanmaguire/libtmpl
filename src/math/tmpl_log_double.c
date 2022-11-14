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
 *                             tmpl_log_double                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at double precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Log                                                       *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (double):                                                       *
 *          The natural log of x at double precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. log from math.h otherwise.                            *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, and if libtmpl algorithms have      *
 *      been requested, log(x) is computed as follows:                        *
 *                                                                            *
 *          Check if x < 0, return Not-A-Number if so.                        *
 *                                                                            *
 *          Check if x = 0.0, return -infinity if so.                         *
 *                                                                            *
 *          Check if x is a subnormal (all exponent bits set to zero) number, *
 *          normalize by 2^52 if so, and then pass to the main part of the    *
 *          algorithm.                                                        *
 *                                                                            *
 *          For values not in the range 0.95 < x < 1.05, compute log(x) as    *
 *          follows:                                                          *
 *                                                                            *
 *              log(x) = log(1.m * 2^b)                                       *
 *                     = log(1.m) + log(2^b)                                  *
 *                     = log(1.m) + b*log(2)                                  *
 *                     = log(u) + b*log(2)      with u = 1.m                  *
 *                     = log(ut/t) + b*log(2)   with t = 1 + k/64 for some k. *
 *                     = log(u/t) + log(t) + b*log(2)                         *
 *                                                                            *
 *          Precompute log(t) in a table. Precompute 1/t in a table so that   *
 *          u/t can be computed as u * (1/t). Also precompute log(2). The     *
 *          value k is chosen to be the largest value such that               *
 *          t = 1 + k/64 <= u. This value k can be obtained directly from the *
 *          mantissa. By looking at the most significant 6 bits of the        *
 *          mantissa, the value k is simply these 6 bits read in binary.      *
 *                                                                            *
 *          The value s = u/t is such that 1 <= s < 1 + 1/64. Compute log(s)  *
 *          via the following sum:                                            *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(s) =  \      2     2n+1                                   *
 *                        /    ------ A             A = (s - 1) / (s + 1)     *
 *                        ---- 2n + 1                                         *
 *                        n = 0                                               *
 *                                                                            *
 *          A polynomial with the first three terms is then used. The         *
 *          standard Taylor series polynomial for ln(1 + x) with x small has  *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values close to 1, the computation of (s-1) / (s+1) leads to  *
 *          large relative error (about ~10^-8) since log(1) = 0              *
 *          (the absolute error is still around 10^-16). We can achieve much  *
 *          better relative error using the standard Taylor series to ten     *
 *          terms. This is slower than the series above, but more accurate in *
 *          this range. That is, for 0.95 < x < 1.05 we use:                  *
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
 *      is called and tmpl_Double_Log returns log(x) from math.h              *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of doubles with 0.0). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test yields the following results versus glibc:   *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231732732340180e-04                                   *
 *          libtmpl: 12.287552 seconds                                        *
 *          C:       13.931813 seconds                                        *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.8218232061381792e-15                             *
 *          rms abs error: 9.0288083896098205e-16                             *
 *          rms rel error: 7.1724645066645684e-17                             *
 *                                                                            *
 *      The error values assume 100% accuracy in glibc. I believe the         *
 *      documentation states the actual error of glibc's log is less then     *
 *      1 ULP. The value 2615628245 was chosen since 3 double arrays of that  *
 *      size take up 62 GB of memory, and the test was performed with 64 GB   *
 *      available.                                                            *
 *                                                                            *
 *      I'm quite pleased with the result. Slightly faster and almost         *
 *      identical in accuracy. It should be noted the DBL_EPSILON for 64-bit  *
 *      double is 2.22044605e-16, and the rms relative error is below this    *
 *      value. If we look at larger values, we get:                           *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e+02                                   *
 *          end:     1.0000000000000000e+08                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231694504430619e-02                                   *
 *          libtmpl: 12.267691 seconds                                        *
 *          C:       12.621467 seconds                                        *
 *          max abs error: 7.1054273576010019e-15                             *
 *          max rel error: 4.2634953389345209e-16                             *
 *          rms abs error: 1.9900347824366729e-15                             *
 *          rms rel error: 1.1289387375111485e-16                             *
 *                                                                            *
 *      The function also handles subnormal (denormal) values well:           *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   4.9406564584124654e-324                                  *
 *          end:     2.2250738585072009e-308                                  *
 *          samples: 2615628245                                               *
 *          dx:      8.5068420527204166e-318                                  *
 *          libtmpl: 20.185706 seconds                                        *
 *          C:       24.695628 seconds                                        *
 *          max abs error: 2.2737367544323206e-13                             *
 *          max rel error: 3.2034265037806259e-16                             *
 *          rms abs error: 7.0236686512747269e-14                             *
 *          rms rel error: 9.8982393371947679e-17                             *
 *                                                                            *
 *      The worst error is in the region around 1.                            *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   9.0000000000000002e-01                                   *
 *          end:     1.1000000000000001e+00                                   *
 *          samples: 2615628245                                               *
 *          dx:      7.6463465472326738e-11                                   *
 *          libtmpl: 12.642206 seconds                                        *
 *          C:       12.995864 seconds                                        *
 *          max abs error: 4.8572257327350599e-16                             *
 *          max rel error: 9.2097825747585990e-15                             *
 *          rms abs error: 9.6042579543112006e-17                             *
 *          rms rel error: 1.6879917053984482e-15                             *
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
 *      Performance will of course vary on different systems. These tests     *
 *      had libtmpl built via clang. Building with GCC yields nearly          *
 *      identical times. Building libtmpl with TCC produced slower times:     *
 *                                                                            *
 *          libtmpl: 66.912582 seconds                                        *
 *          C:       13.422482 seconds                                        *
 *                                                                            *
 *      Building libtmpl with PCC had the following:                          *
 *                                                                            *
 *          libtmpl: 46.706748 seconds                                        *
 *          C:       13.351405 seconds                                        *
 *                                                                            *
 *      All tests were ran using the following options:                       *
 *                                                                            *
 *          gcc -O3 -flto tmpl_log_double_huge_time_test.c -o test -lm -ltmpl *
 *                                                                            *
 *      All tests can be found in libtmpl/tests/math_tests/time_tests/        *
 *                                                                            *
 *      Smaller tests were performed using a Windows 10 Virtual Machine. The  *
 *      results of libtmpl against Microsoft's C Library are as follows:      *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 50000000                                                 *
 *          libtmpl: 0.314 seconds                                            *
 *          C:       0.463 seconds                                            *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.9467566467383324e-15                             *
 *          rms abs error: 9.0989260892815339e-16                             *
 *          rms rel error: 1.0682607458165517e-16                             *
 *                                                                            *
 *      The errors are similar to those for glibc. The performance is about   *
 *      1.47x better. Similar values are found for denormal and large values. *
 *      GNOME Boxes was used for virtualization. libtmpl was built using      *
 *      clang for this test. Using MSVC yields:                               *
 *                                                                            *
 *          samples: 50000000                                                 *
 *          libtmpl: 0.974 seconds                                            *
 *          C:       0.409 seconds                                            *
 *                                                                            *
 *      Significantly worse.                                                  *
 *                                                                            *
 *      Finally, on a FreeBSD 12.2 Virtual Machine (via GNOME Boxes), we have *
 *      the following. Building libtmpl with FreeBSD's cc:                    *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 100000000                                                *
 *          libtmpl: 0.523438 seconds                                         *
 *          C:       0.820312 seconds                                         *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.8111997278351631e-15                             *
 *          rms abs error: 9.0941028467094906e-16                             *
 *          rms rel error: 1.0677265624885180e-16                             *
 *                                                                            *
 *      Building with clang-13 gives:                                         *
 *                                                                            *
 *          libtmpl: 0.492188 seconds                                         *
 *          C:       0.804688 seconds                                         *
 *                                                                            *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 4, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/11: Ryan Maguire                                                  *
 *      Added more terms for the polynomial in the region around 1. Changed   *
 *      this region of 0.95 < x < 1.05 instead of 0.995 < x < 1.0. Worst case *
 *      relative error is 9 x 10^-15. rms error is in this interval is        *
 *      1 x 10^-15. rms error for all positive real numbers is 1 x 10^-17,    *
 *      which is less than 1 ULP.                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested it.                             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Macros for 1/n for n = 2, 3, ..., 6, 7. These make the code look cleaner. */
#define A0 2.0
#define A1 0.666666666666666666666667
#define A2 0.4
#define A3 0.285714285714285714285714
#define A4 0.222222222222222222222222
#define A5 0.181818181818181818181818

/*  If IEEE-754 support is available, use this. It's much faster.             */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Function for computing natural log at double precision.                   */
double tmpl_Double_Log(double x)
{
    /*  Declare all necessary variables.                                      */
    double s, poly, A, A_sq;

    /*  Variable for the exponent of the double x. x is written as            *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 11 bit      *
     *  unsigned exponent in a double.                                        */
    signed int exponent;

    /*  Variable for the index of the arrays table and rcpr defined above     *
     *  which corresponds to the input x.                                     */
    unsigned int ind;

    /*  Variable for the union of a double and the bits representing it.      */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NAN;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0)
            return -TMPL_INFINITY;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^52,      *
         *  which is 4.503599627370496 x 10^15.                               */
        w.r *= 4.503599627370496E15;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS - 52;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    else if (w.bits.expo == 0x7FFU)
        return x;

    /*  For values in the region around 1, the computation of the division    *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-16 absolute error since log(1) = 0). To      *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.875 < w.r && w.r < 1.125)
    {
        A = (x - 1.0)/(x + 1.0);
        A_sq = A*A;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
        return A * (
            A0 + A_sq * (
                A1 + A_sq * (
                    A2 + A_sq * (
                        A3 + A_sq * (A4 + A_sq * A5)
                    )
                )
            )
        );
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  We compute log(x) via:                                                *
     *                                                                        *
     *      log(x) = log(1.m * 2^b)                                           *
     *             = log(1.m) + log(2^b)                                      *
     *             = log(1.m) + b*log(2)                                      *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/64 such that t <= u. We precompute log(t) in a table  *
     *  and then have:                                                        *
     *                                                                        *
     *      log(x) = log(u) + b*log(2)                                        *
     *             = log(ut/t) + b*log(2)                                     *
     *             = log(u/t) + log(t) + b*log(2)                             *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/64. We compute log(u/t) via a    *
     *  power series in the variable (s - 1) / (s + 1) with s = u/t.          *
     *                                                                        *
     *  We compute the value t = 1 + k/64 by computing k. The value k can be  *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625                       *
     *            |   |    |     |      |       |                             *
     *            V   V    V     V      V       V                             *
     *      u = 1.a   b    c     d      e       f       ....                  *
     *                                                                        *
     *  If we treat the abcdef as an integer in binary, this is the number k  *
     *  such that t = 1 + k/64. So we simply need to read off this value from *
     *  the mantissa. The value 1 / (1 + k/64) is stored in the rcpr array.   */
    ind = w.bits.man0;

    /*  man0 has the first 4 bits. The next 16 bits are in man1. We only need *
     *  the first two bits from man1. Obtain these by shifting down 14 bits   *
     *  via >> 14. We also need to shift the value of man0 up by 2^2, which   *
     *  is obtained by << 2. Altogether, this gives us the number abcdef in   *
     *  binary, as above, a is the first bit, ..., f is the sixth.            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    s = w.r*tmpl_double_rcpr_table[ind];

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
     *  With x close to 1, A is close to zero, and the sum is in terms of the *
     *  square of A. This has great convergence.                              */
    A = (s - 1.0) / (s + 1.0);
    A_sq = A*A;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    poly = A * (A0 + A_sq * (A1 + A_sq * A2));

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two*exponent + poly + tmpl_double_log_table[ind];
}
/*  End of tmpl_Double_Log.                                                   */

#else
/*  #if TMPL_HAS_IEEE754_DOUBLE == 1.                                         */

double tmpl_Double_Log(double x)
{
    double mantissa, poly, A, A_sq;
    signed int exponent;

    if (x < 0.0)
        return TMPL_NAN;
    else if (x == 0.0)
        return -TMPL_INFINITY;
    else if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x + x;
    else if (0.875 < x && x < 1.125)
    {
        A = (x - 1.0)/(x + 1.0);
        A_sq = A*A;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
        return A * (
            A0 + A_sq * (
                A1 + A_sq * (
                    A2 + A_sq * (
                        A3 + A_sq * (A4 + A_sq * A5)
                    )
                )
            )
        );
    }

    tmpl_Double_Base2_Mant_and_Exp(x, &mantissa, &exponent);

    if (mantissa > 1.5)
    {
        mantissa *= 0.5;
        exponent += 1;
    }

    A = (mantissa - 1.0) / (mantissa + 1.0);
    A_sq = A*A;

    poly = 0.095238095238095238 * A_sq + 0.10526315789473684;
    poly =                 poly * A_sq + 0.11764705882352941;
    poly =                 poly * A_sq + 0.13333333333333333;
    poly =                 poly * A_sq + 0.15384615384615385;
    poly =                 poly * A_sq + 0.18181818181818182;
    poly =                 poly * A_sq + 0.22222222222222222;
    poly =                 poly * A_sq + 0.28571428571428571;
    poly =                 poly * A_sq + 0.40000000000000000;
    poly =                 poly * A_sq + 0.66666666666666667;
    poly =                 poly * A_sq + 2.0000000000000000;

    return tmpl_Natural_Log_of_Two*exponent + A*poly;
}

#endif
/*  #if TMPL_HAS_IEEE754_DOUBLE == 1.                                         */

/*  undef all the macros in case someone wants to #include this file.         */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
