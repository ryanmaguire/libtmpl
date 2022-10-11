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
.globl  _tmpl_Double_Floor
.p2align        4, 0x90

_tmpl_Double_Floor:
    roundsd $9, %xmm0, %xmm0
    ret

#else
.text;
.p2align 4,0x90;
.globl tmpl_Double_Floor;
.type tmpl_Double_Floor,@function;

tmpl_Double_Floor:
    roundsd $9, %xmm0, %xmm0
    ret

.size tmpl_Double_Floor, . - tmpl_Double_Floor
#endif

/* Enable stack protection.                                                   */
#if defined(__ELF__)
.section .note.GNU-stack,"",%progbits
#endif
