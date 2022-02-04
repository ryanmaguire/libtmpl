
/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

#include <float.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1 && \
    defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Table of the values log(1 + k/64) for k = 0, 1, ..., 62, 63.              */
static double table[64] = {
    0.0,
    0.015504186535965254150854046042447,
    0.030771658666753688371028207596772,
    0.045809536031294203166679267614663,
    0.060624621816434842580606132040420,
    0.075223421237587525698605339983662,
    0.089612158689687132619951469378485,
    0.10379679368164356482606180376397,
    0.11778303565638345453879410947052,
    0.13157635778871927258871612868948,
    0.14518200984449789728193506374056,
    0.15860503017663858409337117462584,
    0.17185025692665922234009894605515,
    0.18492233849401199266390359265925,
    0.19782574332991988036257207119696,
    0.21056476910734963766955281273235,
    0.22314355131420975576629509030983,
    0.23556607131276690907758821894104,
    0.24783616390458125678060276574652,
    0.25995752443692606697207949454231,
    0.27193371548364175883166949453300,
    0.28376817313064459834690122235025,
    0.29546421289383587638668190605496,
    0.30702503529491186207512454053538,
    0.31845373111853461581024721359060,
    0.32975328637246798181442281192079,
    0.34092658697059321030508919978036,
    0.35197642315717818465544745625944,
    0.36290549368936845313782434597749,
    0.37371640979358408082101683271582,
    0.38441169891033203973479006248129,
    0.39499380824086897810639403636498,
    0.40546510810816438197801311546435,
    0.41582789514371096561332889295490,
    0.42608439531090006312454487959548,
    0.43623676677491807034904132306112,
    0.44628710262841951153259018061967,
    0.45623743348158759438080553816393,
    0.46608972992459922455861924750477,
    0.47584590486996391426520958630438,
    0.48550781578170080780179107719079,
    0.49507726679785151459796458484283,
    0.50455601075239528705830853173817,
    0.51394575110223431680100608827422,
    0.52324814376454783651680722493487,
    0.53246479886947184387392372346014,
    0.54159728243274437157654230390043,
    0.55064711795266227925994817920491,
    0.55961578793542268627088850052683,
    0.56850473535266871207873876486696,
    0.57731536503482360431811206151950,
    0.58604904500357820890411943628732,
    0.59470710774669278951434354652921,
    0.60329085143808426234058518666131,
    0.61180154110599290352988976642881,
    0.62024040975185752885149463256725,
    0.62860865942237413774430820577418,
    0.63690746223706923162049442718120,
    0.64513796137358470166522849613473,
    0.65330127201274563875861588121087,
    0.66139848224536500826023583870965,
    0.66943065394262926729888527092950,
    0.67739882359180614080968260999735,
    0.68530400309891941654404807896723
};

/*  The values 1 / (1 + k/64) = 64 / (64 + k) for k = 0, 1, ..., 63, 64.      */
static double rcpr[64] = {
    1.0000000000000000000000000000000,
    0.98461538461538461538461538461538,
    0.96969696969696969696969696969697,
    0.95522388059701492537313432835821,
    0.94117647058823529411764705882353,
    0.92753623188405797101449275362319,
    0.91428571428571428571428571428571,
    0.90140845070422535211267605633803,
    0.88888888888888888888888888888889,
    0.87671232876712328767123287671233,
    0.86486486486486486486486486486486,
    0.85333333333333333333333333333333,
    0.84210526315789473684210526315789,
    0.83116883116883116883116883116883,
    0.82051282051282051282051282051282,
    0.81012658227848101265822784810127,
    0.80000000000000000000000000000000,
    0.79012345679012345679012345679012,
    0.78048780487804878048780487804878,
    0.77108433734939759036144578313253,
    0.76190476190476190476190476190476,
    0.75294117647058823529411764705882,
    0.74418604651162790697674418604651,
    0.73563218390804597701149425287356,
    0.72727272727272727272727272727273,
    0.71910112359550561797752808988764,
    0.71111111111111111111111111111111,
    0.70329670329670329670329670329670,
    0.69565217391304347826086956521739,
    0.68817204301075268817204301075269,
    0.68085106382978723404255319148936,
    0.67368421052631578947368421052632,
    0.66666666666666666666666666666667,
    0.65979381443298969072164948453608,
    0.65306122448979591836734693877551,
    0.64646464646464646464646464646465,
    0.64000000000000000000000000000000,
    0.63366336633663366336633663366337,
    0.62745098039215686274509803921569,
    0.62135922330097087378640776699029,
    0.61538461538461538461538461538462,
    0.60952380952380952380952380952381,
    0.60377358490566037735849056603774,
    0.59813084112149532710280373831776,
    0.59259259259259259259259259259259,
    0.58715596330275229357798165137615,
    0.58181818181818181818181818181818,
    0.57657657657657657657657657657658,
    0.57142857142857142857142857142857,
    0.56637168141592920353982300884956,
    0.56140350877192982456140350877193,
    0.55652173913043478260869565217391,
    0.55172413793103448275862068965517,
    0.54700854700854700854700854700855,
    0.54237288135593220338983050847458,
    0.53781512605042016806722689075630,
    0.53333333333333333333333333333333,
    0.52892561983471074380165289256198,
    0.52459016393442622950819672131148,
    0.52032520325203252032520325203252,
    0.51612903225806451612903225806452,
    0.51200000000000000000000000000000,
    0.50793650793650793650793650793651,
    0.50393700787401574803149606299213
};

