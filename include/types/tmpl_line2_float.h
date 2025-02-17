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
 *                              tmpl_line2_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a single precision two dimensional line struct.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 16, 2025                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_LINE2_FLOAT_H
#define TMPL_TYPES_LINE2_FLOAT_H

/*  Two dimensional vector struct defined here.                               */
#include <libtmpl/include/types/tmpl_vec2_float.h>

/*  Single precision 2D line. A line is a point and a velocity.               */
typedef struct tmpl_TwoLineFloat_Def {
    tmpl_TwoVectorFloat dat[2];
} tmpl_TwoLineFloat;

#endif
/*  End of include guard.                                                     */
