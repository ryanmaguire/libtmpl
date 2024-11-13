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
#ifndef TMPL_AARCH64_ASM_H
#define TMPL_AARCH64_ASM_H

/******************************************************************************
 *                                  Generic                                   *
 ******************************************************************************/
#ifdef __ELF__
#define ELF_FUNC(func) .type func, %function
#define ELF_SIZE(func) .size func, . - func
#define GNU_STACK_PROTECTION .section .note.GNU-stack, "", %progbits
#else
/*  Else for #ifdef __ELF__.                                                  */

#define ELF_FUNC(func)
#define ELF_SIZE(func)
#define GNU_STACK_PROTECTION
#endif
/*  End of #ifdef __ELF__.                                                    */

#ifndef ALIGN
#define ALIGN 2
#endif
/*  End of #ifndef ALIGN.                                                     */

/******************************************************************************
 *                                   APPLE                                    *
 ******************************************************************************/
#if defined (__APPLE__)

#ifndef __NO_UNDERSCORES__
#define EXT(x) _##x
#else
#define EXT(x) x
#endif

#define ASM_END(func) ELF_SIZE(EXT(func))
#define ASM_BEGIN(func) EXT(func):

/******************************************************************************
 *                           GNU/Linux and FreeBSD                            *
 ******************************************************************************/
#else

#define ASM_END(func)       \
ELF_SIZE(func);             \
GNU_STACK_PROTECTION

#define ASM_BEGIN(func)     \
.text;                      \
.align ALIGN;               \
.globl func;                \
ELF_FUNC(func);             \
func:

#endif
/*  End of #ifdef __APPLE__.                                                  */

#endif
/*  End of include guard.                                                     */
