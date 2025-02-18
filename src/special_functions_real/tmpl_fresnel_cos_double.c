/******************************************************************************
 *                             Fresnel Cosine                                 *
 ******************************************************************************
 *  This C program contains several algorithms for the computation of the     *
 *  Fresnel Cosine integral. This is meant to test the accuracy and           *
 *  efficiency of the various algorithms. This file is not included in the    *
 *  setup.py file, and thus will not be compiled. The fresnel sine and cosine *
 *  functions that are used in the _special_functions.c file are the          *
 *  functions that had the best combination of speed and accuracy. This file  *
 *  is kept so that users may experiment with the various known algorithms.   *
 ******************************************************************************
 *  We define the Fresnel Cosine Integrals as follows:                        *
 *                 x                                                          *
 *                 -                                                          *
 *                | |                                                         *
 *       C(x) =   |   cos(t^2) dt                                             *
 *              | |                                                           *
 *               -                                                            *
 *               0                                                            *
 ******************************************************************************
 *  It is very common for a pi/2 to be placed inside the cosine term,         *
 *  and thus in translating one would need to scale x by sqrt(2/pi) and scale *
 *  the results by sqrt(pi/2). Several of the algorithms implemented compute  *
 *  the latter definition. We have taken this into account in our functions   *
 *  and return the values corresponding to the equations above.               *
 ******************************************************************************
 *                              DEFINED FUNCTIONS                             *
 ******************************************************************************
 *  Fresnel_Cos_Float/Fresnel_Cos_Double/Fresnel_Cos_Long_Double:             *
 *      This uses the standard Taylor expansion for small inputs (|x|<=4),    *
 *      and asymptotic expansions for large input (|x|>4). The Taylor Series  *
 *      are:                                                                  *
 *                  ___                                                       *
 *                  \      (-1)^n x^(4n+1)/                                   *
 *        C(x)=     /__                /  (4n+1)(2n)!                         *
 *                  n = 0                                                     *
 *                                                                            *
 *      This can be obtained by substituting the Taylor expansions for        *
 *      sin(x^2) and cos(x^2), respectively, and integrating term by term.    *
 *                                                                            *
 *      The asymptotic expansions can be obtained by iteratively using        *
 *      integration by parts. The Asymptotic expansions diverge for all x,    *
 *      but by cutting off the expansion at a particular N, one finds a very  *
 *      good approximations. The series are given by:                         *
 *                                                                            *
 *          a_n(x) = (4n+2)! / (2^(4n+3) (2n+1)! x^(4n+3))                    *
 *          b_n(x) = (4n)! / (2^(4n+1) (2n)! x^(4n+1))                        *
 *                                                                            *
 *                             ___                                            *
 *                             \                                              *
 *        C(x) = sqrt(pi/i) +  /__  (-1)^n (b_n(x)sin(x^2) - a_n(x)cos(x^2))  *
 *                             n = 0                                          *
 *                                                                            *
 *      The error in the asympotic series goes like |a_N(x)|+|b_N(x)|.        *
 *      For large x, and appropriate N, this can be made incredibly small.    *
 *      For |x|>10, and choosing N=6, the max error is 1.e-12. For values     *
 *      near |x|=4 the error is 1.e-6.                                        *
 ******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                               *
 *  Date:       August 30, 2019                                               *
 ******************************************************************************/

/*  The C standard library header math.h is included here, as are aliases for *
 *  various functions, the macros INFINITY and NAN, as well as the max legal  *
 *  values for the exponential function which don't return INFINITY.          */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

