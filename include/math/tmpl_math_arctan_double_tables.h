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
#ifndef TMPL_MATH_ARCTAN_DOUBLE_TABLES_H
#define TMPL_MATH_ARCTAN_DOUBLE_TABLES_H

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const double tmpl_atan_double_v[8] = {
    0.05,
    0.18,
    0.35,
    0.72,
    1.35,
    2.5,
    4.0,
    8.0
};

static const double tmpl_atan_double_atan_of_v[8] = {
    0.0499583957219427614100063,
    0.178092938231197549667920,
    0.336674819386727181396699,
    0.624023052976756847589791,
    0.933247528656203869893663,
    1.19028994968253173292773,
    1.32581766366803246505924,
    1.44644133224813518419997
};

#endif
/*  End of include guard.                                                     */
