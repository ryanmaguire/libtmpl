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
 *                             tmpl_affine_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a struct for Affine transformations, f(x) = Ax + B.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 29, 2026                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_AFFINE_DOUBLE_H
#define TMPL_TYPES_AFFINE_DOUBLE_H

/*  Double precision affine transformation of the real line.                  */
typedef struct tmpl_AffineDouble_Type {
    double dat[2];
} tmpl_AffineDouble;

/*  Helper macros for accessing the data.                                     */
#define TMPL_AFFINE_DOUBLE_SLOPE(transform) ((transform).dat[0])
#define TMPL_AFFINE_DOUBLE_INTERCEPT(transform) ((transform).dat[1])

/*  Helper macros for accessing the data when the input is a pointer.         */
#define TMPL_AFFINE_DOUBLE_PTR_SLOPE(transform) ((transform)->dat[0])
#define TMPL_AFFINE_DOUBLE_PTR_INTERCEPT(transform) ((transform)->dat[1])

#endif
/*  End of include guard.                                                     */
