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
 *                  tmpl_arcsin_aux_shifted_rat_remez_ldouble                 *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      centered about 5/8 on the interval [1/2, 3/4].                        *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez                             *
 *  Purpose:                                                                  *
 *      Computes a degree (6, 6) rational Remez approximation for asin(x)     *
 *      on the interval [1/2, 3/4] by shifting the input by 5/8.              *
 *  Arguments:                                                                *
 *      x (const long double):                                                *
 *          A real number in the interval [1/2, 3/4].                         *
 *  Output:                                                                   *
 *      asin_x (long double):                                                 *
 *          asin(x) to long double precision.                                 *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      The coefficients for the degree (M, N) rational Remez approximation   *
 *      on the interval [-1/8, 1/8] for the function                          *
 *                                                                            *
 *                 asin(h + 5/8) - asin(5/8)                                  *
 *          f(h) = -------------------------                                  *
 *                             h                                              *
 *                                                                            *
 *      have been pre-computed. asin(x) is computed by setting x = 5/8 + h    *
 *      and evaluating                                                        *
 *                                                                            *
 *          asin(x) = asin(5/8) + h * (5/4 + r(h))                            *
 *                  = asin_5_8_hi + (5/4 * h + (asin_5_8_lo + h * r(h)))      *
 *                                                                            *
 *      where r is the rational Remez approximation, and asin(5/8) is split   *
 *      into asin_5_8_hi + asin_5_8_lo for improved accuracy. The degree of   *
 *      the approximation depends on how long double is implemented:          *
 *                                                                            *
 *                                                                            *
 *          long double           |  M |  N                                   *
 *          --------------------------------                                  *
 *          64-bit double         |  6 |  6                                   *
 *          80-bit extended       |  8 |  7                                   *
 *          128-bit double-double | 12 | 12                                   *
 *          128-bit quadruple     | 14 | 12                                   *
 *                                                                            *
 *      r(h) is computed by shifting h into the interval [0, 1/4] using       *
 *      x_shift = 3/4 - x. This is done to avoid large coefficients with      *
 *      alternating signs in the numerator and denominator for the rational   *
 *      Remez approximation. Performing this extra shift let's us keep the    *
 *      error under 1 ULP.                                                    *
 *  Notes:                                                                    *
 *      1.) Accurate to long double precision for 1/2 <= x <= 3/4. There are  *
 *          no checks that the input falls within this interval.              *
 *  References:                                                               *
 *      1.) Maguire, Ryan (2024)                                              *
 *          tmpld                                                             *
 *          https://github.com/ryanmaguire/libtmpl_data                       *
 *                                                                            *
 *          Python library providing an implementation of the rational        *
 *          Remez exchange algorithm. The coefficients for the                *
 *          approximation used by this function were computed using this.     *
 *                                                                            *
 *      2.) Tasissa, Abiy (2019)                                              *
 *          Function Approximation and the Remez Exchange Algorithm.          *
 *          https://sites.tufts.edu/atasissa/files/2019/09/remez.pdf          *
 *                                                                            *
 *          Survey of the Remez polynomial and Remez exchange algorithm.      *
 *          The implementation in tmpld is based on these notes.              *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_config.h:                                                        *
 *          Header file containing the TMPL_ALWAYS_INLINE macro.              *
 *  2.) tmpl_attributes.h:                                                    *
 *          Header with macros for C23 attributes on supported compilers.     *
 *  3.) tmpl_math_auxiliary.h:                                                *
 *          Contains the function prototype / forward declaration.            *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       October 6, 2026                                               *
 ******************************************************************************/

/*  Location of the TMPL_ALWAYS_INLINE macro.                                 */
#include <libtmpl/include/tmpl_config.h>

