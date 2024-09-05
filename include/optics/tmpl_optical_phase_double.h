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
 *                         tmpl_optical_phase_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes optical phase angle from complex transmittance.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Optical_Phase                                            *
 *  Purpose:                                                                  *
 *      Computes phase from (complex) optical transmittance.                  *
 *  Arguments:                                                                *
 *      transmittance (tmpl_ComplexDouble):                                   *
 *          The complex transmittance, unitless.                              *
 *  Output:                                                                   *
 *      phase (double):                                                       *
 *          The corresponding optical phase.                                  *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_Arctan2:                                              *
 *              Computes the angle the point (x, y) makes with the x-axis.    *
 *  Method:                                                                   *
 *      Given "power" and "phase", the optical transmittance is defined by:   *
 *                                                                            *
 *          transmittance = sqrt(power) * exp(i phase)                        *
 *                                                                            *
 *      The phase can be computed as the complex argument.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_complex_double.h:                                                *
 *          Header file with complex numbers.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 5, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_OPTICAL_PHASE_DOUBLE_H
#define TMPL_OPTICAL_PHASE_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Definition of complex numbers provided here.                              */
#include <libtmpl/include/tmpl_complex_double.h>

/*  The complex argument is computed with the Arctan2 function.               */
extern double tmpl_Double_Arctan2(double y, double x);

/*  Computes the phase from the complex optical transmittance.                */
TMPL_INLINE_DECL
double tmpl_CDouble_Optical_Phase(tmpl_ComplexDouble transmittance)
{
    /*  Transmittance is sqrt(power) * exp(i phase). Phase can be computed    *
     *  from the complex argument, which is the angle made with the x-axis.   */
    return tmpl_Double_Arctan2(transmittance.dat[1], transmittance.dat[0]);
}
/*  End of tmpl_CDouble_Optical_Phase.                                        */

#endif
/*  End of include guard.                                                     */
