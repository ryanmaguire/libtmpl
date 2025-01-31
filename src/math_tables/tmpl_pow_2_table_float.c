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
 *      Provides a lookup table for 2^n at single precision.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 14, 2024                                             *
 ******************************************************************************/

/*  The lookup table is declared here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Powers of 2, 2^n, for n = 0 to n = 64.                                    */
const float tmpl_float_pow_2_table[65] = {
    1.0F, 2.0F, 4.0F, 8.0F, 16.0F, 32.0F, 64.0F, 128.0F, 256.0F, 512.0F,
    1024.0F, 2048.0F, 4096.0F, 8192.0F, 16384.0F, 32768.0F, 65536.0F, 131072.0F,
    262144.0F, 524288.0F, 1048576.0F, 2097152.0F, 4194304.0F, 8388608.0F,
    16777216.0F, 33554432.0F, 67108864.0F, 134217728.0F, 268435456.0F,
    536870912.0F, 1073741824.0F, 2147483648.0F, 4294967296.0F, 8589934592.0F,
    17179869184.0F, 34359738368.0F, 68719476736.0F, 137438953472.0F,
    274877906944.0F, 549755813888.0F, 1099511627776.0F, 2199023255552.0F,
    4398046511104.0F, 8796093022208.0F, 17592186044416.0F, 35184372088832.0F,
    70368744177664.0F, 140737488355328.0F, 281474976710656.0F,
    562949953421312.0F, 1125899906842624.0F, 2251799813685248.0F,
    4503599627370496.0F, 9007199254740992.0F, 18014398509481984.0F,
    36028797018963968.0F, 72057594037927936.0F, 144115188075855872.0F,
    288230376151711744.0F, 576460752303423488.0F, 1152921504606846976.0F,
    2305843009213693952.0F, 4611686018427387904.0F, 9223372036854775808.0F,
    18446744073709551616.0F
};
