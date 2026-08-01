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
 *                    tmpl_time_dependent_function_ldouble                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a long double-precision function type (x, t) -> R.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 31, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_TIME_DEPENDENT_FUNCTION_LDOUBLE_H
#define TMPL_TYPES_TIME_DEPENDENT_FUNCTION_LDOUBLE_H

/*  Typedef for long double-precision time-dependent real-valued functions.   */
typedef long double
(*tmpl_TimeDependentFunctionLongDouble)(long double, long double);

#endif
/*  End of include guard.                                                     */
