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
 *                        tmpl_kbmd20_rat_remez_ldouble                       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) for small x.   *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_KBMD20_Rat_Remez                                         *
 *  Purpose:                                                                  *
 *      Computes the modified Kaiser-Bessel window (alpha = 2) using a        *
 *      rational Remez approximation for small arguments.                     *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number, the input for the window.                          *
 *  Output:                                                                   *
 *      kbmd20_x (long double):                                               *
 *          The modified Kaiser-Bessel window (alpha = 2) of x.               *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the (N, M) rational Remez approximation for the  *
 *      modified Kaiser-Bessel window (alpha = 2) have been pre-computed on   *
 *      the interval [-1/4, 1/4], where N and M depend on how long double is  *
 *      implemented:                                                          *
 *                                                                            *
 *          Implementation        | Numerator | Denominator                   *
 *          -----------------------------------------------                   *
 *          64-bit double         |        10 |           8                   *
 *          80-bit extended       |        10 |          10                   *
 *          128-bit double-double |        16 |          14                   *
 *          128-bit quadruple     |        16 |          16                   *
 *                                                                            *
 *      Since the window is an even function, half of the coefficients are    *
 *      zero, meaning we only have (N / 2) + 1 non-zero terms in the          *
 *      numerator and (M / 2) + 1 non-zero terms in the denominator. The      *
 *      approximation is performed using Horner's method for the numerator    *
 *      and denominator, and then returning the ratio.                        *
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
 *  Date:       February 19, 2026                                             *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_KBMD20_RAT_REMEZ_LDOUBLE_H
#define TMPL_KBMD20_RAT_REMEZ_LDOUBLE_H

/*  Location of the TMPL_STATIC_INLINE and TMPL_LDOUBLE_TYPE macros.          */
#include <libtmpl/include/tmpl_config.h>

/*  The degrees of the polynomials depend on how long double is implemented.  */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+9.9999999999999999366600378259771379869378926410852E-01L)
#define A01 (-9.4212661861610618389182687877338447490565358937343E+00L)
#define A02 (+3.2924950968533714211260399764822484280641871514011E+01L)
#define A03 (-5.5478200884536421439946455007527188358710270248590E+01L)
#define A04 (+4.5955380454711921805431324786962958768702779852283E+01L)
#define A05 (-1.5523654895689552074358932031563523118063969102151E+01L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+2.2301555070371895676893883291386650151597404400153E+00L)
#define B02 (+2.3384956231098968317299016143783847487680799293970E+00L)
#define B03 (+1.4039036477276375600119534981510529794871571385465E+00L)
#define B04 (+4.2233936108924244735545866013547998564883503796379E-01L)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*A05))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*B04)))

/*  128-bit double-double, more terms needed.                                 */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                           128-bit Double-Double                            *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.0000000000000000000000000000000034563025678006611E+00L)
#define A01 (-1.0091505005974699379544702128563007715526664784994E+01L)
#define A02 (+3.9597330129134156700538270960621394808778839999417E+01L)
#define A03 (-8.0953886134171812914054790937857717533295862697707E+01L)
#define A04 (+9.5238443149851089102128428001646580004469355285465E+01L)
#define A05 (-6.7146721205845522323249309871167476852038182626868E+01L)
#define A06 (+2.8209729432656769892501102997384969399611193950781E+01L)
#define A07 (-6.5854392182392094755456095551464738526261621374722E+00L)
#define A08 (+6.6800711076468822035823259759422696865896150962689E-01L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.5599166872235728149222395214973349486783832160585E+00L)
#define B02 (+1.2016396588991224831461317320396458385944073260891E+00L)
#define B03 (+5.9826860932579918863882658952658586930760793392698E-01L)
#define B04 (+2.1022164110674232188867142253437771372828303328445E-01L)
#define B05 (+5.2806128170098720179091684652379780208408222678708E-02L)
#define B06 (+8.9143062696442953646256555665902356594905318336183E-03L)
#define B07 (+7.9469081581704783889338951648639471396765324644113E-04L)

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
                        B06 + z*B07\
                    )\
                )\
            )\
        )\
    )\
)

/*  128-bit quadruple, one more term than double-double.                      */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                             128-bit Quadruple                              *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+9.9999999999999999999999999999999998824478964158362E-01L)
#define A01 (-1.0022944909047322467807741309737278004882811458971E+01L)
#define A02 (+3.8924133329676717563361582255092760094032837962369E+01L)
#define A03 (-7.8424175540514372090433056058077625530380342106964E+01L)
#define A04 (+9.0393537213583232553078361807103479868938586843691E+01L)
#define A05 (-6.1995061691036143451054443153033171036838097889284E+01L)
#define A06 (+2.5113100933261497376829550862285317525246220621362E+01L)
#define A07 (-5.5925762907761848015763622983454544496596300171954E+00L)
#define A08 (+5.3413674214789451440909413299398997474208375089896E-01L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.6284767841509497266592003402943166166142477306907E+00L)
#define B02 (+1.3272654600690989018394719038135678659780710481946E+00L)
#define B03 (+7.1318942287760298706888636350042146088699785257616E-01L)
#define B04 (+2.7901477869418640558177069109918756948981806820239E-01L)
#define B05 (+8.2285712202315238468305030134846236394192684534209E-02L)
#define B06 (+1.8095866656842530525327900972277110411304819444320E-02L)
#define B07 (+2.7548187430174901107015573278106234425880568609133E-03L)
#define B08 (+2.2643399481981120947675174918672570390613744690213E-04L)

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

/*  Lastly, extended precision and portable versions.                         */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.0000000000000000000000937833831600619579685064491E+00)
#define A01 (-9.6911569510859905566416439755331198863590716170923E+00)
#define A02 (+3.5587336216442482775583641304501123649326016194640E+01)
#define A03 (-6.5451022645947606712772627523031795125105131104225E+01)
#define A04 (+6.4465245454445271446677347194093913332905637944711E+01)
#define A05 (-3.3074498733023520482508257973428569965925806156497E+01)
#define A06 (+7.1061710083493863218890093121531760174204619404719E+00)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define B01 (+1.9602647421122816382656270324730390913584919031512E+00)
#define B02 (+1.8562697577674827889132024110523068210305848730752E+00)
#define B03 (+1.0804386014016604310090126451340876635814445663672E+00)
#define B04 (+3.9509495822879977264576093174572081870869577613657E-01)
#define B05 (+7.4698604431351457479772425500363624729998674496715E-02)

/*  Helper macro for evaluating the numerator via Horner's method.            */
#define TMPL_NUM_EVAL(z) A00 + z*(A01 + z*(A02 + z*(A03 + z*(A04 + z*(A05+z*A06)))))

/*  Helper macro for evaluating the denominator via Horner's method.          */
#define TMPL_DEN_EVAL(z) B00 + z*(B01 + z*(B02 + z*(B03 + z*(B04 + z*B05))))

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Computes the modified Kaiser-Bessel window via a rational Remez expansion.*/
TMPL_STATIC_INLINE
long double tmpl_LDouble_KBMD20_Rat_Remez(const long double x)
{
    /*  The polynomials are in terms of x^2. Compute.                         */
    const long double x2 = x * x;

    /*  The numerator and denominator can be computed using Horner's method.  */
    const long double numer = TMPL_NUM_EVAL(x2);
    const long double denom = TMPL_DEN_EVAL(x2);

    /*  The modified Kaiser-Bessel window is the ratio.                       */
    return numer / denom;
}
/*  End of tmpl_LDouble_KBMD20_Rat_Remez.                                     */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */
