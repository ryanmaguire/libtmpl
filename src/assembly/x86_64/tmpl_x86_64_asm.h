/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_X86_64_ASM_H
#define TMPL_X86_64_ASM_H

/******************************************************************************
 *                                  Generic                                   *
 ******************************************************************************/
#ifdef __ELF__
#define ELF_FUNC(f) .type f, @function
#define ELF_SIZE(f) .size f, . - f
#define GNU_STACK_PROTECTION .section .note.GNU-stack, "", @progbits
#else
/*  Else for #ifdef __ELF__.                                                  */

#define ELF_FUNC(f)
#define ELF_SIZE(f)
#define GNU_STACK_PROTECTION
#endif
/*  End of #ifdef __ELF__.                                                    */

#ifndef ALIGN
#define ALIGN 4, 0x90
#endif
/*  End of #ifndef ALIGN.                                                     */

/******************************************************************************
 *                                  WINDOWS                                   *
 ******************************************************************************/
#if defined(_WIN32)
#define ASM_RODATA .section .rodata
#define ASM_END(f) .end
#define ASM_BEGIN(f)        \
    .text;                  \
    .p2align ALIGN;         \
    .globl f;               \
    .section .drectve;      \
    .ascii " -export:", #f; \
    .section .text;         \
    .def f;                 \
    .scl 2;                 \
    .type 32;               \
    .endef;                 \
    f:

/******************************************************************************
 *                                   APPLE                                    *
 ******************************************************************************/
#elif defined(__APPLE__)

#ifndef __NO_UNDERSCORES__
#define EXT(x) _##x
#else
/*  Else for #ifndef __NO_UNDERSCORES__.                                      */

#define EXT(x) x
#endif
/*  End of #ifndef __NO_UNDERSCORES__.                                        */

#define ASM_RODATA .section __TEXT, __const
#define ASM_BEGIN(f) .text; .globl EXT(f); .p2align ALIGN; EXT(f):
#define ASM_END(f)

/******************************************************************************
 *                           GNU/Linux and FreeBSD                            *
 ******************************************************************************/
#else

#define ASM_RODATA .section .rodata
#define ASM_BEGIN(f) .text; .p2align ALIGN; .globl f; ELF_FUNC(f); f:
#define ASM_END(f) ELF_SIZE(f); GNU_STACK_PROTECTION

#endif
/*  End of #if defined(_WIN32).                                               */

#endif
/*  End of include guard.                                                     */
