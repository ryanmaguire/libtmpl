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
#include "auxiliary/tmpl_sin_precise_eval_double.h"
#include "auxiliary/tmpl_sincos_reduction.h"
#include "auxiliary/tmpl_sincos_reduction_very_large.h"

double tmpl_Double_Sin(double x)
{
    double a, da, out;
    tmpl_IEEE754_Double w;
    unsigned int n;
    const double pi_by_two_hi = 1.570796326794896619231321691639E+00;
    const double pi_by_two_lo = 6.123233995736766035868820147292E-17;

    w.r = x;
    w.bits.sign = 0x00U;

    if (w.bits.expo < TMPL_DOUBLE_BIAS - 26U)
        return x;

    else if (w.r < 8.5546875E-01)
        return tmpl_Double_Sin_Precise_Eval(x, 0.0);

    else if (w.r < 2.426265)
    {
        w.r = pi_by_two_hi - w.r;
        da = pi_by_two_lo;
        return tmpl_Double_Copysign(tmpl_Double_Cos_Precise_Eval(w.r, da), x);
    }
    else if (w.bits.expo < TMPL_DOUBLE_NANINF_EXP)
    {
        if (w.r < 1.05414336E+08)
            n = tmpl_Double_SinCos_Reduction(x, &a, &da);
        else
            n = tmpl_Double_SinCos_Reduction_Very_Large(x, &a, &da);

        if (n & 1)
            out = tmpl_Double_Cos_Precise_Eval(a, da);
        else
            out = tmpl_Double_Sin_Precise_Eval(a, da);

        return (n & 2 ? -out : out);
    }
    else
        return TMPL_NAN;
}

#else

#include "auxiliary/tmpl_cospi_maclaurin_double.h"
#include "auxiliary/tmpl_sinpi_maclaurin_double.h"

double tmpl_Double_Sin(double x)
{
    double arg, abs_x, sgn_x, cx, cdx, sx, sdx, dx;
    unsigned int ind;

    if (x >= 0.0)
    {
        abs_x = x;
        sgn_x = 1.0;
    }
    else
    {
        abs_x = -x;
        sgn_x = -1.0;
    }

    arg = tmpl_Double_Mod_2(abs_x * tmpl_Double_Rcpr_Pi);

    if (arg >= 1.0)
    {
        sgn_x *= -1.0;
        arg -= 1.0;
    }

    ind = (unsigned int)(128.0*arg);
    dx = arg - 0.0078125*ind;

    sx = tmpl_double_sinpi_table[ind];
    cx = tmpl_double_cospi_table[ind];
    sdx = tmpl_Double_SinPi_Maclaurin(dx);
    cdx = tmpl_Double_CosPi_Maclaurin(dx);
    return sgn_x * (cdx*sx + cx*sdx);
}

#endif

#endif
