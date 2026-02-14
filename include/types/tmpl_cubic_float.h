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
 *                              tmpl_cubic_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for cubic polynomials, a + bx + cx^2 + dx^3.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 14, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_CUBIC_FLOAT_H
#define TMPL_TYPES_CUBIC_FLOAT_H

/*  Single precision cubic polynomial with real coefficients.                 */
typedef struct tmpl_CubicFloat_Type {
    float dat[4];
} tmpl_CubicFloat;

/*  Helper macros for accessing the data.                                     */
#define TMPL_CUBIC_FLOAT_CONSTANT_TERM(cubic) ((cubic).dat[0])
#define TMPL_CUBIC_FLOAT_LINEAR_TERM(cubic) ((cubic).dat[1])
#define TMPL_CUBIC_FLOAT_QUADRATIC_TERM(cubic) ((cubic).dat[2])
#define TMPL_CUBIC_FLOAT_CUBIC_TERM(cubic) ((cubic).dat[3])

/*  Helper macros for accessing the data when the input is a pointer.         */
#define TMPL_CUBIC_FLOAT_PTR_CONSTANT_TERM(cubic) ((cubic)->dat[0])
#define TMPL_CUBIC_FLOAT_PTR_LINEAR_TERM(cubic) ((cubic)->dat[1])
#define TMPL_CUBIC_FLOAT_PTR_QUADRATIC_TERM(cubic) ((cubic)->dat[2])
#define TMPL_CUBIC_FLOAT_PTR_CUBIC_TERM(cubic) ((cubic)->dat[3])

/*  Evaluates a cubic polynomial using Horner's method.                       */
#define TMPL_CUBIC_FLOAT_EVAL(p, x) \
    ((p).dat[0] + (x)*((p).dat[1] + (x)*((p).dat[2] + (x)*(p).dat[3])))

#define TMPL_CUBIC_FLOAT_PTR_EVAL(p, x) \
    ((p)->dat[0] + (x)*((p)->dat[1] + (x)*((p)->dat[2] + (x)*(p)->dat[3])))

/*  Evaluates the derivative using Horner's method.                           */
#define TMPL_CUBIC_FLOAT_DERIV_EVAL(p, x) \
    ((p).dat[1] + (x) * ((2.0 * (p).dat[2]) + (x) * (3.0 * (p).dat[3])))

#define TMPL_CUBIC_FLOAT_PTR_DERIV_EVAL(p, x) \
    ((p)->dat[1] + (x) * ((2.0 * (p)->dat[2]) + (x) * (3.0 * (p)->dat[3])))

#endif
/*  End of include guard.                                                     */
