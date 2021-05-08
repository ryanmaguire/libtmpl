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

static float __arctan_small_vals(float x)
{
    float x_sq = x*x;
    float out;

    out = 1.62858201153657823623E-02F * x_sq - 3.65315727442169155270E-02F;
    out = out * x_sq + 4.97687799461593236017E-02F;
    out = out * x_sq - 5.83357013379057348645E-02F;
    out = out * x_sq + 6.66107313738753120669E-02F;
    out = out * x_sq - 7.69187620504482999495E-02F;
    out = out * x_sq + 9.09088713343650656196E-02F;
    out = out * x_sq - 1.11111104054623557880E-01F;
    out = out * x_sq + 1.42857142725034663711E-01F;
    out = out * x_sq - 1.99999999998764832476E-01F;
    out = out * x_sq + 3.33333333333329318027E-01F;
    out = x*(1.0F - x_sq * out);

    return out;
}

#define ATAN_OF_ONE_HALF    0.46364760900080611621425623146121440202853705F
#define ATAN_OF_ONE         0.78539816339744830961566084581987572104929234F
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745F

float tmpl_Float_Arctan(float x)
{
    float arg, sgn_x;

    if (x < 0.0F)
    {
        sgn_x = -1.0F;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0F;
        arg = x;
    }

    if (arg < 0.4375F)
        return sgn_x * __arctan_small_vals(arg);

    else if (arg < 0.6875F)
    {
        arg = (2.0F * arg - 1.0F) / (2.0F + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + __arctan_small_vals(arg));
    }
    else if (arg < 1.1875F)
    {
        arg = (arg - 1.0F) / (arg + 1.0F);
        return sgn_x * (ATAN_OF_ONE + __arctan_small_vals(arg));
    }
    else if (arg < 2.4375F)
    {
        arg = (2.0F * arg - 3.0F) / (2.0F + 3.0F * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + __arctan_small_vals(arg));
    }
    else
    {
        arg = -1.0F / arg;
        return sgn_x * (tmpl_Pi_By_Two_F + __arctan_small_vals(arg));
    }
}

