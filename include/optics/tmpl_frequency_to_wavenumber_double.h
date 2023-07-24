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
 *                    tmpl_frequency_to_wavenumber_double                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Converts a frequency in Hertz to a wave number.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Frequency_To_Wavenumber                                   *
 *  Purpose:                                                                  *
 *      Computes the wave number of a ray of light from the frequency of the  *
 *      ray, given in Hertz.                                                  *
 *  Arguments:                                                                *
 *      frequency (double):                                                   *
 *          A real number, the frequency of the ray of light.                 *
 *  Output:                                                                   *
 *      k (double):                                                           *
 *          The corresponding wave number.                                    *
 *  Method:                                                                   *
 *      Use the formula wave-number / frequency = 2 pi / speed-of-light.      *
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
#ifndef TMPL_FREQUENCY_TO_WAVENUMBER_DOUBLE_H
#define TMPL_FREQUENCY_TO_WAVENUMBER_DOUBLE_H

/*  Location of the TMPL_INLINE_DECL macro.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_optics.h>

/*  Converts the frequency of a ray of light to the corresponding wave number.*/
TMPL_INLINE_DECL
double tmpl_Double_Frequency_To_Wavenumber(double frequency)
{
    /*  The conversion factor is 2 pi over the speed of light.                */
    return 2.095845021951681812130606289821675823611E-05 * frequency;
}
/*  End of tmpl_Double_Frequency_To_Wavenumber.                               */

#endif
/*  End of include guard.                                                     */
