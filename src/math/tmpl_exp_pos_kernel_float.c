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
 *              the exponent bit to k. exp(r) is computed via a rational      *
 *              approximation.                                                *
 *      Error:                                                                *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Pow2 (tmpl_math.h):                                    *
 *              Computes a power of 2.                                        *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but compute 2^k with tmpl_Float_Pow2.    *
 *      Error:                                                                *
 *  Notes:                                                                    *
 *      This function assumes the input x is not infinity, not NaN, and       *
 *      positive between 1 and log(FLT_MAX) ~= 88 for 32-bit float.           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 07, 2022                                             *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only compiled if inline support is not requested.            */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynonial. They are 1 / n!.                         */
#define A0 (1.000000000000000000000000000000000000000E+00F)
#define A1 (1.000000000000000000000000000000000000000E+00F)
#define A2 (5.000000000000000000000000000000000000000E-01F)

/*  Check for IEEE-754 support. Significantly faster.                         */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(FLT_MAX).                   */
float tmpl_Float_Exp_Pos_Kernel(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float exp_w;
    float r, t, hi, lo;
    int ind, t256;

    /*  log(2) split into two components for extra precision.                 */
    const float ln_2_hi = 6.9314575195E-01F;
    const float ln_2_lo = 1.4286067653e-06F;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const float rcpr_ln_2 = 1.44269504088896338700E+00F;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const unsigned int k = (unsigned int)(rcpr_ln_2*x + 0.5F);
    t = (float)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  exp(r) is computed via a Taylor series for the function               *
     *  f(r) = r*(exp(r) + 1)/(exp(r) - 1) and solving for exp(r) in          *
     *  terms of f(r).                                                        */
    hi = x - ln_2_hi*t;
    lo = t*ln_2_lo;
    t = hi - lo;

    t256 = (int)(256.0F*t);
    ind = t256 + 177;
    t = t - 0.00390625F*(float)t256;
    r = A0 + t*(A1 + t*A2);
    exp_w.r = r*tmpl_float_exp_table[ind];

    /*  Compute exp(x) via 2^k * exp(t).                                      */
    exp_w.bits.expo += k & 0xFF;
    return exp_w.r;
}
/*  End of tmpl_Float_Exp_Neg_Kernel.                                         */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing exp(x) for 1 < x < log(FLT_MAX).                   */
float tmpl_Float_Exp_Pos_Kernel(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float r, t, hi, lo;
    int ind, t256;

    /*  log(2) split into two components for extra precision.                 */
    const float ln_2_hi = 6.9314575195E-01F;
    const float ln_2_lo = 1.4286067653e-06F;

    /*  Reciprocal of log(2). Low part not needed.                            */
    const float rcpr_ln_2 = 1.44269504088896338700E+00F;

    /*  Compute the correctly rounded down integer part of |x|/log(2).        */
    const int k = (int)(rcpr_ln_2*x + 0.5F);
    t = (float)k;

    /*  Compute exp(x) via exp(x) = exp(k*ln(2)+r) = 2^k * exp(r).            *
     *  exp(r) is computed via a Taylor series for the function               *
     *  f(r) = r*(exp(r) + 1)/(exp(r) - 1) and solving for exp(r) in          *
     *  terms of f(r).                                                        */
    hi = x - ln_2_hi*t;
    lo = t*ln_2_lo;
    t = hi - lo;

    t256 = (int)(256.0F*t);
    ind = t256 + 177;
    t = t - 0.00390625F*(float)t256;
    r = A0 + t*(A1 + t*A2);

    /*  Compute exp(x) via 2^k * exp(t).                                      */
    return r*tmpl_float_exp_table[ind]*tmpl_Float_Pow2(k);
}
/*  End of tmpl_Float_Exp_Pos_Kernel.                                         */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

/*  Undefine all coefficients in case someone wants to #include this file.    */
#undef A0
#undef A1
#undef A2

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
