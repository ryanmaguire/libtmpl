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

/*  Typedef's for 2D vectors at various precisions provided here.             */
#include <libtmpl/include/types/tmpl_vec2_double.h>
#include <libtmpl/include/types/tmpl_vec2_float.h>
#include <libtmpl/include/types/tmpl_vec2_ldouble.h>

/*  Forward declarations provided here.                                       */
#include <libtmpl/include/constants/tmpl_vec2_constants.h>

/*  1 / sqrt(2), used for northeast, northwest, southeast, southwest.         */
#define VAL  7.071067811865475244008443621048490392848359376884740365883398E-01
#define VALF 7.071067811865475244008443621048490392848359376884740365883398E-01F
#define VALL 7.071067811865475244008443621048490392848359376884740365883398E-01L

/*  Unit vector in the positive x direction, x_hat = (1, 0).                  */
const tmpl_TwoVectorDouble tmpl_2DDouble_X_Hat = {{1.0, 0.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_X_Hat = {{1.0F, 0.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_X_Hat = {{1.0L, 0.0L}};

/*  Unit vector in the positive y direction, y_hat = (0, 1).                  */
const tmpl_TwoVectorDouble tmpl_2DDouble_Y_Hat = {{0.0, 1.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_Y_Hat = {{0.0F, 1.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Y_Hat = {{0.0L, 1.0L}};

/*  Unit vector in the positive y direction, North = (0, 1).                  */
const tmpl_TwoVectorDouble tmpl_2DDouble_North = {{0.0, 1.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_North = {{0.0F, 1.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_North = {{0.0L, 1.0L}};

/*  Unit vector in the negative y direction, South = (0, -1).                 */
const tmpl_TwoVectorDouble tmpl_2DDouble_South = {{0.0, -1.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_South = {{0.0F, -1.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_South = {{0.0L, -1.0L}};

/*  Unit vector in the positive x direction, East = (1, 0).                  */
const tmpl_TwoVectorDouble tmpl_2DDouble_East = {{1.0, 0.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_East = {{1.0F, 0.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_East = {{1.0L, 0.0L}};

/*  Unit vector in the negative x direction, West = (-1, 0).                  */
const tmpl_TwoVectorDouble tmpl_2DDouble_West = {{-1.0, 0.0}};
const tmpl_TwoVectorFloat tmpl_2DFloat_West = {{-1.0F, 0.0F}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_West = {{-1.0L, 0.0L}};

/*  Unit vector along the y = x direction, Northeast = (1, 1) / sqrt(2).      */
const tmpl_TwoVectorDouble tmpl_2DDouble_Northeast = {{VAL, VAL}};
const tmpl_TwoVectorFloat tmpl_2DFloat_Northeast = {{VALF, VALF}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Northeast = {{VALL, VALL}};

/*  Unit vector along the y = -x direction, Northwest = (-1, 1) / sqrt(2).    */
const tmpl_TwoVectorDouble tmpl_2DDouble_Northwest = {{-VAL, VAL}};
const tmpl_TwoVectorFloat tmpl_2DFloat_Northwest = {{-VALF, VALF}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Northwest = {{-VALL, VALL}};

/*  Unit vector along the y = x direction, Southwest = (-1, -1) / sqrt(2).    */
const tmpl_TwoVectorDouble tmpl_2DDouble_Southwest = {{-VAL, -VAL}};
const tmpl_TwoVectorFloat tmpl_2DFloat_Southwest = {{-VALF, -VALF}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Southwest = {{-VALL, -VALL}};

/*  Unit vector along the y = -x direction, Southeast = (1, -1) / sqrt(2).    */
const tmpl_TwoVectorDouble tmpl_2DDouble_Southeast = {{VAL, -VAL}};
const tmpl_TwoVectorFloat tmpl_2DFloat_Southeast = {{VALF, -VALF}};
const tmpl_TwoVectorLongDouble tmpl_2DLDouble_Southeast = {{VALL, -VALL}};

/*  Undefine everything in case someone wants to #include this file.          */
#undef VAL
#undef VALF
#undef VALL
