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
 *                        tmpl_two_by_two_scale_float                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply a 2x2 matrix by a real number.                               *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the 2x2 matrix struct by address, rather than value. *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for multiplying a 2x2 matrix by a real number.                   */
tmpl_TwoByTwoMatrixFloat
tmpl_2x2Float_Scale(float r, const tmpl_TwoByTwoMatrixFloat *A)
{
    tmpl_TwoByTwoMatrixFloat rA;

    rA.dat[0][0] = r*A->dat[0][0];
    rA.dat[0][1] = r*A->dat[0][1];
    rA.dat[1][0] = r*A->dat[1][0];
    rA.dat[1][1] = r*A->dat[1][1];
    return rA;
}
/*  End of tmpl_2x2Float_Scale.                                               */
