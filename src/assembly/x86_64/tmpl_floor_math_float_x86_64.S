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
 *                              tmpl_floor_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the floor function at single precision.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Floor                                                      *
 *  Purpose:                                                                  *
 *      Computes y = floor(x), the largest integer less than or equal to x.   *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      floor_x (float):                                                      *
 *          The floor of x at single precision.                               *
 *  Called Functions:                                                         *
 *      roundss:                                                              *
 *          Rounds a single-precision floating-point number in the requested  *
 *          rounding mode.                                                    *
 *  Method:                                                                   *
 *      The roundss instruction with 1 passed to it computes floor(x).        *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_x86_64_asm.h:                                                    *
 *          Provides x86_64 / amd64 helper macros to improve portability.     *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 5, 2022                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2026/05/21: Ryan Maguire                                                  *
 *      Added comments, updated docstring.                                    *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

/*  Single-precision floor function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Float_Floor)

    /*  roundsd rounds a single-precision floating-point number to the        *
     *  requested rounding mode. Rounding mode "1" is round towards negative  *
     *  infinity, which is equivalent to computing the floor of the input.    */
    roundss $1, %xmm0, %xmm0

    /*  We have now set x = floor(x). Return back to the caller.              */
    ret

ASM_END(tmpl_Float_Floor)
