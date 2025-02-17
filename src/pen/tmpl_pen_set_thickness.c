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
 *                           tmpl_pen_set_thickness                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Changes the thickness in a pen.                                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Pen_Set_Thickness                                                *
 *  Purpose:                                                                  *
 *      Sets the thickness in a pen to a new value.                           *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * TMPL_RESTRICT const):                                 *
 *          The pen whose thickness is being changed.                         *
 *      thickness (double):                                                   *
 *          The desired thickness for the pen.                                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Check that the input is legal and copy it into the pen.               *
 *  Notes:                                                                    *
 *      1.) This function checks if the input pen is NULL.                    *
 *      2.) If the requested thickness is negative, thickness is set to zero. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_pen_type.h:                                                      *
 *          Header with the definition of the tmpl_Pen data type.             *
 *  2.) tmpl_pen.h:                                                           *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 17, 2025                                             *
 ******************************************************************************/

/*  tmpl_Pen definition provided here.                                        */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_pen.h>

/*  Function for changing the thickness in a pen.                             */
void tmpl_Pen_Set_Thickness(tmpl_Pen * const pen, double thickness)
{
    /*  Avoid dereferencing a NULL pointer. Check that the pen is valid.      */
    if (!pen)
        return;

    /*  Thickness should be a non-negative real value. Check for this.        */
    if (thickness < 0.0)
        pen->thickness = 0.0;

    /*  Otherwise, copy the new value into the pen.                           */
    else
        pen->thickness = thickness;
}
/*  End of tmpl_Pen_Set_Thickness.                                            */
