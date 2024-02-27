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

#if TMPL_HAS_IEEE754_DOUBLE == 1

#include "auxiliary/tmpl_cos_precise_eval_double.h"
#include "auxiliary/tmpl_cos_small_eval_double.h"
#include "auxiliary/tmpl_sin_precise_eval_double.h"
#include "auxiliary/tmpl_sincos_reduction.h"

double tmpl_Double_Cos(double x)
{
    double a, da, out;
    tmpl_IEEE754_Double w;
    unsigned int n;
    const double pi_by_two_low_half = 6.123233995736766035868820147292E-17;

    w.r = x;

    if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
        return TMPL_NAN;

    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_BIAS - 27U)
        return 1.0;

    if (w.r < 8.5546875E-01)
        return tmpl_Double_Cos_Small_Eval(x);

    if (w.r < 2.426265)
    {
        w.r = tmpl_Pi_By_Two - w.r;
        a = w.r + pi_by_two_low_half;
        da = (w.r - a) + pi_by_two_low_half;
        return tmpl_Double_Sin_Precise_Eval(a, da);
    }

    n = tmpl_Double_SinCos_Reduction(x, &a, &da) + 1;

    if (n & 1)
        out = tmpl_Double_Cos_Precise_Eval(a, da);
    else
        out = tmpl_Double_Sin_Precise_Eval(a, da);

    return (n & 2 ? -out : out);
}

#else

#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"

double tmpl_Double_Cos(double x)
{
    double arg, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    arg = tmpl_Double_Mod_2(tmpl_Double_Abs(x) * tmpl_One_By_Pi);

    if (arg >= 1.0)
    {
        sgn_x = -1.0;
        arg = arg - 1.0;
    }
    else
        sgn_x = 1.0;

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*ind;

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*cx - sx*sdx);
}

#endif

#endif
