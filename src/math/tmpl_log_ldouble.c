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
 *                            tmpl_log_ldouble                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at long double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Log                                                      *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (double):                                                       *
 *          The natural log of x at long double precision.                    *
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
 *          t = 1 + k/128 <= u. This value k can be obtained directly from the*
 *          mantissa. By looking at the most significant 7 bits of the        *
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
 *          A polynomial with the first few terms is then used. The           *
 *          standard Taylor series polynomial for ln(1 + x) with x small has  *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values slightly less than 1, the computation of (s-1) / (s+1) *
 *          leads to large relative error since log(1) = 1. We can achieve    *
 *          better relative error using the standard Taylor series to several *
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
 *                                                                            *
 *          For double-double implementations, we compute log(x) as follows.  *
 *                                                                            *
 *              log(x) = log(x_hi + x_low)                                    *
 *                     = log(x * x_hi / x_hi)                                 *
 *                     = log(x / x_hi) + log(x_hi)                            *
 *                     = log(1 - 1 + x/x_hi) + log(x_hi)                      *
 *                     = log(1 + (x - x_hi)/x_hi) + log(x_hi)                 *
 *                     = log(1 + x_low / x_hi) + log(x_hi)                    *
 *                                                                            *
 *          x_low / x_hi is small, so log (1 + x_low / x_hi) can be well      *
 *          approximated by the first few terms of the Taylor series for      *
 *          log(1 + t). log(x_hi) is computed in the same way as a normal     *
 *          long double (see above).                                          *
 *                                                                            *
 *      If the user has not requested libtmpl algorithms, or if IEEE-754      *
 *      support is not available (highly unlikely), then #include <math.h>    *
 *      is called and tmpl_Double_Log returns logl(x) from math.h             *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_LDOUBLE == 0 or if              *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_LDouble_Log is identical to the logl function.               *
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
 *  Date:       February 12, 2022                                             *
 ******************************************************************************/

/*  TODO: Clean this up. Get rid of unused macro warnings on ppc64.           */

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if TMPL_HAS_IEEE754_LDOUBLE == 1 && TMPL_USE_MATH_ALGORITHMS == 1

/*  Macros for 1/n for n = 2, 3, ..., 6, 7. These make the code look cleaner. */
#define ONE_HALF 0.50L
#define ONE_THIRD 0.3333333333333333333333333333333333333L
#define ONE_FOURTH 0.250L
#define ONE_FIFTH 0.20L
#define ONE_SIXTH 0.1666666666666666666666666666666666667L
#define ONE_SEVENTH 0.14285714285714285714285714285714L

/*  Not needed for 64-bit.                                                    */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
#define ONE_EIGHTH 0.1250L
#define ONE_NINTH 0.11111111111111111111111111111111111L
#endif

/*  Double double uses a different algorithm. 64-bit, 80-bit extended, and    *
 *  128-bit quadruple use the same idea.                                      */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN \
    && TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN

/*  Function for computing natural log at long double precision.              */
long double tmpl_LDouble_Log(long double x)
{
    /*  Declare all necessary variables.                                      */
    long double s, poly, A, A_sq;

    /*  Variable for the exponent of the double x. x is written as            *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 15 bit      *
     *  unsigned exponent in a double.                                        */
    signed int exponent;

    /*  Variable for the index of the arrays table and rcpr defined above     *
     *  which corresponds to the input x.                                     */
    unsigned int ind;

    /*  Variable for the union of a double and the bits representing it.      */
    tmpl_IEEE754_LDouble w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NANL;

    /*  Subnormal normal or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0L)
            return -TMPL_INFINITYL;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^63,      *
         *  which is 9.223372036854775808 x 10^18.                            */
        w.r *= 9.223372036854775808E18L;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_LDOUBLE_BIAS - 63;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
    else if (w.bits.expo == 0x7FFU)
        return x;
#else
    else if (w.bits.expo == 0x7FFFU)
        return x;
#endif

    /*  For values close to but less than 1, the computation of the division  *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-16 absolute error since log(1) = 0). To      *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.99L < w.r && w.r < 1.0L)
    {
        s = 1.0L - x;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
        return -s * (
            1.0L + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * (
                        ONE_FOURTH + s * (
                            ONE_FIFTH + s * (
                                ONE_SIXTH + s * (
                                    ONE_SEVENTH + s * (
                                        ONE_EIGHTH + s * ONE_NINTH
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );
#else
        /*  Few terms needed for 64-bit.                                      */
        return -s * (
            1.0L + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * (
                        ONE_FOURTH + s * (
                            ONE_FIFTH + s * (
                                ONE_SIXTH + s * ONE_SEVENTH
                            )
                        )
                    )
                )
            )
        );
