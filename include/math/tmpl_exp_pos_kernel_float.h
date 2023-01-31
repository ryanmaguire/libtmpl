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
 *                         tmpl_exp_pos_kernel_float                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes exp(x) for 1 < x < log(FLT_MAX).                             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Exp_Pos_Kernel                                             *
 *  Purpose:                                                                  *
 *      Computes exp(x) for positive values, 1 < x < log(FLT_MAX).            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for exp(x).                           *
 *  Output:                                                                   *
 *      exp_x (float):                                                        *
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
 *              and exp(t) is computed using a degree 2 Minimax polynomial.   *
 *              The coefficients were computed using the Remez exchange       *
 *              algorithm. Peak theoretical error is 2 x 10^-8. Actual        *
 *              machine error is about 1 ULP (~1 x 10^-7).                    *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Pow2 (tmpl_math.h):                                    *
 *              Computes a power of 2.                                        *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but compute 2^k with tmpl_Float_Pow2.    *
 *  Notes:                                                                    *
 *      This function assumes the input x is not infinity, not NaN, and       *
 *      positive between 1 and log(FLT_MAX) ~= -88 for 32-bit float.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_USE_INLINE macro.                 *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EXP_POS_KERNEL_FLOAT_H
#define TMPL_EXP_POS_KERNEL_FLOAT_H

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator of the Remez polynomial.                   */
#define A0 (+9.9999999998109338754067767533573865627674687051644E-01F)
#define A1 (+1.0000076243218341525635923446100548002732087957627E+00F)
#define A2 (+5.0000187484695511437532498098172375200616122154453E-01F)
#define TMPL_ONE_BY_128 (0.0078125F)

/*  Check for IEEE-754 support. Significantly faster.                         */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(FLT_MAX).                   */
TMPL_INLINE_DECL
float tmpl_Float_Exp_Pos_Kernel(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float exp_w;

    /*  log(2) split into two components for extra precision.                 */
    const float ln_2_hi = 6.9314575195E-01F;
    const float ln_2_lo = 1.4286067653e-06F;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const float rcpr_ln_2 = 1.44269504088896338700E+00F;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const unsigned int k = (unsigned int)(rcpr_ln_2*x + 0.5F);
    const float kf = (float)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const float hi = x - ln_2_hi*kf;
    const float lo = kf*ln_2_lo;
    const float r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0F*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const float t = r - TMPL_ONE_BY_128*(float)r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~2x10^-8. */
    exp_w.r = A0 + t*(A1 + t*A2);

    /*  Compute exp(n/128)*exp(t) using the table.                            */
    exp_w.r *= tmpl_float_exp_table[ind];

    /*  Compute exp(x) via 2^k * exp(r).                                      */
    exp_w.bits.expo += k & 0xFF;
    return exp_w.r;
}
/*  End of tmpl_Float_Exp_Pos_Kernel.                                         */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(FLT_MAX).                   */
TMPL_INLINE_DECL
float tmpl_Float_Exp_Pos_Kernel(float x)
{
    /*  log(2) split into two components for extra precision.                 */
    const float ln_2_hi = 6.9314575195E-01F;
    const float ln_2_lo = 1.4286067653e-06F;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const float rcpr_ln_2 = 1.44269504088896338700E+00F;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const signed int k = (signed int)(rcpr_ln_2*x + 0.5F);
    const float kf = (float)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  Compute the value r by subtracting k*ln(2) from x.                    */
    const float hi = x - ln_2_hi*kf;
    const float lo = kf*ln_2_lo;
    const float r = hi - lo;

    /*  Split r into r = n/128 + t for an integer n and |t| < 1/128.          */
    const int r128 = (int)(128.0F*r);

    /*  The indices range from -89 to + 89. Shift r128 by 89 to make it a     *
     *  positive index for the table.                                         */
    const int ind = r128 + 89;

    /*  Compute t = r - n/128.                                                */
    const float t = r - TMPL_ONE_BY_128*(float)r128;

    /*  Compute exp(t) via the Remez Minimax polynomial. Peak error ~2x10^-8. */
    const float poly = A0 + t*(A1 + t*A2);

    /*  Compute 2^k*exp(n/128)*exp(t) using the table.                        */
    return poly*tmpl_float_exp_table[ind]*tmpl_Float_Pow2(k);
}
/*  End of tmpl_Float_Exp_Neg_Kernel.                                         */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine all coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2
#undef TMPL_ONE_BY_128

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
