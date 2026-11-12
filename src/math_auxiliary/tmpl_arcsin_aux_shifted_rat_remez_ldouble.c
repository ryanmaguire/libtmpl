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

/******************************************************************************
 *                           64-Bit Double Version                            *
 ******************************************************************************/

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

/*  Helper macro for evaluating the numerator using Horner's method.          */
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

/*  Helper macro for evaluating the denominator using Horner's method.        */
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

/*  asin(5/8) split into a high and low part for extra accuracy.              */
#define ASIN_5_8_HI (+6.75131532937031653140991238615243E-01L)
#define ASIN_5_8_LO (-5.93193497332085475014956678498079E-18L)

/*  128-bit double-double, degrees (10, 8) and (11, 9).                       */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                       128-Bit Double-Double Version                        *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez approximation on [1/2, 5/8].  */
#define A00 (+6.5341016883920761535552448276552879509732571535508E-02L)
#define A01 (-1.2291374265473019675713742496055274765616261484834E-01L)
#define A02 (-9.0670304876985927828024361733727683188296212110123E+00L)
#define A03 (-5.9866222800781088351942421032879810062534834210284E+01L)
#define A04 (-1.5967937328524840259901771969793308864657305813411E+02L)
#define A05 (-1.6524605615233600128326301176197867065270089512722E+02L)
#define A06 (+1.9079067136806446331046295624114863668544977815933E+01L)
#define A07 (+1.1954250083750161819281152354483574722828861796998E+02L)
#define A08 (+1.7129376229885496532234540041115921228359490890122E+01L)
#define A09 (-2.3493471644015008203275447728018736904559718727021E+01L)
#define A10 (-3.8013713404382881957413411891016196012851600616188E-01L)
#define A11 (+2.4898769393964537559952992997093563885943681911186E-01L)

/*  Coefficients for the denominator of the Remez approximation on [1/2, 5/8].*/
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.5631165667463271460770748188743098325984627971035E+01L)
#define B02 (+9.7848376749369714161839520738153876279739032627125E+01L)
#define B03 (+3.0806469053148539782527562680832308640487597908327E+02L)
#define B04 (+4.8810245426720196779378961001988932521303796464485E+02L)
#define B05 (+2.8477500057143670442105382221785315510464847714813E+02L)
#define B06 (-1.4108857401930068725025182570999159062974041233695E+02L)
#define B07 (-1.9576160393039339456110181375903086627536394807968E+02L)
#define B08 (-3.6604189755674091911030892244250910353241197749787E+00L)
#define B09 (+2.6841221163551966181974755198500093790677025201496E+01L)

/*  Coefficients for the numerator of the Remez approximation on [5/8, 3/4].  */
#define C00 (-6.3981393330970735160656158377689082354522579762608E-03L)
#define C01 (-6.5632848308457998921993618350995290357988178056732E-01L)
#define C02 (-4.6505330689420247821197816337067186296761597119773E+00L)
#define C03 (-1.1650086101359377776667836790523097483681039347663E+01L)
#define C04 (-9.5468154363147445739210373032935758125025511874307E+00L)
#define C05 (+4.4918697291165970613347080597392010360060001429707E+00L)
#define C06 (+8.2926159703665373174593708136741492034436559344830E+00L)
#define C07 (+1.5898082689643620113943083227375161314002045579677E-01L)
#define C08 (-1.6071369212472935682076704089848377159280292600452E+00L)
#define C09 (-1.1264878976648988517600745976151959819050900759581E-02L)
#define C10 (+1.6882077604937003396100128124341878445678726282160E-02L)

/*  Coefficients for the denominator of the Remez approximation on [5/8, 3/4].*/
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (+8.9955163067719489299362939984581340007827303866605E+00L)
#define D02 (+3.0453561200250260428288343320626565189028370128129E+01L)
#define D03 (+4.5265148707242004700311819956401799302863607199788E+01L)
#define D04 (+1.9759492589206643551508286834449146389949896250863E+01L)
#define D05 (-1.7764683800732761519222194487113477921332178900219E+01L)
#define D06 (-1.5900285124416890478103110095945912349324836774670E+01L)
#define D07 (+9.1971082551675868513120260069448758107150601848626E-01L)
#define D08 (+2.0863256545046779621795896764154167816528479200745E+00L)

