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
 *      Provides a lookup table for n! at single precision.                   *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 18, 2022                                              *
 ******************************************************************************/

/*  The lookup table is declared here.                                        */
#include <libtmpl/include/tmpl_math.h>

/*  Lookup table for the factorial function.                                  */
const float tmpl_float_factorial_table[34] = {
    1.000000000000000000000000000000e+00F,
    1.000000000000000000000000000000e+00F,
    2.000000000000000000000000000000e+00F,
    6.000000000000000000000000000000e+00F,
    2.400000000000000000000000000000e+01F,
    1.200000000000000000000000000000e+02F,
    7.200000000000000000000000000000e+02F,
    5.040000000000000000000000000000e+03F,
    4.032000000000000000000000000000e+04F,
    3.628800000000000000000000000000e+05F,
    3.628800000000000000000000000000e+06F,
    3.991680000000000000000000000000e+07F,
    4.790016000000000000000000000000e+08F,
    6.227020800000000000000000000000e+09F,
    8.717829120000000000000000000000e+10F,
    1.307674368000000000000000000000e+12F,
    2.092278988800000000000000000000e+13F,
    3.556874280960000000000000000000e+14F,
    6.402373705728000000000000000000e+15F,
    1.216451004088320000000000000000e+17F,
    2.432902008176640000000000000000e+18F,
    5.109094217170944000000000000000e+19F,
    1.124000727777607680000000000000e+21F,
    2.585201673888497821286400000000e+22F,
    6.204484017332394099998720000000e+23F,
    1.551121004333098605530316800000e+25F,
    4.032914611266056503227842560000e+26F,
    1.088886945041835194023988428800e+28F,
    3.048883446117138719189028044800e+29F,
    8.841761993739701898620088352768e+30F,
    2.652528598121910682176017190093e+32F,
    8.222838654177922430198509928972e+33F,
    2.631308369336935177663523177271e+35F,
    8.683317618811885938715673895318e+36F
};
