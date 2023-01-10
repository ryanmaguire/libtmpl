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
 *                      tmpl_bessel_i0_maclaurin_double                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Maclaurin expansion of I0(x) at double precision.        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Bessel_I0_Maclaurin                                       *
 *  Purpose:                                                                  *
 *      Computes the Maclaurin expansion of I0(x) for small x.                *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      I0_x (double):                                                        *
 *          The modified Bessel function I0 at x.                             *
 *  Called Functions:                                                         *
 *      tmpl_Double_Exp_Pos_Kernel (tmpl_math.h):                             *
 *          Computes exp(x) for x > 1.                                        *
 *      tmpl_Double_Sqrt (tmpl_math.h):                                       *
 *          Computes the square root of a real number.                        *
 *  Method:                                                                   *
 *      Compute the Maclaurin series of I0(x) using Horner's method:          *
 *                                                                            *
 *                   infty                                                    *
 *                   -----                                                    *
 *                   \          x^2n                                          *
 *          I0(x) =  /      ------------                                      *
 *                   -----   (n!)^2 4^n                                       *
 *                   n = 0                                                    *
 *                                                                            *
 *      Use the first 21 terms (0 <= n <= 20) of this expansion to compute.   *
 *  Notes:                                                                    *
 *      Accurate for small values. For |x| < 8, accurate to double precision. *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file containing exp and sqrt functions.                    *
 *  3.) tmpl_special_functions_real.h:                                        *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 10, 2022                                              *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_BESSEL_I0_MACLAURIN_DOUBLE_H
#define TMPL_BESSEL_I0_MACLAURIN_DOUBLE_H

/*  TMPL_USE_INLINE macro found here.                                         */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support was requested.                            */
#if TMPL_USE_INLINE == 1

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define A01 (+2.5000000000000000000000000000000000000000000000000E-01)
#define A02 (+1.5625000000000000000000000000000000000000000000000E-02)
#define A03 (+4.3402777777777777777777777777777777777777777777778E-04)
#define A04 (+6.7816840277777777777777777777777777777777777777778E-06)
#define A05 (+6.7816840277777777777777777777777777777777777777778E-08)
#define A06 (+4.7095027970679012345679012345679012345679012345679E-10)
#define A07 (+2.4028075495244394053917863441672965482489292013102E-12)
#define A08 (+9.3859669903298414273116654069035021415973796926178E-15)
#define A09 (+2.8969033920771115516394029033652784387646233619191E-17)
#define A10 (+7.2422584801927788790985072584131960969115584047977E-20)
#define A11 (+1.4963343967340452229542370368622305985354459514045E-22)
#define A12 (+2.5978027721077174009622170778858170113462603322994E-25)
#define A13 (+3.8429035090350849126660015945056464664885507874252E-28)
#define A14 (+4.9016626390753634090127571358490388603170290655934E-31)
#define A15 (+5.4462918211948482322363968176100431781300322951038E-34)
#define A16 (+5.3186443566355939767933562671973077911426096631873E-37)
#define A17 (+4.6009034226951504989561905425582247328223266982589E-40)
#define A18 (+3.5500798014623074837624927025912227876715483782862E-43)
#define A19 (+2.4585040176331769278133605973623426507420695140486E-46)
#define A20 (+1.5365650110207355798833503733514641567137934462804E-49)

/*  Helper macro for evaluating a polynomial with Horner's method.            */
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
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*A20\
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
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Compute the modified Bessel function I0 with a Maclaurin series.          */
TMPL_INLINE_DECL
double tmpl_Double_Bessel_I0_Maclaurin(double x)
{
    /*  The function is even and the series is in terms of x^2.               */
    const double x2 = x*x;

    /*  Use Horner's method to compute and return.                            */
    return TMPL_POLY_EVAL(x2);
}
/*  End of tmpl_Double_Bessel_I0_Maclaurin.                                   */

/*  Undef everything in case someone wants to #include this file.             */
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
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20

#endif
/*  End of #if TMPL_USE_INLINE == 1.                                          */

#endif
/*  End of include guard.                                                     */
