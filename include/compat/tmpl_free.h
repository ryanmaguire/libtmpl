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
 *                                  tmpl_free                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a macro for free with C vs. C++ compatibility.               *
 *  Notes:                                                                    *
 *      The TMPL_FREE macro expands the input twice: once to free the data,   *
 *      and once to set the input to NULL. Do not use this macro with the     *
 *      ++ or -- operators:                                                   *
 *                                                                            *
 *          TMPL_FREE(ptr);         good                                      *
 *          TMPL_FREE(++ptr);       bad                                       *
 *          TMPL_FREE(ptr[n++]);    bad                                       *
 *                                                                            *
 *      Improper use may lead to unintended results or crashes.               *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header file providing free.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 21, 2024                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2025/04/10: Ryan Maguire                                                  *
 *      Moved macro to its own file.                                          *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPAT_FREE_H
#define TMPL_COMPAT_FREE_H

/*  Standard macro for C++ usage. Check for this.                             */
#ifdef __cplusplus

/*  free is provided here in the std namespace.                               */
#include <cstdlib>

/*  Frees a pointer and sets it to NULL to avoid double frees.                */
#define TMPL_FREE(ptr)                                                         \
    do {                                                                       \
        std::free(ptr);                                                        \
        ptr = NULL;                                                            \
    } while (0)

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  Standard library header file providing the free function.                 */
#include <stdlib.h>

/*  Frees a pointer and sets it to NULL to avoid double frees.                */
#define TMPL_FREE(ptr)                                                         \
    do {                                                                       \
        free(ptr);                                                             \
        ptr = NULL;                                                            \
    } while (0)

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
