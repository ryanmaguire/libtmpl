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
 *                         tmpl_complex_expipi_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the f(t) = exp(i pi t) for real t.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_ExpiPi                                                   *
 *  Purpose:                                                                  *
 *      Computes the point on the unit circle corresponding to a normalized   *
 *      phase t. That, given a real number t, this computes:                  *
 *                                                                            *
 *          f(t) = e^{i pi t}                                                 *
 *               = exp(i pi t)                                                *
 *               = (cos(pi t), sin(pi t))                                     *
 *                                                                            *
 *  Arguments:                                                                *
 *      t (double):                                                           *
 *          The normalized phase.                                             *
 *  Output:                                                                   *
 *      exp_i_pi_t (tmpl_ComplexDouble):                                      *
 *          The point on the unit circle corresponding to t.                  *
 *  Called Functions:                                                         *
 *      src/math/                                                             *
 *          tmpl_Double_SinCosPi:                                             *
 *              Computes sin(pi t) and cos(pi t) simultaneously.              *
 *  Method:                                                                   *
 *      Compute x = cos(pi t) and y = sin(pi t) and return z = x + iy.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file where TMPL_INLINE_DECL is found.                      *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header providing double precision complex numbers.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 12, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/13: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_expipi_double.c to include this.     *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_EXPIPI_DOUBLE_H
#define TMPL_COMPLEX_EXPIPI_DOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  Tell the compiler about the SinCosPi function.                            */
extern void tmpl_Double_SinCosPi(double t, double *sinpi_t, double *cospi_t);

/*  Computes the point on the unit circle with angle pi*t from the real axis. */
TMPL_INLINE_DECL
tmpl_ComplexDouble tmpl_CDouble_ExpiPi(double t)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ComplexDouble z;

    /*  Use SinCosPi to compute sin(pi t) and cos(pi t), simultaneously, and  *
     *  store the results in the imaginary and real part of z, respectively.  */
    tmpl_Double_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
/*  End of tmpl_CDouble_ExpiPi.                                               */

#endif
/*  End of include guard.                                                     */
