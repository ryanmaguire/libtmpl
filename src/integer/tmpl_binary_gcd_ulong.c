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
 *  Computes the GCD of two non-negative integers.                            *
 ******************************************************************************
 *  Author: Ryan Maguire                                                      *
 *  Date:   2022/05/12                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_integer.h>

/*  Binary GCD Algorithm for unsigned integers.                               */
unsigned long int tmpl_ULong_GCD(unsigned long int m, unsigned long int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    int m_zeros, n_zeros;
    unsigned long int tmp;

    if (m == 0U)
        return n;
    else if (n == 0U)
        return m;

    m_zeros = TMPL_ULONG_TRAILING_ZEROS(m);
    n_zeros = TMPL_ULONG_TRAILING_ZEROS(n);

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
        m >>= TMPL_ULONG_TRAILING_ZEROS(m);
    }
    m = m << (m_zeros < n_zeros ? m_zeros : n_zeros);
    return m;
}
/*  End of tmpl_ULong_GCD.                                                    */
