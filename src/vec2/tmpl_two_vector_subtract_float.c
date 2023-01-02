/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
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
 *                          tmpl_two_vector_subtract                          *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide the main tools for working with vectors, both two and three   *
 *      dimensional. The typedef's are provided in kissvg.h.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 3, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2020/09/20: Ryan Maguire                                                  *
 *      Created file (KissVG).                                                *
 *  2021/03/03: Ryan Maguire                                                  *
 *      Edited file for use in libtmpl.                                       *
 ******************************************************************************/

#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing vector subtraction.                                */
tmpl_TwoVectorFloat
tmpl_2DFloat_Subtract(const tmpl_TwoVectorFloat *P,
                      const tmpl_TwoVectorFloat *Q)
{
    tmpl_TwoVectorFloat diff;

    diff.dat[0] = P->dat[0] - Q->dat[0];
    diff.dat[1] = P->dat[1] - Q->dat[1];

    return diff;
}
