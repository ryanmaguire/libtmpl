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
 *                              tmpl_sqrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing square roots at double precision.         *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Sqrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = sqrt(x), the unique non-negative number y such that for  *
 *      non-negative x we have x = y^2.                                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      sqrt_x (double):                                                      *
 *          The square root of x at double precision.                         *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. sqrt from math.h otherwise.                           *
 *  Method:                                                                   *
 *      Use a combination of square root rules, Taylor series, and Newton's   *
 *      method. That is, sqrt(x) is computed as follows:                      *
 *                                                                            *
 *          If x < 0, return Not-A-Number.                                    *
 *          If x = +/- NaN, +Inf, or +/- 0, return x.                         *
 *          If x is subnormal (denormal), normalize by 2^52.                  *
 *                                                                            *
 *          sqrt(x) = sqrt(1.m * 2^b)                                         *
 *                  = sqrt(1.m) * sqrt(2^b)                                   *
 *                  = sqrt(1.m) * 2^{b/2}                                     *
 *                  = sqrt(u) * 2^{b/2}     with u = 1.m                      *
 *                  = sqrt(ut/t) * 2^{b/2}  with t = 1 + k/128 for some k.    *
 *                  = sqrt(u/t) * sqrt(t) * 2^{b/2}                           *
 *                                                                            *
 *      Choose t = 1 + k/128 by choosing k to be the largest integer such     *
 *      that 1 + k/128 <= u. Precompute sqrt(t) and 1/t in a table. The       *
 *      value u/t is now between 1 and 1 + 1/128. Compute sqrt(u/t) by:       *
 *                                                                            *
 *                                                                            *
 *          y = sqrt(u/t)                                                     *
 *            = sqrt(1 + s)             with s = u/t - 1.                     *
 *            ~ 1 + 0.5x - 0.125x^2                                           *
 *                                                                            *
 *      y is now accurate to at least 8 decimals. We can double this to at    *
 *      least 16 decimals using 1 iteration of Newton's method. We have:      *
 *                                                                            *
 *                y ~ sqrt(x)                                                 *
 *          y^2 - x ~ 0                                                       *
 *             f(y) = y^2 - x                                                 *
 *            f'(y) = 2y                                                      *
 *                                                                            *
 *      Apply Newton's method for 1 iteration:                                *
 *                                                                            *
 *              out = y - f(y)/f'(y)                                          *
 *                  = y - (y^{2} - x)/(2y)                                    *
 *                  = (2y^{2} - y^{2} + x)/(2y)                               *
 *                  = (y^{2} + x)/(2y)                                        *
 *                  = 0.5*(y + x/y)                                           *
 *                                                                            *
 *      Lastly, since 2^{b/2} is not an integer for odd valued b, use the     *
 *      fact that for odd b we have b = 2k+1, so b/2 = k+1/2, and thus:       *
 *                                                                            *
 *          2^{b/2} = 2^{k + 1/2}                                             *
 *                  = 2^{k} * 2^{1/2}                                         *
 *                  = sqrt(2) * 2^{k}                                         *
 *                                                                            *
 *      Precompute sqrt(2) and multiply the result by this if b is odd.       *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of doubles with 0.0). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *      sqrt is usually implemented in hardware, and the built-in square root *
 *      function is much faster than anything done in software. Comparing     *
 *      this routine againt the __builtin_sqrt from glibc on x86_64, we find: *
 *                                                                            *
 *          tmpl_Double_Sqrt vs. sqrt                                         *
 *          start:   1.0000000000000000e-04                                   *
 *          end:     1.0000000000000000e+04                                   *
 *          samples: 2615628245                                               *
 *          dx:      3.8231732353846026e-06                                   *
 *          libtmpl: 13.689632 seconds                                        *
 *          C:       8.601256 seconds                                         *
 *          max abs error: 5.6843418860808015e-14                             *
 *          max rel error: 6.6359741442268620e-16                             *
 *          rms abs error: 6.7487215520428957e-15                             *
 *          rms rel error: 9.4046566544817157e-17                             *
 *                                                                            *
 *      The rms relative error is below DBL_EPSILON, but the time is          *
 *      much worse (about 59% worse). It may be fairer to compare this        *
 *      function against another implementation in software. The openlibm     *
 *      implementation uses a bit-by-bit algorithm to ensure the value is     *
 *      accurate to all 52 bits in a double, and correctly rounded. This      *
 *      is a lot slower, as the test below reveals.                           *
 *                                                                            *
 *          tmpl_Double_Sqrt vs. sqrt                                         *
 *          start:    1.0000000000000000e-04                                  *
 *          end:      1.0000000000000000e+04                                  *
 *          samples:  2615628245                                              *
 *          dx:       3.8231732353846026e-06                                  *
 *          libtmpl:  13.816768 seconds                                       *
 *          openlibm: 420.931444 seconds                                      *
 *          max abs error: 5.6843418860808015e-14                             *
 *          max rel error: 6.6359741442268620e-16                             *
 *          rms abs error: 6.7487215520428957e-15                             *
 *          rms rel error: 9.4046566544817157e-17                             *
 *                                                                            *
 *      So, there's a bit of a trade off. The algorithm is not accurate to    *
 *      all bits, but it is 30x faster. Note, openlibm also implements        *
 *      sqrt in hardware, the bit-by-bit method is only used if a built-in    *
 *      square root function is not available.                                *
 *                                                                            *
 *      The value 2615628245 was chosen since 3 double arrays of that size    *
 *      take up 62 GB of memory, and there was 64 GB available.               *
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
 *      The glibc tests were ran using the following options:                 *
 *                                                                            *
 *          gcc -O3 -flto tmpl_sqrt_double_huge_time_test.c -o test -lm -ltmpl*
 *                                                                            *
 *      -O3 is optimization level, and -flto is link-time optimization.       *
 *      tmpl_sqrt_double_huge_time_test.c can be found in                     *
 *          libtmpl/tests/math_tests/time_tests/                              *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_DOUBLE == 0 or if               *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_Double_Sqrt is identical to the standard sqrt function.      *
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
 *  Date:       February 22, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1 && \
    defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  The values sqrt(1 + k/128) for k = 0, 1, ..., 126, 127.                   */
