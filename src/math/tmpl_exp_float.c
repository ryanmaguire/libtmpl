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
 *                               tmpl_exp_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes f(x) = e^x at single precision.                              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Exp                                                        *
 *  Purpose:                                                                  *
 *      Computes the base e exponential of a real number.                     *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      exp_x (float):                                                        *
 *          The exponential of x.                                             *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Exp_Maclaurin (tmpl_math.h):                           *
 *              Computes exp(x) via a Maclaurin series for |x| < 1/16.        *
 *          tmpl_Float_Exp_Remez (tmpl_math.h):                               *
 *              Computes exp(x) via a Remez minimax polynomial for |x| < 1/4. *
 *          tmpl_Float_Exp_Pade (tmpl_math.h):                                *
 *              Computes exp(x) with a Pade approximant for |x| < 1.          *
 *          tmpl_Float_Exp_Neg_Kernel (tmpl_math.h):                          *
 *              Computes exp(x) for negative x with x <= -1.                  *
 *          tmpl_Float_Exp_Pos_Kernel (tmpl_math.h):                          *
 *              Computes exp(x) for positive x with x >= 1.                   *
 *      Method:                                                               *
 *          For very small x, |x| < 1/16, use a Maclaurin series.             *
 *                                                                            *
 *                        infty                                               *
 *                        -----                                               *
 *                        \      1   n                                        *
 *              exp(x) =  /     --- x                                         *
 *                        -----  n!                                           *
 *                        n = 0                                               *
 *                                                                            *
 *          For slightly larger x, |x| < 1/4, use a Minimax polynomial on     *
 *          the interval [-1/4, 1/4]. The coefficients were computed using    *
 *          the Remez exchange algorithm.                                     *
 *                                                                            *
 *          For |x| < 1 use a Pade approximant.                               *
 *                                                                            *
 *                        a0 + a1 x + ... + an x^n                            *
 *              exp(x) ~= ------------------------                            *
 *                         1 + b1 x + ... + bm x^m                            *
 *                                                                            *
 *          For |x| > log(FLT_MAX) ~= 89, use the limit.                      *
 *                                                                            *
 *              exp(+inf) = +inf                                              *
 *              exp(-inf) = 0                                                 *
 *                                                                            *
 *          For x = +/- NaN, return x. Lastly, for 1 <= |x| <= log(FLT_MAX)   *
 *          perform the following:                                            *
 *                                                                            *
 *              exp(x) = exp(k*ln(2) + r)           k integer, |r| < ln(2)/2  *
 *                     = exp(k*ln(2)) * exp(r)                                *
 *                     = 2^k * exp(r)                                         *
 *                     = 2^k * exp(n/128 + t)       n integer, |t| < 1/128    *
 *                     = 2^k * exp(n/128) * exp(t)                            *
 *                                                                            *
 *          2^k can be computed by setting the exponent bit to k, exp(n/128)  *
 *          is computed with a lookup table, and exp(t) is computed using a   *
 *          minimax polynomial on the interval [-1/128, 1/128]. The           *
 *          coefficients were again computed using the Remez exchange         *
 *          algorithm. Note the coefficients for the minimax polynomial for   *
 *          exp on [-1/128, 1/128] differ from the ones on [-1/4, 1/4].       *
 *      Error:                                                                *
 *          Based on 4,489,209,719 samples with -80 < x < 80.                 *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16).                                       *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Is_NaN (tmpl_math.h):                                  *
 *              Determines if a real number is NaN.                           *
 *          tmpl_Float_Is_Inf (tmpl_math.h):                                  *
 *              Determines if a real number is infinity.                      *
 *          tmpl_Float_Abs (tmpl_math.h):                                     *
 *              Computes the absolute value of a real number.                 *
 *          tmpl_Float_Exp_Maclaurin (tmpl_math.h):                           *
 *              Computes exp(x) via a Maclaurin series for |x| < 1/16.        *
 *          tmpl_Float_Exp_Remez (tmpl_math.h):                               *
 *              Computes exp(x) via a Remez minimax polynomial for |x| < 1/4. *
 *          tmpl_Float_Exp_Pade (tmpl_math.h):                                *
 *              Computes exp(x) with a Pade approximant for |x| < 1.          *
 *          tmpl_Float_Exp_Neg_Kernel (tmpl_math.h):                          *
 *              Computes exp(x) for negative x with x <= -1.                  *
 *          tmpl_Float_Exp_Pos_Kernel (tmpl_math.h):                          *
 *              Computes exp(x) for positive x with x >= 1.                   *
 *      Method:                                                               *
 *          Same as IEEE-754 method, but determine the range of x by          *
 *          computing |x| and comparing this value with 1/16, 1/4, etc.       *
 *      Error:                                                                *
 *          Based on 4,489,209,719 samples with -80 < x < 80.                 *
 *              max relative error: 0.0000000000000000e+00                    *
 *              rms relative error: 0.0000000000000000e+00                    *
 *              max absolute error: 0.0000000000000000e+00                    *
 *              rms absolute error: 0.0000000000000000e+00                    *
 *          Values assume 100% accuracy of glibc. Actual error in glibc is    *
 *          around 1 ULP (~2 x 10^-16).                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 30, 2023                                              *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  With IEEE-754 support we can get a bit of a speed boost.                  */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Function for computing e^x at single precision (expf equivalent).         */
