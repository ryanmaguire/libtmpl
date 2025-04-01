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
 *                                 tmpl_stdlib                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides macros for stdlib functions with C vs. C++ compatibility.    *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header file providing malloc and free.           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 21, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPAT_STDLIB_H
#define TMPL_COMPAT_STDLIB_H

/*  Standard macro for C++ usage. Check for this.                             */
#ifdef __cplusplus

/*  malloc provided here. As is free.                                         */
#include <cstdlib>

/*  Macro for allocating memory. In C++ one must cast the result of malloc.   */
#define TMPL_MALLOC(type, N) static_cast<type *>(std::malloc(sizeof(type) * N))

/*  Free's a pointer and sets it to NULL to avoid double free's.              */
#define TMPL_FREE(var) if (var){std::free(var); var = NULL;}

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  malloc provided here. As is free.                                         */
#include <stdlib.h>

/*  Macro for malloc. In C one should not cast the result of malloc.          */
#define TMPL_MALLOC(type, N) malloc(sizeof(type) * N)

/*  Free's a pointer and sets it to NULL to avoid double free's.              */
#define TMPL_FREE(var) if (var){free(var); var = NULL;}

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
