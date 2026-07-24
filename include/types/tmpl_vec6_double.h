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
 *                              tmpl_vec6_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the definition of a 6D vector at double precision.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 24, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC6_DOUBLE_H
#define TMPL_TYPES_VEC6_DOUBLE_H

/*  6D Vectors with double-precision components.                              */
typedef union tmpl_SixVectorDouble_Type {
    double dat[6];
} tmpl_SixVectorDouble;

#endif
/*  End of include guard.                                                     */
