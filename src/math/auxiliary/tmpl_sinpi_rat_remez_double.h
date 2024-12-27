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
 *                        tmpl_sinpi_rat_remez_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a rational Remez approximation for sin(pi x).                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_SinPi_Rat_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes a degree (9, 8) rational Remez approximation for sin(pi x).  *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number between -1/2 and 1/2.                               *
 *  Output:                                                                   *
 *      sinpi_x (double):                                                     *
 *          The value sin(pi x) to double precision.                          *
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
#ifndef TMPL_SINPI_RAT_REMEZ_DOUBLE_H
#define TMPL_SINPI_RAT_REMEZ_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+3.1415926535897932380642334764171342830817187492778E+00)
#define A01 (-4.5743888148462756299036403644165522776215856440802E+00)
#define A02 (+1.6292017018094983466323950027174469236871713853184E+00)
#define A03 (-2.0505237807290074266150130302419433165491651916134E-01)
#define A04 (+8.6468410417852049888816124049990359926712601051849E-03)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.8886088383410325809597811211529790940077772058935E-01)
#define B02 (+1.7512284703856701943897842362033154275068054963446E-02)
#define B03 (+9.8178680868043825404521238677864219186267996528532E-04)
#define B04 (+2.9595384754649813964515269222537366378937690171092E-05)

/*  Helper macros for evaluating polynomials via Horner's method.             */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Computes the (9, 8) Remez approximation for sin(pi x) on [-0.5, 0.5].     */
TMPL_STATIC_INLINE
double tmpl_Double_SinPi_Rat_Remez(double x)
{
    /*  sin(pi x) is odd, the polynomials are in terms of x^{2n+1}.           */
    const double x2 = x * x;

    /*  Compute the numerator and denominator using Horner's method.          */
    const double num = TMPL_NUM_EVAL(x2);
    const double den = TMPL_DEN_EVAL(x2);

    /*  num / den is the (8, 8) Remez approximation for sin(pi x) / x. We get *
     *  the rational Remez approximation for sin(pi x) by scaling by x.       */
    return x * num / den;
}
/*  End of tmpl_Double_SinPi_Rat_Remez.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
