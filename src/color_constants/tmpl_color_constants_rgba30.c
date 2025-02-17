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
 *                         tmpl_color_constants_rgba30                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 30-bit RGBA format.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba30.h:                                                        *
 *          Header file providing the tmpl_RGBA30 struct.                     *
 *  2.) tmpl_rgba30_constants.h:                                              *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGBA30 data type defined here.                                       */
#include <libtmpl/include/types/tmpl_rgba30.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgba30_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For 30-bit RGBA this is 0 and 1023 = 2^10-1, respectively. */
const tmpl_RGBA30 tmpl_RGBA30_Black = {0x000U, 0x000U, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_White = {0x3FFU, 0x3FFU, 0x3FFU, 1.0};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGBA30 tmpl_RGBA30_Red = {0x3FFU, 0x000U, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Green = {0x000U, 0x3FFU, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Blue = {0x000U, 0x000U, 0x3FFU, 1.0};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGBA30 tmpl_RGBA30_Cyan = {0x000U, 0x3FFU, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Yellow = {0x3FFU, 0x3FFU, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Magenta = {0x3FFU, 0x000U, 0x3FFU, 1.0};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGBA30 tmpl_RGBA30_Dark_Gray = {0x0FFU, 0x0FFU, 0x0FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Gray = {0x1FFU, 0x1FFU, 0x1FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Light_Gray = {0x2FFU, 0x2FFU, 0x2FFU, 1.0};

/*  Different types of blue.                                                  */
const tmpl_RGBA30 tmpl_RGBA30_Royal_Blue = {0x000U, 0x0CCU, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Dark_Blue = {0x000U, 0x000U, 0x1FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Light_Blue = {0x265U, 0x332U, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Marine = {0x132U, 0x132U, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Azure = {0x000U, 0x1FFU, 0x3FFU, 1.0};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGBA30 tmpl_RGBA30_Purple = {0x2CCU, 0x000U, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Violet = {0x1FFU, 0x000U, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Lavender = {0x332U, 0x332U, 0x3FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Hot_Pink = {0x3FFU, 0x066U, 0x332U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Deep_Pink = {0x3FFU, 0x066U, 0x265U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Pink = {0x3FFU, 0x199U, 0x3FFU, 1.0};

/*  Orange and other shades of red.                                           */
const tmpl_RGBA30 tmpl_RGBA30_Crimson = {0x332U, 0x000U, 0x066U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Orange = {0x3FFU, 0x199U, 0x066U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Carrot = {0x3FFU, 0x265U, 0x132U, 1.0};

/*  Various types of green.                                                   */
const tmpl_RGBA30 tmpl_RGBA30_Dark_Green = {0x0FFU, 0x1FFU, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Teal = {0x000U, 0x1FFU, 0x1FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Lime = {0x2FFU, 0x398U, 0x000U, 1.0};

/*  A few more colors.                                                        */
const tmpl_RGBA30 tmpl_RGBA30_Brown = {0x132U, 0x0CCU, 0x000U, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Sand = {0x398U, 0x332U, 0x1FFU, 1.0};
const tmpl_RGBA30 tmpl_RGBA30_Mustard = {0x398U, 0x332U, 0x132U, 1.0};
