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
 *                            tmpl_two_prod_double                            *
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
 *      out (double * TMPL_RESTRICT const):                                   *
 *          The rounded product x * y will be stored here.                    *
 *      err (double * TMPL_RESTRICT const):                                   *
 *          The error term, prod(x, y) - (x * y), is stored here.             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      tmpl_split.h:                                                         *
 *          tmpl_Double_Even_High_Split:                                      *
 *              Splits a double into two parts, xhi and xlo, so that xhi and  *
 *              xlo have half the number of bits of x. This function returns  *
 *              xhi. xlo is computed via xlo = x - hi.                        *
 *  Method:                                                                   *
 *      This is the standard 2Prod algorithm. Split x and y into two parts:   *
 *                                                                            *
 *          x = xhi + xlo                                                     *
 *          y = yhi + ylo                                                     *
 *                                                                            *
 *      The product is then:                                                  *
 *                                                                            *
 *          x * y = (xhi + xlo) * (yhi + ylo)                                 *
 *                = xhi*yhi + xhi*ylo + xlo*yhi + xlo*ylo                     *
 *                                                                            *
 *      xhi*yhi has the highest order bits of the product. Let prod be the    *
 *      product of x and y, with rounding. The error is then:                 *
 *                                                                            *
 *          err = ((xhi*yhi - prod) + xhi*ylo + yhi*xlo) + xlo*ylo            *
 *                                                                            *
 *      We store prod in "out" and err in "err", and return.                  *
 *  Notes:                                                                    *
 *      1.) On compilers supporting the "restrict" keyword, out and err are   *
 *          declared as "restrict" pointers. This requires that out and err   *
 *          point to different locations. To properly use this function, the  *
 *          caller should do this regardless.                                 *
 *  References:                                                               *
 *      1.) Hida, Y., Li, X., Bailey, D. (May 2008).                          *
 *          "Library for Double-Double and Quad-Double Arithmetic."           *
 *      2.) Schewchuk, J. (October 1997).                                     *
 *          "Adaptive Precision Floating-Point Arithmetic                     *
 *              and Fast Robust Geometric Predicates."                        *
 *          Discrete & Computational Geometry Vol 18, Number 3: Pages 305-363 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_split.h:                                                         *
 *          Contains functions for splitting an input into two parts.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 22, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TWO_PROD_DOUBLE_H
#define TMPL_TWO_PROD_DOUBLE_H

/*  TMPL_INLINE_DECL macro found here, as is TMPL_RESTRICT.                   */
#include <libtmpl/include/tmpl_config.h>

/*  Splitting functions for breaking a number into two parts.                 */
#include <libtmpl/include/tmpl_split.h>

/*  Standard 2Prod algorithm at double precision.                             */
TMPL_INLINE_DECL
void
tmpl_Double_Two_Prod(double x,
                     double y,
                     double * TMPL_RESTRICT const out,
                     double * TMPL_RESTRICT const err)
{
    /*  Split the inputs into two parts with half the bits stored in each.    */
    const double xhi = tmpl_Double_Even_High_Split(x);
    const double yhi = tmpl_Double_Even_High_Split(y);

    /*  The low parts can be computed from the difference.                    */
    const double xlo = x - xhi;
    const double ylo = y - yhi;

    /*  Perform the two-product. We have:                                     *
     *      x * y = (xhi + xlo) * (yhi + ylo)                                 *
     *            = xhi * yhi + xhi * ylo + xlo * yhi + xlo * ylo.            *
     *  We perform this sum, and keep track of the error term from rounding.  */
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
