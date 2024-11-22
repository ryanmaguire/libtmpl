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
 *                          tmpl_fast_two_prod_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses the 2Prod algorithm for multiplying with error.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Two_Prod                                                  *
 *  Purpose:                                                                  *
 *      Evaluates the product of two doubles, with the rounding error.        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *      y (double):                                                           *
 *          Another real number.                                              *
 *      out (double * const):                                                 *
 *          The rounded product x * y will be stored here.                    *
 *      err (double * const):                                                 *
 *          The error term, prod(x, y) - (x * y), is stored here.             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_PROD_DOUBLE_H
#define TMPL_TWO_PROD_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_VOLATILE.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Splitting functions for breaking a number into two parts.                 */
#include <libtmpl/include/tmpl_split.h>

/*  Standard 2Prod algorithm at double precision.                             */
TMPL_INLINE_DECL
void
tmpl_Double_Two_Prod(double x, double y, double * const out, double * const err)
{
    /*  Split the input into two parts with half the bits stored in each.     */
    const double xhi = tmpl_Double_Even_High_Split(x);
    const double yhi = tmpl_Double_Even_High_Split(y);

    /*  The low parts can be computed from the difference.                    */
    const double xlo = x - xhi;
    const double ylo = y - yhi;

    /*  Perform the two-product. We have:                                     *
    *       x * y = (xhi + xlo) * (yhi + ylo)                                 *
    *             = xhi * yhi + xhi * ylo + xlo * yhi + xlo * ylo.            *
    *   We perform this sum, and keep track of the error term from rounding.  */
    const double prod = x * y;
    const double err_hi = xhi * yhi - prod;
    const double prod_mid = xhi * ylo + xlo * yhi;
    const double prod_lo = xlo * ylo;

    /*  "prod" has the rounded product. The error is computed from the sum.   */
    *out = prod;
    *err = (err_hi + prod_mid) + prod_lo;
}
/*  End of tmpl_Double_Two_Prod.                                              */

#endif
/*  End of include guard.                                                     */
