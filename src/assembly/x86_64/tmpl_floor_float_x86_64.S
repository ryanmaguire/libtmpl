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

/*  Apple x86_64 machines. Works with clang and gcc.                          */
#if defined(__APPLE__)
.globl _tmpl_Float_Floor
.align 4,0x90;

_tmpl_Float_Floor:
    roundss $9, %xmm0, %xmm0
    ret

/*  GNU/Linux and FreeBSD (and others). Works with gcc, clang, and pcc.       */
#else
.text;
.p2align 4,0x90;
.globl tmpl_Float_Floor;
.type tmpl_Float_Floor,@function;

tmpl_Float_Floor:
    roundss $9, %xmm0, %xmm0
    ret

.size tmpl_Float_Floor, . - tmpl_Float_Floor
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif