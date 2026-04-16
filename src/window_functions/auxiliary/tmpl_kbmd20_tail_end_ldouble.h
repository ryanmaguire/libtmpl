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
 *                        tmpl_kbmd20_tail_end_ldouble                        *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2).               *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_KBMD20_Tail_End                                          *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for 1 / 4 <= x <= 1 / 2.                 *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (long double):                                               *
 *          The Kaiser-Bessel window (alpha = 2) of x.                        *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The modified Kaiser-Bessel window can be expanded about x = 1 / 2 in  *
 *      terms of x - 1 / 2. The coefficients for the (N, M) rational Remez    *
 *      approximation for the function:                                       *
 *                                                                            *
 *                 KBMD20(x + 1 / 2)                                          *
 *          f(x) = -----------------                                          *
 *                         x                                                  *
 *                                                                            *
 *      on the interval [-1/4, 0] (the limit of f at zero is used to avoid a  *
 *      division by zero), where KBMD20 represents the modified Kaiser-Bessel *
 *      window with alpha = 2, have been pre-computed below. N and M depend   *
 *      on how long double is represented:                                    *
 *                                                                            *
 *          Implementation        | Numerator | Denominator                   *
 *          -----------------------------------------------                   *
 *          64-bit double         |         8 |           6                   *
 *          80-bit extended       |         8 |           8                   *
 *          128-bit double-double |        12 |          12                   *
 *          128-bit quadruple     |        14 |          12                   *
 *                                                                            *
 *      Given 1 / 4 <= x <= 1 / 2, we translate x into this interval using:   *
 *                                                                            *
 *                     1                                                      *
 *          t(x) = x - -                                                      *
 *                     2                                                      *
 *                                                                            *
 *      and then return t(x) * P(t(x)) / Q(t(x)), where P and Q are the       *
 *      numerator and denominator, respectively, for the degree (N, M)        *
 *      rational minimax approximation for f.                                 *
 *                                                                            *
 *      Note that since we scale the result by t(x), the approximation is     *
 *      exactly zero when x = 1 / 2. That is, the window goes to zero at the  *
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
 *  Date:       February 19, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_TAIL_END_LDOUBLE_H
#define TMPL_KBMD20_TAIL_END_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degrees of the polynomials depend on how long double is implemented.  */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847288850771500899519121342862207284106326971267E-01L)
#define A01 (+3.7703430459325869351666011886888007493805010737097E+00L)
#define A02 (-9.2748851460735770070873687837606018595281772953278E+00L)
#define A03 (-3.8267011521033769098516401710300698080047799965873E+00L)
#define A04 (+3.3241952707923226984534441308247753279970050447856E+01L)
#define A05 (-8.8023196313354674135314845279407756721537549999632E+00L)
#define A06 (-4.3525180967189236054858575836264308737025742917772E+01L)
#define A07 (+1.2013007956983332028738370656593394262634958622036E+01L)
#define A08 (+2.3806275613935762858840601619804706484041671686613E+01L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+6.4590537669403026293698188389403347665806182276329E-01L)
#define B02 (+2.4051579740584122995183821213142052648841929286432E+00L)
#define B03 (+1.2777876092667613335039744181571401022051044423763E+00L)
#define B04 (+2.3792291101954749461991531959571485074038718990322E+00L)
#define B05 (+8.1892168756447741399149509936664863887984649458537E-01L)
#define B06 (+9.2248073688651589231687136340824688169125570621861E-01L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
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
                    B05 + z*B06\
                )\
            )\
        )\
    )\
)

/*  128-bit double-double, more terms needed.                                 */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                           128-bit Double-Double                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847288850771499858078489078021537492833265455446E-01L)
#define A01 (+3.8304070782953068608132646180100697975442878156307E+00L)
#define A02 (-9.6330920760737561982159156373937321052867221986096E+00L)
#define A03 (-3.8263822289745975090239685299196876887564209391679E+00L)
#define A04 (+3.7131685465737556996019753699493371316178284655866E+01L)
#define A05 (-1.2648384834744389671645120082942089627829281669532E+01L)
#define A06 (-5.6335158419402989294518279686158640777635537849017E+01L)
#define A07 (+2.5836305494477370824080729839941537446415988620775E+01L)
#define A08 (+4.5062769260216020887044459086398250641423199315694E+01L)
#define A09 (-1.7559239156203839792200238830586425859539879425751E+01L)
#define A10 (-1.9618426050251743537883468936286880396472726951593E+01L)
#define A11 (+4.3301302265523161811340990234752164027819035778781E+00L)
#define A12 (+3.8137578819974222893803472088438037130496333670098E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+5.1489646893024622461538376392055428423871102925535E-01L)
#define B02 (+2.0244652871808327844583482589171184527670731983671E+00L)
#define B03 (+9.8624566145050726599650384061479530354073665171161E-01L)
#define B04 (+2.0037569283073864552904586851673993725096132966379E+00L)
#define B05 (+9.0152303353947868565354587459174302530493896296454E-01L)
#define B06 (+1.2478798042329174668541158822540837286318592500138E+00L)
#define B07 (+4.9656769050480589371328247385189583357717225941712E-01L)
#define B08 (+5.1626023552735541318313207922906950155122293821666E-01L)
#define B09 (+1.6616518455718910581829282643162555848607086929953E-01L)
#define B10 (+1.3319334672767330664002647760424601714889133533671E-01L)
#define B11 (+2.7093744599585277216382530575466003937609182863724E-02L)
#define B12 (+1.6095185235837203616182338777371068025899440468362E-02L)

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
                                        B10 + z*(\
                                            B11 + z*B12\
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

/*  128-bit quadruple needs two more terms than double-double.                */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                             128-bit Quadruple                              *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847288850771499858078489078020801140394891932787E-01L)
#define A01 (+3.8706474183851924127965209964873616090315977132097E+00L)
#define A02 (-9.8319105591237874432534768011881823944226910310655E+00L)
#define A03 (-4.1381273630774800927472395944410266419172179011056E+00L)
#define A04 (+4.0414696879690736091212603608532484530737878284083E+01L)
#define A05 (-1.4808755926946634885533278382471160928238470661796E+01L)
#define A06 (-6.6792943022925158599472411461624574740636858859990E+01L)
#define A07 (+3.5138933062357929905287928055541293905380028341713E+01L)
#define A08 (+6.0790094091045603259548534984152432760435126994508E+01L)
#define A09 (-3.0651903676083546252604078883761530786175708893676E+01L)
#define A10 (-3.3059371133462435742001425269782454921438109733190E+01L)
#define A11 (+1.2686767751084153849172730947902829325510711575263E+01L)
#define A12 (+1.0408801620011693933927949951764481781475246527201E+01L)
#define A13 (-2.1436572245078936195665941741016376033331336646462E+00L)
#define A14 (-1.5170096728401630923080372128245678203774089765452E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+4.2712608795774428436462763487213343302309402550272E-01L)
#define B02 (+1.6796304703890656012410302014128491952580705620144E+00L)
#define B03 (+6.7498044191031503646822700210386993423835126836981E-01L)
#define B04 (+1.3618768324553594959167271001831522984473851125767E+00L)
#define B05 (+5.0176419148531690040292879755428778641146482705241E-01L)
#define B06 (+6.8579484089813049194633473504514720483584844320128E-01L)
#define B07 (+2.2133393013598519706948909495768420085341171228389E-01L)
#define B08 (+2.2667884647980377809525977411345388198638310246893E-01L)
#define B09 (+5.8410175946636701172273478688585325697151369792746E-02L)
#define B10 (+4.6388635710180577959888701398657852696096968882448E-02L)
#define B11 (+7.4154825724831790799146144418074623225404886719271E-03L)
#define B12 (+4.4852501526834845786524521260017372918131891865642E-03L)

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
                                            A11 + z*(\
                                                A12 + z*(\
                                                    A13 + z*A14\
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
                                        B10 + z*(\
                                            B11 + z*B12\
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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (-4.5847288850771499859819148705902600542188565169189E-01L)
#define A01 (+3.7354080495939655805445280812424673219091514691267E+00L)
#define A02 (-9.1263456777439517898748561821330677435458253553074E+00L)
#define A03 (-3.4510328872269089369561063335690067415613636683710E+00L)
#define A04 (+3.0522037290013136406407909239471630117589943654322E+01L)
#define A05 (-7.7766816514931084261209843953371574833790389161825E+00L)
#define A06 (-3.6584933504905667488032775469687491329226818087248E+01L)
#define A07 (+9.1006891686145828177113243750679842065658020240886E+00L)
#define A08 (+1.7458027427611389178586109293332718481444204682122E+01L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+7.2210398562889750899253710025293864693932024664842E-01L)
#define B02 (+2.7570220275193878985028422804462565873221431298682E+00L)
#define B03 (+1.7845314672993180974281568560646411026164138266487E+00L)
#define B04 (+3.5137740750905700074960158374293895144139255060131E+00L)
#define B05 (+1.8769789023747790297710372202442699734202293306262E+00L)
#define B06 (+2.4221134445711898857181229477162156059873002299923E+00L)
#define B07 (+8.4169957292920663572462061248995811043661521447703E-01L)
#define B08 (+7.1101575144711553358807748806789211197588653762486E-01L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) \
A00 + z*(\
    A01 + z*(\
        A02 + z*(\
            A03 + z*(\
                A04 + z*(\
                    A05 + z*(\
                        A06 + z*(\
                            A07 + z*A08\
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
                            B07 + z*B08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
long double tmpl_LDouble_KBMD20_Tail_End(const long double x)
{
    /*  The polynomials are in terms of x - 1 / 2. Compute.                   */
    const long double shift = x - 0.5L;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const long double numer = TMPL_NUM_EVAL(shift);
    const long double denom = TMPL_DEN_EVAL(shift);

    /*  The Kaiser-Bessel window is the ratio scaled by the translation.      */
    return shift * numer / denom;
}
/*  End of tmpl_LDouble_KBMD20_Tail_End.                                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
