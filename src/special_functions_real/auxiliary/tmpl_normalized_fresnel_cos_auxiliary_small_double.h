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
 *             tmpl_normalized_fresnel_cos_auxiliary_small_double             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for mid-sized inputs.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Auxiliary_Small                    *
 *  Purpose:                                                                  *
 *      Computes C(x) for 2 <= x < 4.                                         *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_Double_SinCosPi:                                             *
 *              Simultaneously computes sin(pi x) and cos(pi x).              *
 *  Method:                                                                   *
 *      The normalized Fresnel functions are asymptotic to 1/2 as x tends to  *
 *      positive infinity. They also have highly oscillatory behavior and can *
 *      be approximated using cosine and sine. That is, we may use auxiliary  *
 *      functions f and g to write:                                           *
 *                                                                            *
 *          C(x) = 0.5 + f(x) sin(pi/2 x^2) - g(x) cos(pi/2 x^2)              *
 *          S(x) = 0.5 - f(x) cos(pi/2 x^2) - g(x) sin(pi/2 x^2)              *
 *                                                                            *
 *      Solving for f and g gives us the following:                           *
 *                                                                            *
 *          f(x) = sin(pi/2 x^2) (C(x) - 0.5) - cos(pi/2 x^2) (S(x) - 0.5)    *
 *          g(x) = -sin(pi/2 x^2) (S(x) - 0.5) - cos(pi/2 x^2) (C(x) - 0.5)   *
 *                                                                            *
 *      We shift the interval [4, infty):                                     *
 *                                                                            *
 *          t = 1 / x                                                         *
 *                                                                            *
 *      And compute rational Remez approximations for f(t) and g(t). We must  *
 *      be careful when squaring. Naively squaring a large number may lead    *
 *      precision loss in the calculation of sin(pi/2 x^2) and cos(pi/2 x^2). *
 *      We split the input into two parts to relieve us of this issue. That   *
 *      is, we write:                                                         *
 *                                                                            *
 *                         x = xhi + xlo                                      *
 *                    => x^2 = xhi^2 + 2 xhi xlo + xlo^2                      *
 *          => cos(pi/2 x^2) = cos(u) cos(v) - sin(u) sin(v)                  *
 *          => sin(pi/2 x^2) = cos(u) sin(v) + sin(u) cos(v)                  *
 *                                                                            *
 *      where u = pi/2 xhi^2 and v = pi/2 (2 xhi xlo + xlo^2). v is small     *
 *      enough that cos(v) and sin(v) can be computed using small Taylor      *
 *      polynomials. cos(u) and sin(u) are computed in their entirety.        *
 *  Notes:                                                                    *
 *      This function assumes the input is between 2 and 4.                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       July 8, 2024                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_SMALL_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_SMALL_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Splitting function for retrieving the high part of a double given here.   */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/split/tmpl_even_high_split_double.h>
