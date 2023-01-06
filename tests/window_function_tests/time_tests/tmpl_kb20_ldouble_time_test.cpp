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
#include "tmpl_window_functions_time_tests.h"

static long double func(long double x, long double W)
{
    const long double c = 2.0L*x/W;
    const long double arg = 1.0L - c*c;
    const long double alpha = 2.0L*tmpl_One_Pi_L;

    if (arg < 0.0L)
        return 0.0L;
    else
    {
        const long double numer = cyl_bessel_il(0.0L, alpha*sqrt(arg));
        const long double denom = cyl_bessel_il(0.0L, alpha);
        return numer / denom;
    }
}

TEST1(long double, -0.5L, 0.5L, tmpl_LDouble_Kaiser_Bessel_2_0, func)
