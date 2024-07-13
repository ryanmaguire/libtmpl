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
 *                tmpl_normalized_fresnel_cos_auxiliary_double                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Cos_Auxiliary                          *
 *  Purpose:                                                                  *
 *      Computes C(x) for large positive inputs.                              *
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
 *          C(x) = 0.5 + f(x) cos(pi/2 x^2) - g(x) sin(pi/2 x^2)              *
 *          S(x) = 0.5 - f(x) sin(pi/2 x^2) - g(x) cos(pi/2 x^2)              *
 *                                                                            *
 *      Solving for f and g gives us the following:                           *
 *                                                                            *
 *          f(x) = sin(pi/2 x^2) (C(x) - 0.5) - cos(pi/2 x^2) (S(x) - 0.5)    *
 *          g(x) = -sin(pi/2 x^2) (S(x) - 0.5) - cos(pi/2 x^2) (C(x) - 0.5)   *
 *                                                                            *
 *      We shift the interval [4, infty) via:                                 *
 *                                                                            *
 *          t = 4 / x                                                         *
 *                                                                            *
 *      And compute rational Remez approximations for f(t) and g(t). We must  *
 *      be careful when squaring. Naively squaring a large number may lead    *
 *      precision loss in the calculation of sin(pi/2 x^2) and cos(pi/2 x^2). *
 *      We split the input into two parts to relieve us of this issue. That   *
 *      is, we write:                                                         *
 *                                                                            *
 *                         x = xhi + xlo                                      *
 *                    => x^2 = xhi^2 + 2 xhi xlo + xlo^2                      *
 *          => cos(pi/2 x^2) = cos(u) cos(pi/2 xlo^2) - sin(u) sin(pi/2 xlo^2)*
 *          => sin(pi/2 x^2) = cos(u) sin(pi/2 xlo^2) + sin(u) cos(pi/2 xlo^2)*
 *                                                                            *
 *      where u = pi/2 (xhi^2 + 2 xhi xlo).                                   *
 *                                                                            *
 *      For 4 <= x < 2^17 we have |xlo| < 2^-10, hence xlo^2 < 2^-20.         *
 *      We can compute cos and sin of pi/2 xlo^2 safely using the first few   *
 *      terms of their respective Taylor series. After this, all that is left *
 *      to compute is cos(u) and sin(u). This is done using the angle sum     *
 *      formula for cos and sin, recalling that u = pi/2 (xhi^2 + 2 xhi xlo). *
 *  Notes:                                                                    *
 *      This function assumes the input is between 4 and 2^17.                *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_DOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void tmpl_Double_SinCosPi(double t, double *sin_t, double *cos_t);

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (-2.1447177918579579753388433334911075409571981652522E-17)
#define A01 (+7.9577471545956793464435579966743818103647044950248E-02)
#define A02 (-1.2981161608641168980253175509340062024354018232720E-02)
#define A03 (+3.1265770142568086318447462445674196101423129654279E-03)
#define A04 (+7.7189914096390976785579606078912825867840834363500E-03)
#define A05 (+1.2152711327644207051269759240566405273724207890213E-03)
#define A06 (-4.2580086843249039236789916436456229647180162906877E-04)
#define A07 (+2.5599751814229062968976494152423993700328342606881E-04)
#define A08 (-9.2991030649511374603974585631455140488901798820494E-06)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (-1.6312608777091934006569688848947319631644210599940E-01)
#define B02 (+3.9289725286653476885524131750142019793543796155984E-02)
#define B03 (+9.6999710172863227181034452265627316168021158412569E-02)
#define B04 (+1.6458875720410357910114941861796832691658504516205E-02)
#define B05 (-5.5442943302851907019637247635816813200757166309069E-03)
#define B06 (+3.2629747328741893876385822248293808741755682623822E-03)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+4.1888470497242228970512655048232789216782855688029E-18)
#define C01 (-1.9399304561569123981472429874629917184781769350025E-15)
#define C02 (+1.5079232893754790305784439966341317007503129139523E-13)
#define C03 (+1.5831434897680803460728630060707251688669525968296E-03)
#define C04 (-8.5860131430356321612346593614783654305957210855428E-04)
#define C05 (+4.2520325383513231021011832063304578196045175371085E-04)
#define C06 (+3.3997508002435750699645210285275720556079846712290E-05)
#define C07 (-5.5470926830268577613702499017237117454491309503712E-06)
#define C08 (+7.5271268828364550735383328753338000305964366209750E-06)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define D01 (-5.4233958725410615801476694071713976580197499138498E-01)
#define D02 (+2.6858208718351641067450334485612139901006052610880E-01)
#define D03 (+2.1471758208227504686456421042560514470187040155549E-02)
#define D04 (+2.4456357033936610541923412853466023983394272209113E-03)
#define D05 (+1.4961320031496760787440948034839831542661075561170E-03)
#define D06 (+1.6780659196575798229291066904872309116983197533248E-03)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*B06)))))

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) \
C00+z*(C01+z*(C02+z*(C03+z*(C04+z*(C05+z*(C06+z*(C07+z*C08)))))))

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) D00+z*(D01+z*(D02+z*(D03+z*(D04+z*(D05+z*D06)))))

