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
 *                tmpl_normalized_fresnel_cos_asymptotic_float                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Cos_Asymptotic                          *
 *  Purpose:                                                                  *
 *      Computes C(x) for large positive inputs.                              *
 *  Arguments:                                                                *
 *      x (const float):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      fresnel_cos_x (float):                                                *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_Mod_2:                                                *
 *              Computes the remainder after division by 2.                   *
 *          tmpl_Float_SinPi:                                                 *
 *              Computes sin(pi t) for a real number t.                       *
 *  Method:                                                                   *
 *      Use the asymptotic expansion for C(x):                                *
 *                                                                            *
 *                 1    1                                                     *
 *          C(x) ~ - + ---- sin(pi/2 x^2)                                     *
 *                 2   pi x                                                   *
 *                                                                            *
 *      To avoid precision loss in the computation of sin(pi/2 x^2) we        *
 *      convert to a double. Since float has a 23-bit mantissa, and double    *
 *      has 52-bits, the entirety of x^2 can be stored in a double. We pass   *
 *      x^2 / 2 to the mod 2 function (at double precision), and then compute *
 *      the sine of this (at single precision).                               *
 *  Notes:                                                                    *
 *      1.) This function assumes the input is greater than 2^7.              *
 *                                                                            *
 *      2.) Do not use this function for arguments greater than 2^23. The     *
 *          computation of sin(pi x^2) is redundant since the final           *
 *          expression is divided by pi x, meaning the output is 1 / 2 to     *
 *          single precision. For extremely large inputs, simply return 1 / 2.*
 *                                                                            *
 *      3.) There are no checks for NaN or infinity.                          *
 *                                                                            *
 *      4.) There are no checks for negative numbers. This function assumes   *
 *          the input is positive.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 *  2.) tmpl_cast.h:                                                          *
 *          Header file providing the TMPL_CAST macro.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_COS_ASYMPTOTIC_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Helper macro for casting with C vs. C++ compatibility.                    */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  The denominator of the asymptotic expansion is scaled by pi.              */
extern const float tmpl_float_pi;

/*  Computes sin(pi t) at single precision.                                   */
extern float tmpl_Float_SinPi(const float t);

/*  Computes the remainder of a double after division by 2.                   */
extern double tmpl_Double_Mod_2(const double t);

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Cos_Asymptotic(const float x)
{
    /*  Float has a 23-bit mantissa, double has 52 bits. This means for every *
     *  representable float x, x^2 is perfectly representable once converted  *
     *  to a double. Do this and compute sin(pi/2 x^2) this way.              */
    const double x_double = TMPL_CAST(x, double);

    /*  The scale factor for the asymptotic expansion. For x > 2^7 we only    *
     *  need the first term of the approximation.                             */
    const float t = 1.0F / (tmpl_float_pi * x);

    /*  Compute sin(pi/2 x^2) using the promoted double. Since sin(pi t) is   *
     *  periodic with period 2, we can reduce the argument first.             */
    const double sin_arg = tmpl_Double_Mod_2(0.5 * x_double * x_double);
    const float sin_val = tmpl_Float_SinPi(TMPL_CAST(sin_arg, float));

    /*  The first term of the asymptotic expansion is all that is needed.     */
    return 0.5F + t * sin_val;
}
/*  End of tmpl_Float_Normalized_Fresnel_Cos_Asymptotic.                      */

#endif
/*  End of include guard.                                                     */