/*  Macro for evaluating the numerator on [1/2, 5/8] using Horner's method.   */
#define TMPL_POLYA_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * (\
                                A08 + z * (\
                                    A09 + z * (\
                                        A10 + z * A11\
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

/*  Macro for evaluating the denominator on [1/2, 5/8] using Horner's method. */
#define TMPL_POLYB_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * (\
                        B06 + z * (\
                            B07 + z * (\
                                B08 +  z * B09\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Macro for evaluating the numerator on [5/8, 3/4] using Horner's method.   */
#define TMPL_POLYC_EVAL(z) \
C00 + z * (\
    C01 + z * (\
        C02 + z * (\
            C03 + z * (\
                C04 + z * (\
                    C05 + z * (\
                        C06 + z * (\
                            C07 + z * (\
                                C08 + z * (\
                                    C09 + z * C10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Macro for evaluating the denominator on [5/8, 3/4] using Horner's method. */
#define TMPL_POLYD_EVAL(z) \
D00 + z * (\
    D01 + z * (\
        D02 + z * (\
            D03 + z * (\
                D04 + z * (\
                    D05 + z * (\
                        D06 + z * (\
                            D07 + z * D08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  asin(9/16) split as hi + lo for extra precision.                          */
#define ASIN_9_16_HI (+5.9740641664535021430381036628424296539958684123571E-01L)
#define ASIN_9_16_LO (+5.6785774839183500611054108423192290842024515433612E-33L)

/*  asin(11/16) split as hi + lo for extra precision.                         */
#define ASIN_11_16_HI (+7.580407654262359604569723109811356755131844294362E-01L)
#define ASIN_11_16_LO (-2.758756603230145709546291556273057119332963550840E-33L)

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                         128-Bit Quadruple Version                          *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez approximation on [1/2, 5/8].  */
#define A00 (+6.5341016883920761535552448276562260944827642296593E-02L)
#define A01 (-5.9014691975229633549372571160545044361341070894985E-02L)
#define A02 (-9.2312160204101558171261211612296316146593624053939E+00L)
#define A03 (-6.8542677381877064608323909151311997675035001957814E+01L)
#define A04 (-2.1259252618506729277357362825445114175406102851070E+02L)
#define A05 (-2.9478335101678557907387237861605869642060256015183E+02L)
#define A06 (-1.0018137003759209133761754411389341449254163488257E+02L)
#define A07 (+1.3802877014092731994360031870582824512780787556914E+02L)
#define A08 (+8.8041914678226714605225139919552693591595620893306E+01L)
#define A09 (-1.7020738278375368234747144557382223442156247442045E+01L)
#define A10 (-9.4997632454041447084201249140084902339784429162115E+00L)
#define A11 (+2.1136564236214937092698779203232442168302167058721E-01L)

/*  Coefficients for the denominator of the Remez approximation on [1/2, 5/8].*/
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+1.6609097351523501627738169191480563960316492349783E+01L)
#define B02 (+1.1246143916157705706426731173351843659531628271934E+02L)
#define B03 (+3.9488052841128649055548477882946506290958351596275E+02L)
#define B04 (+7.4516180835560471597512321305471807322186378502946E+02L)
#define B05 (+6.6345463477947045791549610977936640787236656390363E+02L)
#define B06 (+6.1738827894018241877917998903342450695260179950456E+01L)
#define B07 (-2.8387627788099303302390767612515416444513320870935E+02L)
#define B08 (-1.1047434452293182576141975043609876644233159712504E+02L)
#define B09 (+2.5265230299312793606607608378640330187126383373348E+01L)
#define B10 (+9.2350684079180288846077955243991626940281788645077E+00L)

/*  Coefficients for the numerator of the Remez approximation on [5/8, 3/4].  */
#define C00 (-6.3981393330970735160656158377701055323301607793327E-03L)
#define C01 (-6.5874456779969932199038077868465632805153486067624E-01L)
#define C02 (-4.8949969473266287194438162349586304670577268128089E+00L)
#define C03 (-1.3063625955002220018796316053454939744535932939923E+01L)
#define C04 (-1.1912967801017423583608188863609562102998750486348E+01L)
#define C05 (+4.7028495245986305635493283980789633312127300705485E+00L)
#define C06 (+1.1234575794945549311848168838168495721456213180623E+01L)
#define C07 (+7.2463184110219088759978250690953747506786022952037E-01L)
#define C08 (-2.6763617999345452188806605298363840611194193681005E+00L)
#define C09 (-5.0446495532468075651450688391323982317867471225833E-02L)
#define C10 (+5.7430556124676316219381208727363165743503602035595E-02L)
#define C11 (-4.9914532135121972412507031740921715688247566942843E-03L)
#define C12 (+3.0153280540543875948394934117328274581121472109468E-03L)

/*  Coefficients for the denominator of the Remez approximation on [5/8, 3/4].*/
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (+9.3731393295500112681851885414946808529508373101082E+00L)
#define D02 (+3.3322061113236517255777063843916302200318413768488E+01L)
#define D03 (+5.2668940293703321804616641977509482885457734534282E+01L)
#define D04 (+2.5561108997537698254060833350885461412341768367796E+01L)
#define D05 (-2.2167953341702072246325970242597817204150883259219E+01L)
#define D06 (-2.2878298300627253100248340501505564367269891829004E+01L)
#define D07 (+9.9970864776726046785164104310707119909558178987040E-01L)
#define D08 (+3.7320503983151579567755672282033686318279350193445E+00L)

/*  Macro for evaluating the numerator on [1/2, 5/8] using Horner's method.   */
#define TMPL_POLYA_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * (\
                            A07 + z * (\
                                A08 + z * (\
                                    A09 + z * (\
                                        A10 + z*A11\
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

/*  Macro for evaluating the denominator on [1/2, 5/8] using Horner's method. */
#define TMPL_POLYB_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * (\
                    B05 + z * (\
                        B06 + z * (\
                            B07 + z * (\
                                B08 + z * (\
                                    B09 + z * B10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Macro for evaluating the numerator on [5/8, 3/4] using Horner's method.   */
#define TMPL_POLYC_EVAL(z) \
C00 + z * (\
    C01 + z * (\
        C02 + z * (\
            C03 + z * (\
                C04 + z * (\
                    C05 + z * (\
                        C06 + z * (\
                            C07 + z * (\
                                C08 + z * (\
                                    C09 + z * (\
                                        C10 + z * (\
                                            C11 + z * C12\
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

/*  Macro for evaluating the denominator on [5/8, 3/4] using Horner's method. */
#define TMPL_POLYD_EVAL(z) \
D00 + z * (\
    D01 + z * (\
        D02 + z * (\
            D03 + z * (\
                D04 + z * (\
                    D05 + z * (\
                        D06 + z * (\
                            D07 + z * D08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  asin(9/16) split as hi + lo for extra precision.                          */
#define ASIN_9_16_HI (+5.9740641664535021430381036628424864689292278358147E-01L)
#define ASIN_9_16_LO (-2.9158520239957054097240883063065054849483188742363E-36L)

/*  asin(11/16) split as hi + lo for extra precision.                         */
#define ASIN_11_16_HI (+7.580407654262359604569723109811328829147650679442E-01L)
#define ASIN_11_16_LO (+3.384181613134627738487646047508749254728383907194E-35L)

#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  Coefficients for the numerator of the Remez approximation on [1/2, 5/8].  */
#define A00 (+6.5341016883920761517741897193393863415315680144456E-02L)
#define A01 (-5.4282343235174453368557328746999522003780680277491E-01L)
#define A02 (-6.2534881128884596185825061993819840372318327521099E+00L)
#define A03 (-1.4108061136007547100791006610032673714987256022600E+01L)
#define A04 (-3.9504982174280577679683873767051898512758266965609E+00L)
#define A05 (+7.8467381598620709879811926248153953133884915665171E+00L)
#define A06 (+4.0983077729516575548259416427065999772411392280371E-01L)
#define A07 (-3.0726601345053402013324585467011146845384451886692E-01L)

/*  Coefficients for the denominator of the Remez approximation on [1/2, 5/8].*/
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+9.2047323224942164100073090291118672991074185762886E+00L)
#define B02 (+2.8366254476407675819643593463508863819468857243496E+01L)
#define B03 (+3.0148176395278143639184598012708875700566175230216E+01L)
#define B04 (-1.0096761064584672994153685604498038745057569693581E+00L)
#define B05 (-1.0974581159135158911916456013943039025334213623449E+01L)

/*  Coefficients for the numerator of the Remez approximation on [5/8, 3/4].  */
#define C00 (-6.3981393330970735393258438023827812172940579325597E-03L)
#define C01 (-6.3258233597189036024639058358760438028465916023399E-01L)
#define C02 (-2.2873635264235380838062002046737774991769498569010E+00L)
#define C03 (-1.6493162450263219913382916659442478506389228758900E+00L)
#define C04 (+1.0263412103420186399938856664734339872503782234081E+00L)
#define C05 (+6.2662403866083409197115434966083619831041056608908E-01L)
#define C06 (-5.0014098879217837032131789335238885051201608678191E-02L)

/*  Coefficients for the denominator of the Remez approximation on [5/8, 3/4].*/
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (+5.2841018038316015955423298979561486389054096156468E+00L)
#define D02 (+8.4360123556887275003043624356100493189940129229661E+00L)
#define D03 (+2.9005753356125637631384251177022144363495363178383E+00L)
#define D04 (-2.1738288657565720304777269782827116578618999801325E+00L)
#define D05 (-7.9173372870994893038505920603328297394038662845588E-01L)

/*  Macro for evaluating the numerator on [1/2, 5/8] using Horner's method.   */
#define TMPL_POLYA_EVAL(z) \
A00 + z * (\
    A01 + z * (\
        A02 + z * (\
            A03 + z * (\
                A04 + z * (\
                    A05 + z * (\
                        A06 + z * A07\
                    )\
                )\
            )\
        )\
    )\
)

/*  Macro for evaluating the denominator on [1/2, 5/8] using Horner's method. */
#define TMPL_POLYB_EVAL(z) \
B00 + z * (\
    B01 + z * (\
        B02 + z * (\
            B03 + z * (\
                B04 + z * B05\
            )\
        )\
    )\
)

/*  Macro for evaluating the numerator on [5/8, 3/4] using Horner's method.   */
#define TMPL_POLYC_EVAL(z) \
C00 + z * (\
    C01 + z * (\
        C02 + z * (\
            C03 + z * (\
                C04 + z * (\
                    C05 + z * C06\
                )\
            )\
        )\
    )\
)

/*  Macro for evaluating the denominator on [5/8, 3/4] using Horner's method. */
#define TMPL_POLYD_EVAL(z) \
D00 + z * (\
    D01 + z * (\
        D02 + z * (\
            D03 + z * (\
                D04 + z * D05\
            )\
        )\
    )\
)

/*  asin(9/16) split as hi + lo to extra precision.                           */
#define ASIN_9_16_HI (+5.9740641664535021430068942316360391941998386755586E-01L)
#define ASIN_9_16_LO (+3.1209431206447245570868920299111876808760390972139E-21L)

/*  asin(11/16) split as hi + lo to extra precision.                          */
#define ASIN_11_16_HI (+7.580407654262359604373927579601399884268175810575E-01L)
#define ASIN_11_16_LO (+1.957955302099292832976361823296605795255258622173E-20L)

#endif

/*  64-bit long double uses one interval, the same as double.                 */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

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

/*  The other formats split the interval at 5/8.                              */
#else

TMPL_CONST_FUNC
TMPL_ALWAYS_INLINE
long double
tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez(const long double x)
TMPL_UNSEQUENCED
{
    /*  Left half, 1/2 <= x < 5/8, centered at 9/16.                          */
    if (x < 0.625L)
    {
        /*  Both differences are exact by the Sterbenz lemma.                 */
        const long double h = x - 0.5625L;
        const long double s = 0.625L - x;

        /*  Evaluate the rational Remez approximation using Horner's method.  */
        const long double num = TMPL_POLYC_EVAL(s);
        const long double den = TMPL_POLYD_EVAL(s);
        const long double rat = num / den;

        /*  Compute asin(x) from the rational approximation.                  */
        const long double low_bits = ASIN_9_16_LO + h * rat;
        return ASIN_9_16_HI + (1.25L * h + low_bits);
    }

    /*  Right half, 5/8 <= x <= 3/4, centered at 11/16.                       */
    else
    {
        /*  Different shift factor for the right half of the interval.        */
        const long double h = x - 0.6875L;
        const long double s = 0.75L - x;

        /*  Evaluate the rational Remez approximation using Horner's method.  */
        const long double num = TMPL_POLYA_EVAL(s);
        const long double den = TMPL_POLYB_EVAL(s);
        const long double rat = num / den;

        /*  Compute asin(x) from the rational approximation.                  */
        const long double low_bits = ASIN_11_16_LO + h * rat;
        return ASIN_11_16_HI + (1.375L * h + low_bits);
    }
}
/*  End of tmpl_LDouble_Arcsin_Aux_Shifted_Rat_Remez.                         */

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT.                      */

/*  Undefine everything to avoid collisions with other macros.                */
#include <libtmpl/include/tmpl_math_undef.h>

#undef ASIN_5_8_HI
#undef ASIN_5_8_LO
#undef ASIN_9_16_HI
#undef ASIN_9_16_LO
#undef ASIN_11_16_HI
#undef ASIN_11_16_LO
