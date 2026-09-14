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

ASM_BEGIN(_ZGVcM4v_tmpl_Double_Sqrt)

    /*  AVX2 and AVX-512 need fewer instructions than AVX.                    */
#if defined(__AVX512F__) || defined(__AVX2__)
    pushq %rbp
    vsqrtpd %ymm0, %ymm0
    vpxor %xmm2, %xmm2, %xmm2
    vpcmpeqq %ymm1, %ymm2, %ymm2
    movq %rsp, %rbp
    andq $-32, %rsp
    vblendvpd %ymm2, -32(%rsp), %ymm0, %ymm0

    /*  AVX version below.                                                    */
#else
    pushq %rbp
    vpxor %xmm4, %xmm4, %xmm4
    vsqrtpd %xmm0, %xmm2
    vextractf128 $0x1, %ymm0, %xmm0
    vpcmpeqq %xmm4, %xmm1, %xmm3
    vextractf128 $0x1, %ymm1, %xmm1
    vsqrtpd %xmm0, %xmm0
    vpcmpeqq %xmm4, %xmm1, %xmm1
    movq %rsp, %rbp
    andq $-32, %rsp
    vblendvpd %xmm1, -16(%rsp), %xmm0, %xmm0
    vblendvpd %xmm3, -32(%rsp), %xmm2, %xmm2
    vmovapd %xmm2, -32(%rsp)
    vmovapd %xmm0, -16(%rsp)
    vmovupd -32(%rsp), %ymm0

#endif
/*  End of #if defined(__AVX512F__) || defined(__AVX2__).                     */

    leave
    ret

ASM_END(_ZGVcM4v_tmpl_Double_Sqrt)
