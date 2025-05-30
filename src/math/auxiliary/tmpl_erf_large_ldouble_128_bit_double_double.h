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
#ifndef TMPL_ERF_LARGE_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H
#define TMPL_ERF_LARGE_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H

/*  TMPL_LDOUBLE_TYPE macro provided here.                                    */
#include <libtmpl/include/tmpl_config.h>

/*  Only use this code for 128-bit double-double.                             */
#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

/*  tmpl_IEEE754_LDouble and tmpl_IEEE754_Double typedef's found here.        */
#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

/*  Coefficients for the Remez polynomial on [1.99951171875, 2.50048828125].  */
#define A00 (+9.9853728341331884830208920362701704859637514293612E-01L)
#define A01 (+7.1423190220179830392855515665922946287266731671241E-03L)
#define A02 (-1.6070217799540461838392491024754285089293484559809E-02L)
#define A03 (+2.1724553691971365077826885947945342356411964533065E-02L)
#define A04 (-1.9083383636954298433091083081497390168070871131208E-02L)
#define A05 (+1.0657679165667459066433941873383594744743293860086E-02L)
#define A06 (-2.9043570710627813843344796399151767633414903861296E-03L)
#define A07 (-6.7045596995189269732435573480250118647385010109357E-04L)
#define A08 (+9.9949371261139279602727354984791708749546773074477E-04L)
#define A09 (-3.6938041770393948369031252288671849609152565940447E-04L)
#define A10 (-1.1466583164141506817286304292125755369502119236941E-05L)
#define A11 (+6.5134943282338820322528360100477974508749565386133E-05L)
#define A12 (-2.2688242645401096168239227945190473078295550707456E-05L)
#define A13 (-1.3320746753794253499043241607457575291757464893056E-06L)
#define A14 (+3.4200230329643915914338587407307705740284227848737E-06L)
#define A15 (-8.6108337878597607183300923413757958158715722798450E-07L)
#define A16 (-1.5682298692839933415929391656857557562602415206800E-07L)
#define A17 (+1.3648440175529809426127239226184593770659391774754E-07L)
#define A18 (-1.7721310271625312132489533849902593737072305225458E-08L)
#define A19 (-9.3715215263242630943017966986287213196928962510072E-09L)
#define A20 (+3.7874436442499474492720817119575922136014807090426E-09L)
#define A21 (+3.6797646170177439256466888895826819469154245748258E-11L)
#define A22 (-3.3535563534968567553589080124316437169613207213104E-10L)
#define A23 (+5.9700492748041620274435703552607304742480003356009E-11L)
#define A24 (+1.5066449928157542676099574895519586910568632983047E-11L)

/*  Coefficients for the Remez polynomial on [2.49951171875, 3.00048828125].  */
#define B00 (+9.9989937807788036316309560802491484384890283979433E-01L)
#define B01 (+5.8627724709379232629721438471101770938305852034991E-04L)
#define B02 (-1.6122624295079288973173395662890743094165054286179E-03L)
#define B03 (+2.7603887050666055363160510972103695462865682925211E-03L)
#define B04 (-3.2581136596306063133287840713420176891209389019732E-03L)
#define B05 (+2.7558084140736852837668377144760034848903258105056E-03L)
#define B06 (-1.6573274036660498265671427933743426313664266090897E-03L)
#define B07 (+6.4604095667244741521742847567963267999086197312739E-04L)
#define B08 (-8.9011571212439777693738697408634406458350751844033E-05L)
#define B09 (-7.1223114723151577943861705201187184537006059419486E-05L)
#define B10 (+5.4996992424389302090581598262982306561444248389347E-05L)
#define B11 (-1.5843804712042556596921176219611847623476403101780E-05L)
#define B12 (-1.0711338137046374953973516100587141670220453514474E-06L)
#define B13 (+2.6875547139057991364456565981599674421895587837441E-06L)
#define B14 (-9.1457665124036018509767280632568897937896489243005E-07L)
#define B15 (+2.5999028098127682648192600855018189865786811383596E-09L)
#define B16 (+1.0580689416154654113646055985171688787142406781403E-07L)
#define B17 (-3.4518396865176278895985164714335234179005145236844E-08L)
#define B18 (-5.1750933464857134152327452081696428856288766740692E-10L)
#define B19 (+3.5814685589309106490915063347801138333876988780292E-09L)
#define B20 (-9.3562275675533548120010064188472837726213038249334E-10L)
#define B21 (-7.9087057850146507462380710848911211258148645496325E-11L)
#define B22 (+9.9236383339428625179322483047099515040416179170110E-11L)
#define B23 (-1.6645643406718417961759336403468108811213837549505E-11L)

