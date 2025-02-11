
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
 *                      tmpl_bessel_j1_third_zero_double                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes J1(x) for x near the third zero of J1, j_{1, 3}.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_J1_Third_Zero                                      *
 *  Purpose:                                                                  *
 *      Computes J1(x), the first Bessel function of the first kind, for x    *
 *      near the third zero, j_{1, 3}.                                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      J1_x (double):                                                        *
 *          J1(x) for x near j_{1, 3}.                                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use a rational Remez approximation centered about j_{1, 3}. j_{1, 3}  *
 *      is irrational, so we split it into two doubles to preserve accuracy.  *
 *      To achieve double precision, we use a degree (8, 7) approximation.    *
 *  Error:                                                                    *
 *      Based on 350,000 samples with 8 < x < 11.5.                           *
 *          max relative error: 6.0882168008247195E-16                        *
 *          rms relative error: 1.1207250680268742E-16                        *
 *          max absolute error: 1.5371867654095873E-16                        *
 *          rms absolute error: 2.3877516038566942E-17                        *
 *      Values were computed using mpmath with the precision set to 224       *
 *      bits (octuple precision), significantly higher than double or         *
 *      quadruple precisions.                                                 *
 *  Notes:                                                                    *
 *      Since the expansion is centered about j_{1, 3}, for all representable *
 *      doubles x near j_{1, 3} the relative error, as well as the absolute   *
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
#ifndef TMPL_BESSEL_J1_THIRD_ZERO_DOUBLE_H
#define TMPL_BESSEL_J1_THIRD_ZERO_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-2.4970487705784319764889934019111811069823040637371E-01)
#define A01 (+5.9471317809651860385843839422994003057684006361385E-03)
#define A02 (+3.6123290550347988735988685513072899638803024356973E-02)
#define A03 (-7.8847918571213796992692496833625157308973341556949E-04)
#define A04 (-1.2519547004716792613209336658171025243283985598437E-03)
#define A05 (+2.1874412960787701240856137463909487935561182588006E-05)
#define A06 (+1.5043635217530366760302496004425510204709917831446E-05)
#define A07 (-1.5217776274634306797685136188834886047627786570258E-07)
#define A08 (-6.0585118114850098724196917431622771000982562505626E-08)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+2.5330805904408207562433671362682910066573718307859E-02)
#define B02 (+1.8416730989988873741701437632737287857021722811144E-02)
#define B03 (+4.4582462976525696101515055308863314896154749157525E-04)
#define B04 (+1.6530351162332960238020408312147555232099491748867E-04)
#define B05 (+3.5249871479496522417183357944691094723796166419365E-06)
#define B06 (+8.8446069309460403183752208445407482616410554275501E-07)
#define B07 (+1.3124944180241335729016000288576433145104718606517E-08)
#define B08 (+2.4648296223832791424491904356821760211836501321568E-09)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*B08)))))))

/*  Function for computing J1(x) for x near the third zero of J1, j_{1, 3}.   */
TMPL_STATIC_INLINE
double tmpl_Double_Bessel_J1_Third_Zero(double x)
{
    /*  The high part of j_{1, 3}. Good to 16 decimals.                       */
    const double zhi = +1.017346813506272162896948E+01;

    /*  The low part of j_{1, 3}. j_{1, 3} - zhi - zlo is less than 10^-31.   */
    const double zlo = +4.482162274768888435518742E-16;

    /*  Shift the input so that the expansion is centered about j_{1, 3}.     */
    const double arg = (x - zhi) - zlo;

    /*  Compute the numerator and denominator of the Remez approximation.     */
    const double num = TMPL_NUM_EVAL(arg);
    const double den = TMPL_DEN_EVAL(arg);

    /*  To ensure the function tends to zero as x tends to j_{1, 3}, the      *
     *  Remez approximation was computed so that it is scaled by the argument,*
     *  which is x - j_{1, 3}. For all representable doubles, the relative    *
     *  error near this point is excellent.                                   */
    return arg * num / den;
}
/*  End of tmpl_Double_Bessel_J1_Third_Zero.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
