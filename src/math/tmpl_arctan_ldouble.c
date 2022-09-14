/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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

#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

/*  Check for IEEE-754 long double support.                                   */
#if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1

/******************************************************************************
 *                          64 BIT DOUBLE PRECISION                           *
 ******************************************************************************/

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN

/*  Coefficients for the computation of the polynomial approximation. The     *
 *  coefficients for the Taylor series are 1 / (1 + 2n).                      */
#define A00 3.33333333333329318027E-01L
#define A01 -1.99999999998764832476E-01L
#define A02 1.42857142725034663711E-01L
#define A03 -1.11111104054623557880E-01L
#define A04 9.09088713343650656196E-02L
#define A05 -7.69187620504482999495E-02L
#define A06 6.66107313738753120669E-02L
#define A07 -5.83357013379057348645E-02L

/*  This function computes arctan(x) via a MacLaurin series for small |x|.    */
static long double tmpl_ldouble_arctan_maclaurin_series(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double x_sq = x*x;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return x * (
        1.0L - x_sq * (
            A00 + x_sq * (
                A01 + x_sq * (
                    A02 + x_sq * (
                        A03 + x_sq * (
                            A04 + x_sq * (
                                A05 + x_sq * (
                                    A06 + x_sq * A07
                                )
                            )
                        )
                    )
                )
            )
        )
    );
}
/*  End of tmpl_ldouble_arctan_maclaurin_series.                              */

static long double tmpl_ldouble_arctan_small_vals(long double x)
{
    const long double x_sq = x*x;
    return  x * (
        1.0L - x_sq * (
            A00 + x_sq * (
                A01 + x_sq * (
                    A02 + x_sq * (
                        A03 + x_sq * (
                            A04 + x_sq * (
                                A05 + x_sq * A06
                            )
                        )
                    )
                )
            )
        )
    );
}

/*  This function computes arctan(x) via the asymptotic expansion.            */
static long double tmpl_ldouble_arctan_large_vals(long double x)
{
    /*  Declare necessary variables.                                          */
    const long double arg = -1.0L / x;
    const long double arg_sq = arg*arg;

    /*  Use Horner's method to compute the polynomial. The signs of the       *
     *  coefficients oscillate.                                               */
    return arg * (
        1.0L - arg_sq * (
            A00 + arg_sq * (
                A01 + arg_sq * (
                    A02 + arg_sq * (
                        A03 + arg_sq * A04
                    )
                )
            )
        )
    );
}
/*  End of tmpl_ldouble_arctan_large_vals.                                    */

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const long double tmpl_atan_ldouble_v[7] = {
    0.18L,
    0.35L,
    0.72L,
    1.35L,
    2.5L,
    4.0L,
    8.0L
};

static const long double tmpl_atan_ldouble_atan_of_v[7] = {
    0.178092938231197549667920L,
    0.336674819386727181396699L,
    0.624023052976756847589791L,
    0.933247528656203869893663L,
    1.19028994968253173292773L,
    1.32581766366803246505924L,
    1.44644133224813518419997L
};

