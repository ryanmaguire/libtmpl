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

/*  TMPL_USE_MATH_ALGORITHMS macro found here.                                */
#include <libtmpl/include/tmpl_config.h>

/*  These tables are only needed if libtmpl math algorithms are used.         */
#if TMPL_USE_MATH_ALGORITHMS == 1

/*  Declarations given here.                                                  */
#include <libtmpl/include/tmpl_math.h>

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */

const double tmpl_atan_double_v[8] = {
    0.05, 0.18, 0.35, 0.72, 1.35, 2.5, 4.0, 8.0
};

const double tmpl_atan_double_atan_of_v[8] = {
    4.99583957219427614100063E-02,
    1.78092938231197549667920E-01,
    3.36674819386727181396699E-01,
    6.24023052976756847589791E-01,
    9.33247528656203869893663E-01,
    1.19028994968253173292773E+00,
    1.32581766366803246505924E+00,
    1.44644133224813518419997E+00
};

#endif
/*  End of #if TMPL_USE_MATH_ALGORITHMS == 1.                                 */
