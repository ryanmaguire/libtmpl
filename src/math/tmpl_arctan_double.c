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
 ******************************************************************************
 *                             tmpl_arctan_double                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Computes the arc-tangent function at double precision.                *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_Double_Arctan                                                    *
 *  Purpose:                                                                  *
 *      Computes atan(x), the inverse tangent function.                       *
 *  Arguments:                                                                *
 *      x (double):                                                           *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      atan_x (double):                                                      *
 *          The arc-tangent of x.                                             *
 *  Called Functions:                                                         *
 *      None if IEEE-754 support is available.                                *
 *      If not, the following are called.                                     *
 *          tmpl_Double_Is_NaN (tmpl_math.h)                                  *
 *              Determines if a double is NaN.                                *
 *          tmpl_Double_Is_Inf (tmpl_math.h)                                  *
 *              Determines if a double is infinity.                           *
 *  Method:                                                                   *
 *      Check if the input is is NaN or infinity. Return NaN if it is         *
 *      NaN, and sign(x) * pi / 2 if it is +/- infinity.                      *
 *                                                                            *
 *      Next, use the fact that atan(x) is odd to reduce to the case          *
 *      x >= 0. For small values, use the MacLaurin series. For values in     *
 *      certain ranges, use formula 4.4.34 from Abramowitz and Stegun to      *
 *      reduce the argument to a smaller value. This formula states that:     *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) - atan(v) = atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *      With the portable method, use the following:                          *
 *          x in [0.0,    0.4375)  polynomial.                                *
 *          x in [0.4375, 0.6875)  u = x, v = 1/2, reduce and use polynomial. *
 *          x in [0.6875, 1.1875)  u = x, v = 1, reduce and use polynomial.   *
 *          x in [1.1875, 2.4375)  u = x, v = 3/2, reduce and use polynomial. *
 *          x in [2.4375, inf)     atan(x) = pi/2 + atan(-1/x).               *
 *                                                                            *
 *      x > 2.4375 uses the asymptotic expansion, a polynomial in 1/x. This   *
 *      converges very quickly to pi/2 as x gets larger.                      *
 *                                                                            *
 *      The IEEE-754 method can get a big speed boost. Extract the exponent   *
 *      of the input x. That is, given:                                       *
 *                                                                            *
 *          x = s * 1.m * 2^e                                                 *
 *                                                                            *
 *      where s is the sign, m the mantissa, and e the exponent, extract the  *
 *      value e. Precompute 7 values of atan(v) and use the value e to index  *
 *      this list (e varies from -3 to 3, corresponding to 0.125 to 8. For    *
 *      e < -3 we have |x| < 0.125, so use the MacLaurin series. For e > 3 we *
 *      have |x| > 8, so use the asymptotic expansion). Values of |x| lying   *
 *      between 2^e and 2^{e+1} will use these precomputed values in the      *
 *      formula above from Abramowitz and Stegun. Because of this we can skip *
 *      most of the if-then statements used in the portable method.           *
 *                                                                            *
 *      The following values were obtained via guess-and-check to reduce the  *
 *      relative error to below 2 * 10^-16 ~= 2^-52 = double epsilon.         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *          x in [0.0, 1/8) u = x, v = 0.18, reduce and use polynomial.       *
 *          x in [1/8, 1/4) u = x, v = 0.35, reduce and use polynomial.       *
 *          x in [1/4, 1/2) u = x, v = 0.72, reduce and use polynomial.       *
 *          x in [1/2, 1)   u = x, v = 1.35, reduce and use polynomial.       *
 *          x in [1, 2)     u = x, v = 2.50, reduce and use polynomial.       *
 *          x in [2, 4)     u = x, v = 4.00, reduce and use polynomial.       *
 *          x in [4, 8)     u = x, v = 8.00, reduce and use polynomial.       *
 *          x >= 8          atan(x) = pi/2 + atan(-1/x).                      *
 *                                                                            *
 *      Very small values need the first 8 terms of the MacLaurin series.     *
 *      Very large values need 6 terms of the asymptotic expansion. All other *
 *      intervals need the first 9 terms.                                     *
 *                                                                            *
 *  Notes:                                                                    *
 *      There are three special cases. If the input is NaN, the output will   *
 *      also be NaN. If the input is positive infinity, the limit is used and *
 *      pi/2 is returned. If the input is negative infinity, the limit is     *
 *      used and -pi/2 is returned.                                           *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file where the function prototype is given.                *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       September 09, 2021                                            *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/09/12: Ryan Maguire                                                  *
 *      Added IEEE-754 version. This yields a 2.3x speed boost.               *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>

/*  Only implement this if the user requested libtmpl algorithms.             */
#if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1

