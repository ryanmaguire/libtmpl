/******************************************************************************
 *                                 LICENSE                                    *
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
 *                          tmpl_create_svg_canvas                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Create an SVG canvas.                                                 *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_svg.h:                                                           *
 *          Header file where tmpl_SVG_Color is defined.                      *
 *  2.) stdlib.h:                                                             *
 *          Standard C header file containing malloc.                         *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 19 2021                                                  *
 ******************************************************************************/

/*  tmpl_SVG_Color data type is defined here.                                 */
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_svg.h>
#include <stdlib.h>

/*  Function for transforming user coordinates to the coordinate of the file. *
 *  That is, the user coordinates are of the form (x, y), a point in the      *
 *  Cartesian plane, whereas the file coordinates depend on the .svg/.ps/.pdf *
 *  file. This function transforms the x coordinate.                          */
static double tmpl_SVG_Canvas_X_Transform(tmpl_SVG_Canvas *canvas, double x)
{
    /*  Compute the transformed x coordinate and return.                      */
    return canvas->x_shift + canvas->x_scale * x;
}

/*  Same as __kissvg_CanvasTransformX but for the y coordinate.               */
static double tmpl_SVG_Canvas_Y_Transform(tmpl_SVG_Canvas *canvas, double y)
{
    /*  Compute the transformed x coordinate and return.                      */
    return canvas->y_shift - canvas->y_scale * y;
}

/*  Function for creating an SVG canvas.                                      */
tmpl_SVG_Canvas *
tmpl_Create_SVG_Canvas(unsigned int width, unsigned int height,
                       double x_min, double x_max, double y_min, double y_max,
                       tmpl_SVG_Color background, tmpl_SVG_Pen outline,
                       tmpl_Bool use_one_to_one_aspect_ratio)
{
    /*  Allocate memory for the canvas using malloc.                          */
    tmpl_SVG_Canvas *canvas = malloc(sizeof(*canvas));

    /*  If malloc fails, it returns NULL. Check for this.                     */
    if (canvas == NULL)
        return NULL;

    /*  Otherwise, set the values in this canvas to the given inputs.         */
    canvas->width = width;
    canvas->height = height;
    canvas->background = background;
    canvas->outline = outline;

    /*  Compute the scale and shift factors and store them in the canvas.     */
    canvas->x_scale = (double)width/(x_max - x_min);
    canvas->y_scale = (double)height/(y_max - y_min);

    /*  If 1-1 aspect ratio has been requested, choose the smaller of x_scale *
     *  and y_scale and set both variables to this value. This ensures the    *
     *  drawing does not fall outside of the bounds.                          */
    if (use_one_to_one_aspect_ratio)
    {
        if (canvas->x_scale < canvas->y_scale)
            canvas->y_scale = canvas->x_scale;
        else
            canvas->x_scale = canvas->y_scale;
    }

    canvas->x_shift = 0.5 * ((double)width - (x_min + x_max)*canvas->x_scale);
    canvas->y_shift = 0.5 * ((double)height - (y_min + y_max)*canvas->y_scale);

    /*  And have the function pointers point to the above functions.          */
    canvas->X_Transform = tmpl_SVG_Canvas_X_Transform;
    canvas->Y_Transform = tmpl_SVG_Canvas_Y_Transform;
    return canvas;
}
/*  End of tmpl_Create_SVG_Canvas.                                            */