/*  First two terms for the Maclaurin series of cos(pi/2 x^2).                */
#define C0 (+1.0000000000000000000000000000000000000000000E+00)
#define C1 (-1.2337005501361698273543113749845188919142124E+00)

/*  First two terms for the Maclaurin series of sin(pi/2 x^2).                */
#define S0 (+1.5707963267948966192313216916397514420985846E+00)
#define S1 (-6.4596409750624625365575656389794573337969351E-01)

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
double tmpl_Double_Normalized_Fresnel_Cos_Auxiliary(double x)
{
    /*  Use the double-double trick, split x into two parts, high and low.    *
     *  The magic number 134217729 is 2^27 + 1. This results in xhi and xlo   *
     *  both having half of the bits of x.                                    */
    const double split = 134217729.0 * x;
    const double xhi = split - (split - x);
    const double xlo = x - xhi;

    /*  The Maclaurin series for cos(pi/2 x^2) is in terms of x^4. Compute.   */
    const double xlo_sq = xlo * xlo;
    const double xlo_qr = xlo_sq * xlo_sq;

    /*  xlo^2 is small, so sin(pi/2 xlo^2) and cos(pi/2 xlo^2) can be         *
     *  accurately computed using a few terms of the Maclaurin series.        */
    const double cos_lo = C0 + xlo_qr * C1;
    const double sin_lo = xlo_sq * (S0 + xlo_qr * S1);

    /*  The auxiliary functions f and g are computed by shifting the interval *
     *  [4, infty) using the following formula.                               */
    const double t = 4.0 / x;

    /*  Compute the auxiliary function f using a rational Remez approximation.*/
    const double fn = TMPL_POLYA_EVAL(t);
    const double fd = TMPL_POLYB_EVAL(t);
    const double f = fn / fd;

    /*  Perform the same calculation for the auxiliary function g.            */
    const double gn = TMPL_POLYC_EVAL(t);
    const double gd = TMPL_POLYD_EVAL(t);
    const double g = gn / gd;

    /*  Variables for storing the values of sine and cosine.                  */
    double cos_hi, sin_hi, cos_mid, sin_mid, cos_midlo, sin_midlo, cos_x, sin_x;

    /*  xhi^2 and 2 xhi xlo are big enough that we need to use the full sine  *
     *  and cosine functions. Run the computation.                            */
    tmpl_Double_SinCosPi(0.5 * xhi * xhi, &sin_hi, &cos_hi);
    tmpl_Double_SinCosPi(xhi * xlo, &sin_mid, &cos_mid);

    /*  The sine and cosine of the low part was computed using a Maclaurin    *
     *  series, and the sine and cosine of the mid part have been computed as *
     *  well. Compute the sine and cosine of the sum using the angle sum      *
     *  formula.                                                              */
    cos_midlo = cos_mid * cos_lo - sin_mid * sin_lo;
    sin_midlo = cos_mid * sin_lo + sin_mid * cos_lo;

    /*  Perform the same calculation with the sine and cosine of the mid and  *
     *  high parts using the angle sum formula.                               */
    cos_x = cos_hi * cos_midlo - sin_hi * sin_midlo;
    sin_x = cos_hi * sin_midlo + sin_hi * cos_midlo;

    /*  With the auxiliary functions computed, we can compute C(x).           */
    return 0.5 + (f*sin_x - g*cos_x);
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Auxiliary.                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"
#undef C0
#undef C1
#undef S0
#undef S1

#endif
/*  End of include guard.                                                     */
