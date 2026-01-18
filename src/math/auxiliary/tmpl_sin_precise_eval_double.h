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

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SIN_PRECISE_EVAL_DOUBLE_H
#define TMPL_SIN_PRECISE_EVAL_DOUBLE_H

/*  TMPL_STATIC_INLINE macro provided here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The lookup table is defined here.                                         */
#include <libtmpl/include/tmpl_math.h>

/*  Remez coefficients for sin(x).                                            */
#define A1 (-1.666666666666666574148081281237e-01)
#define A2 (+8.333333333332328812792511030239e-03)
#define A3 (-1.984126983441464233542950168498e-04)
#define A4 (+2.755729806860771032218275847225e-06)
#define A5 (-2.502201484831839766033848070168e-08)

/*  Remez coefficients for sin(x), smaller degree.                            */
#define S0 (+1.00000000000000000000000000000000E+00)
#define S1 (-1.66666666666664880952546298448555E-01)
#define S2 (+8.33333214285722277379541354343671E-03)

/*  Remez coefficients for cos(x).                                            */
#define C0 (+4.99999999999999999999950396842453E-01)
#define C1 (-4.16666666666664434524222570944589E-02)
#define C2 (+1.38888874007937613028114285595617E-03)

/*  Shift factor for reducing the argument. This is 1.5 x 2^45. This trick    *
 *  requires IEEE-754 64-bit doubles in order to work.                        */
#define TMPL_BIG_NUMBER (5.2776558133248E13)

/*  Computes sin(x + dx) for small dx.                                        */
TMPL_STATIC_INLINE
double tmpl_Double_Sin_Precise_Eval(double x, double dx)
{
    double x2, s, sn, ssn, c, cs, ccs, cor;
    tmpl_IEEE754_Double w, tmp;
    unsigned int k;
    tmp.r = x;

    if (tmp.bits.expo < TMPL_DOUBLE_UBIAS - 3U)
    {
        const double xsq = x*x;
        const double poly = x*(A1 + xsq*(A2 + xsq*(A3 + xsq*(A4 + xsq*A5))));
        return (poly - 0.5*dx)*xsq + dx + x;
    }

    if (tmp.bits.sign)
    {
        x = -x;
        dx = -dx;
    }

    w.r = TMPL_BIG_NUMBER + x;
    x = x - (w.r - TMPL_BIG_NUMBER);

    x2 = x*x;
    s = dx + x*(S0 + x2*(S1 + x2*S2));
    c = x*dx + x2*(C0 + x2*(C1 + x2*C2));
    k = (w.bits.man3 << 2U) & 0xFFFF;
    sn = tmpl_double_sincos_table[k];
    ssn = tmpl_double_sincos_table[k + 1];
    cs = tmpl_double_sincos_table[k + 2];
    ccs = tmpl_double_sincos_table[k + 3];
    cor = (ssn + s * ccs - sn * c) + cs * s;
    w.r = cor + sn;
    w.bits.sign = tmp.bits.sign;
    return w.r;
}

/*  Undefine everything in case someone wants to #include this file.          */
#undef S0
#undef S1
#undef S2
#undef C0
#undef C1
#undef C2
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5
#undef TMPL_BIG_NUMBER

#endif
/*  End of include guard.                                                     */
