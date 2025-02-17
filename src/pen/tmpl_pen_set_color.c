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
 *                             tmpl_pen_set_color                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Changes the color in a pen.                                           *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Pen_Set_Color                                                    *
 *  Purpose:                                                                  *
 *      Sets the color in a pen to a new value.                               *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * TMPL_RESTRICT const):                                 *
 *          The pen whose color is being changed.                             *
 *      color (const tmpl_RGBA24 * TMPL_RESTRICT const):                      *
 *          The desired color for the pen.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check that the input is legal and copy it into the pen.               *
 *  Notes:                                                                    *
 *      1.) NULL pointers are checked for both the pen and the color.         *
 *      2.) On compilers supporting the restrict keyword, color and pen are   *
 *          declared as restrict pointers and should not point to the same    *
 *          thing. To use this function properly, this should be true anyways.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_RESTRICT macro.                   *
 *  2.) tmpl_rgba24.h:                                                        *
 *          Header file providing the typedef for tmpl_RGBA24.                *
 *  3.) tmpl_pen_type.h:                                                      *
 *          Header with the definition of the tmpl_Pen data type.             *
 *  4.) tmpl_pen.h:                                                           *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 17, 2025                                             *
 ******************************************************************************/

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_RGBA24 typedef provided here.                                        */
#include <libtmpl/include/types/tmpl_rgba24.h>

/*  tmpl_Pen definition provided here.                                        */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_pen.h>

/*  24-bit RGBA color struct for the color black. Used for the default color. */
extern const tmpl_RGBA24 tmpl_RGBA24_Black;

/*  Function for changing the color in a pen.                                 */
void
tmpl_Pen_Set_Color(tmpl_Pen * TMPL_RESTRICT const pen,
                   const tmpl_RGBA24 * TMPL_RESTRICT const color)
{
    /*  Avoid dereferencing a NULL pointer. Check that the pen is valid.      */
    if (!pen)
        return;

    /*  Check for a valid color. If the pointer is NULL, make the pen black.  */
    if (!color)
        pen->color = &tmpl_RGBA24_Black;

    /*  Otherwise, use the user-provided color.                               */
    else
        pen->color = color;
}
/*  End of tmpl_Pen_Set_Color.                                                */
