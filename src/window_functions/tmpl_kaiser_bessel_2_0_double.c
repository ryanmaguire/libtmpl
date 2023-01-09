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
 *                       tmpl_kaiser_bessel_2_0_double                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window with alpha = 2 pi.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Kaiser_Bessel_2_0                                         *
 *  Purpose:                                                                  *
 *      Computes the Kaiser-Bessel window function with alpha set to 2 pi.    *
 *      This is defined in terms of modified Bessel functions:                *
 *                                                                            *
 *                        I_0(2 pi sqrt(1 - (2x/W)^2))                        *
 *          kb20(x, W) =  ----------------------------                        *
 *                                 I_0(2 pi)                                  *
 *                                                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number, the input data value.                              *
 *      W (double):                                                           *
 *          The width of the window. Units are the same as x.                 *
 *  Output:                                                                   *
 *      window (double):                                                      *
 *          The Kaiser-Bessel window with alpha = 2 Pi and window width W     *
 *          evaluated at the point x.                                         *
 *  IEEE-754 Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Compute the value 1 - (2x/W)^2. Check that sign bit. It the       *
 *          value is negative, then x falls outside the window and 0 is       *
 *          returned. Otherwise a (9, 9) Pade approximant is used.            *
 *  Portable Version:                                                         *
 *      Called Functions:                                                     *
 *          None.                                                             *
 *      Method:                                                               *
 *          Same as IEEE-754 method but check if 1 - (2x/W)^2 is negative     *
 *          using comparisons, rather than examining the sign bit. This is    *
 *          slightly slower on some machines, but not by much.                *
 *  Error:                                                                    *
 *      Max Relative Error: 2E-18                                             *
 *      RMS Relative Error: 7E-19                                             *
 *                                                                            *
 *      These values are theoretical errors from the Pade approximant.        *
 *      Actual error for 64-bit double is 1 ULP, 2^-52 ~= 2.22E-16.           *
 *  Notes:                                                                    *
 *      No checks for x = NaN or x = +/- Inf are performed. For x = +/- inf,  *
 *      1 - (x/W)^2 will be negative, so zero is returned. For NaN the result *
 *      can be +/- NaN or zero.                                               *
 *                                                                            *
 *      No checks for W = NaN, +/- Inf, or zero are performed. W = zero will  *
 *      result in divide-by-zero, and NaN or Inf may return.                  *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing TMPL_HAS_IEEE754_DOUBLE macro.             *
 *  2.) tmpl_window_functions.h:                                              *
 *          Header file with the functions prototype.                         *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       November 27, 2020                                             *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2023/01/05: Ryan Maguire                                                  *
 *      Changed algorithm from Taylor series to Pade approximant. This        *
 *      improves the precision from 1E-10 to 2E-16, double precision.         *
 *  2023/01/06: Ryan Maguire                                                  *
 *      Added license and comments.                                           *
 ******************************************************************************/

/*  TMPL_HAS_IEEE754_DOUBLE found here, as is the tmpl_Double_IEEE754 type.   */
#include <libtmpl/include/tmpl_math.h>

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_window_functions.h>

/*  Coefficients of the numerator.                                            */
#define P00 (+1.147993453795864792123256251730288859461E-02)
#define P01 (+1.089790128371111321554374900397660538008E-01)
#define P02 (+2.377105794800031186134565326466905228847E-01)
#define P03 (+2.092636283774886203212152441457477172325E-01)
#define P04 (+9.257515648344964470757412174676463620137E-02)
#define P05 (+2.287912862416715797377369389546066335607E-02)
#define P06 (+3.309532224917444846997983825846377306060E-03)
#define P07 (+2.797860700165350538361382529918277822222E-04)
#define P08 (+1.290527907066360424942306464948584998564E-05)
#define P09 (+2.537011972925611522691331552438283809594E-07)

