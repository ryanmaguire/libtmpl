/******************************************************************************
 *                                  LICENSE                                   *
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
 *                              tmpl_cbrt_double                              *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing cubic roots at double precision.          *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Cbrt                                                      *
 *  Purpose:                                                                  *
 *      Computes y = cbrt(x), the unique number y such that x = y^3.          *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      cbrt_x (double):                                                      *
 *          The cubic root of x at double precision.                          *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available and libtmpl algorithms have     *
 *      been requested. cbrt from math.h otherwise.                           *
 *  Method:                                                                   *
 *      Use a combination of cubic root rules, Taylor series, and Newton's    *
 *      method. That is, cbrt(x) is computed as follows:                      *
 *                                                                            *
 *          If x = +/- NaN, +Inf, or +/- 0, return x.                         *
 *          If x is subnormal (denormal), normalize by 2^52.                  *
 *          If x < 0, return -cbrt(-x) since cbrt is an odd function.         *
 *                                                                            *
 *          cbrt(x) = cbrt(1.m * 2^b)                                         *
 *                  = cbrt(1.m) * cbrt(2^b)                                   *
 *                  = cbrt(1.m) * 2^{b/3}                                     *
 *                  = cbrt(u) * 2^{b/3}     with u = 1.m                      *
 *                  = cbrt(ut/t) * 2^{b/3}  with t = 1 + k/128 for some k.    *
 *                  = cbrt(u/t) * cbrt(t) * 2^{b/3}                           *
 *                                                                            *
 *      Choose t = 1 + k/128 by choosing k to be the largest integer such     *
 *      that 1 + k/128 <= u. Precompute cbrt(t) and 1/t in a table. The       *
 *      value u/t is now between 1 and 1 + 1/128. Compute cbrt(u/t) by:       *
 *                                                                            *
 *                                                                            *
 *          y = cbrt(u/t)                                                     *
 *            = cbrt(1 + s)             with s = u/t - 1.                     *
 *            ~ 1 + (1/3)s - (1/9)s^2 + (5/81)s^3                             *
 *                                                                            *
 *      y is now accurate to at least 8 decimals. We can double this to at    *
 *      least 16 decimals using 1 iteration of Newton's method. We have:      *
 *                                                                            *
 *                y ~ cbrt(x)                                                 *
 *          y^3 - x ~ 0                                                       *
 *             f(y) = y^3 - x                                                 *
 *            f'(y) = 3y^2                                                    *
 *                                                                            *
 *      Apply Newton's method for 1 iteration:                                *
 *                                                                            *
 *              out = y - f(y)/f'(y)                                          *
 *                  = y - (y^{3} - x)/(3y^{2})                                *
 *                  = (3y^{3} - y^{3} + x)/(3y^{2})                           *
 *                  = (2y^{3} + x)/(3y^{2})                                   *
 *                  = 0.3333*(2y + x/y^2)                                     *
 *                                                                            *
 *      Lastly, since 2^{b/3} is not an integer for some values of b write    *
 *      b = 3k + r, with r = 0, 1, 2. Then 2^{b/3} is 2^{k}2^{r/3}. If r = 0  *
 *      we are done. If r = 1, multiply by cbrt(2). If r = 2, multiply by     *
 *      2^{2/3}. Precompute these two values and multiply if needed.          *
 *  Notes:                                                                    *
 *      This function compiles without error or warning on Debian 11          *
 *      GNU/Linux with clang, gcc, tcc, and pcc using -Wall, -Wextra,         *
 *      -Wpedantic, and other options. It passes clang with -Weverything if   *
 *      -Wno-float-equal is also called (otherwise it complains about         *
 *      comparison of doubles with 0.0). -std=c89, -std=c99, -std=c11, and    *
 *      -std=c18 flags have been passed as well, and no problems were found.  *
 *      If any error or warnings arise on your platform, please report this.  *
 *                                                                            *
 *  Accuracy and Performance:                                                 *
 *                                                                            *
 *      A time and accuracy test yields the following results versus glibc:   *
 *                                                                            *
 *          tmpl_Double_Cbrt vs. cbrt                                         *
 *          start:   -1.0000000000000000e+04                                  *
 *          end:     1.0000000000000000e+04                                   *
 *          samples: 2615628245                                               *
 *          dx:      7.6463465472326701e-06                                   *
 *          libtmpl: 18.104055 seconds                                        *
 *          C:       32.453732 seconds                                        *
 *          max abs error: 1.4210854715202004e-14                             *
 *          max rel error: 7.0469763017409916e-16                             *
 *          rms abs error: 2.6790772954468324e-15                             *
 *          rms rel error: 1.5775644974028550e-16                             *
 *                                                                            *
 *      Talk about speed! The rms relative error is also below DBL_EPSILON.   *
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
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  The values cbrt(1 + k/128) for k = 0, 1, ..., 126, 127.                   */
static double tmpl_cbrt_double_table[128] = {
    1.0000000000000000000000000000000, 1.0025974142646002445641810219251,
    1.0051814396472644940216361286079, 1.0077522473643225547531221593643,
    1.0103100051555475677004975186586, 1.0128548773804866675475088668966,
    1.0153870251114199472705153964498, 1.0179066062230899643192835511298,
    1.0204137754793370176414454033065, 1.0229086846167688117779793730487,
    1.0253914824255868804617962455355, 1.0278623148276862444158197280055,
    1.0303213249521392048443722793416, 1.0327686532081689053986600606709,
    1.0352044373557133125011297023314, 1.0376288125736755494301153185484,
    1.0400419115259520572650284121789, 1.0424438644253258305299813331824,
    1.0448347990953079730140940872272, 1.0472148410300070265876039863363,
    1.0495841134521019305383246481663, 1.0519427373689910594909927770260,
    1.0542908316271865535571371892576, 1.0566285129650200849034033336674,
    1.0589558960637232909745381060545, 1.0612730935969433373157816981626,
    1.0635802162787514440183421655311, 1.0658773729101997114903243952323,
    1.0681646704244792062469321323106, 1.0704422139307300088815492517690,
    1.0727101067565517779070785583636, 1.0749684504892613387200716047905,
    1.0772173450159418608796467832597, 1.0794568885623263338910985399200,
    1.0816871777305562867412287330851, 1.0839083075358550148472712375198,
    1.0861203714421529754305876365136, 1.0883234613967014844470426559062,
    1.0905176678637093911784948691690, 1.0927030798570360167223371961119,
    1.0948797849719723164299508828431, 1.0970478694161409605615204997782,
    1.0992074180395448189523026981346, 1.1013585143637921814080145318314,
    1.1035012406105259431129103596633, 1.1056356777290829309461032498228,
    1.1077619054234085398073632889972, 1.1098800021782508855365861940661,
    1.1119900452846577605826816883611, 1.1140921108647987981690823586204,
    1.1161862738961344083584921202686, 1.1182726082349522432889772842143,
    1.1203511866392911771868705035096, 1.1224220807912720479028475840938,
    1.1244853613188536990978901985768, 1.1265410978170321843407408496362,
    1.1285893588685003448612656756661, 1.1306302120637843502020093130867,
    1.1326637240208731942598194251101, 1.1346899604043565670129440911379,
    1.1367089859440859734504803853303, 1.1387208644533734447828035919396,
    1.1407256588467416818909839765751, 1.1427234311572389861994923911088,
    1.1447142425533318678080422119397, 1.1466981533553877739198725482300,
    1.1486752230517599515235741161056, 1.1506455103144860461334884503723,
    1.1526090730146116424186740244852, 1.1545659682371495720383124605517,
    1.1565162522956854482730905924478, 1.1584599807466395354515076137057,
    1.1603972084031947231025190877299, 1.1623279893489000496364014611865,
    1.1642523769509589076072526412113, 1.1661704238732107617127964804177,
    1.1680821820888149211350055787562, 1.1699877028926446291372689373998,
    1.1718870369133994645518358669049, 1.1737802341254437914779769778665,
    1.1756673438603787447500081699785, 1.1775484148183549991276512210927,
    1.1794234950791333393301323359957, 1.1812926321128998256183452161415,
    1.1831558727908421352812658600906, 1.1850132633954934537742500850417,
    1.1868648496308500900734435322338, 1.1887106766322687987520409685971,
    1.1905507889761496060637792294542, 1.1923852306894097586628826691946,
    1.1942140452587542412359333662832, 1.1960372756397481430196324621974,
    1.1978549642656959926900021618350, 1.1996671530563330262045908935440,
    1.2014738834263332026410145965253, 1.2032751962936386386935304736870,
    1.2050711320876149930641848338016, 1.2068617307570371973249159805438,
    1.2086470317779097997485535323917, 1.2104270741611260629344918698729,
    1.2122018964599698346209428535405, 1.2139715367774640937192187140860,
    1.2157360327735699601723683945382, 1.2174954216722398475830650255974,
    1.2192497402683283315324629316265, 1.2209990249343642039872395530485,
    1.2227433116271870850362574853643, 1.2244826358944518672866319590649,
    1.2262170328810041754619949364720, 1.2279465373351299339688209355567,
    1.2296711836146820483199013553121, 1.2313910056930871222219615234699,
    1.2331060371652350507458056615773, 1.2348163112532542512051178446185,
    1.2365218608121752170809009143826, 1.2382227183354850064529787321534,
    1.2399189159605752048520550759500, 1.2416104854740858331429509912674,
    1.2432974583171476039125208457138, 1.2449798655905248647881774585442,
    1.2466577380596615040817183752122, 1.2483311061596320330678687683278,
    1.2500000000000000000000000000000, 1.2516644493695858335718170483743,
    1.2533244837411461578909044387303, 1.2549801322759665670777461332602,
    1.2566314238283697952843517179059, 1.2582783869501411671842892252039
};

