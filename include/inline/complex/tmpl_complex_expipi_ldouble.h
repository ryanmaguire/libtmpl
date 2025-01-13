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
 *                        tmpl_complex_expipi_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains the source code for the f(t) = exp(i pi t) for real t.       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CLDouble_ExpiPi                                                  *
 *  Purpose:                                                                  *
 *      Computes the point on the unit circle corresponding to a normalized   *
 *      phase t. That, given a real number t, this computes:                  *
 *                                                                            *
 *          f(t) = e^{i pi t}                                                 *
 *               = exp(i pi t)                                                *
 *               = (cos(pi t), sin(pi t))                                     *
 *                                                                            *
 *  Arguments:                                                                *
 *      t (long double):                                                      *
 *          The normalized phase.                                             *
 *  Output:                                                                   *
 *      exp_i_pi_t (tmpl_ComplexLongDouble):                                  *
 *          The point on the unit circle corresponding to t.                  *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_SinCosPi:                                            *
 *              Computes sin(pi t) and cos(pi t) simultaneously.              *
 *  Method:                                                                   *
 *      Compute x = cos(pi t) and y = sin(pi t) and return z = x + iy.        *
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
 *  Date:       February 12, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/07/13: Ryan Maguire                                                  *
 *      Changed src/complex/tmpl_complex_expipi_ldouble.c to include this.    *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPLEX_EXPIPI_LDOUBLE_H
#define TMPL_COMPLEX_EXPIPI_LDOUBLE_H

/*  TMPL_INLINE_DECL found here.                                              */
#include <libtmpl/include/tmpl_config.h>

/*  Header file containing math functions.                                    */
#include <libtmpl/include/tmpl_math.h>

/*  Complex routines and data types defined here.                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Computes the point on the unit circle with angle pi*t from the real axis. */
TMPL_INLINE_DECL
tmpl_ComplexLongDouble tmpl_CLDouble_ExpiPi(long double t)
{
    /*  Declare a variable for the output.                                    */
    tmpl_ComplexLongDouble z;

    /*  Use SinCosPi to compute sin(pi t) and cos(pi t), simultaneously, and  *
     *  store the results in the imaginary and real part of z, respectively.  */
    tmpl_LDouble_SinCosPi(t, &z.dat[1], &z.dat[0]);
    return z;
}
/*  End of tmpl_CLDouble_ExpiPi.                                              */

#endif
/*  End of include guard.                                                     */
