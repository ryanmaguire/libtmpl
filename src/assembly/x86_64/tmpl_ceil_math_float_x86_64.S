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
 *                               tmpl_ceil_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the ceiling function at single precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Ceil                                                       *
 *  Purpose:                                                                  *
 *      Computes y = ceil(x), the smallest integer greater than or equal to x.*
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      ceil_x (float):                                                       *
 *          The ceiling of x at single precision.                             *
 *  Called Functions:                                                         *
 *      roundss:                                                              *
 *          Rounds a single-precision floating-point number in the requested  *
 *          rounding mode.                                                    *
 *  Method:                                                                   *
 *      The roundss instruction with 2 passed to it computes ceil(x).         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_x86_64_asm.h:                                                    *
 *          Provides x86_64 / amd64 helper macros to improve portability.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 10, 2024                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/21: Ryan Maguire                                                  *
 *      Added comments, updated docstring.                                    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Single-precision ceiling function for x86_64 machines.                    */
ASM_BEGIN(tmpl_Float_Ceil)

    /*  roundss rounds a single-precision floating-point number to the        *
     *  requested rounding mode. Rounding mode "2" is round towards positive  *
     *  infinity, which is equivalent to computing the ceiling of the input.  */
    roundss $2, %xmm0, %xmm0

    /*  We have now set x = ceil(x). Return back to the caller.               */
    ret

ASM_END(tmpl_Float_Ceil)
