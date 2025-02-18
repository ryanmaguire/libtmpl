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
 *                            tmpl_binary_gcd_uint                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the GCD of unsigned integers.             *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_UInt_GCD                                                         *
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
 *      TMPL_UINT_TRAILING_ZEROS    (tmpl_integer.h)                          *
 *          Function that counts the number of trailing zeros in a number.    *
 *  Method:                                                                   *
 *      There are four implementations available. Binary, Mixed-Binary,       *
 *      Euclidean, and "by-hand". The Binary algorithm, also called the Stein *
 *      GCD algorithm, is the fastest and the default. Mixed-binary is from   *
 *      The Mixed Binary Euclid Algorithm, Sidi Mohamed Sedjelmaci,           *
 *      Electronic Notes in Discrete Mathematics 35 (2009) 169-176. The       *
 *      Euclidean algorithm is the classic algorithm using repeated modulo    *
 *      operations. The "by-hand" method is the way one computes GCD by hand. *
 *      Subtract the smaller from the larger and repeat until the values are  *
 *      equal. This is by far the slowest.                                    *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything.     *
 *      -std=c89, -std=c99, -std=c11, and -std=c18 flags have been passed as  *
 *      well, and no problems were found. If any error or warnings arise on   *
 *      your platform, please report this.                                    *
 *  Accuracy and Performance:                                                 *
 *      A time and accuracy test yields the following results versus boost.   *
 *      All times are in seconds.                                             *
 *      Binary GCD                                                            *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1405097472                                               *
 *          libtmpl: 71.781926                                                *
 *          boost:   99.431520                                                *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      Mixed Binary GCD                                                      *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1405097472                                               *
 *          libtmpl: 100.545565                                               *
 *          boost:   100.181320                                               *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      Euclidean GCD                                                         *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1405097472                                               *
 *          libtmpl: 88.997715                                                *
 *          boost:   98.855792                                                *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      By-Hand GCD                                                           *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1405097472                                               *
 *          libtmpl: 314.039140                                               *
 *          boost:   101.945712                                               *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      These tests were performed with the following specs:                  *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MIN:  2200.0000 MHz                                               *
 *          MAX:  4672.0698 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *      Using a Windows 10 virtual machine (same specs) with GNOME Boxes:     *
 *      Building libtmpl with MSVC, Binary GCD                                *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 23401941                                                 *
 *          libtmpl: 0.640000                                                 *
 *          boost:   1.522000                                                 *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      Building libtmpl with LLVM's clang, Binary GCD                        *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 23401941                                                 *
 *          libtmpl: 0.630000                                                 *
 *          boost:   0.893000                                                 *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      Using a FreeBSD 13 virtual machine (same specs) with GNOME Boxes:     *
 *      Building libtmpl with LLVM's clang, Binary GCD                        *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1073462016                                               *
 *          libtmpl: 59.601562                                                *
 *          boost:   83.625000                                                *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 *      Building libtmpl with GCC, Binary GCD                                 *
 *          tmpl_UInt_GCD vs. boost::integer::gcd                             *
 *          samples: 1073462016                                               *
 *          libtmpl: 73.781250                                                *
 *          boost:   78.312653                                                *
 *          rms error: 0.000000e+00                                           *
 *          max error: 0.000000e+00                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_integer.h:                                                       *
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
 ******************************************************************************/

#include <libtmpl/include/helper/tmpl_min.h>

/*  Function prototype is found here.                                         */
#include <libtmpl/include/tmpl_integer.h>

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
    m_zeros = TMPL_UINT_TRAILING_ZEROS(m);
    n_zeros = TMPL_UINT_TRAILING_ZEROS(n);
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
         *  we are guaranteed that m - n is positive.                         */
        m >>= TMPL_UINT_TRAILING_ZEROS(m);
    }

    /*  If a < b, we have GCD(2^a m, 2^b n) = 2^a GCD(m, 2^{b-a} n). We have  *
     *  just computed GCD(m, 2^{b-a} n). We now need to multiply by 2^a. Here *
     *  we have a is the number of trailing zeros in the input m, and b is    *
     *  the number of trailing zeros in the input n. We've saved both of      *
     *  these values as m_zeros and n_zeros, respectively. Compute the        *
     *  minimum of these two and then bit-shift m to the left by this min.    *
     *  This is the equivalent of multiplying m by 2^min(m_zeros, n_zeros).   */
    return m << TMPL_MIN(m_zeros, n_zeros);
}
/*  End of tmpl_UInt_GCD.                                                     */
