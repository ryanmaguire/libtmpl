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
 *                          tmpl_color_constants_rgba                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in real RGBA format.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba.h:                                                          *
 *          Header file providing the tmpl_RGBA struct.                       *
 *  2.) tmpl_rgba_constants.h:                                                *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGBA data type defined here.                                         */
#include <libtmpl/include/types/tmpl_rgba.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgba_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For real-valued RGB this is 0 and 1, respectively.         */
const tmpl_RGBA tmpl_RGBA_Black = {{0.0, 0.0, 0.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_White = {{1.0, 1.0, 1.0, 1.0}};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGBA tmpl_RGBA_Red = {{1.0, 0.0, 0.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Green = {{0.0, 1.0, 0.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Blue = {{0.0, 0.0, 1.0, 1.0}};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGBA tmpl_RGBA_Cyan = {{0.0, 1.0, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Yellow = {{1.0, 1.0, 0.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Magenta = {{1.0, 0.0, 1.0, 1.0}};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGBA tmpl_RGBA_Dark_Gray = {{0.25, 0.25, 0.25, 1.0}};
const tmpl_RGBA tmpl_RGBA_Gray = {{0.50, 0.50, 0.50, 1.0}};
const tmpl_RGBA tmpl_RGBA_Light_Gray = {{0.75, 0.75, 0.75, 1.0}};

/*  Different types of blue.                                                  */
const tmpl_RGBA tmpl_RGBA_Royal_Blue = {{0.0, 0.2, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Dark_Blue = {{0.0, 0.0, 0.6, 1.0}};
const tmpl_RGBA tmpl_RGBA_Light_Blue = {{0.6, 0.8, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Marine = {{0.3, 0.3, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Azure = {{0.0, 0.5, 1.0, 1.0}};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGBA tmpl_RGBA_Purple = {{0.7, 0.0, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Violet = {{0.5, 0.0, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Lavender = {{0.8, 0.8, 1.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Hot_Pink = {{1.0, 0.1, 0.8, 1.0}};
const tmpl_RGBA tmpl_RGBA_Deep_Pink = {{1.0, 0.1, 0.6, 1.0}};
const tmpl_RGBA tmpl_RGBA_Pink = {{1.0, 0.4, 1.0, 1.0}};

/*  Orange and other shades of red.                                           */
const tmpl_RGBA tmpl_RGBA_Crimson = {{0.8, 0.0, 0.1, 1.0}};
const tmpl_RGBA tmpl_RGBA_Orange = {{1.0, 0.4, 0.1, 1.0}};
const tmpl_RGBA tmpl_RGBA_Carrot = {{1.0, 0.6, 0.3, 1.0}};

/*  Various types of green.                                                   */
const tmpl_RGBA tmpl_RGBA_Dark_Green = {{0.25, 0.50, 0.00, 1.0}};
const tmpl_RGBA tmpl_RGBA_Teal = {{0.00, 0.50, 0.50, 1.0}};
const tmpl_RGBA tmpl_RGBA_Lime = {{0.75, 0.90, 0.00, 1.0}};

/*  A few more colors.                                                        */
const tmpl_RGBA tmpl_RGBA_Brown = {{0.3, 0.2, 0.0, 1.0}};
const tmpl_RGBA tmpl_RGBA_Sand = {{0.9, 0.8, 0.5, 1.0}};
const tmpl_RGBA tmpl_RGBA_Mustard = {{0.9, 0.8, 0.3, 1.0}};
