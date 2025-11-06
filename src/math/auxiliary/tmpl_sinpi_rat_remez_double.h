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
#define A00 (+3.1415926535897933816689261989974778492927729378371E+00)
#define A01 (-4.6309682400663881726236459217765142802257155106728E+00)
#define A02 (+1.7086545536188555702013479156466255697465554856228E+00)
#define A03 (-2.3014753989906207114628975956276586215957780394430E-01)
#define A04 (+1.0868664330885190338945814092471211589229325620862E-02)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.7085109343196858358034464552453687304674362904032E-01)
#define B02 (+1.3177995148998066543135059031824581216538369577977E-02)
#define B03 (+4.8343916432920043476968950843493255913336423877781E-04)


/*  Helper macros for evaluating polynomials via Horner's method.             */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*B03))

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
