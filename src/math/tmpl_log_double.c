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
 *                             tmpl_log_double                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at double precision.      *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Log                                                       *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (double):                                                       *
 *          The natural log of x at double precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. log from math.h otherwise.                            *
 *  Method:                                                                   *
 *      If IEEE-754 support is available, and if libtmpl algorithms have      *
 *      been requested, log(x) is computed as follows:                        *
 *                                                                            *
 *          Check if x < 0, return Not-A-Number if so.                        *
 *                                                                            *
 *          Check if x = 0.0, return -infinity if so.                         *
 *                                                                            *
 *          Check if x is a subnormal (all exponent bits set to zero) number, *
 *          normalize by 2^52 if so, and then pass to the main part of the    *
 *          algorithm.                                                        *
 *                                                                            *
 *          For values not in the range 0.95 < x < 1.05, compute log(x) as    *
 *          follows:                                                          *
 *                                                                            *
 *              log(x) = log(1.m * 2^b)                                       *
 *                     = log(1.m) + log(2^b)                                  *
 *                     = log(1.m) + b*log(2)                                  *
 *                     = log(u) + b*log(2)      with u = 1.m                  *
 *                     = log(ut/t) + b*log(2)   with t = 1 + k/64 for some k. *
 *                     = log(u/t) + log(t) + b*log(2)                         *
 *                                                                            *
 *          Precompute log(t) in a table. Precompute 1/t in a table so that   *
 *          u/t can be computed as u * (1/t). Also precompute log(2). The     *
 *          value k is chosen to be the largest value such that               *
 *          t = 1 + k/64 <= u. This value k can be obtained directly from the *
 *          mantissa. By looking at the most significant 6 bits of the        *
 *          mantissa, the value k is simply these 6 bits read in binary.      *
 *                                                                            *
 *          The value s = u/t is such that 1 <= s < 1 + 1/64. Compute log(s)  *
 *          via the following sum:                                            *
 *                                                                            *
 *                        inf                                                 *
 *                        ----                                                *
 *              log(s) =  \      2     2n+1                                   *
 *                        /    ------ A             A = (s - 1) / (s + 1)     *
 *                        ---- 2n + 1                                         *
 *                        n = 0                                               *
 *                                                                            *
 *          A polynomial with the first three terms is then used. The         *
 *          standard Taylor series polynomial for ln(1 + x) with x small has  *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values close to 1, the computation of (s-1) / (s+1) leads to  *
 *          large relative error (about ~10^-8) since log(1) = 0              *
 *          (the absolute error is still around 10^-16). We can achieve much  *
 *          better relative error using the standard Taylor series to ten     *
 *          terms. This is slower than the series above, but more accurate in *
 *          this range. That is, for 0.95 < x < 1.05 we use:                  *
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
 *      is called and tmpl_Double_Log returns log(x) from math.h              *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of doubles with 0.0). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test yields the following results versus glibc:   *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231732732340180e-04                                   *
 *          libtmpl: 12.287552 seconds                                        *
 *          C:       13.931813 seconds                                        *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.8218232061381792e-15                             *
 *          rms abs error: 9.0288083896098205e-16                             *
 *          rms rel error: 7.1724645066645684e-17                             *
 *                                                                            *
 *      The error values assume 100% accuracy in glibc. I believe the         *
 *      documentation states the actual error of glibc's log is less then     *
 *      1 ULP. The value 2615628245 was chosen since 3 double arrays of that  *
 *      size take up 62 GB of memory, and the test was performed with 64 GB   *
 *      available.                                                            *
 *                                                                            *
 *      I'm quite pleased with the result. Slightly faster and almost         *
 *      identical in accuracy. It should be noted the DBL_EPSILON for 64-bit  *
 *      double is 2.22044605e-16, and the rms relative error is below this    *
 *      value. If we look at larger values, we get:                           *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e+02                                   *
 *          end:     1.0000000000000000e+08                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231694504430619e-02                                   *
 *          libtmpl: 12.267691 seconds                                        *
 *          C:       12.621467 seconds                                        *
 *          max abs error: 7.1054273576010019e-15                             *
 *          max rel error: 4.2634953389345209e-16                             *
 *          rms abs error: 1.9900347824366729e-15                             *
 *          rms rel error: 1.1289387375111485e-16                             *
 *                                                                            *
 *      The function also handles subnormal (denormal) values well:           *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   4.9406564584124654e-324                                  *
 *          end:     2.2250738585072009e-308                                  *
 *          samples: 2615628245                                               *
 *          dx:      8.5068420527204166e-318                                  *
 *          libtmpl: 20.185706 seconds                                        *
 *          C:       24.695628 seconds                                        *
 *          max abs error: 2.2737367544323206e-13                             *
 *          max rel error: 3.2034265037806259e-16                             *
 *          rms abs error: 7.0236686512747269e-14                             *
 *          rms rel error: 9.8982393371947679e-17                             *
 *                                                                            *
 *      The worst error is in the region around 1.                            *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   9.0000000000000002e-01                                   *
 *          end:     1.1000000000000001e+00                                   *
 *          samples: 2615628245                                               *
 *          dx:      7.6463465472326738e-11                                   *
 *          libtmpl: 12.642206 seconds                                        *
 *          C:       12.995864 seconds                                        *
 *          max abs error: 4.8572257327350599e-16                             *
 *          max rel error: 9.2097825747585990e-15                             *
 *          rms abs error: 9.6042579543112006e-17                             *
 *          rms rel error: 1.6879917053984482e-15                             *
 *                                                                            *
 *      These tests were performed with the following specs:                  *
 *                                                                            *
 *          CPU:  AMD Ryzen 3900 12-core                                      *
 *          MIN:  2200.0000 MHz                                               *
 *          MAX:  4672.0698 MHz                                               *
 *          ARCH: x86_64                                                      *
 *          RAM:  Ripjaw DDR4-3600 16GBx4                                     *
 *          MB:   Gigabyte Aorus x570 Elite WiFi                              *
 *          OS:   Debian 11 (Bullseye) GNU/LINUX                              *
 *                                                                            *
 *      Performance will of course vary on different systems. These tests     *
 *      had libtmpl built via clang. Building with GCC yields nearly          *
 *      identical times. Building libtmpl with TCC produced slower times:     *
 *                                                                            *
 *          libtmpl: 66.912582 seconds                                        *
 *          C:       13.422482 seconds                                        *
 *                                                                            *
 *      Building libtmpl with PCC had the following:                          *
 *                                                                            *
 *          libtmpl: 46.706748 seconds                                        *
 *          C:       13.351405 seconds                                        *
 *                                                                            *
 *      All tests were ran using the following options:                       *
 *                                                                            *
 *          gcc -O3 -flto tmpl_log_double_huge_time_test.c -o test -lm -ltmpl *
 *                                                                            *
 *      All tests can be found in libtmpl/tests/math_tests/time_tests/        *
 *                                                                            *
 *      Smaller tests were performed using a Windows 10 Virtual Machine. The  *
 *      results of libtmpl against Microsoft's C Library are as follows:      *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 50000000                                                 *
 *          libtmpl: 0.314 seconds                                            *
 *          C:       0.463 seconds                                            *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.9467566467383324e-15                             *
 *          rms abs error: 9.0989260892815339e-16                             *
 *          rms rel error: 1.0682607458165517e-16                             *
 *                                                                            *
 *      The errors are similar to those for glibc. The performance is about   *
 *      1.47x better. Similar values are found for denormal and large values. *
 *      GNOME Boxes was used for virtualization. libtmpl was built using      *
 *      clang for this test. Using MSVC yields:                               *
 *                                                                            *
 *          samples: 50000000                                                 *
 *          libtmpl: 0.974 seconds                                            *
 *          C:       0.409 seconds                                            *
 *                                                                            *
 *      Significantly worse.                                                  *
 *                                                                            *
 *      Finally, on a FreeBSD 12.2 Virtual Machine (via GNOME Boxes), we have *
 *      the following. Building libtmpl with FreeBSD's cc:                    *
 *                                                                            *
 *          tmpl_Double_Log vs. log                                           *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+06                                   *
 *          samples: 100000000                                                *
 *          libtmpl: 0.523438 seconds                                         *
 *          C:       0.820312 seconds                                         *
 *          max abs error: 3.5527136788005009e-15                             *
 *          max rel error: 8.8111997278351631e-15                             *
 *          rms abs error: 9.0941028467094906e-16                             *
 *          rms rel error: 1.0677265624885180e-16                             *
 *                                                                            *
 *      Building with clang-13 gives:                                         *
 *                                                                            *
 *          libtmpl: 0.492188 seconds                                         *
 *          C:       0.804688 seconds                                         *
 *                                                                            *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_DOUBLE == 0 or if               *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_Double_Log is identical to the standard library log function.*
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
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/03/11: Ryan Maguire                                                  *
 *      Added more terms for the polynomial in the region around 1. Changed   *
 *      this region of 0.95 < x < 1.05 instead of 0.995 < x < 1.0. Worst case *
 *      relative error is 9 x 10^-15. rms error is in this interval is        *
 *      1 x 10^-15. rms error for all positive real numbers is 1 x 10^-17,    *
 *      which is less than 1 ULP.                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1 && \
    defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