static double table[128] = {
    1.0000000000000000000000000000000,
    1.0038986502630631587814157208459,
    1.0077822185373187065458266537880,
    1.0116508785149153420370293943119,
    1.0155048005794950450574854460333,
    1.0193441518937556547578604929810,
    1.0231690964840562462442129655917,
    1.0269797953221864627318183427515,
    1.0307764064044151374553524639935,
    1.0345590848279280370779360753360,
    1.0383279828647593565730328431134,
    1.0420832500333166759944035177135,
    1.0458250331675944349727150322315,
    1.0495534764841665751224584232305,
    1.0532687216470448288292674882753,
    1.0569709078304851811357823701735,
    1.0606601717798212866012665431573,
    1.0643366478704000728833326139923,
    1.0680004681646913959839560407800,
    1.0716517624676404179613117826838,
    1.0752906583803283464661841918812,
    1.0789172813520042973878796249536,
    1.0825317547305483084546539634412,
    1.0861341998114229346449263315813,
    1.0897247358851683880592454959649,
    1.0933034802834938382889036645398,
    1.0968705484240152575507985384270,
    1.1004260538536880716105767610310,
    1.1039701082909808568455053408699,
    1.1075028216668344001244453185960,
    1.1110243021644486062614302094261,
    1.1145346562579379927031483855089,
    1.1180339887498948482045868343656,
    1.1215224028078975471714659308581,
    1.1250000000000000000000000000000,
    1.1284668803292367782613181982975,
    1.1319231422671770783217260208730,
    1.1353688827865593745334498036443,
    1.1388041973930373602432032630861,
    1.1422291801560665785020669945915,
    1.1456439237389600016470117984320,
    1.1490485194281397271513720884204,
    1.1524430571616109137502842852203,
    1.1558276255566830844219110715227,
    1.1592023119369629690645520092488,
    1.1625672023586421474977133451070,
    1.1659223816361018806943094427901,
    1.1692679333668566829949214788489,
    1.1726039399558573886414075283861,
    1.1759304826391737005723170719273,
    1.1792476415070754764150825472028,
    1.1825554955265313044453633803626,
    1.1858541225631422494995850791623,
    1.1891435994025280040371184834364,
    1.1924240017711820614407769825290,
    1.1956954043568119359739067970636,
    1.1989578808281798853993595160407,
    1.2022115038544590469909601825758,
    1.2054563451241193744700038809291,
    1.2086924753633572612702712080185,
    1.2119199643540822535186101438557,
    1.2151388809514737933061188942665,
    1.2183492931011204883548016499875,
    1.2215512678557539772367511819066,
    1.2247448713915890490986420373529,
    1.2279301690242812826432845870217,
    1.2311072252245130902182764268647,
    1.2342761036332186885899038152327,
    1.2374368670764581677014776336835,
    1.2405895775799504918231541078932,
    1.2437342963832749434180997762515,
    1.2468710839537502082283676396337,
    1.2500000000000000000000000000000,
    1.2531211034852138344224211564032,
    1.2562344526401112837774081140949,
    1.2593401049756177760254071743209,
    1.2624381172952597441704232396337,
    1.2655285457072866833279313931188,
    1.2686114456365274335810650148670,
    1.2716868718359877760746043112424,
    1.2747548783981962075070560272557,
    1.2778155187663045438976964067523,
    1.2808688457449497979026298350651,
    1.2839149115108835747211747948459,
    1.2869537676233750394746711830247,
    1.2899854650343933235708268617173,
    1.2930100540985750587173249303284,
    1.2960275845829825546599366749906,
    1.2990381056766579701455847561294,
    1.3020416659999786658132951021649,
    1.3050383136138187724697192528185,
    1.3080280960285218582946961804402,
    1.3110110602126894337393168920999,
    1.3139872526017898930262410660935,
    1.3169567191065923560501755827375,
    1.3199195051214297439241398350616,
    1.3228756555322952952508078768196,
    1.3258252147247766082515831789466,
    1.3287682265918311759998902393662,
    1.3317047345414072680269071455173,
    1.3346347815039139013514404956995,
    1.3375584099395435373907689818678,
    1.3404756618454510381017699590193,
    1.3433865787627923149527506609676,
    1.3462912017836260078126776228851,
    1.3491895715576814374475295341304,
    1.3520817282989959849197079753014,
    1.3549677117924249636868515300458,
    1.3578475614000269654864366718422,
    1.3607213160673275790718439061685,
    1.3635890143294643014377693109216,
    1.3664506943172153842454612562837,
    1.3693063937629152836424244570020,
    1.3721561500062593094816361902560,
    1.3750000000000000000000000000000,
    1.3778379803155376802359722920221,
    1.3806701271484075967763642304180,
    1.3834964763236659577495159256893,
    1.3863170633011771452564500128262,
    1.3891319231808043075860224840425,
    1.3919410907075054805298678247296,
    1.3947446002763373308359242543712,
    1.3975424859373685602557335429570,
    1.4003347814005049556930185898401,
    1.4031215200402280195939057746187,
    1.4059027349002490648793174696195,
    1.4086784586980806103562504614679,
    1.4114487238295268656075312412307
};

