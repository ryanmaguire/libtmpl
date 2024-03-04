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
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ERF_ASYMPTOTIC_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H
#define TMPL_ERF_ASYMPTOTIC_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Only use this code for 128-bit double-double.                             */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  Coefficients for the Remez polynomial of erf on [2, 2.8].                 */
#define PA00 (+9.9931148610335492111445002519029448587565964115273E-01L)
#define PA01 (+3.5556486808777486276786110747440203795719876678814E-03L)
#define PA02 (-8.5335568341065963906236239595350759106745079295134E-03L)
#define PA03 (+1.2468474707611304177150192242118385485794732208537E-02L)
#define PA04 (-1.2117650704431365661994173914031210389905841891924E-02L)
#define PA05 (+7.8924022639707193518641066247095590710806951347788E-03L)
#define PA06 (-3.0825482899948777379652407137559161612571248899467E-03L)
#define PA07 (+2.3460400267012576305922253344508263842456443494442E-04L)
#define PA08 (+5.1978366053968406274023587172343732436357058914978E-04L)
#define PA09 (-3.2283539725146705371197722178260498626292885089838E-04L)
#define PA10 (+6.2555006584760342472444549664734926251436260555979E-05L)
#define PA11 (+2.5530880313253688845443679264282164797291866377910E-05L)
#define PA12 (-1.9690383426022609449598634724175659151753215357749E-05L)
#define PA13 (+3.6697866567146786948291367406069374309873704231358E-06L)
#define PA14 (+1.3383215101376401155573206947943876698348288758053E-06L)
#define PA15 (-8.8261742171252868502411801713791596663000099284255E-07L)
#define PA16 (+1.0864771703770558153656957988639121788301087230511E-07L)
#define PA17 (+6.6670507500236341269714956864296620369559778621199E-08L)
#define PA18 (-2.9140655176414109592070294573793012795246525170685E-08L)
#define PA19 (+7.3378588413018391206092318983816023410867175917792E-10L)
#define PA20 (+2.5845880506529152842932031388022817201496075769618E-09L)
#define PA21 (-6.5714382429986059247322009367076598068836939981681E-10L)
#define PA22 (-8.0412110521551648062357689763436087109751237697968E-11L)
#define PA23 (+7.1293990716012855781990254550635798066803921972918E-11L)
#define PA24 (-7.7996862217791476212327833072053081818797732112631E-12L)
#define PA25 (-3.8990020302420473938573607405882270221556697087441E-12L)
#define PA26 (+1.2002269785216306943319839484523753324537765405588E-12L)

/*  Coefficients for the Remez polynomial of erf on [2.8, 3.6].               */
#define PB00 (+9.9999397423884823791218655568627695949932305159197E-01L)
#define PB01 (+4.0297635533235574954748059453146413048474347386096E-05L)
#define PB02 (-1.2895243370635384701349183935489501544835143822046E-04L)
#define PB03 (+2.6166598006247636391490191303966976209927796042999E-04L)
#define PB04 (-3.7568142353117758983328678187349415533589472214162E-04L)
#define PB05 (+4.0237242810116443250601869438076891487477260503025E-04L)
#define PB06 (-3.2901554369959472787611063189013601951151932383549E-04L)
#define PB07 (+2.0501125231078080776739510489347562267733507733954E-04L)
#define PB08 (-9.3505671055854356487632121969197618557045122270683E-05L)
#define PB09 (+2.6629622579289056372575631948291432850830366191897E-05L)
#define PB10 (-4.1972804081533365051553434019343784891549109581455E-07L)
#define PB11 (-4.1133691983184041052320878488320864080319992969251E-06L)
#define PB12 (+2.2573920634691086924504631983167287756415102123517E-06L)
#define PB13 (-5.3124094943157838983974782260650498657965452890575E-07L)
#define PB14 (-5.4825068849184798468867378497653706809762055001573E-08L)
#define PB15 (+8.9164718342593144686141034069299267394194194435595E-08L)
#define PB16 (-2.9269629304598195236122268510263150095763819490360E-08L)
#define PB17 (+1.1848107461823001468587764562687901747090516692726E-09L)
#define PB18 (+2.6396102236484465697675248175609326461292131255665E-09L)
#define PB19 (-1.0069210268219209416388398938392448558164768878291E-09L)
#define PB20 (+7.2146394997350190638345894091154547136282864497573E-11L)
#define PB21 (+6.9120158153296792542940993048963835681827742345334E-11L)
#define PB22 (-2.6354142283676088175832350378095505297317654833982E-11L)
#define PB23 (+1.5773971523679154678911112716299681860254769190240E-12L)
#define PB24 (+1.6801202588286709154697539654076408885138662038645E-12L)
#define PB25 (-5.1212318765407957022930284410963217192090699327249E-13L)
#define PB26 (+1.8517130145187075774371064106952061097456908758265E-15L)