static double table[128] = {
    0.0,
    0.00778214044205494894746290006113676368,
    0.0155041865359652541508540460424468359,
    0.0231670592815343782287991609622899166,
    0.0307716586667536883710282075967721641,
    0.0383188643021365991937553251237972903,
    0.0458095360312942031666792676146633421,
    0.0532445145188122828658701937865287769,
    0.0606246218164348425806061320404202633,
    0.0679506619085077493945652777726294140,
    0.0752234212375875256986053399836624146,
    0.0824436692110745912681600686683078059,
    0.0896121586896871326199514693784845288,
    0.0967296264585511122955710564874634370,
    0.103796793681643564826061803763974688,
    0.110814366340290114194806169323211928,
    0.117783035656383454538794109470521705,
    0.124703478500957235863406515380863268,
    0.131576357788719272588716128689483162,
    0.138402322859119135685325873601649187,
    0.145182009844497897281935063740564324,
    0.151916042025841975071803424896884511,
    0.158605030176638584093371174625841575,
    0.165249572895307162875611449277240314,
    0.171850256926659222340098946055147265,
    0.178407657472818297119400241510941968,
    0.184922338494011992663903592659249621,
    0.191394852999629454609298807561308873,
    0.197825743329919880362572071196961469,
    0.204215541428690891503820386196239272,
    0.210564769107349637669552812732351514,
    0.216873938300614359619089525744347498,
    0.223143551314209755766295090309834503,
    0.229374101064845829991480725046139872,
    0.235566071312766909077588218941043410,
    0.241719936887145168144307515913513900,
    0.247836163904581256780602765746524748,
    0.253915209980963444137323297906606667,
    0.259957524436926066972079494542311045,
    0.265963548497137941339125926537543389,
    0.271933715483641758831669494532999162,
    0.277868451003456306186350032923401233,
    0.283768173130644598346901222350254767,
    0.289633292583042676878893055525668970,
    0.295464212893835876386681906054964195,
    0.301261330578161781012875538233755493,
    0.307025035294911862075124540535377902,
    0.312755710003896888386246559688319032,
    0.318453731118534615810247213590599596,
    0.324119468654211976090670760434987352,
    0.329753286372467981814422811920789811,
    0.335355541921137830257179579814166199,
    0.340926586970593210305089199780356208,
    0.346466767346208580918462188425772951,
    0.351976423157178184655447456259438926,
    0.357455888921803774226009490140904474,
    0.362905493689368453137824345977489846,
    0.368325561158707653048230154050398827,
    0.373716409793584080821016832715823507,
    0.379078352934969458390853345631019859,
    0.384411698910332039734790062481290869,
    0.389716751140025213370463604003520867,
    0.394993808240868978106394036364981768,
    0.400243164127012706929325101995131170,
    0.405465108108164381978013115464349137,
    0.410659924985268385934306203175822788,
    0.415827895143710965613328892954902305,
    0.420969294644129636128867161506795972,
    0.426084395310900063124544879595476619,
    0.431173464818371340859172478955594998,
    0.436236766774918070349041323061121301,
    0.441274560804875229489496441661301225,
    0.446287102628419511532590180619669007,
    0.451274644139458585144692383079012479,
    0.456237433481587594380805538163929748,
    0.461175715122170166367999925597855359,
    0.466089729924599224558619247504769400,
    0.470979715218791012546897856056359251,
    0.475845904869963914265209586304381412,
    0.480688529345751907676618455448011551,
    0.485507815781700807801791077190788901,
    0.490303988045193838150346159645746861,
    0.495077266797851514597964584842833665,
    0.499827869556449329821331415247044142,
    0.504556010752395287058308531738174930,
    0.509261901789807946804074919228323825,
    0.513945751102234316801006088274217593,
    0.518607764208045632152976996364798699,
    0.523248143764547836516807224934870842,
    0.527867089620842385113892217778300964,
    0.532464798869471843873923723460142243,
    0.537041465896883654566729244153832299,
    0.541597282432744371576542303900434099,
    0.546132437598135650382397209231209164,
    0.550647117952662279259948179204913460,
    0.555141507540501592715480359515904050,
    0.559615787935422686270888500526826593,
    0.564070138284802966071384290090190712,
    0.568504735352668712078738764866962264,
    0.572919753561785509092756726626261069,
    0.577315365034823604318112061519496402,
    0.581691739634622482520610753725372341,
    0.586049045003578208904119436287324350,
    0.590387446602176374641916708123598758,
    0.594707107746692789514343546529205333,
    0.599008189646083399381600024461651502,
    0.603290851438084262340585186661310606,
    0.607555250224541795501085152791125372,
    0.611801541105992903529889766428814784,
    0.616029877215514019647565928196700650,
    0.620240409751857528851494632567246857,
    0.624433288011893501042538744054673120,
    0.628608659422374137744308205774183640,
    0.632766669571037829545786468503579758,
    0.636907462237069231620494427181199191,
    0.641031179420931291055601334405392547,
    0.645137961373584701665228496134731906,
    0.649227946625109818890839969905311122,
    0.653301272012745638758615881210873885,
    0.657358072708360030141890023245936166,
    0.661398482245365008260235838709650938,
    0.665422632545090448950092610006660181,
    0.669430653942629267298885270929503510,
    0.673422675212166720297960388801017265,
    0.677398823591806140809682609997348299,
    0.681359224807903068948071559568089442,
    0.685304003098919416544048078967232986,
    0.689233281238808980324914337814603903
};