/* Define Coefficients for the Fresnel Cosine Taylor Expansion.               */
#define FRESNEL_COSINE_TAYLOR_00    1.0
#define FRESNEL_COSINE_TAYLOR_01   -0.10
#define FRESNEL_COSINE_TAYLOR_02    4.62962962962962962962962962963e-3
#define FRESNEL_COSINE_TAYLOR_03   -1.06837606837606837606837606838e-4
#define FRESNEL_COSINE_TAYLOR_04    1.45891690009337068160597572362e-6
#define FRESNEL_COSINE_TAYLOR_05   -1.31225329638028050726463424876e-8
#define FRESNEL_COSINE_TAYLOR_06    8.35070279514723959168403612848e-11
#define FRESNEL_COSINE_TAYLOR_07   -3.95542951645852576339713723403e-13
#define FRESNEL_COSINE_TAYLOR_08    1.44832646435981372649642651246e-15
#define FRESNEL_COSINE_TAYLOR_09   -4.22140728880708823303144982434e-18
#define FRESNEL_COSINE_TAYLOR_10    1.00251649349077191670194893133e-20
#define FRESNEL_COSINE_TAYLOR_11   -1.97706475387790517483308832056e-23
#define FRESNEL_COSINE_TAYLOR_12    3.28926034917575173275247613225e-26
#define FRESNEL_COSINE_TAYLOR_13   -4.67848351551848577372630857707e-29
#define FRESNEL_COSINE_TAYLOR_14    5.75419164398217177219656443388e-32
#define FRESNEL_COSINE_TAYLOR_15   -6.18030758822279613746380577975e-35
#define FRESNEL_COSINE_TAYLOR_16    5.84675500746883629629795521967e-38
#define FRESNEL_COSINE_TAYLOR_17   -4.90892396452342296700208077293e-41
#define FRESNEL_COSINE_TAYLOR_18    3.68249351546114573519399405667e-44
#define FRESNEL_COSINE_TAYLOR_19   -2.48306909745491159103989919027e-47
#define FRESNEL_COSINE_TAYLOR_20    1.51310794954121709805375306783e-50
#define FRESNEL_COSINE_TAYLOR_21   -8.37341968387228154282667202938e-54
#define FRESNEL_COSINE_TAYLOR_22    4.22678975419355257583834431490e-57

/* Define Coefficients for the Fresnel Cosine Asymptotic Expansion.           */
#define FRESNEL_COSINE_ASYM_00     0.50
#define FRESNEL_COSINE_ASYM_01    -0.250
#define FRESNEL_COSINE_ASYM_02    -0.3750
#define FRESNEL_COSINE_ASYM_03     0.93750
#define FRESNEL_COSINE_ASYM_04     3.281250
#define FRESNEL_COSINE_ASYM_05    -14.7656250
#define FRESNEL_COSINE_ASYM_06    -81.21093750
#define FRESNEL_COSINE_ASYM_07     527.871093750
#define FRESNEL_COSINE_ASYM_08     3959.0332031250
#define FRESNEL_COSINE_ASYM_09    -33651.78222656250

double tmpl_Double_Fresnel_Cos(double x)
{
    /* Variables for C(x) and powers of x, respectively.                      */
    double cx, arg;

    /*  Variables for the asymptotic expansion of C(x).                       */
    double sinarg, cosarg, cos_x_squared, sin_x_squared;
    arg = x*x;

    /* For small x use the Taylor expansion to compute C(x). For larger x,  *
     * use the asymptotic expansion. For values near 3.076, accuracy of 5   *
     * decimals is guaranteed. Higher precicion outside this region.        */
    if (arg < 13.19)
    {
        arg *= arg;
        cx = arg * FRESNEL_COSINE_TAYLOR_22 + FRESNEL_COSINE_TAYLOR_21;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_20;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_19;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_18;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_17;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_16;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_15;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_14;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_13;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_12;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_11;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_10;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_09;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_08;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_07;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_06;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_05;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_04;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_03;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_02;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_01;
        cx = arg * cx + FRESNEL_COSINE_TAYLOR_00;
        cx = cx*x;
    }
    else if (arg < 1.0e16)
    {
        cos_x_squared = tmpl_Double_Cos(arg);
        sin_x_squared = tmpl_Double_Sin(arg);

        arg = 1.0/arg;
        sin_x_squared *= arg;
        arg *= arg;
        cos_x_squared *= arg;

        sinarg  = arg * FRESNEL_COSINE_ASYM_08 + FRESNEL_COSINE_ASYM_06;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYM_04;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYM_02;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYM_00;
        sinarg *= sin_x_squared;

        cosarg  = arg * FRESNEL_COSINE_ASYM_09 + FRESNEL_COSINE_ASYM_07;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYM_05;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYM_03;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYM_01;
        cosarg *= cos_x_squared;

        cx = cosarg + sinarg;
        cx *= x;

        if (x > 0.0)
            cx += tmpl_Double_Sqrt_Pi_By_Eight;
        else
            cx -= tmpl_Double_Sqrt_Pi_By_Eight;
    }

    /* For large values, return the limit of S(x) as x -> +/- infinity.       */
    else
    {
        if (x > 0.0)
            return tmpl_Double_Sqrt_Pi_By_Eight;
        else
            return -tmpl_Double_Sqrt_Pi_By_Eight;
    }

    return cx;
}
