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

unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n)
{
    unsigned int m_zeros, n_zeros, k;

    if (m == 0U)
        return n;
    else if (n == 0U)
        return m;

    m_zeros = tmpl_UInt_Trailing_Zeros(m);
    n_zeros = tmpl_UInt_Trailing_Zeros(n);

    m = m >> m_zeros;
    n = n >> n_zeros;

    if (m_zeros < n_zeros)
        k = m_zeros;
    else
        k = n_zeros;

    while (1)
    {
        if (m > n)
        {
            m -= n;
            if (m == 0)
                return n << k;

            m >>= tmpl_UInt_Trailing_Zeros(m);
        }
        else
        {
            n -= m;
            if (n == 0)
                return m << k;

            n >>= tmpl_UInt_Trailing_Zeros(n);
        }
    }
}

