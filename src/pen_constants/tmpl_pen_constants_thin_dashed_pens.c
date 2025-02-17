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
 *                    tmpl_pen_constants_thin_dashed_pens                     *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides pens used for drawing thin dashed lines and curves.          *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_pen_type.h:                                                      *
 *          Provides the typedef for the tmpl_Pen data type.                  *
 *  2.) tmpl_pen_constants_thin_dashed_pens.h:                                *
 *          Header file providing forward declarations for the pens.          *
 *  3.) tmpl_rgba24_constants.h:                                              *
 *          Header file providing common colors in 24-bit RGBA format.        *
 *  4.) stddef.h:                                                             *
 *          Standard library file providing NULL.                             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2025                                             *
 ******************************************************************************/

/*  Header file providing the tmpl_Pen type.                                  */
#include <libtmpl/include/types/tmpl_pen_type.h>

/*  Declarations for the constant pens provided here.                         */
#include <libtmpl/include/constants/tmpl_pen_thin_dashed_constants.h>

/*  The 24-bit RGBA colors. A pen is a color plus line width and dash array.  */
#include <libtmpl/include/constants/tmpl_rgba24_constants.h>

/*  Standard library header file providing the NULL macro.                    */
#include <stddef.h>

/*  Char array for a dashed pen. Equal amounts of fill and space for the dash.*
 *  Note that although the string only has 3 explicit characters, there is an *
 *  implicit NULL terminator at the end, hence the array needs four elements. */
static const char tmpl_pen_dash_char_array_thin_dashed_pen[4] = "8 8";

/*  Linewidth for the pens. tmpl_pen_type.h has TMPL_PEN_THIN_LINEWIDTH.      */
#define LINEWIDTH TMPL_PEN_THIN_LINEWIDTH

/*  The dash type for the pen. Given by the above char array.                 */
#define DASH tmpl_pen_dash_char_array_thin_dashed_pen

/*  Macro for creating a pen from a given RGBA24 color constant.              */
#define TMPL_DEFINE_PEN(Name) const tmpl_Pen \
tmpl_Pen_Thin_Dashed_##Name = {&tmpl_RGBA24_##Name, LINEWIDTH, DASH}

/*  Create all of the constant pens.                                          */
TMPL_DEFINE_PEN(Black);
TMPL_DEFINE_PEN(White);
TMPL_DEFINE_PEN(Red);
TMPL_DEFINE_PEN(Green);
TMPL_DEFINE_PEN(Blue);
TMPL_DEFINE_PEN(Cyan);
TMPL_DEFINE_PEN(Magenta);
TMPL_DEFINE_PEN(Yellow);
TMPL_DEFINE_PEN(Gray);
TMPL_DEFINE_PEN(Dark_Gray);
TMPL_DEFINE_PEN(Light_Gray);
TMPL_DEFINE_PEN(Dark_Blue);
TMPL_DEFINE_PEN(Light_Blue);
TMPL_DEFINE_PEN(Royal_Blue);
TMPL_DEFINE_PEN(Marine);
TMPL_DEFINE_PEN(Azure);
TMPL_DEFINE_PEN(Purple);
TMPL_DEFINE_PEN(Violet);
TMPL_DEFINE_PEN(Lavender);
TMPL_DEFINE_PEN(Hot_Pink);
TMPL_DEFINE_PEN(Deep_Pink);
TMPL_DEFINE_PEN(Pink);
TMPL_DEFINE_PEN(Orange);
TMPL_DEFINE_PEN(Crimson);
TMPL_DEFINE_PEN(Carrot);
TMPL_DEFINE_PEN(Dark_Green);
TMPL_DEFINE_PEN(Teal);
TMPL_DEFINE_PEN(Lime);
TMPL_DEFINE_PEN(Brown);
TMPL_DEFINE_PEN(Sand);
TMPL_DEFINE_PEN(Mustard);

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_DEFINE_PEN
#undef LINEWIDTH
#undef DASH
