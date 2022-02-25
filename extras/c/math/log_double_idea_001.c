/******************************************************************************
 *                                 LICENSE                                    *
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
 *  Old algorithm used for log. It has good performance and accuracy, but the *
 *  current method is faster and more accurate. This is saved here for        *
 *  archiving purposes.                                                       *
 ******************************************************************************/

#include <libtmpl/include/tmpl_math.h>

double old_log(double x)
{
    double mantissa, poly, A, A_sq;
    signed int exponent;
    tmpl_IEEE754_Double w;

    if (x < 0.0)
        return TMPL_NAN;
    else if (x == 0.0)
        return -TMPL_INFINITY;
    else if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x + x;

    w.r = x;
    exponent = w.bits.expo - TMPL_DOUBLE_BIAS;
    w.bits.expo = TMPL_DOUBLE_BIAS;
    mantissa = w.r;

    if (mantissa > 1.5)
    {
        mantissa *= 0.5;
        exponent += 1;
    }

    A = (mantissa - 1.0) / (mantissa + 1.0);
    A_sq = A*A;

    poly = 0.095238095238095238 * A_sq + 0.10526315789473684;
    poly =                 poly * A_sq + 0.11764705882352941;
    poly =                 poly * A_sq + 0.13333333333333333;
    poly =                 poly * A_sq + 0.15384615384615385;
    poly =                 poly * A_sq + 0.18181818181818182;
    poly =                 poly * A_sq + 0.22222222222222222;
    poly =                 poly * A_sq + 0.28571428571428571;
    poly =                 poly * A_sq + 0.40000000000000000;
    poly =                 poly * A_sq + 0.66666666666666667;
    poly =                 poly * A_sq + 2.0000000000000000;

    return tmpl_Natural_Log_of_Two*exponent + A*poly;
}
/*  End of old_log.                                                           */

