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
 *                             tmpl_rgba_constants                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used colors in real RGBA format.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba.h:                                                          *
 *          Header file providing the tmpl_RGBA struct.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 18, 2023                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_RGBA_CONSTANTS_H
#define TMPL_RGBA_CONSTANTS_H

/*  Real RGBA color data type defined here.                                   */
#include <libtmpl/include/types/tmpl_rgba.h>

/*  Commonly used colors in real RGBA format.                                 */
extern const tmpl_RGBA tmpl_RGBA_Black;
extern const tmpl_RGBA tmpl_RGBA_White;
extern const tmpl_RGBA tmpl_RGBA_Red;
extern const tmpl_RGBA tmpl_RGBA_Green;
extern const tmpl_RGBA tmpl_RGBA_Blue;
extern const tmpl_RGBA tmpl_RGBA_Cyan;
extern const tmpl_RGBA tmpl_RGBA_Magenta;
extern const tmpl_RGBA tmpl_RGBA_Yellow;
extern const tmpl_RGBA tmpl_RGBA_Gray;
extern const tmpl_RGBA tmpl_RGBA_Dark_Gray;
extern const tmpl_RGBA tmpl_RGBA_Light_Gray;

/*  Various types of blue.                                                    */
extern const tmpl_RGBA tmpl_RGBA_Dark_Blue;
extern const tmpl_RGBA tmpl_RGBA_Light_Blue;
extern const tmpl_RGBA tmpl_RGBA_Royal_Blue;
extern const tmpl_RGBA tmpl_RGBA_Marine;
extern const tmpl_RGBA tmpl_RGBA_Azure;

/*  Red / Blue blends resulting in different types of purple and pink.        */
extern const tmpl_RGBA tmpl_RGBA_Purple;
extern const tmpl_RGBA tmpl_RGBA_Violet;
extern const tmpl_RGBA tmpl_RGBA_Lavender;
extern const tmpl_RGBA tmpl_RGBA_Hot_Pink;
extern const tmpl_RGBA tmpl_RGBA_Deep_Pink;
extern const tmpl_RGBA tmpl_RGBA_Pink;

/*  Orange and other shades of red.                                           */
extern const tmpl_RGBA tmpl_RGBA_Orange;
extern const tmpl_RGBA tmpl_RGBA_Crimson;
extern const tmpl_RGBA tmpl_RGBA_Carrot;

/*  Various types of green.                                                   */
extern const tmpl_RGBA tmpl_RGBA_Dark_Green;
extern const tmpl_RGBA tmpl_RGBA_Teal;
extern const tmpl_RGBA tmpl_RGBA_Lime;

/*  A few more colors.                                                        */
extern const tmpl_RGBA tmpl_RGBA_Brown;
extern const tmpl_RGBA tmpl_RGBA_Sand;
extern const tmpl_RGBA tmpl_RGBA_Mustard;

#endif
/*  End of include guard.                                                     */
