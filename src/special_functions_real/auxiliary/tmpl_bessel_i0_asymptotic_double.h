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
 *                      tmpl_bessel_i0_asymptotic_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) at double precision.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_I0_Asymptotic                                      *
 *  Purpose:                                                                  *
 *      Computes the asymptotic expansion of I0(x) for large positive x.      *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (double):                                                        *
 *          The asymptotic expansion of I0 at x.                              *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Exp_Pos_Kernel:                                       *
 *              Computes exp(x) for x > 1.                                    *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a real number.                    *
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
 *      Use the first 11 terms (0 <= n <= 10) of this expansion to compute.   *
 *  Notes:                                                                    *
 *      Only accurate for large POSITIVE values. For x > 64, this function    *
 *      is accurate to double precision (10^-16 relative error). The closer   *
 *      the input is to 0, the worse the error.                               *
 *                                                                            *
 *      This function can be used for large negative values via:              *
 *          I0(x) ~= tmpl_Double_Bessel_I0_Asymptotic(-x).                    *
 *                                                                            *
 *      This function has been replaced by tmpl_Double_Bessel_I0_Large, which *
 *      uses a Remez polynomial in terms of 1 / x. This allows identical      *
 *      precision while uses fewer terms in the polynomial.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing exp and sqrt functions.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/25: Ryan Maguire                                                  *
 *      Changed src/special_functions_real/tmpl_bessel_i0_asymptotic_double.c *
 *      to include this file.                                                 *
 *  2023/10/05: Ryan Maguire                                                  *
 *      Replaced this function with a Remez approximation in the main I0      *
 *      routine.                                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_ASYMPTOTIC_DOUBLE_H
#define TMPL_BESSEL_I0_ASYMPTOTIC_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the asymptotic expansion.                                */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+1.2500000000000000000000000000000000000000000000000E-01)
#define A02 (+7.0312500000000000000000000000000000000000000000000E-02)
#define A03 (+7.3242187500000000000000000000000000000000000000000E-02)
#define A04 (+1.1215209960937500000000000000000000000000000000000E-01)
#define A05 (+2.2710800170898437500000000000000000000000000000000E-01)
#define A06 (+5.7250142097473144531250000000000000000000000000000E-01)
#define A07 (+1.7277275025844573974609375000000000000000000000000E+00)
#define A08 (+6.0740420012734830379486083984375000000000000000000E+00)
#define A09 (+2.4380529699556063860654830932617187500000000000000E+01)
#define A10 (+1.1001714026924673817120492458343505859375000000000E+02)

/*  Helper macro for evaluating the polynomial part using Horner's method.    */
#define TMPL_ASYMPTOTIC_EXPANSION(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*A10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  The value 1 / (2 pi), well beyond double precision.                       */
#define RCPR_TWO_PI (+1.591549430918953357688837633725143620345E-01)

/*  Function for computing the asymptotic expansion of the Bessel I0 function.*/
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_I0_Asymptotic(double x)
{
    /*  The asymptotic expansion is in terms of 1 / x. Compute this.          */
    const double rcpr_x = 1.0 / x;

    /*  The polynomial is scaled by exp(x) / sqrt(2 pi x). Compute these.     */
    const double exp_x = tmpl_Double_Exp_Pos_Kernel(x);
    const double inv_sqrt_two_pi_x = tmpl_Double_Sqrt(RCPR_TWO_PI * rcpr_x);

    /*  Lastly, evaluate the polynomial using Horner's method.                */
    const double poly = TMPL_ASYMPTOTIC_EXPANSION(rcpr_x);

    /*  Compute the asymptotic expansion and return.                          */
    return exp_x * poly * inv_sqrt_two_pi_x;
}
/*  End of tmpl_Double_Bessel_I0_Asymptotic.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_ASYMPTOTIC_EXPANSION
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
#undef RCPR_TWO_PI

#endif
/*  End of include guard.                                                     */
