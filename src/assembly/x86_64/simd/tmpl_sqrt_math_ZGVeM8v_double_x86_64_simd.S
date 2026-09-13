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

ASM_BEGIN(_ZGVeM8v_tmpl_Double_Sqrt)
    pushq %rbp
    vmovd %edi, %xmm1
    vpcmpeqd %ymm2, %ymm2, %ymm2
    vpbroadcastd %xmm1, %ymm1
    vpsrld $31, %ymm2, %ymm2
    movq %rsp, %rbp
    andq $-64, %rsp
    vpsrlvd .LC0(%rip), %ymm1, %ymm1
    vpand %ymm2, %ymm1, %ymm1
    vpxor %xmm2, %xmm2, %xmm2
    vpcmpeqd %ymm2, %ymm1, %ymm1
    vsqrtpd %ymm0, %ymm2
    vextractf64x4 $0x1, %zmm0, %ymm0
    vsqrtpd %ymm0, %ymm0
    vpmovsxdq %xmm1, %ymm3
    vextracti128 $0x1, %ymm1, %xmm1
    vpmovsxdq %xmm1, %ymm1
    vblendvpd %ymm3, -64(%rsp), %ymm2, %ymm2
    vblendvpd %ymm1, -32(%rsp), %ymm0, %ymm0
    vmovapd %ymm2, -64(%rsp)
    vmovapd %ymm0, -32(%rsp)
    vmovupd -64(%rsp), %zmm0
    leave
    ret

.LC0:
    .long 0
    .long 1
    .long 2
    .long 3
    .long 4
    .long 5
    .long 6
    .long 7
ASM_END(_ZGVeM8v_tmpl_Double_Sqrt)
