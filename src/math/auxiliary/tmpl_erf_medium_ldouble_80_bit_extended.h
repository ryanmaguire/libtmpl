#ifndef TMPL_ERF_MEDIUM_LDOUBLE_80_BIT_EXTENDED_H
#define TMPL_ERF_MEDIUM_LDOUBLE_80_BIT_EXTENDED_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_80_BIT

#include <libtmpl/include/tmpl_ieee754_ldouble.h>

static long double tmpl_erflm_coeffs[160] = {
    +8.5527181044291702615532011392059985315011643310179E-01L,
    +3.8957677365552820120107545174321575896260929249941E-01L,
    -4.0175104783226356775314400998731238801864204345391E-01L,
    +1.4634492083283840088157151854026171312248544547374E-01L,
    +5.8457916140559016863871737248690349394831523228956E-02L,
    -6.8017366657489451969678782918620069761004218552519E-02L,
    +7.7921895601197100846572501503921539766835714128724E-03L,
    +1.3898697387182788145702228232409912913487880920395E-02L,
    -5.2499801255311284211892881778456084436126809740440E-03L,
    -1.4987119000288413462535038200476259619167916852917E-03L,
    +8.7808757515181000832916699972948517932092103582088E-01L,
    +3.4112482093974109369639247321606954703428807984621E-01L,
    -3.7310527290284192809430737995591628719178986663807E-01L,
    +1.5834765451174184392842635462589222362898649059498E-01L,
    +3.7772050740714084292688378176029279731448921874561E-02L,
    -6.4029568552430596699942714401803487010387787618997E-02L,
    +1.3271564159555953507219738675917349440583054679963E-02L,
    +1.1097771237746248156736771003410443614838240071075E-02L,
    -5.8755142746773913874981388149393497163073868334753E-03L,
    -7.2949855558090949553490296784971833957309826272739E-04L,
    +8.9798960920701778884043558499756012946531863389927E-01L,
    +2.9637438049741345913211007486498297621013061611726E-01L,
    -3.4268287745013440827671857375568329540226907070863E-01L,
    +1.6535992453534079058882209860241534942975139467606E-01L,
    +1.8628919445505427487075708016605994406177533747968E-02L,
    -5.8223852604168282267546475481364594702212506661074E-02L,
    +1.7472729079689475147608245296518475400739636127997E-02L,
    +8.0905812252558915219078207896196342957299619575284E-03L,
    -6.0801952496623346858052103308925051660213863949390E-03L,
    -1.0912448552086927785102621467681295378579633773851E-05L,
    +9.1521500387173225030764177380778197879375772644707E-01L,
    +2.5549068578278909188176542083504315930791037725431E-01L,
    -3.1137927329777428567749574890591535144852339934904E-01L,
    +1.6783209762684527682682772248557325040997106652830E-01L,
    +1.5204066085543010334469293566911536739055383453978E-03L,
    -5.1090827509893031872651348120534624313612526828722E-02L,
    +2.0350205035102872399414704297447618475639539890788E-02L,
    +5.0782509773250355702123213929578749035103962367584E-03L,
    -5.9058389960905167050072281245598351757524953980944E-03L,
    +6.1174982429041512669987619563058905034058186557642E-04L,
    +9.3000779678611949130641633198144112173796581855818E-01L,
    +2.1853276425487758174722198656255613126357492202433E-01L,
    -2.7999510420156196189197892214872633475320555644640E-01L,
    +1.6631823008720837228943766877559684539986274878246E-01L,
    -1.3215914748603314739493503912283995627907132520609E-02L,
    -4.3122312717790040388835512627391041903370656312642E-02L,
    +2.1941063573147305724132310541095292182002491450729E-02L,
    +2.2352214217440116757036564656197214741981259623504E-03L,
    -5.4159679603962732322277758015199221822780758459527E-03L,
    +1.1068768525185064392140625737971376946843956381275E-03L,
    +9.4261272724427840712057714688472275383644268541078E-01L,
    +1.8546634817174812772493794723126200216472608017594E-01L,
    -2.4922040535578658583096367099414276431170963122089E-01L,
    +1.6143783040730951398471290026828470780609253835063E-01L,
    -2.5392573852661021566660026913768588783841179348757E-02L,
    -3.4782840676756105489126817834485597063878143463755E-02L,
    +2.2351166159387019941887205492452776239630865032969E-02L,
    -2.9962179361682112952886835345925453439451745003709E-04L,
    -4.6878032191725697711370440861905615589098468333219E-03L,
    +1.4573834406573628766927282548367403431534750443423E-03L,
    +9.5326985102802300853073645381381843517580703668523E-01L,
    +1.5617832355458161997713979115766721034235956885118E-01L,
    -2.1962576749863042167300284457883440670059692595268E-01L,
    +1.5383971584510556291526581044797714546014162607187E-01L,
    -3.4959961037227457198585130186120512038203685776483E-02L,
    -2.6486936670505560806296529428355652463831364807456E-02L,
    +2.1738407404246828145681031977046790624412428119812E-02L,
    -2.4277671892204783246350801573566444591723777198009E-03L,
    -3.8042071303879484280853193045396558660760731849871E-03L,
    +1.6600812656318902461728632835617381145688559665341E-03L,
    +9.6221008419949118040547474226281761150883935699579E-01L,
    +1.3049187367280633149132663020772093661367873027356E-01L,
    -1.9165993945693429935790319392018321904806749544468E-01L,
    +1.4416973282731277760322779456248071485917398866636E-01L,
    -4.1988001059413247541090357334033588078774700383284E-02L,
    -1.8582969226096794885662001357599310047847711707582E-02L,
    +2.0294712300091824604952766933758254770252659813746E-02L,
    -4.0920138446101731552729594203675678002902873136458E-03L,
    -2.8463314363187389428618047686736854567516882576225E-03L,
    +1.7239290981849900205881517972683429175710963603471E-03L,
    +9.6965169513984221822338229925909363983981047745714E-01L,
    +1.0818156296067483235062361206443969329569927930256E-01L,
    -1.6565301828353332151590392294109502746082361546669E-01L,
    +1.3304360184421540344500477632387082388414011138773E-01L,
    -4.6643834900926835246296929340232567363193935635687E-02L,
    -1.1343731676856849530834980063745015775996111780514E-02L,
    +1.8228386048433184429838128695245564498120873234765E-02L,
    -5.2740295452757647084590886067684147342308201639937E-03L,
    -1.8875453153031746364053509583301498891449199740494E-03L,
    +1.6669993266596942404397262207100584396787273700994E-03L,
    +9.7579772059009134815451548049025559026253953119999E-01L,
    +8.8987726356669563882584369776580353340134398817561E-02L,
    -1.4182418888094209021184546464887670000545918148603E-01L,
    +1.2102562523377785696120028789469442647789150810335E-01L,
    -4.9167565481409119676874463291100062345895441540162E-02L,
    -4.9633645761055383959848743028050020170530359645055E-03L,
    +1.5748138865873810896823027548491874012488416503462E-02L,
    -5.9892732745270296166305398999246261137478148099576E-03L,
    -9.8899899672001787417026825369271464129719609449451E-04L,
    +1.5141304278347216662487121592872746030140116836277E-03L,
    +9.8083424596655095168323376218603729849806978885526E-01L,
    +7.2629665503254818793194795735769902421097141792522E-02L,
    -1.2029288348976575872299130608067176285780548344453E-01L,
    +1.0861350368553148205937922297274295754739355710381E-01L,
    -4.9847929909944825178420732461797831053599884684476E-02L,
    +4.4020245936403984224198094447768352395460965430418E-04L,
    +1.3049753688358430870650895678235439176543633184379E-02L,
    -6.2801393215235109917073844739045770691608474730503E-03L,
    -1.9696560403801680105356297846813146891319860244271E-04L,
    +1.2930186072336678137805290596215189079834371673826E-03L,
    +9.8492946350821115327736101488045848054077546342784E-01L,
    +5.8817295576895811896202577084923133422523792230185E-02L,
    -1.0109222677278963799505650631118864007040557277891E-01L,
    +9.6229077984856239768834490493151842693744331079391E-02L,
    -4.8999454969289723648254876813797332924350161850996E-02L,
    +4.8184018956796421352048640948469346874498798064502E-03L,
    +1.0305979481794527340180514052824716692766712414197E-02L,
    -6.2082100908264806124028810105692096198115771411481E-03L,
    +4.5810164903351121455181332857350627480829217725860E-04L,
    +1.0316943264535931248077588351869813980287861823232E-03L,
    +9.8823340391229524410052414579870154002914359248166E-01L,
    +4.7261024719377530990688192284937968424441729617771E-02L,
    -8.4183700281391188010902941637970580776272113078250E-02L,
    +8.4214469177692895468225205069092909984451050469153E-02L,
    -4.6942278184572430971823826196905019042142898664610E-02L,
    +8.1820324530176406623701646178224773353866505630412E-03L,
    +7.6598599981854716238970620746089257637354507462733E-03L,
    -5.8464241904268166249511491381394353761386896074948E-03L,
    +9.6101273306932519631121240757612581917588055077330E-04L,
    +7.5604747365343371757777871203327015876774254056523E-04L,
    +9.9087822750686267783724253349536651590217789220201E-01L,
    +3.7679774086816650472495539973840983986490315245072E-02L,
    -6.9472083472568162665325652510320574386804638790497E-02L,
    +7.2832844572759506739469631625255943724286310723074E-02L,
    -4.3985417433290187905322238099300409114727150606523E-02L,
    +1.0589391985106931179104769652412676982523118233726E-02L,
    +5.2213816857055052540842720724297819097099553156825E-03L,
    -5.2718328433413284248301824630479744894613315347635E-03L,
    +1.3101101264003401715634432677427976400170730338329E-03L,
    +4.8806883390080334015526723846360767316410303889671E-04L,
    +9.9297895874393468508828134870757128469690693898717E-01L,
    +2.9807154664801724901051948503962349003425462777661E-02L,
    -5.6819888579778255910767140954017071819036993541219E-02L,
    +6.2272890181867637016812636815861431362482431500909E-02L,
    -4.0413885594930188807846882010187538421266629506781E-02L,
    +1.2133720711516606968386775381008865900793544610376E-02L,
    +3.0670685460456534482357822792688556191716323891274E-03L,
    -4.5594379784262675667025892836910786851921767669759E-03L,
    +1.5147430781794170069920750277046315635736743846853E-03L,
    +2.4478257401904771307315399610631599854863865145460E-04L,
    +9.9463455163389428654359960715607018801286103390678E-01L,
    +2.3395903761608298681110304834983666957560347331287E-02L,
    -4.6060685530666311582496889955878465863752294200838E-02L,
    +5.2656015171796769406652212531653595092656715677159E-02L,
    -3.6479703091398692470971518208542060893685338977506E-02L,
    +1.2930961632930425932274863577445222758228682403053E-02L,
    +1.2419778741577075667259921641201156506586762961723E-03L,
    -3.7774129289373699457150827282177682123817740420921E-03L,
    +1.5923299611791642438374931766315348602389869137322E-03L,
    +3.7837994276239749306418099010378344315041830076800E-05L
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
#define TMPL_POLY_EVAL(z)\
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*(A08+z*A09))))))))

TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Medium(tmpl_IEEE754_LDouble w)
{
    tmpl_IEEE754_LDouble shift;
    const unsigned int n = 10U * (w.bits.man0 >> 11);
    shift = w;
    shift.bits.man0 = (w.bits.man0 & 0x7800U) | 0x0400U;
    shift.bits.man1 = 0x0000U;
    shift.bits.man2 = 0x0000U;
    shift.bits.man3 = 0x0000U;
    w.r -= shift.r;

    return TMPL_POLY_EVAL(w.r);
}

#else

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define A00 (+1.1283791670955125739314171099502484148921208531728E+00L)
#define A01 (+1.4920278237619000520975885116068698561112023586927E-01L)
#define A02 (+5.0588484962684315204267352164775505017461778659975E-02L)
#define A03 (+2.6489483697996107296745572800020345150179790692195E-03L)
#define A04 (+3.7382085181878354886406664584462812986478153325447E-04L)
#define A05 (+6.9849093394408771121764941438879029490407386521203E-06L)
#define A06 (+5.2271592348959230742733499169922504752755806934622E-07L)
#define A07 (-2.2548217663449974511513795025550328723019126737930E-09L)
#define A08 (+4.4833375185725042453350109956947121349577136152256E-11L)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define B00 (+1.0000000000000000000000000000000000000000000000000E+00L)
#define B01 (+4.6556085642758115526601848367010609878104037398728E-01L)
#define B02 (+1.0001982963431972190942543669112576477130666430471E-01L)
#define B03 (+1.2940950747657570801136517026358823617460758702752E-02L)
#define B04 (+1.0981100562225000377092715573987637968278869464382E-03L)
#define B05 (+6.1757762759998746846404373055996794564606731333935E-05L)
#define B06 (+2.1612799584693033700667928383065551889479216822305E-06L)
#define B07 (+3.7024380616574339157661134936776156061716153770560E-08L)

#define TMPL_NUM_EVAL(z) \
A00+z*(A01+z*(A02+z*(A03+z*(A04+z*(A05+z*(A06+z*(A07+z*A08)))))))

#define TMPL_DEN_EVAL(z) \
B00+z*(B01+z*(B02+z*(B03+z*(B04+z*(B05+z*(B06+z*B07))))))


TMPL_STATIC_INLINE
long double tmpl_LDouble_Erf_Medium(long double x)
{
    const long double x2 = x*x;
    const long double p = TMPL_NUM_EVAL(x2);
    const long double q = TMPL_DEN_EVAL(x2);
    return x * p / q;
}


#endif

#include "tmpl_math_undef.h"

#endif
/*  End of include guard.                                                     */