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
 ******************************************************************************
 *                         tmpl_erf_maclaurin_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) at long double precision.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Erf_Maclaurin                                            *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin series of erf(x) for small values x.           *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      erf_x (long double):                                                  *
 *          The Maclaurin series of erf(x).                                   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Use Horner's method to evaluate the polynomial.                       *
 *                                                                            *
 *                             infty                                          *
 *                             -----                                          *
 *                      2      \        (-1)^n                                *
 *          erf(x) = --------  /      ----------- * x^{2n+1}                  *
 *                   sqrt(pi)  -----  (2n + 1) n!                             *
 *                             n = 0                                          *
 *                                                                            *
 *      Use the first few terms to compute.                                   *
 *  Notes:                                                                    *
 *      Only accurate for small values.                                       *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 27, 2024                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_MACLAURIN_LDOUBLE_H
#define TMPL_ERF_MACLAURIN_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  64-bit long double does not need any more precision than 64-bit double.   */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00L)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01L)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01L)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02L)
#define A04 (+5.2239776254421878421118467737108572763338021234167E-03L)
#define A05 (-8.5483270234508528325466583569814028158189489292273E-04L)
#define A06 (+1.2055332981789664251027338708563516791539543361731E-04L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*A06)))))

/*  double-double, need several more terms.                                   */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00L)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01L)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01L)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02L)
#define A04 (+5.2239776254421878421118467737108572763338021234167E-03L)
#define A05 (-8.5483270234508528325466583569814028158189489292273E-04L)
#define A06 (+1.2055332981789664251027338708563516791539543361731E-04L)
#define A07 (-1.4925650358406250977462419353459592218096577495476E-05L)
#define A08 (+1.6462114365889247401612962522198079652312401649422E-06L)
#define A09 (-1.6365844691234924317393003677039026554930457780127E-07L)
#define A10 (+1.4807192815879217239546050945892452597318033229639E-08L)
#define A11 (-1.2290555301717927352982888136906778835718525605629E-09L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*A11\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  128-bit quadruple, a few more terms.                                      */
#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00L)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01L)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01L)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02L)
#define A04 (+5.2239776254421878421118467737108572763338021234167E-03L)
#define A05 (-8.5483270234508528325466583569814028158189489292273E-04L)
#define A06 (+1.2055332981789664251027338708563516791539543361731E-04L)
#define A07 (-1.4925650358406250977462419353459592218096577495476E-05L)
#define A08 (+1.6462114365889247401612962522198079652312401649422E-06L)
#define A09 (-1.6365844691234924317393003677039026554930457780127E-07L)
#define A10 (+1.4807192815879217239546050945892452597318033229639E-08L)
#define A11 (-1.2290555301717927352982888136906778835718525605629E-09L)
#define A12 (+9.4227590646504109706202142382951971073842029643158E-11L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*(\
                                A08 + z*(\
                                    A09 + z*(\
                                        A10 + z*(\
                                            A11 + z*A12\
                                        )\
                                    )\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Portable and 80-bit extended.                                             */
#else

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.1283791670955125738961589031215451716881012586580E+00L)
#define A01 (-3.7612638903183752463205296770718172389603375288600E-01L)
#define A02 (+1.1283791670955125738961589031215451716881012586580E-01L)
#define A03 (-2.6866170645131251759432354836227265992573839491857E-02L)
#define A04 (+5.2239776254421878421118467737108572763338021234167E-03L)
#define A05 (-8.5483270234508528325466583569814028158189489292273E-04L)
#define A06 (+1.2055332981789664251027338708563516791539543361731E-04L)
#define A07 (-1.4925650358406250977462419353459592218096577495476E-05L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_POLY_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*(A06 + z*A07))))))

#endif
/*  End of quadruple vs. double-double vs. extended vs. double.               */

/*  Function for computing erf(x) via a Maclaurin series.                     */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Maclaurin(long double x)
{
    /*  The polynomial is odd, in terms of x^{2n+1}. Compute x^2.             */
    const long double x2 = x*x;

    /*  Evaluate the polynomial using Horner's method and return.             */
    const long double poly = TMPL_POLY_EVAL(x2);
    return x*poly;
}
/*  End of tmpl_LDouble_Erf_Maclaurin.                                        */

/*  #undef everything in case someone wants to #include this file.            */
#undef TMPL_POLY_EVAL
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07
#undef A08
#undef A09
#undef A10
#undef A11
#undef A12

#endif
/*  End of include guard.                                                     */
