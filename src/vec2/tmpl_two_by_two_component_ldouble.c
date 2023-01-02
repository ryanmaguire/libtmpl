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
 *                     tmpl_two_by_two_component_ldouble                      *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Returns the (m, n) component of a 2x2 matrix.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 03, 2021                                                *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/12/30: Ryan Maguire                                                  *
 *      Moved float and long double versions to their own files. Changed      *
 *      behavior of function. Instead of returning NaN for invalid entries    *
 *      it computes the indices mod two. Also changed function to pass the    *
 *      2x2 matrix struct by address, rather than value.                      *
 ******************************************************************************/

/*  size_t is here.                                                           */
#include <stddef.h>

/*  Function prototype and two-vector typedef found here.                     */
#include <libtmpl/include/tmpl_vec2.h>

/*  Returns the (m, n) component of a 2x2 matrix.                             */
long double
tmpl_2x2LDouble_Component(const tmpl_TwoByTwoMatrixLongDouble *A,
                          size_t m, size_t n)
{
    /*  The former code returned NAN for out of bound indices. Instead we     *
     *  simply cyclicly wrap the indices around and compute mod 2.            */
    const size_t one = (size_t)1;
    return A->dat[m & one][n & one];
}
/*  End of tmpl_2x2LDouble_Component.                                         */
