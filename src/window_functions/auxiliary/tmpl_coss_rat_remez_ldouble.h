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
 *                         tmpl_coss_rat_remez_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for small x.                       *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Coss_Rat_Remez                                           *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a rational Remez             *
 *      approximation for small arguments.                                    *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (long double):                                                 *
 *          The squared cosine of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the (N, M) rational Remez approximation for the  *
 *      squared cosine window have been pre-computed on the interval          *
 *      [-1/4, 1/4], where N and M depend on how long double is implemented:  *
 *                                                                            *
 *          Implementation        | Numerator | Denominator                   *
 *          -----------------------------------------------                   *
 *          64-bit double         |         8 |           8                   *
 *          80-bit extended       |        10 |           8                   *
 *          128-bit double-double |        14 |          12                   *
 *          128-bit quadruple     |        14 |          14                   *
 *                                                                            *
 *      Since the window is an even function, half of the coefficients are    *
 *      zero, meaning we only have (N / 2) + 1 non-zero terms in the          *
 *      numerator and (M / 2) + 1 non-zero terms in the denominator. The      *
 *      approximation is performed using Horner's method for the numerator    *
 *      and denominator, and then returning their ratio.                      *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for |x| < 0.25.                 *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing TMPL_STATIC_INLINE macro.                  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       April 7, 2026                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_COSS_RAT_REMEZ_LDOUBLE_H
#define TMPL_COSS_RAT_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degrees of the polynomials depend on how long double is implemented.  */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999814294167983477388606818921917447E-01L)
#define A01 (-8.9909753678859383203473172175891602746773609095774E+00L)
#define A02 (+2.4184740936822766200042961247244511937750797180333E+01L)
#define A03 (-1.7911116274298446927652579161391059800213681918521E+01L)
#define A04 (+4.1110377986602408304634553634346278069211474884566E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+8.7862903320341543362110676916516883420189191660289E-01L)
#define B02 (+3.8676489852003343630654296694332946146724035323969E-01L)
#define B03 (+1.0569037984474647161225234531782473681512124350968E-01L)
#define B04 (+1.6120651585134203120937922938676077964136587073203E-02L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*A04)))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  128-bit double-double, more terms needed.                                 */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                           128-bit Double-Double                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999999999999999999915722554064002911E-01L)
#define A01 (-9.3896098318482590573337980880712444669193254597571E+00L)
#define A02 (+2.7846435939931048544892042254814171176980971223960E+01L)
#define A03 (-2.8251761513287829271722585463833090262481993018426E+01L)
#define A04 (+1.3147220167079241024017838945262447692605303126501E+01L)
#define A05 (-3.0812831704713131601041286619631795332422521164093E+00L)
#define A06 (+3.5944850961289039087838292552143610886508752309937E-01L)
#define A07 (-1.6937841222360308076065904363365774525952312920625E-02L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+4.7999456924109956150069291179959986956805728536306E-01L)
#define B02 (+1.1409544167784991343378140460275417304179130483982E-01L)
#define B03 (+1.7445733042625223636395938783837557138528325580426E-02L)
#define B04 (+1.8416250256725892359861216752979470154022657372685E-03L)
#define B05 (+1.2997524102959627246595604325674284428693189707025E-04L)
#define B06 (+4.9190739460197445059738054618262286422762946992500E-06L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*(A06 + z*A07))))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*(B05 + z*B06)))))

/*  128-bit quadruple, one more term than double-double.                      */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                             128-bit Quadruple                              *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.0000000000000000000000000000000000010449235984281E+00L)
#define A01 (-9.3676699779987294476833228591743974551930909083084E+00L)
#define A02 (+2.7642748440925299671724235799969750170196834077672E+01L)
#define A03 (-2.7662416079686136138349629221287714864081703633010E+01L)
#define A04 (+1.2590322813816719987040508467843744658183714215135E+01L)
#define A05 (-2.8535160662848067596373117444916949369630315707589E+00L)
#define A06 (+3.1749030653689578501952793650069966978086316837228E-01L)
#define A07 (-1.4021474920950013596322739455869472943047820089534E-02L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+5.0193442309062917115116814070176123257889829543675E-01L)
#define B02 (+1.2694562078467578248954189156845965098676349356121E-01L)
#define B03 (+2.1236943944653958595191625296253248578925270557304E-02L)
#define B04 (+2.5756414076736922137813711609764828681532778862395E-03L)
#define B05 (+2.3045149136304118651130850613998401504670248366248E-04L)
#define B06 (+1.4385719996795593573479928494392735720583485484652E-05L)
#define B07 (+4.9621461549671858905308724032039846803545468597561E-07L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*(A06 + z*A07))))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*(B05 + z*(B06 + z*B07))))))

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999999866947662560581633830620700251E-01L)
#define A01 (-9.2121298105473137083341160712527177777888542112970E+00L)
#define A02 (+2.6189287586223357427411805457412534936385522738918E+01L)
#define A03 (-2.3400108200726195697949532487008005521382789561223E+01L)
#define A04 (+8.4202932388762362077933254271763308685830514401301E+00L)
#define A05 (-1.0886159317338155419559788462154312982197940439493E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+6.5747459054204490621125887408448011696812484663669E-01L)
#define B02 (+2.0860468730740436514966783423127333439590290682091E-01L)
#define B03 (+3.9145395006049044155512279963174787469373793099027E-02L)
#define B04 (+3.8340748043492814131662495660722369321022753489992E-03L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the squared cosine window via a rational Remez expansion.        */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Coss_Rat_Remez(const long double x)
{
    /*  The polynomials are in terms of x^2. Compute.                         */
    const long double x2 = x * x;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const long double numer = TMPL_NUM_EVAL(x2);
    const long double denom = TMPL_DEN_EVAL(x2);

    /*  The squared cosine window is the ratio.                               */
    return numer / denom;
}
/*  End of tmpl_LDouble_Coss_Rat_Remez.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
