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
 *  Date:       May 13, 2024                                                  *
 ******************************************************************************/
#include <libtmpl/include/tmpl_math.h>

#define PEAK (sizeof(tmpl_ldouble_factorial_table) / sizeof(long double))

long double tmpl_LDouble_Falling_Factorial(unsigned int x, unsigned int N)
{
    unsigned int n;
    long double y, out;

    if (N < 3U)
    {
        switch (N)
        {
            case 0:
                return 1.0L;
            case 1:
                return (long double)x;
            default:
                y = (long double)x;
                return y * (y - 1.0L);
        }
    }

    if (N > x)
        return 0.0;

    if (N == x)
        return tmpl_LDouble_Factorial(x);

    if (x <= PEAK)
        return tmpl_LDouble_Factorial(x) / tmpl_LDouble_Factorial(x - N);

    out = (long double)x;
    y = (long double)((x - N) + 1U);

    for (n = 1U; n < N; ++n)
    {
        out *= y;
        y += 1.0L;
    }

    return out;
}

#undef PEAK
