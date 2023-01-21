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
 *                         tmpl_erf_asymptotic_double                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the error function for larger values at double precision.    *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Erf_Asymptotic                                            *
 *  Purpose:                                                                  *
 *      Computes the Error function erf(x) for x >= 2.                        *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A positive real number.                                           *
 *  Output:                                                                   *
 *      erf_x (double):                                                       *
 *          The error function at x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      For arguments greater than 6 we can return erf(x) = 1. Otherwise      *
 *      compute using a Chebyshev approximation on the interval [2, 6].       *
 *      The function:                                                         *
 *                                                                            *
 *              x - 4                                                         *
 *          y = ------                                                        *
 *                2                                                           *
 *                                                                            *
 *      Transforms the interval [2, 6] to [-1, 1]. We then compute the        *
 *      Chebyshev coefficients for the function:                              *
 *                                                                            *
 *          f(x) = erf(y)                                                     *
 *                                                                            *
 *      We can accurately compute f(x) using a degree 28 Chebyshev expansion: *
 *                                                                            *
 *                  28                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     c_n T_n(x)                                           *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where c_n are the coefficients and T_n is the nth Chebyshev           *
 *      polynomial. We further simplify this into a proper polynomial form    *
 *      by expanding the Chebyshev polynomials.                               *
 *                                                                            *
 *                             --                   --                        *
 *                  28        |    n                  |                       *
 *                 -----      |  -----                |                       *
 *                 \          |  \                    |                       *
 *          f(x) = /      c_n |  /      t_{k, n} x^k  |                       *
 *                 -----      |  -----                |                       *
 *                 n = 0      |  k = 0                |                       *
 *                             --                   --                        *
 *                                                                            *
 *      where t_{k, n} is the kth coefficients of the nth Chebyshev           *
 *      polynomial. By collecting all of the terms together we get:           *
 *                                                                            *
 *                  28                                                        *
 *                 -----                                                      *
 *                 \                                                          *
 *          f(x) = /     a_n x^n                                              *
 *                 -----                                                      *
 *                 n = 0                                                      *
 *                                                                            *
 *      where the a_n are computed from c_n and t_{k, n} via a Cauchy product.*
 *      This is evaluated by Horner's method, which is faster than Clenshaw's *
 *      algorithm for Chebyshev polynomials in their usual form.              *
 *  Notes:                                                                    *
 *      Accurate for x >= 2.                                                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_USE_INLINE macro.                     *
 *  2.) tmpl_math.h:                                                          *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       January 19, 2023                                              *
 ******************************************************************************/

/*  Location of the TMPL_USE_INLINE macro.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this if inline support is not requested.                         */
#if TMPL_USE_INLINE != 1

/*  Header file where the prototype for the function is defined.              */
#include <libtmpl/include/tmpl_math.h>

/*  Coefficients for the polynomial.                                          */
#define A00 (+9.9999998458274208175762223432456249549502926125902E-01)
#define A01 (+2.5396469525474072315862812598955621859919646326548E-07)
#define A02 (-2.0317175394844726792687825258483860217780185054774E-06)
#define A03 (+1.0497207069080116271795993263702674395391427601173E-05)
#define A04 (-3.9279873177333922332504582408292863721138592106915E-05)
#define A05 (+1.1309895453180181019695864439888849555213331820018E-04)
#define A06 (-2.5969863460533195402065003140932652966375366791973E-04)
#define A07 (+4.8588341847909702467484668684320352857808118756892E-04)
#define A08 (-7.4916869570307642471241000326288407502585539013626E-04)
#define A09 (+9.5394799730152875257183607105413033610653843788256E-04)
#define A10 (-9.9356840621075477417401777813978245219270495985029E-04)
#define A11 (+8.2077528526549566750423593640687943522778182310869E-04)
#define A12 (-4.9224095874765589683524100421085379296630966396968E-04)
#define A13 (+1.4289232555329850569658571761403619851382390125881E-04)
#define A14 (+9.6486156696501415073601843161908176802061454681505E-05)
#define A15 (-1.7387132048917405833406069947674234470948247832292E-04)
#define A16 (+1.2842036683237362577907948087598827419660540901807E-04)
#define A17 (-4.3736670033750639293565686279690644772836500156280E-05)
#define A18 (-1.3968592680472564591301820887056412312450355889885E-05)
#define A19 (+2.8477740952087858732556725910687380969690523319095E-05)
#define A20 (-1.8784109116878038541530774069664042408599979607120E-05)
#define A21 (+4.7769180412788485349581455781508742561230050421662E-06)
#define A22 (+4.4055944252548251721699015960894969923081057719191E-06)
#define A23 (-5.2584269297611801936006586952343815902797544183977E-06)
#define A24 (+1.0842314956315554309365139272279286619655706290006E-06)
#define A25 (+1.2336068166571108768589898358888108462984792853852E-06)
#define A26 (-5.8142324105960777505247152292366581743257402006747E-07)
#define A27 (-1.0351072922623697344366646442050567968311005346654E-07)
#define A28 (+7.3988306580553170372966300684171750570874673426603E-08)

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
                      A11 + z*(\
                        A12 + z*(\
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*(\
                                        A20 + z*(\
                                          A21 + z*(\
                                            A22 + z*(\
                                              A23 + z*(\
                                                A24 + z*(\
                                                  A25 + z*(\
                                                    A26 + z*(\
                                                      A27 + z*A28\
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
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Function for computing erf(x) for x >= 2.                                 */
double tmpl_Double_Erf_Asymptotic(double x)
{
    /*  For x >= 6 we have |1 - erf(x)| < 2^-52, double epsilon. Return 1.    */
    if (x >= 6.0)
        return 1.0;

    /*  For other values use the Chebyshev expansion from above.              */
    else
    {
        /*  Shift the interval [2, 6] to [-1, 1] for the polynomial.          */
        const double z = 0.5*(x - 4.0);

        /*  Evaluate the polynomial using Horner's method.                    */
        return TMPL_POLY_EVAL(z);
    }
}
/*  End of tmpl_Double_Erf_Asymptotic.                                        */

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
#undef A13
#undef A14
#undef A15
#undef A16
#undef A17
#undef A18
#undef A19
#undef A20
#undef A21
#undef A22
#undef A23
#undef A24
#undef A25
#undef A26
#undef A27
#undef A28

#endif
/*  End of #if TMPL_USE_INLINE != 1.                                          */
