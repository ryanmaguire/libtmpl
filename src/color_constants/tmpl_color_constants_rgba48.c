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
 *                         tmpl_color_constants_rgba48                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 48-bit RGBA format.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba48.h:                                                        *
 *          Header file providing the tmpl_RGBA48 struct.                     *
 *  2.) tmpl_rgba48_constants.h:                                              *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGBA48 data type defined here.                                       */
#include <libtmpl/include/types/tmpl_rgba48.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgba48_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For 48-bit RGBA this is 0 and 65535 = 2^16-1, respectively.*/
const tmpl_RGBA48 tmpl_RGBA48_Black = {{0x0000U, 0x0000U, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_White = {{0xFFFFU, 0xFFFFU, 0xFFFFU}, 1.0};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGBA48 tmpl_RGBA48_Red = {{0xFFFFU, 0x0000U, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Green = {{0x0000U, 0xFFFFU, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Blue = {{0x0000U, 0x0000U, 0xFFFFU}, 1.0};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGBA48 tmpl_RGBA48_Cyan = {{0x0000U, 0xFFFFU, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Yellow = {{0xFFFFU, 0xFFFFU, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Magenta = {{0xFFFFU, 0x0000U, 0xFFFFU}, 1.0};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGBA48 tmpl_RGBA48_Dark_Gray = {{0x3FFFU, 0x3FFFU, 0x3FFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Gray = {{0x8CCCU, 0x8CCCU, 0x8CCCU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Light_Gray = {{0xBFFFU, 0xBFFFU, 0xBFFFU}, 1.0};

/*  Different types of blue.                                                  */
const tmpl_RGBA48 tmpl_RGBA48_Royal_Blue = {{0x0000U, 0x3333U, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Dark_Blue = {{0x0000U, 0x0000U, 0x9999U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Light_Blue = {{0x9999U, 0xCCCCU, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Marine = {{0x4CCCU, 0x4CCCU, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Azure = {{0x0000U, 0x7FFFU, 0xFFFFU}, 1.0};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGBA48 tmpl_RGBA48_Purple = {{0xB332U, 0x0000U, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Violet = {{0x7FFFU, 0x0000U, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Lavender = {{0xCCCCU, 0xCCCCU, 0xFFFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Hot_Pink = {{0xFFFFU, 0x1999U, 0xCCCCU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Deep_Pink = {{0xFFFFU, 0x1999U, 0x9999U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Pink = {{0xFFFFU, 0x6666U, 0xFFFFU}, 1.0};

/*  Orange and other shades of red.                                           */
const tmpl_RGBA48 tmpl_RGBA48_Crimson = {{0xCCCCU, 0x0000U, 0x1999U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Orange = {{0xFFFFU, 0x6666U, 0x1999U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Carrot = {{0xFFFFU, 0x9999U, 0x4CCCU}, 1.0};

/*  Various types of green.                                                   */
const tmpl_RGBA48 tmpl_RGBA48_Dark_Green = {{0x3FFFU, 0x7FFFU, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Teal = {{0x0000U, 0x7FFFU, 0x7FFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Lime = {{0xBFFFU, 0xE665U, 0x0000U}, 1.0};

/*  A few more colors.                                                        */
const tmpl_RGBA48 tmpl_RGBA48_Brown = {{0x4CCCU, 0x3333U, 0x0000U}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Sand = {{0xE665U, 0xCCCCU, 0x7FFFU}, 1.0};
const tmpl_RGBA48 tmpl_RGBA48_Mustard = {{0xE665U, 0xCCCCU, 0x4CCCU}, 1.0};
