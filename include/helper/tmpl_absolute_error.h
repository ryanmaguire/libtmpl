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
 *                             tmpl_absolute_error                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a helper macro for computing absolute error.                 *
 *  Notes:                                                                    *
 *      1.) The arguments for this macro are expanded three times. Use this   *
 *          with variable-like expressions and not function calls.            *
 *                                                                            *
 *      2.) To avoid unexpected results, do not combine this macro with the   *
 *          ++ or -- operators.                                               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_ABSOLUTE_ERROR_H
#define TMPL_HELPER_ABSOLUTE_ERROR_H

/*  Computes the absolute error between two values (integer / floating point).*/
#define TMPL_ABSOLUTE_ERROR(x, y) ((x) < (y) ? ((y) - (x)) : ((x) - (y)))

#endif
/*  End of include guard.                                                     */