/*  Coefficients for the Remez polynomial on [2.99951171875, 3.50048828125].  */
#define C00 (+9.9999569722053632487816952410486930909153624227428E-01L)
#define C01 (+2.9189025383581700722234265079220572620779333656200E-05L)
#define C02 (-9.4864332496640527347261359403956805181177089817541E-05L)
#define C03 (+1.9580971194819390901165485335136366171987980842688E-04L)
#define C04 (-2.8656933775026825969485361488556513262500427518611E-04L)
#define C05 (+3.1379722549089056489981492497034678830666229089196E-04L)
#define C06 (-2.6352850421505990938902980106647296806079231020324E-04L)
#define C07 (+1.6999141451139120993235487684217351841732550770023E-04L)
#define C08 (-8.1647630530135377559737384194429744393243349934960E-05L)
#define C09 (+2.5913847005660593016236550017129433646005516319090E-05L)
#define C10 (-2.3288662372108672698736506777829304728308366154817E-06L)
#define C11 (-2.8642994607562241548614496496805501346076042383743E-06L)
#define C12 (+1.9043540620320993611144741417336823093813843260317E-06L)
#define C13 (-5.4823736347334725152773867965153447487590533852443E-07L)
#define C14 (+3.4151633370819304955426692763933581764410428947971E-09L)
#define C15 (+6.6397102788279026597003446851411407379682068566028E-08L)
#define C16 (-2.7372259093880003057515669757747939064577201875295E-08L)
#define C17 (+3.1426540214548377318303185013588200159812985801366E-09L)
#define C18 (+1.7276172401481026851220757158401024243709305605225E-09L)
#define C19 (-9.0345629141411732347582460673293918502349849765203E-10L)
#define C20 (+1.2989025845265397822581153186147959068501665555295E-10L)
#define C21 (+4.1553954024415157693791759844788377345531948654881E-11L)
#define C22 (-2.3134410580136746199662379530677456656413491254736E-11L)
#define C23 (+2.9952877032170052593809933079851014758452893539599E-12L)

/*  Coefficients for the Remez polynomial on [3.49951171875, 4.00048828125].  */
#define D00 (+9.9999988627274343020334674092341719384935610068652E-01L)
#define D01 (+8.8143219123180396655047398871094305046746641809170E-07L)
#define D02 (-3.3053707171192648745642785787632453226331368085331E-06L)
#define D03 (+7.9696160623875608642273046041083783315496696001269E-06L)
#define D04 (-1.3841239877936921662237311903246565310354602486287E-05L)
#define D05 (+1.8370974998189114234046410911285555029540057794187E-05L)
#define D06 (-1.9272721446953213682848016205229561022874329085487E-05L)
#define D07 (+1.6275302741214368421927290861880605384842707362836E-05L)
#define D08 (-1.1128227438398496003216540776960422104087251210859E-05L)
#define D09 (+6.1088806656515075198666805921266545480951946570557E-06L)
#define D10 (-2.6033089546344562843216955701468034150045652168070E-06L)
#define D11 (+7.7534836014421031407257034558433951817753658048570E-07L)
#define D12 (-9.0151974387793665336410087269248061907706556923492E-08L)
#define D13 (-5.7333245055317144224392906693558593013094048394206E-08L)
#define D14 (+4.2602410863939581849549245277318487076896816393248E-08L)
#define D15 (-1.4202803600354634536020474450183699545049676332744E-08L)
#define D16 (+1.6872830473703524592793158801567669501269838267158E-09L)
#define D17 (+8.2209498993856175169338210675277407281954554378620E-10L)
#define D18 (-5.1898950238353738632292443343226429274172765031863E-10L)
#define D19 (+1.2314809790093988274667325028974728656046555822445E-10L)
#define D20 (+3.0073448441854093761746438048016701776926324367185E-12L)
#define D21 (-1.2296215888510685802015957449482275680749793414421E-11L)
#define D22 (+3.8124365972046155961898197438678715601097157974431E-12L)

