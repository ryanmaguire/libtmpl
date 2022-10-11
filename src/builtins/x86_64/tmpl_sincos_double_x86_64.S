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
#ifdef __APPLE__

#else
.text
.p2align 4
.globl  tmpl_Double_SinCos
.type   tmpl_Double_SinCos, @function

tmpl_Double_SinCos:
        pushq   %rbp
        movq    %rdi, %rbp
        pushq   %rbx
        movq    %rsi, %rbx
        subq    $24, %rsp
        leaq    8(%rsp), %rdi
        movq    %rsp, %rsi
        call    sincos@PLT
        movsd   8(%rsp), %xmm0
        movsd   %xmm0, 0(%rbp)
        movsd   (%rsp), %xmm0
        movsd   %xmm0, (%rbx)
        addq    $24, %rsp
        popq    %rbx
        popq    %rbp
        ret

.size   tmpl_Double_SinCos, .-tmpl_Double_SinCos

#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
