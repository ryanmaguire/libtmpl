/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                            tmpl_gcd_binary_uint                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of unsigned integers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_GCD_Binary                                                  *
 *  Purpose:                                                                  *
 *      Computes GCD(m, n), the greatest common divisor of m and n.           *
 *  Arguments:                                                                *
 *      m (unsigned int):                                                     *
 *          An integer.                                                       *
 *      n (unsigned int):                                                     *
 *          Another integer.                                                  *
 *  Output:                                                                   *
 *      gcd (unsigned int):                                                   *
 *          The greatest common divisor of m and n.                           *
 *  Called Functions:                                                         *
 *      tmpl_integer.h:                                                       *
 *          TMPL_UINT_TRAILING_ZEROS/                                         *
 *              Counts the number of trailing zeros in an unsigned int. On    *
 *              platforms supporting ctz or bsf this macro expands to one of  *
 *              those, otherwise it is tmpl_UInt_Trailing_Zeros.              *
 *  Method:                                                                   *
 *      Use the classic Stein algorithm, also known as the binary GCD         *
 *      algorithm. This uses the fact that:                                   *
 *                                                                            *
 *          GCD(2m, 2n) = 2 GCD(m, n)                                         *
 *                                                                            *
 *      We iteratively remove trailing zeros from m and n until they are odd  *
 *      and then invoke the following identity:                               *
 *                                                                            *
 *          GCD(m, n) = GCD(m, n - m)                                         *
 *                                                                            *
 *      This holds when m and n are odd and m <= n. We then remove trailing   *
 *      zeros again and repeat. Eventually we will reduce to m = n, and then  *
 *      GCD can be obtained by multiplying by 2^min(ctz(m), ctz(n)), where    *
 *      ctz is the "count-trailing-zeros" function. That is, we bit shift by  *
 *      minimum number of trailing zeros that were removed at the start of    *
 *      the function.                                                         *
 *  Notes:                                                                    *
 *      1.) On some platforms, and with some compilers, this is the fastest   *
 *          algorithm for the GCD that libtmpl provides. This is both CPU and *
 *          compiler specific, and also depends on compiler flags at build    *
 *          time. On x86_64 with GCC or LLVM's Clang, and with optimizations  *
 *          enabled, the mixed-binary algorithm is much faster, almost by a   *
 *          factor of 2. The tmpl_UInt_GCD function selects the algorithm     *
 *          requested at build time, the default is mixed-binary. If the      *
 *          Stein algorithm is faster, set the TMPL_GCD_ALGORITHM flag at     *
 *          compile time to use this function instead. See build instructions *
 *          for more details. Usually if the architecture can do fast modulus *
 *          operations, the mixed-binary algorithm will be faster.            *
 *                                                                            *
 *      2.) By definition, GCD(0, 0) = 0, GCD(n, 0) = n, and GCD(0, n) = n.   *
 *          This function follows these requirements.                         *
 *  Error:                                                                    *
 *      Based on 2,245,328,622 samples with 0 <= x, y < RAND_MAX.             *
 *          max relative error: 0                                             *
 *          rms relative error: 0                                             *
 *          max absolute error: 0                                             *
 *          rms absolute error: 0                                             *
 *      Tests were performed in C++ using glibc (std::gcd) and boost          *
 *      (boost::integer::gcd). Error values assume 100% accuracy with these   *
 *      implementations.                                                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_min.h:                                                           *
 *          Header file providing the TMPL_MIN macro.                         *
 *  2.) tmpl_swap.h:                                                          *
 *          Header file providing the TMPL_SWAP macro.                        *
 *  3.) tmpl_integer.h:                                                       *
 *          Header file containing the function prototype.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 29, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/05/24: Ryan Maguire                                                  *
 *      Added more algorithms. There are 4 available: binary, mixed binary,   *
 *      Euclidean, and "by-hand". Binary is fastest, followed by Euclidean,   *
 *      and then mixed-binary. The "by-hand" algorithm is the slowest.        *
 *  2025/12/30: Ryan Maguire                                                  *
 *      Added references, fixed docstring, added TMPL_SWAP macro, clean-up.   *
 ******************************************************************************/

/*  The TMPL_MIN macro is found here, computes the minimum of two values.     */
#include <libtmpl/include/helper/tmpl_min.h>

/*  TMPL_SWAP macro, used for swapping the data in two variables.             */
#include <libtmpl/include/helper/tmpl_swap.h>

/*  Function prototype is found here, as is TMPL_UINT_TRAILING_ZEROS.         */
#include <libtmpl/include/tmpl_integer.h>

/*  Function for computing the GCD of two unsigned integers.                  */
unsigned int tmpl_UInt_GCD_Binary(const unsigned int m, const unsigned int n)
{
    /*  Declare all necessary variables. C89 requires this at the top.        */
    int m_zeros, n_zeros;
    unsigned int u, v;

    /*  Special cases. GCD(0, n) = n. It is best to avoid using the trailing  *
     *  zeros function on zero. The libtmpl macro makes ctz(0) = 0, but in    *
     *  general this is not well defined. It may be 0, it may be the number   *
     *  of bits in unsigned int, or it may be something else. This if-then    *
     *  statement for zero helps us avoid such issues.                        */
    if (m == 0U)
        return n;

    /*  Same check for n, use GCD(m, 0) = m.                                  */
    if (n == 0U)
        return m;

    /*  Use the fact that GCD(2m, 2n) = 2 GCD(m, n) to reduce the arguments.  *
     *  Since GCD(2^k m, 2^k n) = 2^k GCD(m, n), we will eventually scale the *
     *  result by 2^k where k is the minimum of ctz(m) and ctz(n), given by   *
     *  m_zeros and n_zeros, respectively.                                    */
    m_zeros = TMPL_UINT_TRAILING_ZEROS(m);
    n_zeros = TMPL_UINT_TRAILING_ZEROS(n);
    u = m >> m_zeros;
    v = n >> n_zeros;

    /*  Keep reducing the arguments until we have n = m. GCD(n, n) = n, and   *
     *  our computation will be almost complete.                              */
    while (u != v)
    {
        /*  Swap the variables so that u is larger, if necessary.             */
        if (v > u)
            TMPL_SWAP(unsigned int, u, v);

        /*  Next reduction step in the GCD algorithm. Use the fact that, for  *
         *  odd inputs u and v, GCD(u, v) = GCD(|u - v|, min(u, v)). Since we *
         *  have removed all trailing zeros from u and v, both are odd.       */
        u -= v;

        /*  Remove all trailing zeros from m, ensuring m is odd. Since m != n *
         *  we are guaranteed that m - n is positive.                         */
        u >>= TMPL_UINT_TRAILING_ZEROS(u);
    }

    /*  If a < b, we have GCD(2^a u, 2^b v) = 2^a GCD(u, 2^{b-a} v). We have  *
     *  just computed GCD(u, 2^{b-a} v). We now need to multiply by 2^a. Here *
     *  we have a is the number of trailing zeros in the input m, and b is    *
     *  the number of trailing zeros in the input n. We've saved both of      *
     *  these values as m_zeros and n_zeros, respectively. Compute the        *
     *  minimum of these two and then bit-shift m to the left by this min.    *
     *  This is the equivalent of multiplying u by 2^min(m_zeros, n_zeros).   */
    return u << TMPL_MIN(m_zeros, n_zeros);
}
/*  End of tmpl_UInt_GCD_Binary.                                              */
