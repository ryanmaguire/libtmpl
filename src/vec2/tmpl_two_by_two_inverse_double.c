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
 *                     tmpl_two_by_two_inverse_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the inverse of a 2x2 matrix.                                 *
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

/*  NaN found here.                                                           */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the inverse of a 2x2 matrix.                       */
tmpl_TwoByTwoMatrixDouble
tmpl_2x2Double_Inverse(const tmpl_TwoByTwoMatrixDouble *A)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_TwoByTwoMatrixDouble InvA;

    /*  Compute the determinant.                                              */
    const double det = A->dat[0][0]*A->dat[1][1] - A->dat[1][0]*A->dat[0][1];
    const double det_rcp = 1.0 / det;

    InvA.dat[0][0] = A->dat[1][1]*det_rcp;
    InvA.dat[0][1] = -A->dat[0][1]*det_rcp;
    InvA.dat[1][0] = -A->dat[1][0]*det_rcp;
    InvA.dat[1][1] = A->dat[0][0]*det_rcp;
    return InvA;
}
/*  End of tmpl_2x2Double_Inverse.                                            */
