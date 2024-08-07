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
#ifndef TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_LDOUBLE_H
#define TMPL_NORMALIZED_FRESNEL_COS_AUXILIARY_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Used to compute sin(pi t) and cos(pi t) simultaneously.                   */
extern void
tmpl_LDouble_SinCosPi(long double t, long double *sin_t, long double *cos_t);

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

#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/******************************************************************************
 *                            128-Bit Double-Double                           *
 ******************************************************************************/

/*  High-Low splitting factor, set to 2^53 + 1 = 2^(floor(104 / 2) + 1) + 1.  */
#define TMPL_LDOUBLE_SPLIT (+9.007199254740993E+15L)

/*  Coefficients for the numerator of the "f" auxiliary function.             */
#define A00 (-2.8556240227444046817384387706152797887109428853832E-08L)
#define A01 (-3.1831172418792733844174801845927112951332490249957E-01L)
#define A02 (+1.4133720750587364950432464445571777856780101672632E+01L)
#define A03 (-1.9681371222318134067444237828166988075736664829625E+02L)
#define A04 (+1.5541974745958619259609606369255908633910681252354E+03L)
#define A05 (-8.3377427549300795604384363679505182913728143539364E+03L)
#define A06 (+3.2764077216232985831093499906935985530028456035230E+04L)
#define A07 (-9.5920103054926111413453829093994458184816664330438E+04L)
#define A08 (+2.0305806204843873343225346501166061149488675861154E+05L)
#define A09 (-2.1917323398432761419872515158782003189710859884604E+05L)
#define A10 (-2.0162503537786477019940674878583430949398464458673E+05L)
#define A11 (+2.5565606527117980023520525547216448698535053731727E+06L)
#define A12 (-5.8203920888491336903230438968051864829248279214186E+06L)
#define A13 (+1.7707387909980786195046391834895351133832729923339E+07L)
#define A14 (-1.5615076195923857821292787679573464912513597849958E+07L)
#define A15 (+3.4108860354110723911195060080355608027241880943265E+07L)
#define A16 (-1.0032584000340389894073879986342272168114602426703E+07L)

/*  Coefficients for the denominator of the "f" auxiliary function.           */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (-4.4402523241484149024855791017148946017027388937808E+01L)
#define B02 (+6.1830859578414724016362951749851334373554204837176E+02L)
#define B03 (-4.8825775508415317360808219838039199904623394475720E+03L)
#define B04 (+2.6196413533926709994514495418425880149516367376848E+04L)
#define B05 (-1.0290428745359681056329298089048218034272649450211E+05L)
#define B06 (+3.0203412616671524970375458001333807415010048607125E+05L)
#define B07 (-6.3465896666041494599836897915214465694144096739206E+05L)
#define B08 (+7.3152811729864055314585120497638524162398733487610E+05L)
#define B09 (+8.0696882499536180343659688995195692932066282314771E+05L)
#define B10 (-6.9871494887626542577563351731281129943357943125401E+06L)
#define B11 (+2.1605547951612518525775592071638660144536326029726E+07L)
#define B12 (-4.5441702108275938598918012566559545342887239710263E+07L)
#define B13 (+7.0523307758605004456380806526503986331107414794694E+07L)
#define B14 (-7.9585736208642992136645245097737860395663923436846E+07L)
#define B15 (+5.9682167999278313178779429738219707224890954028231E+07L)
#define B16 (-2.2716865846050869893777655443145680610959693526351E+07L)

/*  Coefficients for the numerator of the "g" auxiliary function.             */
#define C00 (-1.3227451447933565895455103586596499223433705738271E-07L)
#define C01 (-1.0120736786157221236389624421564539950125322024015E-05L)
#define C02 (-3.6815918909656117681488035919743355657271467757785E-04L)
#define C03 (-1.0978284776428243684111381431360083813307286554987E-01L)
#define C04 (+1.7102112365778145384144599452282260611788933955466E+00L)
#define C05 (-1.9339237014009067826261992425877041567644086644814E+01L)
#define C06 (+1.0093453262787456356596797287339244049795553702014E+02L)
#define C07 (-7.2204862393316095221883407090263153196189512861028E+02L)
#define C08 (+1.7628374361829342230403024285128544271121072902144E+03L)
#define C09 (-1.2567816197782734110728668790303451453240343582418E+04L)
#define C10 (+1.1508439137669046747981013594287780039895177738263E+04L)
#define C11 (-1.1791953216606980096162459546039151538156761284926E+05L)
#define C12 (+2.5685008254546773440878057012419393994320868275009E+04L)
#define C13 (-5.4436693346434619170625891840573411492002891654721E+05L)
#define C14 (+1.0250589453342478531911577463936395845211286143526E+05L)
#define C15 (-8.9975882526258522225634835254905016938379466830014E+05L)
#define C16 (+5.7963041343263164178319628665321830357375650732884E+05L)

/*  Coefficients for the denominator of the "g" auxiliary function.           */
#define D00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define D01 (-1.8238293340225048852283633291820163864259083023086E+01L)
#define D02 (+1.7423582503969823527507292002907813768907448010729E+02L)
#define D03 (-1.1548349593951767952709109171669423014401639532568E+03L)
#define D04 (+5.9225760088947526442300707011204565694987661231524E+03L)
#define D05 (-2.4815597462939772070682439248439103614097268485899E+04L)
#define D06 (+8.7515362742417408570314590253146094684380615718046E+04L)
#define D07 (-2.6409119078143004465044046029075772829287951091236E+05L)
#define D08 (+6.8756780252013791244869795166515065277233503365360E+05L)
#define D09 (-1.5477708660953638802542727718019615632366981814079E+06L)
#define D10 (+3.0023063099593462997364757798396512601190346889648E+06L)
#define D11 (-4.9700808641531619223769138635704634283673573727620E+06L)
#define D12 (+6.8951082491871032932360709792996006668276625031000E+06L)
#define D13 (-7.7676705974876180320548958183058161905247941338443E+06L)
#define D14 (+6.7197271389511135282292863873764253873263349340014E+06L)
#define D15 (-4.0003054216543981648593847625532668550964610497860E+06L)
#define D16 (+1.2383998353249195671666383791872715092843615294963E+06L)

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
    /*  Use the double-double trick, split x into two parts, high and low.    *
     *  The magic number 134217729 is 2^27 + 1. This results in xhi and xlo   *
     *  both having half of the bits of x.                                    */
    const long double split = TMPL_LDOUBLE_SPLIT * x;
    const long double xhi = split - (split - x);
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
