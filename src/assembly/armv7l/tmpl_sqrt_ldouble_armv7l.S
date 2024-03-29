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
 *                             tmpl_sqrt_ldouble                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at long double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Sqrt                                                     *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (long double):                                                 *
 *          The square root of x at long double precision.                    *
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
.global tmpl_LDouble_Sqrt
.arch armv7-a
.syntax unified
.thumb
.thumb_func
.fpu vfpv3-d16
.type   tmpl_LDouble_Sqrt, %function

tmpl_LDouble_Sqrt:
        vcmp.f64    d0, #0
        vmov.f64    d7, d0
        vmrs        APSR_nzcv, FPSCR
        vsqrt.f64   d0, d7
        bx          lr

.size   tmpl_LDouble_Sqrt, .-tmpl_LDouble_Sqrt

#if defined(__ELF__)
.section        .note.GNU-stack,"",%progbits
#endif
