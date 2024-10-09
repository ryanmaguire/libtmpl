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
 *                   tmpl_normalized_fresnel_sin_pade_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin_Pade                               *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1.                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (double):                                                         *
 *          The normalized Fresnel sine of x.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the (20, 16) Pade approximant for C(x). The polynomials are   *
 *      in terms of x^4, so only 5 terms are needed for the numerator and     *
 *      4 terms required for the denominator.                                 *
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
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_PADE_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_SIN_PADE_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01)
#define A01 (-7.5646702684156373657133062485951711722422797821397E-02)
#define A02 (+4.5603135186970685798333089934580883578580099903679E-03)
#define A03 (-1.2343163613744783025262037672315575856900093113426E-04)
#define A04 (+1.5893800791950822561593328505853377660316668412608E-06)
#define A05 (-8.1994804828506437950754119866572847262867244360994E-09)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+3.1768375804301341219415408603904367390762622593100E-02)
#define B02 (+4.7199046505149390245676635290448031218427214415959E-04)
#define B03 (+3.9836521640342121153574740992762308824026092219817E-06)
#define B04 (+1.6616163918330675261060649578315035528058167218657E-08)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the normalized Fresnel sine function using a Pade approximant.   */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Sin_Pade(double x)
{
    /*  The Pade approximant is in terms of x^4.                              */
    const double x2 = x*x;
    const double x4 = x2*x2;

    /*  Compute the Pade approximant.                                         */
    const double num = TMPL_NUM_EVAL(x4);
    const double den = TMPL_DEN_EVAL(x4);
    return x * x2 * num / den;
}
/*  End of tmpl_Double_Normalized_Fresnel_Sin_Pade.                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