/*  Coefficients for the Remez polynomial of erf on [3.6, 4.4].               */
#define PC00 (+9.9999998458274209971998114784030296053488920916762E-01L)
#define PC01 (+1.2698234671866558268349648663962761533930492050251E-07L)
#define PC02 (-5.0792938687466233073396040851144965377103569394045E-07L)
#define PC03 (+1.3121509160928776877328673113135683575105468152661E-06L)
#define PC04 (-2.4549920365608679318960907600035092068849694533523E-06L)
#define PC05 (+3.5343419836695253840455062341049144343671617054541E-06L)
#define PC06 (-4.0577914351431357291454130301175316661809969426296E-06L)
#define PC07 (+3.7959659297660777063138042345998469963817916078691E-06L)
#define PC08 (-2.9264391936639772653816049747539284360569410614264E-06L)
#define PC09 (+1.8631747969134616975347613886236436346040069694939E-06L)
#define PC10 (-9.7028398087939270825588819901739447616495401325352E-07L)
#define PC11 (+4.0077792841744776024529000992995403379005155920852E-07L)
#define PC12 (-1.2017256123604173017593759459432186260286500258272E-07L)
#define PC13 (+1.7432381110163776680971894086031302597518873896271E-08L)
#define PC14 (+5.8855705189391095070773332146406620595201743444876E-09L)
#define PC15 (-5.2972657222666358038217731645114610393559084241843E-09L)
#define PC16 (+1.9619829515825312158249935657990783879129323969427E-09L)
#define PC17 (-3.3902907847558623717779892590234369160557437876338E-10L)
#define PC18 (-5.4494968565272586410554157478560732429085979691065E-11L)
#define PC19 (+5.6651322186295752263412076316115446821150848600008E-11L)
#define PC20 (-1.7498562967016015433955537171288604933003065743758E-11L)
#define PC21 (+1.5349169732444640250822582610838061093978257317634E-12L)
#define PC22 (+9.5944390391323843844055175817205318163366750597292E-13L)
#define PC23 (-4.4838143234594803327972353871176903619659526695696E-13L)
#define PC24 (+6.7603516003093474389482447083328109619872205310799E-14L)

