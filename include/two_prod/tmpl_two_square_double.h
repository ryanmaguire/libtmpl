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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 25, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_SQUARE_DOUBLE_H
#define TMPL_TWO_SQUARE_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_RESTRICT.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Splitting functions for breaking a number into two parts.                 */
#include <libtmpl/include/tmpl_split.h>

/*  Standard 2Prod algorithm for squaring at double precision.                */
TMPL_INLINE_DECL
void
tmpl_Double_Two_Square(double x,
                       double * TMPL_RESTRICT const out,
                       double * TMPL_RESTRICT const err)
{
    /*  Split the input into two parts with half the bits stored in each.     */
    const double xhi = tmpl_Double_Even_High_Split(x);

    /*  The low part can be computed from the difference.                     */
    const double xlo = x - xhi;

    /*  Perform the two-product. We have:                                     *
     *      x * x = (xhi + xlo) * (xhi + xlo)                                 *
     *            = xhi*xhi + 2*xhi*xlo + xlo*xlo                             *
     *  We perform this sum, and keep track of the error term from rounding.  */
    const double prod = x * x;
    const double err_hi = xhi * xhi - prod;
    const double prod_mid = 2.0 * xlo * xhi;
    const double prod_lo = xlo * xlo;

    /*  "prod" has the rounded product. The error is computed from the sum.   */
    *out = prod;
    *err = (err_hi + prod_mid) + prod_lo;
}
/*  End of tmpl_Double_Two_Square.                                            */

#endif
/*  End of include guard.                                                     */
