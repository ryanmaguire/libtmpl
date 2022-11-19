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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_MATH_ARCTAN_FLOAT_TABLES_H
#define TMPL_MATH_ARCTAN_FLOAT_TABLES_H

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const float tmpl_atan_float_v[8] = {
    0.05F,
    0.18F,
    0.35F,
    0.72F,
    1.35F,
    2.5F,
    4.0F,
    8.0F
};

static const float tmpl_atan_float_atan_of_v[8] = {
    0.0499583957219427614100063F,
    0.178092938231197549667920F,
    0.336674819386727181396699F,
    0.624023052976756847589791F,
    0.933247528656203869893663F,
    1.19028994968253173292773F,
    1.32581766366803246505924F,
    1.44644133224813518419997F
};

#endif
/*  End of include guard.                                                     */