/*  Coefficients for the Remez polynomial on [3.99951171875, 4.50048828125].  */
#define E00 (+9.9999999814942586261325747994416189130682645138516E-01L)
#define E01 (+1.6143993719507411497195585282632501452768139270214E-08L)
#define E02 (-6.8611973307906498863081137977276360986913229436538E-08L)
#define E03 (+1.8901925979923260961301752382185750723226086933800E-07L)
#define E04 (-3.7879526930406712914003871374570501923085592465005E-07L)
#define E05 (+5.8724617987714433664607821155442691024583213298281E-07L)
#define E06 (-7.3092001634486990912509393321228532060222493149066E-07L)
#define E07 (+7.4772521511468862056834811466392890618545749335998E-07L)
#define E08 (-6.3783232327117025307006757727001784100094505812341E-07L)
#define E09 (+4.5700618015047117618633426106628995246708592396933E-07L)
#define E10 (-2.7506284010191443639091843185499180054024120306645E-07L)
#define E11 (+1.3776572878141290945016249480264072514856449967691E-07L)
#define E12 (-5.5907869992617771231162953761075696345065967346343E-08L)
#define E13 (+1.7126645551195503031380384128783398578932809813287E-08L)
#define E14 (-3.0258541401028181353457808400393524690482237841899E-09L)
#define E15 (-4.0579113859275697685376841071674734840323722679967E-10L)
#define E16 (+5.6859284742377603919781218738361646236925058007844E-10L)
#define E17 (-2.3954026486047354333634851026677741420106395748590E-10L)
#define E18 (+5.3655726088151485881971289132738802611889034289469E-11L)
#define E19 (-1.8750839900309480894465176377915391841554912276440E-13L)
#define E20 (-5.0053023073602035304838855919338932046505375969410E-12L)
#define E21 (+2.0274599393522048816260859016837749178927839087812E-12L)
#define E22 (-3.3938123894301217002270167536128462385604418637090E-13L)

/*  Coefficients for the Remez polynomial on [4.49951171875, 5.00048828125].  */
#define F00 (+9.9999999998151495227851468911257034002359223095828E-01L)
#define F01 (+1.7934357034341337193962679723768436104823521182015E-10L)
#define F02 (-8.5188195913121351671224104392626253277313541048346E-10L)
#define F03 (+2.6378450138010383456003698832448226310024057270036E-09L)
#define F04 (-5.9809212547337282325271154713363265813626987068007E-09L)
#define F05 (+1.0572396879853772141404584568994401100691922935711E-08L)
#define F06 (-1.5144716058506144871499220781804044000371411896450E-08L)
#define F07 (+1.8036305869912202657000069697730228921498296859474E-08L)
#define F08 (-1.8172816922269443958394564649933684662569888761912E-08L)
#define F09 (+1.5675358387690432310713131289386982692760302708436E-08L)
#define F10 (-1.1660867459900959485595675119535372694413212834364E-08L)
#define F11 (+7.5056905246524377926308323142270986094136798643020E-09L)
#define F12 (-4.1752068987675769768568017641512843671734355234940E-09L)
#define F13 (+1.9926179162774378186870261911943085643522435906407E-09L)
#define F14 (-8.0155685007332323685305794509173912863060570286078E-10L)
#define F15 (+2.6094759268112293743936187356786236375645024058748E-10L)
#define F16 (-6.1422706921576041619688011880873348855280425732196E-11L)
#define F17 (+5.5435319136955084074300242510962488701845893613170E-12L)
#define F18 (+3.4980075088362335607734037974541348662808483333220E-12L)
#define F19 (-2.3007834298311440049625372125860447839481661394312E-12L)
#define F20 (+7.5831927299514077968788865569645020378444777392020E-13L)
#define F21 (-1.3080222957661488995939558246640517335346069357396E-13L)