/*  Coefficients of the denominator.                                          */
#define Q00 (+1.000000000000000000000000000000000000000E+00)
#define Q01 (-3.766049003718496129020039336140441103214E-01)
#define Q02 (+7.128316873877182778240295206238813275886E-02)
#define Q03 (-8.963795068655300298779633628452570816671E-03)
#define Q04 (+8.318633930931961266076848105490873301205E-04)
#define Q05 (-5.961413170047543637842885985788132655307E-05)
#define Q06 (+3.332692590401286361374502373956321918915E-06)
#define Q07 (-1.417912095440724499980310056000438703332E-07)
#define Q08 (+4.222465742471958776777040882707095535238E-09)
#define Q09 (-6.812597858597641118443266860521373937274E-11)

/*  Helper macro for the Pade approximant. This uses Horner's method.         */
#define TMPL_PADE_HELPER(x, A) \
A##00 + x*(\
    A##01 + x*(\
        A##02 + x*(\
            A##03 + x*(\
                A##04 + x*(\
                    A##05 + x*(\
                        A##06 + x*(\
                            A##07 + x*(\
                                A##08 + x*A##09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  With IEEE-754 support we can check if the input falls within the window   *
 *  more efficiently. This gives a slight performance boost.                  */
#if TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision Kaiser-Bessel window with alpha = 2 pi.                  */
double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const double c = 2.0*x/W;

    /*  Set the double part of the union to 1 - (2x/W)^2 and check the sign.  */
    w.r = 1.0 - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (w.bits.sign)
        return 0.0;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(w.r, P);
    denom = TMPL_PADE_HELPER(w.r, Q);
    return numer / denom;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

#else
/*  Else for #if TMPL_HAS_IEEE754_DOUBLE == 1.                                */

/*  Double precision Kaiser-Bessel window with alpha = 2 pi.                  */
double tmpl_Double_Kaiser_Bessel_2_0(double x, double W)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double numer, denom;

    /*  The Function is I_0(2 pi sqrt(1 - (2x/W)^2))/I_0(2pi) for values      *
     *  inside the window. To determine if x falls in the window we need to   *
     *  check if 1 - (2x/W)^2 is non-negative. Compute this.                  */
    const double c = 2.0*x/W;
    const double arg = 1.0 - c*c;

    /*  Negative means the input falls outside of the window. Return 0.       */
    if (arg < 0.0)
        return 0.0;

    /*  Otherwise x falls inside the window. Compute via the Pade approximant.*/
    numer = TMPL_PADE_HELPER(arg, P);
    denom = TMPL_PADE_HELPER(arg, Q);
    return numer / denom;
}
/*  End of tmpl_Double_Kaiser_Bessel_2_0.                                     */

#endif
/*  End of #if TMPL_HAS_IEEE754_DOUBLE == 1.                                  */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_PADE_HELPER
#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08
#undef Q09

/******************************************************************************
 *  (8, 8) Pade approximant. Coefficients saved for future reference.         *
 *      Max Relative Error: 3E-15                                             *
 *      RMS Relative Error: 1E-15                                             *
 *  #define P00 (+1.14799345379586479212325625173E-02)                        *
 *  #define P01 (+1.08460957320536773036375456606E-01)                        *
 *  #define P02 (+2.32805011457736410816092872215E-01)                        *
 *  #define P03 (+1.98654102911356976882372573366E-01)                        *
 *  #define P04 (+8.33924574747798099715396990518E-02)                        *
 *  #define P05 (+1.89374146455274903062254800825E-02)                        *
 *  #define P06 (+2.38528881140176091721254727362E-03)                        *
 *  #define P07 (+1.58185689589546216155616576405E-04)                        *
 *  #define P08 (+4.36543773687157959376385892914E-06)                        *
 *                                                                            *
 *  #define Q00 (+1.00000000000000000000000000000E+00)                        *
 *  #define Q01 (-4.21731944856415054085193094988E-01)                        *
 *  #define Q02 (+8.93525212632413657127079762661E-02)                        *
 *  #define Q03 (-1.25350222898161735099188621406E-02)                        *
 *  #define Q04 (+1.28667499707303873183193073396E-03)                        *
 *  #define Q05 (-1.00125398262872993854148570995E-04)                        *
 *  #define Q06 (+5.84738134193771654036450053602E-06)                        *
 *  #define Q07 (-2.38084238875396710793297721666E-07)                        *
 *  #define Q08 (+5.27370330232818833752452109393E-09)                        *
 ******************************************************************************/
