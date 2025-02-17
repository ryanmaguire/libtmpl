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
 *                               tmpl_pen_type                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for a pen used for drawing objects.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/02/16: Ryan Maguire                                                  *
 *      Moved this typedef to its own file.                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_PEN_TYPE_H
#define TMPL_TYPES_PEN_TYPE_H

/*  24-bit RGB color struct with alpha compositing defined here.              */
#include <libtmpl/include/types/tmpl_rgba24.h>

/*  Pen used for drawing. Commonly used in vector graphics like SVGs.         */
typedef struct tmpl_Pen_Def {

    /*  The defining color, with possible alpha value for transparency.       */
    const tmpl_RGBA24 *color;

    /*  The line width for the pen.                                           */
    double thickness;

    /*  Optional pattern for dashes. Set to NULL if you want a solid pen.     */
    const char *dash_pattern;
} tmpl_Pen;

/*  Default parameters for various types of pens.                             */
#define TMPL_PEN_AXIS_LINEWIDTH (+2.0)
#define TMPL_PEN_THIN_LINEWIDTH (+0.5)
#define TMPL_PEN_THICK_LINEWIDTH (+1.5)
#define TMPL_PEN_DEFAULT_LINEWIDTH (+1.2)

#endif
/*  End of include guard.                                                     */
