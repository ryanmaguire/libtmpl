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
 *      Writes the TMPL_USE_INLINE and TMPL_ALWAYS_INLINE macros to a file.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_write_use_inline                                                 *
 *  Purpose:                                                                  *
 *      Writes the inline macros to a file.                                   *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          File pointer for the file being written to.                       *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Called Functions:                                                         *
 *      stdio.h:                                                              *
 *          fputs:                                                            *
 *              Writes a string to a file.                                    *
 *          puts:                                                             *
 *              Prints an error message if fp is NULL.                        *
 *  Method:                                                                   *
 *      Check if the C compiler supports inline and force-inline, and then    *
 *      check the TMPL_SET_INLINE_TRUE and TMPL_SET_ALWAYS_INLINE_TRUE build  *
 *      options. Write the result with fputs.                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard library header file providing FILE, fputs, and puts.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 27, 2025                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_CONFIG_WRITE_USE_INLINE_H
#define TMPL_CONFIG_WRITE_USE_INLINE_H

/*  FILE type, fputs, and puts provided here.                                 */
#include <stdio.h>

/******************************************************************************
 *                              Language Support                              *
 ******************************************************************************/

/*  C introduced the inline keyword starting with C99. Check for support.     */
#ifdef __STDC_VERSION__

/*  C99, C11, C18, and C23 (and likely later revisions) all support inline.   */
#if __STDC_VERSION__ >= 199901L
#define TMPL_CONFIG_HAS_INLINE 1
#else
#define TMPL_CONFIG_HAS_INLINE 0
#endif
/*  End of #if __STDC_VERSION__ >= 199901L.                                   */

/*  C23 standardized attribute syntax and allows vendor-specific attributes   *
 *  like [[gnu::always_inline]] or [[msvc::forceinline]]. Check for support.  */
#if __STDC_VERSION__ >= 202311L && defined(__has_c_attribute)
#define TMPL_CONFIG_HAS_C23_ATTRIBUTE(x) __has_c_attribute(x)
#else
#define TMPL_CONFIG_HAS_C23_ATTRIBUTE(x) 0
#endif
/*  End of #if __STDC_VERSION__ >= 202311L && defined(__has_c_attribute).     */

/*  C++ compilers also provide the inline keyword. MSVC supports inlining     *
 *  functions but does not define the __STDC_VERSION__ macro by default.      */
#elif defined(__cplusplus) || defined(_MSC_VER)
#define TMPL_CONFIG_HAS_INLINE 1

/*  C89/C90 compilers are not required to support the inline keyword.         */
#else
#define TMPL_CONFIG_HAS_INLINE 0
#endif
/*  End of #ifdef __STDC_VERSION__.                                           */

/*  C89 compilers and MSVC without the /std flag will not have this macro     *
 *  defined, nor will they support C23 attributes.                            */
#ifndef TMPL_CONFIG_HAS_C23_ATTRIBUTE
#define TMPL_CONFIG_HAS_C23_ATTRIBUTE(x) 0
#endif

/******************************************************************************
 *                            Force Inline Support                            *
 ******************************************************************************/

/*  C89 does not have the inline keyword, so there is nothing to do here.     */
#if TMPL_CONFIG_HAS_INLINE == 0

#define TMPL_CONFIG_FORCE_INLINE ""
#define TMPL_CONFIG_FORCE_STATIC "static"

/*  GCC, and compilers that claim GCC compatibility.                          */
#elif defined(__GNUC__)

#if TMPL_CONFIG_HAS_C23_ATTRIBUTE(gnu::always_inline)
#define TMPL_CONFIG_FORCE_INLINE "[[gnu::always_inline]] inline"
#define TMPL_CONFIG_FORCE_STATIC "[[gnu::always_inline]] static inline"
#else
#define TMPL_CONFIG_FORCE_INLINE "__attribute__((always_inline)) inline"
#define TMPL_CONFIG_FORCE_STATIC "__attribute__((always_inline)) static inline"
#endif
/*  End of #if TMPL_CONFIG_HAS_C23_ATTRIBUTE(gnu::always_inline).             */

/*  Clang supports GNU-style attributes, and recent versions of clang support *
 *  C23 attributes. Note, clang defines __GNUC__ by default meaning the       *
 *  previous branch will likely be used with clang instead.                   */
#elif defined(__clang__)