/*  Coefficients for the Remez polynomial on [4.99951171875, 5.50048828125].  */
#define G00 (+9.9999999999988689686733112846117243303956638086595E-01L)
#define G01 (+1.2084074716006755033256607375876905230844783060677E-12L)
#define G02 (-6.3441392259035463925171545761278326101870800671074E-12L)
#define G03 (+2.1801684800128853645795457945663786261687296520911E-11L)
#define G04 (-5.5114709525037058653426450656730330770218053260967E-11L)
#define G05 (+1.0920038456253924515242664110147033639428451270662E-10L)
#define G06 (-1.7640341711110047216553164394609918085754969795463E-10L)
#define G07 (+2.3860503410412904456538616521989690798894620452126E-10L)
#define G08 (-2.7536837502357530933283826867683094840996161372608E-10L)
#define G09 (+2.7486768089721473309610650326596500121353834908866E-10L)
#define G10 (-2.3965668716018736848915212718281857789321825184900E-10L)
#define G11 (+1.8378485354127452934338811403330278084998604198398E-10L)
#define G12 (-1.2450012757822628952839010788896024379241484681462E-10L)
#define G13 (+7.4639420391512299132628738664986900584361669179876E-11L)
#define G14 (-3.9561966160954349301135832542658498611906883634832E-11L)
#define G15 (+1.8452267626082032233959479752298193372781031259848E-11L)
#define G16 (-7.4937358671729644068742445874901102703241370075625E-12L)
#define G17 (+2.5937830235645946270717918434169682123325791099072E-12L)
#define G18 (-7.2940536545535442940732383775117961913167958584594E-13L)
#define G19 (+1.4186197751844522777106757634883127712023108251408E-13L)
#define G20 (-5.2177695507644570160946626007237273573787089963210E-15L)

/*  Coefficients for the Remez polynomial on [5.49951171875, 6.00048828125].  */
#define H00 (+9.9999999999999957678633825742624680018793755020627E-01L)
#define H01 (+4.9384851409642187608298611267111922685213837364094E-15L)
#define H02 (-2.8396289560544288103532832170177772945396382097364E-14L)
#define H03 (+1.0720628160176496909845284975894626806175937371812E-13L)
#define H04 (-2.9875262975154363336142314902737483822772463487802E-13L)
#define H05 (+6.5496916394804048552850375362007197288556032127150E-13L)
#define H06 (-1.1756901963032395159339361112175662439037013161692E-12L)
#define H07 (+1.7755459977457957595675144734625822378168724303058E-12L)
#define H08 (-2.3004137579304768089207916317734727468273420901170E-12L)
#define H09 (+2.5941725246895622337449049657963249062736473829920E-12L)
#define H10 (-2.5743359774986439204509264827672563249664658708855E-12L)
#define H11 (+2.2668502795007511314066912773347189963145337096761E-12L)
#define H12 (-1.7823465560195129324558450196456599560043210788368E-12L)
#define H13 (+1.2570075102804404216625788321824717079289478840238E-12L)
#define H14 (-7.9752337371641624854947487607388186187766099651543E-13L)
#define H15 (+4.5579849640577554539765034106462158503607530118814E-13L)
#define H16 (-2.3434133553711893109581725907261347053468836254563E-13L)
#define H17 (+1.0833172933186960371296269030949289174612390029939E-13L)
#define H18 (-4.6351261743364675086367691248036427418448521731561E-14L)
#define H19 (+1.6758351569489450355746450661431444674838581714310E-14L)

/*  Coefficients for the Remez polynomial on [5.99951171875, 6.50048828125].  */
#define I00 (+9.9999999999999999903277958681237523948526962649492E-01L)
#define I01 (+1.2241280792599983989131461521900695180753492295109E-17L)
#define I02 (-7.6508004953748874512213460445805502278058687842106E-17L)
#define I03 (+3.1470292704264101920804412499027815804700326947864E-16L)
#define I04 (-9.5794397869082295008673277123284987641829537442842E-16L)
#define I05 (+2.3004490687392548025096077429982756167095920947094E-15L)
#define I06 (-4.5371504987991029208102389576788969654871046271649E-15L)
#define I07 (+7.5543284774682558041514349520084799159416499020868E-15L)
#define I08 (-1.0831391719134440309907922400886984141537583415812E-14L)
#define I09 (+1.3574703505213781098700548438882863254977926244162E-14L)
#define I10 (-1.5042798162990467446641796102275416485966222117776E-14L)
#define I11 (+1.4872729127878890707975453272968084654642945521531E-14L)
#define I12 (-1.3213230046573894803654954669453418038057250826286E-14L)
#define I13 (+1.0608685256179788504084220211466707128095725598905E-14L)
#define I14 (-7.7293086418911798484647698598035235308417491442193E-15L)
#define I15 (+5.1117196509375545018625478369636070336353531009725E-15L)
#define I16 (-3.0959278831836791204260457216169407730407951171700E-15L)
#define I17 (+1.8394109239383305227943355123121898650552393255169E-15L)
#define I18 (-9.2441983435524144572187651807127906682999699556273E-16L)