/*  Coefficients for the Remez polynomial of erf on [4.4, 5.2].               */
#define PD00 (+9.9999999998864785641507801928268163405907593327148E-01L)
#define PD01 (+1.1125260689810878994556739241907389236884936029777E-10L)
#define PD02 (-5.3401251311092217197789652104469674015878990644797E-10L)
#define PD03 (+1.6717558396555812906596634127678482722441591865176E-09L)
#define PD04 (-3.8342098441364208912531653915230578498720443307005E-09L)
#define PD05 (+6.8601561488452534094753760124900308788997982407397E-09L)
#define PD06 (-9.9537938797160262116960682471912583208881499201843E-09L)
#define PD07 (+1.2017546809123588388719763978082331934238571564866E-08L)
#define PD08 (-1.2288100339580581136359679439355145662766257432490E-08L)
#define PD09 (+1.0770561816000622644265052101713448481267114764952E-08L)
#define PD10 (-8.1551881718797849964624985706269137432911473190759E-09L)
#define PD11 (+5.3547995619371538711449463320596590582691878256493E-09L)
#define PD12 (-3.0482050780481515389719861360952257355459669537418E-09L)
#define PD13 (+1.4958181705784473497580237791325460154927085898291E-09L)
#define PD14 (-6.2374277928372584549154702306231978599333675926599E-10L)
#define PD15 (+2.1399884492787333026392259907229720220059726989386E-10L)
#define PD16 (-5.5629315087124649866435497781780306157056412926132E-11L)
#define PD17 (+7.8113730575057336317597184297707514848891813590599E-12L)
#define PD18 (+1.6513712946260937611139011169829938234622878713168E-12L)
#define PD19 (-1.6108565299838518771685860288107888762937867332082E-12L)
#define PD20 (+6.1680849321813951458268744914163714897355787063171E-13L)
#define PD21 (-1.3657819265721700563097615216266361318431092379034E-13L)
#define PD22 (+6.0405973277647989696245340634324413387846123429104E-15L)
#define PD23 (+9.6169306032318522948628010365091616900121682685031E-15L)
#define PD24 (-4.0077211868369917237193264223357993886145993486947E-15L)

/*  Coefficients for the Remez polynomial of erf on [5.2, 6.0].               */
#define PE00 (+9.9999999999999761716371541697200054317458389510918E-01L)
#define PE01 (+2.7100674924697916704949088646342260535486878922984E-14L)
#define PE02 (-1.5176377957830832322736382995885079074614172215085E-13L)
#define PE03 (+5.5755121878411904175823654409175349825335296200179E-13L)
#define PE04 (-1.5105554860694306387839632224995035659047343656104E-12L)
#define PE05 (+3.2163789231601843075206798712546736604611167887096E-12L)
#define PE06 (-5.6010925269471404407112316163301911261935721866543E-12L)
#define PE07 (+8.1959435376089161433847010132699461555519261614937E-12L)
#define PE08 (-1.0274086839736491075763857200433764960723216937625E-11L)
#define PE09 (+1.1191874601255843541971963806619692416492378444932E-11L)
#define PE10 (-1.0708395226299407975901900724916252146627038816958E-11L)
#define PE11 (+9.0716956675812661308203099076399511164752025901460E-12L)
#define PE12 (-6.8444318321448459545207848393354866624083068159662E-12L)
#define PE13 (+4.6173994387736916350400699811673236291480973963125E-12L)
#define PE14 (-2.7913570982245604364511659604568378618385859468622E-12L)
#define PE15 (+1.5125367229113822074493322174026664879539216604670E-12L)
#define PE16 (-7.3311750648372577912571920421927045183342292176710E-13L)
#define PE17 (+3.1616104574960300366663810843393112699294967553964E-13L)
#define PE18 (-1.2005572840351772000525970501829389344497046628901E-13L)
#define PE19 (+3.9382817280168473244568136784041974371135086615618E-14L)
#define PE20 (-1.0683975344365246672896119927539817671636798074483E-14L)
#define PE21 (+2.0241081364723035681013709829525244803924858316069E-15L)
#define PE22 (-9.7775342352335099837670847053878704304021694984194E-17L)

