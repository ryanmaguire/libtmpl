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
 *                              tmpl_pen_create                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates a pen from a desired color, line-width, and dash pattern.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Pen_Create                                                       *
 *  Purpose:                                                                  *
 *      Creates a pen from a specified color, thickness, and dash array.      *
 *  Arguments:                                                                *
 *      color (const tmpl_RGBA24 * TMPL_RESTRICT const):                      *
 *          The desired color for the pen.                                    *
 *      thickness (double):                                                   *
 *          The line-width for the pen.                                       *
 *      dash (const char * TMPL_RESTRICT const):                              *
 *          The dash pattern for the pen. Use NULL for a solid pen.           *
 *  Output:                                                                   *
 *      pen (tmpl_Pen):                                                       *
 *          The desired pen.                                                  *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check that the inputs are legal and copy them into the pen.           *
 *  Notes:                                                                    *
 *      1.) NULL pointers are allowed for the dash array. These represent     *
 *          solid pens.                                                       *
 *      2.) On compilers supporting the restrict keyword, color and dash are  *
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

/*  Function used for creating new pens.                                      */
tmpl_Pen
tmpl_Pen_Create(const tmpl_RGBA24 * TMPL_RESTRICT const color,
                double thickness, const char * TMPL_RESTRICT const dash)
{
    /*  Declare necessary variables. C89 requires declarations at the top.    */
    tmpl_Pen pen;

    /*  The thickness should be positive. Check for this.                     */
    if (thickness < 0.0)
        pen.thickness = 0.0;

    /*  Otherwise, copy the thickness into the pen.                           */
    else
        pen.thickness = thickness;

    /*  There is no check for the dash array. NULL pointers are allowed and   *
     *  are used to represent solid pens.                                     */
    pen.dash_pattern = dash;

    /*  Check for a valid color. If the pointer is NULL, make the pen black.  */
    if (!color)
        pen.color = &tmpl_RGBA24_Black;

    /*  Otherwise, use the user-provided color.                               */
    else
        pen.color = color;

    return pen;
}
/*  End of tmpl_Pen_Create.                                                   */