#define ONE_HALF 0.5
#define ONE_THIRD 0.3333333333333333333333333333
#define ONE_FOURTH 0.25
#define ONE_FIFTH 0.20
#define ONE_SIXTH 0.166666666666666666666666667
#define ONE_SEVENTH 0.14285714285714285714285714285714

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

    /*  Subnormal normal or zero.                                             */
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

    /*  NaN of infinity. Simply return the input.                             */
    else if (w.bits.expo == 0xFFU)
        return x;

    /*  For values close to but less than 1, the computation of the division  *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-16 absolute error since log(1) = 0). To      *
     *  avoid this, use the basic Taylor series for log(1+s), s = 1-x, and    *
     *  return this. Since 1-x is very small, only a few terms are needed.    */
    else if (0.995 < w.r && w.r < 1.0)
    {
        s = 1.0 - x;
        return -s*(
            1.0 + s*(
                ONE_HALF + s*(
                    ONE_THIRD + s *(
                        ONE_FOURTH + s * (
                            ONE_FIFTH + s * (
                                ONE_SIXTH + ONE_SEVENTH*s
                            )
                        )
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
     *  the first two bits from man1. Obtain these with w.bits.man1 & 0xC000U *
     *  and then shift this value down by 2^14 via >> 14. We also need to     *
     *  shift the value of man0 up by 4, which is obtained by << 2.           *
     *  Altogether, this gives us the number abcdef in binary, as above,      *
     *  a is the first bit, b is the second, ..., f is the sixth.             */
    ind = (ind << 2U) + ((w.bits.man1 & 0xC000U) >> 14U);

    /*  Compute s = u/t via s = u * (1/t) using the array rcpr.               */
    s = w.r*rcpr[ind];

    /*  The Taylor series of log(1+x) for small x has very poor convergence.  *
     *  Using the alternating series test, the error is like 1/N where N is   *
     *  the number of terms in the series. To get 16 decimals would require a *
     *  sum of 10^16 terms! log(x) has a different expansion:                 *
     *                                                                        *
     *                inf                                                     *
     *                ----                                                    *
     *      log(x) =  \      2     2n+1                                       *
     *                /    ------ q             A = (x - 1) / (x + 1)         *
     *                ---- 2n + 1                                             *
     *                 n                                                      *
     *                                                                        *
     *  With x close to 1, q is close to zero, and the sum is in terms of the *
     *  square of q. This has great convergence.                              */
    A = (s - 1.0) / (s + 1.0);
    A_sq = A*A;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    poly = A*(2.0 + A_sq * (0.666666666666666667 + A_sq * 0.4));

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two*exponent + poly + table[ind];
}
/*  End of tmpl_Double_Log.                                                   */

#else

/*  The C Standard Library requires a log function. If these user lacks       *
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

/******************************************************************************
 *  This alternative algorithm uses an if-then statement to reduce the        *
 *  argument of x even further. It has slightly better peak relative error,   *
 *  but identical RMS relative error. It is significantly slower (about 1.6x) *
 *  and hence the other method is implemented. The algorithm is saved here    *
 *  just in case.                                                             *
 ******************************************************************************/

/*
double tmpl_Double_Log(double x)
{
    double mantissa, poly, A, A_sq;
    signed int exponent;
    tmpl_IEEE754_Double w;

    if (x < 0.0)
        return TMPL_NAN;
    else if (x == 0.0)
        return -TMPL_INFINITY;
    else if (tmpl_Double_Is_NaN_Or_Inf(x))
        return x + x;

    w.r = x;
    exponent = w.bits.expo - TMPL_DOUBLE_BIAS;
    w.bits.expo = TMPL_DOUBLE_BIAS;
    mantissa = w.r;

    if (mantissa > 1.5)
    {
        mantissa *= 0.5;
        exponent += 1;
    }

    A = (mantissa - 1.0) / (mantissa + 1.0);
    A_sq = A*A;

    poly = 0.095238095238095238 * A_sq + 0.10526315789473684;
    poly =                 poly * A_sq + 0.11764705882352941;
    poly =                 poly * A_sq + 0.13333333333333333;
    poly =                 poly * A_sq + 0.15384615384615385;
    poly =                 poly * A_sq + 0.18181818181818182;
    poly =                 poly * A_sq + 0.22222222222222222;
    poly =                 poly * A_sq + 0.28571428571428571;
    poly =                 poly * A_sq + 0.40000000000000000;
    poly =                 poly * A_sq + 0.66666666666666667;
    poly =                 poly * A_sq + 2.0000000000000000;

    return tmpl_Natural_Log_of_Two*exponent + A*poly;
}
*/

