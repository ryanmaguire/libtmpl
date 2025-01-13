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
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Float_Sqrt:                                                  *
 *              Computes the square root of a real number.                    *
 *      tmpl_complex.h:                                                       *
 *          tmpl_CFloat_Polar:                                                *
 *              Computes r * exp(i theta) with theta in radians.              *
 *  Method:                                                                   *
 *      Compute sqrt(power) * e^{i psi} and return.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_INLINE_DECL macro.                *
 *  2.) tmpl_complex_float.h:                                                 *
 *          Header file where complex numbers are defined.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 21, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_OPTICAL_TRANSMITTANCE_FLOAT_H
#define TMPL_OPTICAL_TRANSMITTANCE_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Complex numbers provided here.                                            */
#include <libtmpl/include/tmpl_complex_float.h>

/*  The polar function is inlined. Check for inline support.                  */
#if TMPL_USE_INLINE == 1

/*  Routine is found here.                                                    */
#include <libtmpl/include/complex/tmpl_complex_polar_float.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, declare it as extern.                             */
extern tmpl_ComplexFloat tmpl_CFloat_Polar(float r, float theta);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  And tell the compiler about the square root function.                     */
extern float tmpl_Float_Sqrt(float x);

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
