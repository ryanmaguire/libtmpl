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

/*  realloc provided here.                                                    */
#include <cstdlib>

/*  Macro for reallocating memory. The output is a void pointer.              */
#define TMPL_REALLOC(ptr, size) std::realloc(ptr, sizeof(*(ptr)) * (size))

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  Standard library header file providing the realloc function.              */
#include <stdlib.h>

/*  Macro for reallocating memory. The output is a void pointer.              */
#define TMPL_REALLOC(ptr, size) realloc(ptr, sizeof(*(ptr)) * (size))

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