/*  The values 1/(1 + k/128) for k = 0, 1, ..., 126, 127.                     */
static double tmpl_cbrt_double_rcpr[128] = {
    1.00000000000000000000000000000000, 0.99224806201550387596899224806202,
    0.98461538461538461538461538461538, 0.97709923664122137404580152671756,
    0.96969696969696969696969696969697, 0.96240601503759398496240601503759,
    0.95522388059701492537313432835821, 0.94814814814814814814814814814815,
    0.94117647058823529411764705882353, 0.93430656934306569343065693430657,
    0.92753623188405797101449275362319, 0.92086330935251798561151079136691,
    0.91428571428571428571428571428571, 0.90780141843971631205673758865248,
    0.90140845070422535211267605633803, 0.89510489510489510489510489510490,
    0.88888888888888888888888888888889, 0.88275862068965517241379310344828,
    0.87671232876712328767123287671233, 0.87074829931972789115646258503401,
    0.86486486486486486486486486486486, 0.85906040268456375838926174496644,
    0.85333333333333333333333333333333, 0.84768211920529801324503311258278,
    0.84210526315789473684210526315789, 0.83660130718954248366013071895425,
    0.83116883116883116883116883116883, 0.82580645161290322580645161290323,
    0.82051282051282051282051282051282, 0.81528662420382165605095541401274,
    0.81012658227848101265822784810127, 0.80503144654088050314465408805031,
    0.80000000000000000000000000000000, 0.79503105590062111801242236024845,
    0.79012345679012345679012345679012, 0.78527607361963190184049079754601,
    0.78048780487804878048780487804878, 0.77575757575757575757575757575758,
    0.77108433734939759036144578313253, 0.76646706586826347305389221556886,
    0.76190476190476190476190476190476, 0.75739644970414201183431952662722,
    0.75294117647058823529411764705882, 0.74853801169590643274853801169591,
    0.74418604651162790697674418604651, 0.73988439306358381502890173410405,
    0.73563218390804597701149425287356, 0.73142857142857142857142857142857,
    0.72727272727272727272727272727273, 0.72316384180790960451977401129944,
    0.71910112359550561797752808988764, 0.71508379888268156424581005586592,
    0.71111111111111111111111111111111, 0.70718232044198895027624309392265,
    0.70329670329670329670329670329670, 0.69945355191256830601092896174863,
    0.69565217391304347826086956521739, 0.69189189189189189189189189189189,
    0.68817204301075268817204301075269, 0.68449197860962566844919786096257,
    0.68085106382978723404255319148936, 0.67724867724867724867724867724868,
    0.67368421052631578947368421052632, 0.67015706806282722513089005235602,
    0.66666666666666666666666666666667, 0.66321243523316062176165803108808,
    0.65979381443298969072164948453608, 0.65641025641025641025641025641026,
    0.65306122448979591836734693877551, 0.64974619289340101522842639593909,
    0.64646464646464646464646464646465, 0.64321608040201005025125628140704,
    0.64000000000000000000000000000000, 0.63681592039800995024875621890547,
    0.63366336633663366336633663366337, 0.63054187192118226600985221674877,
    0.62745098039215686274509803921569, 0.62439024390243902439024390243902,
    0.62135922330097087378640776699029, 0.61835748792270531400966183574879,
    0.61538461538461538461538461538462, 0.61244019138755980861244019138756,
    0.60952380952380952380952380952381, 0.60663507109004739336492890995261,
    0.60377358490566037735849056603774, 0.60093896713615023474178403755869,
    0.59813084112149532710280373831776, 0.59534883720930232558139534883721,
    0.59259259259259259259259259259259, 0.58986175115207373271889400921659,
    0.58715596330275229357798165137615, 0.58447488584474885844748858447489,
    0.58181818181818181818181818181818, 0.57918552036199095022624434389140,
    0.57657657657657657657657657657658, 0.57399103139013452914798206278027,
    0.57142857142857142857142857142857, 0.56888888888888888888888888888889,
    0.56637168141592920353982300884956, 0.56387665198237885462555066079295,
    0.56140350877192982456140350877193, 0.55895196506550218340611353711790,
    0.55652173913043478260869565217391, 0.55411255411255411255411255411255,
    0.55172413793103448275862068965517, 0.54935622317596566523605150214592,
    0.54700854700854700854700854700855, 0.54468085106382978723404255319149,
    0.54237288135593220338983050847458, 0.54008438818565400843881856540084,
    0.53781512605042016806722689075630, 0.53556485355648535564853556485356,
    0.53333333333333333333333333333333, 0.53112033195020746887966804979253,
    0.52892561983471074380165289256198, 0.52674897119341563786008230452675,
    0.52459016393442622950819672131148, 0.52244897959183673469387755102041,
    0.52032520325203252032520325203252, 0.51821862348178137651821862348178,
    0.51612903225806451612903225806452, 0.51405622489959839357429718875502,
    0.51200000000000000000000000000000, 0.50996015936254980079681274900398,
    0.50793650793650793650793650793651, 0.50592885375494071146245059288538,
    0.50393700787401574803149606299213, 0.50196078431372549019607843137255
};

