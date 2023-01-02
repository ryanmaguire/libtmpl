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
 *                      tmpl_two_vector_midpoint_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the midpoint of two vectors.                                 *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 29, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Also changed *
 *      function to pass the vector struct by address, rather than value.     *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for computing the midpoint of 2 two dimensional vectors.         */
tmpl_TwoVectorLongDouble
tmpl_2DLDouble_Midpoint(const tmpl_TwoVectorLongDouble *P,
                        const tmpl_TwoVectorLongDouble *Q)
{
    tmpl_TwoVectorLongDouble mid;

    mid.dat[0] = 0.5L*(P->dat[0] + Q->dat[0]);
    mid.dat[1] = 0.5L*(P->dat[1] + Q->dat[1]);

    return mid;
}
/*  End of tmpl_2DLDouble_Midpoint.                                           */
