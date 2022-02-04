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
 *          For single precision, only the first term is needed. The          *
 *          standard Taylor series for ln(1 + x) with x small has             *
 *          poor convergences, roughly on the order of 1/N where N is the     *
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

/*  Table of the values log(1 + k/64) for k = 0, 1, ..., 62, 63.              */
static float table[64] = {
    0.0F,
    0.015504186535965254150854046042447F,
    0.030771658666753688371028207596772F,
    0.045809536031294203166679267614663F,
    0.060624621816434842580606132040420F,
    0.075223421237587525698605339983662F,
    0.089612158689687132619951469378485F,
    0.10379679368164356482606180376397F,
    0.11778303565638345453879410947052F,
    0.13157635778871927258871612868948F,
    0.14518200984449789728193506374056F,
    0.15860503017663858409337117462584F,
    0.17185025692665922234009894605515F,
    0.18492233849401199266390359265925F,
    0.19782574332991988036257207119696F,
    0.21056476910734963766955281273235F,
    0.22314355131420975576629509030983F,
    0.23556607131276690907758821894104F,
    0.24783616390458125678060276574652F,
    0.25995752443692606697207949454231F,
    0.27193371548364175883166949453300F,
    0.28376817313064459834690122235025F,
    0.29546421289383587638668190605496F,
    0.30702503529491186207512454053538F,
    0.31845373111853461581024721359060F,
    0.32975328637246798181442281192079F,
    0.34092658697059321030508919978036F,
    0.35197642315717818465544745625944F,
    0.36290549368936845313782434597749F,
    0.37371640979358408082101683271582F,
    0.38441169891033203973479006248129F,
    0.39499380824086897810639403636498F,
    0.40546510810816438197801311546435F,
    0.41582789514371096561332889295490F,
    0.42608439531090006312454487959548F,
    0.43623676677491807034904132306112F,
    0.44628710262841951153259018061967F,
    0.45623743348158759438080553816393F,
    0.46608972992459922455861924750477F,
    0.47584590486996391426520958630438F,
    0.48550781578170080780179107719079F,
    0.49507726679785151459796458484283F,
    0.50455601075239528705830853173817F,
    0.51394575110223431680100608827422F,
    0.52324814376454783651680722493487F,
    0.53246479886947184387392372346014F,
    0.54159728243274437157654230390043F,
    0.55064711795266227925994817920491F,
    0.55961578793542268627088850052683F,
    0.56850473535266871207873876486696F,
    0.57731536503482360431811206151950F,
    0.58604904500357820890411943628732F,
    0.59470710774669278951434354652921F,
    0.60329085143808426234058518666131F,
    0.61180154110599290352988976642881F,
    0.62024040975185752885149463256725F,
    0.62860865942237413774430820577418F,
    0.63690746223706923162049442718120F,
    0.64513796137358470166522849613473F,
    0.65330127201274563875861588121087F,
    0.66139848224536500826023583870965F,
    0.66943065394262926729888527092950F,
    0.67739882359180614080968260999735F,
    0.68530400309891941654404807896723F
};

/*  The values 1 / (1 + k/64) = 64 / (64 + k) for k = 0, 1, ..., 63, 64.      */
static float rcpr[64] = {
    1.0000000000000000000000000000000F,
    0.98461538461538461538461538461538F,
    0.96969696969696969696969696969697F,
    0.95522388059701492537313432835821F,
    0.94117647058823529411764705882353F,
    0.92753623188405797101449275362319F,
    0.91428571428571428571428571428571F,
    0.90140845070422535211267605633803F,
    0.88888888888888888888888888888889F,
    0.87671232876712328767123287671233F,
    0.86486486486486486486486486486486F,
    0.85333333333333333333333333333333F,
    0.84210526315789473684210526315789F,
    0.83116883116883116883116883116883F,
    0.82051282051282051282051282051282F,
    0.81012658227848101265822784810127F,
    0.80000000000000000000000000000000F,
    0.79012345679012345679012345679012F,
    0.78048780487804878048780487804878F,
    0.77108433734939759036144578313253F,
    0.76190476190476190476190476190476F,
    0.75294117647058823529411764705882F,
    0.74418604651162790697674418604651F,
    0.73563218390804597701149425287356F,
    0.72727272727272727272727272727273F,
    0.71910112359550561797752808988764F,
    0.71111111111111111111111111111111F,
    0.70329670329670329670329670329670F,
    0.69565217391304347826086956521739F,
    0.68817204301075268817204301075269F,
    0.68085106382978723404255319148936F,
    0.67368421052631578947368421052632F,
    0.66666666666666666666666666666667F,
    0.65979381443298969072164948453608F,
    0.65306122448979591836734693877551F,
    0.64646464646464646464646464646465F,
    0.64000000000000000000000000000000F,
    0.63366336633663366336633663366337F,
    0.62745098039215686274509803921569F,
    0.62135922330097087378640776699029F,
    0.61538461538461538461538461538462F,
    0.60952380952380952380952380952381F,
    0.60377358490566037735849056603774F,
    0.59813084112149532710280373831776F,
    0.59259259259259259259259259259259F,
    0.58715596330275229357798165137615F,
    0.58181818181818181818181818181818F,
    0.57657657657657657657657657657658F,
    0.57142857142857142857142857142857F,
    0.56637168141592920353982300884956F,
    0.56140350877192982456140350877193F,
    0.55652173913043478260869565217391F,
    0.55172413793103448275862068965517F,
    0.54700854700854700854700854700855F,
    0.54237288135593220338983050847458F,
    0.53781512605042016806722689075630F,
    0.53333333333333333333333333333333F,
    0.52892561983471074380165289256198F,
    0.52459016393442622950819672131148F,
    0.52032520325203252032520325203252F,
    0.51612903225806451612903225806452F,
    0.51200000000000000000000000000000F,
    0.50793650793650793650793650793651F,
    0.50393700787401574803149606299213F
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

    /*  Variable for the index of the arrays table and rcpr defined above     *
     *  which corresponds to the input x.                                     */
    unsigned int ind;

    /*  Variable for the union of a float and the bits representing it.       */
    tmpl_IEEE754_Float w;

    /*  Set the float part of the union to the input.                         */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NANF;

    /*  Subnormal normal or zero.                                             */
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
     *  the mantissa. The value 1 / (1 + k/64) is stored in the rcpr array.   *
     *  man0 is 7 bits wide, and we need the most significant 6. Bit shift    *
     *  by 1 to obtain this.                                                  */
    ind = w.bits.man0 >> 1U;

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
     *  With x close to 1, q is close to zero, and the sum is in terms of the *
     *  square of q. This has great convergence.                              */
    A = (s - 1.0F) / (s + 1.0F);

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_F*(float)exponent + 2.0F*A + table[ind];
}
/*  End of tmpl_Float_Log.                                                    */

/*  undef all the macros incase someone wants to #include this file.          */
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

