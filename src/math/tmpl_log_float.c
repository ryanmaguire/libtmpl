/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 *                              tmpl_log_float                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at single precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Float_Log                                                        *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (float):                                                            *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (float):                                                        *
 *          The natural log of x at single precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. logf from math.h otherwise.                           *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, and if libtmpl algorithms have      *
 *      been requested, log(x) is computed as follows:                        *
 *                                                                            *
 *          Check if x < 0, return Not-A-Number if so.                        *
 *                                                                            *
 *          Check if x = 0.0, return -infinity if so.                         *
 *                                                                            *
 *          Check if x is a subnormal (all exponent bits set to zero) number, *
 *          normalize by 2^23 if so, and then pass to the main part of the    *
 *          algorithm.                                                        *
 *                                                                            *
 *          For values not in the range 0.99 < x < 1.0, compute log(x) as     *
 *          follows:                                                          *
 *                                                                            *
 *              log(x) = log(1.m * 2^b)                                       *
 *                     = log(1.m) + log(2^b)                                  *
 *                     = log(1.m) + b*log(2)                                  *
 *                     = log(u) + b*log(2)      with u = 1.m                  *
 *                     = log(ut/t) + b*log(2)   with t = 1 + k/128 for some k.*
 *                     = log(u/t) + log(t) + b*log(2)                         *
 *                                                                            *
 *          Precompute log(t) in a table. Precompute 1/t in a table so that   *
 *          u/t can be computed as u * (1/t). Also precompute log(2). The     *
 *          value k is chosen to be the largest value such that               *
 *          t = 1 + k/128 <= u. This value k can be obtained directly from    *
 *          the mantissa. By looking at the most significant 7 bits of the    *
 *          mantissa, the value k is simply these 7 bits read in binary.      *
 *                                                                            *
 *          The value s = u/t is such that 1 <= s < 1 + 1/128. Compute log(s) *
 *          via the following sum:                                            *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(s) =  \      2     2n+1                                   *
 *                        /    ------ A             A = (s - 1) / (s + 1)     *
 *                        ---- 2n + 1                                         *
 *                        n = 0                                               *
 *                                                                            *
 *          For single precision, only the first term is needed. The          *
 *          standard Taylor series for ln(1 + x) with x small has             *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values slightly less than 1, the computation of (s-1) / (s+1) *
 *          leads to large relative error (about ~10^-3) since log(1) = 0     *
 *          (the absolute error is still around 10^-8). We can achieve much   *
 *          better relative error using the standard Taylor series to 4       *
 *          terms. This is slower than the series above, but more accurate in *
 *          this range. That is, for 0.99 < x < 1.0 we use:                   *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(x) =  \    -1   n                                         *
 *                        /    --- s             s = 1 - x                    *
 *                        ----  n                                             *
 *                        n = 1                                               *
 *                                                                            *
 *      If the user has not requested libtmpl algorithms, or if IEEE-754      *
 *      support is not available (highly unlikely), then #include <math.h>    *
 *      is called and tmpl_Float_Log returns logf(x) from math.h              *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of floats with 0.0F). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *      A time and accuracy test against glibc yields the following:          *
 *                                                                            *
 *          start:   9.9999997473787516e-05                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 5220285568                                               *
 *          libtmpl: 17.070764 seconds                                        *
 *          glibc:   15.557277 seconds                                        *
 *          max abs error: 9.5367431640625000e-07                             *
 *          max rel error: 8.5725469034514390e-06                             *
 *          rms abs error: 1.5724722349494647e-08                             *
 *          rms rel error: 2.3073108488104276e-09                             *
 *                                                                            *
 *      Not quite as fast, but the rms error is less the FLT_EPSILON. You     *
 *      win some, you lose some. The function handles denormal values well.   *
 *                                                                            *
 *          start:   1.4012984643248171e-45                                   *
 *          end:     1.1663469547068680e-38                                   *
 *          samples: 10000000                                                 *
 *          libtmpl: 0.051760 seconds                                         *
 *          glibc:   0.062876 seconds                                         *
 *          max abs error: 1.5258789062500000e-05                             *
 *          max rel error: 1.6292271709517081e-07                             *
 *          rms abs error: 4.1573249165892662e-06                             *
 *          rms rel error: 4.7154503634772946e-08                             *
 *                                                                            *
 *      For larger values, we have:                                           *
 *                                                                            *
 *          start:   1.0000000000000000e+02                                   *
 *          end:     1.0000000000000000e+08                                   *
 *          samples: 5220285568                                               *
 *          libtmpl: 17.439378 seconds                                        *
 *          glibc:   15.840557 seconds                                        *
 *          max abs error: 1.9073486328125000e-06                             *
 *          max rel error: 2.1024642649081215e-07                             *
 *          rms abs error: 3.8128065862738070e-08                             *
 *          rms rel error: 3.2184329775011985e-09                             *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MAX:  4672.0698 MHz                                               *
 *          MIN:  2200.0000 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems.                 *
 *      All tests were ran using the following options:                       *
 *                                                                            *
 *          gcc -O3 -flto tmpl_log_float_huge_time_test.c -o test -lm -ltmpl  *
 *                                                                            *
 *      -O3 is optimization level, and -flto is link-time optimization.       *
 *      tmpl_log_float_huge_time_test.c can be found in                       *
 *          libtmpl/tests/math_tests/time_tests/                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Float typedef and the         *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_FLOAT == 0 or if                *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_Float_Log is identical to the standard library logf function.*
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 4, 2022                                              *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if defined(TMPL_HAS_IEEE754_FLOAT) && TMPL_HAS_IEEE754_FLOAT == 1 && \
    defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Table of the values log(1 + k/128) for k = 0, 1, ..., 126, 127.           */
