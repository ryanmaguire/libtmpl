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
 *                             tmpl_floor_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |_x_|, the floor of x. This is the largest integer    *
 *      that is less than or equal to the input x.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Floor                                                     *
 *  Purpose:                                                                  *
 *      Computes the floor function. The largest integer less than or equal   *
 *      to the input.                                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for |_x_|.                            *
 *  Output:                                                                   *
 *      floor_x (double):                                                     *
 *          The floor of x.                                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, use bit-twiddling. A double is      *
 *      represented as follows:                                               *
 *                                                                            *
 *        s eeeeeeeeeee xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  *
 *        - ----------- ----------------------------------------------------  *
 *      sign exponent                mantissa                                 *
 *                                                                            *
 *      If exponent >= 52, the number is an integer. If exponent < 0, the     *
 *      number is such that |x| < 1, so floor(x) = 0 is x is non-negative,    *
 *      and -1 if x is negative. Otherwise, shift the bit point "exponent" to *
 *      the right and zero out all mantissa bits that are to the right of the *
 *      new bit point.                                                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 26, 2022                                            *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS is found here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  This function is only implemented if tmpl's libm was requested.           */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Check for IEEE-754 support. This makes the function much faster.          */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  If 64-bit integers are available, we can make the code shorter.           */
#include <libtmpl/include/tmpl_integer.h>

/*  Check for 64-bit integer support.                                         */
#if TMPL_HAS_64_BIT_INT == 1

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    union {
        tmpl_IEEE754_Double w;
        tmpl_UInt64 i;
    } word64;
    tmpl_UInt64 i, j;
    
    word64.w.r = x;

    if (word64.w.bits.expo < TMPL_DOUBLE_BIAS)
    {
        if (word64.w.bits.sign)
            return -1.0;
        else
            return 0.0;
    }

    if (word64.w.bits.expo > TMPL_DOUBLE_BIAS + 51U)
        return x;

    i = ((word64.i >> 52U) & 0x7FFU) - 0x3FFU;
    j = 0x000fffffffffffffl >> i;

	if ((word64.i & j) == 0)
	    return x;

	if (word64.w.bits.sign)
	    word64.i += 0x0010000000000000 >> i;

	word64.i &= ~j;
    return word64.w.r;
}
/*  End of tmpl_Double_Floor.                                                 */

#else
/*  Else for #if TMPL_HAS_64_BIT_INT == 1.                                    */

/*  This method does not require 64 bit integer types be available. It does   *
 *  require that IEEE-754 support for double is available. It is a little     *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  The mantissa is split into 4 components. The highest component has 4 bits *
 *  and the other three have 16 each. These three numbers are the cutoff      *
 *  values for the components.                                                */
#define A0 36U
#define A1 20U
#define A2 4U

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    tmpl_IEEE754_Double w;
    w.r = x;

    if (w.bits.expo < TMPL_DOUBLE_BIAS)
    {
        if (x == 0.0)
            return x;

        if (w.bits.sign)
            return -1.0;
        else
            return 0.0;
    }

    if (w.bits.expo > TMPL_DOUBLE_BIAS + 51U)
        return x;

    if (w.bits.expo < TMPL_DOUBLE_BIAS + A0)
        w.bits.man3 = 0x00U;
    else
    {
        w.bits.man3 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A0));
        goto TMPL_DOUBLE_FLOOR_FINISH;
    }

    if (w.bits.expo < TMPL_DOUBLE_BIAS + A1)
        w.bits.man2 = 0x00U;
    else
    {
        w.bits.man2 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A1));
        goto TMPL_DOUBLE_FLOOR_FINISH;
    }

    if (w.bits.expo < TMPL_DOUBLE_BIAS + A2)
        w.bits.man1 = 0x00U;
    else
    {
        w.bits.man1 &= ~(0xFFFF >> (w.bits.expo - TMPL_DOUBLE_BIAS - A2));
        goto TMPL_DOUBLE_FLOOR_FINISH;
    }

    w.bits.man0 &= ~(0xF >> (w.bits.expo - TMPL_DOUBLE_BIAS));


