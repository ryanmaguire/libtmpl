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
 *                            tmpl_log_ldouble                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Contains code for computing the natural log at long double precision. *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_LDouble_Log                                                      *
 *  Purpose:                                                                  *
 *      Computes log(x) = ln(x) = log_e(x), with e = 2.71828...               *
 *  Arguments:                                                                *
 *      x (long double):                                                      *
 *          A real number.                                                    *
 *  Output:                                                                   *
 *      log_x (double):                                                       *
 *          The natural log of x at long double precision.                    *
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
 *          t = 1 + k/128 <= u. This value k can be obtained directly from the*
 *          mantissa. By looking at the most significant 7 bits of the        *
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
 *          A polynomial with the first few terms is then used. The           *
 *          standard Taylor series polynomial for ln(1 + x) with x small has  *
 *          poor convergence, roughly on the order of 1/N where N is the      *
 *          number of terms. This alternative sum in is terms of the square   *
 *          of a small value, and has much better convergence.                *
 *                                                                            *
 *          For values slightly less than 1, the computation of (s-1) / (s+1) *
 *          leads to large relative error since log(1) = 1. We can achieve    *
 *          better relative error using the standard Taylor series to several *
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
 *                                                                            *
 *          For double-double implementations, we compute log(x) as follows.  *
 *                                                                            *
 *              log(x) = log(x_hi + x_low)                                    *
 *                     = log(x * x_hi / x_hi)                                 *
 *                     = log(x / x_hi) + log(x_hi)                            *
 *                     = log(1 - 1 + x/x_hi) + log(x_hi)                      *
 *                     = log(1 + (x - x_hi)/x_hi) + log(x_hi)                 *
 *                     = log(1 + x_low / x_hi) + log(x_hi)                    *
 *                                                                            *
 *          x_low / x_hi is small, so log (1 + x_low / x_hi) can be well      *
 *          approximated by the first few terms of the Taylor series for      *
 *          log(1 + t). log(x_hi) is computed in the same way as a normal     *
 *          long double (see above).                                          *
 *                                                                            *
 *      If the user has not requested libtmpl algorithms, or if IEEE-754      *
 *      support is not available (highly unlikely), then #include <math.h>    *
 *      is called and tmpl_Double_Log returns logl(x) from math.h             *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_math.h:                                                          *
 *          Header file containing tmpl_IEEE754_Double typedef and the        *
 *          function prototype.                                               *
 *  2.) math.h:                                                               *
 *          Only included if TMPL_HAS_IEEE754_LDOUBLE == 0 or if              *
 *          TMPL_USE_MATH_ALGORITHMS == 0. If either of these is true, then   *
 *          tmpl_LDouble_Log is identical to the logl function.               *
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
 *  Date:       February 12, 2022                                             *
 ******************************************************************************/

/*  Function prototype found here.                                            */
#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/math/tmpl_math_rcpr_table_ldouble.h>

/*  We can only implement this function if IEEE754 support is available. Also *
 *  only implement this if the user has requested libtmpl algorithms.         */
#if TMPL_HAS_IEEE754_LDOUBLE == 1 && TMPL_USE_MATH_ALGORITHMS == 1

