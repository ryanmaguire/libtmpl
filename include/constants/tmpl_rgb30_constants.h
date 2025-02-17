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
 *                            tmpl_rgb30_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in 30-bit RGB format.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgb30.h:                                                         *
 *          Header file providing the tmpl_RGB30 struct.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RGB30_CONSTANTS_H
#define TMPL_RGB30_CONSTANTS_H

/*  30-bit RGB color data type defined here.                                  */
#include <libtmpl/include/types/tmpl_rgb30.h>

/*  Commonly used colors in 30-bit RGB format.                                */
extern const tmpl_RGB30 tmpl_RGB30_Black;
extern const tmpl_RGB30 tmpl_RGB30_White;
extern const tmpl_RGB30 tmpl_RGB30_Red;
extern const tmpl_RGB30 tmpl_RGB30_Green;
extern const tmpl_RGB30 tmpl_RGB30_Blue;
extern const tmpl_RGB30 tmpl_RGB30_Cyan;
extern const tmpl_RGB30 tmpl_RGB30_Magenta;
extern const tmpl_RGB30 tmpl_RGB30_Yellow;
extern const tmpl_RGB30 tmpl_RGB30_Gray;
extern const tmpl_RGB30 tmpl_RGB30_Dark_Gray;
extern const tmpl_RGB30 tmpl_RGB30_Light_Gray;

/*  Various types of blue.                                                    */
extern const tmpl_RGB30 tmpl_RGB30_Dark_Blue;
extern const tmpl_RGB30 tmpl_RGB30_Light_Blue;
extern const tmpl_RGB30 tmpl_RGB30_Royal_Blue;
extern const tmpl_RGB30 tmpl_RGB30_Marine;
extern const tmpl_RGB30 tmpl_RGB30_Azure;

/*  Red / Blue blends resulting in different types of purple and pink.        */
extern const tmpl_RGB30 tmpl_RGB30_Purple;
extern const tmpl_RGB30 tmpl_RGB30_Violet;
extern const tmpl_RGB30 tmpl_RGB30_Lavender;
extern const tmpl_RGB30 tmpl_RGB30_Hot_Pink;
extern const tmpl_RGB30 tmpl_RGB30_Deep_Pink;
extern const tmpl_RGB30 tmpl_RGB30_Pink;

/*  Orange and other shades of red.                                           */
extern const tmpl_RGB30 tmpl_RGB30_Orange;
extern const tmpl_RGB30 tmpl_RGB30_Crimson;
extern const tmpl_RGB30 tmpl_RGB30_Carrot;

/*  Various types of green.                                                   */
extern const tmpl_RGB30 tmpl_RGB30_Dark_Green;
extern const tmpl_RGB30 tmpl_RGB30_Teal;
extern const tmpl_RGB30 tmpl_RGB30_Lime;

/*  A few more colors.                                                        */
extern const tmpl_RGB30 tmpl_RGB30_Brown;
extern const tmpl_RGB30 tmpl_RGB30_Sand;
extern const tmpl_RGB30 tmpl_RGB30_Mustard;

#endif
/*  End of include guard.                                                     */
