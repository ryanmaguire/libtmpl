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
 *                     tmpl_bessel_j1_fourth_zero_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes J1(x) for x near the fourth zero of J1, j_{1, 4}.            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_J1_Fourth_Zero                                     *
 *  Purpose:                                                                  *
 *      Computes J1(x), the first Bessel function of the first kind, for x    *
 *      near the fourth zero, j_{1, 4}.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      J1_x (double):                                                        *
 *          J1(x) for x near j_{1, 4}.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a rational Remez approximation centered about j_{1, 4}. j_{1, 4}  *
 *      is irrational, so we split it into two doubles to preserve accuracy.  *
 *      To achieve double precision, we use a degree (8, 7) approximation.    *
 *  Error:                                                                    *
 *      Based on 350,000 samples with 11.5 < x < 15.                          *
 *          max relative error: 5.9760797053348367E-16                        *
 *          rms relative error: 1.3635256810934322E-16                        *
 *          max absolute error: 1.3690834687693715E-16                        *
 *          rms absolute error: 2.4006310664990920E-17                        *
 *      Values were computed using mpmath with the precision set to 224       *
 *      bits (octuple precision), significantly higher than double or         *
 *      quadruple precisions.                                                 *
 *  Notes:                                                                    *
 *      Since the expansion is centered about j_{1, 4}, for all representable *
 *      doubles x near j_{1, 4} the relative error, as well as the absolute   *
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
#ifndef TMPL_BESSEL_J1_FOURTH_ZERO_DOUBLE_H
#define TMPL_BESSEL_J1_FOURTH_ZERO_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+2.1835940724787296263917835788278374376670018169276E-01)
#define A01 (-3.0551317580521181823496723779901801668979722971648E-03)
#define A02 (-3.1891505589423626871625202110940206860321043610976E-02)
#define A03 (+4.1529226065726582045971752222484144826837754783463E-04)
#define A04 (+1.1274813918681650025831942221616706184297738566394E-03)
#define A05 (-1.2185526658669038295384880878261050615522103585140E-05)
#define A06 (-1.3907779987718869206686648446759817771572447085962E-05)
#define A07 (+9.4019529160937196165956199879207238389275326107407E-08)
#define A08 (+5.6765121575720115005942599424974890700956486422634E-08)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+2.3535837043152866021019780922700839288196852265903E-02)
#define B02 (+1.8682804533251328392010482608527474753247456456953E-02)
#define B03 (+4.1620918556809266087332811645897056923811914223999E-04)
#define B04 (+1.7127495701799434862824694057520894750371062158693E-04)
#define B05 (+3.3232887112662583850965257751858184214451206647931E-06)
#define B06 (+9.4809136204930156632416781142740306040530158931035E-07)
#define B07 (+1.2634410083908511082175822309931518939414946164684E-08)
#define B08 (+2.8114930335114778108213580376422832687468274519644E-09)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*B08)))))))

/*  Function for computing J1(x) for x near the fourth zero of J1, j_{1, 4}.  */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Fourth_Zero(double x)
{
    /*  The high part of j_{1, 4}. Good to 16 decimals.                       */
    const double zhi = +1.332369193631422277235288E+01;

    /*  The low part of j_{1, 4}. j_{1, 4} - zhi - zlo is less than 10^-31.   */
    const double zlo = +2.600408064718813132531965E-16;

    /*  Shift the input so that the expansion is centered about j_{1, 4}.     */
    const double arg = (x - zhi) - zlo;

    /*  Compute the numerator and denominator of the Remez approximation.     */
    const double num = TMPL_NUM_EVAL(arg);
    const double den = TMPL_DEN_EVAL(arg);

    /*  To ensure the function tends to zero as x tends to j_{1, 4}, the      *
     *  Remez approximation was computed so that it is scaled by the argument,*
     *  which is x - j_{1, 4}. For all representable doubles, the relative    *
     *  error near this point is excellent.                                   */
    return arg * num / den;
}
/*  End of tmpl_Double_Bessel_J1_Fourth_Zero.                                 */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
