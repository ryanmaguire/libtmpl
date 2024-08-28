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
 *                tmpl_normalized_fresnel_cos_auxiliary_ldouble               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the normalized Fresnel cosine for large positive inputs.     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Normalized_Fresnel_Cos_Auxiliary                         *
 *  Purpose:                                                                  *
 *      Computes C(x) for large positive inputs.                              *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      C_x (long double):                                                    *
 *          The normalized Fresnel cosine of x.                               *
 *  Called Functions:                                                         *
 *      tmpl_math.h:                                                          *
 *          tmpl_LDouble_SinCosPi:                                            *
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
 *      xlo^2 is small, and sin and cos of this can be computed by a few      *
 *      terms from the Taylor series. cos(u) and sin(u) are computed using    *
 *      the angle sum formula.                                                *
 *  Notes:                                                                    *
 *      This function assumes the input is between 4 and 2^N, where           *
 *      N = floor(m / 3), m being the number of bits in the mantissa.         *
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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Splitting function for retreiving the high part of a double given here.   */
#if TMPL_USE_INLINE == 1
#include <libtmpl/include/split/tmpl_high_split_double.h>
#else
extern long double tmpl_LDouble_Even_High_Split(long double x);
#endif

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void
tmpl_LDouble_SinCosPi(long double t, long double *sin_t, long double *cos_t);

/*  64-bit long double, needs no precision than ordinary double.              */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT

/******************************************************************************
 *                                64-Bit Double                               *
 ******************************************************************************/

/*  High-Low splitting factor, set to 2^27 + 1 = 2^(floor(52 / 2) + 1) + 1.   */
#define TMPL_LDOUBLE_SPLIT (+1.34217729E+08L)

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (-2.1447177918579579753388433334911075409571981652522E-17L)
#define A01 (+7.9577471545956793464435579966743818103647044950248E-02L)
#define A02 (-1.2981161608641168980253175509340062024354018232720E-02L)
#define A03 (+3.1265770142568086318447462445674196101423129654279E-03L)
#define A04 (+7.7189914096390976785579606078912825867840834363500E-03L)
#define A05 (+1.2152711327644207051269759240566405273724207890213E-03L)
#define A06 (-4.2580086843249039236789916436456229647180162906877E-04L)
#define A07 (+2.5599751814229062968976494152423993700328342606881E-04L)
#define A08 (-9.2991030649511374603974585631455140488901798820494E-06L)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.6312608777091934006569688848947319631644210599940E-01L)
#define B02 (+3.9289725286653476885524131750142019793543796155984E-02L)
#define B03 (+9.6999710172863227181034452265627316168021158412569E-02L)
#define B04 (+1.6458875720410357910114941861796832691658504516205E-02L)
#define B05 (-5.5442943302851907019637247635816813200757166309069E-03L)
#define B06 (+3.2629747328741893876385822248293808741755682623822E-03L)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+4.1888470497242228970512655048232789216782855688029E-18L)
#define C01 (-1.9399304561569123981472429874629917184781769350025E-15L)
#define C02 (+1.5079232893754790305784439966341317007503129139523E-13L)
#define C03 (+1.5831434897680803460728630060707251688669525968296E-03L)
#define C04 (-8.5860131430356321612346593614783654305957210855428E-04L)
#define C05 (+4.2520325383513231021011832063304578196045175371085E-04L)
#define C06 (+3.3997508002435750699645210285275720556079846712290E-05L)
#define C07 (-5.5470926830268577613702499017237117454491309503712E-06L)
#define C08 (+7.5271268828364550735383328753338000305964366209750E-06L)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (-5.4233958725410615801476694071713976580197499138498E-01L)
#define D02 (+2.6858208718351641067450334485612139901006052610880E-01L)
#define D03 (+2.1471758208227504686456421042560514470187040155549E-02L)
#define D04 (+2.4456357033936610541923412853466023983394272209113E-03L)
#define D05 (+1.4961320031496760787440948034839831542661075561170E-03L)
#define D06 (+1.6780659196575798229291066904872309116983197533248E-03L)

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

/*  Quadruple precision needs very large sums to obtain 34 decimals.          */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT

/******************************************************************************
 *                              128-Bit Quaduple                              *
 ******************************************************************************/