float tmpl_Float_Exp(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases, NaN or infinity.                                       */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
    {
        /*  If the input is NaN, so is the output.                            */
        if (TMPL_FLOAT_IS_NAN(w))
            return x;

        /*  The limit of exp(x) as x tends to -infinity is zero.              */
        else if (w.bits.sign)
            return 0.0F;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return x;
    }

    /*  For |x| < 1/4 use one of two polynomial approximations.               */
    if (w.bits.expo < TMPL_FLOAT_UBIAS - 2U)
    {
        /*  For very small x, the Maclaurin series uses less terms.           */
        if (w.bits.expo < TMPL_FLOAT_UBIAS - 4U)
            return tmpl_Float_Exp_Maclaurin(x);

        /*  Otherwise, for |x| < 1/4 the minimax polynomial is accurate.      */
        else
            return tmpl_Float_Exp_Remez(x);
    }

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS)
        return tmpl_Float_Exp_Pade(x);

    /*  Special cases, if |x| > log(FLT_MAX) we will overflow or underflow.   */
    else if (w.r > tmpl_Max_Float_Base_E)
        return TMPL_INFINITYF;

    /*  For large negative numbers, return zero.                              */
    else if (w.r < tmpl_Min_Float_Base_E)
        return 0.0F;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (w.bits.sign)
        return tmpl_Float_Exp_Neg_Kernel(x);
    else
        return tmpl_Float_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Float_Exp.                                                    */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Function for computing e^x at single precision (expf equivalent).         */
float tmpl_Float_Exp(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    float abs_x;

    /*  Special cases, Not-a-Number, return NaN.                              */
    if (tmpl_Float_Is_NaN(x))
        return x;

    /*  Next special cases, +/- infinity.                                     */
    else if (tmpl_Float_Is_Inf(x))
    {
        /*  The limit of exp(x) as x tends to -infinity is 0.                 */
        if (x < 0.0F)
            return 0.0F;

        /*  And the limit as x tends to +infinity is +infinity.               */
        else
            return x;
    }

    /*  Compute |x| to reduce the number of comparisons made. We want to find *
     *  the range |x| lives in and use the appropriate exp function.          */
    abs_x = tmpl_Float_Abs(x);

    /*  For |x| < 1/16 the Maclaurin series is accurate to single precision.  */
    if (abs_x < 0.0625F)
        return tmpl_Float_Exp_Maclaurin(x);

    /*  For |x| < 1/4 the Remez minimax polynomial is fast and accurate.      */
    else if (abs_x < 0.25F)
        return tmpl_Float_Exp_Remez(x);

    /*  For |x| < 1, the Pade approximant is sufficient and much faster than  *
     *  the kernel functions. Use this.                                       */
    else if (abs_x < 1.0F)
        return tmpl_Float_Exp_Pade(x);

    /*  Special cases, if |x| > log(FLT_MAX) we will overflow or underflow.   */
    else if (x > tmpl_Max_Float_Base_E)
        return TMPL_INFINITYF;

    /*  For large negative numbers, return zero.                              */
    else if (x < tmpl_Min_Float_Base_E)
        return 0.0F;

    /*  Non-special case, the argument is not too big and not too small.      */
    if (x < 0.0F)
        return tmpl_Float_Exp_Neg_Kernel(x);
    else
        return tmpl_Float_Exp_Pos_Kernel(x);
}
/*  End of tmpl_Float_Exp.                                                    */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */
