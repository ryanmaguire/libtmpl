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
 *                              tmpl_sinh_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes hyperbolic sine at single precision.                         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sinh                                                       *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic sine of a number.                             *
 *                                                                            *
 *                     exp(x) - exp(-x)                                       *
 *          sinh(x) =  ----------------                                       *
 *                            2                                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for sinh(x).                          *
 *  Output:                                                                   *
 *      cosh_x (float):                                                       *
 *          The hyperbolic cosine of x.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a float.                   *
 *              tmpl_Float_Sinh_Maclaurin:                                    *
 *                  Computes cosh via a Maclaurin series for small inputs.    *
 *              tmpl_Float_Sinh_Rat_Remez:                                    *
 *                  Computes cosh via a rational Remez approximation.         *
 *      Method:                                                               *
 *      Error:                                                                *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_Float_Exp (tmpl_math.h):                                     *
 *              Computes the exponential of a float.                          *
 *      Method:                                                               *
 *          Compute t = exp(x) and return (t + 1/t)/2.                        *
 *      Error:                                                                *
 *  Notes:                                                                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_MATH_ALGORITHMS macro.            *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 10, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/12/10 (Ryan Maguire):                                                *
 *      Frozen for v1.3.                                                      *
 *  2022/11/03 (Ryan Maguire):                                                *
 *      Migrated to libtmpl from rss_ringoccs. Updated with IEEE-754 method.  *
 ******************************************************************************/

/*  TMPL_USE_MATH_ALGORITHMS macro provided here.                             */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 support. Bit of a speed boost this way.                */
#if TMPL_HAS_IEEE754_FLOAT == 1

/******************************************************************************
 *                              IEEE-754 Version                              *
 ******************************************************************************/

/*  Rational Remez approximation provided here.                               */
#include "auxiliary/tmpl_sinh_rat_remez_float.h"

/*  Maclaurin series to the first few terms given here.                       */
#include "auxiliary/tmpl_sinh_maclaurin_float.h"

/*  Single precision hyperbolic sine (sinh equivalent).                       */
float tmpl_Float_Sinh(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;
    float exp_x, sinh_x;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  +/- NaN returns NaN, for +/- infinity the limit is + infinity.        */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
        return w.r;

    /*  For |x| > log(DBL_MAX) ~= 709, exp will overflow. Return infinity.    */
    if (w.r > 88.02969193111305F)
    {
        const float infinity = TMPL_INFINITYF;

        if (TMPL_FLOAT_IS_NEGATIVE(w))
            return -infinity;

        return infinity;
    }

    /*  For small x, |x| < 1/32, the Maclaurin series is sufficient.          */
    if (w.bits.expo < TMPL_FLOAT_UBIAS - 4U)
    {
        /*  Avoid underflow. For |x| < 2^-57, sinh(x) = x to single precision.*/
        if (TMPL_FLOAT_EXPO_BITS(w) < TMPL_FLOAT_UBIAS - 28U)
            return x;

        /*  Otherwise, use the Maclaurin series.                              */
        return tmpl_Float_Sinh_Maclaurin(w.r);
    }

    /*  For slightly larger x, |x| < 1, use the Pade approximant.             */
    if (w.bits.expo < TMPL_FLOAT_UBIAS)
        return tmpl_Float_Sinh_Rat_Remez(w.r);

    /*  Compute the absolute value by setting the sign bit to zero. sinh is   *
     *  an odd function, sinh(-x) = -sinh(x). Compute for positive x.         */
    w.bits.sign = 0x00U;

    /*  Normal value, not too small, not too big. Compute exp(x).             */
    exp_x = tmpl_Float_Exp_Pos_Kernel(w.r);

    /*  For large x only the e^x term is significant. e^-x is negligible.     */
    if (w.bits.expo > TMPL_FLOAT_UBIAS + 4U)
        sinh_x = 0.5F * exp_x;

    /*  Otherwise, compute sinh(x) via (exp(x) + exp(-x))/2.                  */
    else
        sinh_x = 0.5F * (exp_x - 1.0F/exp_x);

    if (x < 0.0F)
        return -sinh_x;

    return sinh_x;
}
/*  End of tmpl_Float_Sinh.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision hyperbolic sine (sinh equivalent).                       */
float tmpl_Float_Sinh(float x)
{
    /*  The definition of sinh(x) is [exp(x) - exp(-x)]/2, so return this. It *
     *  is computationally faster to compute exp(x) and then exp(-x) via the  *
     *  formula exp(-x) = 1/exp(x). This saves us from computing two          *
     *  exponentials at the cost of an extra division.                        */
    const float exp_x = tmpl_Float_Exp(x);
    const float exp_minus_x = 1.0F / exp_x;

    /*  Compute sinh from the two exponentials and return.                    */
    return 0.5F * (exp_x - exp_minus_x);
}
/*  End of tmpl_Float_Sinh.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