/*  The values 1/(1 + k/128) for k = 0, 1, ..., 126, 127.                     */
static double rcpr[128] = {
    1.0000000000000000000000000000000,
    0.99224806201550387596899224806202,
    0.98461538461538461538461538461538,
    0.97709923664122137404580152671756,
    0.96969696969696969696969696969697,
    0.96240601503759398496240601503759,
    0.95522388059701492537313432835821,
    0.94814814814814814814814814814815,
    0.94117647058823529411764705882353,
    0.93430656934306569343065693430657,
    0.92753623188405797101449275362319,
    0.92086330935251798561151079136691,
    0.91428571428571428571428571428571,
    0.90780141843971631205673758865248,
    0.90140845070422535211267605633803,
    0.89510489510489510489510489510490,
    0.88888888888888888888888888888889,
    0.88275862068965517241379310344828,
    0.87671232876712328767123287671233,
    0.87074829931972789115646258503401,
    0.86486486486486486486486486486486,
    0.85906040268456375838926174496644,
    0.85333333333333333333333333333333,
    0.84768211920529801324503311258278,
    0.84210526315789473684210526315789,
    0.83660130718954248366013071895425,
    0.83116883116883116883116883116883,
    0.82580645161290322580645161290323,
    0.82051282051282051282051282051282,
    0.81528662420382165605095541401274,
    0.81012658227848101265822784810127,
    0.80503144654088050314465408805031,
    0.80000000000000000000000000000000,
    0.79503105590062111801242236024845,
    0.79012345679012345679012345679012,
    0.78527607361963190184049079754601,
    0.78048780487804878048780487804878,
    0.77575757575757575757575757575758,
    0.77108433734939759036144578313253,
    0.76646706586826347305389221556886,
    0.76190476190476190476190476190476,
    0.75739644970414201183431952662722,
    0.75294117647058823529411764705882,
    0.74853801169590643274853801169591,
    0.74418604651162790697674418604651,
    0.73988439306358381502890173410405,
    0.73563218390804597701149425287356,
    0.73142857142857142857142857142857,
    0.72727272727272727272727272727273,
    0.72316384180790960451977401129944,
    0.71910112359550561797752808988764,
    0.71508379888268156424581005586592,
    0.71111111111111111111111111111111,
    0.70718232044198895027624309392265,
    0.70329670329670329670329670329670,
    0.69945355191256830601092896174863,
    0.69565217391304347826086956521739,
    0.69189189189189189189189189189189,
    0.68817204301075268817204301075269,
    0.68449197860962566844919786096257,
    0.68085106382978723404255319148936,
    0.67724867724867724867724867724868,
    0.67368421052631578947368421052632,
    0.67015706806282722513089005235602,
    0.66666666666666666666666666666667,
    0.66321243523316062176165803108808,
    0.65979381443298969072164948453608,
    0.65641025641025641025641025641026,
    0.65306122448979591836734693877551,
    0.64974619289340101522842639593909,
    0.64646464646464646464646464646465,
    0.64321608040201005025125628140704,
    0.64000000000000000000000000000000,
    0.63681592039800995024875621890547,
    0.63366336633663366336633663366337,
    0.63054187192118226600985221674877,
    0.62745098039215686274509803921569,
    0.62439024390243902439024390243902,
    0.62135922330097087378640776699029,
    0.61835748792270531400966183574879,
    0.61538461538461538461538461538462,
    0.61244019138755980861244019138756,
    0.60952380952380952380952380952381,
    0.60663507109004739336492890995261,
    0.60377358490566037735849056603774,
    0.60093896713615023474178403755869,
    0.59813084112149532710280373831776,
    0.59534883720930232558139534883721,
    0.59259259259259259259259259259259,
    0.58986175115207373271889400921659,
    0.58715596330275229357798165137615,
    0.58447488584474885844748858447489,
    0.58181818181818181818181818181818,
    0.57918552036199095022624434389140,
    0.57657657657657657657657657657658,
    0.57399103139013452914798206278027,
    0.57142857142857142857142857142857,
    0.56888888888888888888888888888889,
    0.56637168141592920353982300884956,
    0.56387665198237885462555066079295,
    0.56140350877192982456140350877193,
    0.55895196506550218340611353711790,
    0.55652173913043478260869565217391,
    0.55411255411255411255411255411255,
    0.55172413793103448275862068965517,
    0.54935622317596566523605150214592,
    0.54700854700854700854700854700855,
    0.54468085106382978723404255319149,
    0.54237288135593220338983050847458,
    0.54008438818565400843881856540084,
    0.53781512605042016806722689075630,
    0.53556485355648535564853556485356,
    0.53333333333333333333333333333333,
    0.53112033195020746887966804979253,
    0.52892561983471074380165289256198,
    0.52674897119341563786008230452675,
    0.52459016393442622950819672131148,
    0.52244897959183673469387755102041,
    0.52032520325203252032520325203252,
    0.51821862348178137651821862348178,
    0.51612903225806451612903225806452,
    0.51405622489959839357429718875502,
    0.51200000000000000000000000000000,
    0.50996015936254980079681274900398,
    0.50793650793650793650793650793651,
    0.50592885375494071146245059288538,
    0.50393700787401574803149606299213,
    0.50196078431372549019607843137255
};

