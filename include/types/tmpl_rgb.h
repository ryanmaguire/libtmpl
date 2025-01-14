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
 *                                  tmpl_rgb                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a floating-point RGB color struct.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/01/13: Ryan Maguire                                                  *
 *      Moved this typedef to its own file.                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_RGB_H
#define TMPL_TYPES_RGB_H

/*  Color struct for "arbitrary" RGB color depth. In reality double has a     *
 *  52-bit mantissa, so this is a 156-bit color. There are 10^47 possible     *
 *  colors, far beyond the 10^14 colors possible with 48-bit colors, and      *
 *  much higher than the 10^7 colors present in standard 24-bit depths. So    *
 *  one may safely consider this "arbitrary" color depth.                     */
typedef struct tmpl_RGB_Def {

    /*  To make the data contiguous, use an array of three doubles.           */
    double dat[3];
} tmpl_RGB;

#endif
/*  End of include guard.                                                     */