/*  Double precision inverse tangent (atan equivalent).                       */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Small values, |x| < 1/8. Use the MacLaurin series to 8 terms.         */
    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 3U)
        return tmpl_ldouble_arctan_small_vals(x);

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L + tmpl_ldouble_arctan_large_vals(w.r);
        return (x < 0.0 ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_double_v and *
     *  tmpl_atan_double_atan_of_v that correspond to x. The index is simply  *
     *  the exponent plus three (since the lowest value is 1/8 = 2^-3, we     *
     *  need to shift up by 3). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 3U) - TMPL_LDOUBLE_BIAS;
    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0L + w.r*v);
    out = atan_v + tmpl_ldouble_arctan_maclaurin_series(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

/*  Undefine all of the macros.                                               */
#undef A00
#undef A01
#undef A02
#undef A03
#undef A04
#undef A05
#undef A06
#undef A07

/******************************************************************************
 *                         80 BIT EXTENDED PRECISION                          *
 ******************************************************************************/

/*  80-bit extended precision. Functions are accurate to a relative error of  *
 *  less than 2^-63 ~= 10^-19.                                                */
#elif \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_BIG_ENDIAN      || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_EXTENDED_LITTLE_ENDIAN  || \
  TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/*  The following functions compute atan(x) with relative error bounded by    *
 *  2^-63 ~= 10^-19. RMS error is ~0.3 ULP based on sampling between +/- 1E6. */

/*  Taylor series centered at x0 = 0 for atan(x).                             */
static long double tmpl_double_arctan_maclaurin_series(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x_sq = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    long double out = -0.0434782608695652173913043478260869565L*x_sq
                     + 0.047619047619047619047619047619047619L;
    out = out*x_sq - 0.0526315789473684210526315789473684211L;
    out = out*x_sq + 0.0588235294117647058823529411764705882L;
    out = out*x_sq - 0.0666666666666666666666666666666666667L;
    out = out*x_sq + 0.0769230769230769230769230769230769231L;
    out = out*x_sq - 0.0909090909090909090909090909090909091L;
    out = out*x_sq + 0.111111111111111111111111111111111111L;
    out = out*x_sq - 0.142857142857142857142857142857142857L;
    out = out*x_sq + 0.200000000000000000000000000000000000L;
    out = out*x_sq - 0.333333333333333333333333333333333333L;
    out = out*x_sq + 1.000000000000000000000000000000000000L;

    /*  The Taylor series is in terms of x^{2n+1}, not x^{2n}. Multiplying    *
     *  by the input gives us the correct result.                             */
    return x*out;
}
/*  End of tmpl_double_arctan_maclaurin_series.                               */

/*  Asymptotic expansion for atan(x). This works well for large values.       */
static long double tmpl_ldouble_arctan_large_vals(long double x)
{
    const long double arg = -1.0L/x;
    const long double arg_sq = arg*arg;

    long double out = 0.0769230769230769230769230769230769231L * arg_sq
                    - 0.0909090909090909090909090909090909091L;
    out = out * arg_sq + 0.111111111111111111111111111111111111L;
    out = out * arg_sq - 0.142857142857142857142857142857142857L;
    out = out * arg_sq + 0.200000000000000000000000000000000000L;
    out = out * arg_sq - 0.333333333333333333333333333333333333L;
    out = out * arg_sq + 1.000000000000000000000000000000000000L;
    return arg*out;
}
/*  End of tmpl_ldouble_arctan_large_vals.                                    */

/*  For very small values we need fewer terms to get with 1 ULP.              */
static long double tmpl_ldoule_arctan_small_vals(long double x)
{
    /*  The Taylor series for atan(x) is in terms of x^{2n+1}. Compute the    *
     *  square of x and use this for the series.                              */
    const long double x_sq = x*x;

    /*  Use Horner's method to efficiently evaluate the polynomial.           */
    long double out = -0.0666666666666666666666666666666666667L * x_sq
                    + 0.0769230769230769230769230769230769231L;
    out = out*x_sq - 0.0909090909090909090909090909090909091L;
    out = out*x_sq + 0.111111111111111111111111111111111111L;
    out = out*x_sq - 0.142857142857142857142857142857142857L;
    out = out*x_sq + 0.200000000000000000000000000000000000L;
    out = out*x_sq - 0.333333333333333333333333333333333333L;
    out = out*x_sq + 1.000000000000000000000000000000000000L;

    /*  The Taylor series is in terms of x^{2n+1}, not x^{2n}. Multiplying    *
     *  by the input gives us the correct result.                             */
    return x*out;
}
/*  End of tmpl_ldoule_arctan_small_vals.                                     */

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const long double tmpl_atan_ldouble_v[8] = {
    0.05L,
    0.18L,
    0.35L,
    0.72L,
    1.35L,
    2.5L,
    4.0L,
    8.0L
};

static const long double tmpl_atan_ldouble_atan_of_v[8] = {
    0.0499583957219427614100063L,
    0.178092938231197549667920L,
    0.336674819386727181396699L,
    0.624023052976756847589791L,
    0.933247528656203869893663L,
    1.19028994968253173292773L,
    1.32581766366803246505924L,
    1.44644133224813518419997L
};

/*  Long double precision inverse tangent (atan equivalent).                  */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    /*  Small values, |x| < 1/8. Use the MacLaurin series to 8 terms.         */
    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 4U)
        return tmpl_ldoule_arctan_small_vals(x);

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L + tmpl_ldouble_arctan_large_vals(w.r);
        return (x < 0.0L ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_ldouble_v    *
     *  and tmpl_atan_ldouble_atan_of_v that correspond to x. The index is    *
     *  the exponent plus three (since the lowest value is 1/8 = 2^-3, we     *
     *  need to shift up by 3). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_LDOUBLE_BIAS;
    v = tmpl_atan_ldouble_v[ind];
    atan_v = tmpl_atan_ldouble_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0L + w.r*v);
    out = atan_v + tmpl_double_arctan_maclaurin_series(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

/******************************************************************************
 *                        128 BIT QUADRUPLE PRECISION                         *
 ******************************************************************************/

#elif \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

/* arctan(k/8), k = 0, ..., 128 */
static const long double tmpl_ldouble_atan_n_by_8[129] = {
    0.0000000000000000000000000000000000000000E0L,
    1.2435499454676143503135484916387102557317E-1L,
    2.4497866312686415417208248121127581091414E-1L,
    3.5877067027057222039592006392646049977698E-1L,
    4.6364760900080611621425623146121440202854E-1L,
    5.5859931534356243597150821640166127034645E-1L,
    6.4350110879328438680280922871732263804151E-1L,
    7.1882999962162450541701415152590465395142E-1L,
    7.8539816339744830961566084581987572104929E-1L,
    8.4415398611317100251784414827164750652594E-1L,
    8.9605538457134395617480071802993782702458E-1L,
    9.4200004037946366473793717053459358607166E-1L,
    9.8279372324732906798571061101466601449688E-1L,
    1.0191413442663497346383429170230636487744E0L,
    1.0516502125483736674598673120862998296302E0L,
    1.0808390005411683108871567292171998202703E0L,
    1.1071487177940905030170654601785370400700E0L,
    1.1309537439791604464709335155363278047493E0L,
    1.1525719972156675180401498626127513797495E0L,
    1.1722738811284763866005949441337046149712E0L,
    1.1902899496825317329277337748293183376012E0L,
    1.2068173702852525303955115800565576303133E0L,
    1.2220253232109896370417417439225704908830E0L,
    1.2360594894780819419094519711090786987027E0L,
    1.2490457723982544258299170772810901230778E0L,
    1.2610933822524404193139408812473357720101E0L,
    1.2722973952087173412961937498224804940684E0L,
    1.2827408797442707473628852511364955306249E0L,
    1.2924966677897852679030914214070816845853E0L,
    1.3016288340091961438047858503666855921414E0L,
    1.3101939350475556342564376891719053122733E0L,
    1.3182420510168370498593302023271362531155E0L,
    1.3258176636680324650592392104284756311844E0L,
    1.3329603993374458675538498697331558093700E0L,
    1.3397056595989995393283037525895557411039E0L,
    1.3460851583802539310489409282517796256512E0L,
    1.3521273809209546571891479413898128509842E0L,
    1.3578579772154994751124898859640585287459E0L,
    1.3633001003596939542892985278250991189943E0L,
    1.3684746984165928776366381936948529556191E0L,
    1.3734007669450158608612719264449611486510E0L,
    1.3780955681325110444536609641291551522494E0L,
    1.3825748214901258580599674177685685125566E0L,
    1.3868528702577214543289381097042486034883E0L,
    1.3909428270024183486427686943836432060856E0L,
    1.3948567013423687823948122092044222644895E0L,
    1.3986055122719575950126700816114282335732E0L,
    1.4021993871854670105330304794336492676944E0L,
    1.4056476493802697809521934019958079881002E0L,
    1.4089588955564736949699075250792569287156E0L,
    1.4121410646084952153676136718584891599630E0L,
    1.4152014988178669079462550975833894394929E0L,
    1.4181469983996314594038603039700989523716E0L,
    1.4209838702219992566633046424614466661176E0L,
    1.4237179714064941189018190466107297503086E0L,
    1.4263547484202526397918060597281265695725E0L,
    1.4288992721907326964184700745371983590908E0L,
    1.4313562697035588982240194668401779312122E0L,
    1.4337301524847089866404719096698873648610E0L,
    1.4360250423171655234964275337155008780675E0L,
    1.4382447944982225979614042479354815855386E0L,
    1.4403930189057632173997301031392126865694E0L,
    1.4424730991091018200252920599377292525125E0L,
    1.4444882097316563655148453598508037025938E0L,
    1.4464413322481351841999668424758804165254E0L,
    1.4483352693775551917970437843145232637695E0L,
    1.4501726582147939000905940595923466567576E0L,
    1.4519559822271314199339700039142990228105E0L,
    1.4536875822280323362423034480994649820285E0L,
    1.4553696664279718992423082296859928222270E0L,
    1.4570043196511885530074841089245667532358E0L,
    1.4585935117976422128825857356750737658039E0L,
    1.4601391056210009726721818194296893361233E0L,
    1.4616428638860188872060496086383008594310E0L,
    1.4631064559620759326975975316301202111560E0L,
    1.4645314639038178118428450961503371619177E0L,
    1.4659193880646627234129855241049975398470E0L,
    1.4672716522843522691530527207287398276197E0L,
    1.4685896086876430842559640450619880951144E0L,
    1.4698745421276027686510391411132998919794E0L,
    1.4711276743037345918528755717617308518553E0L,
    1.4723501675822635384916444186631899205983E0L,
    1.4735431285433308455179928682541563973416E0L,
    1.4747076112775297156457696020843429121750E0L,
    1.4758446204521402994740697066993045737807E0L,
    1.4769551141655601073845643918489010491235E0L,
    1.4780400066067528742912956492679274173081E0L,
    1.4791001705350335920067055415092607945848E0L,
    1.4801364395941515057329350163312858240725E0L,
    1.4811496104734101005230254685700755826154E0L,
    1.4821404449274591535866502155505515382824E0L,
    1.4831096716653961446653884363217722221355E0L,
    1.4840579881189115074204117986550232546263E0L,
    1.4849860620983944584330588319254642223696E0L,
    1.4858945333451746684000206793240900744035E0L,
    1.4867840149874020396578063976185774328938E0L,
    1.4876550949064553893206533769889701445675E0L,
    1.4885083370202147351605477895533266305580E0L,
    1.4893442824890256416375381678846838656578E0L,
    1.4901634508497227996178425022670335106973E0L,
    1.4909663410826593033383675000724190851828E0L,
    1.4917534326163040343047464110667474168911E0L,
    1.4925251862736186574372737258621480949375E0L,
    1.4932820451641048379521906024777377613925E0L,
    1.4940244355251185800019995584923659339920E0L,
    1.4947527675157795396087307557692440871168E0L,
    1.4954674359665565006171167688311694261887E0L,
    1.4961688210873838771202975793537579544411E0L,
    1.4968572891369562763722351552743516865583E0L,
    1.4975331930556571615295846136533458351021E0L,
    1.4981968730644019949034322665438486358775E0L,
    1.4988486572315145661857645980708538360309E0L,
    1.4994888620096062927989507017866583810753E0L,
    1.5001177927442910140857596690590647397203E0L,
    1.5007357441564411850523945880885632115724E0L,
    1.5013430007995745002297298103299323309651E0L,
    1.5019398374938520197571649905681176269652E0L,
    1.5025265197380690797791405520832913365105E0L,
    1.5031033041009279678124130530803583941493E0L,
    1.5036704385927959126560829413161988499911E0L,
    1.5042281630190728150326749973457803750007E0L,
    1.5047767093162198170166093290594653407112E0L,
    1.5053163018714318083306395218738285783435E0L,
    1.5058471578268738696935788811632539967881E0L,
    1.5063694873693430686317821563374018259572E0L,
    1.5068834940061625962000055895618863582185E0L,
    1.5073893748280646390591656283411759619585E0L,
    1.5078873207597713231536332351575422706711E0L,
    1.5083775167989392707573425786542463284923E0L
};


/* arctan t = t + t^3 p(t^2) / q(t^2)
   |t| <= 0.09375
   peak relative error 5.3e-37 */

static const long double tmpl_ldouble_arctan_numer_coeffs[5] = {
    -4.283708356338736809269381409828726405572E1L,
    -8.636132499244548540964557273544599863825E1L,
    -5.713554848244551350855604111031839613216E1L,
    -1.371405711877433266573835355036413750118E1L,
    -8.638214309119210906997318946650189640184E-1L
};

static const long double tmpl_ldouble_arctan_denom_coeffs[5] = {
    1.285112506901621042780814422948906537959E2L,
    3.361907253914337187957855834229672347089E2L,
    3.180448303864130128268191635189365331680E2L,
    1.307244136980865800160844625025280344686E2L,
    2.173623741810414221251136181221172551416E1L
};

static long double tmpl_ldouble_arctan_rational_approx(long double x)
{
    long double numer, denom;
    const long double x_sq = x*x;

    numer = tmpl_ldouble_arctan_numer_coeffs[4];
    numer = numer*x_sq + tmpl_ldouble_arctan_numer_coeffs[3];
    numer = numer*x_sq + tmpl_ldouble_arctan_numer_coeffs[2];
    numer = numer*x_sq + tmpl_ldouble_arctan_numer_coeffs[1];
    numer = numer*x_sq + tmpl_ldouble_arctan_numer_coeffs[0];
    numer = numer*x_sq;

    denom = x_sq + tmpl_ldouble_arctan_denom_coeffs[4];
    denom = denom*x_sq + tmpl_ldouble_arctan_denom_coeffs[3];
    denom = denom*x_sq + tmpl_ldouble_arctan_denom_coeffs[2];
    denom = denom*x_sq + tmpl_ldouble_arctan_denom_coeffs[1];
    denom = denom*x_sq + tmpl_ldouble_arctan_denom_coeffs[0];
    return x * (1.0L + numer/denom);
}

#include <stdlib.h>

/*  Long double precision inverse tangent (atanl equivalent).                 */
long double tmpl_LDouble_Arctan(long double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_LDouble w;
    long double out, t;
    unsigned int n;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_LDOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two_L;
        else
            return tmpl_Pi_By_Two_L;
    }

    else if (w.bits.expo < TMPL_LDOUBLE_BIAS - 52U)
        return x;

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_LDOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L + tmpl_ldouble_arctan_rational_approx(-1.0L/w.r);
        return (x < 0.0L ? -out : out);
    }

    n = (unsigned int)(8.0L*w.r + 0.25L);
    t = 0.125L * (long double)n;
    t = (w.r - t) / (1.0 + w.r*t);
    out = tmpl_ldouble_atan_n_by_8[n] + tmpl_ldouble_arctan_rational_approx(t);
    return (x < 0.0L ? -out : out);
}
/*  End of tmpl_LDouble_Arctan.                                               */

