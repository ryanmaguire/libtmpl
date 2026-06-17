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

/*  The __has_cpp_attribute macro was introduced in C++20, but older          *
 *  compilers may support attribute checking.                                 */
#ifdef __has_cpp_attribute
#define TMPL_HAS_ATTRIBUTE(attr) __has_cpp_attribute(attr)
#else
#define TMPL_HAS_ATTRIBUTE(attr) 0
#endif

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
#define TMPL_HAS_ATTRIBUTE(attr) __has_c_attribute(attr)

#endif
/*  End of #if __STDC_VERSION__ >= 202311L.                                   */

#endif
/*  End of #ifdef __STDC_VERSION__.                                           */

#endif
/*  End of #ifdef __cplusplus.                                                */

/*  Provide some common attribute lists for libtmpl functions.                */
#ifdef TMPL_ATTRIBUTES_SUPPORTED

/*  Math functions of the form double -> double often do not need to edit     *
 *  global data in order to perform their computation. The gnu::const         *
 *  attribute helps compilers (like GCC) vectorize such functions on CPUs     *
 *  that support SIMD operations.                                             */
#if TMPL_HAS_ATTRIBUTE(nodiscard) && TMPL_HAS_ATTRIBUTE(gnu::const)
#define TMPL_CONST_FUNC [[nodiscard, gnu::const]]
#elif TMPL_HAS_ATTRIBUTE(gnu::const)
#define TMPL_CONST_FUNC [[gnu::const]]
#else
#define TMPL_CONST_FUNC
#endif

/*  Some math functions take in pointers to constants. These can often be     *
 *  declared with the GNU pure attribute.                                     */
#if TMPL_HAS_ATTRIBUTE(nodiscard) && TMPL_HAS_ATTRIBUTE(gnu::pure)
#define TMPL_PURE_FUNC [[nodiscard, gnu::pure]]
#elif TMPL_HAS_ATTRIBUTE(gnu::pure)
#define TMPL_PURE_FUNC [[gnu::pure]]
#else
#define TMPL_PURE_FUNC
#endif

/*  Reproducible is a C23 attribute that provides optimization hints.         */
#if TMPL_HAS_ATTRIBUTE(reproducible)
#define TMPL_REPRODUCIBLE [[reproducible]]
#else
#define TMPL_REPRODUCIBLE
#endif

/*  Unsequenced implies reproducible, but not the other way around. Check for *
 *  unsequenced support first, but if the compiler does not implement         *
 *  unsequenced but does support reproducible, then have the macro fall back  *
 *  to reproducible.                                                          */
#if TMPL_HAS_ATTRIBUTE(unsequenced)
#define TMPL_UNSEQUENCED [[unsequenced]]
#else
#define TMPL_UNSEQUENCED TMPL_REPRODUCIBLE
#endif

/*  Leaf functions are functions with external linkage that make no function  *
 *  calls. This attribute helps improve optimizations.                        */
#if TMPL_HAS_ATTRIBUTE(gnu::leaf)
#define TMPL_LEAF_FUNC [[gnu::leaf]]
#else
#define TMPL_LEAF_FUNC
#endif

/*  Some functions, like 2Sum, Fast2Sum, and 2Prod, make use of the fact that *
 *  floating-point arithmetic is not associative. The gnu::optimize attribute *
 *  can help prevent compilers from aggressively optimizing and breaking such *
 *  functions.                                                                */
#if TMPL_HAS_ATTRIBUTE(gnu::optimize)
#define TMPL_NO_ASSOCIATIVE_MATH [[gnu::optimize("no-associative-math")]]
#else
#define TMPL_NO_ASSOCIATIVE_MATH
#endif

/*  Similarly, some functions make use of the fact that x * y + z is done in  *
 *  two steps, producing two roundings: fl(fl(x * y) + z), where fl(a) is     *
 *  the real number a rounded to the nearest floating-point value. Compilers  *
 *  may replace x * y + z with a Fused-Multiply-Add call (FMA), which may     *
 *  ruin certain functions. The following attribute prevents this.            */
#if TMPL_HAS_ATTRIBUTE(gnu::optimize)
#define TMPL_NO_CONTRACT_MATH [[gnu::optimize("fp-contract=off")]]
#else
#define TMPL_NO_CONTRACT_MATH
#endif

/*  Many helper / auxiliary functions serve no purpose other than to improve  *
 *  the organization of some main function. These functions should always be  *
 *  inlined. Various compilers provide methods of doing this.                 */
#if TMPL_HAS_ATTRIBUTE(gnu::always_inline)
#define TMPL_ALWAYS_INLINE [[gnu::always_inline]]
#elif TMPL_HAS_ATTRIBUTE(clang::always_inline)
#define TMPL_ALWAYS_INLINE [[clang::always_inline]]
#elif TMPL_HAS_ATTRIBUTE(msvc::forceinline)
#define TMPL_ALWAYS_INLINE [[msvc::forceinline]]
#else
#define TMPL_ALWAYS_INLINE
#endif

/*  Undefine the attribute macro to prevent possible collisions.              */
#undef TMPL_HAS_ATTRIBUTE

#else
/*  Else for #ifdef TMPL_ATTRIBUTES_SUPPORTED.                                */

/*  For compilers lacking C23 support, or when using older C++ compilers, set *
 *  these macros to be empty.                                                 */
#define TMPL_CONST_FUNC
#define TMPL_PURE_FUNC
#define TMPL_LEAF_FUNC
#define TMPL_REPRODUCIBLE
#define TMPL_UNSEQUENCED
#define TMPL_NO_ASSOCIATIVE_MATH
#define TMPL_NO_CONTRACT_MATH
#define TMPL_ALWAYS_INLINE

#endif
/*  End of #ifdef TMPL_ATTRIBUTES_SUPPORTED.                                  */

#endif
/*  End of include guard.                                                     */
