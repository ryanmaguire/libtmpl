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
#ifndef TMPL_SIN_PADE_DOUBLE_H
#define TMPL_SIN_PADE_DOUBLE_H

/*  TMPL_STATIC_INLINE macro is provided here.                                */
#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Pade approximant.                   */
#define P5 (-1.326704727342721470669055072831298848429E-09)
#define P4 (+5.598649443506351144049005322725000700547E-07)
#define P3 (-8.729668102813383765882747644727845428251E-05)
#define P2 (+5.837572014686924154215552897431476591273E-03)
#define P1 (-1.509578793694727814326849370942536167352E-01)
#define P0 (+1.000000000000000000000000000000000000000E+00)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define Q5 (+3.387582241998014353822768271665615717203E-12)
#define Q4 (+1.946668781997946805314637818154451688036E-09)
#define Q3 (+6.044395000441469584887798898086945171697E-07)
#define Q2 (+1.223698975525716932125078261669849131795E-04)
#define Q1 (+1.570878729719388523398172957241304993144E-02)
#define Q0 (+1.000000000000000000000000000000000000000E+00)

TMPL_STATIC_INLINE
double tmpl_Double_Sin_Pade(double x)
{
    const double x2 = x*x;
    const double p = x*(P0 + x2*(P1 + x2*(P2 + x2*(P3 + x2*(P4 + x2*P5)))));
    const double q = Q0 + x2*(Q1 + x2*(Q2 + x2*(Q3 + x2*(Q4 + x2*Q5))));
    return p / q;
}

/*  Undefine everything in case someone wants to #include this file.          */
#undef P5
#undef P4
#undef P3
#undef P2
#undef P1
#undef P0
#undef Q5
#undef Q4
#undef Q3
#undef Q2
#undef Q1
#undef Q0

#endif
/*  End of include guard.                                                     */
