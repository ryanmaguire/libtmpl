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
 *                             tmpl_cubic_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for cubic polynomials, a + bx + cx^2 + dx^3.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 13, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_CUBIC_DOUBLE_H
#define TMPL_TYPES_CUBIC_DOUBLE_H

/*  Double precision cubic polynomial with real coefficients.                 */
typedef struct tmpl_CubicDouble_Type {
    double dat[4];
} tmpl_CubicDouble;

/*  Helper macros for accessing the data.                                     */
#define TMPL_CUBIC_DOUBLE_CONSTANT_TERM(cubic) ((cubic).dat[0])
#define TMPL_CUBIC_DOUBLE_LINEAR_TERM(cubic) ((cubic).dat[1])
#define TMPL_CUBIC_DOUBLE_QUADRATIC_TERM(cubic) ((cubic).dat[2])
#define TMPL_CUBIC_DOUBLE_CUBIC_TERM(cubic) ((cubic).dat[3])

/*  Helper macros for accessing the data when the input is a pointer.         */
#define TMPL_CUBIC_DOUBLE_PTR_CONSTANT_TERM(cubic) ((cubic)->dat[0])
#define TMPL_CUBIC_DOUBLE_PTR_LINEAR_TERM(cubic) ((cubic)->dat[1])
#define TMPL_CUBIC_DOUBLE_PTR_QUADRATIC_TERM(cubic) ((cubic)->dat[2])
#define TMPL_CUBIC_DOUBLE_PTR_CUBIC_TERM(cubic) ((cubic)->dat[3])

#endif
/*  End of include guard.                                                     */
