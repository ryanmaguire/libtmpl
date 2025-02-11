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
 *                     tmpl_bessel_j1_first_zero_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes J1(x) for x near the first zero of J1, j_{1, 1}.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_J1_First_Zero                                      *
 *  Purpose:                                                                  *
 *      Computes J1(x), the first Bessel function of the first kind, for x    *
 *      near the first zero, j_{1, 1}.                                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      J1_x (double):                                                        *
 *          J1(x) for x near j_{1, 1}.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a rational Remez approximation centered about j_{1, 1}. j_{1, 1}  *
 *      is irrational, so we split it into two doubles to preserve accuracy.  *
 *      To achieve double precision, we use a degree (8, 7) approximation.    *
 *  Error:                                                                    *
 *      Based on 300,000 samples with 2 < x < 5.                              *
 *          max relative error: 4.4916822937578210E-16                        *
 *          rms relative error: 1.0839471736657227E-16                        *
 *          max absolute error: 2.1521948511155610E-16                        *
 *          rms absolute error: 3.4430613378791660E-17                        *
 *      Values were computed using mpmath with the precision set to 224       *
 *      bits (octuple precision), significantly higher than double or         *
 *      quadruple precisions.                                                 *
 *  Notes:                                                                    *
 *      Since the expansion is centered about j_{1, 1}, for all representable *
 *      doubles x near j_{1, 1} the relative error, as well as the absolute   *
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
#ifndef TMPL_BESSEL_J1_FIRST_ZERO_DOUBLE_H
#define TMPL_BESSEL_J1_FIRST_ZERO_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.0275939570255296868146282830931324445104611953398E-01)
#define A01 (+4.0075914863769931250382220259424560100072179279813E-02)
#define A02 (+4.8394186668677401845659233370642210255207563089505E-02)
#define A03 (-2.8667034362033312030285617941183944578925403513268E-03)
#define A04 (-1.5342894476833611858567207388955352139220411266624E-03)
#define A05 (+5.2646204859899928803756712929615245799830911674763E-05)
#define A06 (+1.8629016635933130938262271630759047485536301476590E-05)
#define A07 (-2.9750019886308761168555630915842920896374146211138E-07)
#define A08 (-8.2333671683904448304026054199996940480216340614823E-08)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+3.0986815270783209065208926916254862418237234504429E-02)
#define B02 (+1.6498199962463525125352864705204931479110373520032E-02)
#define B03 (+5.1913266896335127017504835198376302539556543496212E-04)
#define B04 (+1.2196091586649651640061254208326712516767978494012E-04)
#define B05 (+3.7280365062300944724446152961787901684393685894248E-06)
#define B06 (+4.2303870907338101684960809254035102938852968228768E-07)
#define B07 (+1.1126878660835891548457309280335779427917198190484E-08)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))

/*  Function for computing J1(x) for x near the first zero of J1, j_{1, 1}.   */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_First_Zero(double x)
{
    /*  The high part of j_{1, 1}. Good to 16 decimals.                       */
    const double zhi = +3.831705970207512468306277E+00;

    /*  The low part of j_{1, 1}. j_{1, 1} - zhi - zlo is less than 10^-31.   */
    const double zlo = -1.526918409008806685673183E-16;

    /*  Shift the input so that the expansion is centered about j_{1, 1}.     */
    const double arg = (x - zhi) - zlo;

    /*  Compute the numerator and denominator of the Remez approximation.     */
    const double num = TMPL_NUM_EVAL(arg);
    const double den = TMPL_DEN_EVAL(arg);

    /*  To ensure the function tends to zero as x tends to j_{1, 1}, the      *
     *  Remez approximation was computed so that it is scaled by the argument,*
     *  which is x - j_{1, 1}. For all representable doubles, the relative    *
     *  error near this point is excellent.                                   */
    return arg * num / den;
}
/*  End of tmpl_Double_Bessel_J1_First_Zero.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
