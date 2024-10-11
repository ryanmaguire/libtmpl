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
 *                 tmpl_normalized_fresnel_sin_auxiliary_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for large positive inputs.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Sin_Asymptotic                          *
 *  Purpose:                                                                  *
 *      Computes S(x) for large positive inputs.                              *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (float):                                                          *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Mod_2:                                                *
 *              Computes the remainder after division by 2.                   *
 *          tmpl_Float_CosPi:                                                 *
 *              Computes cos(pi t) for a real number t.                       *
 *  Method:                                                                   *
 *      Use the asymptotic expansion for C(x):                                *
 *                                                                            *
 *                 1    1                                                     *
 *          C(x) ~ - - ---- cos(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      To avoid precision loss in the computation of cos(pi/2 x^2) we        *
 *      convert to a double. Since float has a 23-bit mantissa, and double    *
 *      has 52-bits, the entirety of x^2 can be stored in a double. We pass   *
 *      x^2 / 2 to the mod 2 function (at double precision), and then compute *
 *      the cosine of this (at single precision).                             *
 *  Notes:                                                                    *
 *      This function assumes the input is greater than 2^7.                  *
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
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_ASYMPTOTIC_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_SIN_ASYMPTOTIC_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  The denominator of the asymptotic expansion is scaled by pi.              */
#define TMPL_ONE_PI (+3.14159265358979323846264338327950288419716939E+00F)

/*  Computes cos(pi t) at single precision.                                   */
extern float tmpl_Float_CosPi(float t);

/*  Computes the remainder of a double after division by 2.                   */
extern double tmpl_Double_Mod_2(double t);

/*  Function for computing the normalized Fresnel sine of a large input.      */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Sin_Asymptotic(float x)
{
    /*  Float has a 23-bit mantissa, double has 52 bits. This means for every *
     *  representable float x, x^2 is perfectly representable once converted  *
     *  to a double. Do this and compute sin(pi/2 x^2) this way.              */
    const double x_double = (double)x;

    /*  The scale factor for the asymptotic expansion. For x > 2^7 we only    *
     *  need the first term of the approximation.                             */
    const float t = 1.0F / (TMPL_ONE_PI * x);

    /*  Compute cos(pi/2 x^2) using the promoted double. Since cos(pi t) is   *
     *  periodic with period 2, we can reduce the argument first.             */
    const double cos_arg = tmpl_Double_Mod_2(0.5 * x_double * x_double);
    const float cos_val = tmpl_Float_CosPi((float)cos_arg);

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5F - t * cos_val;
}
/*  End of tmpl_Float_Normalized_Fresnel_Sin_Asymptotic.                      */

/*  Undefine everything in case someone wants to include this file.           */
#undef TMPL_ONE_PI

#endif
/*  End of include guard.                                                     */
