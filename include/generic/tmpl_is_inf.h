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
 *                                tmpl_is_inf                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides an isinf helper macro using the _Generic keyword.            *
 *  Notes:                                                                    *
 *      1.) Using this file requires a C11-compatible or C++ compiler.        *
 *          Because of this, tmpl_is_inf.h is not directly included in tmpl.h *
 *          in order to preserve portability. To use this header you must     *
 *          explicitly include it via                                         *
 *          #include <libtmpl/include/generic/tmpl_is_inf.h>. That is,        *
 *          #include <libtmpl/include/tmpl.h> will skip this header file.     *
 *                                                                            *
 *      2.) If using libtmpl with a C++ compiler, this file uses function     *
 *          overloading instead of the _Generic keyword since _Generic is a   *
 *          C11 feature and not required by C++ compilers.                    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans (True and False).                  *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with support for infinity.                            *
 *  3.) tmpl_cast.h:                                                          *
 *          Header with the TMPL_CAST macro for C vs. C++ compatibility.      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_GENERIC_IS_INF_H
#define TMPL_GENERIC_IS_INF_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  libtmpl's implementation of isinf given here.                             */
#include <libtmpl/include/tmpl_math.h>

/*  C++ does not have the _Generic keyword, which is a C11 feature. C++       *
 *  does have function overloading, which achieves the same goal.             */
#ifdef __cplusplus

/*  C++ function overloading for checking if a floating-point number is inf.  */
static inline tmpl_Bool TMPL_IS_INF(const float x)
{
    return tmpl_Float_Is_Inf(x);
}

static inline tmpl_Bool TMPL_IS_INF(const double x)
{
    return tmpl_Double_Is_Inf(x);
}

static inline tmpl_Bool TMPL_IS_INF(const long double x)
{
    return tmpl_LDouble_Is_Inf(x);
}

template <typename T>
static inline tmpl_Bool TMPL_IS_INF(const T x)
{
    (void)x;
    return tmpl_False;
}

/*  C11 introduced the _Generic keyword instead of function overloading.      */
#else

/*  TMPL_CAST provided here.                                                  */
#include <libtmpl/include/compat/tmpl_cast.h>

/*  C11 generic macro for checking if a floating-point number is infinite.    */
#define TMPL_IS_INF(x) _Generic((x),                                           \
    long double: tmpl_LDouble_Is_Inf(TMPL_CAST(x, long double)),               \
    double:      tmpl_Double_Is_Inf(TMPL_CAST(x, double)),                     \
    float:       tmpl_Float_Is_Inf(TMPL_CAST(x, float)),                       \
    default:     tmpl_False                                                    \
)

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
