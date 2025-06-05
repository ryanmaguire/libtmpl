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
 *                         tmpl_complex_divide_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for complex division.                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Divide                                                   *
 *  Purpose:                                                                  *
 *      Divides two complex numbers.                                          *
 *                                                                            *
 *          div(z, w) = z / w                                                 *
 *                                                                            *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexDouble):                                               *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexDouble):                                               *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      quot (tmpl_ComplexDouble):                                            *
 *          The quotient z / w.                                               *
 *  Method:                                                                   *
 *      Use the fact that z / w = z * w^-1. The reciprocal formula for w      *
 *      yields:                                                               *
 *                                                                            *
 *           -1           -1    c - i d    c - i d                            *
 *          w   = (c + id)   = --------- = -------                            *
 *                             c^2 + d^2     |w|                              *
 *                                                                            *
 *      The intermediate computation c^2 + d^2 may underflow or underflow. To *
 *      avoid this we first normalize w by its magnitude |w|, the reciprocal  *
 *      is then given by:                                                     *
 *                                                                            *
 *           -1    c / |w| - i d / |w|                                        *
 *          w   = --------------------                                        *
 *                        |w|                                                 *
 *                                                                            *
 *      The final quotient is:                                                *
 *                                                                            *
 *           z    a + ib                                                      *
 *          --- = ------                                                      *
 *           w    c + id                                                      *
 *                                                                            *
 *                         c - i d                                            *
 *                (a + ib) -------                                            *
 *                           |w|                                              *
 *              = ----------------                                            *
 *                      |w|                                                   *
 *                                                                            *
 *                 -             -       -             -                      *
 *                |    c       d  |     |    c       d  |                     *
 *                | a --- + b --- | + i | b --- - a --- |                     *
 *                |   |w|     |w| |     |   |w|     |w| |                     *
 *                 -             -       -             -                      *
 *              = ---------------------------------------                     *
 *                                  |w|                                       *
 *                                                                            *
 *      That is, the real and imaginary parts are given by:                   *
 *                                                                            *
 *               ac / |w| + bd / |w|                                          *
 *          re = -------------------                                          *
 *                       |w|                                                  *
 *                                                                            *
 *               bc / |w| - ad / |w|                                          *
 *          im = -------------------                                          *
 *                       |w|                                                  *
 *                                                                            *
 *      We compute these and store them in the output complex number.         *
 *  Notes:                                                                    *
 *      1.) No error check is performed on the inputs. In particular, there   *
 *          are no checks for zero in the denominator, or NaNs or infinities. *
 *      2.) Division is not commutative. tmpl_CDouble_Divide(z, w) returns    *
 *          z / w, and not w / z. That is, the first entry is divided by the  *
 *          second one.                                                       *
 *      3.) In most realistic applications the precautions taken to prevent   *
 *          underflow and overflow are unnecessary since you would need to    *
 *          work with very small or very large numbers. Use the function      *
 *          tmpl_CDouble_Quick_Divide instead to get a performance boost if   *
 *          you are not working with such complex numbers.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          TMPL_INLINE_DECL macro found here.                                *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2020/11/30: Ryan Maguire                                                  *
 *      Created file (Wellesley College for librssringoccs).                  *
 *  2021/02/16: Ryan Maguire                                                  *
 *      Copied from rss_ringoccs.                                             *
 *  2025/06/05: Ryan Maguire                                                  *
 *      Inlined functions, moved float and long double versions to their own  *
 *      file, made the algorithm safely handle extreme denominators by using  *
 *      the hypot function (tmpl_CDouble_Quick_Divide now provides the faster *
 *      algorithm that is susceptible to overflow and underflow).             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_DIVIDE_DOUBLE_H
#define TMPL_COMPLEX_DIVIDE_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  The hypot function allows us to normalize the denominator.                */
extern double tmpl_Double_Hypot(double x, double y);

/*  In C99, since _Complex is a built-in data type, given double _Complex z   *
 *  and double _Complex w, you can just do z / w. Structs cannot be           *
 *  divided so we need a function for computing this.                         */

/*  Double precision complex division.                                        */
TMPL_INLINE_DECL
tmpl_ComplexDouble
tmpl_CDouble_Divide(tmpl_ComplexDouble z, tmpl_ComplexDouble w)
{
    /*  Declare a variable for the output, the quotient z / w.                */
    tmpl_ComplexDouble quot;

    /*  The standard division formula is given by:                            *
     *                                                                        *
     *       z    a + ib   (a + ib) (c - id)                                  *
     *      --- = ------ = -----------------                                  *
     *       w    c + id       c^2 + d^2                                      *
     *                                                                        *
     *  This is susceptible to both underflow and overflow when the           *
     *  denominator is either very small or very large, respectively. We can  *
     *  compensate for this by normalizing the denominator first and then     *
     *  using the division formula with the unit-length complex number. We    *
     *  compute the length of the denominator using the hypot function.       */
    const double norm_w = tmpl_Double_Hypot(w.dat[0], w.dat[1]);

    /*  Multiplication is faster than division. Pre-compute the reciprocal.   */
    const double rcpr_norm_w = 1.0 / norm_w;

    /*  Compute the normalized components of the denominator. The complex     *
     *  number wx_n + i wn_y has unit magnitude, allowing us to avoid         *
     *  underflow or overflow in the intermediate computations.               */
    const double wn_x = w.dat[0] * rcpr_norm_w;
    const double wn_y = w.dat[1] * rcpr_norm_w;

    /*  The normalized denominator can be used to compute the quotient via:   *
     *                                                                        *
     *                               c - i d                                  *
     *                               -------                                  *
     *       z    a + ib   (a + ib)    |w|     (a + ib) (c / |w| - i d / |w|) *
     *      --- = ------ = ----------------- = ------------------------------ *
     *       w    c + id          |w|                        |w|              *
     *                                                                        *
     *  Expanding out this last product using the standard product formula    *
     *  for complex numbers gives us the following.                           */
    quot.dat[0] = (z.dat[0] * wn_x + z.dat[1] * wn_y) * rcpr_norm_w;
    quot.dat[1] = (z.dat[1] * wn_x - z.dat[0] * wn_y) * rcpr_norm_w;
    return quot;
}
/*  End of tmpl_CDouble_Divide.                                               */

#endif
/*  End of include guard.                                                     */
