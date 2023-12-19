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
 *                         tmpl_color_constants_rgb24                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 24-bit RGB format.                   *
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
 *  color channel. For 24-bit RGB this is 0 and 255 = 2^8-1, respectively.    */
const tmpl_RGB24 tmpl_RGB24_Black = {{0x00U, 0x00U, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_White = {{0xFFU, 0xFFU, 0xFFU}};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGB24 tmpl_RGB24_Red = {{0xFFU, 0x00U, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_Green = {{0x00U, 0xFFU, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_Blue = {{0x00U, 0x00U, 0xFFU}};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGB24 tmpl_RGB24_Cyan = {{0x00U, 0xFFU, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Yellow = {{0xFFU, 0xFFU, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_Magenta = {{0xFFU, 0x00U, 0xFFU}};
