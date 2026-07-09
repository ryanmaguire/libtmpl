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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 29, 2024                                             *
 ******************************************************************************/

/*  TMPL_INLINE_DECL macro found here, as is TMPL_USE_INLINE.                 */
#include <libtmpl/include/tmpl_config.h>

/*  tmpl_DoubleDouble typedef provided here.                                  */
#include <libtmpl/include/tmpl_doubledouble.h>

/*  2Sum and Fast2Sum are needed for double-double addition.                  */
#include <libtmpl/include/tmpl_two_sum.h>

TMPL_ALWAYS_INLINE
tmpl_DoubleDouble
tmpl_DoubleDouble_Create(double x, double y)
{
    tmpl_DoubleDouble out;
    tmpl_Double_Two_Sum(x, y, &out.dat[0], &out.dat[1]);
    return out;
}