/*  Macros providing C23 attributes (for optimization) are found here.        */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function prototype / forward declaration found here.                      */
#include <libtmpl/include/tmpl_math_auxiliary.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.3344436835559469595933260383708100557742108606499E-01L)
#define A01 (-1.6764774733355302248522602489702722880532643594747E-01L)
#define A02 (-3.5483641492619427301139507242315868891809665125055E+00L)
#define A03 (-1.3897446385017834603076922677961123507848059825378E+00L)
#define A04 (+1.3348516580316006893470465900994667135492646210811E+01L)
#define A05 (+5.2807480383099683013151527604578390929860834130040E+00L)
#define A06 (-6.2271380776933370302536180921122423699654126877916E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+6.4420885850039326272682541583381673295089182072854E+00L)
#define B02 (+6.9023983022068339899286855265441000748317061377661E+00L)
#define B03 (-2.2098631522653329372202851046373866129795990784743E+01L)
#define B04 (-3.7978626734498617105101775346011213398588421323294E+01L)
#define B05 (-1.8672873962820900652152782607054696985961999966209E+00L)
#define B06 (+8.4500371338110282128410268906438815961749159794093E+00L)

#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * A06\
                )\
            )\
        )\
    )\
)

#define TMPL_DEN_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * B06\
                )\
            )\
        )\
    )\
)

#define ASIN_5_8_HI (+6.75131532937031653140991238615243E-01L)
#define ASIN_5_8_LO (-5.93193497332085475014956678498079E-18L)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.3344436835559488675110458963224425829756427871242E-01L)
#define A01 (+1.4432489389833630561116777119205266014377969479991E+00L)
#define A02 (+2.1705533446821069971290125825689899385441903675581E+00L)
#define A03 (-3.3612498892118720144089729173435559032852719444142E+01L)
#define A04 (-1.9683205243516337240965566244985396785829502658641E+02L)
#define A05 (-4.3491357864009459743210778892706386827484084245759E+02L)
#define A06 (-3.5001851297826546324182075351281887121720732956880E+02L)
#define A07 (+1.4079531982871689292549368295521108829585919579001E+02L)
#define A08 (+3.2345804769889105130791377369575292664921246296857E+02L)
#define A09 (+3.2084880641438798934412545329198092822154053242806E+01L)
#define A10 (-8.3784937160322479968867844832494679501086137065310E+01L)
#define A11 (-7.2706139801413565957103058840088413562708419205014E+00L)
#define A12 (+5.9582615484203163925331759432097089871010609054993E+00L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.8513760894356189872335054216947684147066092952682E+01L)
#define B02 (+1.4269115837433291877003310445786486650670448105659E+02L)
#define B03 (+5.8742456829072503291588001164878340689123561023814E+02L)
#define B04 (+1.3626269665414564761805649236260095073245046519714E+03L)
#define B05 (+1.6544115823830376313835507696758837799399454668814E+03L)
#define B06 (+6.0680763306247232326867394533858136968446744483234E+02L)
#define B07 (-7.1317167308271885369059808952104665386999903590082E+02L)
#define B08 (-6.5719629286095873205182497573065085631832169096869E+02L)
#define B09 (+3.2981578154346551123765803609880326362885556313604E+01L)
#define B10 (+1.3210610133768997454724099459067963682382321936238E+02L)
#define B11 (+4.0408232682803461022257443609411010759372904976071E+00L)
#define B12 (-6.3597514912207880865019662984823408940812285068241E+00L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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

#define ASIN_5_8_HI (+6.75131532937031647209056265294393919000292301254667E-01L)
#define ASIN_5_8_LO (-5.90479610695000498778262158015095439734389108052690E-33L)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.3344436835559488675110458963224048655194936205650E-01L)
#define A01 (+1.5289040398916662831537513122357556721913201038424E+00L)
#define A02 (+2.9615675801470201872008967002314852263828655247688E+00L)
#define A03 (-3.3443058767473085431705431966894592489248193637762E+01L)
#define A04 (-2.1860164411149422608210542886228086913547374617175E+02L)
#define A05 (-5.2801681300438891512061176299841261258795858623880E+02L)
#define A06 (-4.8686772291692249535009114702554760961594589089005E+02L)
#define A07 (+1.4111213876657078877077040130448458850841265869017E+02L)
#define A08 (+4.8350154523015787486276362726287666693228792611168E+02L)
#define A09 (+8.9992846797916480844917170454895132512691003825601E+01L)
#define A10 (-1.5124004029942163165877773265302640150032921694298E+02L)
#define A11 (-2.4708234712057243393417184741003639906249802905996E+01L)
#define A12 (+1.6835873586557259945215652259307024592780971619479E+01L)
#define A13 (+1.9164157263517335427168350378294975823782348904343E-01L)
#define A14 (-8.5201932870017569106987468363752858773724353846614E-02L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.9155639618530254938996042360280054905085931894380E+01L)
#define B02 (+1.5356026827620586084230356866207187219514398395667E+02L)
#define B03 (+6.6203431683861678284456474844915177687637334585077E+02L)
#define B04 (+1.6238351055826313479904948180355321150651368094848E+03L)
#define B05 (+2.1202382601632001270153154482161330602849507735275E+03L)
#define B06 (+9.0155175661300908187183662225402598224993084411101E+02L)
#define B07 (-9.6799526699732633573384746665083727151657782402125E+02L)
#define B08 (-1.0651195171805147213665563520626743773993863034522E+03L)
#define B09 (+1.3931310488061379377523723016382282675760706343098E+01L)
#define B10 (+2.6702099107981942585753524152767733567324995972831E+02L)
#define B11 (+1.7357434026945270978283546121971534343186962625645E+01L)
#define B12 (-2.0082874602278024689012925609002360865412439155710E+01L)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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

