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
 *                    tmpl_wavelength_to_wavenumber_double                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts wavelength to wave number.                                   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Wavelength_To_Wavenumber                                  *
 *  Purpose:                                                                  *
 *      Computes the wave number from a given wavelength.                     *
 *  Arguments:                                                                *
 *      lambda (double):                                                      *
 *          A real number, the wavelength of the light ray.                   *
 *  Output:                                                                   *
 *      k (double):                                                           *
 *          The corresponding wave number.                                    *
 *  Method:                                                                   *
 *      Use the formula wavelength * wavenumber = 2 pi.                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_INLINE_DECL macro.                    *
 *  2.) tmpl_optics.h:                                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 21, 2023                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_WAVELENGTH_TO_WAVENUMBER_DOUBLE_H
#define TMPL_WAVELENGTH_TO_WAVENUMBER_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_optics.h>

/*  Converts the wavelength to the corresponding wave number.                 */
TMPL_INLINE_DECL
double tmpl_Double_Wavelength_To_Wavenumber(double lambda)
{
    /*  The conversion factor is 2 pi.                                     .  */
    return 6.283185307179586476925286766559005768394 / lambda;
}
/*  End of tmpl_Double_Wavelength_To_Wavenumber.                              */

#endif
/*  End of include guard.                                                     */
