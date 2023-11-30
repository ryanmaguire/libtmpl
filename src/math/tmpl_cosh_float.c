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
 *                              tmpl_cosh_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes hyperbolic cosine at single precision.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Cosh                                                       *
 *  Purpose:                                                                  *
 *      Computes the hyperbolic cosine of a number.                           *
 *                                                                            *
 *                     exp(x) + exp(-x)                                       *
 *          cosh(x) =  ----------------                                       *
 *                            2                                               *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number, the argument for cosh(x).                          *
 *  Output:                                                                   *
 *      cosh_x (float):                                                       *
 *          The hyperbolic cosine of x.                                       *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Abs:                                               *
 *                  Computes the absolute value of a float.                   *
 *              tmpl_Float_Cosh_Maclaurin:                                    *
 *                  Computes cosh via a Maclaurin series for small inputs.    *
 *              tmpl_Float_Cosh_Pade:                                         *
 *                  Computes cosh via a Pade approximation.                   *
 *      Method:                                                               *
 *      Error:                                                                *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          tmpl_math.h:                                                      *
 *              tmpl_Float_Exp:                                               *
 *                  Computes the exponential of a float.                      *
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

/*  Pade approximation provided here.                                         */
#include "auxiliary/tmpl_cosh_pade_float.h"

/*  Maclaurin series to the first few terms given here.                       */
#include "auxiliary/tmpl_cosh_maclaurin_float.h"

/*  Single precision hyperbolic cosine (coshf equivalent).                    */
float tmpl_Float_Cosh(float x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Float w;
    float exp_x;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Compute the absolute value by setting the sign bit to zero. cosh is   *
     *  an even function, cosh(-x) = cosh(x). Compute for positive x.         */
    w.bits.sign = 0x00U;

    /*  +/- NaN returns NaN, for +/- infinity the limit is + infinity.        */
    if (TMPL_FLOAT_IS_NAN_OR_INF(w))
        return w.r;

    /*  For |x| > log(FLT_MAX) ~= 88, exp will overflow. Return infinity.    */
    else if (w.r > 88.02969193111305F)
        return TMPL_INFINITYF;

    /*  For small x, |x| < 1/16, the Maclaurin series is sufficient.          */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS - 4U)
        return tmpl_Float_Cosh_Maclaurin(w.r);

    /*  For slightly larger x, |x| < 1, use the Pade approximant.             */
    else if (w.bits.expo < TMPL_FLOAT_UBIAS)
        return tmpl_Float_Cosh_Pade(w.r);

    /*  Normal value, not too small, not too big. Compute exp(x).             */
    exp_x = tmpl_Float_Exp_Pos_Kernel(w.r);

    /*  For large x only the e^x term is significant. e^-x is negligible.     */
    if (w.bits.expo > TMPL_FLOAT_UBIAS + 4U)
        return 0.5F*exp_x;

    /*  Otherwise, compute cosh(x) via (exp(x) + exp(-x))/2.                  */
    return 0.5F*(exp_x + 1.0F/exp_x);
}
/*  End of tmpl_Float_Cosh.                                                   */

#else
/*  Else for #if TMPL_HAS_IEEE754_FLOAT == 1.                                 */

/******************************************************************************
 *                              Portable Version                              *
 ******************************************************************************/

/*  Single precision hyperbolic cosine (cosh equivalent).                     */
float tmpl_Float_Cosh(float x)
{
    /*  The definition of cosh(x) is [exp(x) + exp(-x)]/2, so return this. It *
     *  is computationally faster to compute exp(x) and then exp(-x) via the  *
     *  formula exp(-x) = 1/exp(x). This saves us from computing two          *
     *  exponentials at the cost of an extra division.                        */
    const float exp_x = tmpl_Float_Exp(x);
    const float exp_minus_x = 1.0F / exp_x;

    /*  Compute cosh from the two exponentials and return.                    */
    return 0.5F*(exp_x + exp_minus_x);
}
/*  End of tmpl_Float_Cosh.                                                   */

#endif
/*  End of #if TMPL_HAS_IEEE754_FLOAT == 1.                                   */

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
