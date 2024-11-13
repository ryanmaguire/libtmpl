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
 ******************************************************************************
 *                              tmpl_floor_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the floor function at double precision.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Floor                                                     *
 *  Purpose:                                                                  *
 *      Computes y = floor(x), the largest integer less than or equal to x.   *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (double):                                                     *
 *          The floor of x at double precision.                               *
 *  Called Functions:                                                         *
 *      frintm                                                                *
 *  Method:                                                                   *
 *      Use frintm on the argument.                                           *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 11, 2022                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_aarch64_asm.h"

#ifdef __APPLE__
.section __TEXT, __text, regular, pure_instructions
.globl tmpl_Double_Floor
.p2align ALIGN
#endif

ASM_BEGIN(tmpl_Double_Floor)

    /*  frintm is Round-to-Minus-Infinity (floor function).                   */
    frintm d0, d0
    ret

ASM_END(tmpl_Double_Floor)
