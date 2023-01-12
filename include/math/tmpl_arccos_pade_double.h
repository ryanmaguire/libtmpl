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
 *                       tmpl_arccos_pade_double_inline                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (10, 8) Pade approximant of acos(x) at double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arccos_Pade                                               *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (10, 8) for arccos.            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (double):                                                      *
 *          The Pade approximation of acos(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          asin(x)+x-pi/2   a0 + a1*x^2 + a2*x^4 + a3*x^6 + a4*x^8 + a5*x^10 *
 *          -------------- = ------------------------------------------------ *
 *               x^3               1 + b1*x^2 + b2*x^4 + b3*x^6 + b4*x^8      *
 *  Notes:                                                                    *
 *      Accurate for |x| < 0.5.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 2, 2023                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_PADE_DOUBLE_H
#define TMPL_ARCCOS_PADE_DOUBLE_H

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Check if inline support has been requested.                               */
#if TMPL_USE_INLINE == 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (+1.66666666666666657415E-01)
#define P1 (-3.25565818622400915405E-01)
#define P2 (+2.01212532134862925881E-01)
#define P3 (-4.00555345006794114027E-02)
#define P4 (+7.91534994289814532176E-04)
#define P5 (+3.47933107596021167570E-05)

/*  Coefficients for the denominator.                                         */
#define Q0 (+1.00000000000000000000E+00)
#define Q1 (-2.40339491173441421878E+00)
#define Q2 (+2.02094576023350569471E+00)
#define Q3 (-6.88283971605453293030E-01)
#define Q4 (+7.70381505559019352791e-02)

/*  Function for computing the (10, 8) Pade approximant of acos(x).           */
TMPL_INLINE_DECL
double tmpl_Double_Arccos_Pade(double x)
{
    /*  The polynomials for the numerator and denominator are in terms of x^2.*/
    const double x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = P0 + x2*(P1 + x2*(P2 + x2*(P3 + x2*(P4 + x2*P5))));
    const double q = Q0 + x2*(Q1 + x2*(Q2 + x2*(Q3 + x2*Q4)));
    const double r = x2*p/q;

    /*  p/q is the Pade approximant for (acos(x) - pi/2 + x) / x^3.           */
    return tmpl_Pi_By_Two - (x + x*r);
}
/*  End of tmpl_Double_Arccos_Pade.                                           */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P5
#undef P4
#undef P3
#undef P2
#undef P1
#undef P0
#undef Q4
#undef Q3
#undef Q2
#undef Q1
#undef Q0

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */

#endif
/*  End of include guard.                                                     */
