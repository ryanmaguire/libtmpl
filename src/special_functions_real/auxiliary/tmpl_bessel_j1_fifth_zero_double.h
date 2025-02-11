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
 *                     tmpl_bessel_j1_fifth_zero_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes J1(x) for x near the fifth zero of J1, j_{1, 5}.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_J1_Fifth_Zero                                      *
 *  Purpose:                                                                  *
 *      Computes J1(x), the first Bessel function of the first kind, for x    *
 *      near the fifth zero, j_{1, 5}.                                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      J1_x (double):                                                        *
 *          J1(x) for x near j_{1, 5}.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a rational Remez approximation centered about j_{1, 5}. j_{1, 5}  *
 *      is irrational, so we split it into two doubles to preserve accuracy.  *
 *      To achieve double precision, we use a degree (8, 7) approximation.    *
 *  Error:                                                                    *
 *      Based on 300,000 samples with 15 < x < 18.                            *
 *          max relative error: 4.8837918812598380E-16                        *
 *          rms relative error: 1.1939423663384138E-16                        *
 *          max absolute error: 8.2937344400057030E-17                        *
 *          rms absolute error: 1.6282675854926280E-17                        *
 *      Values were computed using mpmath with the precision set to 224       *
 *      bits (octuple precision), significantly higher than double or         *
 *      quadruple precisions.                                                 *
 *  Notes:                                                                    *
 *      Since the expansion is centered about j_{1, 5}, for all representable *
 *      doubles x near j_{1, 5} the relative error, as well as the absolute   *
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
#ifndef TMPL_BESSEL_J1_FIFTH_ZERO_DOUBLE_H
#define TMPL_BESSEL_J1_FIFTH_ZERO_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-1.9646537146865718666310620746831023265349856948290E-01)
#define A01 (+2.4817083492397433669920388248115276872902785287589E-04)
#define A02 (+2.9219057399859321363334733356616269406012392547084E-02)
#define A03 (-3.0297076712124111265948039365436434423900088905861E-05)
#define A04 (-1.0850712656569231985887211678599422134869448937625E-03)
#define A05 (+7.8274351065057126910722979447884097227712961048105E-07)
#define A06 (+1.4672326663597428644116265151305355294606928787281E-05)
#define A07 (-4.9856932848155910452027981747802205118684527116014E-09)
#define A08 (-6.9416558890647464985614603074825372767691792469908E-08)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+2.9093887277921147596764803658470503737760972983611E-02)
#define B02 (+1.6983066625617956281265741606109529959919009718867E-02)
#define B03 (+5.1751645544798143681827920603723770769928290580546E-04)
#define B04 (+1.3027719041928805892459026477189074717759447774715E-04)
#define B05 (+4.1759767486180208423434101533756737022144508022688E-06)
#define B06 (+4.7544885054101567717337329742646823813765161430803E-07)
#define B07 (+1.6197787110629037209933657706828505514884616307114E-08)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))

/*  Function for computing J1(x) for x near the fifth zero of J1, j_{1, 5}.   */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Fifth_Zero(double x)
{
    /*  The high part of j_{1, 5}. Good to 16 decimals.                       */
    const double zhi = +1.647063005087763443157201E+01;

    /*  The low part of j_{1, 5}. j_{1, 5} - zhi - zlo is less than 10^-31.   */
    const double zlo = -1.619019544798128039602757E-15;

    /*  Shift the input so that the expansion is centered about j_{1, 5}.     */
    const double arg = (x - zhi) - zlo;

    /*  Compute the numerator and denominator of the Remez approximation.     */
    const double num = TMPL_NUM_EVAL(arg);
    const double den = TMPL_DEN_EVAL(arg);

    /*  To ensure the function tends to zero as x tends to j_{1, 5}, the      *
     *  Remez approximation was computed so that it is scaled by the argument,*
     *  which is x - j_{1, 5}. For all representable doubles, the relative    *
     *  error near this point is excellent.                                   */
    return arg * num / den;
}
/*  End of tmpl_Double_Bessel_J1_Fifth_Zero.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
