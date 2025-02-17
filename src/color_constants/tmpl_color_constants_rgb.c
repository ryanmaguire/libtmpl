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
 *                          tmpl_color_constants_rgb                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in real RGB format.                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgb.h:                                                           *
 *          Header file providing the tmpl_RGB struct.                        *
 *  2.) tmpl_rgb_constants.h:                                                 *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGB data type defined here.                                          */
#include <libtmpl/include/types/tmpl_rgb.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgb_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For real-valued RGB this is 0 and 1, respectively.         */
const tmpl_RGB tmpl_RGB_Black = {{0.0, 0.0, 0.0}};
const tmpl_RGB tmpl_RGB_White = {{1.0, 1.0, 1.0}};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGB tmpl_RGB_Red = {{1.0, 0.0, 0.0}};
const tmpl_RGB tmpl_RGB_Green = {{0.0, 1.0, 0.0}};
const tmpl_RGB tmpl_RGB_Blue = {{0.0, 0.0, 1.0}};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGB tmpl_RGB_Cyan = {{0.0, 1.0, 1.0}};
const tmpl_RGB tmpl_RGB_Yellow = {{1.0, 1.0, 0.0}};
const tmpl_RGB tmpl_RGB_Magenta = {{1.0, 0.0, 1.0}};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGB tmpl_RGB_Dark_Gray = {{0.25, 0.25, 0.25}};
const tmpl_RGB tmpl_RGB_Gray = {{0.50, 0.50, 0.50}};
const tmpl_RGB tmpl_RGB_Light_Gray = {{0.75, 0.75, 0.75}};

/*  Different types of blue.                                                  */
const tmpl_RGB tmpl_RGB_Royal_Blue = {{0.0, 0.2, 1.0}};
const tmpl_RGB tmpl_RGB_Dark_Blue = {{0.0, 0.0, 0.6}};
const tmpl_RGB tmpl_RGB_Light_Blue = {{0.6, 0.8, 1.0}};
const tmpl_RGB tmpl_RGB_Marine = {{0.3, 0.3, 1.0}};
const tmpl_RGB tmpl_RGB_Azure = {{0.0, 0.5, 1.0}};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGB tmpl_RGB_Purple = {{0.7, 0.0, 1.0}};
const tmpl_RGB tmpl_RGB_Violet = {{0.5, 0.0, 1.0}};
const tmpl_RGB tmpl_RGB_Lavender = {{0.8, 0.8, 1.0}};
const tmpl_RGB tmpl_RGB_Hot_Pink = {{1.0, 0.1, 0.8}};
const tmpl_RGB tmpl_RGB_Deep_Pink = {{1.0, 0.1, 0.6}};
const tmpl_RGB tmpl_RGB_Pink = {{1.0, 0.4, 1.0}};

/*  Orange and other shades of red.                                           */
const tmpl_RGB tmpl_RGB_Crimson = {{0.8, 0.0, 0.1}};
const tmpl_RGB tmpl_RGB_Orange = {{1.0, 0.4, 0.1}};
const tmpl_RGB tmpl_RGB_Carrot = {{1.0, 0.6, 0.3}};

/*  Various types of green.                                                   */
const tmpl_RGB tmpl_RGB_Dark_Green = {{0.25, 0.50, 0.00}};
const tmpl_RGB tmpl_RGB_Teal = {{0.00, 0.50, 0.50}};
const tmpl_RGB tmpl_RGB_Lime = {{0.75, 0.90, 0.00}};

/*  A few more colors.                                                        */
const tmpl_RGB tmpl_RGB_Brown = {{0.3, 0.2, 0.0}};
const tmpl_RGB tmpl_RGB_Sand = {{0.9, 0.8, 0.5}};
const tmpl_RGB tmpl_RGB_Mustard = {{0.9, 0.8, 0.3}};
