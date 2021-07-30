/******************************************************************************
 *                                 LICENSE                                    *
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
 *  Computes the GCD of two non-negative integers.                            *
 ******************************************************************************
 *  Author: Ryan Maguire, Dartmouth College                                   *
 *  Date:   2021/07/29                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_number_theory.h>

unsigned int tmpl_Int_GCD(int m, int n)
{
    unsigned int m_zeros, n_zeros, k;
    unsigned int abs_m, abs_n;

    if (m == 0)
        return (unsigned int)n;
    else if (n == 0)
        return (unsigned int)m;

    if (m < 0)
        abs_m = (unsigned int)(-m);
    else
        abs_m = (unsigned int)m;

    if (n < 0)
        abs_n = (unsigned int)(-n);
    else
        abs_n = (unsigned int)n;

    m_zeros = tmpl_UInt_Trailing_Zeros(abs_m);
    n_zeros = tmpl_UInt_Trailing_Zeros(abs_n);

    abs_m = abs_m >> m_zeros;
    abs_n = abs_n >> n_zeros;

    if (m_zeros < n_zeros)
        k = m_zeros;
    else
        k = n_zeros;

    while (1)
    {
        if (abs_m > abs_n)
        {
            abs_m -= abs_n;
            if (abs_m == 0)
                return abs_n << k;

            abs_m >>= tmpl_UInt_Trailing_Zeros(abs_m);
        }
        else
        {
            abs_n -= abs_m;
            if (abs_n == 0)
                return abs_m << k;

            abs_n >>= tmpl_UInt_Trailing_Zeros(abs_n);
        }
    }
}

