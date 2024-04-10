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
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Sqrt:                                                 *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *          asin(x) = pi/2 - 2*asin(sqrt((1-x)/2))                            *
 *      Compute this using a Remez rational minimax approximation.            *
 *  Notes:                                                                    *
 *      Accurate for 0.5 <= x < 1.0.                                          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 9, 2023                                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCSIN_TAIL_END_DOUBLE_H
#define TMPL_ARCSIN_TAIL_END_DOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  The compiler needs to know about the sqrt function.                       */
extern double tmpl_Double_Sqrt(double x);

/*  Coefficients for the numerator.                                           */
#define A00 (+1.66666666666666657415E-01)
#define A01 (-3.25565818622400915405E-01)
#define A02 (+2.01212532134862925881E-01)
#define A03 (-4.00555345006794114027E-02)
#define A04 (+7.91534994289814532176E-04)
#define A05 (+3.47933107596021167570E-05)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.00000000000000000000E+00)
#define B01 (-2.40339491173441421878E+00)
#define B02 (+2.02094576023350569471E+00)
#define B03 (-6.88283971605453293030E-01)
#define B04 (+7.70381505559019352791e-02)

/*  Helper macros for evaluating polynomials using Horner's method.           */
#define TMPL_POLYA_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))
#define TMPL_POLYB_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  Function for computing asin(x) for 0.5 <= x < 1.0.                        */
TMPL_STATIC_INLINE
double tmpl_Double_Arcsin_Tail_End(double x)
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const double z = 0.5*(1.0 - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const double p = TMPL_POLYA_EVAL(z);
    const double q = TMPL_POLYB_EVAL(z);

    /*  p(z) / q(z) is the rational minimax approximant for                   *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const double r = z*p/q;
    const double s = tmpl_Double_Sqrt(z);
    const double t = r*s;

    /*  We now have asin(sqrt(z)) - sqrt(z). We need pi/2 - 2*asin(sqrt(z)).  */
    return tmpl_Pi_By_Two - 2.0*(s + t);
}
/*  End of tmpl_Double_Arcsin_Tail_End.                                       */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
