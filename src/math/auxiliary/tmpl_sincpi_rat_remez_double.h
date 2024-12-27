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
 *                        tmpl_sincpi_rat_remez_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a rational Remez approximation for sinc(pi x).               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SincPi_Rat_Remez                                          *
 *  Purpose:                                                                  *
 *      Computes the (8, 8) rational Remez approximation for sinc(pi x).      *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number between -1/2 and 1/2.                               *
 *  Output:                                                                   *
 *      sincpi_x (double):                                                    *
 *          sinc(pi x) = sin(pi x) / (pi x) for non-zero x, and 1 if x = 0.   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator, and then return the quotient.                        *
 *  Notes:                                                                    *
 *      Accurate to double precision for |x| < 0.5.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 27, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SINCPI_RAT_REMEZ_DOUBLE_H
#define TMPL_SINCPI_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+9.9999999999999999987318218789214480855942729063647E-01)
#define A01 (-1.4560731830141230954346554745833737178489988660599E+00)
#define A02 (+5.1859100827341948727978752227380440269603658014049E-01)
#define A03 (-6.5270199126100649352332440974088794928702769073125E-02)
#define A04 (+2.7523749878599785582475694961087653192755005420240E-03)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.8886088383410325809597811211529790940077772058935E-01)
#define B02 (+1.7512284703856701943897842362033154275068054963446E-02)
#define B03 (+9.8178680868043825404521238677864219186267996528532E-04)
#define B04 (+2.9595384754649813964515269222537366378937690171092E-05)

/*  Helper macros for evaluating polynomials via Horner's method.             */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the (8, 8) Remez approximation for sinc(pi x) on [-0.5, 0.5].    */
TMPL_STATIC_INLINE
double tmpl_Double_SincPi_Rat_Remez(double x)
{
    /*  sinc(pi x) is even, the polynomials are in terms of x^2.              */
    const double x2 = x * x;

    /*  Compute the rational Remez approximation and return.                  */
    const double num = TMPL_NUM_EVAL(x2);
    const double den = TMPL_DEN_EVAL(x2);
    return num / den;
}
/*  End of tmpl_Double_SincPi_Rat_Remez.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
