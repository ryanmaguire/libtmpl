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

ASM_BEGIN(_ZGVdM4v_tmpl_Double_Sqrt)
    pushq %rbp
    vsqrtpd %ymm0, %ymm0
    vpxor %xmm2, %xmm2, %xmm2
    vpcmpeqq %ymm1, %ymm2, %ymm2
    movq %rsp, %rbp
    andq $-32, %rsp
    vblendvpd %ymm2, -32(%rsp), %ymm0, %ymm0
    leave
    ret
ASM_END(_ZGVdM4v_tmpl_Double_Sqrt)
