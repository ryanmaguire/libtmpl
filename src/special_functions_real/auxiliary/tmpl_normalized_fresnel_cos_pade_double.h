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
 *                   tmpl_normalized_fresnel_cos_pade_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for small values.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Pade                               *
 *  Purpose:                                                                  *
 *      Computes C(x) for |x| < 1.                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_PADE_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_PADE_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (-2.1090942541681899242845079918511663967216358911725E-01)
#define A02 (+1.9952947354822570927809856437132718931800178922439E-02)
#define A03 (-7.3911123111933377948080176313020983341150763045957E-04)
#define A04 (+1.2274218310026533331254617912315044753062117420452E-05)
#define A05 (-7.8097325185845863146674684390301377301045873738860E-08)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+3.5830684610414973042411475811787138710678896063772E-02)
#define B02 (+6.0831354005325641202296672843869017418765178894320E-04)
#define B03 (+5.9614617845960804718215100801144490827271427390733E-06)
#define B04 (+2.9455885172523367699202977882571957391522644286406E-08)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the normalized Fresnel cosine function using a Pade approximant. */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Cos_Pade(double x)
{
    /*  The Pade approximant is in terms of x^4.                              */
    const double x2 = x*x;
    const double x4 = x2*x2;

    /*  Compute the Pade approximant.                                         */
    const double num = TMPL_NUM_EVAL(x4);
    const double den = TMPL_DEN_EVAL(x4);
    return x * num / den;
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Pade.                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