static double rcpr[128] = {
    1.0,
    0.992248062015503875968992248062015504,
    0.984615384615384615384615384615384615,
    0.977099236641221374045801526717557252,
    0.969696969696969696969696969696969697,
    0.962406015037593984962406015037593985,
    0.955223880597014925373134328358208955,
    0.948148148148148148148148148148148148,
    0.941176470588235294117647058823529412,
    0.934306569343065693430656934306569343,
    0.927536231884057971014492753623188406,
    0.920863309352517985611510791366906475,
    0.914285714285714285714285714285714286,
    0.907801418439716312056737588652482270,
    0.901408450704225352112676056338028169,
    0.895104895104895104895104895104895105,
    0.888888888888888888888888888888888889,
    0.882758620689655172413793103448275862,
    0.876712328767123287671232876712328767,
    0.870748299319727891156462585034013605,
    0.864864864864864864864864864864864865,
    0.859060402684563758389261744966442953,
    0.853333333333333333333333333333333333,
    0.847682119205298013245033112582781457,
    0.842105263157894736842105263157894737,
    0.836601307189542483660130718954248366,
    0.831168831168831168831168831168831169,
    0.825806451612903225806451612903225806,
    0.820512820512820512820512820512820513,
    0.815286624203821656050955414012738854,
    0.810126582278481012658227848101265823,
    0.805031446540880503144654088050314465,
    0.800000000000000000000000000000000000,
    0.795031055900621118012422360248447205,
    0.790123456790123456790123456790123457,
    0.785276073619631901840490797546012270,
    0.780487804878048780487804878048780488,
    0.775757575757575757575757575757575758,
    0.771084337349397590361445783132530120,
    0.766467065868263473053892215568862275,
    0.761904761904761904761904761904761905,
    0.757396449704142011834319526627218935,
    0.752941176470588235294117647058823529,
    0.748538011695906432748538011695906433,
    0.744186046511627906976744186046511628,
    0.739884393063583815028901734104046243,
    0.735632183908045977011494252873563218,
    0.731428571428571428571428571428571429,
    0.727272727272727272727272727272727273,
    0.723163841807909604519774011299435028,
    0.719101123595505617977528089887640449,
    0.715083798882681564245810055865921788,
    0.711111111111111111111111111111111111,
    0.707182320441988950276243093922651934,
    0.703296703296703296703296703296703297,
    0.699453551912568306010928961748633880,
    0.695652173913043478260869565217391304,
    0.691891891891891891891891891891891892,
    0.688172043010752688172043010752688172,
    0.684491978609625668449197860962566845,
    0.680851063829787234042553191489361702,
    0.677248677248677248677248677248677249,
    0.673684210526315789473684210526315789,
    0.670157068062827225130890052356020942,
    0.666666666666666666666666666666666667,
    0.663212435233160621761658031088082902,
    0.659793814432989690721649484536082474,
    0.656410256410256410256410256410256410,
    0.653061224489795918367346938775510204,
    0.649746192893401015228426395939086294,
    0.646464646464646464646464646464646465,
    0.643216080402010050251256281407035176,
    0.640000000000000000000000000000000000,
    0.636815920398009950248756218905472637,
    0.633663366336633663366336633663366337,
    0.630541871921182266009852216748768473,
    0.627450980392156862745098039215686275,
    0.624390243902439024390243902439024390,
    0.621359223300970873786407766990291262,
    0.618357487922705314009661835748792271,
    0.615384615384615384615384615384615385,
    0.612440191387559808612440191387559809,
    0.609523809523809523809523809523809524,
    0.606635071090047393364928909952606635,
    0.603773584905660377358490566037735849,
    0.600938967136150234741784037558685446,
    0.598130841121495327102803738317757009,
    0.595348837209302325581395348837209302,
    0.592592592592592592592592592592592593,
    0.589861751152073732718894009216589862,
    0.587155963302752293577981651376146789,
    0.584474885844748858447488584474885845,
    0.581818181818181818181818181818181818,
    0.579185520361990950226244343891402715,
    0.576576576576576576576576576576576577,
    0.573991031390134529147982062780269058,
    0.571428571428571428571428571428571429,
    0.568888888888888888888888888888888889,
    0.566371681415929203539823008849557522,
    0.563876651982378854625550660792951542,
    0.561403508771929824561403508771929825,
    0.558951965065502183406113537117903930,
    0.556521739130434782608695652173913043,
    0.554112554112554112554112554112554113,
    0.551724137931034482758620689655172414,
    0.549356223175965665236051502145922747,
    0.547008547008547008547008547008547009,
    0.544680851063829787234042553191489362,
    0.542372881355932203389830508474576271,
    0.540084388185654008438818565400843882,
    0.537815126050420168067226890756302521,
    0.535564853556485355648535564853556485,
    0.533333333333333333333333333333333333,
    0.531120331950207468879668049792531120,
    0.528925619834710743801652892561983471,
    0.526748971193415637860082304526748971,
    0.524590163934426229508196721311475410,
    0.522448979591836734693877551020408163,
    0.520325203252032520325203252032520325,
    0.518218623481781376518218623481781377,
    0.516129032258064516129032258064516129,
    0.514056224899598393574297188755020080,
    0.512000000000000000000000000000000000,
    0.509960159362549800796812749003984064,
    0.507936507936507936507936507936507937,
    0.505928853754940711462450592885375494,
    0.503937007874015748031496062992125984,
    0.501960784313725490196078431372549020
};

