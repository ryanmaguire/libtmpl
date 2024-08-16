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
#ifndef TMPL_PPC64LE_ASM_H
#define TMPL_PPC64LE_ASM_H

#define ASM_BEGIN(func) \
.section ".text";       \
.align 2;               \
.p2align 4,,15;         \
.globl func;            \
.type func, @function;  \
func:

#if defined(__ELF__)
#define ASM_END(func) \
.size func,.-func;    \
.section .note.GNU-stack,"",%progbits
#else
#define ASM_END(func) ELF_SIZE(func) \
.size func,.-func
#endif

#endif
/*  End of include guard.                                                     */
