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
 *                     tmpl_complex_dist_squared_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z, w) = |z - w|^2.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Dist_Squared                                            *
 *  Purpose:                                                                  *
 *      Computes the square of the distance between two complex numbers:      *
 *                                                                            *
 *          dist(z, w)^2 = dist(a + ib, c + id)^2                             *
 *                       = (c - a)^2 + (d - b)^2                              *
 *                                                                            *
 *      This is provided so that users can avoid redundant and expensive      *
 *      calls to the hypot function made with tmpl_CLDouble_Dist.             *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexLongDouble):                                           *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      dist (long double):                                                   *
 *          The distance between z and w.                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Treat the points as elements of the Euclidean plane and use           *
 *      the Pythagorean formula.                                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/02/16: Ryan Maguire                                                  *
 *      Created file.                                                         *
 *  2023/07/13: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_dist_squared_ldouble.c to use this.  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_DIST_SQUARED_LDOUBLE_H
#define TMPL_COMPLEX_DIST_SQUARED_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  Long double precision distance squared function for complex variables.    */
TMPL_INLINE_DECL
long double
tmpl_CLDouble_Dist_Squared(tmpl_ComplexLongDouble z0, tmpl_ComplexLongDouble z1)
{
    /*  Compute the difference in both components and use Pythagoras.         */
    const long double dx = z0.dat[0] - z1.dat[0];
    const long double dy = z0.dat[1] - z1.dat[1];
    return dx*dx + dy*dy;
}
/*  End of tmpl_CLDouble_Dist_Squared.                                        */

#endif
/*  End of include guard.                                                     */
