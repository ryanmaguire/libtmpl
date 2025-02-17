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
 *                             tmpl_rgb_constants                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in real RGB format.                     *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgb.h:                                                           *
 *          Header file providing the tmpl_RGB struct.                        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RGB_CONSTANTS_H
#define TMPL_RGB_CONSTANTS_H

/*  Real RGB color data type defined here.                                    */
#include <libtmpl/include/types/tmpl_rgb.h>

/*  Commonly used colors in real RGB format.                                  */
extern const tmpl_RGB tmpl_RGB_Black;
extern const tmpl_RGB tmpl_RGB_White;
extern const tmpl_RGB tmpl_RGB_Red;
extern const tmpl_RGB tmpl_RGB_Green;
extern const tmpl_RGB tmpl_RGB_Blue;
extern const tmpl_RGB tmpl_RGB_Cyan;
extern const tmpl_RGB tmpl_RGB_Magenta;
extern const tmpl_RGB tmpl_RGB_Yellow;
extern const tmpl_RGB tmpl_RGB_Gray;
extern const tmpl_RGB tmpl_RGB_Dark_Gray;
extern const tmpl_RGB tmpl_RGB_Light_Gray;

/*  Various types of blue.                                                    */
extern const tmpl_RGB tmpl_RGB_Dark_Blue;
extern const tmpl_RGB tmpl_RGB_Light_Blue;
extern const tmpl_RGB tmpl_RGB_Royal_Blue;
extern const tmpl_RGB tmpl_RGB_Marine;
extern const tmpl_RGB tmpl_RGB_Azure;

/*  Red / Blue blends resulting in different types of purple and pink.        */
extern const tmpl_RGB tmpl_RGB_Purple;
extern const tmpl_RGB tmpl_RGB_Violet;
extern const tmpl_RGB tmpl_RGB_Lavender;
extern const tmpl_RGB tmpl_RGB_Hot_Pink;
extern const tmpl_RGB tmpl_RGB_Deep_Pink;
extern const tmpl_RGB tmpl_RGB_Pink;

/*  Orange and other shades of red.                                           */
extern const tmpl_RGB tmpl_RGB_Orange;
extern const tmpl_RGB tmpl_RGB_Crimson;
extern const tmpl_RGB tmpl_RGB_Carrot;

/*  Various types of green.                                                   */
extern const tmpl_RGB tmpl_RGB_Dark_Green;
extern const tmpl_RGB tmpl_RGB_Teal;
extern const tmpl_RGB tmpl_RGB_Lime;

/*  A few more colors.                                                        */
extern const tmpl_RGB tmpl_RGB_Brown;
extern const tmpl_RGB tmpl_RGB_Sand;
extern const tmpl_RGB tmpl_RGB_Mustard;

#endif
/*  End of include guard.                                                     */
