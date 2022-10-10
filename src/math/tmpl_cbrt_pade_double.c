/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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

#if TMPL_USE_INLINE != 1

#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the numerator.                                           */
#define P0 (1.000000000000000000000000000000000000000E+00)
#define P1 (3.666666666666666666666666666666666666667E+00)
#define P2 (5.358974358974358974358974358974358974359E+00)
#define P3 (3.969610636277302943969610636277302943970E+00)
#define P4 (1.563786008230452674897119341563786008230E+00)
#define P5 (3.127572016460905349794238683127572016461E-01)
#define P6 (2.702840014225473759081440837270741248793E-02)
#define P7 (6.435333367203508950193906755406526782841E-04)

/*  Coefficients for the denominator.                                         */
#define Q0 (1.000000000000000000000000000000000000000E+00)
#define Q1 (3.333333333333333333333333333333333333333E+00)
#define Q2 (4.358974358974358974358974358974358974359E+00)
#define Q3 (2.825261158594491927825261158594491927825E+00)
#define Q4 (9.417537195314973092750870528648306426084E-01)
#define Q5 (1.506805951250395694840139284583729028173E-01)
#define Q6 (9.301271304014788239753946201134129803540E-03)
#define Q7 (1.107294202858903361875469785849301167088E-04)

/*  Function for computing the (7, 7) Pade approximate of cbrt(x) at x = 1.   */
double tmpl_Double_Cbrt_Pade(double x)
{
    /*  The approximant is computed at x = 1. Shift the input.                */
    const double xs = x - 1.0;

    /*  Use Horner's method to evaluate the numerator and denominator.        */
    const double p = P0+xs*(P1+xs*(P2+xs*(P3+xs*(P4+xs*(P5+xs*(P6+xs*P7))))));
    const double q = Q0+xs*(Q1+xs*(Q2+xs*(Q3+xs*(Q4+xs*(Q5+xs*(Q6+xs*Q7))))));

    /*  Return the fraction.                                                  */
    return p/q;
}
/*  End of tmpl_Double_Cbrt_Pade.                                             */

/*  Undefine all macros in case someone wants to #include this file.          */
#undef P0
#undef P1
#undef P2
#undef P3
#undef P4
#undef P5
#undef P6
#undef P7
#undef Q0
#undef Q1
#undef Q2
#undef Q3
#undef Q4
#undef Q5
#undef Q6
#undef Q7

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
