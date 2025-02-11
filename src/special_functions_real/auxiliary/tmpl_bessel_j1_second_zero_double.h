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
 *                     tmpl_bessel_j1_second_zero_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes J1(x) for x near the second zero of J1, j_{1, 2}.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_J1_Second_Zero                                     *
 *  Purpose:                                                                  *
 *      Computes J1(x), the first Bessel function of the first kind, for x    *
 *      near the second zero, j_{1, 2}.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      J1_x (double):                                                        *
 *          J1(x) for x near j_{1, 2}.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a rational Remez approximation centered about j_{1, 2}. j_{1, 2}  *
 *      is irrational, so we split it into two doubles to preserve accuracy.  *
 *      To achieve double precision, we use a degree (8, 7) approximation.    *
 *  Error:                                                                    *
 *      Based on 300,000 samples with 5 < x < 8.                              *
 *          max relative error: 6.7172532111176170E-16                        *
 *          rms relative error: 1.5227880201191481E-16                        *
 *          max absolute error: 2.2375795579310753E-16                        *
 *          rms absolute error: 3.7671383617060384E-17                        *
 *      Values were computed using mpmath with the precision set to 224       *
 *      bits (octuple precision), significantly higher than double or         *
 *      quadruple precisions.                                                 *
 *  Notes:                                                                    *
 *      Since the expansion is centered about j_{1, 2}, for all representable *
 *      doubles x near j_{1, 2} the relative error, as well as the absolute   *
 *      error, is very good.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_J1_SECOND_ZERO_DOUBLE_H
#define TMPL_BESSEL_J1_SECOND_ZERO_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+3.0011575252613256611000514563201850401904206783705E-01)
#define A01 (-1.3966960736056833529660200317075112947047151530845E-02)
#define A02 (-4.2554387103115728818651600358092928553343343895081E-02)
#define A03 (+1.7281327381821346068455346918767254668024163218908E-03)
#define A04 (+1.4373703814828303776357548368088074422368581776783E-03)
#define A05 (-4.1320117722953718768291536344112465361064863034503E-05)
#define A06 (-1.7835355177731267450397549239318634863636459920841E-05)
#define A07 (+2.7672712526232187446352408414655218074206815929184E-07)
#define A08 (+7.9699291944395083124425708524928621801156289531701E-08)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+2.4731297876936438173694174993277836368767958218071E-02)
#define B02 (+1.6477225198421956378271917530379978496556211808890E-02)
#define B03 (+3.7291209740746555157219131514627016855743768690934E-04)
#define B04 (+1.2090840401411335987673546098969860644472769002818E-04)
#define B05 (+2.1237228362595819448146991558256294136858979662683E-06)
#define B06 (+4.1013124017175469970990246304385323643012025356031E-07)
#define B07 (+2.3763469198526631635374425914269652535147779448801E-09)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))

/*  Function for computing J1(x) for x near the second zero of J1, j_{1, 2}.  */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Second_Zero(double x)
{
    /*  The high part of j_{1, 2}. Good to 16 decimals.                       */
    const double zhi = +7.015586669815618847678707E+00;

    /*  The low part of j_{1, 2}. j_{1, 2} - zhi - zlo is less than 10^-31.   */
    const double zlo = -9.414165653410388907504424E-17;

    /*  Shift the input so that the expansion is centered about j_{1, 2}.     */
    const double arg = (x - zhi) - zlo;

    /*  Compute the numerator and denominator of the Remez approximation.     */
    const double num = TMPL_NUM_EVAL(arg);
    const double den = TMPL_DEN_EVAL(arg);

    /*  To ensure the function tends to zero as x tends to j_{1, 2}, the      *
     *  Remez approximation was computed so that it is scaled by the argument,*
     *  which is x - j_{1, 2}. For all representable doubles, the relative    *
     *  error near this point is excellent.                                   */
    return arg * num / den;
}
/*  End of tmpl_Double_Bessel_J1_Second_Zero.                                 */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
