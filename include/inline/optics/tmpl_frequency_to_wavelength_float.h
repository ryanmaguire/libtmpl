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
 *                     tmpl_frequency_to_wavelength_float                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts a frequency in Hertz to a wavelength in kilometers.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Frequency_To_Wavelength                                    *
 *  Purpose:                                                                  *
 *      Computes the wavelength of a ray of light, in kilometers, from the    *
 *      frequency of the ray, given in Hertz.                                 *
 *  Arguments:                                                                *
 *      frequency (float):                                                    *
 *          A real number, the frequency of the ray of light.                 *
 *  Output:                                                                   *
 *      lambda (float):                                                       *
 *          The corresponding wavelength.                                     *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use the formula frequency * wavelength = speed-of-light.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 21, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_FREQUENCY_TO_WAVELENGTH_FLOAT_H
#define TMPL_FREQUENCY_TO_WAVELENGTH_FLOAT_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Converts the frequency of a ray of light to the corresponding wavelength. */
TMPL_INLINE_DECL
float tmpl_Float_Frequency_To_Wavelength(float frequency)
{
    /*  The conversion is the speed of light divided by the input frequency.  */
    return 299792.4580F / frequency;
}
/*  End of tmpl_Float_Frequency_To_Wavelength.                                */

#endif
/*  End of include guard.                                                     */
