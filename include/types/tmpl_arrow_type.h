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
 *                              tmpl_arrow_type                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for arrows used in vector graphics.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/02/17: Ryan Maguire                                                  *
 *      Moved this typedef to its own file.                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_ARROW_TYPE_H
#define TMPL_TYPES_ARROW_TYPE_H

/*  tmpl_Pen defined here, used for drawing the arrow.                        */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  2D vector struct provided here. Defines the location of the arrow.        */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Arrow types supported by libtmpl.                                         */
typedef enum tmpl_ArrowType_Def {
    tmpl_arrow_type_none,
    tmpl_arrow_type_stealth,
    tmpl_arrow_type_reverse_stealth,
    tmpl_arrow_type_triangular,
    tmpl_arrow_type_reverse_triangular,
    tmpl_arrow_type_latex,
    tmpl_arrow_type_reverse_latex
} tmpl_ArrowType;

/*  Struct containing all of the information for arrows.                      */
typedef struct tmpl_Arrow_Def {

    /*  The type of arrow to draw (stealth, triangle, latex, etc).            */
    tmpl_ArrowType arrow_type;

    /*  The center of the arrow.                                              */
    const tmpl_TwoVector *anchor;

    /*  The direction the arrow is pointing.                                  */
    const tmpl_TwoVector *direction;

    /*  The color of the interior of the arrow drawn.                         */
    const tmpl_Pen *fill_pen;

    /*  The color of the outline of the arrow.                                */
    const tmpl_Pen *line_pen;

    /*  The radius of the arrow head. The arrow head is defined by three      *
     *  points on a circle about the point corresponding to the anchor.       */
    double arrow_size;
} tmpl_Arrow;

#endif
/*  End of include guard.                                                     */
