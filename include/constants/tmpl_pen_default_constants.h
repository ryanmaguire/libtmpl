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
 *                         tmpl_pen_default_constants                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used pens with default line width.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_pen.h:                                                           *
 *          Header file containing the tmpl_Pen definition.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_PEN_DEFAULT_CONSTANTS_H
#define TMPL_PEN_DEFAULT_CONSTANTS_H

/*  tmpl_Pen typedef provided here. Used for drawing vector graphics.         */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Commonly used pens. One for each constant RGBA24 color provided.          */
extern const tmpl_Pen tmpl_Pen_Black;
extern const tmpl_Pen tmpl_Pen_White;
extern const tmpl_Pen tmpl_Pen_Red;
extern const tmpl_Pen tmpl_Pen_Green;
extern const tmpl_Pen tmpl_Pen_Blue;
extern const tmpl_Pen tmpl_Pen_Cyan;
extern const tmpl_Pen tmpl_Pen_Magenta;
extern const tmpl_Pen tmpl_Pen_Yellow;
extern const tmpl_Pen tmpl_Pen_Gray;
extern const tmpl_Pen tmpl_Pen_Dark_Gray;
extern const tmpl_Pen tmpl_Pen_Light_Gray;
extern const tmpl_Pen tmpl_Pen_Dark_Blue;
extern const tmpl_Pen tmpl_Pen_Light_Blue;
extern const tmpl_Pen tmpl_Pen_Royal_Blue;
extern const tmpl_Pen tmpl_Pen_Marine;
extern const tmpl_Pen tmpl_Pen_Azure;
extern const tmpl_Pen tmpl_Pen_Purple;
extern const tmpl_Pen tmpl_Pen_Violet;
extern const tmpl_Pen tmpl_Pen_Lavender;
extern const tmpl_Pen tmpl_Pen_Hot_Pink;
extern const tmpl_Pen tmpl_Pen_Deep_Pink;
extern const tmpl_Pen tmpl_Pen_Pink;
extern const tmpl_Pen tmpl_Pen_Orange;
extern const tmpl_Pen tmpl_Pen_Crimson;
extern const tmpl_Pen tmpl_Pen_Carrot;
extern const tmpl_Pen tmpl_Pen_Dark_Green;
extern const tmpl_Pen tmpl_Pen_Teal;
extern const tmpl_Pen tmpl_Pen_Lime;
extern const tmpl_Pen tmpl_Pen_Brown;
extern const tmpl_Pen tmpl_Pen_Sand;
extern const tmpl_Pen tmpl_Pen_Mustard;

#endif
/*  End of include guard.                                                     */