#endif
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_LDOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_LDOUBLE_BIAS;

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN

    /*  64-bit. man0 is 4 bits, man1 is 16 bits.                              */
    ind = w.bits.man0;
    ind = (ind << 3U) + (w.bits.man1 >> 13U);
#elif \
 TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
 TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

    /*  128-bit quadruple. man0 is 16 bits wide.                              */
    ind = w.bits.man0 >> 9U;
#else

    /*  Extended precision (96-bit or 128-bit). man0 is 15 bits wide.         */
    ind = w.bits.man0 >> 8U;
#endif

    s = w.r*tmpl_ldouble_rcpr_table[ind];
    A = (s - 1.0L) / (s + 1.0L);
    A_sq = A*A;

#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
    poly = A * (
        2.0L + A_sq * (
            0.666666666666666666666666666666666666667L + A_sq * (
                0.4L + A_sq * 0.285714285714285714285714285714285714L
            )
        )
    );
#else
    /*  Few terms needed for 64-bit.                                          */
    poly = A*(2.0 + A_sq * (0.666666666666666667 + A_sq * 0.4));
#endif

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_L*exponent + poly +
        tmpl_ldouble_log_table[ind];
}
/*  End of tmpl_LDouble_Log.                                                  */

#else

/*  Double double not implemented yet.                                        */
long double tmpl_LDouble_Log(long double x)
{
    tmpl_IEEE754_LDouble w, xhi, xlow;
    long double s, polya, polyb, A, A_sq;
    signed int exponent;
    unsigned int ind;
    w.r = x;

    xhi.r = (long double)w.d[0];
    xlow.r = x - xhi.r;
    s = -xlow.r / xhi.r;

    polya = -s * (1.0L + s * (ONE_HALF + s * ONE_THIRD));

    exponent = xhi.bits.expo - TMPL_LDOUBLE_BIAS;
    xhi.bits.expo = TMPL_LDOUBLE_BIAS;

    ind = w.bits.man0;
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    s = xhi.r*tmpl_ldouble_rcpr_table[ind];
    A = (s - 1.0L) / (s + 1.0L);
    A_sq = A*A;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    polyb = A*(
        2.0L + A_sq * (
            0.666666666666666666666666666666666666667L + A_sq * (
                0.4L + A_sq * (
                    0.285714285714285714285714285714285714L + A_sq * (
                        0.222222222222222222222222222222222222L + A_sq * (
                            0.181818181818181818181818181818181818L + A_sq * 0.153846153846153846153846153846153846L
                        )
                    )
                )
            )
        )
    );

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_L*exponent + polya + polyb +
        tmpl_ldouble_log_table[ind];
}
#endif
/*  End of if for double double.                                              */

/*  undef all the macros incase someone wants to #include this file.          */
#undef ONE_HALF
#undef ONE_THIRD
#undef ONE_FOURTH
#undef ONE_FIFTH
#undef ONE_SIXTH
#undef ONE_SEVENTH

/*  Not defined for 64-bit.                                                   */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
#undef ONE_EIGHTH
#undef ONE_NINTH
#endif

#else
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
long double tmpl_LDouble_Log(long double x)
{
    return logl(x);
}
#else
long double tmpl_LDouble_Log(long double x)
{
    double logx = log((double)x);
    return (long double)logx;
}
#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L       */

#endif
/*  End of if for TMPL_USE_MATH_ALGORITHMS.                                   */