#else
extern double tmpl_Double_Even_High_Split(double x);
#endif

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void tmpl_Double_SinCosPi(double t, double *sin_t, double *cos_t);

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (+2.5703724299657391880484846679213652814012552703086E-07)
#define A01 (+3.1830090055989159443079660141643697380527143958367E-01)
#define A02 (-5.8364360938790173766825869667058317208792477494973E-01)
#define A03 (+2.1270894621813623233357731534627057397142961709989E+00)
#define A04 (-1.3707938560959418037898894458374663307834900805917E+00)
#define A05 (+2.5885155851674980284912655727964308957274722252260E+00)
#define A06 (+1.1096318379407176910580428607896631060221419264663E-01)
#define A07 (+1.5677269150255168623117903590862822519021085751393E-01)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-1.8340061067984813713149842839488538605288002066046E+00)
#define B02 (+6.6862881102108010107333439887856875158324172145474E+00)
#define B03 (-4.3270587876109819201264786452599507842454214366160E+00)
#define B04 (+8.4987835739785486837778649463261557667671771347990E+00)
#define B05 (-2.6581276744363058729791325678478430945922854114764E-01)
#define B06 (+2.2005566252691005977332094546307120239536233286139E+00)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (-1.5037922851806219733961438088877029730210353047650E-07)
#define C01 (+5.8825135283577460507410927514017802605784905819186E-06)
#define C02 (-1.0404950252132407674352474461119774828636605755187E-04)
#define C03 (+1.0241463717486993400039703075086120344700114645998E-01)
#define C04 (-1.8819547496642853895882397386460270632119181024707E-01)
#define C05 (+8.3903448432340481802419018665178495348306087113855E-01)
#define C06 (-6.1254499526256925705463330744836837221709800954563E-01)
#define C07 (+1.5116321008288957217408083103517520076531766119719E+00)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define D01 (-1.7830899368808261165532882721325366394047352626272E+00)
#define D02 (+7.9327411271741694324594596490129404224576060387241E+00)
#define D03 (-4.9327126910218758142609575150656502509143664321137E+00)
#define D04 (+1.4055732441050503326502540808950918539606318078526E+01)
#define D05 (+7.8731074657517163897183369777297374492877974905501E-01)
#define D06 (+7.0782106464978070017788685865819834136757486939388E+00)
#define D07 (+2.6225196697592760185024826482142321645031047869881E+00)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*A07))))))

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*B06)))))

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) \
C00+z*(C01+z*(C02+z*(C03+z*(C04+z*(C05+z*(C06+z*C07))))))

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) \
D00+z*(D01+z*(D02+z*(D03+z*(D04+z*(D05+z*(D06+z*D07))))))

/*  First two terms for the Maclaurin series of cos(pi/2 x).                  */
#define C0 (+1.0000000000000000000000000000000000000000000E+00)
#define C1 (-1.2337005501361698273543113749845188919142124E+00)

/*  First two terms for the Maclaurin series of sin(pi/2 x).                  */
#define S0 (+1.5707963267948966192313216916397514420985846E+00)
#define S1 (-6.4596409750624625365575656389794573337969351E-01)

/*  Function for computing the normalized Fresnel cosine for 2 <= x < 4.      */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Cos_Auxiliary_Small(double x)
{
    /*  Split the input into two parts, high and low.                         */
    const double xhi = tmpl_Double_Even_High_Split(x);
    const double xlo = x - xhi;

    /*  The auxiliary functions f and g are computed by shifting the interval *
     *  [2, 4) using the following formula.                                   */
    const double t = 1.0 / x;

    /*  Compute the auxiliary function f using a rational Remez approximation.*/
    const double fn = TMPL_POLYA_EVAL(t);
    const double fd = TMPL_POLYB_EVAL(t);
    const double f = fn / fd;

    /*  Perform the same calculation for the auxiliary function g.            */
    const double gn = TMPL_POLYC_EVAL(t);
    const double gd = TMPL_POLYD_EVAL(t);
    const double g = gn / gd;

    /*  With v = 2 xlo xhi + xlo^2, compute cos(pi/2 v) and sin(pi/2 v) using *
     *  Taylor polynomials. v is small, only a few terms needed.              */
    const double v = 2.0 * xhi * xlo + xlo * xlo;
    const double v_sq = v * v;
    const double cos_lo = C0 + v_sq * C1;
    const double sin_lo = v * (S0 + v_sq * S1);

    /*  Variables for storing the values of sine and cosine.                  */
    double cos_hi, sin_hi, cos_x, sin_x;

    /*  xhi^2 is big enough that we need to compute cos and sin fully. Do     *
     *  this simultaneously using the SinCosPi function.                      */
    tmpl_Double_SinCosPi(0.5 * xhi * xhi, &sin_hi, &cos_hi);

    /*  cos and sin can be computed using the angle sum formula.              */
    cos_x = cos_hi * cos_lo - sin_hi * sin_lo;
    sin_x = cos_hi * sin_lo + sin_hi * cos_lo;

    /*  With the auxiliary functions computed, we can compute C(x).           */
    return 0.5 + (f*sin_x - g*cos_x);
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Auxiliary_Small.                */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"
#undef TMPL_COS_MACLAURIN
#undef TMPL_SIN_MACLAURIN
#undef C0
#undef C1
#undef S0
#undef S1

#endif
/*  End of include guard.                                                     */
