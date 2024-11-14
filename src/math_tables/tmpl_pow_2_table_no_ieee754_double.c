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
 *  Purpose:                                                                  *
 *      Provides a lookup table for 2^n at double precision.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2024                                             *
 ******************************************************************************/

/*  The lookup table is declared here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Only needed for the "portable" versions lacking IEEE-754 support.         */
#if TMPL_HAS_IEEE754_DOUBLE != 1

/*  Powers of 2, 2^n, for n = 0 to n = 64.                                    */
const double tmpl_double_pow_2_table[65] = {
    1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0,
    4096.0, 8192.0, 16384.0, 32768.0, 65536.0, 131072.0, 262144.0, 524288.0,
    1048576.0, 2097152.0, 4194304.0, 8388608.0, 16777216.0, 33554432.0,
    67108864.0, 134217728.0, 268435456.0, 536870912.0, 1073741824.0,
    2147483648.0, 4294967296.0, 8589934592.0, 17179869184.0, 34359738368.0,
    68719476736.0, 137438953472.0, 274877906944.0, 549755813888.0,
    1099511627776.0, 2199023255552.0, 4398046511104.0, 8796093022208.0,
    17592186044416.0, 35184372088832.0, 70368744177664.0, 140737488355328.0,
    281474976710656.0, 562949953421312.0, 1125899906842624.0,
    2251799813685248.0, 4503599627370496.0, 9007199254740992.0,
    18014398509481984.0, 36028797018963968.0, 72057594037927936.0,
    144115188075855872.0, 288230376151711744.0, 576460752303423488.0,
    1152921504606846976.0, 2305843009213693952.0, 4611686018427387904.0,
    9223372036854775808.0, 18446744073709551616.0
};

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE != 1.                                  */
