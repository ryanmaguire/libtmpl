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
 *                                  tmpl_cast                                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides macros for casting with C vs. C++ compatibility.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 21, 2024                                            *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COMPAT_CAST_H
#define TMPL_COMPAT_CAST_H

/*  Standard macro for C++ usage. Check for this.                             */
#ifdef __cplusplus

/*  Macro for casting data using C++ static_cast syntax.                      */
#define TMPL_CAST(x, type) static_cast<type>((x))

#else
/*  Else for #ifdef __cplusplus. Below is C code.                             */

/*  Macro for casting data using the standard C syntax.                       */
#define TMPL_CAST(x, type) (type)((x))

#endif
/*  End of #ifdef __cplusplus.                                                */

#endif
/*  End of include guard.                                                     */