/*  Helper macro for evaluating a polynomial via Horner's method.             */
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

#define ASIN_5_8_HI (+6.75131532937031647209056265294388044913961920185316E-01L)
#define ASIN_5_8_LO (-3.07097765689356367826215801509544226398766044411917E-35L)

#else

/*  Coefficients for the numerator of the rational Remez approximation.       */
#define A00 (+1.3344436835559488674272523354830133052328931438647E-01L)
#define A01 (+4.1648480576425124516016476139186352198394133921637E-01L)
#define A02 (-3.3339327713898081215997492427855377654242618274041E+00L)
#define A03 (-1.6175906200679487739236749388013394716147482582906E+01L)
#define A04 (-1.7271359093769215018984627828872456339815644167677E+01L)
#define A05 (+5.6541471863424443540910573498084693530588036017352E+00L)
#define A06 (+8.7346138519661185657087615593000482659962845289830E+00L)
#define A07 (-1.4614086098447224036644626387247117366456394664595E+00L)
#define A08 (-1.8448928160413506909712709763286568636641937928219E-01L)

/*  Coefficients for the denominator of the rational Remez approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.0819437440532722732779437366728220135107576779454E+01L)
#define B02 (+4.2207880003719609801632374419236425079022615235873E+01L)
#define B03 (+6.8414383703567093631482407903144931377951738031114E+01L)
#define B04 (+3.1206216569241222837334513633121663810320133912495E+01L)
#define B05 (-2.0297401955874299438742385064393351453679113426964E+01L)
#define B06 (-1.1502161611716045882908383206842091084734440641707E+01L)
#define B07 (+2.0045714616986740970716226759191125930296327978622E+00L)

#define TMPL_NUM_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * A08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)


#define TMPL_DEN_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * (\
                        B06 + z * B07\
                    )\
                )\
            )\
        )\
    )\
)

#define ASIN_5_8_HI (+6.75131532937031647232089398569243599013134371489286E-01L)
#define ASIN_5_8_LO (-2.30331332748555848089490202396072053510723384544148E-20L)

#endif

/*  Computes a degree (10, 8) Remez approximation for (asin(x) - x) / x.      */
TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  asin(5/8) to extra precision using two long doubles.                  */
    const long double asin_three_eigths_hi = ASIN_5_8_HI;
    const long double asin_three_eigths_lo = ASIN_5_8_LO;

    /*  The approximation is centered at 5/8 and evaluated in powers of       *
     *  3/4 - x. For 1/2 <= x <= 3/4 both differences are exact.              */
    const long double center = x - 0.625L;
    const long double x_shift = 0.75L - x;

    /*  Evaluate the rational Remez approximation using Horner's method.      */
    const long double p = TMPL_NUM_EVAL(x_shift);
    const long double q = TMPL_DEN_EVAL(x_shift);
    const long double rat = p / q;

    /*  Evaluate asin(x) using the Remez expansion.                           */
    const long double low_bits = asin_three_eigths_lo + center * rat;
    return asin_three_eigths_hi + (1.25L * center + low_bits);
}
/*  End of tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez.                         */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>

#undef ASIN_5_8_HI
#undef ASIN_5_8_LO