#else

/*  Double-double not implemented yet.                                        */

#endif
/*  #if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_96_BIT_EXTENDED_LITTLE_ENDIAN */

#else
/*  #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1.   */

/*  Portable algorithm that does not use IEEE-754 tricks.                     */

static long double tmpl_arctan_small_vals(long double x)
{
    const long double x_sq = x*x;
    long double out = 0.030303030303030303030303030303030303L * x_sq
                    - 0.0322580645161290322580645161290322581L;
    out = out*x_sq + 0.0344827586206896551724137931034482759L;
    out = out*x_sq - 0.037037037037037037037037037037037037L;
    out = out*x_sq + 0.0400000000000000000000000000000000000L;
    out = out*x_sq - 0.0434782608695652173913043478260869565L;
    out = out*x_sq + 0.047619047619047619047619047619047619L;
    out = out*x_sq - 0.0526315789473684210526315789473684211L;
    out = out*x_sq + 0.0588235294117647058823529411764705882L;
    out = out*x_sq - 0.0666666666666666666666666666666666667L;
    out = out*x_sq + 0.0769230769230769230769230769230769231L;
    out = out*x_sq - 0.0909090909090909090909090909090909091L;
    out = out*x_sq + 0.111111111111111111111111111111111111L;
    out = out*x_sq - 0.142857142857142857142857142857142857L;
    out = out*x_sq + 0.200000000000000000000000000000000000L;
    out = out*x_sq - 0.333333333333333333333333333333333333L;
    out = out*x_sq + 1.000000000000000000000000000000000000L;

    /*  The Taylor series is in terms of x^{2n+1}, not x^{2n}. Multiplying    *
     *  by the input gives us the correct result.                             */
    return x*out;
}
/*  End of tmpl_double_arctan_maclaurin_series.                               */

