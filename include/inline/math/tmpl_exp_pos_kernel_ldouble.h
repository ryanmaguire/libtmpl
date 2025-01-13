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
 *                         tmpl_exp_pos_kernel_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(DBL_MAX).                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Pos_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for negative values, 1 < x < log(DBL_MAX).            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the argument for exp(x).                           *
 *  Output:                                                                   *
 *      exp_x (double):                                                       *
 *          The exponential of x.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Put x into the form x = ln(2)*k + r. Then:                        *
 *                                                                            *
 *              exp(x) = exp(ln(2)k + r)                                      *
 *                     = exp(ln(2^k))*exp(r)                                  *
 *                     = 2^k*exp(r)                                           *
 *                                                                            *
 *              with |r| < ln(2)/2. 2^k can be computed instantly by setting  *
 *              the exponent bit to k. exp(r) is computed by writing:         *
 *                                                                            *
 *                  exp(r) = exp(k/128 + t)                                   *
 *                         = exp(k/128)*exp(t)                                *
 *                                                                            *
 *              with |t| < 1/128. exp(k/128) is computed via a lookup table   *
 *              and exp(t) is computed using a degree 5 Minimax polynomial.   *
 *              The coefficients were computed using the Remez exchange       *
 *              algorithm. Peak theoretical error is 1 x 10^-17. Actual       *
 *              machine error is about 1 ULP (~2 x 10^-16).                   *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Double_Pow2 (tmpl_math.h):                                   *
 *              Computes a power of 2.                                        *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but compute 2^k with tmpl_Double_Pow2.   *
 *  Notes:                                                                    *
 *      This function assumes the input x is not infinity, not NaN, and       *
 *      negative between -1 and -log(DBL_MAX) ~= -709 for 64-bit double.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/30: Ryan Maguire                                                  *
 *      Changed Maclaurin series to Remez Minimax polynomial. Fixed comments. *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_POS_KERNEL_LDOUBLE_H
#define TMPL_EXP_POS_KERNEL_LDOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_LDOUBLE macro and IEEE data type.        */
#include <libtmpl/include/tmpl_ieee754_ldouble.h>

/*  Lookup table for exp.                                                     */
extern const long double tmpl_ldouble_exp_table[179];

/*  64-bit long double. Uses the same number of terms as 64-bit double.       */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                               64-bit double                                *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000098587946152856174807029410330051E+00L)
#define A01 (+1.0000000000000000008748316302907966777737099829574E+00L)
#define A02 (+4.9999999999709155360859588933075934522906491959593E-01L)
#define A03 (+1.6666666666645166766791450283566916964696588807315E-01L)
#define A04 (+4.1666793780976833837294253334799291363485692856199E-02L)
#define A05 (+8.3333466936726279750868430183007422022303377304455E-03L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*A05))))

/*  ln(2) split into two parts.                                               */
#define TMPL_LN2_HI (+6.93147180369123816490e-01L)
#define TMPL_LN2_LO (+1.90821492927058770002e-10L)

/*  Bit masked, this is the number of bits in the exponents, written in hex.  */
#define TMPL_BITMASK (0x7FF)

/*  128-bit double-double. More terms to get ~5 x 10^-32 peak error.          */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT || \
      TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                     128-bit double-double / quadruple                      *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+1.0000000000000000000000000000000000000565152668486E+00L)
#define A01 (+1.0000000000000000000000000000002277417724792912500E+00L)
#define A02 (+4.9999999999999999999999999999994619309021027761533E-01L)
#define A03 (+1.6666666666666666666666659202667190696065095119770E-01L)
#define A04 (+4.1666666666666666666666673462654436922178773289334E-02L)
#define A05 (+8.3333333333333333401828282229962163491180862188154E-03L)
#define A06 (+1.3888888888888888887030304039474566517024083478372E-03L)
#define A07 (+1.9841269841244185833600164547228304084060638439823E-04L)
#define A08 (+2.4801587301583078512959598177460791166292031088162E-05L)
#define A09 (+2.7557361265493688544737857478863731875176059077397E-06L)
#define A10 (+2.7557341055632737587480078761940129942894524490180E-07L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00+\
z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*(A09+z*A10)))))))))

/*  ln(2) split into two parts.                                               */
#define TMPL_LN2_HI (+6.9314718055994530941723154115927820850644180961098E-01L)
#define TMPL_LN2_LO (+5.8029889835956905832474897278545862267173858328198E-25L)

