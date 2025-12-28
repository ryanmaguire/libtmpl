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
 *                        tmpl_window_function_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a typedef for double precision tapering functions.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 28, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_WINDOW_FUNCTION_DOUBLE_H
#define TMPL_TYPES_WINDOW_FUNCTION_DOUBLE_H

/*  Window functions take in two arguments, the x value and the window width. *
 *  The output is the value of the window. This provide a typedef for this.   */
typedef double (*tmpl_WindowFunctionDouble)(double, double);

#endif
/*  End of include guard.                                                     */
