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
 *                              tmpl_trunc_float                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computing the truncation of a float (round-to-zero).                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Truncate                                                   *
 *  Purpose:                                                                  *
 *      Computes y = trunc(x), which is round-to-zero of the input.           *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      trunc_x (float):                                                      *
 *          The truncation of x at single precision.                          *
 *  Called Functions:                                                         *
 *      friz                                                                  *
 *  Method:                                                                   *
 *      The friz instruction computes trunc(x).                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 11, 2024                                             *
 ******************************************************************************/

/*  Helper macros for PowerPC assembly found here.                            */
#include "tmpl_ppc64le_asm.h"

ASM_BEGIN(tmpl_Float_Truncate)
    friz 1, 1
    blr
ASM_END(tmpl_Float_Truncate)
