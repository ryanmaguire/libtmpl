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
 *                         tmpl_two_by_two_new_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Creates a 2x2 matrix from 4 doubles.                                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 28, 2020                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files.              *
 ******************************************************************************/

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Function for creating a new 2x2 matrix.                                   */
tmpl_TwoByTwoMatrixLongDouble
tmpl_2x2LDouble_New(long double a, long double b, long double c, long double d)
{
    tmpl_TwoByTwoMatrixLongDouble A;

    A.dat[0][0] = a;
    A.dat[0][1] = b;
    A.dat[1][0] = c;
    A.dat[1][1] = d;

    return A;
}
/*  End of tmpl_2x2LDouble_New.                                               */