static long double tmpl_ldouble_log_table[128] = {
    0.0L,
    0.00778214044205494894746290006113676368L,
    0.0155041865359652541508540460424468359L,
    0.0231670592815343782287991609622899166L,
    0.0307716586667536883710282075967721641L,
    0.0383188643021365991937553251237972903L,
    0.0458095360312942031666792676146633421L,
    0.0532445145188122828658701937865287769L,
    0.0606246218164348425806061320404202633L,
    0.0679506619085077493945652777726294140L,
    0.0752234212375875256986053399836624146L,
    0.0824436692110745912681600686683078059L,
    0.0896121586896871326199514693784845288L,
    0.0967296264585511122955710564874634370L,
    0.103796793681643564826061803763974688L,
    0.110814366340290114194806169323211928L,
    0.117783035656383454538794109470521705L,
    0.124703478500957235863406515380863268L,
    0.131576357788719272588716128689483162L,
    0.138402322859119135685325873601649187L,
    0.145182009844497897281935063740564324L,
    0.151916042025841975071803424896884511L,
    0.158605030176638584093371174625841575L,
    0.165249572895307162875611449277240314L,
    0.171850256926659222340098946055147265L,
    0.178407657472818297119400241510941968L,
    0.184922338494011992663903592659249621L,
    0.191394852999629454609298807561308873L,
    0.197825743329919880362572071196961469L,
    0.204215541428690891503820386196239272L,
    0.210564769107349637669552812732351514L,
    0.216873938300614359619089525744347498L,
    0.223143551314209755766295090309834503L,
    0.229374101064845829991480725046139872L,
    0.235566071312766909077588218941043410L,
    0.241719936887145168144307515913513900L,
    0.247836163904581256780602765746524748L,
    0.253915209980963444137323297906606667L,
    0.259957524436926066972079494542311045L,
    0.265963548497137941339125926537543389L,
    0.271933715483641758831669494532999162L,
    0.277868451003456306186350032923401233L,
    0.283768173130644598346901222350254767L,
    0.289633292583042676878893055525668970L,
    0.295464212893835876386681906054964195L,
    0.301261330578161781012875538233755493L,
    0.307025035294911862075124540535377902L,
    0.312755710003896888386246559688319032L,
    0.318453731118534615810247213590599596L,
    0.324119468654211976090670760434987352L,
    0.329753286372467981814422811920789811L,
    0.335355541921137830257179579814166199L,
    0.340926586970593210305089199780356208L,
    0.346466767346208580918462188425772951L,
    0.351976423157178184655447456259438926L,
    0.357455888921803774226009490140904474L,
    0.362905493689368453137824345977489846L,
    0.368325561158707653048230154050398827L,
    0.373716409793584080821016832715823507L,
    0.379078352934969458390853345631019859L,
    0.384411698910332039734790062481290869L,
    0.389716751140025213370463604003520867L,
    0.394993808240868978106394036364981768L,
    0.400243164127012706929325101995131170L,
    0.405465108108164381978013115464349137L,
    0.410659924985268385934306203175822788L,
    0.415827895143710965613328892954902305L,
    0.420969294644129636128867161506795972L,
    0.426084395310900063124544879595476619L,
    0.431173464818371340859172478955594998L,
    0.436236766774918070349041323061121301L,
    0.441274560804875229489496441661301225L,
    0.446287102628419511532590180619669007L,
    0.451274644139458585144692383079012479L,
    0.456237433481587594380805538163929748L,
    0.461175715122170166367999925597855359L,
    0.466089729924599224558619247504769400L,
    0.470979715218791012546897856056359251L,
    0.475845904869963914265209586304381412L,
    0.480688529345751907676618455448011551L,
    0.485507815781700807801791077190788901L,
    0.490303988045193838150346159645746861L,
    0.495077266797851514597964584842833665L,
    0.499827869556449329821331415247044142L,
    0.504556010752395287058308531738174930L,
    0.509261901789807946804074919228323825L,
    0.513945751102234316801006088274217593L,
    0.518607764208045632152976996364798699L,
    0.523248143764547836516807224934870842L,
    0.527867089620842385113892217778300964L,
    0.532464798869471843873923723460142243L,
    0.537041465896883654566729244153832299L,
    0.541597282432744371576542303900434099L,
    0.546132437598135650382397209231209164L,
    0.550647117952662279259948179204913460L,
    0.555141507540501592715480359515904050L,
    0.559615787935422686270888500526826593L,
    0.564070138284802966071384290090190712L,
    0.568504735352668712078738764866962264L,
    0.572919753561785509092756726626261069L,
    0.577315365034823604318112061519496402L,
    0.581691739634622482520610753725372341L,
    0.586049045003578208904119436287324350L,
    0.590387446602176374641916708123598758L,
    0.594707107746692789514343546529205333L,
    0.599008189646083399381600024461651502L,
    0.603290851438084262340585186661310606L,
    0.607555250224541795501085152791125372L,
    0.611801541105992903529889766428814784L,
    0.616029877215514019647565928196700650L,
    0.620240409751857528851494632567246857L,
    0.624433288011893501042538744054673120L,
    0.628608659422374137744308205774183640L,
    0.632766669571037829545786468503579758L,
    0.636907462237069231620494427181199191L,
    0.641031179420931291055601334405392547L,
    0.645137961373584701665228496134731906L,
    0.649227946625109818890839969905311122L,
    0.653301272012745638758615881210873885L,
    0.657358072708360030141890023245936166L,
    0.661398482245365008260235838709650938L,
    0.665422632545090448950092610006660181L,
    0.669430653942629267298885270929503510L,
    0.673422675212166720297960388801017265L,
    0.677398823591806140809682609997348299L,
    0.681359224807903068948071559568089442L,
    0.685304003098919416544048078967232986L,
    0.689233281238808980324914337814603903L
};

