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
 *  Date:   2021/07/29                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_number_theory.h>

#define CREATE_GCD_FUNC(type, name)                                            \
type tmpl_##name##_GCD(type m, type n)                                         \
{                                                                              \
    unsigned int m_zeros, n_zeros;                                             \
    type tmp;                                                                  \
                                                                               \
    if (m == 0U)                                                               \
        return n;                                                              \
    else if (n == 0U)                                                          \
        return m;                                                              \
                                                                               \
    m_zeros = tmpl_##name##_Trailing_Zeros(m);                                 \
    n_zeros = tmpl_##name##_Trailing_Zeros(n);                                 \
                                                                               \
    m = m >> m_zeros;                                                          \
    n = n >> n_zeros;                                                          \
                                                                               \
    while (m != n)                                                             \
    {                                                                          \
        if (n > m)                                                             \
        {                                                                      \
            tmp = m;                                                           \
            m = n;                                                             \
            n = tmp;                                                           \
        }                                                                      \
                                                                               \
        m -= n;                                                                \
        tmpl_##name##_Remove_Trailing_Zeros(&m);                               \
    }                                                                          \
    m = m << (m_zeros < n_zeros ? m_zeros : n_zeros);                          \
    return m;                                                                  \
}

CREATE_GCD_FUNC(unsigned int, UInt)
CREATE_GCD_FUNC(unsigned long int, ULong)