TMPL_DOUBLE_FLOOR_FINISH:
    if (w.r == x)
        return x;

    if (w.bits.sign)
        return w.r - 1.0;
    else
        return w.r;
}
/*  End of tmpl_Double_Floor.                                                 */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_HAS_64_BIT_INT == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *  DO NOT USE UNLESS YOU HAVE NO OTHER OPTIONS.                              *
 *      This code is portable but stupidly slow. The default build of libtmpl *
 *      uses assembly code that is very fast. If the user requested no        *
 *      assembly code and IEEE-754 support is available, the above code is    *
 *      used, and is nearly as fast. This portable code is available in case  *
 *      assembly language nor IEEE-754 support can be used, but it is slow.   *
 *                                                                            *
 *      On x86_64 machines, the assembly code and both versions of the floor  *
 *      function above that take advantage of the IEEE-754 format have        *
 *      computational time comparable to other libm implementations. This     *
 *      version is about 10x slower.                                          *
 ******************************************************************************/

/*  Powers of 2, 2^n, for n = 0 to n = 64.                                    */
static const double tmpl_double_pow_2_table[65] = {
    1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0,
    4096.0, 8192.0, 16384.0, 32768.0, 65536.0, 131072.0, 262144.0, 524288.0,
    1048576.0, 2097152.0, 4194304.0, 8388608.0, 16777216.0, 33554432.0,
    67108864.0, 134217728.0, 268435456.0, 536870912.0, 1073741824.0,
    2147483648.0, 4294967296.0, 8589934592.0, 17179869184.0, 34359738368.0,
    68719476736.0, 137438953472.0, 274877906944.0, 549755813888.0,
    1099511627776.0, 2199023255552.0, 4398046511104.0, 8796093022208.0,
    17592186044416.0, 35184372088832.0, 70368744177664.0, 140737488355328.0,
    281474976710656.0, 562949953421312.0, 1125899906842624.0,
    2251799813685248.0, 4503599627370496.0, 9007199254740992.0,
    18014398509481984.0, 36028797018963968.0, 72057594037927936.0,
    144115188075855872.0, 288230376151711744.0, 576460752303423488.0,
    1152921504606846976.0, 2305843009213693952.0, 4611686018427387904.0,
    9223372036854775808.0, 18446744073709551616.0
};

/*  Function for computing the floor of a double (floor equivalent).          */
double tmpl_Double_Floor(double x)
{
    double abs_x, mant, y, out;
    signed int expo;

    /*  Special case, floor(0) = 0.                                           */
    if (x == 0.0)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_Double_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. floor(x) = 0 if x >= 0 and -1 otherwise. */
    if (expo < 0)
    {
        if (x < 0.0)
            return -1.0;
        else
            return 0.0;
    }

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 52 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that floor(x) = -1 - floor(-x) for negative non-integer  *
     *  values to reduce the argument.                                        */
    abs_x = tmpl_Double_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_double_pow_2_table[expo];

    /*  We will iteratively add the non-zero bits of the integer part to out, *
     *  resulting in us computing floor(abs_x).                               */
    out = y;

    /*  Zero out the highest bit of abs_x by subtracting y.                   */
    abs_x = abs_x - y;

    /*  This highest non-zero bit has been zeroed out, move to the next one.  */
    expo -= 1;

    /*  Loop over the remaining bits of the integer part of abs_x and repeat. */
    while (expo >= 0)
    {
        y = tmpl_double_pow_2_table[expo];

        /*  If abs_x < y, this bit is already zero. No need to subtract.      */
        if (abs_x < y)
            expo--;

        /*  Otherwise, zero this bit out and add it to out.                   */
        else
        {
            abs_x = abs_x - y;
            out += y;
            expo--;
        }
    }

    /*  If the input was negative we need to use floor(x) = -1 - floor(-x).   */
    if (x < 0.0)
    {
        /*  The formula does not work for integers. If the input was an       *
         *  integer to begin with, return it.                                 */
        if (x == -out)
            return x;

        /*  Otherwise, use the negation formula and return.                   */
        else
            return -1.0 - out;
    }

    /*  For positive values, we are done with the computation.                */
    else
        return out;
}
/*  End of tmpl_Double_Floor.                                                 */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */
