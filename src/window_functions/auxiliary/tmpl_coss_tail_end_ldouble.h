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
 *                         tmpl_coss_tail_end_ldouble                         *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the squared cosine window for x near 1 / 2.                  *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Coss_Tail_End                                            *
 *  Purpose:                                                                  *
 *      Computes the squared cosine window using a rational Remez             *
 *      approximation for 1 / 4 <= x <= 1 / 2.                                *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      coss_x (long double):                                                 *
 *          The squared cosine of x.                                          *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The squared cosine window can be expanded about x = 1 / 2 in terms    *
 *      of x - 1 / 2. The coefficients for the (M, N) rational Remez          *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 Coss(x + 1 / 2)                                            *
 *          f(x) = ---------------                                            *
 *                        2                                                   *
 *                       x                                                    *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division-by-zero), where Coss represents the squared cosine window,   *
 *      have been pre-computed below. The values for M and N depend on how    *
 *      on how long double is implemented:                                    *
 *                                                                            *
 *          Implementation        | Numerator | Denominator                   *
 *          -----------------------------------------------                   *
 *          64-bit double         |         6 |           6                   *
 *          80-bit extended       |         8 |           6                   *
 *          128-bit double-double |        12 |          10                   *
 *          128-bit quadruple     |        12 |          11                   *
 *                                                                            *
 *      Given x with 1 / 4 <= x <= 1 / 2, we translate x into this interval   *
 *      using:                                                                *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x)^2 * P(t(x)) / Q(t(x)), where P and Q are the     *
 *      numerator and denominator, respectively, for the degree (M, N)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x)^2, the approximation is   *
 *      zero, exact, when x = 1 / 2. That is, the window goes to zero at the  *
 *      right endpoint in the window.                                         *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for 0.25 <= x <= 0.5.           *
 *                                                                            *
 *      2.) This function assumes a normalized window of width 1 is being     *
 *          used on the interval [-1/2, 1/2].                                 *
 *                                                                            *
 *      3.) This function does not accept negative inputs. Use the absolute   *
 *          value of the input if -1/2 <= x <= -1/4.                          *
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
#ifndef TMPL_COSS_TAIL_END_LDOUBLE_H
#define TMPL_COSS_TAIL_END_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degrees of the polynomials depend on how long double is implemented.  */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044010893586824329547474673439140231054116780E+00L)
#define A01 (+4.1647184904568528445364666288540106779119337166960E-01L)
#define A02 (-2.4136360656962329950727086127689298722114082152450E+01L)
#define A03 (-9.5448863792651996029791063270767758721509615075691E-01L)
#define A04 (+1.8647970303817305011034580719878434061915137689507E+01L)
#define A05 (+5.9632459933589183805630582645746132153056504681312E-01L)
#define A06 (-4.3418192157556894760118122867013711529066539213096E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+4.2197420699013371567416842553524757201407202681295E-02L)
#define B02 (+8.4434350311280177014393653960965466579522394674775E-01L)
#define B03 (+4.2114030951057903183272843119015208642281408199238E-02L)
#define B04 (+3.3792026629994898311416323969857683590745206390916E-01L)
#define B05 (+1.6284730518041398561273679141628350855706280155634E-02L)
#define B06 (+6.8410307571893272522513404516975144026427994193341E-02L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05 + z*A06)))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*(B05 + z*B06)))))

