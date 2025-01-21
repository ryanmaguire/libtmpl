#ifndef TMPL_ERF_MEDIUM_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H
#define TMPL_ERF_MEDIUM_LDOUBLE_128_BIT_DOUBLE_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE

#include <libtmpl/include/types/tmpl_ieee754_ldouble.h>

static long double tmpl_erflm_coeffs[256] = {
    +8.5527181044291702615316701466484360128231331740379E-01L,
    +3.8957677365552820120155200462678648266884580998328E-01L,
    -4.0175104783226345748910050477670982627024544833073E-01L,
    +1.4634492083283839328990592883830758144432992556932E-01L,
    +5.8457916139655522622925871800993891358757567455213E-02L,
    -6.8017366657459421068928872779467620788910995187544E-02L,
    +7.7921921512602032920571162490140601262816850420847E-03L,
    +1.3898697350065457023631638728244693903438509323069E-02L,
    -5.2530133715480761326578229494499599539786580825218E-03L,
    -1.4987089204218523648205751371308243597846323428832E-03L,
    +1.2429777586595107392781398606527777978628969370824E-03L,
    +1.2184948144216078445118916504200916004160651153310E-05L,
    -1.9042424139163314733330947582906920509794523058548E-04L,
    +2.8493142390006602793898312235880192609964239343097E-05L,
    +2.0906933727580070816694030550366199706078160363251E-05L,
    -6.3992804537079537901968071870366981080238483553770E-06L,
    +8.7808757515181000832708034713440644526318398611359E-01L,
    +3.4112482093974109369914126781663325107722385407936E-01L,
    -3.7310527290284182123343576167655623572841950769980E-01L,
    +1.5834765451174179674966648696530156072308148143790E-01L,
    +3.7772050739838478647004772626484872075705050836526E-02L,
    -6.4029568552201873432964729394993629158853432782073E-02L,
    +1.3271566670700005382861308072541173897479536568340E-02L,
    +1.1097770784978122945902438956220400942793578963553E-02L,
    -5.8784538427388837192416072520316163055014764308547E-03L,
    -7.2910901030227106652437776201970520425193555259403E-04L,
    +1.2045510569317044556014982085309298353561091006728E-03L,
    -1.2023265622022598177332846850246292726333278370833E-04L,
    -1.6059032064529881718706982246584297920431978090270E-04L,
    +4.3978290452320438270668368652051464837293618367929E-05L,
    +1.4302639826648153366965665863219788071539449504838E-05L,
    -7.5270677556329423272712876722143120428508256718071E-06L,
    +8.9798960920701778883855807912279408434012235504308E-01L,
    +2.9637438049741345913662719687921680444175908913411E-01L,
    -3.4268287745013431212672519639065542529945039991200E-01L,
    +1.6535992453534071255214160660633066128787747178722E-01L,
    +1.8628919444717587931368178941415808861033610128864E-02L,
    -5.8223852603784098183900459121267075050558621929787E-02L,
    +1.7472731339117097726845695637816165638290604272148E-02L,
    +8.0905804454188393077905605462954387583966911770209E-03L,
    -6.0828401255289762737856987620619636720092592849160E-03L,
    -1.0216443244138194091134173102053740944131535687203E-05L,
    +1.0837563525957033200144371707872028042381547839182E-03L,
    -2.2616336067875209196045703975408266508298239862231E-04L,
    -1.2062194543431007482430513799475566884955071076469E-04L,
    +5.3351614536818095756986509734805191219094723777761E-05L,
    +7.0947582395486436284022332180387263845229652738310E-06L,
    -7.6954918203778883900215179784014116617379816964978E-06L,
    +9.1521500387173225030608080521594344276481492494072E-01L,
    +2.5549068578278909188745915445878683564901261315511E-01L,
    -3.1137927329777420573784084449317041364815701383568E-01L,
    +1.6783209762684517819950930134440496652015224422353E-01L,
    +1.5204066078992881139542262311815226820051923550586E-03L,
    -5.1090827509404456415405648778490629557983677568777E-02L,
    +2.0350206913589083588983270726142462506058947525058E-02L,
    +5.0782499757810527787652191515777869292706404542674E-03L,
    -5.9080379138363098948773808895511457282159630432246E-03L,
    +6.1265610637323709730762023420491370685304479609324E-04L,
    +9.0098292542558512311112931805468877874990230743126E-04L,
    -2.9990244292111451657380201236486450937180126541705E-04L,
    -7.5594887256995831282701417959533450195249333256603E-05L,
    +5.6467969538822538873085017757740630538312377560203E-05L,
    +1.4118693732904145590767576220755556393679378757361E-07L,
    -7.0108456235318744430978858837371411788843515555660E-06L,
    +9.3000779678611949130523944842851263056865628776576E-01L,
    +2.1853276425487758175347960379873749275629403353690E-01L,
    -2.7999510420156190162164574236187679357502524305528E-01L,
    +1.6631823008720826371732920367831513830566775816159E-01L,
    -1.3215914749097160070032220017231646184375596826537E-02L,
    -4.3122312717250184579307384522039807850976858807054E-02L,
    +2.1941064989418175683680526599784361104997619869950E-02L,
    +2.2352203085761284450082829055097423453510957126108E-03L,
    -5.4176257885375468006925281611670139329897668901280E-03L,
    +1.1078922825688017632875232234038392157144454313466E-03L,
    +6.7923607611767110942317319458097344243124476728590E-04L,
    -3.3952259578402084622822205845703366641385177802924E-04L,
    -3.0412345865506191935392329722570139460757348027175E-05L,
    +5.3876128113909144481066484476205530859511501530816E-05L,
    -5.8446268571836896377004268869797939733867755980874E-06L,
    -5.6692151146740400540657846862776157397097373407532E-06L,
    +9.4261272724427840711981186517156664033579988913813E-01L,
    +1.8546634817174812773118535773304527800926136587749E-01L,
    -2.4922040535578654663878032444760763872318182526507E-01L,
    +1.6143783040730940545351225474689407709735980637362E-01L,
    -2.5392573852982157909485237413732836758177461956837E-02L,
    -3.4782840676214911759705451586345111324320645683892E-02L,
    +2.2351167080349838002651656939007913803575806412806E-02L,
    -2.9962291448790524221891077091391857872841004647334E-04L,
    -4.6888812300963318516277467524206663183805812625796E-03L,
    +1.4584120451375234051128277803229552666261802672328E-03L,
    +4.4163064822930922143530078401849959502561242919184E-04L,
    -3.4654764075722126197313808040599044105276912381750E-04L,
    +1.0698485894039986988353769414968389130613111680095E-05L,
    +4.6660393678140380529240590545487181669375407243852E-05L,
    -1.0360626482494201658617606369117529456048037163831E-05L,
    -3.9188717569432811540069188867579467361236554692179E-06L,
    +9.5326985102802300853037385214901908542582657305405E-01L,
    +1.5617832355458161998288927754405747147583592382605E-01L,
    -2.1962576749863040310093804654008605927238948340140E-01L,
    +1.5383971584510546291283299278652400855454478539734E-01L,
    -3.4959961037379644243606483510076756477733837200369E-02L,
    -2.6486936670005588986821292801600721151524842165171E-02L,
    +2.1738407840699691636967894787936442827671297538933E-02L,
    -2.4277682288512239641687319447572299489007313436033E-03L,
    -3.8047179836230013529785945442633374708021197058909E-03L,
    +1.6610404143810362174907546884990209517388315903714E-03L,
    +2.0922669166465059814861928748537402133472131764410E-04L,
    -3.2530207419783083421604708779481279513088858645975E-04L,
    +4.4541648044781883094155091320930270052108339777364E-05L,
    +3.6239517684952775856268538295796801199099989837182E-05L,
    -1.3146506197589747409798628206796623004654662253009E-05L,
    -2.0208969865978960570187940738727481854256251720637E-06L,
    +9.6221008419949118040547512512493828893935006413178E-01L,
    +1.3049187367280633149390742186536160560257308355121E-01L,
    -1.9165993945693429938167652585915154008859953407073E-01L,
    +1.4416973282731272431325579094839303119521550534639E-01L,
    -4.1988001059413015456988499925534371590166800076420E-02L,
    -1.8582969225788670712995990594373455836971291329781E-02L,
    +2.0294712299302507492754331422290059771781925197636E-02L,
    -4.0920145718409520816773665216155546719154085655860E-03L,
    -2.8463303206812631247684005723063750138698910196792E-03L,
    +1.7246800908580974267120439935342106281691931625481E-03L,
    -6.1049744867049377025713748100259030471864666013350E-07L,
    -2.8205734793538548844670680595866130755099136578823E-04L,
    +6.9137777415251088974855863342585197327563423775581E-05L,
    +2.4154839705557584688937974584558240097523123129732E-05L,
    -1.4178658324309352527812119669964804630760294215857E-05L,
    -2.1388499883035337481113669280564448853368158611721E-07L,
    +9.6965169513984221822368542398904338371111324100820E-01L,
    +1.0818156296067483235440774425183865616504066979509E-01L,
    -1.6565301828353333704268685838119959443667272600353E-01L,
    +1.3304360184421533744627358651044417707820469272038E-01L,
    -4.6643834900799588718074357117106266857051706301474E-02L,
    -1.1343731676524853144061492191583314335703820442896E-02L,
    +1.8228385683439450784548173444915000534462607432997E-02L,
    -5.2740302420940803984589876572087660937625985229402E-03L,
    -1.8871179443996738692553795492079446660512465651064E-03L,
    +1.6676501809320720493234071591015591835672315861889E-03L,
    -1.7523023334364610234274555031710762729695859233455E-04L,
    -2.2410252146152874325743076363457853337836743944506E-04L,
    +8.3742858051500171827928163426032454197222568945814E-05L,
    +1.1876318185643242583601818006731921156552538813111E-05L,
    -1.3635726923876486112767507998565295469105878257068E-05L,
    +1.3128893590566074725637092107718347954084638645769E-06L,
    +9.7579772059009134815504717008285046985358178475596E-01L,
    +8.8987726356669563885166797397042256307236295419744E-02L,
    -1.4182418888094211744198458334857199609941451044814E-01L,
    +1.2102562523377781182038635400373497079644670343924E-01L,
    -4.9167565481185987980375578478486865165793257059317E-02L,
    -4.9633645758772762086264085285161518042729036726321E-03L,
    +1.5748138225917733114455222156880125547301907015244E-02L,
    -5.9892737574262829462875264984815216023134589753688E-03L,
    -9.8824978568641030018268717340734311764619363052066E-04L,
    +1.5145861408190487760660135256975038157816607148159E-03L,
    -3.0708548159278558249345223812295409189646051584570E-04L,
    -1.5885637099284168521337899055973126134165765193791E-04L,
    +8.8724321259908100916213492769964130886206835334924E-05L,
    +6.4830269265230678490678723555025524951339407308566E-07L,
    -1.1844013113616715976042578292623589997751580080277E-05L,
    +2.4353839417814894588563639119094292679969230737021E-06L,
    +9.8083424596655095168391534242022071412969224391826E-01L,
    +7.2629665503254818794590526771407052970176723887915E-02L,
    -1.2029288348976579362854055996371088518731954883369E-01L,
    +1.0861350368553145753331669269656220389604875615190E-01L,
    -4.9847929909658807060264396950700425909744182154342E-02L,
    +4.4020245948952241743023621110478029020492157801779E-04L,
    +1.3049752868065841381699906570912159956155288893493E-02L,
    -6.2801395916119957537055441476110208105911249300765E-03L,
    -1.9600531493369646245111033776009730180159442178810E-04L,
    +1.2932790990043195122536852496717355863218758523530E-03L,
    -3.9355331222141657437373865720691001132629340832266E-04L,
    -9.3114275591269232984975596722796008908869365364327E-05L,
    +8.5332706870370564447803538125274751758517559452956E-05L,
    -8.6119269463455396667517531566538952399714253037874E-06L,
    -9.2133291366529963558774161492983724866582740437179E-06L,
    +3.0993359432366269805683589964687231876129670033384E-06L,
    +9.8492946350821115327811673793639701440980054833390E-01L,
    +5.8817295576895811896524455587245537878584444564549E-02L,
    -1.0109222677278967669715140804055611206989118782256E-01L,
    +9.6229077984856233916644503178552757176736298916394E-02L,
    -4.8999454968972600456399234401952117423408706903732E-02L,
    +4.8184018957117926387811969169430354845750174209790E-03L,
    +1.0305978572307812255742277454624614416200429649543E-02L,
    -6.2082101669277750995583076478962888812585905661167E-03L,
    +4.5916632632153286228255859686243044469640982154769E-04L,
    +1.0317759494881500390487790174192933352249779765042E-03L,
    -4.3630255176034057985044090328365086614039623364372E-04L,
    -3.2491517039279722806532492064842502358688054206333E-05L,
    +7.5413913006642324010619730728043386941060489989662E-05L,
    -1.5359039073341108729420496259046985627005588739708E-05L,
    -6.1734681586332845321134850438791065548001939973203E-06L,
    +3.3147656628919764765898105239135274336339046325338E-06L,
    +9.8823340391229524410128696534097909503952081921329E-01L,
    +4.7261024719377530990117451863465848518508260418967E-02L,
    -8.4183700281391227076146711132908478305155929948826E-02L,
    +8.4214469177692905156218402176467289226283347559823E-02L,
    -4.6942278184252334629374753522004429968618095163645E-02L,
    +8.1820324529719168765640697750428996615552386477137E-03L,
    +7.6598590801818802555110927241720472961610696203549E-03L,
    -5.8464241040144490296824723593822342301742693208953E-03L,
    +9.6208735949424649430887346180682682501877733348083E-04L,
    +7.5597844042522731661016016694626354439855035452794E-04L,
    -4.4035507220218378221103935275669133529981351054359E-04L,
    +1.8909431993251440505926913723231022569163920454104E-05L,
    +6.1106729943268326513522354401520112760333750969404E-05L,
    -1.9412306291253903689486614078079178145376743264210E-05L,
    -3.1196032592255230836197870420683574336458379894575E-06L,
    +3.1428192915135476240158711368497953574475417818211E-06L,
    +9.9087822750686267783795801931551990999248752620244E-01L,
    +3.7679774086816650471252038580866654313801732058568E-02L,
    -6.9472083472568199306370946135370106533372606125190E-02L,
    +7.2832844572759528156996941759386425892043568028843E-02L,
    -4.3985417432989956917607866169546219613232754472142E-02L,
    +1.0589391985002234779636784443779543398242532687765E-02L,
    +5.2213808246813650527093542116616028769447915281208E-03L,
    -5.2718326332404178477109254524847899445522087804645E-03L,
    +1.3111180348096782211273950153420721753255165980896E-03L,
    +4.8788437275667264960392970774153047796558199872328E-04L,
    -4.1299501308979336431240331059253382218065299165074E-04L,
    +5.8611567252921050796052346246641905611738915319585E-05L,
    +4.4564159352955134328213459637450477012696396440204E-05L,
    -2.0906526731863906656732493285686885774578080853235E-05L,
    -3.7220422007564661513319317712076357702898653651537E-07L,
    +2.6786430692939191539875404238416866058647515138100E-06L,
    +9.9297895874393468508890969983425317392012533393441E-01L,
    +2.9807154664801724899367121533431783641337513976142E-02L,
    -5.6819888579778288089418575425417476004082359230274E-02L,
    +6.2272890181867666147180399088244709370570955525536E-02L,
    -4.0413885594666523266725076324537961319648818229863E-02L,
    +1.2133720711372924146723799669108960936561672544838E-02L,
    +3.0670677898928606524883527947638183631075146491887E-03L,
    -4.5594376858935340215477600284088874946211407883480E-03L,
    +1.5156282100637402357643165505205485955641674486494E-03L,
    +2.4452037771618701245927834761568230393740540851874E-04L,
    -3.6266840913032180247546691673662708195307775961405E-04L,
    +8.5685148172904345467556198788575442380801056577991E-05L,
    +2.7726877678083915344509084808552327771092995628824E-05L,
    -2.0215241301619905198622420792102847433046980246660E-05L,
    +1.8460189007985427914490177049485847097565646672516E-06L,
    +2.0326745991263034009660279089804400684590181782740E-06L,
    +9.9463455163389428654411594357457228124178534816849E-01L,
    +2.3395903761608298679203921397751457027101625502914E-02L,
    -4.6060685530666338024682720254209818040957179712199E-02L,
    +5.2656015171796802430994763198731384327924740519265E-02L,
    -3.6479703091182031384782845277159806974078863633337E-02L,
    +1.2930961632766808986218092036558605572795208970906E-02L,
    +1.2419772528119899716492675826667334493782470747164E-03L,
    -3.7774125934607464988081796751817206427913008323459E-03L,
    +1.5930572780985364368464263105383640705500397144834E-03L,
    +3.7534334004813811439018081979478207597096130614426E-05L,
    -2.9798932679116518374838808951046857311407604615657E-04L,
    +1.0052465209273127599231484871430337525148377525137E-04L,
    +1.2165251004847624368822850018791966282234896361569E-05L,
    -1.7861219771897108500318263664930477251035607847757E-05L,
    +3.4164394073813211451888130631251407573937692570915E-06L,
    +1.3139541079273725711474095699695515470260206724275E-06L
};

