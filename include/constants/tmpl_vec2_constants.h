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
 *                            tmpl_vec2_constants                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides commonly used vectors in the plane.                          *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 10, 2025                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VEC2_CONSTANTS_H
#define TMPL_VEC2_CONSTANTS_H

/*  Typedef's for 2D vectors at various precisions provided here.             */
#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_vec2_float.h>
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Unit vector in the positive x direction, x_hat = (1, 0).                  */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_X_Hat;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_X_Hat;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_X_Hat;

/*  Unit vector in the positive y direction, y_hat = (0, 1).                  */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_Y_Hat;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_Y_Hat;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Y_Hat;

/*  Unit vector in the positive y direction, North = (0, 1).                  */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_North;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_North;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_North;

/*  Unit vector in the negative y direction, South = (0, -1).                 */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_South;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_South;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_South;

/*  Unit vector in the positive x direction, East = (1, 0).                   */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_East;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_East;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_East;

/*  Unit vector in the negative x direction, West = (-1, 0).                  */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_West;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_West;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_West;

/*  Unit vector along the y = x direction, Northeast = (1, 1) / sqrt(2).      */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_Northeast;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_Northeast;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Northeast;

/*  Unit vector along the y = -x direction, Northwest = (-1, 1) / sqrt(2).    */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_Northwest;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_Northwest;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Northwest;

/*  Unit vector along the y = x direction, Southwest = (-1, -1) / sqrt(2).    */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_Southwest;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_Southwest;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Southwest;

/*  Unit vector along the y = -x direction, Southeast = (1, -1) / sqrt(2).    */
extern const tmpl_TwoVectorDouble tmpl_2DDouble_Southeast;
extern const tmpl_TwoVectorFloat tmpl_2DFloat_Southeast;
extern const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Southeast;

#endif
