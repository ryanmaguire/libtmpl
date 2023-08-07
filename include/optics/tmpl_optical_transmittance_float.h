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
 *                      tmpl_optical_transmittance_float                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes complex transmittance from power and phase.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CFloat_Optical_Transmittance                                     *
 *  Purpose:                                                                  *
 *      Computes the complex optical transmittance from normalized power and  *
 *      phase given in radians.                                               *
 *  Arguments:                                                                *
 *      power (float):                                                        *
 *          The normalized power.                                             *
 *      phase (float):                                                        *
 *          The angle of the complex transmittance with the positive real     *
 *          axis, given in radians.                                           *
 *  Output:                                                                   *
 *      T (tmpl_ComplexFloat):                                                *
 *          The optical transmittance.                                        *
 *  Method:                                                                   *
 *      Compute sqrt(power) * e^{i psi} and return.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_math.h:                                                          *
 *          Header file where complex numbers are defined.                    *
 *  3.) tmpl_complex.h:                                                       *
 *          Header file where the sqrt function is declared.                  *
 *  4.) tmpl_optics.h:                                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 21, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_OPTICAL_TRANSMITTANCE_FLOAT_H
#define TMPL_OPTICAL_TRANSMITTANCE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  sqrt function declared here.                                              */
#include <libtmpl/include/tmpl_math.h>

/*  Complex numbers defined here.                                             */
#include <libtmpl/include/tmpl_complex.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_optics.h>

/*  Computes complex transmittance from power and phase.                      */
TMPL_INLINE_DECL
tmpl_ComplexFloat
tmpl_CFloat_Optical_Transmittance(float power, float phase)
{
    /*  The radius of the point in the complex plane is given by the square   *
     *  root of the normalized power.                                         */
    const float radius = tmpl_Float_Sqrt(power);

    /*  The complex transmittance is r e^{i psi}, psi being the phase.        */
    return tmpl_CFloat_Polar(radius, phase);
}
/*  End of tmpl_CFloat_Optical_Transmittance.                                 */

#endif
/*  End of include guard.                                                     */
