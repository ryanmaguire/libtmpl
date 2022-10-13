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
 *  Author: Ryan Maguire                                                      *
 *  Date:   2021/07/29                                                        *
 ******************************************************************************/

#include <libtmpl/include/tmpl_integer.h>
#include <stdlib.h>

/*  Make sure this macro is available. It should be.                          */
#ifdef TMPL_GCD_ALGORITHM
#undef TMPL_GCD_ALGORITHM
#endif

/*  You may choose which algorithm to implement. There are four available,    *
 *  the binary GCD, mixed binary GCD, Euclidean GCD, and standard GCD. The    *
 *  binary GCD has the best performance and is the default. The Euclidean     *
 *  GCD has the second best performance, followed by mixed binary GCD. Do not *
 *  use the standard GCD algorithm. It is very slow. The mixed binary GCD     *
 *  is supposed to have better performance for smaller inputs. The tests that *
 *  were run chose random inputs, not just small ones.                        *
 *      Binary GCD:         TMPL_GCD_ALGORITHM 1                              *
 *      Mixed Binary GCD:   TMPL_GCD_ALGORITHM 2                              *
 *      Euclidean GCD:      TMPL_GCD_ALGORITHM 3                              *
 *      By-Hand GCD:        TMPL_GCD_ALGORITHM 4                              */
#define TMPL_GCD_ALGORITHM 1

/*  Implementation of the Binary GCD algorithm.                               */
#if TMPL_GCD_ALGORITHM == 1

/*  Function for computing the GCD of two integers.                           */
long int tmpl_Long_GCD(long int m, long int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    long int m_zeros, n_zeros, tmp;

    /*  Special cases. GCD(m, 0) = m and GCD(0, n) = n. Use this.             */
    if (m == 0L)
        return n;
    else if (n == 0L)
        return m;

    /*  The GCD of negative numbers is still positive. Compute the absolute   *
     *  value of m and n and use the unsigned algorithm.                      */
    m = labs(m);
    n = labs(n);

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  */
    m_zeros = TMPL_LONG_TRAILING_ZEROS(m);
    n_zeros = TMPL_LONG_TRAILING_ZEROS(n);
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

        /*  Next reduction step in the GCD algorithm. Use the fact that, for  *
         *  odd inputs m and n, GCD(m, n) = GCD(|m - n|, min(m, n)). Since we *
         *  have removed all trailing zeros from m and n, both are odd.       */
        m -= n;

        /*  Remove all trailing zeros from m, ensuring m is odd. Since m != n *
         *  we are guaranteed the m - n is positive, meaning __builtin_ffs    *
         *  will not cause undefined behavior if it is being used.            */
        m >>= TMPL_LONG_TRAILING_ZEROS(m);
    }

    /*  If a < b, we have GCD(2^a m, 2^b n) = 2^a GCD(m, 2^{b-a} n). We have  *
     *  just computed GCD(m, 2^{b-a} n). We now need to multiply by 2^a. Here *
     *  we have a is the number of trailing zeros in the input m, and b is    *
     *  the number of trailing zeros in the input n. We've saved both of      *
     *  these values as m_zeros and n_zeros, respectively. Compute the        *
     *  minimum of these two and then bit-shift m to the left by this min.    *
     *  This is the equivalent of multiplying m by 2^min(m_zeros, n_zeros).   */
    return m << (m_zeros < n_zeros ? m_zeros : n_zeros);
}
/*  End of tmpl_Long_GCD.                                                     */

/*  Implementation of the Mixed-Binary GCD algorithm.                         */
#elif TMPL_GCD_ALGORITHM == 2

/*  Function for computing the GCD of two integers.                           */
long int tmpl_Long_GCD(long int m, long int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    long int m_zeros, n_zeros, shift, tmp;

    /*  Special cases. GCD(m, 0) = m and GCD(0, n) = n. Use this.             */
    if (m == 0L)
        return n;
    else if (n == 0L)
        return m;

    /*  The GCD of negative numbers is still positive. Compute the absolute   *
     *  value of m and n and use the unsigned algorithm.                      */
    m = abs(m);
    n = abs(n);

    /*  Swap m and n, if necessary, so that m is the larger one.              */
    if (m < n)
    {
        tmp = m;
        m = n;
        n = tmp;
    }

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  */
    m_zeros = TMPL_LONG_TRAILING_ZEROS(m);
    n_zeros = TMPL_LONG_TRAILING_ZEROS(n);
    m = m >> m_zeros;
    n = n >> n_zeros;

    /*  Save the smaller of n_zeros and m_zeros for later. Before returning   *
     *  the output we need to bit shift to the left by this value.            */
    shift = (m_zeros < n_zeros ? m_zeros : n_zeros);

    /*  Apply the Euclidean and Binary reductions repeatedly, decreasing m    *
     *  and n at each step, until one of the values is zero or one.           */
    while (1L < n)
    {
        /*  Apply the Euclidean reduction.                                    */
        m %= n;
        n -= m;

        /*  If m is zero, we are done. Note that n can't be zero since        *
         *  m mod n is less than n, hence n - m is positive.                  */
        if (m == 0L)
            return n << shift;

        /*  Apply the binary (i.e. Stein GCD) reduction step.                 */
        m = m >> TMPL_LONG_TRAILING_ZEROS(m);
        n = n >> TMPL_LONG_TRAILING_ZEROS(n);

        /*  Swap m and n, if necessary, so that m is larger.                  */
        if (m < n)
        {
            tmp = m;
            m = n;
            n = tmp;
        }
    }
    return (n == 1L ? n : m) << shift;
}
/*  End of tmpl_Long_GCD.                                                     */

/*  Implementation of the Euclidean GCD algorithm.                            */
#elif TMPL_GCD_ALGORITHM == 3

/*  Function for computing the GCD of two integers.                           */
long int tmpl_Long_GCD(long int m, long int n)
{
    long int tmp;

    /*  The GCD of negative numbers is still positive. Compute the absolute   *
     *  value of m and n and use the unsigned algorithm.                      */
    m = labs(m);
    n = labs(n);

    /*  Apply the Euclidean GCD algorithm.                                    */
    while(n != 0L)
    {
        m %= n;

        /*  After m %=n we have m < n. Swap the values so that m is larger.   */
        tmp = m;
        m = n;
        n = tmp;
    }
    return m;
}
/*  End of tmpl_Long_GCD.                                                     */

/*  Implementation of the Standard "by-hand" GCD algorithm.                   */
#else

/*  Function for computing the GCD of two integers.                           */
long int tmpl_Long_GCD(long int m, long int n)
{
    /*  Special case. The while loop can be infinite if one of the entries is *
     *  zero. GCD(n, 0) = n, so use this.                                     */
    if (m == 0L)
        return n;
    else if (n == 0L)
        return m;

    /*  The GCD of negative numbers is still positive. Compute the absolute   *
     *  value of m and n and use the unsigned algorithm.                      */
    m = labs(m);
    n = labs(n);

    /*  The "by-hand" algorithm repeatedly subtracts the smaller value from   *
     *  the larger value until the two are equal.                             */
    while(m != n)
    {
        if(m > n)
            m -= n;
        else
            n -= m;
    }
    return m;
}
/*  End of tmpl_Long_GCD.                                                     */

#endif
/*  End of #if TMPL_BINARY_GCD_ALGORITHM == 1.                                */

/*  #undef the macro in case someone wants to #include this file.             */
#undef TMPL_GCD_ALGORITHM
