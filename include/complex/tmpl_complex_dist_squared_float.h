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
 *                      tmpl_complex_dist_squared_float                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the function f(z, w) = |z - w|^2.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Dist_Squared                                              *
 *  Purpose:                                                                  *
 *      Computes the distance between two complex numbers:                    *
 *                                                                            *
 *          dist(z, w) = dist(a + ib, c + id)^2                               *
 *                     = (c - a)^2 + (d - b)^2                                *
 *                                                                            *
 *      This is provided so that users can avoid redundant and expensive      *
 *      calls to the square root function made with tmpl_CFloat_Dist.         *
 *  Arguments:                                                                *
 *      z (tmpl_ComplexFloat):                                                *
 *          A complex number.                                                 *
 *      w (tmpl_ComplexFloat):                                                *
 *          Another complex number.                                           *
 *  Output:                                                                   *
 *      dist (float):                                                         *
 *          The distance between z and w.                                     *
 *  Method:                                                                   *
 *      Treat the points as elements of the Euclidean plane and use           *
 *      the Pythagorean formula.                                              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2021                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2021/02/16: Ryan Maguire                                                  *
 *      Created file                                       .                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_DIST_SQUARED_FLOAT_H
#define TMPL_COMPLEX_DIST_SQUARED_FLOAT_H

/*  TMPL_USE_INLINE found here.                                               */
#include <libtmpl/include/tmpl_config.h>

/*  This file is only used if inline support is requested.                    */
#if TMPL_USE_INLINE == 1

/*  Complex routines and data types defined here.                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Single precision distance squared function for complex variables.         */
TMPL_INLINE_DECL
float tmpl_CFloat_Dist_Squared(tmpl_ComplexFloat z0, tmpl_ComplexFloat z1)
{
    /*  Compute the difference in both components and use Pythagoras.         */
    const float dx = z0.dat[0] - z1.dat[0];
    const float dy = z0.dat[1] - z1.dat[1];
    return dx*dx + dy*dy;
}
/*  End of tmpl_CFloat_Dist_Squared.                                          */

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
