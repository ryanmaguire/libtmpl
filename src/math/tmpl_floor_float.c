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
 *                              tmpl_floor_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = |_x_|, the floor of x. This is the largest integer    *
 *      that is less than or equal to the input x.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Floor                                                      *
 *  Purpose:                                                                  *
 *      Computes the floor function. The largest integer less than or equal   *
 *      to the input.                                                         *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for |_x_|.                            *
 *  Output:                                                                   *
 *      floor_x (float):                                                      *
 *          The floor of x.                                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
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
#if TMPL_HAS_IEEE754_FLOAT == 1

/*  If 32-bit integers are available, we can make the code shorter.           */
#include <libtmpl/include/tmpl_integer.h>

/*  Check for 32-bit integer support.                                         */
#if TMPL_HAS_32_BIT_INT == 1

/*  Function for computing the floor of a float (floorf equivalent).          */
float tmpl_Float_Floor(float x)
{
    union {
        tmpl_IEEE754_Float w;
        tmpl_UInt32 i;
    } word32;
    tmpl_UInt32 i, j;
    
    word32.w.r = x;

    if (word32.w.bits.expo < TMPL_FLOAT_BIAS)
    {
        if (x == 0.0F)
            return x;

        if (word32.w.bits.sign)
            return -1.0;
        else
            return 0.0;
    }

    if (word32.w.bits.expo > TMPL_FLOAT_BIAS + 22U)
        return x;

    i = ((word32.i >> 23U) & TMPL_FLOAT_NANINF_EXP) - TMPL_FLOAT_BIAS;
    j = 0x007FFFFF >> i;

	if ((word32.i & j) == 0)
	    return x;

	if (word32.w.bits.sign)
	    word32.i += 0x00800000 >> i;

	word32.i &= ~j;
    return word32.w.r;
}
/*  End of tmpl_Float_Floor.                                                  */

#else
/*  Else for #if TMPL_HAS_32_BIT_INT == 1.                                    */

/*  This method does not require 32 bit integer types be available. It does   *
 *  require that IEEE-754 support for float is available. It is a little      *
 *  slower since we have to check the mantissa 16 bits at a time.             */

/*  The mantissa is split into 2 components. The highest component has 7 bits *
 *  and the lowest component has 16 bits, 23 bits total.                      */
#define A0 8U

/*  Function for computing the floor of a float (floorf equivalent).          */
float tmpl_Float_Floor(float x)
{
    tmpl_IEEE754_Float w;
    w.r = x;

    if (w.bits.expo < TMPL_FLOAT_BIAS)
    {
        if (x == 0.0F)
            return x;

        if (w.bits.sign)
            return -1.0F;
        else
            return 0.0F;
    }

    if (w.bits.expo > TMPL_FLOAT_BIAS + 22U)
        return x;

    if (w.bits.expo < TMPL_FLOAT_BIAS + A0)
    {
        w.bits.man1 = 0x00U;
        w.bits.man0 &= ~(0x7F >> (w.bits.expo - TMPL_FLOAT_BIAS));
    }
    else
        w.bits.man1 &= ~(0xFFFF >> (w.bits.expo - TMPL_FLOAT_BIAS - A0));

    if (w.r == x)
        return x;

    if (w.bits.sign)
        return w.r - 1.0F;
    else
        return w.r;
}
/*  End of tmpl_Float_Floor.                                                  */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_HAS_32_BIT_INT == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

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
static const float tmpl_float_pow_2_table[65] = {
    1.0F, 2.0F, 4.0F, 8.0F, 16.0F, 32.0F, 64.0F, 128.0F, 256.0F, 512.0F,
    1024.0F, 2048.0F, 4096.0F, 8192.0F, 16384.0F, 32768.0F, 65536.0F, 131072.0F,
    262144.0F, 524288.0F, 1048576.0F, 2097152.0F, 4194304.0F, 8388608.0F,
    16777216.0F, 33554432.0F, 67108864.0F, 134217728.0F, 268435456.0F,
    536870912.0F, 1073741824.0F, 2147483648.0F, 4294967296.0F, 8589934592.0F,
    17179869184.0F, 34359738368.0F, 68719476736.0F, 137438953472.0F,
    274877906944.0F, 549755813888.0F, 1099511627776.0F, 2199023255552.0F,
    4398046511104.0F, 8796093022208.0F, 17592186044416.0F, 35184372088832.0F,
    70368744177664.0F, 140737488355328.0F, 281474976710656.0F,
    562949953421312.0F, 1125899906842624.0F, 2251799813685248.0F,
    4503599627370496.0F, 9007199254740992.0F, 18014398509481984.0F,
    36028797018963968.0F, 72057594037927936.0F, 144115188075855872.0F,
    288230376151711744.0F, 576460752303423488.0F, 1152921504606846976.0F,
    2305843009213693952.0F, 4611686018427387904.0F, 9223372036854775808.0F,
    18446744073709551616.0F
};

/*  Function for computing the floor of a float (floorf equivalent).          */
float tmpl_Float_Floor(float x)
{
    float abs_x, mant, y, out;
    signed int expo;

    /*  Special case, floor(0) = 0.                                           */
    if (x == 0.0F)
        return x;

    /*  Next special case, NaN or inf. Return the input.                      */
    if (tmpl_Float_Is_NaN_Or_Inf(x))
        return x;

    /*  Get the numbers mant and expo such that x = mant * 2^expo with        *
     *  1 <= |mant| < 2. That is, the base 2 scientific notation of x.        */
    tmpl_Float_Base2_Mant_and_Exp(x, &mant, &expo);

    /*  If expo < 0 we have |x| < 1. floor(x) = 0 if x >= 0 and -1 otherwise. */
    if (expo < 0)
    {
        if (x < 0.0F)
            return -1.0F;
        else
            return 0.0F;
    }

    /*  This function is only accurate to 64 bits in the mantissa. For most   *
     *  machines the mantissa has 23 bits, so this is probably overkill.      */
    else if (expo > 64)
        return x;

    /*  Use the fact that floor(x) = -1 - floor(-x) for negative non-integer  *
     *  values to reduce the argument.                                        */
    abs_x = tmpl_Float_Abs(x);

    /*  We're going to "zero" the highest bit of the integer part of abs_x    *
     *  by substracting it off. Compute this from the lookup table.           */
    y = tmpl_float_pow_2_table[expo];

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
        y = tmpl_float_pow_2_table[expo];

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
    if (x < 0.0F)
    {
        /*  The formula does not work for integers. If the input was an       *
         *  integer to begin with, return it.                                 */
        if (x == -out)
            return x;

        /*  Otherwise, use the negation formula and return.                   */
        else
            return -1.0F - out;
    }

    /*  For positive values, we are done with the computation.                */
    else
        return out;
}
/*  End of tmpl_Float_Floor.                                                  */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                  */

#endif
/*  End of TMPL_USE_MATH_ALGORITHMS.                                          */