/*  Coefficients for the Remez polynomial on [6.49951171875, 7.00048828125].  */
#define J00 (+9.9999999999999999999865123211063795173576994463398E-01L)
#define J01 (+1.8404021315846652197962713962293734712422959116104E-20L)
#define J02 (-1.2422714387953554274975548450186501695225065091234E-19L)
#define J03 (+5.5288747368886970120646252308281847855004293451623E-19L)
#define J04 (-1.8245861767711876036117812687308497002497498624681E-18L)
#define J05 (+4.7605164344444881719628957464640142403694321188092E-18L)
#define J06 (-1.0224605495162184511991734057945904595386430081187E-17L)
#define J07 (+1.8585425816690972622139939965286383842242174844700E-17L)
#define J08 (-2.9171932975382973307831582592913234515485348578478E-17L)
#define J09 (+4.0144061372194436807644310928212399806343130256779E-17L)
#define J10 (-4.9007726447971738430425418995824649710376776376293E-17L)
#define J11 (+5.3577014481739844563700083478131467137980448859406E-17L)
#define J12 (-5.2865891349604817704875230028002098743920793222066E-17L)
#define J13 (+4.7339024575820428762044569428148483661553789406058E-17L)
#define J14 (-3.8406623880881640735654348414454189729099429214373E-17L)
#define J15 (+2.8764739632314607781288831804830141167523731236482E-17L)
#define J16 (-2.2086849138887992923044670850593586669389888073094E-17L)
#define J17 (+1.3924408128513897785940499766307490841436734931747E-17L)

/*  Coefficients for the Remez polynomial on [6.99951171875, 7.50048828125].  */
#define K00 (+9.9999999999999999999999885330991962649660509464700E-01L)
#define K01 (+1.6782295476554962358799559036844126356098460546888E-23L)
#define K02 (-1.2167164169541301356989934935491962852646612787307E-22L)
#define K03 (+5.8248528876419865411580277032758880064683401304756E-22L)
#define K04 (-2.0709521047742776016700740000757729888383943619130E-21L)
#define K05 (+5.8310523121491988198781237384026776148992895808162E-21L)
#define K06 (-1.3539439541517396560144040515880675791458473749834E-20L)
#define K07 (+2.6654848820831294778703836257012327116090267162776E-20L)
#define K08 (-4.5411503437940799263699349307520660173921914933948E-20L)
#define K09 (+6.8088516841818097170947902831874392693624523757485E-20L)
#define K10 (-9.0628127890548373817607998773091413862841756700961E-20L)
#define K11 (+1.0606319045164017705379555834007277712694585350753E-19L)
#define K12 (-1.1488271280339292446551496224233643538578423132753E-19L)
#define K13 (+1.3716259764050894255241122618020919952157295885309E-19L)
#define K14 (-1.2291534971007341309167022385396313870845960858317E-19L)

/*  Coefficients for the Remez polynomial on [7.49951171875, 8.00048828125].  */
#define L00 (+9.9999999999999999999999999940603057859847197414623E-01L)
#define L01 (+9.2819561742149995362868398428072506266010638351124E-27L)
#define L02 (-7.1941819235192829868998122029069998263096566897765E-26L)
#define L03 (+3.6860033608688022333670131581270668328308351070425E-25L)
#define L04 (-1.4031144576703272008142942013665620835974363543740E-24L)
#define L05 (+4.2396039569007008979922506359635367844682725651507E-24L)
#define L06 (-1.0661522499180097875860341266761864088834909690905E-23L)
#define L07 (+2.2574343431097862445017048897159924967508556429750E-23L)
#define L08 (-3.8898699954309544866128877355964607836081144976237E-23L)
#define L09 (+6.3130222479754264624899803797919096299863138335654E-23L)
#define L10 (-1.2703305607759812754020050500591479287369541183324E-22L)
#define L11 (+1.6305819586029719838622534566643071898290641013128E-22L)

