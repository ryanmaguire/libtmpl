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
 *                              tmpl_svg_canvas                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for creating SVG figures.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_rgba24.h:                                                        *
 *          Location of the tmpl_RGBA24 color struct with alpha compositing.  *
 *  2.) tmpl_pen.h:                                                           *
 *          Header file containing the tmpl_Pen definition.                   *
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
#ifndef TMPL_TYPES_SVG_CANVAS_H
#define TMPL_TYPES_SVG_CANVAS_H

/*  24-bit RGB colors without alpha compositing. Used for the background.     */
#include <libtmpl/include/types/tmpl_rgb24.h>

/*  Pens used for drawing. The outline of the SVG is defined using a pen.     */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Struct containing the parameters for an SVG image.                        */
typedef struct tmpl_SVGCanvas_Def {

    /*  The size of the SVG, in pixels.                                       */
    unsigned int width, height;

    /*  x_shift and y_shift are used to center the figure. The center is not  *
     *  taken to be (0, 0), but rather the value corresponding to             *
     *  (width, height) / 2.                                                  */
    double x_shift, y_shift;

    /*  x_scale and y_scale are the scales applied to the user's coordinates  *
     *  so that the image is the correct size in the actual file.             */
    double x_scale, y_scale;

    /*  The background color of the SVG.                                      */
    const tmpl_RGB24 *background;

    /*  The outline color and thickness for the SVG.                          */
    const tmpl_Pen *outline;
} tmpl_SVGCanvas;

#endif
/*  End of include guard.                                                     */