#include <libtmpl/include/tmpl_math_arctan_tables.h>

/*  Check for IEEE-754 support.                                               */
#if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1

/*  Double precision inverse tangent (atan equivalent).                       */
double tmpl_Double_Arctan(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double arg, out, v, atan_v;
    unsigned int ind;

    /*  Set the double part of the word to the input.                         */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  Small values, |x| < 1/16. Use the MacLaurin series to 6 terms.        */
    else if (w.bits.expo < TMPL_DOUBLE_BIAS - 4U)
    {
        const double x_sq = x*x;
        return x * (
            1.0 + x_sq * (
                -3.33333333333329318027E-01 + x_sq * (
                    1.99999999998764832476E-01 + x_sq * (
                        -1.42857142725034663711E-01 + x_sq * (
                            1.11111104054623557880E-01 + x_sq *
                                -9.09088713343650656196E-02
                        )
                    )
                )
            )
        );
    }

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 8, use the asymptotic expansion.                            */
    if (w.bits.expo > TMPL_DOUBLE_BIAS + 3U)
    {
        out = tmpl_Double_Arctan_Asymptotic(w.r);
        return (x < 0.0 ? -out : out);
    }

    /*  The exponent tells us the index for the tables tmpl_atan_double_v and *
     *  tmpl_atan_double_atan_of_v that correspond to x. The index is simply  *
     *  the exponent plus four (since the lowest value is 1/16 = 2^-4, we     *
     *  need to shift up by 4). The exponent has a bias, per the IEEE-754     *
     *  format, so we must subtract this off to get the correct index.        */
    ind = (w.bits.expo + 4U) - TMPL_DOUBLE_BIAS;
    v = tmpl_atan_double_v[ind];
    atan_v = tmpl_atan_double_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (w.r - v) / (1.0 + w.r*v);
    out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0 ? -out : out);
}
/*  End of tmpl_Double_Arctan.                                                */

#else
/*  #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1.     *
 *  Portable version of arctan function.                                      */

/*  Double precision inverse tangent (atan equivalent).                       */
double tmpl_Double_Arctan(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    double abs_x, arg, out, v, atan_v;
    unsigned int ind;

    /*  Special cases, NaN and INF.                                           */
    if (tmpl_Double_Is_NaN(x))
        return x;
    else if (tmpl_Double_Is_Inf(x))
        return (x < 0.0 ? -tmpl_Pi_By_Two : tmpl_Pi_By_Two);

    abs_x = tmpl_Double_Abs(x);

    /*  Small values, |x| < 1/16. Use the MacLaurin series to 6 terms.        */
    if (abs_x < 0.0625)
    {
        const double x_sq = x*x;
        return x * (
            1.0 + x_sq * (
                -3.33333333333329318027E-01 + x_sq * (
                    1.99999999998764832476E-01 + x_sq * (
                        -1.42857142725034663711E-01 + x_sq * (
                            1.11111104054623557880E-01 + x_sq *
                                -9.09088713343650656196E-02
                        )
                    )
                )
            )
        );
    }
    else if (abs_x < 0.125)
        ind = 0U;
    else if (abs_x < 0.25)
        ind = 1U;
    else if (abs_x < 0.5)
        ind = 2U;
    else if (abs_x < 1.0)
        ind = 3U;
    else if (abs_x < 2.0)
        ind = 4U;
    else if (abs_x < 4.0)
        ind = 5U;
    else if (abs_x < 8.0)
        ind = 6U;
    else if (abs_x < 16.0)
        ind = 7U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    else
    {
        out = tmpl_Double_Arctan_Asymptotic(abs_x);
        return (x < 0.0 ? -out : out);
    }

    v = tmpl_atan_double_v[ind];
    atan_v = tmpl_atan_double_atan_of_v[ind];

    /*  Compute the argument via formula 4.4.34 from Abramowitz and Stegun.   */
    arg = (abs_x - v) / (1.0 + abs_x*v);
    out = atan_v + tmpl_Double_Arctan_Maclaurin(arg);

    /*  Use the fact that atan is an odd function to complete the computation.*/
    return (x < 0.0 ? -out : out);
}
/*  End of tmpl_Double_Arctan.                                                */

#endif
/*  End #if defined(TMPL_HAS_IEEE754_DOUBLE) && TMPL_HAS_IEEE754_DOUBLE == 1. */

#endif
/*  #if defined(TMPL_USE_MATH_ALGORITHMS) && TMPL_USE_MATH_ALGORITHMS == 1.   */

/*  Pade approximant method of order (7, 7). Slower and requires many more    *
 *  values in the lookup table, so not used. Saved here for later study.      */
#if 0

