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
 *                            tmpl_truncate_float                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for truncating (rounding to zero) a float.              *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Truncate                                                   *
 *  Purpose:                                                                  *
 *      Computes the truncation of the input.                                 *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (float):                                                      *
 *          The truncation of x at single precision.                          *
 *  Called Functions:                                                         *
 *      roundsd:                                                              *
 *          Rounds a float to the indicated rounding mode.                    *
 *  Method:                                                                   *
 *      Compute trunc(x) using roundss with the proper rounding mode.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

ASM_BEGIN(tmpl_Float_Truncate)
    roundss $3, %xmm0, %xmm0    /*  xmm0 = trunc(xmm0)  */
    ret                         /*  return xmm0.        */
ASM_END(tmpl_Float_Truncate)
