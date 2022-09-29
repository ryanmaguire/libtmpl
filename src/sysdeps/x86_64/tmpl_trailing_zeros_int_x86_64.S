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

/*  Clang on intel-based Apple computers supports the following.              */
#if defined(__APPLE__)

.globl _tmpl_Int_Trailing_Zeros
.align 4,0x90;

_tmpl_Int_Trailing_Zeros:
        xorl        %ecx, %ecx
        movl        %edi, %eax
        rep bsfl    %edi, %ecx
        testl       %edi, %edi
        cmovne      %ecx, %eax
        ret

/*  GCC, clang, and PCC support the following on GNU/Linux and FreeBSD.       */
#else

.text
.p2align 4
.globl  tmpl_Int_Trailing_Zeros
.type   tmpl_Int_Trailing_Zeros, @function

tmpl_Int_Trailing_Zeros:
        xorl        %ecx, %ecx
        movl        %edi, %eax
        rep bsfl    %edi, %ecx
        testl       %edi, %edi
        cmovne      %ecx, %eax
        ret

.size   tmpl_Int_Trailing_Zeros, .-tmpl_Int_Trailing_Zeros

#endif
/*  End of #if defined(__APPLE__).                                            */

#if defined(__ELF__)
.section        .note.GNU-stack,"",@progbits
#endif
