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
 *  1.) tmpl_rgb48.h:                                                         *
 *          Header file providing the tmpl_RGB48 struct.                      *
 *  2.) tmpl_rgb48_constants.h:                                               *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGB48 data type defined here.                                        */
#include <libtmpl/include/types/tmpl_rgb48.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgb48_constants.h>

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

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGB48 tmpl_RGB48_Dark_Gray = {{0x3FFFU, 0x3FFFU, 0x3FFFU}};
const tmpl_RGB48 tmpl_RGB48_Gray = {{0x8CCCU, 0x8CCCU, 0x8CCCU}};
const tmpl_RGB48 tmpl_RGB48_Light_Gray = {{0xBFFFU, 0xBFFFU, 0xBFFFU}};

/*  Different types of blue.                                                  */
const tmpl_RGB48 tmpl_RGB48_Royal_Blue = {{0x0000U, 0x3333U, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Dark_Blue = {{0x0000U, 0x0000U, 0x9999U}};
const tmpl_RGB48 tmpl_RGB48_Light_Blue = {{0x9999U, 0xCCCCU, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Marine = {{0x4CCCU, 0x4CCCU, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Azure = {{0x0000U, 0x7FFFU, 0xFFFFU}};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGB48 tmpl_RGB48_Purple = {{0xB332U, 0x0000U, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Violet = {{0x7FFFU, 0x0000U, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Lavender = {{0xCCCCU, 0xCCCCU, 0xFFFFU}};
const tmpl_RGB48 tmpl_RGB48_Hot_Pink = {{0xFFFFU, 0x1999U, 0xCCCCU}};
const tmpl_RGB48 tmpl_RGB48_Deep_Pink = {{0xFFFFU, 0x1999U, 0x9999U}};
const tmpl_RGB48 tmpl_RGB48_Pink = {{0xFFFFU, 0x6666U, 0xFFFFU}};

/*  Orange and other shades of red.                                           */
const tmpl_RGB48 tmpl_RGB48_Crimson = {{0xCCCCU, 0x0000U, 0x1999U}};
const tmpl_RGB48 tmpl_RGB48_Orange = {{0xFFFFU, 0x6666U, 0x1999U}};
const tmpl_RGB48 tmpl_RGB48_Carrot = {{0xFFFFU, 0x9999U, 0x4CCCU}};

/*  Various types of green.                                                   */
const tmpl_RGB48 tmpl_RGB48_Dark_Green = {{0x3FFFU, 0x7FFFU, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_Teal = {{0x0000U, 0x7FFFU, 0x7FFFU}};
const tmpl_RGB48 tmpl_RGB48_Lime = {{0xBFFFU, 0xE665U, 0x0000U}};

/*  A few more colors.                                                        */
const tmpl_RGB48 tmpl_RGB48_Brown = {{0x4CCCU, 0x3333U, 0x0000U}};
const tmpl_RGB48 tmpl_RGB48_Sand = {{0xE665U, 0xCCCCU, 0x7FFFU}};
const tmpl_RGB48 tmpl_RGB48_Mustard = {{0xE665U, 0xCCCCU, 0x4CCCU}};
