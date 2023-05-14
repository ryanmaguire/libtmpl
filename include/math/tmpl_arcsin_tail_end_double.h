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
 *                        tmpl_arcsin_tail_end_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes asin(x) for 0.5 <= x < 1 at double precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arcsin_Tail_End                                           *
 *  Purpose:                                                                  *
 *      Computes arcsin for 0.5 <= x < 1.0.                                   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      asin_x (double):                                                      *
 *          The inverse sine of x.                                            *
 *  Called Functions:                                                         *
 *      tmpl_Double_Sqrt (tmpl_math.h):                                       *
 *          Computes the square root of a number.                             *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *          asin(x) = pi/2 - 2*asin(sqrt((1-x)/2))                            *
 *      Compute this using a Pade approximant.                                *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_TAIL_END_DOUBLE_H
#define TMPL_ARCSIN_TAIL_END_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  The square root function needs to be visible. Give the prototype pending  *
 *  whether libtmpl algorithms are requested.                                 */
#if TMPL_USE_MATH_ALGORITHMS == 1

TMPL_EXPORT extern double tmpl_Double_Sqrt(double x);
#define TMPL_SQUARE_ROOT tmpl_Double_Sqrt

/*  Otherwise use the default libm square root function.                      */
#else

TMPL_EXPORT extern double sqrt(double x);
#define TMPL_SQUARE_ROOT sqrt

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */

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

/*  Function for computing asin(x) for 0.5 <= x < 1.0.                        */
TMPL_INLINE_DECL
double tmpl_Double_Arcsin_Tail_End(double x)
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const double z = 0.5*(1.0 - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = P0 + z*(P1 + z*(P2 + z*(P3 + z*(P4 + z*P5))));
    const double q = Q0 + z*(Q1 + z*(Q2 + z*(Q3 + z*Q4)));
    const double r = z*p/q;
    const double s = TMPL_SQUARE_ROOT(z);
    const double t = r*s;
    return tmpl_Pi_By_Two - 2.0*(s + t);
}
/*  End of tmpl_Double_Arcsin_Tail_End.                                       */

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
#undef TMPL_SQUARE_ROOT

#endif
/*  End of include guard.                                                     */
