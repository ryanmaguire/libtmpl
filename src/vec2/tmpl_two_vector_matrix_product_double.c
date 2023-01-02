/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                       tmpl_two_vector_matrix_product                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Multiply a tmpl_TwoVectorDouble by a tmpl_TwoByTwoMatrixDouble.       *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for multiplying a 2-vector by a 2x2 matrix.                      */
tmpl_TwoVectorDouble
tmpl_2DDouble_Matrix_Product(const tmpl_TwoByTwoMatrixDouble *A,
                             const tmpl_TwoVectorDouble *P)
{
    tmpl_TwoVector out;

    out.dat[0] = A->dat[0][0]*P->dat[0] + A->dat[0][1]*P->dat[1];
    out.dat[1] = A->dat[1][0]*P->dat[0] + A->dat[1][1]*P->dat[1];

    return out;
}
/*  End of tmpl_2DDouble_Matrix_Product.                                      */