static float tmpl_float_log_table[128] = {
    0.0F,
    0.00778214044205494894746290006113676368F,
    0.0155041865359652541508540460424468359F,
    0.0231670592815343782287991609622899166F,
    0.0307716586667536883710282075967721641F,
    0.0383188643021365991937553251237972903F,
    0.0458095360312942031666792676146633421F,
    0.0532445145188122828658701937865287769F,
    0.0606246218164348425806061320404202633F,
    0.0679506619085077493945652777726294140F,
    0.0752234212375875256986053399836624146F,
    0.0824436692110745912681600686683078059F,
    0.0896121586896871326199514693784845288F,
    0.0967296264585511122955710564874634370F,
    0.103796793681643564826061803763974688F,
    0.110814366340290114194806169323211928F,
    0.117783035656383454538794109470521705F,
    0.124703478500957235863406515380863268F,
    0.131576357788719272588716128689483162F,
    0.138402322859119135685325873601649187F,
    0.145182009844497897281935063740564324F,
    0.151916042025841975071803424896884511F,
    0.158605030176638584093371174625841575F,
    0.165249572895307162875611449277240314F,
    0.171850256926659222340098946055147265F,
    0.178407657472818297119400241510941968F,
    0.184922338494011992663903592659249621F,
    0.191394852999629454609298807561308873F,
    0.197825743329919880362572071196961469F,
    0.204215541428690891503820386196239272F,
    0.210564769107349637669552812732351514F,
    0.216873938300614359619089525744347498F,
    0.223143551314209755766295090309834503F,
    0.229374101064845829991480725046139872F,
    0.235566071312766909077588218941043410F,
    0.241719936887145168144307515913513900F,
    0.247836163904581256780602765746524748F,
    0.253915209980963444137323297906606667F,
    0.259957524436926066972079494542311045F,
    0.265963548497137941339125926537543389F,
    0.271933715483641758831669494532999162F,
    0.277868451003456306186350032923401233F,
    0.283768173130644598346901222350254767F,
    0.289633292583042676878893055525668970F,
    0.295464212893835876386681906054964195F,
    0.301261330578161781012875538233755493F,
    0.307025035294911862075124540535377902F,
    0.312755710003896888386246559688319032F,
    0.318453731118534615810247213590599596F,
    0.324119468654211976090670760434987352F,
    0.329753286372467981814422811920789811F,
    0.335355541921137830257179579814166199F,
    0.340926586970593210305089199780356208F,
    0.346466767346208580918462188425772951F,
    0.351976423157178184655447456259438926F,
    0.357455888921803774226009490140904474F,
    0.362905493689368453137824345977489846F,
    0.368325561158707653048230154050398827F,
    0.373716409793584080821016832715823507F,
    0.379078352934969458390853345631019859F,
    0.384411698910332039734790062481290869F,
    0.389716751140025213370463604003520867F,
    0.394993808240868978106394036364981768F,
    0.400243164127012706929325101995131170F,
    0.405465108108164381978013115464349137F,
    0.410659924985268385934306203175822788F,
    0.415827895143710965613328892954902305F,
    0.420969294644129636128867161506795972F,
    0.426084395310900063124544879595476619F,
    0.431173464818371340859172478955594998F,
    0.436236766774918070349041323061121301F,
    0.441274560804875229489496441661301225F,
    0.446287102628419511532590180619669007F,
    0.451274644139458585144692383079012479F,
    0.456237433481587594380805538163929748F,
    0.461175715122170166367999925597855359F,
    0.466089729924599224558619247504769400F,
    0.470979715218791012546897856056359251F,
    0.475845904869963914265209586304381412F,
    0.480688529345751907676618455448011551F,
    0.485507815781700807801791077190788901F,
    0.490303988045193838150346159645746861F,
    0.495077266797851514597964584842833665F,
    0.499827869556449329821331415247044142F,
    0.504556010752395287058308531738174930F,
    0.509261901789807946804074919228323825F,
    0.513945751102234316801006088274217593F,
    0.518607764208045632152976996364798699F,
    0.523248143764547836516807224934870842F,
    0.527867089620842385113892217778300964F,
    0.532464798869471843873923723460142243F,
    0.537041465896883654566729244153832299F,
    0.541597282432744371576542303900434099F,
    0.546132437598135650382397209231209164F,
    0.550647117952662279259948179204913460F,
    0.555141507540501592715480359515904050F,
    0.559615787935422686270888500526826593F,
    0.564070138284802966071384290090190712F,
    0.568504735352668712078738764866962264F,
    0.572919753561785509092756726626261069F,
    0.577315365034823604318112061519496402F,
    0.581691739634622482520610753725372341F,
    0.586049045003578208904119436287324350F,
    0.590387446602176374641916708123598758F,
    0.594707107746692789514343546529205333F,
    0.599008189646083399381600024461651502F,
    0.603290851438084262340585186661310606F,
    0.607555250224541795501085152791125372F,
    0.611801541105992903529889766428814784F,
    0.616029877215514019647565928196700650F,
    0.620240409751857528851494632567246857F,
    0.624433288011893501042538744054673120F,
    0.628608659422374137744308205774183640F,
    0.632766669571037829545786468503579758F,
    0.636907462237069231620494427181199191F,
    0.641031179420931291055601334405392547F,
    0.645137961373584701665228496134731906F,
    0.649227946625109818890839969905311122F,
    0.653301272012745638758615881210873885F,
    0.657358072708360030141890023245936166F,
    0.661398482245365008260235838709650938F,
    0.665422632545090448950092610006660181F,
    0.669430653942629267298885270929503510F,
    0.673422675212166720297960388801017265F,
    0.677398823591806140809682609997348299F,
    0.681359224807903068948071559568089442F,
    0.685304003098919416544048078967232986F,
    0.689233281238808980324914337814603903F
};

