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
 *      Provides a lookup table for 2^n at long double precision.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2024                                             *
 ******************************************************************************/

/*  The lookup table is declared here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Powers of 2, 2^n, for n = 0 to n = 64.                                    */
const long double tmpl_ldouble_pow_2_table[65] = {
    1.0L, 2.0L, 4.0L, 8.0L, 16.0L, 32.0L, 64.0L, 128.0L, 256.0L, 512.0L,
    1024.0L, 2048.0L, 4096.0L, 8192.0L, 16384.0L, 32768.0L, 65536.0L,
    131072.0L, 262144.0L, 524288.0L, 1048576.0L, 2097152.0L, 4194304.0L,
    8388608.0L, 16777216.0L, 33554432.0L, 67108864.0L, 134217728.0L,
    268435456.0L, 536870912.0L, 1073741824.0L,
    2147483648.0L, 4294967296.0L, 8589934592.0L,
    17179869184.0L, 34359738368.0L, 68719476736.0L,
    137438953472.0L, 274877906944.0L, 549755813888.0L,
    1099511627776.0L, 2199023255552.0L, 4398046511104.0L,
    8796093022208.0L, 17592186044416.0L, 35184372088832.0L,
    70368744177664.0L, 140737488355328.0L, 281474976710656.0L,
    562949953421312.0L, 1125899906842624.0L, 2251799813685248.0L,
    4503599627370496.0L, 9007199254740992.0L, 18014398509481984.0L,
    36028797018963968.0L, 72057594037927936.0L, 144115188075855872.0L,
    288230376151711744.0L, 576460752303423488.0L, 1152921504606846976.0L,
    2305843009213693952.0L, 4611686018427387904.0L, 9223372036854775808.0L,
    18446744073709551616.0L
};
