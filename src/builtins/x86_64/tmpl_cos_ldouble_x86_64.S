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
#if defined(__APPLE__)
.globl    _tmpl_LDouble_Cos
.p2align  4, 0x90

_tmpl_LDouble_Cos:
    jmp    cosl@PLT

#else
.text
.p2align 4
.globl  tmpl_LDouble_Cos
.type   tmpl_LDouble_Cos, @function

tmpl_LDouble_Cos:
    jmp    cosl@PLT

.size   tmpl_LDouble_Cos, .-tmpl_LDouble_Cos
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