/*  Table of the values 1 / (1 + k/128) for k = 0, 1, ..., 126, 127.          */
static float tmpl_float_log_rcpr_table[128] = {
    1.0F,
    0.992248062015503875968992248062015504F,
    0.984615384615384615384615384615384615F,
    0.977099236641221374045801526717557252F,
    0.969696969696969696969696969696969697F,
    0.962406015037593984962406015037593985F,
    0.955223880597014925373134328358208955F,
    0.948148148148148148148148148148148148F,
    0.941176470588235294117647058823529412F,
    0.934306569343065693430656934306569343F,
    0.927536231884057971014492753623188406F,
    0.920863309352517985611510791366906475F,
    0.914285714285714285714285714285714286F,
    0.907801418439716312056737588652482270F,
    0.901408450704225352112676056338028169F,
    0.895104895104895104895104895104895105F,
    0.888888888888888888888888888888888889F,
    0.882758620689655172413793103448275862F,
    0.876712328767123287671232876712328767F,
    0.870748299319727891156462585034013605F,
    0.864864864864864864864864864864864865F,
    0.859060402684563758389261744966442953F,
    0.853333333333333333333333333333333333F,
    0.847682119205298013245033112582781457F,
    0.842105263157894736842105263157894737F,
    0.836601307189542483660130718954248366F,
    0.831168831168831168831168831168831169F,
    0.825806451612903225806451612903225806F,
    0.820512820512820512820512820512820513F,
    0.815286624203821656050955414012738854F,
    0.810126582278481012658227848101265823F,
    0.805031446540880503144654088050314465F,
    0.800000000000000000000000000000000000F,
    0.795031055900621118012422360248447205F,
    0.790123456790123456790123456790123457F,
    0.785276073619631901840490797546012270F,
    0.780487804878048780487804878048780488F,
    0.775757575757575757575757575757575758F,
    0.771084337349397590361445783132530120F,
    0.766467065868263473053892215568862275F,
    0.761904761904761904761904761904761905F,
    0.757396449704142011834319526627218935F,
    0.752941176470588235294117647058823529F,
    0.748538011695906432748538011695906433F,
    0.744186046511627906976744186046511628F,
    0.739884393063583815028901734104046243F,
    0.735632183908045977011494252873563218F,
    0.731428571428571428571428571428571429F,
    0.727272727272727272727272727272727273F,
    0.723163841807909604519774011299435028F,
    0.719101123595505617977528089887640449F,
    0.715083798882681564245810055865921788F,
    0.711111111111111111111111111111111111F,
    0.707182320441988950276243093922651934F,
    0.703296703296703296703296703296703297F,
    0.699453551912568306010928961748633880F,
    0.695652173913043478260869565217391304F,
    0.691891891891891891891891891891891892F,
    0.688172043010752688172043010752688172F,
    0.684491978609625668449197860962566845F,
    0.680851063829787234042553191489361702F,
    0.677248677248677248677248677248677249F,
    0.673684210526315789473684210526315789F,
    0.670157068062827225130890052356020942F,
    0.666666666666666666666666666666666667F,
    0.663212435233160621761658031088082902F,
    0.659793814432989690721649484536082474F,
    0.656410256410256410256410256410256410F,
    0.653061224489795918367346938775510204F,
    0.649746192893401015228426395939086294F,
    0.646464646464646464646464646464646465F,
    0.643216080402010050251256281407035176F,
    0.640000000000000000000000000000000000F,
    0.636815920398009950248756218905472637F,
    0.633663366336633663366336633663366337F,
    0.630541871921182266009852216748768473F,
    0.627450980392156862745098039215686275F,
    0.624390243902439024390243902439024390F,
    0.621359223300970873786407766990291262F,
    0.618357487922705314009661835748792271F,
    0.615384615384615384615384615384615385F,
    0.612440191387559808612440191387559809F,
    0.609523809523809523809523809523809524F,
    0.606635071090047393364928909952606635F,
    0.603773584905660377358490566037735849F,
    0.600938967136150234741784037558685446F,
    0.598130841121495327102803738317757009F,
    0.595348837209302325581395348837209302F,
    0.592592592592592592592592592592592593F,
    0.589861751152073732718894009216589862F,
    0.587155963302752293577981651376146789F,
    0.584474885844748858447488584474885845F,
    0.581818181818181818181818181818181818F,
    0.579185520361990950226244343891402715F,
    0.576576576576576576576576576576576577F,
    0.573991031390134529147982062780269058F,
    0.571428571428571428571428571428571429F,
    0.568888888888888888888888888888888889F,
    0.566371681415929203539823008849557522F,
    0.563876651982378854625550660792951542F,
    0.561403508771929824561403508771929825F,
    0.558951965065502183406113537117903930F,
    0.556521739130434782608695652173913043F,
    0.554112554112554112554112554112554113F,
    0.551724137931034482758620689655172414F,
    0.549356223175965665236051502145922747F,
    0.547008547008547008547008547008547009F,
    0.544680851063829787234042553191489362F,
    0.542372881355932203389830508474576271F,
    0.540084388185654008438818565400843882F,
    0.537815126050420168067226890756302521F,
    0.535564853556485355648535564853556485F,
    0.533333333333333333333333333333333333F,
    0.531120331950207468879668049792531120F,
    0.528925619834710743801652892561983471F,
    0.526748971193415637860082304526748971F,
    0.524590163934426229508196721311475410F,
    0.522448979591836734693877551020408163F,
    0.520325203252032520325203252032520325F,
    0.518218623481781376518218623481781377F,
    0.516129032258064516129032258064516129F,
    0.514056224899598393574297188755020080F,
    0.512000000000000000000000000000000000F,
    0.509960159362549800796812749003984064F,
    0.507936507936507936507936507936507937F,
    0.505928853754940711462450592885375494F,
    0.503937007874015748031496062992125984F,
    0.501960784313725490196078431372549020F
};

