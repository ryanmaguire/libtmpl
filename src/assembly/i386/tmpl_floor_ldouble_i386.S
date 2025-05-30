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
 *                             tmpl_floor_ldouble                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the floor function for long doubles.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Floor                                                    *
 *  Purpose:                                                                  *
 *      Computes y = floor(x), the largest integer less than or equal to x.   *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (long double):                                                *
 *          The floor of x at long double precision.                          *
 *  Called Functions:                                                         *
 *      frndint                                                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       December 15, 2022                                             *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_i386_asm.h"

ASM_BEGIN(tmpl_LDouble_Floor)
    subl    $4, %esp
    fnstcw  2(%esp)
    fldt    8(%esp)
    movzwl  2(%esp), %eax
    andb    $-13, %ah
    orb     $4, %ah
    movw    %ax, (%esp)
    fldcw   (%esp)
    frndint
    fldcw   2(%esp)
    addl    $4, %esp
    ret
ASM_END(tmpl_LDouble_Floor)
