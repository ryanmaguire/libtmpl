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
 *                         tmpl_color_constants_rgb30                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 30-bit RGB format.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgb30.h:                                                         *
 *          Header file providing the tmpl_RGB30 struct.                      *
 *  2.) tmpl_rgb30_constants.h:                                               *
 *          Header file where the constants are declared.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  tmpl_RGB30 data type defined here.                                        */
#include <libtmpl/include/types/tmpl_rgb30.h>

/*  Header file where the color constants are declared.                       */
#include <libtmpl/include/constants/tmpl_rgb30_constants.h>

/*  Black and white, set to the minimum and maximum possible values in each   *
 *  color channel. For 30-bit RGB this is 0 and 1023 = 2^10-1, respectively.  */
const tmpl_RGB30 tmpl_RGB30_Black = {0x000U, 0x000U, 0x000U};
const tmpl_RGB30 tmpl_RGB30_White = {0x3FFU, 0x3FFU, 0x3FFU};

/*  The RGB colors (red-green-blue). Set max value in the appropriate channel.*/
const tmpl_RGB30 tmpl_RGB30_Red = {0x3FFU, 0x000U, 0x000U};
const tmpl_RGB30 tmpl_RGB30_Green = {0x000U, 0x3FFU, 0x000U};
const tmpl_RGB30 tmpl_RGB30_Blue = {0x000U, 0x000U, 0x3FFU};

/*  The CYM colors (cyan-yellow-magenta). Blends RGB colors together.         */
const tmpl_RGB30 tmpl_RGB30_Cyan = {0x000U, 0x3FFU, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Yellow = {0x3FFU, 0x3FFU, 0x000U};
const tmpl_RGB30 tmpl_RGB30_Magenta = {0x3FFU, 0x000U, 0x3FFU};

/*  Various types of gray, equal amounts in each color channel.               */
const tmpl_RGB30 tmpl_RGB30_Dark_Gray = {0x0FFU, 0x0FFU, 0x0FFU};
const tmpl_RGB30 tmpl_RGB30_Gray = {0x1FFU, 0x1FFU, 0x1FFU};
const tmpl_RGB30 tmpl_RGB30_Light_Gray = {0x2FFU, 0x2FFU, 0x2FFU};

/*  Different types of blue.                                                  */
const tmpl_RGB30 tmpl_RGB30_Royal_Blue = {0x000U, 0x0CCU, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Dark_Blue = {0x000U, 0x000U, 0x1FFU};
const tmpl_RGB30 tmpl_RGB30_Light_Blue = {0x265U, 0x332U, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Marine = {0x132U, 0x132U, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Azure = {0x000U, 0x1FFU, 0x3FFU};

/*  Red / Blue blends resulting in different types of purple and pink.        */
const tmpl_RGB30 tmpl_RGB30_Purple = {0x2CCU, 0x000U, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Violet = {0x1FFU, 0x000U, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Lavender = {0x332U, 0x332U, 0x3FFU};
const tmpl_RGB30 tmpl_RGB30_Hot_Pink = {0x3FFU, 0x066U, 0x332U};
const tmpl_RGB30 tmpl_RGB30_Deep_Pink = {0x3FFU, 0x066U, 0x265U};
const tmpl_RGB30 tmpl_RGB30_Pink = {0x3FFU, 0x199U, 0x3FFU};

/*  Orange and other shades of red.                                           */
const tmpl_RGB30 tmpl_RGB30_Crimson = {0x332U, 0x000U, 0x066U};
const tmpl_RGB30 tmpl_RGB30_Orange = {0x3FFU, 0x199U, 0x066U};
const tmpl_RGB30 tmpl_RGB30_Carrot = {0x3FFU, 0x265U, 0x132U};

/*  Various types of green.                                                   */
const tmpl_RGB30 tmpl_RGB30_Dark_Green = {0x0FFU, 0x1FFU, 0x000U};
const tmpl_RGB30 tmpl_RGB30_Teal = {0x000U, 0x1FFU, 0x1FFU};
const tmpl_RGB30 tmpl_RGB30_Lime = {0x2FFU, 0x398U, 0x000U};

/*  A few more colors.                                                        */
const tmpl_RGB30 tmpl_RGB30_Brown = {0x132U, 0x0CCU, 0x000U};
const tmpl_RGB30 tmpl_RGB30_Sand = {0x398U, 0x332U, 0x1FFU};
const tmpl_RGB30 tmpl_RGB30_Mustard = {0x398U, 0x332U, 0x132U};
