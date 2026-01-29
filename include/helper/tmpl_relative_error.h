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
 *                             tmpl_relative_error                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a macro for computing the relative error between two values. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_abs.h:                                                           *
 *          Provides the TMPL_ABS macro for computing absolute values.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_HELPER_RELATIVE_ERROR_H
#define TMPL_HELPER_RELATIVE_ERROR_H

/*  Absolute value helper macro found here.                                   */
#include <libtmpl/include/helper/tmpl_abs.h>

/*  Computes the relative error of x with respect to y (integer or float).    */
#define TMPL_RELATIVE_ERROR(x, y) TMPL_ABS(((x) - (y)) / (y))

#endif
/*  End of include guard.                                                     */
