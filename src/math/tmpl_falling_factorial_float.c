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

#define PEAK (sizeof(tmpl_float_factorial_table) / sizeof(float))

float tmpl_Float_Falling_Factorial(unsigned int x, unsigned int N)
{
    unsigned int n;
    float y, out;

    if (N < 3U)
    {
        switch (N)
        {
            case 0:
                return 1.0F;
            case 1:
                return (float)x;
            default:
                y = (float)x;
                return y * (y - 1.0F);
        }
    }

    if (N > x)
        return 0.0F;

    if (N == x)
        return tmpl_Float_Factorial(x);

    if (x <= PEAK)
        return tmpl_Float_Factorial(x) / tmpl_Float_Factorial(x - N);

    out = (float)x;
    y = (float)((x - N) + 1U);

    for (n = 1U; n < N; ++n)
    {
        out *= y;
        y += 1.0F;
    }

    return out;
}

#undef PEAK
