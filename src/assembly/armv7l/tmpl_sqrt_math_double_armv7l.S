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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
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

ASM_BEGIN(tmpl_Double_Sqrt)
    vcmp.f64   d0, #0
    vmov.f64   d7, d0
    vmrs       APSR_nzcv, FPSCR
    vsqrt.f64  d0, d7
    bx         lr
ASM_END(tmpl_Double_Sqrt)
