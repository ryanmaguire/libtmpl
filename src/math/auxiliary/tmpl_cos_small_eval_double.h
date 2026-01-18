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
#ifndef TMPL_COS_SMALL_EVAL_DOUBLE_H
#define TMPL_COS_SMALL_EVAL_DOUBLE_H

/*  TMPL_STATIC_INLINE macro provided here.                                   */
#include <libtmpl/include/tmpl_config.h>

/*  The lookup table is defined here.                                         */
#include <libtmpl/include/tmpl_math.h>

/*  Remez coefficients for sin(x).                                            */
#define S0 (+1.00000000000000000000000000000000E+00)
#define S1 (-1.66666666666664880952546298448555E-01)
#define S2 (+8.33333214285722277379541354343671E-03)

/*  Remez coefficients for cos(x).                                            */
#define C0 (+4.99999999999999999999950396842453E-01)
#define C1 (-4.16666666666664434524222570944589E-02)
#define C2 (+1.38888874007937613028114285595617E-03)

/*  Shift factor for reducing the argument. This is 1.5 x 2^45. This trick    *
 *  requires IEEE-754 64-bit doubles in order to work.                        */
#define TMPL_BIG_NUMBER (5.2776558133248E+13)

/*  Computes cos(x) for small values of x.                                    */
TMPL_STATIC_INLINE
double tmpl_Double_Cos_Small_Eval(double x)
{
    tmpl_IEEE754_Double w;
    double sn, ssn, cs, ccs, cor;
    unsigned int k;
    const double abs_x = tmpl_Double_Abs(x);
    const double x_shift = TMPL_BIG_NUMBER + abs_x;
    const double arg = abs_x - (x_shift - TMPL_BIG_NUMBER);
    const double arg_sq = arg*arg;

    /*  Approximate cosine and sine using Remez minimax polynomials.          */
    const double sin_arg = arg * (S0 + arg_sq*(S1 + arg_sq*S2));
    const double cos_arg = arg_sq * (C0 + arg_sq*(C1 + arg_sq*C2));

    w.r = x_shift;
    k = (w.bits.man3 << 2U) & 0xFFFF;

    sn = tmpl_double_sincos_table[k];
    ssn = tmpl_double_sincos_table[k + 1];
    cs = tmpl_double_sincos_table[k + 2];
    ccs = tmpl_double_sincos_table[k + 3];

    cor = (ccs - sin_arg * ssn - cs * cos_arg) - sin_arg * sn;
    return cs + cor;
}

/*  Undefine everything in case someone wants to #include this file.          */
#undef S0
#undef S1
#undef S2
#undef C0
#undef C1
#undef C2
#undef TMPL_BIG_NUMBER

#endif
/*  End of include guard.                                                     */
