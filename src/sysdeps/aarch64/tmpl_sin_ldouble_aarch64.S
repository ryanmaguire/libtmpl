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
.section __TEXT,__text,regular,pure_instructions
.globl   _tmpl_LDouble_Sin
.p2align 2

_tmpl_LDouble_Sin:
    b    _sinl

#else
/*  Else of #ifdef __APPLE__.                                                 */

/*  The following works with GCC and LLVM's clang on GNU/Linux platforms. Not *
 *  tested on anything else.                                                  */
.text
.align  2
.global tmpl_LDouble_Sin
.type   tmpl_LDouble_Sin, %function

tmpl_LDouble_Sin:
    b    sinl

.size   tmpl_LDouble_Sin, .-tmpl_LDouble_Sin

#endif
/*  End of #ifdef __APPLE__.                                                  */

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
/*  End of #if defined(__ELF__).                                              */