/*  Macros for 1/n for n = 2, 3, ..., 6, 7. These make the code look cleaner. */
#define ONE_HALF 0.50L
#define ONE_THIRD 0.3333333333333333333333333333333333333L
#define ONE_FOURTH 0.250L
#define ONE_FIFTH 0.20L
#define ONE_SIXTH 0.1666666666666666666666666666666666667L
#define ONE_SEVENTH 0.14285714285714285714285714285714L

/*  Not needed for 64-bit.                                                    */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
#define ONE_EIGHTH 0.1250L
#define ONE_NINTH 0.11111111111111111111111111111111111L
#endif

/*  Double double uses a different algorithm. 64-bit, 80-bit extended, and    *
 *  128-bit quadruple use the same idea.                                      */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_LITTLE_ENDIAN \
    && TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_128_BIT_DOUBLEDOUBLE_BIG_ENDIAN

/*  Function for computing natural log at long double precision.              */
long double tmpl_LDouble_Log(long double x)
{
    /*  Declare all necessary variables.                                      */
    long double s, poly, A, A_sq;

    /*  Variable for the exponent of the double x. x is written as            *
     *  1.m * 2^(expo - bias). signed int is guaranteed to be at least 15     *
     *  bits, per the standard, which is wide enough to store the 15 bit      *
     *  unsigned exponent in a double.                                        */
    signed int exponent;

    /*  Variable for the index of the arrays table and rcpr defined above     *
     *  which corresponds to the input x.                                     */
    unsigned int ind;

    /*  Variable for the union of a double and the bits representing it.      */
    tmpl_IEEE754_LDouble w;

    /*  Set the double part of the union to the input.                        */
    w.r = x;

    /*  Special cases. log(negative) is undefined. log(0) = negative infinity,*
     *  log(inf) = inf, and log(Not-A-Number) = Not-A-Number.                 */
    if (w.bits.sign)
        return TMPL_NANL;

    /*  Subnormal normal or zero.                                             */
    else if (w.bits.expo == 0x00U)
    {
        /*  log(0) = -infinity.                                               */
        if (w.r == 0.0L)
            return -TMPL_INFINITYL;

        /*  Non-zero subnormal number. Normalize by multiplying by 2^63,      *
         *  which is 9.223372036854775808 x 10^18.                            */
        w.r *= 9.223372036854775808E18L;

        /*  Compute the exponent. Since we multiplied by 2^52, subtract 52    *
         *  from the value.                                                   */
        exponent = w.bits.expo - TMPL_LDOUBLE_BIAS - 63;
    }

    /*  NaN or positive infinity. Simply return the input.                    */
#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
    else if (w.bits.expo == 0x7FFU)
        return x;
#else
    else if (w.bits.expo == 0x7FFFU)
        return x;
#endif

    /*  For values close to but less than 1, the computation of the division  *
     *  (x-1)/(x+1) may lose precision and log(x) may have bad relative error *
     *  (it will still have ~10^-16 absolute error since log(1) = 0). To      *
     *  avoid this, use the basic Taylor series for log(1 + (-s)), s = 1 - x, *
     *  and return this. Since 1-x is very small, only a few terms are needed.*/
    else if (0.99L < w.r && w.r < 1.0L)
    {
        s = 1.0L - x;

        /*  Horner's method of polynomial computation reduces the number of   *
         *  multiplications needed. Use this.                                 */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
        return -s * (
            1.0L + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * (
                        ONE_FOURTH + s * (
                            ONE_FIFTH + s * (
                                ONE_SIXTH + s * (
                                    ONE_SEVENTH + s * (
                                        ONE_EIGHTH + s * ONE_NINTH
                                    )
                                )
                            )
                        )
                    )
                )
            )
        );
#else
        /*  Few terms needed for 64-bit.                                      */
        return -s * (
            1.0L + s * (
                ONE_HALF + s * (
                    ONE_THIRD + s * (
                        ONE_FOURTH + s * (
                            ONE_FIFTH + s * (
                                ONE_SIXTH + s * ONE_SEVENTH
                            )
                        )
                    )
                )
            )
        );
