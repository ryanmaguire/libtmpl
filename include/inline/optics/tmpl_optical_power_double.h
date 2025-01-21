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
 *                         tmpl_optical_power_double                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes optical power from complex transmittance.                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_CDouble_Optical_Power                                            *
 *  Purpose:                                                                  *
 *      Computes power from (complex) optical transmittance.                  *
 *  Arguments:                                                                *
 *      transmittance (tmpl_ComplexDouble):                                   *
 *          The complex transmittance, unitless.                              *
 *  Output:                                                                   *
 *      power (double):                                                       *
 *          The corresponding optical power.                                  *
 *  Called Functions:                                                         *
 *      tmpl_complex.h:                                                       *
 *          tmpl_CDouble_Abs_Squared:                                         *
 *              Computes |z|^2 for a complex number z.                        *
 *  Method:                                                                   *
 *      Given "power" and "phase", the optical transmittance is defined by:   *
 *                                                                            *
 *          transmittance = sqrt(power) * exp(i phase)                        *
 *                                                                            *
 *      The power can be recovered via |transmittance|^2.                     *
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
#ifndef TMPL_OPTICAL_POWER_DOUBLE_H
#define TMPL_OPTICAL_POWER_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Definition of complex numbers provided here.                              */
#include <libtmpl/include/types/tmpl_complex_double.h>

/*  The complex abs square function is inlined. Check for inline support.     */
#if TMPL_USE_INLINE == 1

/*  Routine is found here.                                                    */
#include <libtmpl/include/inline/complex/tmpl_complex_abs_squared_double.h>

#else
/*  Else for #if TMPL_USE_INLINE == 1.                                        */

/*  Lacking inline support, declare it as extern.                             */
extern double tmpl_CDouble_Abs_Squared(tmpl_ComplexDouble z);

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

/*  Computes the power from the complex optical transmittance.                */
TMPL_INLINE_DECL
double tmpl_CDouble_Optical_Power(tmpl_ComplexDouble transmittance)
{
    /*  Transmittance is sqrt(power) * exp(i phase). Power can be computed    *
     *  from the square of the absolute value of the transmittance.           */
    return tmpl_CDouble_Abs_Squared(transmittance);
}
/*  End of tmpl_CDouble_Optical_Power.                                        */

#endif
/*  End of include guard.                                                     */
