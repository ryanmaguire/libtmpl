/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                            tmpl_vec3_constants                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide commonly used constant vectors in R^3.                        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_vec3.h:                                                          *
 *          Header containing ThreeVector typedef.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 17, 2022                                                *
 ******************************************************************************/

/*  ThreeVector typedef's found here.                                         */
#include <libtmpl/include/tmpl_vec3.h>

/*  The zero vector.                                                          */
const tmpl_ThreeVectorFloat tmpl_3DFloat_Zero = {{0.0F, 0.0F, 0.0F}};
const tmpl_ThreeVectorDouble tmpl_3DDouble_Zero = {{0.0, 0.0, 0.0}};
const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Zero = {{0.0L, 0.0L, 0.0L}};

/*  Unit vector in the positive x direction. Also called "i" or "i hat".      */
const tmpl_ThreeVectorFloat tmpl_3DFloat_X_Hat = {{1.0F, 0.0F, 0.0F}};
const tmpl_ThreeVectorDouble tmpl_3DDouble_X_Hat = {{1.0, 0.0, 0.0}};
const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_X_Hat = {{1.0L, 0.0L, 0.0L}};

/*  Unit vector in the positive y direction. Also called "j" or "j hat".      */
const tmpl_ThreeVectorFloat tmpl_3DFloat_Y_Hat = {{0.0F, 1.0F, 0.0F}};
const tmpl_ThreeVectorDouble tmpl_3DDouble_Y_Hat = {{0.0, 1.0, 0.0}};
const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Y_Hat = {{0.0L, 1.0L, 0.0L}};

/*  Unit vector in the positive z direction. Also called "k" or "k hat".      */
const tmpl_ThreeVectorFloat tmpl_3DFloat_Z_Hat = {{0.0F, 0.0F, 1.0F}};
const tmpl_ThreeVectorDouble tmpl_3DDouble_Z_Hat = {{0.0, 0.0, 1.0}};
const tmpl_ThreeVectorLongDouble tmpl_3DLDouble_Z_Hat = {{0.0L, 0.0L, 1.0L}};
