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
 *                 tmpl_normalized_fresnel_cos_auxiliary_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Cos_Auxiliary                           *
 *  Purpose:                                                                  *
 *      Computes C(x) for large positive inputs.                              *
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
 *      We shift the interval [4, infty) via:                                 *
 *                                                                            *
 *          t = 4 / x                                                         *
 *                                                                            *
 *      And compute rational Remez approximations for f(t) and g(t). We must  *
 *      be careful when squaring. Naively squaring a large number may lead to *
 *      precision loss in the calculation of sin(pi/2 x^2) and cos(pi/2 x^2). *
 *      Since float has a 23-bit mantissa, and double has 52-bits, for every  *
 *      representable float x, the square x^2 is perfectly representable by a *
 *      double. We convert and perform the sin / cos computations with this.  *
 *  Notes:                                                                    *
 *      This function assumes the input is between 4 and 2^7.                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Computes sin(pi t) and cos(pi t) at single precision.                     */
extern void tmpl_Float_SinCosPi(float t, float *sin_t, float *cos_t);

/*  Computes the remainder of a double after division by 2.                   */
extern double tmpl_Double_Mod_2(double t);

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (+7.3447660845709196929708841858553076854324627302765E-08F)
#define A01 (+7.9575105623629205065261086892669980210540522566726E-02F)
#define A02 (-9.7037810984755525839486287782996115842670377970747E-02F)
#define A03 (+3.5924467666903423540796920123567776791493498285802E-02F)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (-1.2196179926254228181288760314730861775190785656427E+00F)
#define B02 (+4.5188824782911418448242727616484518811887083181770E-01F)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+2.9324187863659231085654700638454232151482114358585E-08F)
#define C01 (-1.2412787022606275166640023231313141502562936645653E-06F)
#define C02 (+1.2173908912304056327261127292325331653509028947236E-05F)
#define C03 (+1.5371563043091155396661385383082228690395665320383E-03F)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define D01 (-4.8489039969553784876915628632774006272172005213782E-02F)
#define D02 (+3.2058335100774952999749638363717831022209892920123E-02F)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*B02)

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) C00 + z*(C01 + z*(C02 + z*C03))

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) D00 + z*(D01 + z*D02)

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Auxiliary(float x)
{
    /*  Float has a 23-bit mantissa, double has 52 bits. This means for every *
     *  representable float x, x^2 is perfectly representable once converted  *
     *  to a double. Do this and compute sin(pi/2 x^2) this way.              */
    const double x_double = (double)x;

    /*  Compute sin and cos using the promoted double. Since sin(pi t) and    *
     *  cos(pi t) periodic with period 2, we can reduce the argument first.   */
    const double arg = tmpl_Double_Mod_2(0.5 * x_double * x_double);

    /*  The auxiliary functions f and g are computed by shifting the interval *
     *  [4, infty) using the following formula.                               */
    const float t = 4.0F / x;

    /*  Compute the auxiliary function f using a rational Remez approximation.*/
    const float fn = TMPL_POLYA_EVAL(t);
    const float fd = TMPL_POLYB_EVAL(t);
    const float f = fn / fd;

    /*  Perform the same calculation for the auxiliary function g.            */
    const float gn = TMPL_POLYC_EVAL(t);
    const float gd = TMPL_POLYD_EVAL(t);
    const float g = gn / gd;

    /*  Variables for storing the values of sine and cosine.                  */
    float cos_x, sin_x;

    /*  Compute sin and cos simultaneously.                                   */
    tmpl_Float_SinCosPi((float)arg, &sin_x, &cos_x);

    /*  With the auxiliary functions computed, we can compute C(x).           */
    return 0.5F + (f*sin_x - g*cos_x);
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Auxiliary.                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
