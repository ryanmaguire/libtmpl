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
 *                                tmpl_variadic                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides helper macros using C99 variadic syntax.                     *
 *  Notes:                                                                    *
 *      Using this header file requires a C99 compatible compiler. Because of *
 *      this, tmpl_variadic.h is not directly included in tmpl.h, in order to *
 *      preserve portability. To use this header you must explicitly include  *
 *      it via #include <libtmpl/include/tmpl_variadic.h>. That is,           *
 *      #include <libtmpl/include/tmpl.h> will skip this header file.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_float.h:                                                         *
 *          Header file providing the limits of various floating point types. *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with support for NaN and infinity.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 17, 2024                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VARIADIC_H
#define TMPL_VARIADIC_H

/*  TMPL_ARRAY_SIZE found here.                                               */
#include <libtmpl/include/tmpl_helper.h>

/*  TMPL_CAST provided here (C/C++ compatibility with casting data types).    */
#include <libtmpl/include/tmpl_compat_cast.h>

/*  TMPL_MALLOC / TMPL_FREE given here (provide C vs.C++ compatibility).      */
#include <libtmpl/include/tmpl_compat_stdlib.h>

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_MALLOC_VARS_HELPER                                               *
 *  Purpose:                                                                  *
 *      Allocates memory for several pointers, each of the same size and type.*
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The type of the data (double, float, int, char, etc.).            *
 *      length:                                                               *
 *          The number of elements for each pointer.                          *
 *      ptr1, ptr2, ...:                                                      *
 *          Pointers to the pointers that will be allocated memory.           *
 *  Example:                                                                  *
 *      size_t len = 10;                                                      *
 *      double *x, *y, *z;                                                    *
 *      TMPL_MALLOC_VARS_HELPER(double, len, &x, &y, &z);                     *
 ******************************************************************************/
#define TMPL_MALLOC_VARS_HELPER(type, length, ...)                             \
do {                                                                           \
    type **my_tmp_ptr_arr[] = {__VA_ARGS__};                                   \
    const size_t my_tmp_ptr_arr_len = TMPL_ARRAY_SIZE(my_tmp_ptr_arr);         \
    size_t my_tmp_iter;                                                        \
    const size_t my_tmp_length = TMPL_CAST(length, size_t);                    \
    for (my_tmp_iter = 0; my_tmp_iter < my_tmp_ptr_arr_len; ++my_tmp_iter)     \
    {                                                                          \
        *my_tmp_ptr_arr[my_tmp_iter] = NULL;                                   \
    }                                                                          \
    if (my_tmp_length == 0)                                                    \
    {                                                                          \
        break;                                                                 \
    }                                                                          \
    for (my_tmp_iter = 0; my_tmp_iter < my_tmp_ptr_arr_len; ++my_tmp_iter)     \
    {                                                                          \
        *my_tmp_ptr_arr[my_tmp_iter] = TMPL_MALLOC(type, my_tmp_length);       \
        if (!*my_tmp_ptr_arr[my_tmp_iter])                                     \
        {                                                                      \
            break;                                                             \
        }                                                                      \
    }                                                                          \
} while (0)

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_NULL_CHECKER                                                     *
 *  Purpose:                                                                  *
 *      Checks several points and make sure none are NULL.                    *
 *  Arguments:                                                                *
 *      success:                                                              *
 *          An integer. This macro sets it to zero if a pointer is NULL.      *
 *      type:                                                                 *
 *          The type of the data (double, float, int, char, etc.).            *
 *      ptr1, ptr2, ...:                                                      *
 *          Pointers to the pointers that will be checked.                    *
 *  Example:                                                                  *
 *      size_t len = 10;                                                      *
 *      double *x, *y, *z;                                                    *
 *      int success;                                                          *
 *                                                                            *
 *      TMPL_MALLOC_VARS_HELPER(double, len, &x, &y, &z);                     *
 *      TMPL_NULL_CHECKER(success, double, &x, &y, &z);                       *
 *                                                                            *
 *      if (!success)                                                         *
 *          return -1;                                                        *
 ******************************************************************************/