/*  Coefficients for the Remez polynomial of erf on [6.0, 6.8].               */
#define PF00 (+9.9999999999999999985829196523315283381053657148749E-01L)
#define PF01 (+1.8354944706991889736170574225185834608233691723332E-18L)
#define PF02 (-1.1747164612464426039533681631454678221928036635104E-17L)
#define PF03 (+4.9509404189633766585346728552993174706266902596640E-17L)
#define PF04 (-1.5451437187193175841124128871690759192524794596198E-16L)
#define PF05 (+3.8070397073247519746574245593022224197877058992660E-16L)
#define PF06 (-7.7096463814440180432176614007709215493674036281878E-16L)
#define PF07 (+1.3191201073872314213785576600885476621927159242787E-15L)
#define PF08 (-1.9453854762495050301880643501910401094084321291545E-15L)
#define PF09 (+2.5102748712057305832097392866990847389086320960722E-15L)
#define PF10 (-2.8673051610062484523219602095456606755860858315619E-15L)
#define PF11 (+2.9257284768483380232602395400492132445290787783596E-15L)
#define PF12 (-2.6863435376402338219375486259218214334937015812710E-15L)
#define PF13 (+2.2324097213270125430728542643396885236829218376846E-15L)
#define PF14 (-1.6867393741154972379502325492434734136228570941697E-15L)
#define PF15 (+1.1629847697238120876792837655537640263464765304297E-15L)
#define PF16 (-7.3418496779009179566180841533301135713806479238260E-16L)
#define PF17 (+4.2434692086254113182297055498511340948640882993422E-16L)
#define PF18 (-2.2226497413455315812906613779153493477750128697868E-16L)
#define PF19 (+1.0830046161285075015886249883890669384810487870867E-16L)
#define PF20 (-5.5397599480457221119088883917965172823308838726517E-17L)
#define PF21 (+2.2186635970609510641152233343193720648231242630414E-17L)

/*  Coefficients for the Remez polynomial of erf on [6.8, 7.6].               */
#define PG00 (+9.9999999999999999999999762220539661112956546348220E-01L)
#define PG01 (+3.4564407965690954449648812453276257198321640089326E-23L)
#define PG02 (-2.4886369703913482043263587380313784563590193022651E-22L)
#define PG03 (+1.1830243203264572697016902371386091835574614509241E-21L)
#define PG04 (-4.1759396796014589657692623376599786795110673467316E-21L)
#define PG05 (+1.1671794662197439273425401429183059158996567635810E-20L)
#define PG06 (-2.6898295266486119324413394889928466591459303549127E-20L)
#define PG07 (+5.2554832063335491680464068138626937407665827898442E-20L)
#define PG08 (-8.8848497407494206405385099735594191521041322786319E-20L)
#define PG09 (+1.3193380949711620172423373908914659012514870040985E-19L)
#define PG10 (-1.7394223877763893882342607840178338010929317353468E-19L)
#define PG11 (+2.0618664184370454289094514717951987707352911154698E-19L)
#define PG12 (-2.2368536128716216510772126953827959651779279904777E-19L)
#define PG13 (+2.1808276707314125760840390295549601566472277461692E-19L)
#define PG14 (-1.7867179638908491573724611103472593328336354230292E-19L)
#define PG15 (+1.4775857903187872202822334854291787722097176510159E-19L)
#define PG16 (-1.6587582607702357192731560736110785247042545633269E-19L)
#define PG17 (+1.1485974589140855660120421918916369656446158163086E-19L)

/*  Coefficients for the Remez polynomial of erf on [7.6, 8.4].               */
#define PH00 (+9.9999999999999999999999999998877044356027826145533E-01L)
#define PH01 (+1.8055400329049751198030211525772945238144851019540E-28L)
#define PH02 (-1.4450001969037664463410552429282644335725253629024E-27L)
#define PH03 (+7.7331006943002617740858863712757494569120580969399E-27L)
#define PH04 (-3.0403298369335493920860982754778863657228685996133E-26L)
#define PH05 (+9.0683290616023809003350206660202822908608517399425E-26L)
#define PH06 (-2.3521502010839422984482762344181560026008636279637E-25L)
#define PH07 (+6.0719224381783851701761634011157416431626818296478E-25L)
#define PH08 (-1.1412126318549389329452218367625426832869484016319E-24L)
#define PH09 (+9.6727469813778780913478243018626764109184958237681E-25L)
#define PH10 (-1.5230430406240636661097075735956508067801315554908E-24L)
#define PH11 (+6.7501057839532475498469628613594178390372580587375E-24L)
#define PH12 (-8.0748104382609726135456739762691779195749042098812E-24L)