static const double tmpl_double_atan_n_by_8[129] = {
    0.0000000000000000000000000000000000000000E0,
    1.2435499454676143503135484916387102557317E-1,
    2.4497866312686415417208248121127581091414E-1,
    3.5877067027057222039592006392646049977698E-1,
    4.6364760900080611621425623146121440202854E-1,
    5.5859931534356243597150821640166127034645E-1,
    6.4350110879328438680280922871732263804151E-1,
    7.1882999962162450541701415152590465395142E-1,
    7.8539816339744830961566084581987572104929E-1,
    8.4415398611317100251784414827164750652594E-1,
    8.9605538457134395617480071802993782702458E-1,
    9.4200004037946366473793717053459358607166E-1,
    9.8279372324732906798571061101466601449688E-1,
    1.0191413442663497346383429170230636487744E0,
    1.0516502125483736674598673120862998296302E0,
    1.0808390005411683108871567292171998202703E0,
    1.1071487177940905030170654601785370400700E0,
    1.1309537439791604464709335155363278047493E0,
    1.1525719972156675180401498626127513797495E0,
    1.1722738811284763866005949441337046149712E0,
    1.1902899496825317329277337748293183376012E0,
    1.2068173702852525303955115800565576303133E0,
    1.2220253232109896370417417439225704908830E0,
    1.2360594894780819419094519711090786987027E0,
    1.2490457723982544258299170772810901230778E0,
    1.2610933822524404193139408812473357720101E0,
    1.2722973952087173412961937498224804940684E0,
    1.2827408797442707473628852511364955306249E0,
    1.2924966677897852679030914214070816845853E0,
    1.3016288340091961438047858503666855921414E0,
    1.3101939350475556342564376891719053122733E0,
    1.3182420510168370498593302023271362531155E0,
    1.3258176636680324650592392104284756311844E0,
    1.3329603993374458675538498697331558093700E0,
    1.3397056595989995393283037525895557411039E0,
    1.3460851583802539310489409282517796256512E0,
    1.3521273809209546571891479413898128509842E0,
    1.3578579772154994751124898859640585287459E0,
    1.3633001003596939542892985278250991189943E0,
    1.3684746984165928776366381936948529556191E0,
    1.3734007669450158608612719264449611486510E0,
    1.3780955681325110444536609641291551522494E0,
    1.3825748214901258580599674177685685125566E0,
    1.3868528702577214543289381097042486034883E0,
    1.3909428270024183486427686943836432060856E0,
    1.3948567013423687823948122092044222644895E0,
    1.3986055122719575950126700816114282335732E0,
    1.4021993871854670105330304794336492676944E0,
    1.4056476493802697809521934019958079881002E0,
    1.4089588955564736949699075250792569287156E0,
    1.4121410646084952153676136718584891599630E0,
    1.4152014988178669079462550975833894394929E0,
    1.4181469983996314594038603039700989523716E0,
    1.4209838702219992566633046424614466661176E0,
    1.4237179714064941189018190466107297503086E0,
    1.4263547484202526397918060597281265695725E0,
    1.4288992721907326964184700745371983590908E0,
    1.4313562697035588982240194668401779312122E0,
    1.4337301524847089866404719096698873648610E0,
    1.4360250423171655234964275337155008780675E0,
    1.4382447944982225979614042479354815855386E0,
    1.4403930189057632173997301031392126865694E0,
    1.4424730991091018200252920599377292525125E0,
    1.4444882097316563655148453598508037025938E0,
    1.4464413322481351841999668424758804165254E0,
    1.4483352693775551917970437843145232637695E0,
    1.4501726582147939000905940595923466567576E0,
    1.4519559822271314199339700039142990228105E0,
    1.4536875822280323362423034480994649820285E0,
    1.4553696664279718992423082296859928222270E0,
    1.4570043196511885530074841089245667532358E0,
    1.4585935117976422128825857356750737658039E0,
    1.4601391056210009726721818194296893361233E0,
    1.4616428638860188872060496086383008594310E0,
    1.4631064559620759326975975316301202111560E0,
    1.4645314639038178118428450961503371619177E0,
    1.4659193880646627234129855241049975398470E0,
    1.4672716522843522691530527207287398276197E0,
    1.4685896086876430842559640450619880951144E0,
    1.4698745421276027686510391411132998919794E0,
    1.4711276743037345918528755717617308518553E0,
    1.4723501675822635384916444186631899205983E0,
    1.4735431285433308455179928682541563973416E0,
    1.4747076112775297156457696020843429121750E0,
    1.4758446204521402994740697066993045737807E0,
    1.4769551141655601073845643918489010491235E0,
    1.4780400066067528742912956492679274173081E0,
    1.4791001705350335920067055415092607945848E0,
    1.4801364395941515057329350163312858240725E0,
    1.4811496104734101005230254685700755826154E0,
    1.4821404449274591535866502155505515382824E0,
    1.4831096716653961446653884363217722221355E0,
    1.4840579881189115074204117986550232546263E0,
    1.4849860620983944584330588319254642223696E0,
    1.4858945333451746684000206793240900744035E0,
    1.4867840149874020396578063976185774328938E0,
    1.4876550949064553893206533769889701445675E0,
    1.4885083370202147351605477895533266305580E0,
    1.4893442824890256416375381678846838656578E0,
    1.4901634508497227996178425022670335106973E0,
    1.4909663410826593033383675000724190851828E0,
    1.4917534326163040343047464110667474168911E0,
    1.4925251862736186574372737258621480949375E0,
    1.4932820451641048379521906024777377613925E0,
    1.4940244355251185800019995584923659339920E0,
    1.4947527675157795396087307557692440871168E0,
    1.4954674359665565006171167688311694261887E0,
    1.4961688210873838771202975793537579544411E0,
    1.4968572891369562763722351552743516865583E0,
    1.4975331930556571615295846136533458351021E0,
    1.4981968730644019949034322665438486358775E0,
    1.4988486572315145661857645980708538360309E0,
    1.4994888620096062927989507017866583810753E0,
    1.5001177927442910140857596690590647397203E0,
    1.5007357441564411850523945880885632115724E0,
    1.5013430007995745002297298103299323309651E0,
    1.5019398374938520197571649905681176269652E0,
    1.5025265197380690797791405520832913365105E0,
    1.5031033041009279678124130530803583941493E0,
    1.5036704385927959126560829413161988499911E0,
    1.5042281630190728150326749973457803750007E0,
    1.5047767093162198170166093290594653407112E0,
    1.5053163018714318083306395218738285783435E0,
    1.5058471578268738696935788811632539967881E0,
    1.5063694873693430686317821563374018259572E0,
    1.5068834940061625962000055895618863582185E0,
    1.5073893748280646390591656283411759619585E0,
    1.5078873207597713231536332351575422706711E0,
    1.5083775167989392707573425786542463284923E0
};

