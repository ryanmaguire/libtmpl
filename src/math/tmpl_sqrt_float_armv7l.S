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
 *                              tmpl_sqrt_float                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at single precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Sqrt                                                       *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (float):                                                       *
 *          The square root of x at single precision.                         *
 *  Called Functions:                                                         *
 *      vsqrt                                                                 *
 *  Method:                                                                   *
 *      For armv7l (armel/armhf) machines sqrt is a built-in function.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 3, 2022                                                   *
 ******************************************************************************/

.arch armv7-a
.eabi_attribute 28, 1
.eabi_attribute 20, 1
.eabi_attribute 21, 1
.eabi_attribute 23, 3
.eabi_attribute 24, 1
.eabi_attribute 25, 1
.eabi_attribute 26, 2
.eabi_attribute 30, 2
.eabi_attribute 34, 1
.eabi_attribute 18, 4
.text
.align  1
.p2align 2,,3
.global tmpl_Float_Sqrt
.arch armv7-a
.syntax unified
.thumb
.thumb_func
.fpu vfpv3-d16
.type   tmpl_Float_Sqrt, %function

tmpl_Float_Sqrt:
        vcmp.f32    s0, #0
        vmov.f32    s15, s0
        vmrs        APSR_nzcv, FPSCR
        vsqrt.f32   s0, s15
        bx          lr

.size   tmpl_Float_Sqrt, .-tmpl_Float_Sqrt

#if defined(__ELF__)
.section        .note.GNU-stack,"",%progbits
#endif
