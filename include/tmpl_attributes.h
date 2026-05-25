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
 *      Provides macros for C23 attributes, while maintaining portability     *
 *      for libtmpl with older compilers and for use with C++.                *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  None.                                                                     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 25, 2026                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ATTRIBUTES_H
#define TMPL_ATTRIBUTES_H

/*  C89 does not define the __STDC_VERSION__ macro at all. Check for this.    */
#ifdef __STDC_VERSION__

/*  C23 introduced attributes. Check for compiler support.                    */
#if __STDC_VERSION__ >= 202311L

/*  C23 support found, indicate this for libtmpl.                             */
#define TMPL_ATTRIBUTES_SUPPORTED 1

#endif
/*  End of #if __STDC_VERSION__ >= 202311L.                                   */

#endif
/*  End of #ifdef __STDC_VERSION__.                                           */

/*  Provide some common attribute lists for libtmpl functions.                */
#ifdef TMPL_ATTRIBUTES_SUPPORTED

/*  Many math functions, like those of the type const double -> double, can   *
 *  be declared with the reproducible and unsequenced attributes. The GNU     *
 *  const attribute, which is stricter, may also be applied. GCC and Clang    *
 *  support gnu::const, and conforming C23 compilers are required to ignore   *
 *  vendor attributes if they are not supported, making this portable.        */
#define TMPL_CONST_FUNC [[nodiscard, gnu::const]]
#define TMPL_UNSEQUENCED [[reproducible, unsequenced]]

#else

/*  For compilers lacking C23 support, or when using C++ compilers, set these *
 *  macros to empty.                                                          */
#define TMPL_CONST_FUNC
#define TMPL_UNSEQUENCED

#endif
/*  End of #ifdef TMPL_ATTRIBUTES_SUPPORTED.                                  */

#endif
/*  End of include guard.                                                     */