#define P2 -6.453546453546453546453546453546453546454E-02
#define P1 -3.384615384615384615384615384615384615385E-01
#define P0 -3.333333333333333333333333333333333333333E-01

#define Q3 8.158508158508158508158508158508158508159E-02
#define Q2 7.342657342657342657342657342657342657343E-01
#define Q1 1.615384615384615384615384615384615384615E00
#define Q0 1.000000000000000000000000000000000000000E00

static double tmpl_double_arctan_rat(double x)
{
    const double x2 = x*x;
    const double p = x2*(P0 + x2*(P1 + x2*P2));
    const double q = Q0 + x2*(Q1 + x2*(Q2 + x2*Q3));
    return x*(1.0 + p/q);
}

double tmpl_Double_Arctan(double x)
{
    /*  Declare necessary variables. C89 requires this at the top.            */
    tmpl_IEEE754_Double w;
    double out, t;
    unsigned int n;

    /*  Set the long double part of the word to the input.                    */
    w.r = x;

    /*  Special cases, NaN and INF.                                           */
    if (w.bits.expo == TMPL_DOUBLE_NANINF_EXP)
    {
        /*  Check if the input is NaN. If it is, simply return the input.     */
        if ((w.bits.man0 != 0x0U || w.bits.man1 != 0x0U))
            return x;

        /*  For infinity the limit is pi/2. Negative infinity gives -pi/2.    */
        if (w.bits.sign)
            return -tmpl_Pi_By_Two;
        else
            return tmpl_Pi_By_Two;
    }

    /*  Avoid underflow. If |x| < 2^-52, atan(x) = x to quadruple precision.  */
    else if (w.bits.expo < TMPL_DOUBLE_BIAS - 52U)
        return x;

    /*  The arctan function is odd. Compute |x| by setting sign to positive.  */
    w.bits.sign = 0x00U;

    /*  For |x| > 16, use the asymptotic expansion.                           */
    if (w.bits.expo > TMPL_DOUBLE_BIAS + 3U)
    {
        out = tmpl_Pi_By_Two_L + tmpl_double_arctan_rat(-1.0/w.r);
        return (x < 0.0 ? -out : out);
    }

    n = (unsigned int)(8.0*w.r + 0.25);
    t = 0.125 * (double)n;
    t = (w.r - t) / (1.0 + w.r*t);
    out = tmpl_double_atan_n_by_8[n] + tmpl_double_arctan_rat(t);
    return (x < 0.0 ? -out : out);
}
#endif
