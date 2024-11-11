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
 *                            tmpl_truncate_double                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for truncating (rounding to zero) a double.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Truncate                                                  *
 *  Purpose:                                                                  *
 *      Computes the truncation of the input.                                 *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (double):                                                     *
 *          The truncation of x at double precision.                          *
 *  Called Functions:                                                         *
 *      roundsd:                                                              *
 *          Rounds a double to the indicated rounding mode.                   *
 *  Method:                                                                   *
 *      Compute trunc(x) using roundsd with the proper rounding mode.         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 9, 2024                                              *
 ******************************************************************************/

/*  Helper macros found here.                                                 */
#include "tmpl_x86_64_asm.h"

ASM_BEGIN(tmpl_Double_Truncate)
    roundsd $3, %xmm0, %xmm0    /*  xmm0 = trunc(xmm0)  */
    ret                         /*  return xmm0.        */
ASM_END(tmpl_Double_Truncate)
