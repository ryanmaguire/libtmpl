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
 *                         tmpl_complex_polard_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for creating complex numbers using their     *
 *      polar representation.                                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Polard                                                  *
 *  Purpose:                                                                  *
 *      Computes the point in the plane given its polar representation. That  *
 *      is, given radius r and angle theta, computes:                         *
 *                                                                            *
 *          z = r e^{i theta}                                                 *
 *            = r exp(i theta)                                                *
 *            = r cos(theta) + i r sin(theta)                                 *
 *                                                                            *
 *  Arguments:                                                                *
 *      r (long double):                                                      *
 *          The magnitude of the point.                                       *
 *      theta (long double):                                                  *
 *          The angle of the point, in degrees.                               *
 *  Output:                                                                   *
 *      z (tmpl_ComplexLongDouble):                                           *
 *          The point r e^{i theta} in the plane.                             *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_SinCosd:                                             *
 *              Computes sind(t) and cosd(t) simultaneously.                  *
 *  Method:                                                                   *
 *      Compute x = cosd(t) and y = sind(t) and return z = rx + iry.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header where complex types are defined.                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 22, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_POLARD_LDOUBLE_H
#define TMPL_COMPLEX_POLARD_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  Tell the compiler about the SinCosd function.                             */
extern void
tmpl_LDouble_SinCosd(long double t, long double *sind_t, long double *cosd_t);

/*  Create a long double precision complex number from its polar coordinates. */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble tmpl_CLDouble_Polard(long double r, long double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexLongDouble z;

    /*  Compute sind(theta) and cosd(theta) simultaneously.                   */
    tmpl_LDouble_SinCosd(theta, &z.dat[1], &z.dat[0]);

    /*  Scale the real and imaginary parts by r to finish the computation.    */
    z.dat[0] *= r;
    z.dat[1] *= r;
    return z;
}
/*  End of tmpl_CLDouble_Polard.                                              */

#endif
/*  End of include guard.                                                     */