#if TMPL_CONFIG_HAS_C23_ATTRIBUTE(clang::always_inline)
#define TMPL_CONFIG_FORCE_INLINE "[[clang::always_inline]] inline"
#define TMPL_CONFIG_FORCE_STATIC "[[clang::always_inline]] static inline"
#else
#define TMPL_CONFIG_FORCE_INLINE "__attribute__((always_inline)) inline"
#define TMPL_CONFIG_FORCE_STATIC "__attribute__((always_inline)) static inline"
#endif
/*  End of #if TMPL_CONFIG_HAS_C23_ATTRIBUTE(clang::always_inline).           */

/*  Microsoft's MSVC. forceinline already implies inline.                     */
#elif defined(_MSC_VER)

#if TMPL_CONFIG_HAS_C23_ATTRIBUTE(msvc::forceinline)
#define TMPL_CONFIG_FORCE_INLINE "[[msvc::forceinline]]"
#define TMPL_CONFIG_FORCE_STATIC "[[msvc::forceinline]] static"
#else
#define TMPL_CONFIG_FORCE_INLINE "__forceinline"
#define TMPL_CONFIG_FORCE_STATIC "static __forceinline"
#endif
/*  End of #if TMPL_CONFIG_HAS_C23_ATTRIBUTE(msvc::forceinline).              */

/*  Solaris Developer Studio supports the GNU always_inline attribute.        */
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#define TMPL_CONFIG_FORCE_INLINE "inline __attribute__((always_inline))"
#define TMPL_CONFIG_FORCE_STATIC "static inline __attribute__((always_inline))"

/*  Any other C99 (or later) compiler. Use the plain inline keyword.          */
#else

#define TMPL_CONFIG_FORCE_INLINE "inline"
#define TMPL_CONFIG_FORCE_STATIC "static inline"

#endif
/*  End of #if TMPL_CONFIG_HAS_INLINE == 0.                                   */

/******************************************************************************
 *                               Build Options                                *
 ******************************************************************************/

/*  Check for an incompatible configuration.                                  */
#if defined(TMPL_SET_INLINE_TRUE) && TMPL_CONFIG_HAS_INLINE == 0
#error "libtmpl: inline requested but not supported."
#endif

/*  Check if inline support has been requested.                               */
#if defined(TMPL_SET_INLINE_TRUE)

#define TMPL_CONFIG_USE_INLINE "1"

/*  Users may also request inline functions be forced inline. This option     *
 *  only has an effect when inline is enabled.                                */
#if defined(TMPL_SET_ALWAYS_INLINE_TRUE)
#define TMPL_CONFIG_INLINE_DECL TMPL_CONFIG_FORCE_STATIC
#define TMPL_CONFIG_ALWAYS_INLINE TMPL_CONFIG_FORCE_INLINE
#else
#define TMPL_CONFIG_INLINE_DECL "static inline"
#define TMPL_CONFIG_ALWAYS_INLINE ""
#endif
/*  End of #if defined(TMPL_SET_ALWAYS_INLINE_TRUE).                          */

/*  If inline has been disabled, the macros are set to their zero values.     */
#else

#define TMPL_CONFIG_USE_INLINE "0"
#define TMPL_CONFIG_INLINE_DECL ""
#define TMPL_CONFIG_ALWAYS_INLINE ""

#endif
/*  End of #if defined(TMPL_SET_INLINE_TRUE).                                 */

/*  TMPL_STATIC_INLINE is used for helper functions that are not visible to   *
 *  the user. These are inlined whenever possible regardless of build options.*
 *  For compilers lacking inline, these functions are declared static.        */
#define TMPL_CONFIG_STATIC_INLINE TMPL_CONFIG_FORCE_STATIC

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
        "#define TMPL_USE_INLINE " TMPL_CONFIG_USE_INLINE "\n"
        "#define TMPL_INLINE_DECL " TMPL_CONFIG_INLINE_DECL "\n"
        "#define TMPL_STATIC_INLINE " TMPL_CONFIG_STATIC_INLINE "\n"
        "#define TMPL_ALWAYS_INLINE " TMPL_CONFIG_ALWAYS_INLINE "\n\n",
        fp
    );
}
/*  End of tmpl_write_use_inline.                                             */

/*  Undefine everything to avoid conflicts.                                   */
#undef TMPL_CONFIG_HAS_INLINE
#undef TMPL_CONFIG_HAS_C23_ATTRIBUTE
#undef TMPL_CONFIG_FORCE_INLINE
#undef TMPL_CONFIG_FORCE_STATIC
#undef TMPL_CONFIG_USE_INLINE
#undef TMPL_CONFIG_INLINE_DECL
#undef TMPL_CONFIG_ALWAYS_INLINE
#undef TMPL_CONFIG_STATIC_INLINE

#endif
/*  End of include guard.                                                     */
