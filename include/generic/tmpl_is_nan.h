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
 *                                tmpl_is_nan                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides helper isnan macro using the _Generic keyword.               *
 *  Notes:                                                                    *
 *      Using this header file requires a C11 compatible compiler. Because of *
 *      this, tmpl_is_nan.h is not directly included in tmpl.h, in order to   *
 *      preserve portability. To use this header you must explicitly include  *
 *      it via #include <libtmpl/include/generic/tmpl_is_nan.h>. That is,     *
 *      #include <libtmpl/include/tmpl.h> will skip this header file.         *
 *                                                                            *
 *      If using libtmpl with a C++ compiler, this file uses function         *
 *      overloading instead of the _Generic keyword since _Generic is a C11   *
 *      extension, and not required by C++ compilers.                         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file providing Booleans (True and False).                  *
 *  2.) tmpl_nan_double.h:                                                    *
 *          Header file providing double precision isnan.                     *
 *  3.) tmpl_nan_float.h:                                                     *
 *          Header file providing single precision isnan.                     *
 *  4.) tmpl_nan_ldouble.h:                                                   *
 *          Header file providing long double precision isnan.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 22, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_IS_NAN_H
#define TMPL_IS_NAN_H

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  libtmpl's implementation of isinf given here.                             */
#include <libtmpl/include/nan/tmpl_nan_double.h>
#include <libtmpl/include/nan/tmpl_nan_float.h>
#include <libtmpl/include/nan/tmpl_nan_ldouble.h>

/*  C++ does not have the _Generic keyword, which is a C11 extension. C++     *
 *  does have function overloading, which achieves the same goal.             */
#ifdef __cplusplus

/*  C++ function overloading for checking if a floating point number is NaN.  */
static inline tmpl_Bool TMPL_IS_NAN(const float x)
{
    return tmpl_Float_Is_NaN(x);
}

static inline tmpl_Bool TMPL_IS_NAN(const double x)
{
    return tmpl_Double_Is_NaN(x);
}

static inline tmpl_Bool TMPL_IS_NAN(const long double x)
{
    return tmpl_LDouble_Is_NaN(x);
}

static inline tmpl_Bool TMPL_IS_NAN(const signed long long int x)
{
    (void)x;
    return tmpl_False;
}

static inline tmpl_Bool TMPL_IS_NAN(const unsigned long long int x)
{
    (void)x;
    return tmpl_False;
}

/*  C11 introduced the _Generic keyword instead of function overloading.      */
#else

/*  C11 generic macro for checking if a floating point number is NaN.         */
#define TMPL_IS_NAN(x) _Generic((x),                                           \
    long double: tmpl_LDouble_Is_NaN((x)),                                     \
    double:      tmpl_Double_Is_NaN((x)),                                      \
    float:       tmpl_Float_Is_NaN((x)),                                       \
    default:     tmpl_False                                                    \
)

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