/*  Coefficients for the Remez polynomial on [7.99951171875, 8.50048828125].  */
#define M00 (+9.9999999999999999999999999999981646471844376264011E-01L)
#define M01 (+3.0610032655162013850238925798791753641141331409740E-30L)
#define M02 (-2.7600173814593923287428117406584148254127477613032E-29L)
#define M03 (+1.4929921566217462863671483705332995865063057933078E-28L)
#define M04 (-4.2282382288854203319149770644060643959715970874392E-28L)
#define M05 (+1.4087085069913640868606141134189799079105993101580E-27L)
#define M06 (-8.3953636058906243543107218196693845415524103377252E-27L)
#define M07 (+1.8630359356331525942840976635370953533319302332889E-26L)

/*  Helper macros for evaluating polynomials via Horner's method.             */
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
                                  A17 + z*(\
                                    A18 + z*(\
                                      A19 + z*(\
                                        A20 + z*(\
                                          A21 + z*(\
                                            A22 + z*(\
                                              A23 + z*A24\
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
                                B16 + z*(\
                                  B17 + z*(\
                                    B18 + z*(\
                                      B19 + z*(\
                                        B20 + z*(\
                                          B21 + z*(\
                                            B22 + z*B23\
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
                                  C17 + z*(\
                                    C18 + z*(\
                                      C19 + z*(\
                                        C20 + z*(\
                                          C21 + z*(\
                                            C22 + z*C23\
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
                                D16 + z*(\
                                  D17 + z*(\
                                    D18 + z*(\
                                      D19 + z*(\
                                        D20 + z*(\
                                          D21 + z*D22\
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
E00 + z*(\
  E01 + z*(\
    E02 + z*(\
      E03 + z*(\
        E04 + z*(\
          E05 + z*(\
            E06 + z*(\
              E07 + z*(\
                E08 + z*(\
                  E09 + z*(\
                    E10 + z*(\
                      E11 + z*(\
                        E12 + z*(\
                          E13 + z*(\
                            E14 + z*(\
                              E15 + z*(\
                                E16 + z*(\
                                  E17 + z*(\
                                    E18 + z*(\
                                      E19 + z*(\
                                        E20 + z*(\
                                          E21 + z*E22\
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
F00 + z*(\
  F01 + z*(\
    F02 + z*(\
      F03 + z*(\
        F04 + z*(\
          F05 + z*(\
            F06 + z*(\
              F07 + z*(\
                F08 + z*(\
                  F09 + z*(\
                    F10 + z*(\
                      F11 + z*(\
                        F12 + z*(\
                          F13 + z*(\
                            F14 + z*(\
                              F15 + z*(\
                                F16 + z*(\
                                  F17 + z*(\
                                    F18 + z*(\
                                      F19 + z*(\
                                        F20 + z*F21\
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
G00 + z*(\
  G01 + z*(\
    G02 + z*(\
      G03 + z*(\
        G04 + z*(\
          G05 + z*(\
            G06 + z*(\
              G07 + z*(\
                G08 + z*(\
                  G09 + z*(\
                    G10 + z*(\
                      G11 + z*(\
                        G12 + z*(\
                          G13 + z*(\
                            G14 + z*(\
                              G15 + z*(\
                                G16 + z*(\
                                  G17 + z*(\
                                    G18 + z*(\
                                      G19 + z*G20\
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

/*  Evaluates the eigth Remez polynomial using Horner's method.               */
#define TMPL_POLYH_EVAL(z) \
H00 + z*(\
  H01 + z*(\
    H02 + z*(\
      H03 + z*(\
        H04 + z*(\
          H05 + z*(\
            H06 + z*(\
              H07 + z*(\
                H08 + z*(\
                  H09 + z*(\
                    H10 + z*(\
                      H11 + z*(\
                        H12 + z*(\
                          H13 + z*(\
                            H14 + z*(\
                              H15 + z*(\
                                H16 + z*(\
                                  H17 + z*(\
                                    H18 + z*H19\
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

#define TMPL_POLYI_EVAL(z) \
I00 + z*(\
  I01 + z*(\
    I02 + z*(\
      I03 + z*(\
        I04 + z*(\
          I05 + z*(\
            I06 + z*(\
              I07 + z*(\
                I08 + z*(\
                  I09 + z*(\
                    I10 + z*(\
                      I11 + z*(\
                        I12 + z*(\
                          I13 + z*(\
                            I14 + z*(\
                              I15 + z*(\
                                I16 + z*(\
                                  I17 + z*I18\
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

#define TMPL_POLYJ_EVAL(z) \
J00 + z*(\
  J01 + z*(\
    J02 + z*(\
      J03 + z*(\
        J04 + z*(\
          J05 + z*(\
            J06 + z*(\
              J07 + z*(\
                J08 + z*(\
                  J09 + z*(\
                    J10 + z*(\
                      J11 + z*(\
                        J12 + z*(\
                          J13 + z*(\
                            J14 + z*(\
                              J15 + z*(\
                                J16 + z*J17\
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

#define TMPL_POLYK_EVAL(z) \
K00 + z*(\
  K01 + z*(\
    K02 + z*(\
      K03 + z*(\
        K04 + z*(\
          K05 + z*(\
            K06 + z*(\
              K07 + z*(\
                K08 + z*(\
                  K09 + z*(\
                    K10 + z*(\
                      K11 + z*(\
                        K12 + z*(\
                          K13 + z*K14\
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

#define TMPL_POLYL_EVAL(z) \
L00 + z*(\
  L01 + z*(\
    L02 + z*(\
      L03 + z*(\
        L04 + z*(\
          L05 + z*(\
            L06 + z*(\
              L07 + z*(\
                L08 + z*(\
                  L09 + z*(\
                    L10 + z*L11\
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

#define TMPL_POLYM_EVAL(z) \
M00+z*(M01+z*(M02+z*(M03+z*(M04+z*(M05+z*(M06+z*M07))))))

/*  Function for computing erf(x) for x >= 2.                                 */
TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Large(long double x)
{
    tmpl_IEEE754_LDouble w;
    tmpl_IEEE754_Double shift;
    unsigned int n;
    long double z;

    if (x > 8.5L)
        return 1.0L;

    w.r = x;
    shift.r = w.d[0] + 549755813886.0;
    n = shift.bits.man3 >> 12;

    switch(n)
    {
        case 0:
            z = x - 2.25L;
            return TMPL_POLYA_EVAL(z);
        case 1:
            z = x - 2.75L;
            return TMPL_POLYB_EVAL(z);
        case 2:
            z = x - 3.25L;
            return TMPL_POLYC_EVAL(z);
        case 3:
            z = x - 3.75L;
            return TMPL_POLYD_EVAL(z);
        case 4:
            z = x - 4.25L;
            return TMPL_POLYE_EVAL(z);
        case 5:
            z = x - 4.75L;
            return TMPL_POLYF_EVAL(z);
        case 6:
            z = x - 5.25L;
            return TMPL_POLYG_EVAL(z);
        case 7:
            z = x - 5.75L;
            return TMPL_POLYH_EVAL(z);
        case 8:
            z = x - 6.25L;
            return TMPL_POLYI_EVAL(z);
        case 9:
            z = x - 6.75L;
            return TMPL_POLYJ_EVAL(z);
        case 10:
            z = x - 7.25L;
            return TMPL_POLYK_EVAL(z);
        case 11:
            z = x - 7.75L;
            return TMPL_POLYL_EVAL(z);
        case 12:
            z = x - 8.25L;
            return TMPL_POLYM_EVAL(z);
        default:
            return 1.0L;
    }
}
/*  End of tmpl_LDouble_Erf_Large.                                            */

/*  Undefine everything in case someone wants to #include this file.          */
#include "tmpl_math_undef.h"

#endif
/*  End of check for 128-bit double-double.                                   */

#endif
/*  End of include guard.                                                     */
