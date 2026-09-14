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

ASM_BEGIN(_ZGVbN2v_tmpl_Double_Sqrt)

    /*  Modern CPUs provide vectorized versions of the square root function.  */
#if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__)
    vxorps  %xmm1, %xmm1, %xmm1
    vmovapd %xmm0, -40(%rsp)
    movl $2, %edx
    xorl %eax, %eax
    jmp .L0
.L1:
    movl    $1, %edx
.L0:
    vsqrtsd -40(%rsp, %rax, 8), %xmm1, %xmm0
    vmovlpd %xmm0, -24(%rsp, %rax, 8)
    movl $1, %eax
    cmpl $1, %edx
    jne .L1
    vmovapd -24(%rsp), %xmm0

    /*  The scalar square root function has been provided as an instruction   *
     *  since SSE 2, released in 2000.                                        */
#else
    movaps %xmm0, -40(%rsp)
    movl $2, %edx
    xorl %eax, %eax
    jmp .L1
.L0:
    movl $1, %edx
.L1:
    movsd -40(%rsp, %rax, 8), %xmm0
    sqrtsd %xmm0, %xmm0
    movsd %xmm0, -24(%rsp, %rax, 8)
    movl $1, %eax
    cmpl $1, %edx
    jne .L0
    movapd -24(%rsp), %xmm0

#endif
/*  End of #if defined(__AVX512F__) || defined(__AVX__) || defined(__AVX2__). */

    ret

ASM_END(_ZGVbN2v_tmpl_Double_Sqrt)
