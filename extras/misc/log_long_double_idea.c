#include <libtmpl/include/tmpl_math.h>
#include <stdio.h>
#include <math.h>

static const unsigned long n_coeffs = 10;

static long double coeffs[13] = {
    2.00000000000000000000000000000000L,
    0.66666666666666666666666666666667L,
    0.40000000000000000000000000000000L,
    0.28571428571428571428571428571429L,
    0.22222222222222222222222222222222L,
    0.18181818181818181818181818181818L,
    0.15384615384615384615384615384615L,
    0.13333333333333333333333333333333L,
    0.11764705882352941176470588235294L,
    0.10526315789473684210526315789474L,
    0.095238095238095238095238095238095L,
    0.086956521739130434782608695652174L,
    0.080000000000000000000000000000000L
};

/*
 * Not needed.
 * #define TMPL_LOGL_A13 0.074074074074074074074074074074074L
 * #define TMPL_LOGL_A14 0.068965517241379310344827586206897L
 * #define TMPL_LOGL_A15 0.064516129032258064516129032258065L
 */

static long double table[32] = {
    0.0L,
    0.03077165866675368837102820759677216L,
    0.06062462181643484258060613204042026L,
    0.08961215868968713261995146937848453L,
    0.1177830356563834545387941094705217L,
    0.1451820098444978972819350637405643L,
    0.1718502569266592223400989460551473L,
    0.1978257433299198803625720711969615L,
    0.2231435513142097557662950903098345L,
    0.2478361639045812567806027657465247L,
    0.2719337154836417588316694945329992L,
    0.2954642128938358763866819060549642L,
    0.3184537311185346158102472135905996L,
    0.3409265869705932103050891997803562L,
    0.3629054936893684531378243459774898L,
    0.3844116989103320397347900624812909L,
    0.4054651081081643819780131154643491L,
    0.4260843953109000631245448795954766L,
    0.4462871026284195115325901806196690L,
    0.4660897299245992245586192475047694L,
    0.4855078157817008078017910771907889L,
    0.5045560107523952870583085317381749L,
    0.5232481437645478365168072249348708L,
    0.5415972824327443715765423039004341L,
    0.5596157879354226862708885005268266L,
    0.5773153650348236043181120615194964L,
    0.5947071077466927895143435465292053L,
    0.6118015411059929035298897664288148L,
    0.6286086594223741377443082057741836L,
    0.6451379613735847016652284961347319L,
    0.6613984822453650082602358387096509L,
    0.6773988235918061408096826099973483L
};

static long double rcpr[32] = {
    1.000000000000000000000000000000000L,
    0.9696969696969696969696969696969697L,
    0.9411764705882352941176470588235294L,
    0.9142857142857142857142857142857143L,
    0.8888888888888888888888888888888889L,
    0.8648648648648648648648648648648649L,
    0.8421052631578947368421052631578947L,
    0.8205128205128205128205128205128205L,
    0.8000000000000000000000000000000000L,
    0.7804878048780487804878048780487805L,
    0.7619047619047619047619047619047619L,
    0.7441860465116279069767441860465116L,
    0.7272727272727272727272727272727273L,
    0.7111111111111111111111111111111111L,
    0.6956521739130434782608695652173913L,
    0.6808510638297872340425531914893617L,
    0.6666666666666666666666666666666667L,
    0.6530612244897959183673469387755102L,
    0.6400000000000000000000000000000000L,
    0.6274509803921568627450980392156863L,
    0.6153846153846153846153846153846154L,
    0.6037735849056603773584905660377358L,
    0.5925925925925925925925925925925926L,
    0.5818181818181818181818181818181818L,
    0.5714285714285714285714285714285714L,
    0.5614035087719298245614035087719298L,
    0.5517241379310344827586206896551724L,
    0.5423728813559322033898305084745763L,
    0.5333333333333333333333333333333333L,
    0.5245901639344262295081967213114754L,
    0.5161290322580645161290322580645161L,
    0.5079365079365079365079365079365079L
};

static long double my_log(long double x)
{
    long double mantissa, A, A_sq, poly;
    signed long int exponent;
    tmpl_IEEE754_LDouble w;
    unsigned int ind, n;

    if (x < 1.0L)
        return -my_log(1.0 / x);

    w.r = x;
    exponent = w.bits.expo - TMPL_LDOUBLE_BIAS;
    w.bits.expo = TMPL_LDOUBLE_BIAS;

    ind = (w.bits.man0 & 0xF800U) >> 11;
    mantissa = w.r*rcpr[ind];

    A = (mantissa - 1.0L) / (mantissa + 1.0L);
    A_sq = A*A;
    poly = coeffs[n_coeffs];

    for (n = 1; n <= n_coeffs; ++n)
        poly = poly*A_sq + coeffs[n_coeffs - n];

    return tmpl_Natural_Log_of_Two_L*(long double)exponent + A*poly + table[ind];
}

int main(void)
{
    unsigned long int n;
    unsigned long int N = 1E7;
    long double start = 2.0L;
    long double end = 100.0L;
    long double dx = (end - start) / (long double)N;
    long double max_rel = 0.0L;
    long double max_abs = 0.0L;
    long double x = start;
    long double y, z, tmp;

    for (n = 0UL; n < N; ++n)
    {
        y = my_log(x);
        z = logl(x);
        tmp = fabsl(y - z);

        if (tmp > max_abs)
            max_abs = tmp;

        tmp = fabsl((y - z)/z);

        if (tmp > max_rel)
            max_rel = tmp;

        x += dx;
    }

    printf("Max Abs: %.32Le\nMax Rel: %.32Le\n", max_abs, max_rel);
}










