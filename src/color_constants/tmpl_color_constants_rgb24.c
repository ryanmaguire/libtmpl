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
 *  1.) tmpl_rgb24.h:                                                         *
 *          Header file providing the tmpl_RGB24 struct.                      *
 *  2.) tmpl_rgb24_constants.h:                                               *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGB24 data type defined here.                                        */
#include <libtmpl/include/types/tmpl_rgb24.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgb24_constants.h>

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

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGB24 tmpl_RGB24_Dark_Gray = {{0x3FU, 0x3FU, 0x3FU}};
const tmpl_RGB24 tmpl_RGB24_Gray = {{0x7FU, 0x7FU, 0x7FU}};
const tmpl_RGB24 tmpl_RGB24_Light_Gray = {{0xBFU, 0xBFU, 0xBFU}};

/*  Different types of blue.                                                  */
const tmpl_RGB24 tmpl_RGB24_Royal_Blue = {{0x00U, 0x33U, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Dark_Blue = {{0x00U, 0x00U, 0x99U}};
const tmpl_RGB24 tmpl_RGB24_Light_Blue = {{0x99U, 0xCCU, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Marine = {{0x4CU, 0x4CU, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Azure = {{0x00U, 0x7FU, 0xFFU}};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGB24 tmpl_RGB24_Purple = {{0xB2U, 0x00U, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Violet = {{0x7FU, 0x00U, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Lavender = {{0xCCU, 0xCCU, 0xFFU}};
const tmpl_RGB24 tmpl_RGB24_Hot_Pink = {{0xFFU, 0x19U, 0xCCU}};
const tmpl_RGB24 tmpl_RGB24_Deep_Pink = {{0xFFU, 0x19U, 0x99U}};
const tmpl_RGB24 tmpl_RGB24_Pink = {{0xFFU, 0x66U, 0xFFU}};

/*  Orange and other shades of red.                                           */
const tmpl_RGB24 tmpl_RGB24_Crimson = {{0xCCU, 0x00U, 0x19U}};
const tmpl_RGB24 tmpl_RGB24_Orange = {{0xFFU, 0x66U, 0x19U}};
const tmpl_RGB24 tmpl_RGB24_Carrot = {{0xFFU, 0x99U, 0x4CU}};

/*  Various types of green.                                                   */
const tmpl_RGB24 tmpl_RGB24_Dark_Green = {{0x3FU, 0x7FU, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_Teal = {{0x0U, 0x7FU, 0x7FU}};
const tmpl_RGB24 tmpl_RGB24_Lime = {{0xBFU, 0xE5U, 0x00U}};

/*  A few more colors.                                                        */
const tmpl_RGB24 tmpl_RGB24_Brown = {{0x4CU, 0x33U, 0x00U}};
const tmpl_RGB24 tmpl_RGB24_Sand = {{0xE5U, 0xCCU, 0x7FU}};
const tmpl_RGB24 tmpl_RGB24_Mustard = {{0xE5U, 0xCCU, 0x4CU}};
