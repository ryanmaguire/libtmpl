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
 *                         tmpl_color_constants_rgba24                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 24-bit RGBA format.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba24.h:                                                        *
 *          Header file providing the tmpl_RGBA24 struct.                     *
 *  2.) tmpl_rgba24_constants.h:                                              *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGBA24 data type defined here.                                       */
#include <libtmpl/include/types/tmpl_rgba24.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgba24_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For 24-bit RGBA this is 0 and 255 = 2^8-1, respectively.   */
const tmpl_RGBA24 tmpl_RGBA24_Black = {{0x00U, 0x00U, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_White = {{0xFFU, 0xFFU, 0xFFU}, 1.0};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGBA24 tmpl_RGBA24_Red = {{0xFFU, 0x00U, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Green = {{0x00U, 0xFFU, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Blue = {{0x00U, 0x00U, 0xFFU}, 1.0};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGBA24 tmpl_RGBA24_Cyan = {{0x00U, 0xFFU, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Yellow = {{0xFFU, 0xFFU, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Magenta = {{0xFFU, 0x00U, 0xFFU}, 1.0};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGBA24 tmpl_RGBA24_Dark_Gray = {{0x3FU, 0x3FU, 0x3FU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Gray = {{0x7FU, 0x7FU, 0x7FU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Light_Gray = {{0xBFU, 0xBFU, 0xBFU}, 1.0};

/*  Different types of blue.                                                  */
const tmpl_RGBA24 tmpl_RGBA24_Royal_Blue = {{0x00U, 0x33U, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Dark_Blue = {{0x00U, 0x00U, 0x99U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Light_Blue = {{0x99U, 0xCCU, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Marine = {{0x4CU, 0x4CU, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Azure = {{0x00U, 0x7FU, 0xFFU}, 1.0};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGBA24 tmpl_RGBA24_Purple = {{0xB2U, 0x00U, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Violet = {{0x7FU, 0x00U, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Lavender = {{0xCCU, 0xCCU, 0xFFU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Hot_Pink = {{0xFFU, 0x19U, 0xCCU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Deep_Pink = {{0xFFU, 0x19U, 0x99U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Pink = {{0xFFU, 0x66U, 0xFFU}, 1.0};

/*  Orange and other shades of red.                                           */
const tmpl_RGBA24 tmpl_RGBA24_Crimson = {{0xCCU, 0x00U, 0x19U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Orange = {{0xFFU, 0x66U, 0x19U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Carrot = {{0xFFU, 0x99U, 0x4CU}, 1.0};

/*  Various types of green.                                                   */
const tmpl_RGBA24 tmpl_RGBA24_Dark_Green = {{0x3FU, 0x7FU, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Teal = {{0x0U, 0x7FU, 0x7FU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Lime = {{0xBFU, 0xE5U, 0x00U}, 1.0};

/*  A few more colors.                                                        */
const tmpl_RGBA24 tmpl_RGBA24_Brown = {{0x4CU, 0x33U, 0x00U}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Sand = {{0xE5U, 0xCCU, 0x7FU}, 1.0};
const tmpl_RGBA24 tmpl_RGBA24_Mustard = {{0xE5U, 0xCCU, 0x4CU}, 1.0};
