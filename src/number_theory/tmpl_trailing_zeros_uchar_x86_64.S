/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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

.text
.p2align 4
.globl  tmpl_UChar_Trailing_Zeros
.type   tmpl_UChar_Trailing_Zeros, @function

tmpl_UChar_Trailing_Zeros:
        movzbl  %dil, %eax
        rep bsfl        %eax, %eax
        ret

.size   tmpl_UChar_Trailing_Zeros, .-tmpl_UChar_Trailing_Zeros

#if defined(__ELF__)
.section        .note.GNU-stack,"",@progbits
#endif
