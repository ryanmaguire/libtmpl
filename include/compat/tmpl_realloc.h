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
 *                                tmpl_realloc                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a macro for realloc with C vs. C++ compatibility.            *
 *  Notes:                                                                    *
 *      1.) This macro does not provide a cast; the output is a void pointer. *
 *          The user is required to examine the output and check for NULL.    *
 *          Intended usage:                                                   *
 *                                                                            *
 *              void * const tmp = TMPL_REALLOC(ptr, n);                      *
 *                                                                            *
 *              if (!tmp)                                                     *
 *                  handle_error();                                           *
 *              else                                                          *
 *                  ptr = TMPL_CAST(tmp, ptr_type);                           *
 *                                                                            *
 *          where "ptr_type" is the type of ptr. Writing                      *
 *                                                                            *
 *              ptr = TMPL_REALLOC(ptr, n);                                   *
 *                                                                            *
 *          risks introducing memory leaks in C, and will not compile in C++  *
 *          since void pointers are not implicitly converted to typed         *
 *          pointers.                                                         *
 *                                                                            *
 *      2.) The input must not be a void pointer. That is, sizeof(*ptr) must  *
 *          be a valid expression.                                            *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header file providing realloc.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 14, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPAT_REALLOC_H
#define TMPL_COMPAT_REALLOC_H

/*  Standard macro for C++ usage. Check for this.                             */
#ifdef __cplusplus

/*  realloc provided here in the std namespace.                               */
#include <cstdlib>

/*  Macro for reallocating memory. The output is a void pointer.              */
#define TMPL_REALLOC(ptr, n) std::realloc((ptr), sizeof(*(ptr)) * (n))

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  Standard library header file providing the realloc function.              */
#include <stdlib.h>

/*  Macro for reallocating memory. The output is a void pointer.              */
#define TMPL_REALLOC(ptr, n) realloc((ptr), sizeof(*(ptr)) * (n))

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
