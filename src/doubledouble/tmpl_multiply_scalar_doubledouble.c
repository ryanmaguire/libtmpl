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
 ******************************************************************************/
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_two_sum.h>
#include <libtmpl/include/tmpl_two_prod.h>
#include <libtmpl/include/tmpl_doubledouble.h>

TMPL_PURE_FUNC
TMPL_ALWAYS_INLINE
tmpl_DoubleDouble
tmpl_DoubleDouble_Multiply_Scalar(const double x,
                                  const tmpl_DoubleDouble * const y)
TMPL_UNSEQUENCED
{
    tmpl_DoubleDouble prod;
    double prod_hi, prod_mid, prod_lo;
    double sum_hi, sum_mid, sum_lo;

    tmpl_Double_Two_Prod(x, y->dat[0], &prod_hi, &prod_mid);
    prod_lo = x * y->dat[1];
    tmpl_Double_Fast_Two_Sum(prod_hi, prod_lo, &sum_hi, &sum_mid);
    sum_lo = sum_mid + prod_mid;
    tmpl_Double_Fast_Two_Sum(sum_hi, sum_lo, &prod.dat[0], &prod.dat[1]);
    return prod;
}