#define A00 (tmpl_erflm_coeffs[n])
#define A01 (tmpl_erflm_coeffs[n+1])
#define A02 (tmpl_erflm_coeffs[n+2])
#define A03 (tmpl_erflm_coeffs[n+3])
#define A04 (tmpl_erflm_coeffs[n+4])
#define A05 (tmpl_erflm_coeffs[n+5])
#define A06 (tmpl_erflm_coeffs[n+6])
#define A07 (tmpl_erflm_coeffs[n+7])
#define A08 (tmpl_erflm_coeffs[n+8])
#define A09 (tmpl_erflm_coeffs[n+9])
#define A10 (tmpl_erflm_coeffs[n+10])
#define A11 (tmpl_erflm_coeffs[n+11])
#define A12 (tmpl_erflm_coeffs[n+12])
#define A13 (tmpl_erflm_coeffs[n+13])
#define A14 (tmpl_erflm_coeffs[n+14])
#define A15 (tmpl_erflm_coeffs[n+15])

#define TMPL_POLY_EVAL(z) \
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
                                                        A14 + z*A15\
                                                    )\
                                                )\
                                            )\
                                        )\
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

static long double tmpl_erflm_shift[16] = {
    1.03125L,
    1.09375L,
    1.15625L,
    1.21875L,
    1.28125L,
    1.34375L,
    1.40625L,
    1.46875L,
    1.53125L,
    1.59375L,
    1.65625L,
    1.71875L,
    1.78125L,
    1.84375L,
    1.90625L,
    1.96875L
};

TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Medium(tmpl_IEEE754_LDouble w)
{
    const unsigned int ind = w.bits.man0;
    const unsigned int n = ind << 4;
    w.r -= tmpl_erflm_shift[ind];

    return TMPL_POLY_EVAL(w.r);
}

#include "tmpl_math_undef.h"

#endif
/*  End of #if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE.                */

#endif
