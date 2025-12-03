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
 *                                 tmpl_calloc                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides a macro for calloc with C vs. C++ compatibility.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdlib.h:                                                             *
 *          Standard library header file providing calloc.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 3, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPAT_CALLOC_H
#define TMPL_COMPAT_CALLOC_H

/*  Standard macro for C++ usage. Check for this.                             */
#ifdef __cplusplus

/*  calloc provided here.                                                     */
#include <cstdlib>

/*  Macro for allocating memory. In C++ one must cast the result of calloc.   */
#define TMPL_CALLOC(type, n) static_cast<type *>(std::calloc(sizeof(type), (n)))

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  Standard library header file providing the calloc function.               */
#include <stdlib.h>

/*  Macro for calloc. In C one should not cast the result of calloc.          */
#define TMPL_CALLOC(type, n) calloc(sizeof(type), (n))

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
