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
 *                   tmpl_normalized_fresnel_sin_pade_float                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Normalized_Fresnel_Sin_Pade                                *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1.                                            *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (float):                                                          *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the (12, 8) Pade approximant for C(x). The polynomials are    *
 *      in terms of x^4, so only 3 terms are needed for the numerator and     *
 *      2 for the denominator.                                                *
 *  Notes:                                                                    *
 *      This function assumes the input is bounded by 1.                      *
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
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_PADE_FLOAT_H
#define TMPL_NORMALIZED_FRESNEL_SIN_PADE_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01F)
#define A01 (-7.0579602539957014002998550718326173656823363505594E-02F)
#define A02 (+3.7447636474822540031860566299303887593243566451154E-03F)
#define A03 (-6.9063640501784258881417564221884521303531043100421E-05F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00F)
#define B01 (+4.1445824225393146045607857705930695799938591298533E-02F)
#define B02 (+6.1998686509498982291526655383097093457925233545907E-04F)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*A03))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*B02)

/*  Computes the normalized Fresnel sine function using a Pade approximant.   */
TMPL_STATIC_INLINE
float tmpl_Float_Normalized_Fresnel_Sin_Pade(float x)
{
    /*  The Pade approximant is in terms of x^4.                              */
    const float x2 = x*x;
    const float x4 = x2*x2;

    /*  Compute the Pade approximant.                                         */
    const float num = TMPL_NUM_EVAL(x4);
    const float den = TMPL_DEN_EVAL(x4);
    return x * x2 * num / den;
}
/*  End of tmpl_Float_Normalized_Fresnel_Sin_Pade.                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
