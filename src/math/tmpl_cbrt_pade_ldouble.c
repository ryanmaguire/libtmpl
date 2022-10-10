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
#define P0 (1.000000000000000000000000000000000000000E+00L)
#define P1 (3.666666666666666666666666666666666666667E+00L)
#define P2 (5.358974358974358974358974358974358974359E+00L)
#define P3 (3.969610636277302943969610636277302943970E+00L)
#define P4 (1.563786008230452674897119341563786008230E+00L)
#define P5 (3.127572016460905349794238683127572016461E-01L)
#define P6 (2.702840014225473759081440837270741248793E-02L)
#define P7 (6.435333367203508950193906755406526782841E-04L)

/*  Coefficients for the denominator.                                         */
#define Q0 (1.000000000000000000000000000000000000000E+00L)
#define Q1 (3.333333333333333333333333333333333333333E+00L)
#define Q2 (4.358974358974358974358974358974358974359E+00L)
#define Q3 (2.825261158594491927825261158594491927825E+00L)
#define Q4 (9.417537195314973092750870528648306426084E-01L)
#define Q5 (1.506805951250395694840139284583729028173E-01L)
#define Q6 (9.301271304014788239753946201134129803540E-03L)
#define Q7 (1.107294202858903361875469785849301167088E-04L)

/*  Function for computing the (7, 7) Pade approximate of cbrt(x) at x = 1.   */
long double tmpl_LDouble_Cbrt_Pade(long double x)
{
    /*  The approximant is computed at x = 1. Shift the input.                */
    const long double xs = x - 1.0L;

    /*  Use Horner's method to evaluate the numerator and denominator.        */
    const long double
    p = P0+xs*(P1+xs*(P2+xs*(P3+xs*(P4+xs*(P5+xs*(P6+xs*P7))))));

    const long double
    q = Q0+xs*(Q1+xs*(Q2+xs*(Q3+xs*(Q4+xs*(Q5+xs*(Q6+xs*Q7))))));

    /*  Return the fraction.                                                  */
    return p/q;
}
/*  End of tmpl_LDouble_Cbrt_Pade.                                            */

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

