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

/*  The following code works with Apple's M1 chip. Tested with Apple's        *
 *  version of clang.                                                         */
#ifdef __APPLE__
.section        __TEXT,__text,regular,pure_instructions
.globl  _tmpl_LDouble_SinCos
.p2align  2

_tmpl_LDouble_SinCos:
    stp     x20, x19, [sp, #-32]!
    stp     x29, x30, [sp, #16]
    add     x29, sp, #16
    mov     x19, x1
    mov     x20, x0
    bl      ___sincos_stret
    str     d0, [x20]
    str     d1, [x19]
    ldp     x29, x30, [sp, #16]
    ldp     x20, x19, [sp], #32
    ret

/*  The following works with GCC and LLVM's clang on GNU/Linux platforms. Not *
 *  tested on anything else.                                                  */
#else
.text
.align  2
.global tmpl_LDouble_SinCos
.type   tmpl_LDouble_SinCos, %function

tmpl_LDouble_SinCos:
        stp     x29, x30, [sp, -64]!
        mov     x29, sp
        stp     x19, x20, [sp, 16]
        mov     x20, x0
        mov     x19, x1
        add     x0, sp, 48
        add     x1, sp, 32
        bl      sincosl
        ldr     q2, [sp, 48]
        ldr     q0, [sp, 32]
        str     q2, [x20]
        str     q0, [x19]
        ldp     x19, x20, [sp, 16]
        ldp     x29, x30, [sp], 64
        ret

.size   tmpl_LDouble_SinCos, .-tmpl_LDouble_SinCos

#endif
/*  End of #ifdef __APPLE__.                                                  */

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
/*  End of #if defined(__ELF__).                                              */
