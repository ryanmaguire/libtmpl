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
 *      roundsd:                                                              *
 *          Rounds a double-precision floating-point number in the requested  *
 *          rounding mode.                                                    *
 *  Method:                                                                   *
 *      The roundsd instruction with 1 passed to it computes floor(x).        *
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

/*  Double-precision floor function for x86_64 machines.                      */
ASM_BEGIN(tmpl_Double_Floor)

    /*  roundsd rounds a double-precision floating-point number to the        *
     *  requested rounding mode. Rounding mode "1" is round towards negative  *
     *  infinity, which is equivalent to computing the floor of the input.    */
    roundsd $1, %xmm0, %xmm0

    /*  We have now set x = floor(x). Return back to the caller.              */
    ret

ASM_END(tmpl_Double_Floor)
