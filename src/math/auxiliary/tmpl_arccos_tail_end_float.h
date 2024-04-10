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
 *                         tmpl_arccos_tail_end_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes acos(x) for 0.5 <= x < 1 at single precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arccos_Tail_End                                            *
 *  Purpose:                                                                  *
 *      Computes arccos for 0.5 <= x < 1.0.                                   *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      acos_x (float):                                                       *
 *          The inverse cosine of x.                                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a number.                         *
 *  Method:                                                                   *
 *      Use the following trig identity:                                      *
 *          acos(x) = 2*asin(sqrt((1-x)/2))                                   *
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
 *  Date:       January 2, 2023                                               *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/04/18: Ryan Maguire                                                  *
 *      Changed src/math/tmpl_arccos_tail_end_float.c to include this file.   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCCOS_TAIL_END_FLOAT_H
#define TMPL_ARCCOS_TAIL_END_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  The compiler needs to know about the sqrt function.                       */
extern float tmpl_Float_Sqrt(float x);

/*  Coefficients for the numerator.                                           */
#define A00 (+1.6666586697E-01F)
#define A01 (-4.2743422091E-02F)
#define A02 (-8.6563630030E-03F)

/*  Coefficients for the denominator.                                         */
#define B00 (+1.0000000000E+00F)
#define B01 (-7.0662963390E-01F)

/*  Function for computing acos(x) for 0.5 <= x < 1.0.                        */
TMPL_STATIC_INLINE
float tmpl_Float_Arccos_Tail_End(float x)
{
    /*  Rational function is computed in terms of (1 - x)/2.                  */
    const float z = 0.5F*(1.0F - x);

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = A00 + z*(A01 + z*A02);
    const float q = B00 + z*B01;

    /*  p(z) / q(z) is the rational minimax approximant for                   *
     *  (asin(sqrt(z)) - sqrt(z)) / z^{3/2}. We need to multiply by z^{3/2}.  */
    const float r = z*p/q;
    const float s = tmpl_Float_Sqrt(z);
    const float t = r*s;

    /*  We now have asin(sqrt(z)) - sqrt(z). We need 2*asin(sqrt(z)).         */
    return 2.0F*(s + t);
}
/*  End of tmpl_Float_Arccos_Tail_End.                                        */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
