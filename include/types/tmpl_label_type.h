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
 *                               tmpl_label_type                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for labels used in vector graphics.                *
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
#ifndef TMPL_TYPES_LABEL_TYPE_H
#define TMPL_TYPES_LABEL_TYPE_H

/*  Booleans provided here.                                                   */
#include <libtmpl/include/tmpl_bool.h>

/*  2D vectors provided here. These serve as the anchor and shift in a label. */
#include <libtmpl/include/types/tmpl_vec2_double.h>

/*  Struct for adding text and labels in a drawing.                           */
typedef struct tmpl_Label_Def {

    /*  The anchor is where the object being labeled is located.              */
    const tmpl_TwoVector *anchor;

    /*  Shift is where the label will be placed relative to the anchor.       */
    const tmpl_TwoVector *shift;

    /*  The actual size of the text being displayed.                          */
    double font_size;

    /*  Rotation angle for the text (optional). Default is no rotation.       */
    double angle;

    /*  Boolean for optionally rotating the text in the image.                */
    tmpl_Bool is_rotated;

    /*  The actual text contained in the label.                               */
    const char *content;
} tmpl_Label;

#endif
/*  End of include guard.                                                     */
