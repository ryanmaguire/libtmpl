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
 *                          tmpl_complex_expi_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the f(t) = exp(i t) for real t.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_Expi                                                    *
 *  Purpose:                                                                  *
 *      Computes the point on the unit circle corresponding to a real angle t.*
 *                                                                            *
 *          f(t) = e^{i t}                                                    *
 *               = exp(i t)                                                   *
 *               = (cos(t), sin(t))                                           *
 *                                                                            *
 *  Arguments:                                                                *
 *      t (long double):                                                      *
 *          The angle of the point.                                           *
 *  Output:                                                                   *
 *      exp_i_t (tmpl_ComplexLongDouble):                                     *
 *          The point on the unit circle corresponding to t.                  *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_LDouble_SinCos:                                              *
 *              Computes sin(t) and cos(t) simultaneously.                    *
 *  Method:                                                                   *
 *      Compute x = cos(t) and y = sin(t) and return z = x + iy.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_ldouble.h:                                               *
 *          Header providing long double precision complex numbers.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 13, 2023                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/06/04: Ryan Maguire                                                  *
 *      Replaced tmpl_math.h include with forward declaration. Removed        *
 *      include for tmpl_complex.h, replaced with tmpl_complex_ldouble.h.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_EXPI_LDOUBLE_H
#define TMPL_COMPLEX_EXPI_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_ldouble.h>

/*  Tell the compiler about the SinCos function.                              */
extern void
tmpl_LDouble_SinCos(long double t, long double *sin_t, long double *cos_t);

/*  Computes the point on the unit circle with angle t from the real axis.    */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble tmpl_CLDouble_Expi(long double t)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ComplexLongDouble z;

    /*  Use SinCos to compute sin(t) and cos(t), simultaneously, and store    *
     *  the results in the imaginary and real part of z, respectively.        */
    tmpl_LDouble_SinCos(t, &z.dat[1], &z.dat[0]);
    return z;
}
/*  End of tmpl_CLDouble_Expi.                                                */

#endif
/*  End of include guard.                                                     */