#define TMPL_NULL_CHECKER(success, type, ...)                                  \
do {                                                                           \
    int my_tmp_should_free = 0;                                                \
    type **my_tmp_ptr_arr[] = {__VA_ARGS__};                                   \
    const size_t my_tmp_ptr_arr_len = TMPL_ARRAY_SIZE(my_tmp_ptr_arr);         \
    size_t my_tmp_iter;                                                        \
    success = 1;                                                               \
    for (my_tmp_iter = 0; my_tmp_iter < my_tmp_ptr_arr_len; ++my_tmp_iter)     \
    {                                                                          \
        if (*my_tmp_ptr_arr[my_tmp_iter] == NULL)                              \
        {                                                                      \
            my_tmp_should_free = 1;                                            \
            success = 0;                                                       \
            break;                                                             \
        }                                                                      \
    }                                                                          \
    if (my_tmp_should_free)                                                    \
    {                                                                          \
        for (my_tmp_iter = 0; my_tmp_iter < my_tmp_ptr_arr_len; ++my_tmp_iter) \
        {                                                                      \
            TMPL_FREE(*my_tmp_ptr_arr[my_tmp_iter]);                           \
        }                                                                      \
    }                                                                          \
} while (0)

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_MALLOC_VARS                                                      *
 *  Purpose:                                                                  *
 *      Allocates memory for several pointers, each of the same size and type.*
 *  Arguments:                                                                *
 *      success:                                                              *
 *          An integer. This macro sets it to zero if a pointer becomes NULL. *
 *      type:                                                                 *
 *          The type of the data (double, float, int, char, etc.).            *
 *      length:                                                               *
 *          The number of elements for each pointer.                          *
 *      ptr1, ptr2, ...:                                                      *
 *          Pointers to the pointers that will be allocated memory.           *
 *  Example:                                                                  *
 *      size_t len = 10;                                                      *
 *      double *x, *y, *z;                                                    *
 *      int success;                                                          *
 *      TMPL_MALLOC_VARS(double, len, &x, &y, &z);                            *
 *                                                                            *
 *      if (!success)                                                         *
 *          return -1;                                                        *
 ******************************************************************************/
#define TMPL_MALLOC_VARS(success, type, length, ...)                           \
do {                                                                           \
    TMPL_MALLOC_VARS_HELPER(type, length, __VA_ARGS__);                        \
    TMPL_NULL_CHECKER(success, type, __VA_ARGS__);                             \
} while (0)

/******************************************************************************
 *  Macro:                                                                    *
 *      TMPL_FREE_VARS                                                        *
 *  Purpose:                                                                  *
 *      Free memory allocated to several pointers.                            *
 *  Arguments:                                                                *
 *      type:                                                                 *
 *          The type of the data (double, float, int, char, etc.).            *
 *      ptr1, ptr2, ...:                                                      *
 *          Pointers to the pointers that will be allocated memory.           *
 *  Example:                                                                  *
 *      size_t len = 10;                                                      *
 *      double *x, *y, *z;                                                    *
 *      int success;                                                          *
 *      TMPL_MALLOC_VARS(double, len, &x, &y, &z);                            *
 *                                                                            *
 *      if (!success)                                                         *
 *          return -1;                                                        *
 *                                                                            *
 *      ...                                                                   *
 *                                                                            *
 *      TMPL_FREE_VARS(double, &x, &y, &z);                                   *
 ******************************************************************************/
#define TMPL_FREE_VARS(type, ...)                                              \
do {                                                                           \
    type **my_tmp_ptr_arr[] = {__VA_ARGS__};                                   \
    const size_t my_tmp_ptr_arr_len = TMPL_ARRAY_SIZE(my_tmp_ptr_arr);         \
    size_t my_tmp_iter;                                                        \
    for (my_tmp_iter = 0; my_tmp_iter < my_tmp_ptr_arr_len; ++my_tmp_iter)     \
    {                                                                          \
        TMPL_FREE(*my_tmp_ptr_arr[my_tmp_iter]);                               \
    }                                                                          \
} while (0)

#endif
/*  End of include guard.                                                     */