#define A0 1.0
#define A1 0.333333333333333333333333333333
#define A2 -0.11111111111111111111111111111
#define A3 0.061728395061728395061728395061
#define CBRT_2 1.2599210498948731647672106072782
#define CBRT_2_SQ 1.5874010519681994747517056392722
#define ONE_THIRD 0.333333333333333333333333333333

/*  Function for computing square roots at double precision.                  */
double tmpl_Double_Cbrt(double x)
{
    /*  Union of a double and the bits representing a double.                 */
    tmpl_IEEE754_Double w;

    /*  Integer for indexing the arrays defined above.                        */
    unsigned int ind;

    /*  The exponent part of the input x.                                     */
    signed int exponent;

    /*  Variable for storing the exponent mod 3.                              */
    unsigned int parity;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  cbrt is an odd function. If x is negative, compute -cbrt(-x).         */
    w.bits.sign = 0x00U;

    /*  Subnormal number or zero.                                             */
    if (w.bits.expo == 0x00U)
    {
        /*  cbrt(0) = 0.0.                                                    */
        if (w.r == 0.0)
            return x;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^52,      *
         *  which is 4.503599627370496 x 10^15.                               */
        w.r *= 4.503599627370496E15;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS - 52;
    }

    /*  NaN or infinity. Return the input.                                    */
    else if (w.bits.expo == 0x7FFU)
        return x;

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_DOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    parity = w.bits.expo % 3U;
    w.bits.expo = TMPL_DOUBLE_BIAS;

    /*  We compute cbrt(x) via:                                               *
     *                                                                        *
     *      cbrt(x) = cbrt(1.m * 2^b)                                         *
     *              = cbrt(1.m) * cbrt(2^b)                                   *
     *              = cbrt(1.m) * 2^(b/3)                                     *
     *                                                                        *
     *  We then let u = 1.m and write u = u * t / t where t is the greatest   *
     *  value t = 1 + k/128 such that t <= u. Precompute cbrt(t) in a table   *
     *  and then have:                                                        *
     *                                                                        *
     *      cbrt(x) = cbrt(u) * 2^(b/3)                                       *
     *              = cbrt(ut/t) * 2^(b/3)                                    *
     *              = cbrt(u/t) * cbrt(t) * 2^(b/3)                           *
     *                                                                        *
     *  The value u/t is between 1 and 1 + 1/128. We compute cbrt(u/t) via a  *
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
    w.r = w.r*tmpl_cbrt_double_rcpr[ind] - 1.0;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    w.r = A0 + w.r*(A1 + w.r*(A2 + w.r*A3));

    /*  Get the correctly rounded down integer exponent/3.                    */
    exponent = (exponent < 0 ? (exponent - 2)/3 : exponent/3);
    w.bits.expo = (unsigned int)((signed int)w.bits.expo + exponent) & 0x7FFU;

    /*  If expo mod 3 = 0, expo/3 is an integer so 2^(expo/3) is fine.        */
    if (parity == 0U)
        w.r *= tmpl_cbrt_double_table[ind];

    /*  If expo mod 3 = 1, 2^(expo/3) = 2^(floor(expo/3) + 1/3). Multiply by  *
     *  the cubic root of 2.                                                  */
    else if (parity == 1U)
        w.r *= CBRT_2*tmpl_cbrt_double_table[ind];

    /*  Lastly, if expo mod 3 = 2, multiply by the 2^(2/3).                   */
    else
        w.r *= CBRT_2_SQ*tmpl_cbrt_double_table[ind];

    /*  Apply 1 iteration of Newton's method and return.                      */
    if (x < 0.0)
        return -ONE_THIRD*(2.0*w.r - x/(w.r*w.r));
    else
        return ONE_THIRD*(2.0*w.r + x/(w.r*w.r));
}
/*  End of tmpl_Double_Cbrt.                                                  */

#undef A0
#undef A1
#undef A2
#undef A3
#undef CBRT_2
#undef CBRT_2_SQ
#undef ONE_THIRD

#else
/*  Else for TMPL_HAS_IEEE754_DOUBLE.                                         */

#include <math.h>

/*  Function for computation square roots at double precision.                */
double tmpl_Double_Cbrt(double x)
{
    return cbrt(x);
}
/*  End of tmpl_Double_Cbrt.                                                  */

#endif
/*  End of #if for TMPL_HAS_IEEE754_DOUBLE.                                   */
