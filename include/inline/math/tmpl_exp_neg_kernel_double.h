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
 *                         tmpl_exp_neg_kernel_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < -x < log(DBL_MAX).                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Exp_Neg_Kernel                                            *
 *  Purpose:                                                                  *
 *      Computes exp(x) for negative values, 1 < -x < log(DBL_MAX).           *
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
#ifndef TMPL_EXP_NEG_KERNEL_DOUBLE_H
#define TMPL_EXP_NEG_KERNEL_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Location of the TMPL_HAS_IEEE754_DOUBLE macro and IEEE data type.         */
#include <libtmpl/include/tmpl_ieee754_double.h>

/*  Coefficients for the Remez polynomial.                                    */
#define A0 (+1.0000000000000000098676804486032581931971677454305E+00)
#define A1 (+1.0000000000000000077001514598996570259345221024298E+00)
#define A2 (+4.9999999999708980614478940658809472988077097967424E-01)
#define A3 (+1.6666666666585521370389353791249722847045340843435E-01)
#define A4 (+4.1666793819163332764129161759693899954112387250407E-02)
#define A5 (+8.3333564677959633974492787478109645751141070623399E-03)
#define TMPL_ONE_BY_128 (0.0078125)

/*  Check for IEEE-754 support. Significantly faster.                         */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  With fixed-width 64-bit integers and 64-bit double we can speed this up.  */
#if TMPL_HAS_FLOATINT64 == 1

/******************************************************************************
 *                    IEEE-754 Version with 64-Bit Integers                   *
 ******************************************************************************/

/*  Fixed-width integers found here.                                          */
#include <libtmpl/include/tmpl_inttype.h>

/*  Function for converting from int to float.                                */
#include <libtmpl/include/floatint/tmpl_uint64_to_double.h>
#include <libtmpl/include/floatint/tmpl_double_to_uint64.h>

/*  Lookup table for the exponential function.                                */
extern const tmpl_UInt64 tmpl_double_exp_table[256];

/*
 *  TODO:
 *      Rewrite to work on i386.
 *      Need to declare kd_shift and kd as "volatile" for the shift to work.
 *      Bring back TMPL_VOLATILE so that other architectures are not slowed
 *      down by the unnecessary volatile declaration.
 *
 *      Also, find out why tmpl_Double_Exp_Pos_Kernel does NOT require
 *      volatile. Very strange indeed.
 */

/*  Function for computing exp(x) for 1 < x < log(DBL_MAX).                   */
TMPL_INLINE_DECL
double tmpl_Double_Exp_Neg_Kernel(double x)
{
    /*  The constant 128 / ln(2), to double precision.                        */
    const double rcpr_ln2_times_128 = 1.846649652337873135365953203291e+02;

    /*  -ln(2) / 128 to 128 bits using two doubles.                           */
    const double minus_ln2_by_128_hi = -5.415212348111708706710487604141e-03;
    const double minus_ln2_by_128_lo = -1.286402311163834553810886276993e-14;

    /*  Shift factor for correctly computing the index.                       */
    const double shift = 6.755399441055744E+15;

    /*  exp(x) = e^(ln(2) x / ln(2)) = 2^(x / ln(2)). Compute using this.     */
    const double z = rcpr_ln2_times_128 * x;

    const double kd_shift = z + shift;

    /*  Round the input to an integer.                                        */
    const tmpl_UInt64 ki = tmpl_Double_To_UInt64(kd_shift);

    /*  Cast this integer as a double. exp(k + r) = exp(k) * exp(r). We'll    *
     *  be using this in a few lines.                                         */
    const double kd = kd_shift - shift;

    /*  Compute x - floor(x)/ln(2).                                           */
    const double r = (x + kd*minus_ln2_by_128_hi) + kd*minus_ln2_by_128_lo;

    /*  Index for the lookup table of pre-computed exponential values.        */
    const tmpl_UInt64 ind = (ki & 0x7F) << 1;

    /*  The exponent of the output can be computed using the integer part.    */
    const tmpl_UInt64 top = ki << 45;

    /*  The lookup tables has the values of x stored by their 64-bit integer  *
     *  representations. Convert these to actual doubles.                     */
    const double tail = tmpl_UInt64_To_Double(tmpl_double_exp_table[ind]);

    /*  Compute exp(k + r) = exp(k) * exp(r) using a Remez polynomial.        */
    const tmpl_UInt64 sbits = tmpl_double_exp_table[ind + 1] + top;
    const double tmp = tail + r*(A1 + r*(A2 + r*(A3 + r*(A4 + r*A5))));
    const double scale = tmpl_UInt64_To_Double(sbits);
    return scale + scale * tmp;
}
/*  End of tmpl_Double_Exp_Pos_Kernel.                                        */

/*  Lacking 64-bit integers, but having 64-bit double (strange), use this.    */
#else

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Lookup table for the exponential function.                                */
extern const double tmpl_double_exp_table[179];

/*  Function for computing exp(x) for 1 < -x < log(DBL_MAX).                  */
TMPL_INLINE_DECL
double tmpl_Double_Exp_Neg_Kernel(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double exp_w;

    /*  log(2) split into two components for extra precision.                 */
    const double ln_2_hi = 6.93147180369123816490e-01;
    const double ln_2_lo = 1.90821492927058770002e-10;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const double rcpr_ln_2 = 1.44269504088896338700e+00;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const unsigned int k = (unsigned int)(rcpr_ln_2*(-x) + 0.5);
    const double kd = (double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const double hi = x + ln_2_hi*kd;
    const double lo = kd*ln_2_lo;
    const double r = hi + lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~10^-17.  */
    exp_w.r = A0 + t*(A1 + t*(A2 + t*(A3 + t*(A4 + t*A5))));

    /*  Compute exp(n/128)*exp(t) using the table.                            */
    exp_w.r *= tmpl_double_exp_table[ind];

    /*  Compute exp(x) via 2^k * exp(n/128 + t).                              */
    exp_w.bits.expo -= k & 0x7FF;
    return exp_w.r;
}
/*  End of tmpl_Double_Exp_Neg_Kernel.                                        */

#endif
/*  End of #if TMPL_HAS_FLOATINT64 == 1.                                      */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing 2^n as a double.                                   */
extern double tmpl_Double_Pow2(signed int expo);

/*  Lookup table for the exponential function.                                */
extern const double tmpl_double_exp_table[179];

/*  Function for computing exp(x) for 1 < -x < log(DBL_MAX).                  */
TMPL_INLINE_DECL
double tmpl_Double_Exp_Neg_Kernel(double x)
{
    /*  log(2) split into two components for extra precision.                 */
    const double ln_2_hi = 6.93147180369123816490e-01;
    const double ln_2_lo = 1.90821492927058770002e-10;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const double rcpr_ln_2 = 1.44269504088896338700e+00;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const signed int k = (signed int)(rcpr_ln_2*(-x) + 0.5);
    const double kd = (double)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const double hi = x + ln_2_hi*kd;
    const double lo = kd*ln_2_lo;
    const double r = hi + lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const double t = r - TMPL_ONE_BY_128*r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~10^-17.  */
    const double poly = A0 + t*(A1 + t*(A2 + t*(A3 + t*(A4 + t*A5))));

    /*  Compute 2^k*exp(n/128)*exp(t) using the table.                        */
    return poly*tmpl_double_exp_table[ind]*tmpl_Double_Pow2(-k);
}
/*  End of tmpl_Double_Exp_Neg_Kernel.                                        */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine all coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef TMPL_ONE_BY_128

#endif
/*  End of include guard.                                                     */
