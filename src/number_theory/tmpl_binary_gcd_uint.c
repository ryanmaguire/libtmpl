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

/*  The assembly code for tmpl_UInt_Trailing_Zeros uses the same code as      *
 *  __builtin_ctz on systems using GCC or Clang. However, __builtin_ctz can   *
 *  be inlined by the compiler resulting in about a 2x improvement with that  *
 *  function. Check if your compiler supports this first.                     */
#if defined(__has_builtin)

/*  GCC and Clang both support __builtin_ctz.                                 */
#if __has_builtin(__builtin_ctz)
#define trailing_zeros __builtin_ctz
#else

/*  Lacking this, fall back to libtmpl's function.                            */
#define trailing_zeros tmpl_UInt_Trailing_Zeros

#endif
/*  End of #if __has_builtin(__builtin_ctz).                                  */

#elif defined(_MSC_VER)
/*  Else for #if defined(__has_builtin).                                      */

/*  Microsoft's compiler has _BitScanForward, which does the same thing.      */
unsigned int __inline trailing_zeros(unsigned int n)
{
    unsigned int trailing_zeros = 0U;
    _BitScanForward(&trailing_zeros, n);
    return trailing_zeros;
}

#else
/*  Else for #if defined(__has_builtin).                                      */

/*  Lacking any built-in support, use libtmpl's function.                     */
#define trailing_zeros tmpl_UInt_Trailing_Zeros

#endif
/*  End of #if defined(__has_builtin).                                        */

/*  Make sure all of these macros are available. They should be.              */
#ifdef TMPL_BINARY_GCD_ALGORITHM
#undef TMPL_BINARY_GCD_ALGORITHM
#endif

#ifdef TMPL_MIXED_BINARY_GCD_ALGORITHM
#undef TMPL_MIXED_BINARY_GCD_ALGORITHM
#endif

#ifdef TMPL_EUCLIDEAN_GCD_ALGORITHM
#undef TMPL_EUCLIDEAN_GCD_ALGORITHM
#endif

#ifdef TMPL_STANDARD_GCD_ALGORITHM
#undef TMPL_STANDARD_GCD_ALGORITHM
#endif

/*  You may choose which algorithm to implement. There are four available,    *
 *  the binary GCD, mixed binary GCD, Euclidean GCD, and standard GCD. The    *
 *  binary GCD has the best performance and is the default. The Euclidean     *
 *  GCD has the second best performance, followed by mixed binary GCD. Do not *
 *  use the standard GCD algorithm. It is very slow. The mixed binary GCD     *
 *  is supposed to have better performance for smaller inputs. The tests that *
 *  were run chose random inputs, not just small ones.                        */
#define TMPL_BINARY_GCD_ALGORITHM 1
#define TMPL_MIXED_BINARY_GCD_ALGORITHM 0
#define TMPL_EUCLIDEAN_GCD_ALGORITHM 0
#define TMPL_STANDARD_GCD_ALGORITHM 0

/*  Implementation of the Binary GCD algorithm.                               */
#if TMPL_BINARY_GCD_ALGORITHM == 1

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    int m_zeros, n_zeros;
    unsigned int tmp;

    /*  Special cases. GCD(m, 0) = m and GCD(0, n) = n. Use this.             */
    if (m == 0U)
        return n;
    else if (n == 0U)
        return m;

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  */
    m_zeros = trailing_zeros(m);
    n_zeros = trailing_zeros(n);
    m = m >> m_zeros;
    n = n >> n_zeros;

    /*  Keep reducing the arguments until we have n = m. GCD(n, n) = n, and   *
     *  our computation will be almost complete.                              */
    while (m != n)
    {
        /*  Swap the variables so that m is larger, if necessary.             */
        if (n > m)
        {
            tmp = m;
            m = n;
            n = tmp;
        }

        /*  Next eduction step in the GCD algorithm. Use the fact that, for   *
         *  odd inputs m and n, GCD(m, n) = GCD(m - n, min(m, n)). Since we   *
         *  have removed all trailing zeros from m and n, both are odd.       */
        m -= n;

        /*  Remove all trailing zeros from m, ensuring m is odd. Since m != n *
         *  we are guaranteed the m - n is positive, meaning __builtin_ctz    *
         *  will not cause undefined behavior if it is being used.            */
        m >>= trailing_zeros(m);
    }

    /*  If a < b, we have GCD(2^a m, 2^b n) = 2^a GCD(m, 2^{b-a} n). We have  *
     *  just computed GCD(m, 2^{b-a} n). We now need to multiply by 2^a. Here *
     *  we have a is the number of trailing zeros in the input m, and b is    *
     *  the number of trailing zeros in the input n. We've saved both of      *
     *  these values as m_zeros and n_zeros, respectively. Compute the        *
     *  minimum of these two and then bit-shift m to the left by this min.    *
     *  This is the equivalent of multiply m by 2^min(m_zeros, n_zeros).      */
    return m << (m_zeros < n_zeros ? m_zeros : n_zeros);
}
/*  End of tmpl_UInt_GCD.                                                     */

/*  Implementation of the Mixed-Binary GCD algorithm.                         */
#elif TMPL_MIXED_BINARY_GCD_ALGORITHM == 1

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n)
{
    int m_zeros, n_zeros, shift;
    unsigned int tmp;

    if (m == 0U)
        return n;
    if (n == 0U)
        return m;

    if (m < n)
    {
        tmp = m;
        m = n;
        n = tmp;
    }

    m_zeros = trailing_zeros(m);
    n_zeros = trailing_zeros(n);
    m = m >> m_zeros;
    n = n >> n_zeros;
    shift = (m_zeros < n_zeros ? m_zeros : n_zeros);

    while (1U < n)
    {
        m %= n;
        n -= m;

        if (m == 0U)
            return n << shift;
        if (n == 0U)
            return m << shift;

        m = m >> trailing_zeros(m);
        n = n >> trailing_zeros(n);

        if (m < n)
        {
            tmp = m;
            m = n;
            n = tmp;
        }
    }
    return (n == 1U ? n : m) << shift;
}
/*  End of tmpl_UInt_GCD.                                                     */

/*  Implementation of the Euclidean GCD algorithm.                            */
#elif TMPL_EUCLIDEAN_GCD_ALGORITHM == 1

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n)
{
    unsigned int tmp;
    while(n != 0)
    {
        m %= n;
        tmp = m;
        m = n;
        n = tmp;

    }
    return m;
}
/*  End of tmpl_UInt_GCD.                                                     */

/*  Implementation of the Standard "by-hand" GCD algorithm.                   */
#else

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD(unsigned int m, unsigned int n)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (m == 0U)
        return n;
    else if (n == 0U)
        return m;

    while(m != n)
    {
        if(m > n)
            m -= n;
        else
            n -= m;
    }
    return m;
}
/*  End of tmpl_UInt_GCD.                                                     */

#endif
/*  End of #if TMPL_BINARY_GCD_ALGORITHM == 1.                                */

/*  #undef all of the macros in case someone wants to #include this file.     */
#undef TMPL_BINARY_GCD_ALGORITHM
#undef TMPL_MIXED_BINARY_GCD_ALGORITHM
#undef TMPL_EUCLIDEAN_GCD_ALGORITHM
#undef TMPL_STANDARD_GCD_ALGORITHM
