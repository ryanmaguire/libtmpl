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
 *                          tmpl_destroy_svg_canvas                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Destroy an SVG canvas.                                                *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_svg.h:                                                           *
 *          Header file where tmpl_SVG_Color is defined.                      *
 *  2.) stdlib.h:                                                             *
 *          Standard C header file containing free.                           *
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

#include <stdlib.h>
#include <libtmpl/include/tmpl_svg.h>

/*  Function for freeing the memory in a tmpl_SVG_Canvas.                     */
void tmpl_Destroy_SVG_Canvas(tmpl_SVG_Canvas **canvas_ptr)
{
    /*  If the input pointer is NULL, simply return.                          */
    if (canvas_ptr == NULL)
        return;

    /*  If the pointer being pointed to by canvas_ptr is also NULL, it is     *
     *  likely this canvas has already been destroyed. Return.                */
    if (*canvas_ptr == NULL)
        return;

    /*  Otherwise, since the canvas data type does not contain pointers, we   *
     *  need only free the pointer to the canvas.                             */
    free(*canvas_ptr);

    /*  Set the pointer to the canvas to NULL to prevent accidentally trying  *
     *  to destroy this canvas twice later on.                                */
    *canvas_ptr = NULL;
}
/*  End of tmpl_Destroy_SVG_Canvas.                                           */
