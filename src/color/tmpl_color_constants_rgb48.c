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
 *                         tmpl_color_constants_rgb48                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 48-bit RGB format.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_color.h:                                                         *
 *          Header file where the colors are declared.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Header file where color structs are typedef'd and colors declared.        */
#include <libtmpl/include/tmpl_color.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For 48-bit RGB this is 0 and 65535 = 2^16-1, respectively. */
const tmpl_RGB48 tmpl_RGB48_Black = {{0x0000U, 0x0000U, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_White = {{0xFFFFU, 0xFFFFU, 0xFFFFU}};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGB48 tmpl_RGB48_Red = {{0xFFFFU, 0x0000U, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_Green = {{0x0000U, 0xFFFFU, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_Blue = {{0x0000U, 0x0000U, 0xFFFFU}};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGB48 tmpl_RGB48_Cyan = {{0x0000U, 0xFFFFU, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Yellow = {{0xFFFFU, 0xFFFFU, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_Magenta = {{0xFFFFU, 0x0000U, 0xFFFFU}};
