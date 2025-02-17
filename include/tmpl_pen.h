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
 *                                  tmpl_pen                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides tools for using pens which are used for drawing SVGs.        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file providing the TMPL_RESTRICT macro.                    *
 *  2.) tmpl_pen_type.h:                                                      *
 *          Header file where tmpl_Pen is defined.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 1, 2021                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_PEN_H
#define TMPL_PEN_H

/*  TMPL_RESTRICT macro found here.                                           */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_Pen definition is provided here.                                     */
#include <libtmpl/include/types/tmpl_pen_type.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Pen_Create                                                       *
 *  Purpose:                                                                  *
 *      Create a pen from a given color, thickness, and dash pattern.         *
 *  Arguments:                                                                *
 *      color (const tmpl_RGBA24 * TMPL_RESTRICT const):                      *
 *          A pointer to a 24-bit RGB color with alpha parameter.             *
 *      linewidth (double):                                                   *
 *          The thickness of the pen, a positive real number.                 *
 *      dash (const char * TMPL_RESTRICT const):                              *
 *          The dash array. Set to NULL to create a solid pen.                *
 *  Outputs:                                                                  *
 *      pen (tmpl_Pen):                                                       *
 *          The desired pen.                                                  *
 ******************************************************************************/
extern tmpl_Pen
tmpl_Pen_Create(const tmpl_RGBA24 * TMPL_RESTRICT const color,
                double linewidth, const char * TMPL_RESTRICT const dash);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Pen_Set_Color                                                    *
 *  Purpose:                                                                  *
 *      Changes the color in a pen.                                           *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * TMPL_RESTRICT const):                                 *
 *          A pointer to a pen, the pen that is being modified.               *
 *      color (const tmpl_RGBA24 * TMPL_RESTRICT const):                      *
 *          The desired new color for the pen.                                *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Pen_Set_Color(tmpl_Pen * TMPL_RESTRICT const pen,
                   const tmpl_RGBA24 * TMPL_RESTRICT const color);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Pen_Set_Dash_Pattern                                             *
 *  Purpose:                                                                  *
 *      Changes the dash pattern in a pen.                                    *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * TMPL_RESTRICT const):                                 *
 *          A pointer to a pen, the pen that is being modified.               *
 *      dash (const char * TMPL_RESTRICT const):                              *
 *          The desired new dash pattern for the pen. Use NULL for solid.     *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Pen_Set_Dash_Pattern(tmpl_Pen * TMPL_RESTRICT const pen,
                          const char * TMPL_RESTRICT const dash);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Pen_Set_Thickness                                                *
 *  Purpose:                                                                  *
 *      Sets the thickness of a pen, checking for legal values.               *
 *  Arguments:                                                                *
 *      pen (tmpl_Pen * const):                                               *
 *          A pointer to a pen, the pen that is being modified.               *
 *      thickness (double):                                                   *
 *          The thickness of the pen, a positive real number.                 *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 ******************************************************************************/
extern void tmpl_Pen_Set_Thickness(tmpl_Pen * const pen, double thickness);

#endif
/*  End of include guard.                                                     */
