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
 ******************************************************************************/

#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 long double support.                                   */
#if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1

#define A00 1.0L
#define A01 -0.333333333333333333333333333333333333L
#define A02 0.2L
#define A03 -0.142857142857142857142857142857142857L
#define A04 0.111111111111111111111111111111111111L
#define A05 -0.0909090909090909090909090909090909091L
#define A06 0.0769230769230769230769230769230769231L
#define A07 -0.0666666666666666666666666666666666667L
#define A08 0.0588235294117647058823529411764705882L
#define A09 -0.0526315789473684210526315789473684211L
#define A10 0.047619047619047619047619047619047619L
#define A11 -0.0434782608695652173913043478260869565L

static long double tmpl_double_arctan_maclaurin_series(long double x)
{
    long double x_sq = x*x;
    long double out = x_sq*A11 + A10;
    out = out*x_sq + A09;
    out = out*x_sq + A08;
    out = out*x_sq + A07;
    out = out*x_sq + A06;
    out = out*x_sq + A05;
    out = out*x_sq + A04;
    out = out*x_sq + A03;
    out = out*x_sq + A02;
    out = out*x_sq + A01;
    out = out*x_sq + A00;
    return x*out;
}

static long double tmpl_ldouble_arctan_large_vals(long double x)
{
    const long double arg = -1.0L/x;
    const long double arg_sq = arg*arg;
    long double out = arg_sq*A06 + A05;
    out = out*arg_sq + A04;
    out = out*arg_sq + A03;
    out = out*arg_sq + A02;
    out = out*arg_sq + A01;
    out = out*arg_sq + A00;
    return arg*out;
}

static long double tmpl_ldoule_arctan_small_vals(long double x)
{
    long double x_sq = x*x;
    long double out = x_sq*A07 + A06;
    out = out*x_sq + A05;
    out = out*x_sq + A04;
    out = out*x_sq + A03;
    out = out*x_sq + A02;
    out = out*x_sq + A01;
    out = out*x_sq + A00;
    return x*out;
}

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const long double tmpl_atan_ldouble_v[8] = {
    0.05L,
    0.18L,
    0.35L,
    0.72L,
    1.35L,
    2.5L,
    4.0L,
    8.0L
};

static const long double tmpl_atan_ldouble_atan_of_v[8] = {
    0.0499583957219427614100063L,
    0.178092938231197549667920L,
    0.336674819386727181396699L,
    0.624023052976756847589791L,
    0.933247528656203869893663L,
    1.19028994968253173292773L,
    1.32581766366803246505924L,
    1.44644133224813518419997L
};

/*  Long double precision inverse tangent (atan equivalent).                  */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Small values, |x| < 1/8. Use the MacLaurin series to 8 terms.         */
    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 4U)
        return tmpl_ldoule_arctan_small_vals(x);

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L + tmpl_ldouble_arctan_large_vals(w.r);
        return (x < 0.0L ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_ldouble_v    *
     *  and tmpl_atan_ldouble_atan_of_v that correspond to x. The index is    *
     *  the exponent plus three (since the lowest value is 1/8 = 2^-3, we     *
     *  need to shift up by 3). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_LDOUBLE_BIAS;
    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0L + w.r*v);
    out = atan_v + tmpl_double_arctan_maclaurin_series(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11

#else

#define A00 1.0L
#define A01 -0.333333333333333333333333333333333333L
#define A02 0.2L
#define A03 -0.142857142857142857142857142857142857L
#define A04 0.111111111111111111111111111111111111L
#define A05 -0.0909090909090909090909090909090909091L
#define A06 0.0769230769230769230769230769230769231L
#define A07 -0.0666666666666666666666666666666666667L
#define A08 0.0588235294117647058823529411764705882L
#define A09 -0.0526315789473684210526315789473684211L
#define A10 0.047619047619047619047619047619047619L
#define A11 -0.0434782608695652173913043478260869565L
#define A12 0.04L
#define A13 -0.037037037037037037037037037037037037L
#define A14 0.0344827586206896551724137931034482759L
#define A15 -0.0322580645161290322580645161290322581L
#define A16 0.030303030303030303030303030303030303L

static long double tmpl_arctan_small_vals(long double x)
{
    long double x_sq = x*x;
    long double out = x_sq*A16 + A15;
    out = out*x_sq + A14;
    out = out*x_sq + A13;
    out = out*x_sq + A12;
    out = out*x_sq + A11;
    out = out*x_sq + A10;
    out = out*x_sq + A09;
    out = out*x_sq + A08;
    out = out*x_sq + A07;
    out = out*x_sq + A06;
    out = out*x_sq + A05;
    out = out*x_sq + A04;
    out = out*x_sq + A03;
    out = out*x_sq + A02;
    out = out*x_sq + A01;
    out = out*x_sq + A00;
    return x*out;
}

#define ATAN_OF_ONE_HALF    0.46364760900080611621425623146121440202853705L
#define ATAN_OF_ONE         0.78539816339744830961566084581987572104929234L
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745L

long double tmpl_LDouble_Arctan(long double x)
{
    long double arg, sgn_x;

    if (x < 0.0L)
    {
        sgn_x = -1.0L;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0L;
        arg = x;
    }

    if (arg < 0.25L)
        return sgn_x * tmpl_arctan_small_vals(arg);

    else if (arg < 0.6875L)
    {
        arg = (2.0L * arg - 1.0L) / (2.0L + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + tmpl_arctan_small_vals(arg));
    }
    else if (arg < 1.1875L)
    {
        arg = (arg - 1.0L) / (arg + 1.0L);
        return sgn_x * (ATAN_OF_ONE + tmpl_arctan_small_vals(arg));
    }
    else if (arg < 3.1L)
    {
        arg = (2.0L * arg - 3.0L) / (2.0L + 3.0L * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + tmpl_arctan_small_vals(arg));
    }
    else
    {
        arg = -1.0L / arg;
        return sgn_x * (tmpl_Pi_By_Two_L + tmpl_arctan_small_vals(arg));
    }
}

#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12
#undef A13
#undef A14
#undef A15
#undef A16

#endif
#endif
