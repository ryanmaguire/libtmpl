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
 *                         tmpl_fractional_part_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computing the fractional part of a double.                            *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Fractional_Part                                           *
 *  Purpose:                                                                  *
 *      Computes the fractional part of the input.                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      frac_x (double):                                                      *
 *          The fractional part of x at double precision.                     *
 *  Called Functions:                                                         *
 *      friz                                                                  *
 *      fsub                                                                  *
 *  Method:                                                                   *
 *      Compute x - trunc(x).                                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 11, 2024                                             *
 ******************************************************************************/

/*  Helper macros for PowerPC assembly found here.                            */
#include "tmpl_ppc64le_asm.h"

ASM_BEGIN(tmpl_Double_Fractional_Part)
    friz 0, 1
    fsub 1, 1, 0
    blr
ASM_END(tmpl_Double_Fractional_Part)
