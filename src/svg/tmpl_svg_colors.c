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
 *                             tmpl_svg_colors                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide a predefined colors for working with SVG files.               *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_svg.h:                                                           *
 *          Header file where tmpl_SVG_Color is defined.                      *
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
#include <libtmpl/include/tmpl_svg.h>

/*  Useful colors to have predefined.                                         */
const tmpl_SVG_Color tmpl_SVG_Black = {0x00U, 0x00U, 0x00U, 0.0};
const tmpl_SVG_Color tmpl_SVG_White = {0xFFU, 0xFFU, 0xFFU, 0.0};
const tmpl_SVG_Color tmpl_SVG_Red = {0xFFU, 0x00U, 0x00U, 0.0};
const tmpl_SVG_Color tmpl_SVG_Green = {0x00U, 0xFFU, 0x00U, 0.0};
const tmpl_SVG_Color tmpl_SVG_Blue = {0x00U, 0x00U, 0xFFU, 0.0};
const tmpl_SVG_Color tmpl_SVG_Yellow = {0xFFU, 0xFFU, 0x00U, 0.0};