/*  Bit masked, this is the number of bits in the exponents, written in hex.  */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN
#define TMPL_BITMASK (0x7FF)
#else
#define TMPL_BITMASK (0x7FFF)
#endif

/*  Lastly, portable and 80-bit extended. Peak error ~1 x 10^-19.             */
#else

/******************************************************************************
 *                         80-bit extended / portable                         *
 ******************************************************************************/

/*  Coefficients for the Remez polynomial.                                    */
#define A00 (+9.9999999999999999999999462394527682917191523486311E-01L)
#define A01 (+1.0000000000000000049343307717608995390142238254127E+00L)
#define A02 (+5.0000000000000000220198436065133460092718157932901E-01L)
#define A03 (+1.6666666666601991406365279636808577019578019943954E-01L)
#define A04 (+4.1666666666516565608307910224784060370605018971811E-02L)
#define A05 (+8.3333545261175916787785570653425058076183817419189E-03L)
#define A06 (+1.3888922944678747909527805666137706009248340500039E-03L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*A06)))))

/*  ln(2) split into two parts.                                               */
#define TMPL_LN2_HI (+6.9314575195312500000000E-01L)
#define TMPL_LN2_LO (+1.4286068203094172321215E-06L)

/*  Bit masked, this is the number of bits in the exponents, written in hex.  */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_UNKNOWN
#define TMPL_BITMASK (0x7FFF)
#endif

#endif
/*  End of double vs. extended / portable vs. double-double vs. quadruple.    */

/*  The value 1 / 128 to long double precision.                               */
#define TMPL_ONE_BY_128 (0.0078125L)

/*  Check for IEEE-754 support. Significantly faster.                         */
#if TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(LDBL_MAX).                  */
TMPL_INLINE_DECL
long double tmpl_LDouble_Exp_Pos_Kernel(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble exp_w;

    /*  log(2) split into two components for extra precision.                 */
    const long double ln_2_hi = TMPL_LN2_HI;
    const long double ln_2_lo = TMPL_LN2_LO;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const long double rcpr_ln_2 = 1.4426950408889634073599246810018921374E+00L;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const unsigned int k = (unsigned int)(rcpr_ln_2*x + 0.5L);
    const long double kd = (long double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const long double hi = x - ln_2_hi*kd;
    const long double lo = kd*ln_2_lo;
    const long double r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0L*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const long double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial.                      */
    exp_w.r = TMPL_POLY_EVAL(t);

    /*  Compute exp(n/128)*exp(t) using the table.                            */
    exp_w.r *= tmpl_ldouble_exp_table[ind];

    /*  Compute exp(x) via 2^k * exp(n/128 + t).                              */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN
    {
        tmpl_IEEE754_LDouble two_to_the_minus_k;
        two_to_the_minus_k.r = 1.0L;
        two_to_the_minus_k.bits.expo += k & TMPL_BITMASK;
        exp_w.r *= two_to_the_minus_k.r;
    }
#else
    exp_w.bits.expo += k & TMPL_BITMASK;
#endif
    return exp_w.r;
}
/*  End of tmpl_LDouble_Exp_Pos_Kernel.                                       */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Computes 2^n as a long double.                                            */
extern long double tmpl_LDouble_Pow2(signed int expo);

/*  Function for computing exp(x) for 1 < x < log(LDBL_MAX).                  */
TMPL_INLINE_DECL
long double tmpl_LDouble_Exp_Pos_Kernel(long double x)
{
    /*  log(2) split into two components for extra precision.                 */
    const long double ln_2_hi = TMPL_LN2_HI;
    const long double ln_2_lo = TMPL_LN2_LO;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const long double rcpr_ln_2 = 1.4426950408889634073599246810018921374E+00L;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const signed int k = (signed int)(rcpr_ln_2*x + 0.5L);
    const long double kd = (long double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const long double hi = x - ln_2_hi*kd;
    const long double lo = kd*ln_2_lo;
    const long double r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0L*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const long double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial.                      */
    const long double poly = TMPL_POLY_EVAL(t);

    /*  Compute 2^k*exp(n/128)*exp(t) using the table.                        */
    return poly*tmpl_ldouble_exp_table[ind]*tmpl_LDouble_Pow2(k);
}
/*  End of tmpl_LDouble_Exp_Pos_Kernel.                                       */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine all coefficients in case someone wants to #include this file.    */
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
#undef TMPL_POLY_EVAL
#undef TMPL_BITMASK
#undef TMPL_ONE_BY_128
#undef TMPL_LN2_HI
#undef TMPL_LN2_LO

#endif
/*  End of include guard.                                                     */
