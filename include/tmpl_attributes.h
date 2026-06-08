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
 *                               tmpl_attributes                              *
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

/*  C++ introduced attributes in C++11.                                       */
#ifdef __cplusplus

/*  Check if the compiler supports attributes.                                */
#if __cplusplus >= 201103L

/*  C++11 support found, indicate this.                                       */
#define TMPL_ATTRIBUTES_SUPPORTED 1

#endif
/*  End of #if __cplusplus >= 201103L.                                        */

#else
/*  Else for #ifdef __cplusplus.                                              */

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

#endif
/*  End of #ifdef __cplusplus.                                                */

/*  Provide some common attribute lists for libtmpl functions.                */
#ifdef TMPL_ATTRIBUTES_SUPPORTED

/*  Many math functions, like those of the type const double -> double, can   *
 *  be declared with the reproducible and unsequenced attributes. The GNU     *
 *  const attribute, which is stricter, may also be applied. GCC and Clang    *
 *  support gnu::const, and conforming C23 compilers are required to ignore   *
 *  vendor attributes if they are not supported, making this portable.        */
#define TMPL_CONST_FUNC [[nodiscard, gnu::const]]
#define TMPL_LEAF_FUNC [[gnu::leaf]]
#define TMPL_REPRODUCIBLE [[reproducible]]
#define TMPL_UNSEQUENCED [[reproducible, unsequenced]]
#define TMPL_NO_ASSOCIATIVE_MATH [[gnu::optimize("no-associative-math")]]
#define TMPL_NO_CONTRACT_MATH [[gnu::optimize("fp-contract=off")]]
#define TMPL_NO_FAST_MATH [[gnu::optimize("no-fast-math")]]
#define TMPL_ALWAYS_INLINE [[gnu::always_inline]]

#else

/*  For compilers lacking C23 support, or when using older C++ compilers, set *
 *  these macros to be empty.                                                 */
#define TMPL_CONST_FUNC
#define TMPL_LEAF_FUNC
#define TMPL_REPRODUCIBLE
#define TMPL_UNSEQUENCED
#define TMPL_NO_ASSOCIATIVE_MATH
#define TMPL_NO_CONTRACT_MATH
#define TMPL_NO_FAST_MATH
#define TMPL_ALWAYS_INLINE

#endif
/*  End of #ifdef TMPL_ATTRIBUTES_SUPPORTED.                                  */

#endif
/*  End of include guard.                                                     */
