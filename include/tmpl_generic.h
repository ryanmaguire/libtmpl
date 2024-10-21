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
 *                                tmpl_generic                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides helper macros using the _Generic keyword.                    *
 *  Notes:                                                                    *
 *      Using this header file requires a C11 compatible compiler. Because of *
 *      this, tmpl_generic.h is not directly included in tmpl.h, in order to  *
 *      preserve portability. To use this header you must explicitly include  *
 *      it via #include <libtmpl/include/tmpl_generic.h>. That is,            *
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
 *  2.) tmpl_math.h:                                                          *
 *          Header file with support for NaN and infinity.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_GENERIC_H
#define TMPL_GENERIC_H

/*  Machine precision macros found here.                                      */
#include <libtmpl/include/tmpl_float.h>

/*  libtmpl's implementations of isnan and isinf given here.                  */
#include <libtmpl/include/tmpl_math.h>

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

/*  C++ function overloading for checking if a floating point number is inf.  */
static inline tmpl_Bool TMPL_IS_INF(float x)
{
    return tmpl_Float_Is_Inf(x);
}

static inline tmpl_Bool TMPL_IS_INF(double x)
{
    return tmpl_Double_Is_Inf(x);
}

static inline tmpl_Bool TMPL_IS_INF(long double x)
{
    return tmpl_LDouble_Is_Inf(x);
}

/*  C++ function overloading for checking if a floating point number is NaN.  */
static inline tmpl_Bool TMPL_IS_NAN(float x)
{
    return tmpl_Float_Is_NaN(x);
}

static inline tmpl_Bool TMPL_IS_NAN(double x)
{
    return tmpl_Double_Is_NaN(x);
}

static inline tmpl_Bool TMPL_IS_NAN(long double x)
{
    return tmpl_LDouble_Is_NaN(x);
}

/*  C11 introduced the _Generic keyword instead of function overloading.      */
#else

/*  C11 generic macro for getting machine epsilon for a given data type.      */
#define TMPL_EPS(x) _Generic((x),                                              \
    long double: TMPL_LDBL_EPS,                                                \
    default:     TMPL_DBL_EPS,                                                 \
    float:       TMPL_FLT_EPS                                                  \
)

/*  C11 generic macro for checking if a floating point number is infinite.    */
#define TMPL_IS_INF(x) _Generic((x),                                           \
    long double: tmpl_LDouble_Is_Inf,                                          \
    default:     tmpl_Double_Is_Inf,                                           \
    float:       tmpl_Float_Is_Inf                                             \
)(x)

/*  C11 generic macro for checking if a floating point is Not-a-Number.       */
#define TMPL_IS_NAN(x) _Generic((x),                                           \
    long double: tmpl_LDouble_Is_NaN,                                          \
    default:     tmpl_Double_Is_NaN,                                           \
    float:       tmpl_Float_Is_NaN                                             \
)(x)

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
