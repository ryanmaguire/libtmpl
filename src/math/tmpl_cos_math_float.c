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
 ******************************************************************************/
#include <libtmpl/include/tmpl_config.h>

#if TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math.h>

#if TMPL_HAS_IEEE754_FLOAT == 1

float tmpl_Float_Cos(float x)
{
    const double in = (double)x;
    const double out = tmpl_Double_Cos(in);
    return (float)out;
}

#else

float tmpl_Float_Cos(float x)
{
    float arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Float_Mod_2(tmpl_Float_Abs(x) * tmpl_One_By_Pi_F);

    if (arg >= 1.0F)
    {
        sgn_x = -1.0F;
        arg = arg - 1.0F;
    }
    else
        sgn_x = 1.0F;

    ind = (unsigned int)(128.0F*arg + 0.25F);
    dx = arg - 0.0078125F*(float)ind;

    sx = tmpl_float_sinpi_table[ind];
    cx = tmpl_float_cospi_table[ind];
    sdx = tmpl_Float_SinPi_Maclaurin(dx);
    cdx = tmpl_Float_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}

#endif

#endif
