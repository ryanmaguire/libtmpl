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
 *                           tmpl_arctan_pade_float                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the (11, 11) Pade approximant of atan(x) at single precision.*
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Arctan_Pade                                                *
 *  Purpose:                                                                  *
 *      Computes the Pade approximant of order (11, 11) for arctan.           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (float):                                                       *
 *          The Pade approximation of atan(x).                                *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomials for the numerator     *
 *      and denominator.                                                      *
 *                                                                            *
 *          atan(x) - x     a0 + a1*x^2 + a2*x^4 + a3*x^6 + a4*x^8 + a5*x^10  *
 *          ----------- ~= -------------------------------------------------- *
 *               x           1 + b1*x^2 + b2*x^4 + b3*x^6 + b4*x^8 + b5*x^10  *
 *                                                                            *
 *      Label the rational function as rat and return x*(rat + 1).            *
 *                                                                            *
 *      The coefficients are:                                                 *
 *                                                                            *
 *          ----------------------------------------------                    *
 *          |  n  |        an         |        bn        |                    *
 *          ----------------------------------------------                    *
 *          |  0  |         0         |        1         |                    *
 *          |  1  |      -1 / 3       |     55 / 21      |                    *
 *          |  2  |    -212 / 315     |    330 / 133     |                    *
 *          |  3  |    -178 / 399     |    330 / 323     |                    *
 *          |  4  |  -15292 / 142443  |     55 / 323     |                    *
 *          |  5  |   -1679 / 247401  |     33 / 4199    |                    *
 *          ----------------------------------------------                    *
 *  Notes:                                                                    *
 *      Surprisingly accurate for a fairly large range. For |x| < 1.0,        *
 *      accurate to single precision (10^-8). For |x| < 6.0, max relative     *
 *      error is 5.0 x 10^-2. The function becomes unusable for larger values.*
 *                                                                            *
 *      This function is about 1.5x faster than calling atan directly. Use if *
 *      you know your argument is small, or if you don't need all 8 decimals. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2022                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARCTAN_PADE_FLOAT_H
#define TMPL_ARCTAN_PADE_FLOAT_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant of (atan(x) - x)/x.*/
#define A04 (-6.786553005040399998383191660502584872333E-03F)
#define A03 (-1.073552227908707342586157269925514065275E-01F)
#define A02 (-4.461152882205513784461152882205513784461E-01F)
#define A01 (-6.730158730158730158730158730158730158730E-01F)
#define A00 (-3.333333333333333333333333333333333333333E-01F)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B05 (7.859014050964515360800190521552750654918E-03F)
#define B04 (1.702786377708978328173374613003095975232E-01F)
#define B03 (1.021671826625386996904024767801857585139E+00F)
#define B02 (2.481203007518796992481203007518796992481E+00F)
#define B01 (2.619047619047619047619047619047619047619E+00F)
#define B00 (1.000000000000000000000000000000000000000E+00F)

/*  Function for computing the (11, 11) Pade approximant of atan(x).          */
TMPL_STATIC_INLINE
float tmpl_Float_Arctan_Pade(float x)
{
    /*  The numerator is in terms of x^{2n+1} and the denominator is in terms *
     *  of x^{2n}. Compute the square of x and use this.                      */
    const float x2 = x*x;

    /*  Use Horner's method to evaluate the two polynomials.                  */
    const float p = x2*(A00 + x2*(A01 + x2*(A02 + x2*(A03 + x2*A04))));
    const float q = B00 + x2*(B01 + x2*(B02 + x2*(B03 + x2*(B04 + x2*B05))));

    /*  p/q is the Pade approximant for (atan(x) - x)/x. Compute atan(x) by   *
     *  adding 1 and multiplying by x.                                        */
    return x*(1.0F + p/q);
}
/*  End of tmpl_Float_Arctan_Pade.                                            */

/*  Undefine all macros in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