#endif
    }

    /*  Normal number. Compute the exponent. This is the bits of the exponent *
     *  part of the union minus the bias.                                     */
    else
        exponent = w.bits.expo - TMPL_LDOUBLE_BIAS;

    /*  Reset the exponent to the bias. Since x = 1.m * 2^(expo - bias), by   *
     *  setting expo = bias we have x = 1.m, so 1 <= x < 2.                   */
    w.bits.expo = TMPL_LDOUBLE_BIAS;

#if TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_BIG_ENDIAN || \
    TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN

    /*  64-bit. man0 is 4 bits, man1 is 16 bits.                              */
    ind = w.bits.man0;
    ind = (ind << 3U) + (w.bits.man1 >> 13U);
#elif \
 TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_LITTLE_ENDIAN || \
 TMPL_LDOUBLE_ENDIANNESS == TMPL_LDOUBLE_128_BIT_QUADRUPLE_BIG_ENDIAN

    /*  128-bit quadruple. man0 is 16 bits wide.                              */
    ind = w.bits.man0 >> 9U;
#else

    /*  Extended precision (96-bit or 128-bit). man0 is 15 bits wide.         */
    ind = w.bits.man0 >> 8U;
#endif

    s = w.r*tmpl_ldouble_rcpr_table[ind];
    A = (s - 1.0L) / (s + 1.0L);
    A_sq = A*A;

#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
    poly = A * (
        2.0L + A_sq * (
            0.666666666666666666666666666666666666667L + A_sq * (
                0.4L + A_sq * 0.285714285714285714285714285714285714L
            )
        )
    );
#else
    /*  Few terms needed for 64-bit.                                          */
    poly = A*(2.0 + A_sq * (0.666666666666666667 + A_sq * 0.4));
#endif

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_L*exponent + poly +
        tmpl_ldouble_log_table[ind];
}
/*  End of tmpl_LDouble_Log.                                                  */

#else

/*  Double double not implemented yet.                                        */
long double tmpl_LDouble_Log(long double x)
{
    tmpl_IEEE754_LDouble w, xhi, xlow;
    long double s, polya, polyb, A, A_sq;
    signed int exponent;
    unsigned int ind;
    w.r = x;

    xhi.r = (long double)w.d[0];
    xlow.r = x - xhi.r;
    s = -xlow.r / xhi.r;

    polya = -s * (1.0L + s * (ONE_HALF + s * ONE_THIRD));

    exponent = xhi.bits.expoa - TMPL_LDOUBLE_BIAS;
    xhi.bits.expoa = TMPL_LDOUBLE_BIAS;

    ind = w.bits.man0a;
    ind = (ind << 3U) + (w.bits.man1a >> 13U);

    s = xhi.r*tmpl_ldouble_rcpr_table[ind];
    A = (s - 1.0L) / (s + 1.0L);
    A_sq = A*A;

    /*  Compute the polynomial to the first few terms via Horner's method.    */
    polyb = A*(
        2.0L + A_sq * (
            0.666666666666666666666666666666666666667L + A_sq * (
                0.4L + A_sq * (
                    0.285714285714285714285714285714285714L + A_sq * (
                        0.222222222222222222222222222222222222L + A_sq * (
                            0.181818181818181818181818181818181818L + A_sq * 0.153846153846153846153846153846153846L
                        )
                    )
                )
            )
        )
    );

    /*  We wrote x = 2^b * ut/t. Return b*log(2) + log(u/t) + log(t).         */
    return tmpl_Natural_Log_of_Two_L*exponent + polya + polyb +
        tmpl_ldouble_log_table[ind];
}
#endif
/*  End of if for double double.                                              */

/*  undef all the macros incase someone wants to #include this file.          */
#undef ONE_HALF
#undef ONE_THIRD
#undef ONE_FOURTH
#undef ONE_FIFTH
#undef ONE_SIXTH
#undef ONE_SEVENTH

/*  Not defined for 64-bit.                                                   */
#if TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_BIG_ENDIAN && \
    TMPL_LDOUBLE_ENDIANNESS != TMPL_LDOUBLE_64_BIT_LITTLE_ENDIAN
#undef ONE_EIGHTH
#undef ONE_NINTH
#endif

#else
#include <math.h>
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
long double tmpl_LDouble_Log(long double x)
{
    return logl(x);
}
#else
long double tmpl_LDouble_Log(long double x)
{
    double logx = log((double)x);
    return (long double)logx;
}
#endif
/*  End of #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L       */

#endif
/*  End of if for TMPL_USE_MATH_ALGORITHMS.                                   */
