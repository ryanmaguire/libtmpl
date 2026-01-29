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
 *                                  tmpl_eps                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides machine epsilon helper macro using the _Generic keyword.     *
 *  Notes:                                                                    *
 *      Using this header file requires a C11 compatible compiler. Because of *
 *      this, tmpl_eps.h is not directly included in tmpl.h, in order to      *
 *      preserve portability. To use this header you must explicitly include  *
 *      it via #include <libtmpl/include/generic/tmpl_eps.h>. That is,        *
 *      #include <libtmpl/include/tmpl.h> will skip this header file.         *
 *                                                                            *
 *      If using libtmpl with a C++ compiler, this file uses function         *
 *      overloading instead of the _Generic keyword since _Generic is a C11   *
 *      extension, and not required by C++ compilers.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_float.h:                                                         *
 *          Header file providing the limits of various floating point types. *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_EPS_H
#define TMPL_EPS_H

/*  Machine precision macros found here.                                      */
#include <libtmpl/include/tmpl_float.h>

/*  C++ does not have the _Generic keyword, which is a C11 extension. C++     *
 *  does have function overloading, which achieves the same goal.             */
#ifdef __cplusplus

/*  C++ function overloading for getting machine epsilon for a given type.    */
static inline float TMPL_EPS(float x)
{
    return TMPL_FLT_EPS;
}

static inline double TMPL_EPS(double x)
{
    return TMPL_DBL_EPS;
}

static inline long double TMPL_EPS(long double x)
{
    return TMPL_LDBL_EPS;
}

/*  C11 introduced the _Generic keyword instead of function overloading.      */
#else

/*  C11 generic macro for getting machine epsilon for a given data type.      */
#define TMPL_EPS(x) _Generic((x),                                              \
    long double: TMPL_LDBL_EPS,                                                \
    default:     TMPL_DBL_EPS,                                                 \
    float:       TMPL_FLT_EPS                                                  \
)

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
