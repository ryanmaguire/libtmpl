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

/*  Helper macros for PowerPC assembly found here.                            */
#include "tmpl_ppc64le_asm.h"

ASM_BEGIN(tmpl_UChar_Trailing_Zeros)
    addi    4,3,-1
    cmplwi  3,0
    andc    4,4,3
    popcntw 4,4
    iseleq  3,0,4
    clrldi  3,3,32
    blr
ASM_END(tmpl_UChar_Trailing_Zeros)
