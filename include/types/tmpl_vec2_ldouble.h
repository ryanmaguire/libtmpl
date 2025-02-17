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
 *                             tmpl_vec2_ldouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the definition of a 2D vector at long double precision.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 6, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_VEC2_LDOUBLE_H
#define TMPL_TYPES_VEC2_LDOUBLE_H

/*  2D Vectors with long double precision components.                         */
typedef struct tmpl_TwoVectorLongDouble_Def {
    long double dat[2];
} tmpl_TwoVectorLongDouble;

#endif
/*  End of include guard.                                                     */
