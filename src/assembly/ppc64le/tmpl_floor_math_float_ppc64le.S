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
 *      frim                                                                  *
 *  Method:                                                                   *
 *      The frim instruction computes floor(x).                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 16, 2024                                               *
 ******************************************************************************/

/*  Helper macros for PowerPC assembly found here.                            */
#include "tmpl_ppc64le_asm.h"

ASM_BEGIN(tmpl_Float_Floor)
    frim 1, 1
    blr
ASM_END(tmpl_Float_Floor)
