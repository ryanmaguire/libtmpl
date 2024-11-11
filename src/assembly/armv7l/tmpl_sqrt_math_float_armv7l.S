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
 *      For armv7l (armhf) machines sqrt is a built-in function.              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 3, 2022                                                   *
 ******************************************************************************/

/*  Helper macros for armv7 assembly found here.                              */
#include "tmpl_armv7l_asm.h"

ASM_BEGIN(tmpl_Float_Sqrt)
        vcmp.f32   s0, #0
        vmov.f32   s15, s0
        vmrs       APSR_nzcv, FPSCR
        vsqrt.f32  s0, s15
        bx         lr
ASM_END(tmpl_Float_Sqrt)
