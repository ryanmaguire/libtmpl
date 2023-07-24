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
 *                        tmpl_complex_polarpi_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for creating complex numbers using their     *
 *      polar representation.                                                 *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_PolarPi                                                  *
 *  Purpose:                                                                  *
 *      Computes the point in the plane given its polar representation. That  *
 *      is, given radius r and angle theta, computes:                         *
 *                                                                            *
 *          z = r e^{i pi theta}                                              *
 *            = r exp(i pi theta)                                             *
 *            = r cos(pi theta) + i r sin(pi theta)                           *
 *                                                                            *
 *  Arguments:                                                                *
 *      r (double):                                                           *
 *          The magnitude of the point.                                       *
 *      theta (double):                                                       *
 *          The angle of the point, in normalized units.                      *
 *  Output:                                                                   *
 *      z (tmpl_ComplexDouble):                                               *
 *          The point r e^{i pi theta} in the plane.                          *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCosPi:                                             *
 *              Computes sin(pi t) and cos(pi t) simultaneously.              *
 *  Method:                                                                   *
 *      Compute x = cos(pi t) and y = sin(pi t) and return z = rx + iry.      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex.h:                                                       *
 *          Header where complex types and function prototypes are defined.   *
 *  3.) tmpl_math.h:                                                          *
 *          Header containing various math functions.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 22, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_POLARPI_DOUBLE_H
#define TMPL_COMPLEX_POLARPI_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Header file with math functions.                                          */
#include <libtmpl/include/tmpl_math.h>

/*  Where the prototypes are declared and where complex types are defined.    */
#include <libtmpl/include/tmpl_complex.h>

/*  Create a double precision complex number from its polar coordinates.      */
TMPL_INLINE_DECL
tmpl_ComplexDouble tmpl_CDouble_PolarPi(double r, double theta)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_ComplexDouble z;

    /*  Compute sin(pi theta) and cos(pi theta) simultaneously.               */
    tmpl_Double_SinCosPi(theta, &z.dat[1], &z.dat[0]);

    /*  Scale the real and imaginary parts by r to finish the computation.    */
    z.dat[0] *= r;
    z.dat[1] *= r;
    return z;
}
/*  End of tmpl_CDouble_PolarPi.                                              */

#endif
/*  End of include guard.                                                     */
