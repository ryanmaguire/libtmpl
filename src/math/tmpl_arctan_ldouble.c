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
 ******************************************************************************/

#include <libtmpl/include/tmpl_math.h>

static long double __arctan_small_vals(long double x)
{
    long double x_sq = x*x;
    long double out;

    out = 1.62858201153657823623E-02L * x_sq - 3.65315727442169155270E-02L;
    out = out * x_sq + 4.97687799461593236017E-02L;
    out = out * x_sq - 5.83357013379057348645E-02L;
    out = out * x_sq + 6.66107313738753120669E-02L;
    out = out * x_sq - 7.69187620504482999495E-02L;
    out = out * x_sq + 9.09088713343650656196E-02L;
    out = out * x_sq - 1.11111104054623557880E-01L;
    out = out * x_sq + 1.42857142725034663711E-01L;
    out = out * x_sq - 1.99999999998764832476E-01L;
    out = out * x_sq + 3.33333333333329318027E-01L;
    out = x*(1.0L - x_sq * out);

    return out;
}

#define ATAN_OF_ONE_HALF    0.46364760900080611621425623146121440202853705L
#define ATAN_OF_ONE         0.78539816339744830961566084581987572104929234L
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745L

long double tmpl_LDouble_Arctan(long double x)
{
    long double arg, sgn_x;

    if (x < 0.0L)
    {
        sgn_x = -1.0L;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0L;
        arg = x;
    }

    if (arg < 0.4375L)
        return sgn_x * __arctan_small_vals(arg);

    else if (arg < 0.6875L)
    {
        arg = (2.0L * arg - 1.0L) / (2.0L + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + __arctan_small_vals(arg));
    }
    else if (arg < 1.1875L)
    {
        arg = (arg - 1.0L) / (arg + 1.0L);
        return sgn_x * (ATAN_OF_ONE + __arctan_small_vals(arg));
    }
    else if (arg < 2.4375L)
    {
        arg = (2.0L * arg - 3.0L) / (2.0L + 3.0L * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + __arctan_small_vals(arg));
    }
    else
    {
        arg = -1.0L / arg;
        return sgn_x * (tmpl_Pi_By_Two + __arctan_small_vals(arg));
    }
}