#define ATAN_OF_ONE_HALF    0.46364760900080611621425623146121440202853705L
#define ATAN_OF_ONE         0.78539816339744830961566084581987572104929234L
#define ATAN_OF_THREE_HALFS 0.98279372324732906798571061101466601449687745L

long double tmpl_LDouble_Arctan(long double x)
{
    long double arg, sgn_x;

    if (x < 0.0L)
    {
        sgn_x = -1.0L;
        arg = -x;
    }
    else
    {
        sgn_x = 1.0L;
        arg = x;
    }

    if (arg < 0.25L)
        return sgn_x * tmpl_arctan_small_vals(arg);

    else if (arg < 0.6875L)
    {
        arg = (2.0L * arg - 1.0L) / (2.0L + arg);
        return sgn_x * (ATAN_OF_ONE_HALF + tmpl_arctan_small_vals(arg));
    }
    else if (arg < 1.1875L)
    {
        arg = (arg - 1.0L) / (arg + 1.0L);
        return sgn_x * (ATAN_OF_ONE + tmpl_arctan_small_vals(arg));
    }
    else if (arg < 3.1L)
    {
        arg = (2.0L * arg - 3.0L) / (2.0L + 3.0L * arg);
        return sgn_x * (ATAN_OF_THREE_HALFS + tmpl_arctan_small_vals(arg));
    }
    else
    {
        arg = -1.0L / arg;
        return sgn_x * (tmpl_Pi_By_Two_L + tmpl_arctan_small_vals(arg));
    }
}

#undef ATAN_OF_ONE_HALF
#undef ATAN_OF_ONE
#undef ATAN_OF_THREE_HALFS

#endif
/*  #if defined(TMPL_HAS_IEEE754_LDOUBLE) && TMPL_HAS_IEEE754_LDOUBLE == 1.   */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1.   */
