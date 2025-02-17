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
 *                           tmpl_rgba24_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 24-bit RGBA format.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba24.h:                                                        *
 *          Header file providing the tmpl_RGBA24 struct.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RGBA24_CONSTANTS_H
#define TMPL_RGBA24_CONSTANTS_H

/*  24-bit RGBA color data type defined here.                                 */
#include <libtmpl/include/types/tmpl_rgba24.h>

/*  Commonly used colors in 24-bit RGBA format.                               */
extern const tmpl_RGBA24 tmpl_RGBA24_Black;
extern const tmpl_RGBA24 tmpl_RGBA24_White;
extern const tmpl_RGBA24 tmpl_RGBA24_Red;
extern const tmpl_RGBA24 tmpl_RGBA24_Green;
extern const tmpl_RGBA24 tmpl_RGBA24_Blue;
extern const tmpl_RGBA24 tmpl_RGBA24_Cyan;
extern const tmpl_RGBA24 tmpl_RGBA24_Magenta;
extern const tmpl_RGBA24 tmpl_RGBA24_Yellow;
extern const tmpl_RGBA24 tmpl_RGBA24_Gray;
extern const tmpl_RGBA24 tmpl_RGBA24_Dark_Gray;
extern const tmpl_RGBA24 tmpl_RGBA24_Light_Gray;

/*  Various types of blue.                                                    */
extern const tmpl_RGBA24 tmpl_RGBA24_Dark_Blue;
extern const tmpl_RGBA24 tmpl_RGBA24_Light_Blue;
extern const tmpl_RGBA24 tmpl_RGBA24_Royal_Blue;
extern const tmpl_RGBA24 tmpl_RGBA24_Marine;
extern const tmpl_RGBA24 tmpl_RGBA24_Azure;

/*  Red / Blue blends resulting in different types of purple and pink.        */
extern const tmpl_RGBA24 tmpl_RGBA24_Purple;
extern const tmpl_RGBA24 tmpl_RGBA24_Violet;
extern const tmpl_RGBA24 tmpl_RGBA24_Lavender;
extern const tmpl_RGBA24 tmpl_RGBA24_Hot_Pink;
extern const tmpl_RGBA24 tmpl_RGBA24_Deep_Pink;
extern const tmpl_RGBA24 tmpl_RGBA24_Pink;

/*  Orange and other shades of red.                                           */
extern const tmpl_RGBA24 tmpl_RGBA24_Orange;
extern const tmpl_RGBA24 tmpl_RGBA24_Crimson;
extern const tmpl_RGBA24 tmpl_RGBA24_Carrot;

/*  Various types of green.                                                   */
extern const tmpl_RGBA24 tmpl_RGBA24_Dark_Green;
extern const tmpl_RGBA24 tmpl_RGBA24_Teal;
extern const tmpl_RGBA24 tmpl_RGBA24_Lime;

/*  A few more colors.                                                        */
extern const tmpl_RGBA24 tmpl_RGBA24_Brown;
extern const tmpl_RGBA24 tmpl_RGBA24_Sand;
extern const tmpl_RGBA24 tmpl_RGBA24_Mustard;

#endif
/*  End of include guard.                                                     */
