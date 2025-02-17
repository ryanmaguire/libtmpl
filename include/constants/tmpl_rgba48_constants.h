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
 *                           tmpl_rgba48_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 48-bit RGBA format.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba48.h:                                                        *
 *          Header file providing the tmpl_RGBA48 struct.                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RGBA48_CONSTANTS_H
#define TMPL_RGBA48_CONSTANTS_H

/*  48-bit RGBA color data type defined here.                                 */
#include <libtmpl/include/types/tmpl_rgba48.h>

/*  Commonly used colors in 48-bit RGBA format.                               */
extern const tmpl_RGBA48 tmpl_RGBA48_Black;
extern const tmpl_RGBA48 tmpl_RGBA48_White;
extern const tmpl_RGBA48 tmpl_RGBA48_Red;
extern const tmpl_RGBA48 tmpl_RGBA48_Green;
extern const tmpl_RGBA48 tmpl_RGBA48_Blue;
extern const tmpl_RGBA48 tmpl_RGBA48_Cyan;
extern const tmpl_RGBA48 tmpl_RGBA48_Magenta;
extern const tmpl_RGBA48 tmpl_RGBA48_Yellow;
extern const tmpl_RGBA48 tmpl_RGBA48_Gray;
extern const tmpl_RGBA48 tmpl_RGBA48_Dark_Gray;
extern const tmpl_RGBA48 tmpl_RGBA48_Light_Gray;

/*  Various types of blue.                                                    */
extern const tmpl_RGBA48 tmpl_RGBA48_Dark_Blue;
extern const tmpl_RGBA48 tmpl_RGBA48_Light_Blue;
extern const tmpl_RGBA48 tmpl_RGBA48_Royal_Blue;
extern const tmpl_RGBA48 tmpl_RGBA48_Marine;
extern const tmpl_RGBA48 tmpl_RGBA48_Azure;

/*  Red / Blue blends resulting in different types of purple and pink.        */
extern const tmpl_RGBA48 tmpl_RGBA48_Purple;
extern const tmpl_RGBA48 tmpl_RGBA48_Violet;
extern const tmpl_RGBA48 tmpl_RGBA48_Lavender;
extern const tmpl_RGBA48 tmpl_RGBA48_Hot_Pink;
extern const tmpl_RGBA48 tmpl_RGBA48_Deep_Pink;
extern const tmpl_RGBA48 tmpl_RGBA48_Pink;

/*  Orange and other shades of red.                                           */
extern const tmpl_RGBA48 tmpl_RGBA48_Orange;
extern const tmpl_RGBA48 tmpl_RGBA48_Crimson;
extern const tmpl_RGBA48 tmpl_RGBA48_Carrot;

/*  Various types of green.                                                   */
extern const tmpl_RGBA48 tmpl_RGBA48_Dark_Green;
extern const tmpl_RGBA48 tmpl_RGBA48_Teal;
extern const tmpl_RGBA48 tmpl_RGBA48_Lime;

/*  A few more colors.                                                        */
extern const tmpl_RGBA48 tmpl_RGBA48_Brown;
extern const tmpl_RGBA48 tmpl_RGBA48_Sand;
extern const tmpl_RGBA48 tmpl_RGBA48_Mustard;

#endif
/*  End of include guard.                                                     */
