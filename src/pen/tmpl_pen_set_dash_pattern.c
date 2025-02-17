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
 *                         tmpl_pen_set_dash_pattern                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Changes the dash pattern in a pen.                                    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Pen_Set_Dash_Pattern                                             *
 *  Purpose:                                                                  *
 *      Sets the dash pattern in a pen to a new value.                        *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * TMPL_RESTRICT const):                                 *
 *          The pen whose dash pattern is being changed.                      *
 *      dash (const char * TMPL_RESTRICT const):                              *
 *          The desired dash pattern for the pen.                             *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check that the input is legal and copy it into the pen.               *
 *  Notes:                                                                    *
 *      1.) This function checks if the input pen is NULL.                    *
 *      2.) The input dash pattern is allowed to be NULL. NULL pointers are   *
 *          used to represent solid pens.                                     *
 *      3.) On compilers supporting the restrict keyword, dash and pen are    *
 *          declared as restrict pointers and should not point to the same    *
 *          thing. To use this function properly, this should be true anyways.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_RESTRICT macro.                   *
 *  2.) tmpl_pen_type.h:                                                      *
 *          Header with the definition of the tmpl_Pen data type.             *
 *  3.) tmpl_pen.h:                                                           *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 17, 2025                                             *
 ******************************************************************************/

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_Pen definition provided here.                                        */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_pen.h>

/*  Function for changing the dash pattern in a pen.                          */
void
tmpl_Pen_Set_Dash_Pattern(tmpl_Pen * TMPL_RESTRICT const pen,
                          const char * TMPL_RESTRICT const dash)
{
    /*  Avoid dereferencing a NULL pointer. Check that the pen is valid.      */
    if (!pen)
        return;

    /*  NULL pointers for the string are allowed. These represent solid pens. */
    pen->dash_pattern = dash;
}
/*  End of tmpl_Pen_Set_Dash_Pattern.                                         */
