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
.globl    _tmpl_Float_SinCos
.p2align  4, 0x90

_tmpl_Float_SinCos:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %r14
        pushq   %rbx
        movq    %rsi, %r14
        movq    %rdi, %rbx
        callq   ___sincosf_stret
        movss   %xmm0, (%rbx)
        extractps       $1, %xmm0, (%r14)
        popq    %rbx
        popq    %r14
        popq    %rbp
        retq

#else
.text
.p2align 4
.globl  tmpl_Float_SinCos
.type   tmpl_Float_SinCos, @function

tmpl_Float_SinCos:
        pushq   %rbp
        movq    %rdi, %rbp
        pushq   %rbx
        movq    %rsi, %rbx
        subq    $24, %rsp
        leaq    12(%rsp), %rdi
        leaq    8(%rsp), %rsi
        call    sincosf@PLT
        movss   12(%rsp), %xmm0
        movss   %xmm0, 0(%rbp)
        movss   8(%rsp), %xmm0
        movss   %xmm0, (%rbx)
        addq    $24, %rsp
        popq    %rbx
        popq    %rbp
        ret

.size   tmpl_Float_SinCos, .-tmpl_Float_SinCos

#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
