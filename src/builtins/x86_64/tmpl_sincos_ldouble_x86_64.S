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
.globl    _tmpl_LDouble_SinCos
.p2align  4, 0x90

_tmpl_LDouble_SinCos:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %r14
        pushq   %rbx
        subq    $32, %rsp
        movq    %rsi, %r14
        movq    %rdi, %rbx
        fldt    16(%rbp)
        fld     %st(0)
        fstpt   -28(%rbp)
        fstpt   (%rsp)
        callq   _sinl
        fstpt   (%rbx)
        fldt    -28(%rbp)
        fstpt   (%rsp)
        callq   _cosl
        fstpt   (%r14)
        addq    $32, %rsp
        popq    %rbx
        popq    %r14
        popq    %rbp
        retq

#else
.text
.p2align 4
.globl  tmpl_LDouble_SinCos
.type   tmpl_LDouble_SinCos, @function

tmpl_LDouble_SinCos:
        pushq   %rbp
        movq    %rdi, %rbp
        pushq   %rbx
        movq    %rsi, %rbx
        subq    $40, %rsp
        leaq    16(%rsp), %rdi
        movq    %rsp, %rsi
        pushq   72(%rsp)
        pushq   72(%rsp)
        call    sincosl@PLT
        fldt    32(%rsp)
        fstpt   0(%rbp)
        fldt    16(%rsp)
        fstpt   (%rbx)
        addq    $56, %rsp
        popq    %rbx
        popq    %rbp
        ret

.size   tmpl_LDouble_SinCos, .-tmpl_LDouble_SinCos

#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
