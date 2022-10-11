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

/*  The following works with GCC and LLVM's clang on GNU/Linux platforms. Not *
 *  tested on anything else.                                                  */
#else
.text
.align  2
.global tmpl_Float_SinCos
.type   tmpl_Float_SinCos, %function

tmpl_Float_SinCos:
        stp     x29, x30, [sp, -48]!
        mov     x29, sp
        stp     x19, x20, [sp, 16]
        mov     x20, x0
        mov     x19, x1
        add     x0, sp, 44
        add     x1, sp, 40
        bl      sincosf
        ldp     s0, s1, [sp, 40]
        str     s1, [x20]
        str     s0, [x19]
        ldp     x19, x20, [sp, 16]
        ldp     x29, x30, [sp], 48
        ret

.size   tmpl_Float_SinCos, .-tmpl_Float_SinCos

#endif
/*  End of #ifdef __APPLE__.                                                  */

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
/*  End of #if defined(__ELF__).                                              */
