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
 *                      tmpl_bessel_i0_asymptotic_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) at single precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Bessel_I0_Asymptotic                                       *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) for large positive x.      *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (float):                                                         *
 *          The asymptotic expansion of x.                                    *
 *  Called Functions:                                                         *
 *      tmpl_Float_Exp_Pos_Kernel (tmpl_math.h):                              *
 *          Computes exp(x) for x > 1.                                        *
 *      tmpl_Float_Sqrt (tmpl_math.h):                                        *
 *          Computes the square root of a real number.                        *
 *  Method:                                                                   *
 *      Compute the reciprocal of x and use Horner's method to efficiently    *
 *      evaluate the polynomial.                                              *
 *                                                                            *
 *                                 infty                                      *
 *                                 -----                                      *
 *                      exp(x)     \      ((2n+1)!!)^2                        *
 *          I0(x) ~  ------------  /      ------------     x --> infty        *
 *                   sqrt(2 pi x)  -----   n! (8x)^n                          *
 *                                 n = 0                                      *
 *                                                                            *
 *      Use the first 5 terms (0 <= n <= 4) of this expansion to compute.     *
 *  Notes:                                                                    *
 *      Only accurate for large POSITIVE values. For x > 32 this function     *
 *      is accurate to single precision (10^-7 relative error). The closer    *
 *      the input is to 0, the worse the error.                               *
 *                                                                            *
 *      This function can be used for large negative values via:              *
 *          I0(x) ~= tmpl_Float_Bessel_I0_Asymptotic(-x).                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing exp and sqrt functions.                    *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support was not requested.                        */
#if TMPL_USE_INLINE != 1

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01F)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02F)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02F)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01F)

/*  Helper macro for evaluating the polynomial part using Horner's method.    */
#define TMPL_ASYMPTOTIC_EXPANSION(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Function for computing the asymptotic expansion of the Bessel I0 function.*/
float tmpl_Float_Bessel_I0_Asymptotic(float x)
{
    /*  The asymptotic expansion is in terms of 1 / x. Compute this.          */
    const float rcpr_x = 1.0F / x;

    /*  The polynomial is scaled by exp(x) / sqrt(2 pi x). Compute these.     */
    const float exp_x = tmpl_Float_Exp_Pos_Kernel(x);
    const float inv_sqrt_two_pi_x = 1.0F / tmpl_Float_Sqrt(tmpl_Two_Pi_F * x);

    /*  Lastly, evaluate the polynomial using Horner's method.                */
    const float poly = TMPL_ASYMPTOTIC_EXPANSION(rcpr_x);

    /*  Compute the asymptotic expansion and return.                          */
    return exp_x * poly * inv_sqrt_two_pi_x;
}
/*  End of tmpl_Float_Bessel_I0_Asymptotic.                                   */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_ASYMPTOTIC_EXPANSION
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
