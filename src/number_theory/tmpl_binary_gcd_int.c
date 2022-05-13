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

int tmpl_Int_GCD(int m, int n)
{
    int m_zeros, n_zeros, tmp;

    if (m == 0)
        return n;
    else if (n == 0)
        return m;

    if (m < 0)
        m = -m;

    if (n < 0)
        n = -n;

    m_zeros = tmpl_Int_Trailing_Zeros(m);
    n_zeros = tmpl_Int_Trailing_Zeros(n);

    m = m >> m_zeros;
    n = n >> n_zeros;

    m = m >> m_zeros;
    n = n >> n_zeros;

    while (m != n)
    {
        if (n > m)
        {
            tmp = m;
            m = n;
            n = tmp;
        }

        m -= n;
        m >>= tmpl_Int_Trailing_Zeros(m);
    }
    m = m << (m_zeros < n_zeros ? m_zeros : n_zeros);
    return m;
}

