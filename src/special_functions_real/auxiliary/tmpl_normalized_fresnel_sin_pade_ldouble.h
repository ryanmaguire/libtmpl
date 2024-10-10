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
 *                   tmpl_normalized_fresnel_sin_pade_double                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel sine for small values.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Normalized_Fresnel_Sin_Pade                               *
 *  Purpose:                                                                  *
 *      Computes S(x) for |x| < 1.                                            *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      S_x (double):                                                         *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Compute the (20, 16) Pade approximant for C(x). The polynomials are   *
 *      in terms of x^4, so only 5 terms are needed for the numerator and     *
 *      4 terms required for the denominator.                                 *
 *  Notes:                                                                    *
 *      This function assumes the input is bounded by 1.                      *
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
#ifndef TMPL_NORMALIZED_FRESNEL_SIN_PADE_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_SIN_PADE_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01)
#define A01 (-7.5646702684156373657133062485951711722422797821397E-02)
#define A02 (+4.5603135186970685798333089934580883578580099903679E-03)
#define A03 (-1.2343163613744783025262037672315575856900093113426E-04)
#define A04 (+1.5893800791950822561593328505853377660316668412608E-06)
#define A05 (-8.1994804828506437950754119866572847262867244360994E-09)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+3.1768375804301341219415408603904367390762622593100E-02)
#define B02 (+4.7199046505149390245676635290448031218427214415959E-04)
#define B03 (+3.9836521640342121153574740992762308824026092219817E-06)
#define B04 (+1.6616163918330675261060649578315035528058167218657E-08)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-8.0486141763750771544450102200318667092003503435848E-02L)
#define A02 (+5.2968210372786180327417351402335361546707450231012E-03L)
#define A03 (-1.7102942630506404015365418508455196639540411872895E-04L)
#define A04 (+3.0626738520491902020780093465218676464135134497992E-06L)
#define A05 (-3.2084751766274106013034527304063998879845500805747E-08L)
#define A06 (+1.9763049787375144792956888401814102181507525043528E-10L)
#define A07 (-6.7208633562472193912786230630575015279376482063058E-13L)
#define A08 (+9.9170001620157790706049673802412646328722855334347E-16L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.2525727988586852363083622178572466574580238758440E-02L)
#define B02 (+2.4966482653614088477808522592618415967343248462198E-04L)
#define B03 (+1.7813144516322109583348398482777489700056606150136E-06L)
#define B04 (+8.9290913219144458976516587500767173725981475735249E-09L)
#define B05 (+3.1826756552387062222792340938617478108281929181435E-11L)
#define B06 (+7.5745192989406610779612311053847084297789910132645E-14L)
#define B07 (+9.4395456027820711605628384380488423221454502456054E-17L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-7.9953289965281698458761533204928132915622130461254E-02L)
#define A02 (+5.2169465041694562946417127452369525600933049232498E-03L)
#define A03 (-1.6594662822911479909859867761000396163421399638195E-04L)
#define A04 (+2.9084243308416764297579607577706150117466547920577E-06L)
#define A05 (-2.9581413864484281561532412199718133557488571701138E-08L)
#define A06 (+1.7523587442624624496121815218159509958935578328861E-10L)
#define A07 (-5.6661481403046989104419453719308417531682332021621E-13L)
#define A08 (+7.8400320511967850473147234786584805668495085493780E-16L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.3543399960527965272895230602834418383725345391029E-02L)
#define B02 (+2.7647320122722127001064651663769529679376340261366E-04L)
#define B03 (+2.1324931902695828591562086913527222665231740733218E-06L)
#define B04 (+1.1926105700963773109144504855751616047630121426319E-08L)
#define B05 (+5.0043119919005737490990261251309906294458657182997E-11L)
#define B06 (+1.5572524366513925447226010640150702181776275710203E-13L)
#define B07 (+3.3319730134074715222283720394370548069535038758536E-16L)
#define B08 (+3.8153644178026873154898014946273470405904283625629E-19L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*(B07+z*B08)))))))

#else

/*  Coefficients for the numerator of the Pade approximant.                   */
#define A00 (+5.2359877559829887307710723054658381403286156656252E-01L)
#define A01 (-7.7607006813527965933091162573407772785660660163326E-02L)
#define A02 (+4.8564000854232891179918074083907996709470630271886E-03L)
#define A03 (-1.4230574500260652202534932075955486232031705259771E-04L)
#define A04 (+2.1546056188697033928948475688455782317626809650733E-06L)
#define A05 (-1.6610879242726458035447379126788214478246897226080E-08L)
#define A06 (+5.3137774904477804328966599717850428638015366077611E-11L)

/*  Coefficients for the denominator of the Pade approximant.                 */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.8024470698466022811290406389874088147427990096983E-02L)
#define B02 (+3.7763732622157987783207257479464054089159152989041E-04L)
#define B03 (+3.1102979942114085442779006853646877364697056345684E-06L)
#define B04 (+1.5974110031224817244396756669891736096186401648309E-08L)
#define B05 (+4.1936302065103497572447102420944045502934367886321E-11L)

/*  Helper macro for evaluating the numerator using Horner's method.          */
#define TMPL_NUM_EVAL(z) A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*A06)))))

/*  Helper macro for evaluating the denominator using Horner's method.        */
#define TMPL_DEN_EVAL(z) B00+z*(B01+z*(B02+z*(B03+z*(B04+z*B05))))

#endif

/*  Computes the normalized Fresnel cosine function using a Pade approximant. */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Sin_Pade(long double x)
{
    /*  The Pade approximant is in terms of x^4.                              */
    const long double x2 = x*x;
    const long double x4 = x2*x2;

    /*  Compute the Pade approximant.                                         */
    const long double num = TMPL_NUM_EVAL(x4);
    const long double den = TMPL_DEN_EVAL(x4);
    return x * x2 * num / den;
}
/*  End of tmpl_LDouble_Normalized_Fresnel_Sin_Pade.                           */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
