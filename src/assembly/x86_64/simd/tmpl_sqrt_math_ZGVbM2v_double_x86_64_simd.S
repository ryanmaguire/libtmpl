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

    /*  Modern CPUs provide vectorized versions of the square root function.  */
#if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__)
    vmovq %xmm1, %rax
    testq %rax, %rax
    je .L0

    /*  This is the only difference between AVX / AVX2 and AVX-512.           */
#if defined(__AVX512F__)
    vmovsd %xmm0, %xmm0, %xmm2
#else
    vmovapd %xmm0, %xmm2
#endif

    xorl %edx, %edx
    vsqrtsd %xmm2, %xmm2, %xmm2
    vpinsrq $1, %rdx, %xmm2, %xmm2
.L0:
    vpextrq $1, %xmm1, %rax
    testq %rax, %rax
    je .L1
    vunpckhpd %xmm0, %xmm0, %xmm0
    vsqrtsd %xmm0, %xmm0, %xmm0
    vmovq %xmm0, %rdx
    vpinsrq $1, %rdx, %xmm2, %xmm2
.L1:
    vmovdqa %xmm2, %xmm0

    /*  The scalar square root function has been provided as an instruction   *
     *  since SSE 2, released in 2000.                                        */
#else
    movaps %xmm0, -56(%rsp)
    movl $2, %edx
    xorl %eax, %eax
    movaps %xmm1, -40(%rsp)
    jmp .L1
.L0:
    movl $1, %edx
.L1:
    cmpq $0, -40(%rsp, %rax, 8)
    je .L2
    movsd -56(%rsp, %rax, 8), %xmm0
    sqrtsd %xmm0, %xmm0
    movsd %xmm0, -24(%rsp, %rax, 8)
.L2:
    movl $1, %eax
    cmpl $1, %edx
    jne .L0
    movapd -24(%rsp), %xmm0

#endif
/*  End of #if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__). */

    ret

ASM_END(_ZGVbM2v_tmpl_Double_Sqrt)
