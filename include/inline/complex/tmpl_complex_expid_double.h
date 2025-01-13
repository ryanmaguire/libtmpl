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
 *                          tmpl_complex_expid_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the f(t) = exp(i t) for real t.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Expid                                                    *
 *  Purpose:                                                                  *
 *      Computes the point on the unit circle corresponding to a real angle t.*
 *                                                                            *
 *          f(t) = e^{i t}                                                    *
 *               = exp(i t)                                                   *
 *               = (cosd(t), sind(t))                                         *
 *                                                                            *
 *  Arguments:                                                                *
 *      t (double):                                                           *
 *          The angle of the point, in degrees.                               *
 *  Output:                                                                   *
 *      exp_i_t (tmpl_ComplexDouble):                                         *
 *          The point on the unit circle corresponding to t.                  *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCosd:                                              *
 *              Computes sind(t) and cosd(t) simultaneously.                  *
 *  Method:                                                                   *
 *      Compute x = cosd(t) and y = sind(t) and return z = x + iy.            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 22, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_EXPID_DOUBLE_H
#define TMPL_COMPLEX_EXPID_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Tell the compiler about the SinCosd function.                             */
extern void tmpl_Double_SinCosd(double t, double *sind_t, double *cosd_t);

/*  Computes the point on the unit circle with angle t from the real axis.    */
TMPL_INLINE_DECL
tmpl_ComplexDouble tmpl_CDouble_Expid(double t)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ComplexDouble z;

    /*  Use SinCosd to compute sind(t) and cosd(t), simultaneously, and store  *
     *  the results in the imaginary and real part of z, respectively.        */
    tmpl_Double_SinCosd(t, &z.dat[1], &z.dat[0]);
    return z;
}
/*  End of tmpl_CDouble_Expid.                                                */

#endif
/*  End of include guard.                                                     */