/*  Evaluates the first Remez polynomial using Horner's method.               */
#define TMPL_POLYA_EVAL(z) \
PA00 + z*(\
  PA01 + z*(\
    PA02 + z*(\
      PA03 + z*(\
        PA04 + z*(\
          PA05 + z*(\
            PA06 + z*(\
              PA07 + z*(\
                PA08 + z*(\
                  PA09 + z*(\
                    PA10 + z*(\
                      PA11 + z*(\
                        PA12 + z*(\
                          PA13 + z*(\
                            PA14 + z*(\
                              PA15 + z*(\
                                PA16 + z*(\
                                  PA17 + z*(\
                                    PA18 + z*(\
                                      PA19 + z*(\
                                        PA20 + z*(\
                                          PA21 + z*(\
                                            PA22 + z*(\
                                              PA23 + z*(\
                                                PA24 + z*(\
                                                  PA25 + z*PA26\
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
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the second Remez polynomial using Horner's method.              */
#define TMPL_POLYB_EVAL(z) \
PB00 + z*(\
  PB01 + z*(\
    PB02 + z*(\
      PB03 + z*(\
        PB04 + z*(\
          PB05 + z*(\
            PB06 + z*(\
              PB07 + z*(\
                PB08 + z*(\
                  PB09 + z*(\
                    PB10 + z*(\
                      PB11 + z*(\
                        PB12 + z*(\
                          PB13 + z*(\
                            PB14 + z*(\
                              PB15 + z*(\
                                PB16 + z*(\
                                  PB17 + z*(\
                                    PB18 + z*(\
                                      PB19 + z*(\
                                        PB20 + z*(\
                                          PB21 + z*(\
                                            PB22 + z*(\
                                              PB23 + z*(\
                                                PB24 + z*(\
                                                  PB25 + z*PB26\
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
                )\
              )\
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the third Remez polynomial using Horner's method.               */
#define TMPL_POLYC_EVAL(z) \
PC00 + z*(\
  PC01 + z*(\
    PC02 + z*(\
      PC03 + z*(\
        PC04 + z*(\
          PC05 + z*(\
            PC06 + z*(\
              PC07 + z*(\
                PC08 + z*(\
                  PC09 + z*(\
                    PC10 + z*(\
                      PC11 + z*(\
                        PC12 + z*(\
                          PC13 + z*(\
                            PC14 + z*(\
                              PC15 + z*(\
                                PC16 + z*(\
                                  PC17 + z*(\
                                    PC18 + z*(\
                                      PC19 + z*(\
                                        PC20 + z*(\
                                          PC21 + z*(\
                                            PC22 + z*(\
                                              PC23 + z*PC24\
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
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the fourth Remez polynomial using Horner's method.              */
#define TMPL_POLYD_EVAL(z) \
PD00 + z*(\
  PD01 + z*(\
    PD02 + z*(\
      PD03 + z*(\
        PD04 + z*(\
          PD05 + z*(\
            PD06 + z*(\
              PD07 + z*(\
                PD08 + z*(\
                  PD09 + z*(\
                    PD10 + z*(\
                      PD11 + z*(\
                        PD12 + z*(\
                          PD13 + z*(\
                            PD14 + z*(\
                              PD15 + z*(\
                                PD16 + z*(\
                                  PD17 + z*(\
                                    PD18 + z*(\
                                      PD19 + z*(\
                                        PD20 + z*(\
                                          PD21 + z*(\
                                            PD22 + z*(\
                                              PD23 + z*PD24\
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
            )\
          )\
        )\
      )\
    )\
  )\
)

/*  Evaluates the fifth Remez polynomial using Horner's method.               */
#define TMPL_POLYE_EVAL(z) \
PE00 + z*(\
  PE01 + z*(\
    PE02 + z*(\
      PE03 + z*(\
        PE04 + z*(\
          PE05 + z*(\
            PE06 + z*(\
              PE07 + z*(\
                PE08 + z*(\
                  PE09 + z*(\
                    PE10 + z*(\
                      PE11 + z*(\
                        PE12 + z*(\
                          PE13 + z*(\
                            PE14 + z*(\
                              PE15 + z*(\
                                PE16 + z*(\
                                  PE17 + z*(\
                                    PE18 + z*(\
                                      PE19 + z*(\
                                        PE20 + z*(\
                                          PE21 + z*PE22\
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
        )\
      )\
    )\
  )\
)

/*  Evaluates the sixth Remez polynomial using Horner's method.               */
#define TMPL_POLYF_EVAL(z) \
PF00 + z*(\
  PF01 + z*(\
    PF02 + z*(\
      PF03 + z*(\
        PF04 + z*(\
          PF05 + z*(\
            PF06 + z*(\
              PF07 + z*(\
                PF08 + z*(\
                  PF09 + z*(\
                    PF10 + z*(\
                      PF11 + z*(\
                        PF12 + z*(\
                          PF13 + z*(\
                            PF14 + z*(\
                              PF15 + z*(\
                                PF16 + z*(\
                                  PF17 + z*(\
                                    PF18 + z*(\
                                      PF19 + z*(\
                                        PF20 + z*PF21\
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
      )\
    )\
  )\
)

/*  Evaluates the seventh Remez polynomial using Horner's method.             */
#define TMPL_POLYG_EVAL(z) \
PG00 + z*(\
  PG01 + z*(\
    PG02 + z*(\
      PG03 + z*(\
        PG04 + z*(\
          PG05 + z*(\
            PG06 + z*(\
              PG07 + z*(\
                PG08 + z*(\
                  PG09 + z*(\
                    PG10 + z*(\
                      PG11 + z*(\
                        PG12 + z*(\
                          PG13 + z*(\
                            PG14 + z*(\
                              PG15 + z*(\
                                PG16 + z*PG17\
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

/*  Evaluates the eigth Remez polynomial using Horner's method.               */
#define TMPL_POLYH_EVAL(z) \
PH00 + z*(\
  PH01 + z*(\
    PH02 + z*(\
      PH03 + z*(\
        PH04 + z*(\
          PH05 + z*(\
            PH06 + z*(\
              PH07 + z*(\
                PH08 + z*(\
                  PH09 + z*(\
                    PH10 + z*(\
                      PH11 + z*PH12\
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

/*  Function for computing erf(x) for x >= 2.                                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Asymptotic(long double x)
{
    /*  For large enough values use the limit, erf(infinity) = 1.             */
    if (x >= 8.4L)
        return 1.0L;

    /*  For values in [2, 2.8] use the first polynomial.                      */
    else if (x < 2.8L)
    {
        /*  Shift the interval [2, 2.8] to [-0.4, 0.4] for the polynomial.    */
        const long double z = x - 2.4L;
        return TMPL_POLYA_EVAL(z);
    }

    /*  For values in [2.8, 3.6] use the second polynomial.                   */
    else if (x < 3.6L)
    {
        /*  Shift the interval [2.8, 3.6] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 3.2L;
        return TMPL_POLYB_EVAL(z);
    }

    /*  For values in [3.6, 4.4] use the third polynomial.                    */
    else if (x < 4.4L)
    {
        /*  Shift the interval [3.6, 4.4] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 4.0L;
        return TMPL_POLYC_EVAL(z);
    }

    /*  For values in [4.4, 5.2] use the fourth polynomial.                   */
    else if (x < 5.2L)
    {
        /*  Shift the interval [4.4, 5.2] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 4.8L;
        return TMPL_POLYD_EVAL(z);
    }

    /*  For values in [5.2, 6.0] use the fifth polynomial.                    */
    else if (x < 6.0L)
    {
        /*  Shift the interval [5.2, 6.0] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 5.6L;
        return TMPL_POLYE_EVAL(z);
    }

    /*  For values in [6.0, 6.8] use the sixth polynomial.                    */
    else if (x < 6.8L)
    {
        /*  Shift the interval [6.0, 6.8] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 6.4L;
        return TMPL_POLYF_EVAL(z);
    }

    /*  For values in [6.0, 6.8] use the seventh polynomial.                  */
    else if (x < 7.6L)
    {
        /*  Shift the interval [6.8, 7.6] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 7.2L;
        return TMPL_POLYG_EVAL(z);
    }

    /*  Lastly for values in [7.6, 8.4] use the eigth polynomial.             */
    else
    {
        /*  Shift the interval [7.6, 8.4] to [-0.4, 0.4] for the polynomial.  */
        const long double z = x - 8.0L;
        return TMPL_POLYH_EVAL(z);
    }
}
/*  End of tmpl_LDouble_Erf_Asymptotic.                                       */

/*  Undefine everything in case someone wants to #include this file.          */
#undef TMPL_POLYA_EVAL
#undef TMPL_POLYB_EVAL
#undef TMPL_POLYC_EVAL
#undef TMPL_POLYD_EVAL
#undef TMPL_POLYE_EVAL
#undef TMPL_POLYF_EVAL
#undef TMPL_POLYG_EVAL
#undef TMPL_POLYH_EVAL
#undef PA00
#undef PA01
#undef PA02
#undef PA03
#undef PA04
#undef PA05
#undef PA06
#undef PA07
#undef PA08
#undef PA09
#undef PA10
#undef PA11
#undef PA12
#undef PA13
#undef PA14
#undef PA15
#undef PA16
#undef PA17
#undef PA18
#undef PA19
#undef PA20
#undef PA21
#undef PA22
#undef PA23
#undef PA24
#undef PA25
#undef PA26
#undef PB00
#undef PB01
#undef PB02
#undef PB03
#undef PB04
#undef PB05
#undef PB06
#undef PB07
#undef PB08
#undef PB09
#undef PB10
#undef PB11
#undef PB12
#undef PB13
#undef PB14
#undef PB15
#undef PB16
#undef PB17
#undef PB18
#undef PB19
#undef PB20
#undef PB21
#undef PB22
#undef PB23
#undef PB24
#undef PB25
#undef PB26
#undef PC00
#undef PC01
#undef PC02
#undef PC03
#undef PC04
#undef PC05
#undef PC06
#undef PC07
#undef PC08
#undef PC09
#undef PC10
#undef PC11
#undef PC12
#undef PC13
#undef PC14
#undef PC15
#undef PC16
#undef PC17
#undef PC18
#undef PC19
#undef PC20
#undef PC21
#undef PC22
#undef PC23
#undef PC24
#undef PD00
#undef PD01
#undef PD02
#undef PD03
#undef PD04
#undef PD05
#undef PD06
#undef PD07
#undef PD08
#undef PD09
#undef PD10
#undef PD11
#undef PD12
#undef PD13
#undef PD14
#undef PD15
#undef PD16
#undef PD17
#undef PD18
#undef PD19
#undef PD20
#undef PD21
#undef PD22
#undef PD23
#undef PD24
#undef PE00
#undef PE01
#undef PE02
#undef PE03
#undef PE04
#undef PE05
#undef PE06
#undef PE07
#undef PE08
#undef PE09
#undef PE10
#undef PE11
#undef PE12
#undef PE13
#undef PE14
#undef PE15
#undef PE16
#undef PE17
#undef PE18
#undef PE19
#undef PE20
#undef PE21
#undef PE22
#undef PF00
#undef PF01
#undef PF02
#undef PF03
#undef PF04
#undef PF05
#undef PF06
#undef PF07
#undef PF08
#undef PF09
#undef PF10
#undef PF11
#undef PF12
#undef PF13
#undef PF14
#undef PF15
#undef PF16
#undef PF17
#undef PF18
#undef PF19
#undef PF20
#undef PF21
#undef PG00
#undef PG01
#undef PG02
#undef PG03
#undef PG04
#undef PG05
#undef PG06
#undef PG07
#undef PG08
#undef PG09
#undef PG10
#undef PG11
#undef PG12
#undef PG13
#undef PG14
#undef PG15
#undef PG16
#undef PG17
#undef PH00
#undef PH01
#undef PH02
#undef PH03
#undef PH04
#undef PH05
#undef PH06
#undef PH07
#undef PH08
#undef PH09
#undef PH10
#undef PH11
#undef PH12

#endif
/*  End of check for 128-bit double-double.                                   */

#endif
/*  End of include guard.                                                     */
