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
 *                             tmpl_mat3x3_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides the definition of a 3x3 matrix at single precision.          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 6, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_TYPES_MAT3X3_FLOAT_H
#define TMPL_TYPES_MAT3X3_FLOAT_H

/*  Single precision 3x3 matrix for linear transformations in R^3.            */
typedef struct tmpl_ThreeByThreeMatrixFloat_Type {
    float dat[3][3];
} tmpl_ThreeByThreeMatrixFloat;

#endif
/*  End of include guard.                                                     */
