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
 *                        tmpl_config_write_use_inline                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Writes the TMPL_INLINE macro to a file.                               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_use_inline                                                 *
 *  Purpose:                                                                  *
 *      Writes the TMPL_INLINE macro to a file.                               *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *  Method:                                                                   *
 *      Check the TMPL_SET_INLINE_TRUE macro and C99 support, then call fputs.*
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header file providing FILE and fputs.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_USE_INLINE_H
#define TMPL_CONFIG_WRITE_USE_INLINE_H

/*  FILE type and fputs provided here.                                        */
#include <stdio.h>

#define TMPL_TO_STRING(x) #x
#define TMPL_STRINGIFY(x) TMPL_TO_STRING(x)

/*  Probe to see if the compiler supports some version of always inline.      */
#if !defined(__STDC_VERSION__)

/*  The inline keyword was not defined at all in C89.                         */
#define TMPL_HAS_ATTRIBUTE(x) 0

/*  Attribute syntax was introduced in C23, older versions do not support.    */
#elif __STDC_VERSION__ < 202311L
#define TMPL_HAS_ATTRIBUTE(x) 0

/*  The __has_c_attribute is the standard way of testing for C23 attributes,  *
 *  but C compilers may not implement it. Check first.                        */
#elif !defined(__has_c_attribute)
#define TMPL_HAS_ATTRIBUTE(x) 0

/*  With the __has_c_attribute available macro we can check for always_inline *
 *  in a standard compliant manner. Use this for the macro.                   */
#else
#define TMPL_HAS_ATTRIBUTE(x) __has_c_attribute(x)

#endif
/*  End of #if !defined(__STDC_VERSION__).                                    */

/*  GCC has provided always_inline since the 1990s.                           */
#if defined(__GNUC__)

/*  GCC 15+ set __STDC_VERSION__ to indicate C23 support. C23 attribute       *
 *  syntax is allowed.                                                        */
#if TMPL_HAS_ATTRIBUTE(gnu::always_inline)

#define TMPL_FORCE_EXTERN_INLINE [[gnu::always_inline]] inline
#define TMPL_FORCE_STATIC_INLINE [[gnu::always_inline]] static inline

/*  Older versions of GCC may use the __attribute__ syntax.                   */
#else

#define TMPL_FORCE_EXTERN_INLINE inline __attribute__((always_inline))
#define TMPL_FORCE_STATIC_INLINE static inline __attribute__((always_inline))

#endif
/*  End of #if TMPL_HAS_ATTRIBUTE(gnu::always_inline).                        */

/*  LLVM's Clang has supported always_inline since at least the late 2000's.  */
#elif defined(__clang__)

/*  Clang 22+ set __STDC_VERSION__ to indicate C23 support. C23 attributes    *
 *  are supported with these versions.                                        */
#if TMPL_HAS_ATTRIBUTE(clang::always_inline)

#define TMPL_FORCE_EXTERN_INLINE [[clang::always_inline]] inline
#define TMPL_FORCE_STATIC_INLINE [[clang::always_inline]] static inline

/*  Older versions of Clang still support the GCC __attribute__ syntax.       */
#else

#define TMPL_FORCE_EXTERN_INLINE inline __attribute__((always_inline))
#define TMPL_FORCE_STATIC_INLINE static inline __attribute__((always_inline))

#endif
/*  End of #if TMPL_HAS_ATTRIBUTE(clang::always_inline).                      */

/*  Microsoft's C compiler MSVC supports forceinline, which produces an       *
 *  effect similar to GCC and Clang's always_inline.                          */
#elif defined(_MSC_VER)

/*  MSVC supports the C++11 attribute [[msvc::forceinline]], but C23 support  *
 *  is lacking in MSVC < 19. Check for C23 support.                           */
#if TMPL_HAS_ATTRIBUTE(msvc::forceinline)

#define TMPL_FORCE_EXTERN_INLINE [[msvc::forceinline]]
#define TMPL_FORCE_STATIC_INLINE [[msvc::forceinline]] static

/*  Lacking C23 attributes, MSVC supports the __forceinline specifier.        */
#else

#define TMPL_FORCE_EXTERN_INLINE __forceinline
#define TMPL_FORCE_STATIC_INLINE __forceinline static

#endif
/*  End of #if TMPL_HAS_ATTRIBUTE(msvc::forceinline).                         */

#else
/*  Else for #if defined(__GNUC__).                                           */

/*  The C99 standard (and higher) support the usual inline keyword.           */
#define TMPL_FORCE_EXTERN_INLINE inline
#define TMPL_FORCE_STATIC_INLINE static inline

#endif
/*  End of #if defined(__GNUC__).                                             */

/*  By default we assume inline is not allowed. We'll reset this later.       */
#define TMPL_USE_INLINE 0
#define TMPL_HAS_INLINE 0

/*  The inline keyword was only introduced with the C99 standard. Check.      */
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || \
    (defined(__cplusplus)) || \
    (defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER))

#undef TMPL_HAS_INLINE
#define TMPL_HAS_INLINE 1

