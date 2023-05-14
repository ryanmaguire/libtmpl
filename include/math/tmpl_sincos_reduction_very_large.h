#ifndef TMPL_SINCOS_REDUCTION_VERY_LARGE_H
#define TMPL_SINCOS_REDUCTION_VERY_LARGE_H

#include <libtmpl/include/tmpl_math.h>

static const double split = 134217729.0; /* 2^27 + 1 */
static const double t576 = 2.473304014731045340605025210196E173; /* 2^576 */
static const double tm600 = 2.409919865102884117740750034713E-181; /* 2^-600 */
static const double tm24 = 5.9604644775390625E-08; /* 2^-24 */
static const double big = 6.755399441055744E15; /* 1.5 * 2^52 */
static const double big1 = 2.7021597764222976E16; /* 1.5 * 2^54 */
static const double hp0 = 1.570796326794896557998981734272E00;  /* pi / 2 hi */
static const double hp1 = 6.123233995736766035868820147292E-17; /* pi / 2 lo */
static const double mp1 = 1.5707963407039642333984375E00;        /* pi / 2 hi */
static const double mp2 = -1.390906767539945576572790741920E-08; /* pi / 2 lo */

static const double toverp[75] = { /*  2/ PI base 24*/
    10680707.0,  7228996.0,  1387004.0,  2578385.0, 16069853.0,
    12639074.0,  9804092.0,  4427841.0, 16666979.0, 11263675.0,
    12935607.0,  2387514.0,  4345298.0, 14681673.0,  3074569.0,
    13734428.0, 16653803.0,  1880361.0, 10960616.0,  8533493.0,
    3062596.0,  8710556.0,  7349940.0,  6258241.0,  3772886.0,
    3769171.0,  3798172.0,  8675211.0, 12450088.0,  3874808.0,
    9961438.0,   366607.0, 15675153.0,  9132554.0,  7151469.0,
    3571407.0,  2607881.0, 12013382.0,  4155038.0,  6285869.0,
    7677882.0, 13102053.0, 15825725.0,   473591.0,  9065106.0,
    15363067.0,  6271263.0,  9264392.0,  5636912.0,  4652155.0,
    7056368.0, 13614112.0, 10155062.0,  1944035.0,  9527646.0,
    15080200.0,  6658437.0,  6231200.0,  6832269.0, 16767104.0,
    5075751.0,  3212806.0,  1398474.0,  7579849.0,  6349435.0,
    12618859.0,  4703257.0, 12806093.0, 14477321.0,  2786137.0,
    12875403.0,  9837734.0, 14528324.0, 13719321.0,   343717.0
};

static unsigned int
tmpl_Double_SinCos_Reduction_Very_Large(double x, double *a, double *aa)
{
    unsigned int k;
    tmpl_IEEE754_Double u, gor;
    double r[6], s, t, sum, b, bb, sum1, sum2, b1, bb1, b2, bb2, x1, x2, t1, t2;

    x *= tm600;
    t = x*split;
    x1 = t - (t - x);
    x2 = x - x1;
    sum = 0;
    u.r = x1;
    gor.r = t576;

    if (u.bits.expo < 450U)
        k = 0U;
    else
    {
        k = (u.bits.expo - 450U)/24U;
        gor.bits.expo -= (24U*k & 0x7FF);
    }

    r[0] = x1*toverp[k]*gor.r;
    s = (r[0] + big) - big;
    sum += s;
    r[0] -= s;
    gor.r *= tm24;

    r[1] = x1*toverp[k+1]*gor.r;
    s = (r[1] + big) - big;
    sum += s;
    r[1] -= s;
    gor.r *= tm24;

    r[2] = x1*toverp[k+2]*gor.r;
    s = (r[2] + big) - big;
    sum += s;
    r[2] -= s;
    gor.r *= tm24;

    r[3] = x1*toverp[k+3]*gor.r;
    gor.r *= tm24;
    r[4] = x1*toverp[k+4]*gor.r;
    gor.r *= tm24;
    r[5] = x1*toverp[k+5]*gor.r;
    gor.r *= tm24;

    t = (((((r[5]) + r[4]) + r[3]) + r[2]) + r[1]) + r[0];
    bb = (((((r[0]-t) + r[1]) + r[2]) + r[3]) + r[4]) + r[5];
    s = (t + big) - big;
    sum += s;
    t -= s;
    b = t + bb;
    bb = (t - b) + bb;
    s = (sum + big1) - big1;
    sum -= s;
    b1 = b;
    bb1 = bb;
    sum1 = sum;
    sum = 0;

    u.r = x2;
    gor.r = t576;

    if (u.bits.expo < 450U)
        k = 0U;
    else
    {
        k = (u.bits.expo - 450U)/24U;
        gor.bits.expo -= (24U*k & 0x7FF);
    }

    r[0] = x2*toverp[k]*gor.r;
    s = (r[0] + big) - big;
    sum += s;
    r[0] -= s;
    gor.r *= tm24;

    r[1] = x2*toverp[k+1]*gor.r;
    s = (r[1] + big) - big;
    sum += s;
    r[1] -= s;
    gor.r *= tm24;

    r[2] = x2*toverp[k+2]*gor.r;
    s = (r[2] + big) - big;
    sum += s;
    r[2] -= s;
    gor.r *= tm24;

    r[3] = x2*toverp[k+3]*gor.r;
    gor.r *= tm24;
    r[4] = x2*toverp[k+4]*gor.r;
    gor.r *= tm24;
    r[5] = x2*toverp[k+5]*gor.r;
    gor.r *= tm24;

    t = (((((r[5]) + r[4]) + r[3]) + r[2]) + r[1]) + r[0];
    bb = (((((r[0] - t) + r[1]) + r[2]) + r[3]) + r[4]) + r[5];
    s = (t + big) - big;
    sum += s;
    t -= s;
    b = t + bb;
    bb = (t - b) + bb;
    s = (sum + big1) - big1;
    sum -= s;

    b2 = b;
    bb2 = bb;
    sum2 = sum;

    sum = sum1 + sum2;
    b = b1 + b2;

    if (tmpl_Double_Abs(b1) > tmpl_Double_Abs(b2))
        bb = (b1 - b) + b2;
    else
        bb = (b2 - b) + b1;

    if (b > 0.5)
    {
        b -= 1.0;
        sum += 1.0;
    }
    else if (b < -0.5)
    {
        b+=1.0;
        sum-=1.0;
    }

    s = b + (bb + bb1 + bb2);
    t = ((b - s) + bb) + (bb1 + bb2);
    b = s*split;
    t1 = b - (b - s);
    t2 = s - t1;
    b = s*hp0;
    bb = (((t1*mp1 - b) + t1*mp2) + t2*mp1) + (t2*mp2 + s*hp1 + t*hp0);
    s = b + bb;
    t = (b - s) + bb;
    *a = s;
    *aa = t;
    k = (unsigned int)((int)sum & 3);
    return k; /* return quarter of unit circle */
}

#endif
