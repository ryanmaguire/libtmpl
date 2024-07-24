
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

/*  Declaration given here.                                                   */
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  Remez coefficients for the Normalized Fresnel cosine function on [1, 2].  */
const float tmpl_float_normalized_fresnel_cos_table[128] = {
    +7.7989338985324144980506834215206970051496774302531E-01F,
    +1.0685096972750154710719375830980441660174899918986E-05F,
    -1.5724884665886533796286047527971378745365515958542E+00F,
    -4.3850195344491032427777531993603074507284533736797E-01F,
    +7.7834470673428731677391221823976778436252927321504E-01F,
    -9.9531062067195941017680931724820594345806864007672E-02F,
    -1.6138296363222470049094565258355890585311588489461E+00F,
    -2.4644137442712943474257903508467383444894806249385E-01F,
    +7.7365083303985050990578656107639549681205369066498E-01F,
    -2.0109022572615079543529826517868791240404204689214E-01F,
    -1.6371620823747478823850495351267075690157415599105E+00F,
    -2.3797294761349247741202782845223679459403662801617E-02F,
    +7.6576724453954080744244555181396746293871684575778E-01F,
    -3.0345176149591846916571840475315498743167143512601E-01F,
    -1.6396113603754689095208084522527466237607947545163E+00F,
    +2.2861154589119153392276481508029839785238706039445E-01F,
    +7.5469016923676393093259786040130100536028315201350E-01F,
    -4.0522349598639114933368024619025807883339007127104E-01F,
    -1.6183786924254763770302113060045442066509570292499E+00F,
    +5.0894162573022966382310296800214100214944947749410E-01F,
    +7.4046201748248533591325375722962138874489635690114E-01F,
    -5.0484387520111464790742598516555123892515893918502E-01F,
    -1.5708371272180167707095531612563041578443491351996E+00F,
    +8.1418508315530014059781717360571936430297973541695E-01F,
    +7.2317647178574838559238886928102052450768652109851E-01F,
    -6.0059613002353682669252777014864984853358334261839E-01F,
    -1.4946408479778929410951031406215367612625341674214E+00F,
    +1.1400452849267873498385665163302497540705662147867E+00F,
    +7.0298302340869712070423761178082549341008585147316E-01F,
    -6.9062963489750428123465827015636177105952764168514E-01F,
    -1.3878462197923453679424181764163503859142775956277E+00F,
    +1.4808370530967909961602308570940502040390306839968E+00F,
    +6.8009072024718795025297871599800105590278171086316E-01F,
    -7.7298912013658765198333652599637093592440318827244E-01F,
    -1.2490422720355150645143065702707159817165226778060E+00F,
    +1.8294213312468573197121546757210558887415889061396E+00F,
    +6.5477087240790966648594076958746644487569723941202E-01F,
    -8.4565222512064811413534731376286043217836606647925E-01F,
    -1.0774873900867677651460009831450106988494243090890E+00F,
    +2.1771857391440872149589883695801093140005051842472E+00F,
    +6.2735845016609506320877778994794988014868397342019E-01F,
    -9.0657564473347755128773433734929548961279650466521E-01F,
    -8.7324792110139365219289962054912288486781924556739E-01F,
    +2.5140823126487911579992215816235287053510415171839E+00F,
    +5.9825190564088354970947278245211093493524499365015E-01F,
    -9.5374981972507723798966165265409365142277327049593E-01F,
    -6.3733332489924901724280512986201330951862565321876E-01F,
    +2.8287339202238050613920570897674479195003241106216E+00F,
    +5.6791115666056089247094084317726473343014273927607E-01F,
    -9.8526175247153711571456581652851591372209153063126E-01F,
    -3.7182142464167779954480869095070912276602716684250E-01F,
    +3.1086202951282430554798259637046088557149018131113E+00F,
    +5.3685349099689944179609652854704526549764807877505E-01F,
    -9.9936509502758571126506962241959669662001199007340E-01F,
    -7.9966282088071465025630168895592187081013099732338E-02F,
    +3.3403528492630563300610059008839806750731857234695E+00F,
    +5.0564718338669749970771307914932388777564354135510E-01F,
    -9.9455616234728375618849839186953757135587449887694E-01F,
    +2.3371964335592946500178658573979697490293650996694E-01F,
    +3.5100452362580721440616685752611114875670475050230E+00F,
    +4.7490266820753550572786673103769662593228025496215E-01F,
    -9.6965397964788362766426413983787907165790931945978E-01F,
    +5.6341792697123615587699009622636258805721114424809E-01F,
    +3.6037845517315643124347044843700471847765083911043E+00F,
    +4.4526117871675671662665683151127256253927629789523E-01F,
    -9.2388193907975392801311695985289358321684473327505E-01F,
    +9.0200196403649225592375751567475026658128626335203E-01F,
    +3.6081928804678698935489194528456591025459016155777E+00F,
    +4.1738084904912293442223805510539448715733627841542E-01F,
    -8.5694787577209828534410899464724524569810171186308E-01F,
    +1.2410840108245390327462441794159253618867473633042E+00F,
    +3.5110891593145119995177589587426127285354757464284E+00F,
    +3.9192038080416025546554281512137592320001193191527E-01F,
    -7.6911928887282260952092172044023589169360987755060E-01F,
    +1.5711303545799979851108751558786659797745620723547E+00F,
    +3.3022386101636748803490295963780415209106336788946E+00F,
    +3.6952049346649746916029193853941317829998562382036E-01F,
    -6.6128921189471380963007924452897971611597343342196E-01F,
    +1.8816404825140930877346488909908022472564127421364E+00F,
    +2.9741230821622173865977965109899564661260958177234E+00F,
    +3.5078351534711902299250936210218914213494110502866E-01F,
    -5.3502854754080755555475179253160577561330339317026E-01F,
    +2.1614030897035518160805638086783800400919966479973E+00F,
    +2.5227742666728914355928398854392449740368475192584E+00F,
    +3.3625161436054766581142825960385567070455654420917E-01F,
    -3.9261999892894268173447972675095323833584596230822E-01F,
    +2.3988289013971424206687587153087341533980183484279E+00F,
    +1.9485794548501093163900981318090044464028085899434E+00F,
    +3.2638431807750170113342501372082323428233121290446E-01F,
    -2.3706884120962360454203816265467199819588242159120E-01F,
    +2.5823596405585571846540998582530099184658263116303E+00F,
    +1.2570322916933603129028597825049259714667811965532E+00F,
    +3.2153611946220755545878813928382889538169139462942E-01F,
    -7.2085946672089820048736212259840234927916252678270E-02F,
    +2.7009478261096255878043881135083322996331904832942E+00F,
    +4.5937181866577192513251265441293116967768657424369E-01F,
    +3.2193510113384819371955171049026624303711331766918E-01F,
    +9.7961028887160152162922565681901177569224968425596E-02F,
    +2.7445969538710418771749629607986679691145489414703E+00F,
    -4.2694987627233293134506932408312956118556401194982E-01F,
    +3.2766362684978711841120726539789950803301609950217E-01F,
    +2.6813156249066514988321459549290503565357412697166E-01F,
    +2.7049460035024013587694210804198624378476324011676E+00F,
    -1.3780349024457488856962058768114101727294272112019E+00F,
    +3.3864223328824152712624539836915767406699678487317E-01F,
    +4.3303335747583374325968706055773580305177999404721E-01F,
    +2.5758762388214456731636851968074452921556580547872E+00F,
    -2.3636050648074026698472134589616462324657054597461E+00F,
    +3.5461789658548206935495851409583404357130889058640E-01F,
    +5.8698112657011761875834873843935516884928356953102E-01F,
    +2.3541122876319194948701729320767983921995601117510E+00F,
    -3.3474246909211153171951615830608004881110768867017E+00F,
    +3.7515783493490104254843788036853370816692050298303E-01F,
    +7.2419165406324888275389353651642084093786845733032E-01F,
    +2.0397839050526045215235209171536781343839912870642E+00F,
    -4.2881307921289854591523288152266178309550470744828E+00F,
    +3.9964993014286134412039077521569235943956423801987E-01F,
    +8.3901148208334258518647636937751291460973910654135E-01F,
    +1.6369101030519680599535690319225516512065747074693E+00F,
    -5.1405056634988125917757960774506475500157659771134E+00F,
    +4.2731069832691051571019464806259569141765075670036E-01F,
    +9.2617107109597777777012381460239685000856325249054E-01F,
    +1.1537639798205885753502783961112444770817196036165E+00F,
    -5.8572054136275582400764192363995914190128566658490E+00F,
    +4.5720150665718131235460262732788756166155616488501E-01F,
    +9.8105664356649991180812161351474727404526357565896E-01F,
    +6.0307529726398641463051243344261253185304961087274E-01F,
    -6.3909316539371387027946124972837056984205520801921E+00F
};