/*  Macros for 1/n for n = 2, 3, ..., 6, 7. These make the code look cleaner. */
#define A0 2.0
#define A1 0.666666666666666666666667
#define A2 0.4
#define A3 0.285714285714285714285714
#define A4 0.222222222222222222222222
#define A5 0.181818181818181818181818

/*  Function for computing natural log at double precision.                   */
double tmpl_Double_Log(double x)
{
    /*  Declare all necessary variables.                                      */
    double s, poly, A, A_sq;

    /*  Variable for the exponent of the double x. x is written as            *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 11 bit      *
     *  unsigned exponent in a double.                                        */
    signed int exponent;

    /*  Variable for the index of the arrays table and rcpr defined above     *
     *  which corresponds to the input x.                                     */
    unsigned int ind;

    /*  Variable for the union of a double and the bits representing it.      */
    tmpl_IEEE754_Double w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NAN;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0)
            return -TMPL_INFINITY;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^52,      *
         *  which is 4.503599627370496 x 10^15.                               */
        w.r *= 4.503599627370496E15;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS - 52;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
    else if (w.bits.expo == 0x7FFU)
        return x;

    /*  For values in the region around 1, the computation of the division    *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-16 absolute error since log(1) = 0). To      *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.875 < w.r && w.r < 1.125)
    {
        A = (x - 1.0)/(x + 1.0);
        A_sq = A*A;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
        return A * (
            A0 + A_sq * (
                A1 + A_sq * (
                    A2 + A_sq * (
                        A3 + A_sq * (A4 + A_sq * A5)
                    )
                )
            )
        );
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  We compute log(x) via:                                                *
     *                                                                        *
     *      log(x) = log(1.m * 2^b)                                           *
     *             = log(1.m) + log(2^b)                                      *
     *             = log(1.m) + b*log(2)                                      *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/64 such that t <= u. We precompute log(t) in a table  *
     *  and then have:                                                        *
     *                                                                        *
     *      log(x) = log(u) + b*log(2)                                        *
     *             = log(ut/t) + b*log(2)                                     *
     *             = log(u/t) + log(t) + b*log(2)                             *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/64. We compute log(u/t) via a    *
     *  power series in the variable (s - 1) / (s + 1) with s = u/t.          *
     *                                                                        *
     *  We compute the value t = 1 + k/64 by computing k. The value k can be  *
     *  obtained from the mantissa of the input. We have:                     *
     *                                                                        *
     *           0.5 0.25 0.125 0.0625 0.03125 0.015625                       *
     *            |   |    |     |      |       |                             *
     *            V   V    V     V      V       V                             *
     *      u = 1.a   b    c     d      e       f       ....                  *
     *                                                                        *
     *  If we treat the abcdef as an integer in binary, this is the number k  *
     *  such that t = 1 + k/64. So we simply need to read off this value from *
     *  the mantissa. The value 1 / (1 + k/64) is stored in the rcpr array.   */
    ind = w.bits.man0;

    /*  man0 has the first 4 bits. The next 16 bits are in man1. We only need *
     *  the first two bits from man1. Obtain these by shifting down 14 bits   *
     *  via >> 14. We also need to shift the value of man0 up by 2^2, which   *
     *  is obtained by << 2. Altogether, this gives us the number abcdef in   *
     *  binary, as above, a is the first bit, ..., f is the sixth.            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    s = w.r*rcpr[ind];

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
     *  With x close to 1, A is close to zero, and the sum is in terms of the *
     *  square of A. This has great convergence.                              */
    A = (s - 1.0) / (s + 1.0);
    A_sq = A*A;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    poly = A * (A0 + A_sq * (A1 + A_sq * A2));

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two*exponent + poly + table[ind];
}
/*  End of tmpl_Double_Log.                                                   */

/*  undef all the macros in case someone wants to #include this file.         */
#undef A0
#undef A1
#undef A2
#undef A3
#undef A4
#undef A5

#else
/*  Else for TMPL_HAS_IEEE754_DOUBLE == 1 and TMPL_USE_MATH_ALGORITHMS == 1.  */

/*  The C Standard Library requires a log function. If the user lacks         *
 *  IEEE754 support, or does not want to use libtmpl algorithms, simply wrap  *
 *  this function for tmpl_Double_Log.                                        */
#include <math.h>

/*  Function for computing log at double precision.                           */
double tmpl_Double_Log(double x)
{
    return log(x);
}
/*  End of tmpl_Double_Log.                                                   */

#endif
/*  End of if for TMPL_HAS_IEEE754_DOUBLE and TMPL_USE_MATH_ALGORITHMS.       */
