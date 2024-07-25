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
 *             tmpl_normalized_fresnel_cos_auxiliary_small_float              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for mid-sized inputs.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Cos_Auxiliary_Small                     *
 *  Purpose:                                                                  *
 *      Computes C(x) for 2 <= x < 4.                                         *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (float):                                                          *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Mod_2:                                                *
 *              Computes the remainder after division by 2.                   *
 *          tmpl_Float_SinCosPi:                                              *
 *              Simultaneously computes sin(pi x) and cos(pi x).              *
 *  Method:                                                                   *
 *      The normalized Fresnel functions are asymptotic to 1/2 as x tends to  *
 *      positive infinity. They also have highly oscillatory behavior and can *
 *      be approximated using cosine and sine. That is, we may use auxiliary  *
 *      functions f and g to write:                                           *
 *                                                                            *
 *          C(x) = 0.5 + f(x) cos(pi/2 x^2) - g(x) sin(pi/2 x^2)              *
 *          S(x) = 0.5 - f(x) sin(pi/2 x^2) - g(x) cos(pi/2 x^2)              *
 *                                                                            *
 *      Solving for f and g gives us the following:                           *
 *                                                                            *
 *          f(x) = sin(pi/2 x^2) (C(x) - 0.5) - cos(pi/2 x^2) (S(x) - 0.5)    *
 *          g(x) = -sin(pi/2 x^2) (S(x) - 0.5) - cos(pi/2 x^2) (C(x) - 0.5)   *
 *                                                                            *
 *      We shift the interval [4, infty):                                     *
 *                                                                            *
 *          t = 1 / x                                                         *
 *                                                                            *
 *      And compute rational Remez approximations for f(t) and g(t). We must  *
 *      be careful when squaring. Naively squaring a large number may lead    *
 *      precision loss in the calculation of sin(pi/2 x^2) and cos(pi/2 x^2). *
 *      We convert to a double for some of the intermediate steps to avoid    *
 *      such errors.                                                          *
 *  Notes:                                                                    *
 *      This function assumes the input is between 2 and 4.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 24, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_SMALL_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_SMALL_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Computes sin(pi t) and cos(pi t) at single precision.                     */
extern void tmpl_Float_SinCosPi(float t, float *sin_t, float *cos_t);

/*  Computes the remainder of a double after division by 2.                   */
extern double tmpl_Double_Mod_2(double t);

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.5246280421910551878368225585204082614852964232248E-04F)
#define A01 (+3.1609653241314679857283357836150343739921097859062E-01F)
#define A02 (-4.9623331840301738262354883540181548632010550808145E-01F)
#define A03 (+3.3098392167588884276231638901226486916051539529096E-01F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-1.5965639622977909738889451915430533331550459849930E+00F)
#define B02 (+1.1221940714096073759406009822681650387256187326180E+00F)

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define C00 (-2.4396874784627198132005931327540722310053184512274E-05F)
#define C01 (+1.4676320705970029295603754665410727533417990698878E-04F)
#define C02 (+1.5245048902221946247159304582189880370421596905789E-03F)
#define C03 (+8.2909288144704840406411074152712650884087132659313E-02F)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define D01 (-7.0655337204858631339156855315997334162929299457167E-01F)
#define D02 (+1.0886493929373154383903053885964644577967820375110E+00F)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*B02)

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) C00 + z*(C01 + z*(C02 + z*C03))

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) D00 + z*(D01 + z*D02)

/*  Function for computing the normalized Fresnel cosine for 2 <= x < 4.      */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Auxiliary_Small(float x)
{
    /*  Float has a 23-bit mantissa, double has 52 bits. This means for every *
     *  representable float x, x^2 is perfectly representable once converted  *
     *  to a double. Do this and compute sin(pi/2 x^2) this way.              */
    const double x_double = (double)x;

    /*  Compute sin(pi/2 x^2) using the promoted double. Since sin(pi t) is   *
     *  periodic with period 2, we can reduce the argument first.             */
    const double arg = tmpl_Double_Mod_2(0.5 * x_double * x_double);

    /*  The auxiliary functions f and g are computed by shifting the interval *
     *  [2, 4) using the following formula.                                   */
    const float t = 1.0F / x;

    /*  Compute the auxiliary function f using a rational Remez approximation.*/
    const float fn = TMPL_POLYA_EVAL(t);
    const float fd = TMPL_POLYB_EVAL(t);
    const float f = fn / fd;

    /*  Perform the same calculation for the auxiliary function g.            */
    const float gn = TMPL_POLYC_EVAL(t);
    const float gd = TMPL_POLYD_EVAL(t);
    const float g = gn / gd;

    /*  Variables for storing the values of sine and cosine.                  */
    float sin_arg, cos_arg;

    /*  Compute sin and cos simultaneously.                                   */
    tmpl_Float_SinCosPi((float)arg, &sin_arg, &cos_arg);

    /*  With the auxiliary functions computed, we can compute C(x).           */
    return 0.5F + (f*sin_arg - g*cos_arg);
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Auxiliary_Small.                 */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
