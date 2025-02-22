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
 *                               tmpl_svg_type                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for creating SVG figures.                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans.                                   *
 *  2.) tmpl_svg_canvas.h:                                                    *
 *          Location of the tmpl_SVGCanvas definition.                        *
 *  2.) stdio.h:                                                              *
 *          Standard library header providing the FILE type.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/02/22: Ryan Maguire                                                  *
 *      Moved this typedef to its own file.                                   *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_SVG_TYPE_H
#define TMPL_TYPES_SVG_TYPE_H

/*  C89 compliant Booleans provided here.                                     */
#include <libtmpl/include/tmpl_bool.h>

/*  Definition of the tmpl_SVGCanvas type. This provides the geometry and     *
 *  default colors for the underlying SVG.                                    */
#include <libtmpl/include/types/tmpl_svg_canvas.h>

/*  FILE data type provided here. This is used for the output file of the SVG.*/
#include <stdio.h>

/*  Struct for working with SVG files.                                        */
typedef struct tmpl_SVG_Def {

    /*  File pointer, used for writing the SVG to a file.                     */
    FILE *fp;

    /*  The canvas, which contains the geometry, size, background colors, and *
     *  default outline pen used for constructing the SVG.                    */
    const tmpl_SVGCanvas *canvas;

    /*  Boolean indicating the error status for the SVG.                      */
    tmpl_Bool error_occurred;

    /*  String detailing any error that occurred. Default is NULL.            */
    const char *error_message;
} tmpl_SVG;

#endif
/*  End of include guard.                                                     */