/*  Users may optionally request libtmpl not use inline at all. Check.        */
#ifdef TMPL_SET_INLINE_TRUE

/*  inline is supported and requested. Reset the macro to 1.                  */
#undef TMPL_USE_INLINE
#define TMPL_USE_INLINE 1

#endif
/*  End of #ifdef TMPL_SET_INLINE_TRUE.                                       */

#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

/*  The TMPL_STATIC_INLINE macro does not require the TMPL_SET_INLINE_TRUE    *
 *  macro to be set since it is reserved exclusively for helper and auxiliary *
 *  functions that the user does not have direct access to. Hence the macro   *
 *  only depends on what the compiler can support.                            */
#if TMPL_HAS_INLINE == 1

/*  static inline is the standard declaration for inlining functions, but the *
 *  compiler does not need to actually inline anything. Functions declared    *
 *  with the TMPL_STATIC_INLINE macro are helper functions that are only used *
 *  in one specific library function (for example, tmpl_Double_Arccos calls   *
 *  the tmpl_Double_Arccos_Tail_End function for some arguments). Because of  *
 *  this, it is beneficial to require the compiler to inline the function.    *
 *  This can be achieved with compilers that implement the always_inline      *
 *  attribute or forceinline attribute.                                       */
#define TMPL_STATIC_INLINE_ARG TMPL_FORCE_STATIC_INLINE

/*  Lacking inline support, we can simply use the static keyword.             */
#else

/*  Functions declared with the TMPL_STATIC_INLINE macro are compiled in at   *
 *  most one translation unit at build time, and are not exposed to the user. *
 *  Declaring such functions with the static storage class specifier is the   *
 *  standard practice.                                                        */
#define TMPL_STATIC_INLINE_ARG static

#endif
/*  End of #if TMPL_HAS_INLINE == 1.                                          */

/*  The TMPL_INLINE_DECL macro depends on whether the user wants small        *
 *  library functions to be inlined or not. Check.                            */
#if TMPL_USE_INLINE == 1

/*  By default, TMPL_INLINE_DECL expands to static inline when inline is      *
 *  supported, and nothing otherwise since the function is then compiled and  *
 *  linked into the libtmpl.so file (or .a, .dll, .lib, etc.). The user can   *
 *  request the inline functions be declared with the always_inline attribute *
 *  on compilers that support this. Check for this.                           */
#ifdef TMPL_SET_ALWAYS_INLINE_TRUE

/*  The TMPL_FORCE_..._INLINE macros already contain the correct expansions.  */
#define TMPL_INLINE_ARG TMPL_FORCE_STATIC_INLINE
#define TMPL_ALWAYS_INLINE_ARG TMPL_FORCE_EXTERN_INLINE

#else
/*  Else for #ifdef TMPL_SET_ALWAYS_INLINE_TRUE.                              */

/*  If the user did not request always_inline, but normal inline support was  *
 *  requested, simply use the static inline specifier.                        */
#define TMPL_INLINE_ARG static inline
#define TMPL_ALWAYS_INLINE_ARG

#endif
/*  End of #ifdef TMPL_SET_ALWAYS_INLINE_TRUE.                                */

#else
/*  Else for #if TMPL_HAS_INLINE == 1.                                        */

/*  If inline support was not requested, or not available, then the           *
 *  *_no_inline.c files will be compiled. These files expect TMPL_INLINE_DECL *
 *  to expand to nothing.                                                     */
#define TMPL_INLINE_ARG
#define TMPL_ALWAYS_INLINE_ARG

#endif
/*  End of #if TMPL_HAS_INLINE == 1.                                          */

/*  Function for writing the TMPL_USE_INLINE and related macros to a file.    */
static void tmpl_write_use_inline(FILE *fp)
{
    /*  Avoid writing to a NULL file. Check first.                            */
    if (!fp)
    {
        puts(
            "Error Encountered: libtmpl\n"
            "    tmpl_write_use_inline\n\n"
            "Input FILE pointer is NULL.\n"
        );

        return;
    }

    fputs(
        "#define TMPL_USE_INLINE "
        TMPL_STRINGIFY(TMPL_USE_INLINE) "\n"
        "#define TMPL_INLINE_DECL "
        TMPL_STRINGIFY(TMPL_INLINE_ARG) "\n"
        "#define TMPL_STATIC_INLINE "
        TMPL_STRINGIFY(TMPL_STATIC_INLINE_ARG) "\n"
        "#define TMPL_ALWAYS_INLINE "
        TMPL_STRINGIFY(TMPL_ALWAYS_INLINE_ARG) "\n\n",
        fp
    );
}
/*  End of tmpl_write_use_inline.                                             */

/*  Undefine everything to avoid conflicts.                                   */
#undef TMPL_HAS_INLINE
#undef TMPL_USE_INLINE
#undef TMPL_INLINE_ARG
#undef TMPL_STATIC_INLINE_ARG
#undef TMPL_ALWAYS_INLINE_ARG
#undef TMPL_FORCE_EXTERN_INLINE
#undef TMPL_FORCE_STATIC_INLINE

#endif
/*  End of include guard.                                                     */