/*  High-Low splitting factor, set to 2^57 + 1 = 2^(floor(112 / 2) + 1) + 1.  */
#define TMPL_LDOUBLE_SPLIT (+1.44115188075855873E+17L)

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (-6.4904766979192653068496179233841491806804722684774E-35L)
#define A01 (+7.9577471545947667884441881686417353500492022430675E-02L)
#define A02 (-1.4919298595807526766220211268241052042107772610231E-01L)
#define A03 (+2.4066168754325458483591867577979788083691169954156E-01L)
#define A04 (-1.7854744768727179892601906211213853015357318857025E-01L)
#define A05 (+1.3086839917717520129369830501345015185904272335572E-01L)
#define A06 (-3.0875830655612332967447058377184890425948370623227E-02L)
#define A07 (+2.1785813774732102703817671497063847217699763093872E-02L)
#define A08 (+1.9165895304511916471997977171266327362247148926458E-03L)
#define A09 (+7.3762862024333917953263983136804412488034589734650E-03L)
#define A10 (+9.6066909811372885081693756705254645847582566545084E-04L)
#define A11 (+9.7242145758967713920974851434358964837143059889196E-04L)
#define A12 (+9.4385674013723899679040411175934640741684178402737E-04L)
#define A13 (-4.1431581762394754993056325747509455062803912213571E-05L)
#define A14 (+1.2916731654145958116331187280797332643677246214623E-04L)
#define A15 (+1.1075242606818414035698955249185292656744896551893E-05L)
#define A16 (+3.4270485511036292593002204571426535228627501668449E-06L)
#define A17 (+1.1097488402703227654540866115001016275215156645990E-06L)
#define A18 (-2.5295094882280476886540007946268130752321613128307E-08L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.8748143546120577650108301397768506783520955756534E+00L)
#define B02 (+3.0242439583456434379964328487030292384647213291886E+00L)
#define B03 (-2.2436933998861640100431488433557005088414589933834E+00L)
#define B04 (+1.6457281633890892643232800346326982370239806755480E+00L)
#define B05 (-3.9022320615616700806126409773516358757816074532197E-01L)
#define B06 (+2.7735946913982098996717326648012895734318491366424E-01L)
#define B07 (+2.1420507898137415554881127339653420565846530986160E-02L)
#define B08 (+9.4630766175878171860063218121524247611830290497839E-02L)
#define B09 (+1.1639626144911304099276066394707114520756825572612E-02L)
#define B10 (+1.2499390912930983999482801306265763596182758081023E-02L)
#define B11 (+1.1923191402355596522940623117967810565835345129629E-02L)
#define B12 (-4.3470831360857037070633262695570678855799688520651E-04L)
#define B13 (+1.6421948510930707576513524078498878011907499452453E-03L)
#define B14 (+1.5140389135500365590644157021084628985577000214913E-04L)
#define B15 (+5.5424449453913402414456539674136478346358699824428E-05L)
#define B16 (+1.2883385736904016230674963438322020865664042062275E-05L)
#define B17 (+1.2833983896001658047875733605714164409381004880694E-06L)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+1.1396861658179131978602127012789163913929631315740E-35L)
#define C01 (-2.9347018750672577211923966319322614450461778633985E-32L)
#define C02 (+1.2625387539528915979585395357681792108085063827325E-29L)
#define C03 (+1.5831434944115276788106144398286198252953991602122E-03L)
#define C04 (-3.6781637400818500242450489018650244280481936557098E-03L)
#define C05 (+6.7818939046820923267440598285287989604377780437487E-03L)
#define C06 (-7.2081677805021732803150578295776302266067588156394E-03L)
#define C07 (+6.8916279779716047185072976084010674503534392006248E-03L)
#define C08 (-4.5674381690599000054236870749374931803488485007035E-03L)
#define C09 (+3.2131673111432361126156464003609811103004120698059E-03L)
#define C10 (-1.6796463847382439006435222609903100394972457756395E-03L)
#define C11 (+1.0511958396692101377038730041181764909179740985206E-03L)
#define C12 (-4.4300829700947770647931309517764771947078728652833E-04L)
#define C13 (+2.2195254689535819138989835800997898540314303149255E-04L)
#define C14 (-6.4095621555758081459064022515383092062403547740594E-05L)
#define C15 (+2.4727436612197930384057044293262404104018272687678E-05L)
#define C16 (-4.5009666475134346089411598626017446773072831302488E-06L)
#define C17 (+1.3090049386077826332632712171217441982842671797748E-06L)
#define C18 (-1.0504596431084134722485334251080856187317814717161E-07L)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (-2.3233293463705038547951157748387429413884851160433E+00L)
#define D02 (+4.2838150354797743108120551882530150607318266968131E+00L)
#define D03 (-4.5530729248150248524155485375877247780060753793871E+00L)
#define D04 (+4.3590658647158261062830672987822021466772654691532E+00L)
#define D05 (-2.8988368167489622075596808413330713350953392122718E+00L)
#define D06 (+2.0550442772142880139927789307024970615538087804010E+00L)
#define D07 (-1.0879871316464456349650354340702661198497028549129E+00L)
#define D08 (+6.8972359294694219259438413426543008298017175914392E-01L)
#define D09 (-2.9669412021652235202923875000854871727215150313700E-01L)
#define D10 (+1.5176359078670578710872313235444560400460406084021E-01L)
#define D11 (-4.6271453109994806292652085697374012087111736349852E-02L)
#define D12 (+1.9077046184401586421959349152899412103239802737591E-02L)
#define D13 (-4.1948168509974218487144221236384213892424564684058E-03L)
#define D14 (+1.4595157105166177635762699618030816535724463245760E-03L)
#define D15 (-2.1817043377684758680190528705183066426202703132811E-04L)
#define D16 (+4.6888769145837094609498594514600746793391483420824E-05L)
#define D17 (-3.4254705112204542726738730742626702414411158839396E-06L)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) \
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
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*(\
                                A16 + z*(\
                                  A17 + z*A18\
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
        )\
      )\
    )\
  )\
)

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) \
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
                      B11 + z*(\
                        B12 + z*(\
                          B13 + z*(\
                            B14 + z*(\
                              B15 + z*(\
                                B16 + z*B17\
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
      )\
    )\
  )\
)

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) \
C00 + z*(\
  C01 + z*(\
    C02 + z*(\
      C03 + z*(\
        C04 + z*(\
          C05 + z*(\
            C06 + z*(\
              C07 + z*(\
                C08 + z*(\
                  C09 + z*(\
                    C10 + z*(\
                      C11 + z*(\
                        C12 + z*(\
                          C13 + z*(\
                            C14 + z*(\
                              C15 + z*(\
                                C16 + z*(\
                                  C17 + z*C18\
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
        )\
      )\
    )\
  )\
)

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) \
D00 + z*(\
  D01 + z*(\
    D02 + z*(\
      D03 + z*(\
        D04 + z*(\
          D05 + z*(\
            D06 + z*(\
              D07 + z*(\
                D08 + z*(\
                  D09 + z*(\
                    D10 + z*(\
                      D11 + z*(\
                        D12 + z*(\
                          D13 + z*(\
                            D14 + z*(\
                              D15 + z*(\
                                D16 + z*D17\
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
      )\
    )\
  )\
)

/*  Double double, needs nearly as big a sum as quadruple.                    */
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (+2.2835738757246204686006620965032406581891537178297E-32L)
#define A01 (+7.9577471545947667884441881638058129922181443548178E-02L)
#define A02 (-1.4633361735082050580767193381723219469486205872752E-01L)
#define A03 (+3.2735147336038648732797532152301811717687381396847E-01L)
#define A04 (-3.6116294045704159702476579242173916240650013508447E-01L)
#define A05 (+4.1304280325157920138795197097195929064534123758047E-01L)
#define A06 (-2.7619171776028676498618128434528772276831094667896E-01L)
#define A07 (+2.0009913215850241682843885174936259309065971911656E-01L)
#define A08 (-8.4188616709778979952285372708632206826342243381598E-02L)
#define A09 (+5.0797797123062817342801758551953043223081741109144E-02L)
#define A10 (-1.6252830666213362084269133073581683756188894187510E-02L)
#define A11 (+9.8369496536342976712406142427859250786944112214745E-03L)
#define A12 (-2.1885391501790634612636959564018782969967106572708E-03L)
#define A13 (+1.0282696994033383444260234320637512986425708030640E-03L)
#define A14 (-6.9485156996319652923283775707732508383440038226770E-05L)
#define A15 (+3.3590993023157829113540514302578221480837609563379E-05L)
#define A16 (+3.5614286486481547282851858928777570964172058704567E-06L)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.8388824689702304105616788783510889802664316093926E+00L)
#define B02 (+4.1136199354031403816751698916539287829573028440619E+00L)
#define B03 (-4.5385073619549192143752241538453143939455498794611E+00L)
#define B04 (+5.1916363028739909749901192875803157805854834645502E+00L)
#define B05 (-3.4729108971055533192830289754689591441704572351197E+00L)
#define B06 (+2.5194041922947887198357170371267066661821122392664E+00L)
#define B07 (-1.0633341903886287863191768182671492014193717520926E+00L)
#define B08 (+6.4449182609207300082274966735756493910434139082112E-01L)
#define B09 (-2.0833243518967172226781089447379896868985240054942E-01L)
#define B10 (+1.2653852851225386091198414885764507829547490913135E-01L)
#define B11 (-2.8689903213087504953704178976375293845931946564834E-02L)
#define B12 (+1.3602113538859338275644990709339552857510948155169E-02L)
#define B13 (-1.0646046652951262111193772832681448962959256665246E-03L)
#define B14 (+5.3357648811335636136571556691428421164448950057273E-04L)
#define B15 (+2.5250961114199231934686824664066277371675362358881E-05L)
#define B16 (+8.8534012958389662418383730647919178216514655456687E-06L)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+1.1788212542903726595454468755723542020535379685232E-32L)
#define C01 (-2.4533102533821735213736769535721938279037276406155E-29L)
#define C02 (+8.5257021658269221213274968761284413357393704945039E-27L)
#define C03 (+1.5831434944115276788094324706255198491004476941149E-03L)
#define C04 (-2.7102016594597121580850232515001446441434068978584E-03L)
#define C05 (+4.1476699361853641995543249753572078140952693154731E-03L)
#define C06 (-2.9076295112918715937053269444253509467386562433897E-03L)
#define C07 (+2.1446312985410585995001329770879961618234965123735E-03L)
#define C08 (-6.2561483812379967821106316529280675640020842963857E-04L)
#define C09 (+4.4835234462344093535711412662350132823799033306423E-04L)
#define C10 (-5.4273485935852367816238310589708877971908266360358E-05L)
#define C11 (+1.1035188530243581977881954865729556651807159011242E-04L)
#define C12 (+6.2036157129344614786783177874986012061432176589477E-07L)
#define C13 (+1.2140307645130486046507549688979561063524219720439E-05L)
#define C14 (+5.4512376226305665159554357799553333263224973605379E-06L)
#define C15 (-8.3403868470470297398089959258979046688779928422220E-09L)
#define C16 (+5.9832636949139212087817400752008572585339248705572E-07L)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (-1.7119115664667685296350668689311847689933264127464E+00L)
#define D02 (+2.6198951332122297441480107395888321881908764677790E+00L)
#define D03 (-1.8366177933685477161295576645343598616955076721255E+00L)
#define D04 (+1.3606031882829133372337650484002019352134889525372E+00L)
#define D05 (-4.0533579764594436470558458736165414791860940134414E-01L)
#define D06 (+2.9875761978005752203076408647390687682880942353696E-01L)
#define D07 (-4.5185712152995904167916383300535187025496939343346E-02L)
#define D08 (+7.7633866932503023621557176434158921684335520134643E-02L)
#define D09 (-1.7611228348702460847285278918015641705273881604837E-03L)
#define D10 (+9.0543184739686624476819041131029611958359119131199E-03L)
#define D11 (+3.4469131716586949137095370600994584898557303790085E-03L)
#define D12 (+2.6261218692833700900646374025166313534271809531318E-04L)
#define D13 (+4.1308479730233586850402229603545382247630273381597E-04L)
#define D14 (+3.1619880927066890103333719426765895420784689879979E-05L)
#define D15 (+1.1461663489667163925272003698660545827387726534093E-05L)
#define D16 (+1.1551654431018668171043409244397845877297306226058E-06L)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) \
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
                          A13 + z*(\
                            A14 + z*(\
                              A15 + z*A16\
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
    )\
  )\
)

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) \
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
                      B11 + z*(\
                        B12 + z*(\
                          B13 + z*(\
                            B14 + z*(\
                              B15 + z*B16\
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
    )\
  )\
)

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) \
C00 + z*(\
  C01 + z*(\
    C02 + z*(\
      C03 + z*(\
        C04 + z*(\
          C05 + z*(\
            C06 + z*(\
              C07 + z*(\
                C08 + z*(\
                  C09 + z*(\
                    C10 + z*(\
                      C11 + z*(\
                        C12 + z*(\
                          C13 + z*(\
                            C14 + z*(\
                              C15 + z*C16\
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
    )\
  )\
)

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) \
D00 + z*(\
  D01 + z*(\
    D02 + z*(\
      D03 + z*(\
        D04 + z*(\
          D05 + z*(\
            D06 + z*(\
              D07 + z*(\
                D08 + z*(\
                  D09 + z*(\
                    D10 + z*(\
                      D11 + z*(\
                        D12 + z*(\
                          D13 + z*(\
                            D14 + z*(\
                              D15 + z*D16\
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
    )\
  )\
)

/*  Most common representation, 80-bit extended. 63-bit mantissa.             */
#else

/******************************************************************************
 *                         80-Bit Extended / Portable                         *
 ******************************************************************************/

/*  High-Low splitting factor, set to 2^32 + 1 = 2^(floor(63 / 2) + 1) + 1.   */
#define TMPL_LDOUBLE_SPLIT (+4.294967297E+09L)

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (+3.7917276177869050029828761509968593742453948654175E-20L)
#define A01 (+7.9577471545947647483162446203605621960785339472695E-02L)
#define A02 (-1.0702772616184083317434762476558232886871973965288E-01L)
#define A03 (+7.0214677394665845423075708636903403414849100957703E-02L)
#define A04 (-2.2456657198442821040258429259150040709213968985841E-02L)
#define A05 (+3.6212846038663110734587018475396691772992158521896E-03L)
#define A06 (-1.3534392461520340035266095684409162363017308232756E-03L)
#define A07 (+8.9409047631161517874994665658338950876941878470479E-04L)
#define A08 (-3.0418233176485667863262923186897526228705279564798E-04L)
#define A09 (+4.0188223225057158675146023702563850756825148002687E-05L)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-1.3449500729618602061164669961706406746305420953795E+00L)
#define B02 (+8.8234365870986260349936936639416387565971782233007E-01L)
#define B03 (-2.8219867713067968940020441073447279286754220758297E-01L)
#define B04 (+4.6693762226276923668984745914523262298489759556245E-02L)
#define B05 (-1.8604757143906772512374486191462528462250846899855E-02L)
#define B06 (+1.2283135818350804679027650244575445940005506388053E-02L)
#define B07 (-4.1575582112997939329231886921932219227067210313502E-03L)
#define B08 (+5.4405352410928160690371117357157906667264845964051E-04L)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (+1.1371287603445848005210827361637799770058006544804E-20L)
#define C01 (-7.3986211698354474067331378904045608843652018281185E-18L)
#define C02 (+8.0380321325564849007247513130359683751582888691454E-16L)
#define C03 (+1.5831434943768170834076704881287044117787430950562E-03L)
#define C04 (-1.3035921452531828837507285871279134726941044035574E-03L)
#define C05 (+1.1307281305170076075859713280905325805141340074285E-03L)
#define C06 (-3.1060293044203126946183201675579391030805221475230E-04L)
#define C07 (+1.5228702006410225475652303843447172835521254595927E-04L)
#define C08 (-1.3997039185692189727012679325552570577409787268034E-05L)
#define C09 (+1.1317984824659976934738055426190797194792411724764E-05L)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (-8.2342008203717786026836115897891205151495534936042E-01L)
#define D02 (+7.1422972428057573248241026528723101913138847565171E-01L)
#define D03 (-1.9619385890396477931559143657187789061332304873128E-01L)
#define D04 (+1.0213000503578127641431011519379051416442241112476E-01L)
#define D05 (-1.3731644703832363963112093709093424541352404076204E-02L)
#define D06 (+1.1395653129179652900072876816684677844348399338714E-02L)
#define D07 (-1.1807597917041493642772577686858352534524361402239E-03L)
#define D08 (+4.8807726653950729302350023463505666854567636214956E-04L)

/*  Evaluates the numerator of the "f" function using Horner's method.        */
#define TMPL_POLYA_EVAL(z) \
A00 + z*(\
  A01 + z*(\
    A02 + z*(\
      A03 + z*(\
        A04 + z*(\
          A05 + z*(\
            A06 + z*(\
              A07 + z*(\
                A08 + z*A09\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the denominator of the "f" function using Horner's method.      */
#define TMPL_POLYB_EVAL(z) \
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

/*  Evaluates the numerator of the "g" function using Horner's method.        */
#define TMPL_POLYC_EVAL(z) \
C00 + z*(\
  C01 + z*(\
    C02 + z*(\
      C03 + z*(\
        C04 + z*(\
          C05 + z*(\
            C06 + z*(\
              C07 + z*(\
                C08 + z*C09\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the denominator of the "g" function using Horner's method.      */
#define TMPL_POLYD_EVAL(z) \
D00 + z*(\
  D01 + z*(\
    D02 + z*(\
      D03 + z*(\
        D04 + z*(\
          D05 + z*(\
            D06 + z*(\
              D07 + z*D08\
            )\
          )\
        )\
      )\
    )\
  )\
)

#endif

/*  Coefficients for the Taylor polynomial of cos(pi/2 x^2).                  */
#define C0 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define C1 (-1.2337005501361698273543113749845188919142124259051E+00L)

/*  Coefficients for the Taylor polynomial of sin(pi/2 x^2).                  */
#define S0 (+1.5707963267948966192313216916397514420985846996876E+00L)
#define S1 (-6.4596409750624625365575656389794573337969351178927E-01L)

/*  Helper macros for cos and sin.                                            */
#define TMPL_COS_TAYLOR(z) (C0 + z*C1)
#define TMPL_SIN_TAYLOR(z) (S0 + z*S1)

/*  Function for computing the normalized Fresnel cosine of a large input.    */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Normalized_Fresnel_Cos_Auxiliary(long double x)
{
    /*  Use the double-double trick, split x into two parts, high and low.    */
    const long double xhi = tmpl_LDouble_Even_High_Split(x);
    const long double xlo = x - xhi;

    /*  The Maclaurin series for cos(pi/2 x^2) is in terms of x^4. Compute.   */
    const long double xlo_sq = xlo * xlo;
    const long double xlo_qr = xlo_sq * xlo_sq;

    /*  xlo^2 is small, so sin(pi/2 xlo^2) and cos(pi/2 xlo^2) can be         *
     *  accurately computed using a few terms of the Maclaurin series.        */
    const long double cos_lo = TMPL_COS_TAYLOR(xlo_qr);
    const long double sin_lo = xlo_sq * TMPL_SIN_TAYLOR(xlo_qr);

    /*  The auxiliary functions f and g are computed by shifting the interval *
     *  [4, infty) using the following formula.                               */
    const long double t = 4.0L / x;

    /*  Compute the auxiliary function f using a rational Remez approximation.*/
    const long double fn = TMPL_POLYA_EVAL(t);
    const long double fd = TMPL_POLYB_EVAL(t);
    const long double f = fn / fd;

    /*  Perform the same calculation for the auxiliary function g.            */
    const long double gn = TMPL_POLYC_EVAL(t);
    const long double gd = TMPL_POLYD_EVAL(t);
    const long double g = gn / gd;

    /*  Variables for storing the values of sine and cosine.                  */
    long double cos_hi, sin_hi, cos_mid, sin_mid;
    long double cos_midlo, sin_midlo, cos_x, sin_x;

    /*  xhi^2 and 2 xhi xlo are big enough that we need to use the full sine  *
     *  and cosine functions. Run the computation.                            */
    tmpl_LDouble_SinCosPi(0.5L * xhi * xhi, &sin_hi, &cos_hi);
    tmpl_LDouble_SinCosPi(xhi * xlo, &sin_mid, &cos_mid);

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
    return 0.5L + (f*sin_x - g*cos_x);
}
/*  End of tmpl_Double_Normalized_Fresnel_Cos_Auxiliary.                      */

/*  Undefine everything in case someone wants to #include this file.          */
#include "../../math/auxiliary/tmpl_math_undef.h"
#undef C0
#undef C1
#undef S0
#undef S1
#undef TMPL_LDOUBLE_SPLIT
#undef TMPL_COS_TAYLOR
#undef TMPL_SIN_TAYLOR

#endif
/*  End of include guard.                                                     */
