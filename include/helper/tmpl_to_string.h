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
 *                               tmpl_to_string                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a helper macro for creating a string from the variable name. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 19, 2026                                               *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_TO_STRING_H
#define TMPL_HELPER_TO_STRING_H

/*  #x is the standard way to create a string from a variable using the       *
 *  preprocessor. Some compilers do not like using this inside other macros.  *
 *  The usual trick is to use two macros, one that stringifies, and one that  *
 *  simply passes the input to the stringify macro.                           */
#define TMPL_STRINGIFY_VARIABLE(x) #x
#define TMPL_TO_STRING(x) TMPL_STRINGIFY_VARIABLE(x)

#endif
/*  End of include guard.                                                     */