/*  128-bit double-double, more terms needed.                                 */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                           128-bit Double-Double                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044010893586188344909998761509968987707023444E+00L)
#define A01 (+2.5884048084492978526701767241101714321501068216106E-01L)
#define A02 (-2.7883081319013689147007815655083486438224645349691E+01L)
#define A03 (-7.2055793825809598493298806257821868139243033102547E-01L)
#define A04 (+2.8673494078797878805588075120282201839328475971826E+01L)
#define A05 (+7.2057041430621927402569776363892314284680404802825E-01L)
#define A06 (-1.3524422141091026629182202873710619459296773185339E+01L)
#define A07 (-3.2048864019875612019439230896587037157815762003694E-01L)
#define A08 (+3.2311091022197878143835556084789549383428158184532E+00L)
#define A09 (+6.7299138147165870930467288531374189045431293758345E-02L)
#define A10 (-3.8514469967001659939233350780139413939880593985549E-01L)
#define A11 (-5.6643719234152643856358010698587216006380491087956E-03L)
#define A12 (+1.8439672724370641235384469577019065725758718364555E-02L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.6226023893760143020584570064968129021328858352777E-02L)
#define B02 (+4.6472133085842917993201736722024481369179628335300E-01L)
#define B03 (+1.3272377094450436977810173880269775889235426772868E-02L)
#define B04 (+1.0481132182096401798386571571336865716533807992116E-01L)
#define B05 (+3.1332777842708492229616982044625354498965410404247E-03L)
#define B06 (+1.4619379891802424084317600442799438292077490926365E-02L)
#define B07 (+4.1836433929926993501919448616639888175060623728023E-04L)
#define B08 (+1.2899725547475799992315694587853476886886258459171E-03L)
#define B09 (+2.7387748433829578128443883451134572222410098230732E-05L)
#define B10 (+5.9100937247902910069331512272493356550256823191811E-05L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
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

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(\
    B01 + z*(\
        B02 + z*(\
            B03 + z*(\
                B04 + z*(\
                    B05 + z*(\
                        B06 + z*(\
                            B07 + z*(\
                                B08 + z*(\
                                    B09 + z*B10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  128-bit quadruple needs one more term than double-double.                 */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                             128-bit Quadruple                              *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044010893586188344909998761511395260022804334E+00L)
#define A01 (-1.3020451276408743866758273545746906887241982727942E+00L)
#define A02 (-2.8222285355890250347554204915870522285731620694356E+01L)
#define A03 (+3.5706599473249136735174920159332812388587671665551E+00L)
#define A04 (+2.9618741653064242297000084921992335820501363429911E+01L)
#define A05 (-3.4821430704717887059900534380988356132113173101508E+00L)
#define A06 (-1.4471352909299669053189694504987905248315919135126E+01L)
#define A07 (+1.4827724542250512960893818816039482732483687507344E+00L)
#define A08 (+3.6536065436573221087818659441705127920469054195849E+00L)
#define A09 (-2.9153325899962223058855821195109038774455533823153E-01L)
#define A10 (-4.7432368359537823579856584916154018246713231721886E-01L)
#define A11 (+2.2289779272006448534970079804843105226760261935899E-02L)
#define A12 (+2.6010079446851673612114929690345097974077620374669E-02L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.3192475348831215762059509942968576274536672945877E-01L)
#define B02 (+4.3035277634583680900869913138585948686337502969841E-01L)
#define B03 (-7.2231550299710436969669307200370035255914249523977E-02L)
#define B04 (+8.7516912588493477509931617491547751074364768205420E-02L)
#define B05 (-1.9306229882616764946063864964178534614558235924395E-02L)
#define B06 (+1.0570448036730045765057621808178334284203303469887E-02L)
#define B07 (-3.2053479489268576639292016204727792799609092645301E-03L)
#define B08 (+7.5619377253132148408042030124965256462229117870576E-04L)
#define B09 (-3.3726504679635254414882136107459706353264619983241E-04L)
#define B10 (+2.4872401488908425115792995522049892974179302802843E-05L)
#define B11 (-1.8383835970512015638477435341394783667009206243464E-05L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
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

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(\
    B01 + z*(\
        B02 + z*(\
            B03 + z*(\
                B04 + z*(\
                    B05 + z*(\
                        B06 + z*(\
                            B07 + z*(\
                                B08 + z*(\
                                    B09 + z*(\
                                        B10 + z*B11\
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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.8696044010893586188149894498320793822322123540839E+00L)
#define A01 (+3.3611556953463411423038147732549181402391173718814E-01L)
#define A02 (-2.6395996509552376117694526447225286698291311106963E+01L)
#define A03 (-8.8404302205041018565415153362534058206366246700334E-01L)
#define A04 (+2.4425947658558227620124470701094690984004265331482E+01L)
#define A05 (+7.7807008873614677161917503877382592864599252694153E-01L)
#define A06 (-9.1333553471794085831034377649213360195940157861944E+00L)
#define A07 (-2.3827564891375786638277396552246213998649951100665E-01L)
#define A08 (+1.2268896488504476129882210531539940955303642635140E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+3.4055627345867617270299198114058820234177947568578E-02L)
#define B02 (+6.1539452392959077336386105306706584347184065380799E-01L)
#define B03 (+2.2466237793433823451350176083999842716739704942464E-02L)
#define B04 (+1.7013982744090735168387641203505724531651026054078E-01L)
#define B05 (+5.3091555559959167755895073346679721001466979235500E-03L)
#define B06 (+2.2141249949279602343135239267272529515200933555946E-02L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) \
B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*(B05 + z*B06)))))

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the squared cosine window via a rational Remez expansion.        */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Coss_Tail_End(const long double x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const long double shift = x - 0.5L;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const long double numer = TMPL_NUM_EVAL(shift);
    const long double denom = TMPL_DEN_EVAL(shift);

    /*  The squared cosine window is the ratio scaled by the translation.     */
    return shift * shift * numer / denom;
}
/*  End of tmpl_LDouble_Coss_Tail_End.                                        */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