/*  Macros for 1/n for n = 2, 3, and 4. These make the code look cleaner.     */
#define ONE_HALF 0.5F
#define ONE_THIRD 0.3333333333333333333333333333F
#define ONE_FOURTH 0.25F

/*  Function for computing natural log at single precision.                   */
float tmpl_Float_Log(float x)
{
    /*  Declare all necessary variables.                                      */
    float s, A;

    /*  Variable for the exponent of the float x. x is written as             *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 8 bit       *
     *  unsigned exponent in a float.                                         */
    signed int exponent;

    /*  Variable for the union of a float and the bits representing it.       */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NANF;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0F)
            return -TMPL_INFINITYF;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^23,      *
         *  which is 8.388608 x 10^6.                                         */
        w.r *= 8.388608E6F;

        /*  Compute the exponent. Since we multiplied by 2^23, subtract 23    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_FLOAT_BIAS - 23;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    else if (w.bits.expo == 0xFFU)
        return x;

    /*  For values close to but less than 1, the computation of the division  *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-8 absolute error since log(1) = 0). To       *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.99F < w.r && w.r < 1.0F)
    {
        s = 1.0F - x;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
        return -s * (
            1.0F + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * ONE_FOURTH
                )
            )
        );
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_FLOAT_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_FLOAT_BIAS;

    /*  We compute log(x) via:                                                *
     *                                                                        *
     *      log(x) = log(1.m * 2^b)                                           *
     *             = log(1.m) + log(2^b)                                      *
     *             = log(1.m) + b*log(2)                                      *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. We precompute log(t) in a table *
     *  and then have:                                                        *
     *                                                                        *
     *      log(x) = log(u) + b*log(2)                                        *
     *             = log(ut/t) + b*log(2)                                     *
     *             = log(u/t) + log(t) + b*log(2)                             *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute log(u/t) via a   *
     *  power series in the variable (s - 1) / (s + 1) with s = u/t.          *
     *                                                                        *
     *  We compute the value t = 1 + k/128 by computing k. The value k can be *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625 0.0078125             *
     *            |   |    |     |      |       |        |                    *
     *            V   V    V     V      V       V        V                    *
     *      u = 1.a   b    c     d      e       f        g        ....        *
     *                                                                        *
     *  If we treat the abcdefg as an integer in binary, this is the number k *
     *  such that t = 1 + k/128. So we simply need to read off this value     *
     *  from the mantissa. The value 1 / (1 + k/128) is stored in the rcpr    *
     *  array. man0 is 7 bits wide, so we just need this number.              */

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    s = w.r*tmpl_float_log_rcpr_table[w.bits.man0];

    /*  The Taylor series of log(1+x) for small x has very poor convergence.  *
     *  Using the alternating series test, the error is like 1/N where N is   *
     *  the number of terms in the series. log(x) has a different expansion:  *
     *                                                                        *
     *                inf                                                     *
     *                ----                                                    *
     *      log(x) =  \      2     2n+1                                       *
     *                /    ------ A             A = (x - 1) / (x + 1)         *
     *                ---- 2n + 1                                             *
     *                 n                                                      *
     *                                                                        *
     *  With x close to 1, q is close to zero, and the sum is in terms of the *
     *  square of q. This has great convergence.                              */
    A = 2.0F*(s - 1.0F) / (s + 1.0F);

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_F*(float)exponent + A +
        tmpl_float_log_table[w.bits.man0];
}
/*  End of tmpl_Float_Log.                                                    */

/*  undef all the macros in case someone wants to #include this file.         */
#undef ONE_HALF
#undef ONE_THIRD
#undef ONE_FOURTH

#else
/*  IEEE754 support not available, or libtmpl algorithms not requested.       */

/*  Standard library file containing log and logf.                            */
#include <math.h>

/*  C99 and higher have logf defined. C89 compilers may not.                  */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L

/*  Function for computing log at single precision.                           */
float tmpl_Float_Log(float x)
{
    return logf(x);
}
/*  End of tmpl_Float_Log.                                                    */

#else
/*  Else for #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.    */

/*  Function for computing log at single precision.                           */
float tmpl_Float_Log(float x)
{
    double logx = log((double)x);
    return (float)logx;
}
/*  End of tmpl_Float_Log.                                                    */

#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L.      */

#endif
/*  End of if for TMPL_HAS_IEEE754_FLOAT and TMPL_USE_MATH_ALGORITHMS.        */

