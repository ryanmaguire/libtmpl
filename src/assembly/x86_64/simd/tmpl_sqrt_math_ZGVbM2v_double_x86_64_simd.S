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

/*  Helper macros found here.                                                 */
#include "../tmpl_x86_64_asm.h"

ASM_BEGIN(_ZGVbM2v_tmpl_Double_Sqrt)
    movaps %xmm0, -56(%rsp)
    movl $2, %edx
    xorl %eax, %eax
    movaps %xmm1, -40(%rsp)
    jmp .L8
.L9:
    movl $1, %edx
.L8:
    cmpq $0, -40(%rsp, %rax, 8)
    je .L7
    movsd -56(%rsp, %rax, 8), %xmm0
    sqrtsd %xmm0, %xmm0
    movsd %xmm0, -24(%rsp, %rax, 8)
.L7:
    movl $1, %eax
    cmpl $1, %edx
    jne .L9
    movapd -24(%rsp), %xmm0
    ret
ASM_END(_ZGVbM2v_tmpl_Double_Sqrt)
