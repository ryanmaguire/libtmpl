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
 *                              tmpl_sqrt_ldouble                             *
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
 *      fsqrt                                                                 *
 *  Method:                                                                   *
 *      For s390x machines sqrt is a built-in function.                       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 2, 2026                                                  *
 ******************************************************************************/

/*  Helper macros for s390x assembly found here.                              */
#include "tmpl_s390x_asm.h"

ASM_BEGIN(tmpl_LDouble_Sqrt)

#ifdef __LONG_DOUBLE_VX__
    vl %v0, 0(%r3), 3
    wfsqxb %v2, %v0
    vst %v2, 0(%r2), 3
#else
    ld %f0, 0(%r3)
    ld %f2, 8(%r3)
    sqxbr %f0, %f0
    std %f0, 0(%r2)
    std %f2, 8(%r2)
#endif

    br %r14

ASM_END(tmpl_LDouble_Sqrt)