/*  Function for computing square roots at double precision.                  */
double tmpl_Double_Sqrt(double x)
{
    /*  Union of a double and the bits representing a double.                 */
    tmpl_IEEE754_Double w;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    signed int exponent;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. sqrt(negative) is undefined. sqrt(0) = 0,              *
     *  sqrt(inf) = inf, and sqrt(Not-A-Number) = Not-A-Number.               */
    if (w.bits.sign)
        return TMPL_NAN;

    /*  Subnormal number or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  sqrt(0) = 0.0.                                                    */
        if (w.r == 0.0)
            return x;

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

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  We compute sqrt(x) via:                                               *
     *                                                                        *
     *      sqrt(x) = sqrt(1.m * 2^b)                                         *
     *              = sqrt(1.m) * sqrt(2^b)                                   *
     *              = sqrt(1.m) * 2^(b/2)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute sqrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      sqrt(x) = sqrt(u) * 2^(b/2)                                       *
     *              = sqrt(ut/t) * 2^(b/2)                                    *
     *              = sqrt(u/t) * sqrt(t) * 2^(b/2)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute sqrt(u/t) via a  *
     *  power series in the variable 1 + (u/t - 1).                           *
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
     *  array. man0 is 4 bits wide, so we need this and the first 3 bits of   *
     *  man1, the next part of the mantissa.                                  */
    ind = w.bits.man0;

    /*  Obtain the last 3 bits of man1 by shifting down 13 bits. man1 is 16   *
     *  bits wide.                                                            */
    ind = (ind << 3U) + (w.bits.man1 >> 13U);

    /*  Compute s = u/t - 1 via s = u * (1/t) - 1 using the array rcpr.       */
    w.r = w.r*rcpr[ind] - 1.0;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    w.r = 1.0 + w.r*(0.5 + w.r*(-0.125 + 0.0625*w.r));

    /*  Set the exponent part b to the integral part of b/2 by bit shifting   *
     *  down by 1.                                                            */
    w.bits.expo = (unsigned int)((signed int)w.bits.expo + (exponent >> 1));

    /*  If the exponent is odd, expo/2 is not an integer. Writing expo = 2k+1 *
     *  we have expo/2 = k + 1/2, so 2^{expo/2} = 2^{k+1/2} = 2^{k} * 2^{1/2} *
     *  which is equal to sqrt(2) * 2^{k}. We need to multiply the result by  *
     *  sqrt(2) in the case that exponent is odd. Also, multiply the result   *
     *  sqrt(u/t) by sqrt(t) using the table, giving us sqrt(u).              */
    if (exponent % 2)
        w.r *= 1.4142135623730950488016887242097*table[ind];
    else
        w.r *= table[ind];

    /*  Apply 1 iteration of Newton's method and return.                      */
    return 0.5*(w.r + x/w.r);
}
/*  End of tmpl_Double_Sqrt.                                                  */

#else
/*  Else for TMPL_HAS_IEEE754_DOUBLE and TMPL_USE_MATH_ALGORITHMS.            */

/*  math.h is required to provide a sqrt function. This is usually a builtin  *
 *  function (the computation is done in hardware, not software) which is     *
 *  much faster.                                                              */
#include <math.h>

/*  Function for computation square roots at double precision.                */
double tmpl_Double_Sqrt(double x)
{
    return sqrt(x);
}
/*  End of tmpl_Double_Sqrt.                                                  */

#endif
/*  End of #if for TMPL_HAS_IEEE754_DOUBLE and TMPL_USE_MATH_ALGORITHMS.      */
