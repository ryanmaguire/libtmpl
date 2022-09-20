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

#include <libtmpl/include/tmpl_number_theory.h>

/*  The assembly code for tmpl_ULong_Trailing_Zeros uses the same code as     *
 *  __builtin_ctzl on systems using GCC or Clang. However, __builtin_ctzl can *
 *  be inlined by the compiler resulting in about a 2x improvement with that  *
 *  function. Check if your compiler supports this first.                     */
#if defined(__has_builtin)

/*  GCC and Clang both support __builtin_ctzl.                                */
#if __has_builtin(__builtin_ctzl)
#define trailing_zeros __builtin_ctzl
#else

/*  Lacking this, fall back to libtmpl's function.                            */
#define trailing_zeros tmpl_ULong_Trailing_Zeros

#endif
/*  End of #if __has_builtin(__builtin_ctzl).                                 */

#elif defined(_MSC_VER)
/*  Else for #if defined(__has_builtin).                                      */

/*  Microsoft's compiler has _BitScanForward, which does the same thing.      */
unsigned long int __inline trailing_zeros(unsigned long int n)
{
    unsigned long int trailing_zeros = 0U;
    _BitScanForward(&trailing_zeros, n);
    return trailing_zeros;
}

#else
/*  Else for #if defined(__has_builtin).                                      */

/*  Lacking any built-in support, use libtmpl's function.                     */
#define trailing_zeros tmpl_ULong_Trailing_Zeros

#endif
/*  End of #if defined(__has_builtin).                                        */

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

    m_zeros = trailing_zeros(m);
    n_zeros = trailing_zeros(n);

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
        m >>= trailing_zeros(m);
    }
    m = m << (m_zeros < n_zeros ? m_zeros : n_zeros);
    return m;
}
/*  End of tmpl_ULong_GCD.                                                    */

#undef trailing_zeros
