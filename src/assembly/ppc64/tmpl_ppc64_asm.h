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
#ifndef TMPL_PPC64_ASM_H
#define TMPL_PPC64_ASM_H

/*  IBM PowerPC-64 little endian (ppc64le).                                   */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define ASM_BEGIN(func)                 \
.section ".text";                       \
.align 2;                               \
.p2align 4,,15;                         \
.globl func;                            \
.type func, @function;                  \
func:

#if defined(__ELF__)
#define ASM_END(func)                   \
.size func, . - func;                   \
.section .note.GNU-stack, "", %progbits
#else
#define ASM_END(func) .size func, . - func
#endif

/*  IBM PowerPC-64 big endian (ppc64).                                        */
#else

#define ASM_BEGIN(func)                 \
.section ".text";                       \
.align 2;                               \
.p2align 4,,15;                         \
.globl func;                            \
.section ".opd", "aw";                  \
.align 3;                               \
func:                                   \
.quad .L.func, .TOC.@tocbase, 0;        \
.previous;                              \
.type func, @function;                  \
.L.func:

#if defined(__ELF__)
#define ASM_END(func)                   \
.size func, . - .L.func;                \
.section .note.GNU-stack, "", %progbits
#else
#define ASM_END(func) .size func, . - func
#endif

#endif
/*  End of #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__.                     */

#endif
/*  End of include guard.                                                     */
