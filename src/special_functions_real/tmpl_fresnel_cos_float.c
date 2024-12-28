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
#define FRESNEL_COSINE_TAYLORF_00  1.0F
#define FRESNEL_COSINE_TAYLORF_01 -0.10F
#define FRESNEL_COSINE_TAYLORF_02  4.62962962962962962962962962963E-3F
#define FRESNEL_COSINE_TAYLORF_03 -1.06837606837606837606837606838E-4F
#define FRESNEL_COSINE_TAYLORF_04  1.45891690009337068160597572362E-6F
#define FRESNEL_COSINE_TAYLORF_05 -1.31225329638028050726463424876E-8F
#define FRESNEL_COSINE_TAYLORF_06  8.35070279514723959168403612848E-11F
#define FRESNEL_COSINE_TAYLORF_07 -3.95542951645852576339713723403E-13F
#define FRESNEL_COSINE_TAYLORF_08  1.44832646435981372649642651246E-15F
#define FRESNEL_COSINE_TAYLORF_09 -4.22140728880708823303144982434E-18F
#define FRESNEL_COSINE_TAYLORF_10  1.00251649349077191670194893133E-20F
#define FRESNEL_COSINE_TAYLORF_11 -1.97706475387790517483308832056E-23F
#define FRESNEL_COSINE_TAYLORF_12  3.28926034917575173275247613225E-26F
#define FRESNEL_COSINE_TAYLORF_13 -4.67848351551848577372630857707E-29F
#define FRESNEL_COSINE_TAYLORF_14  5.75419164398217177219656443388E-32F
#define FRESNEL_COSINE_TAYLORF_15 -6.18030758822279613746380577975E-35F

/* Define Coefficients for the Fresnel Cosine Asymptotic Expansion.           */
#define FRESNEL_COSINE_ASYMF_00  0.50F
#define FRESNEL_COSINE_ASYMF_01 -0.250F
#define FRESNEL_COSINE_ASYMF_02 -0.3750F
#define FRESNEL_COSINE_ASYMF_03  0.93750F
#define FRESNEL_COSINE_ASYMF_04  3.281250F
#define FRESNEL_COSINE_ASYMF_05 -14.7656250F
#define FRESNEL_COSINE_ASYMF_06 -81.21093750F
#define FRESNEL_COSINE_ASYMF_07  527.871093750F
#define FRESNEL_COSINE_ASYMF_08  3959.0332031250F
#define FRESNEL_COSINE_ASYMF_09 -33651.78222656250F

float tmpl_Float_Fresnel_Cos(float x)
{
    /* Variables for C(x) and powers of x, respectively.                      */
    float cx, arg;
    float sinarg, cosarg, cos_x_squared, sin_x_squared;
    arg = x*x;

    /* For small x use the Taylor expansion to compute C(x). For larger x,  *
     * use the asymptotic expansion. For values near 3.076, accuracy of 5   *
     * decimals is guaranteed. Higher precicion outside this region.        */
    if (arg < 9.0F)
    {
        arg *= arg;
        cx = arg * FRESNEL_COSINE_TAYLORF_15 + FRESNEL_COSINE_TAYLORF_14;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_13;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_12;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_11;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_10;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_09;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_08;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_07;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_06;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_05;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_04;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_03;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_02;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_01;
        cx = arg * cx + FRESNEL_COSINE_TAYLORF_00;
        cx = cx*x;
    }
    else if (arg < 1.0e16F)
    {
        cos_x_squared = tmpl_Float_Cos(arg);
        sin_x_squared = tmpl_Float_Sin(arg);

        arg = 1.0F/arg;
        sin_x_squared *= arg;
        arg *= arg;
        cos_x_squared *= arg;

        sinarg  = arg * FRESNEL_COSINE_ASYMF_08 + FRESNEL_COSINE_ASYMF_06;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYMF_04;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYMF_02;
        sinarg  = arg * sinarg + FRESNEL_COSINE_ASYMF_00;
        sinarg *= sin_x_squared;

        cosarg  = arg * FRESNEL_COSINE_ASYMF_09 + FRESNEL_COSINE_ASYMF_07;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYMF_05;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYMF_03;
        cosarg  = arg * cosarg + FRESNEL_COSINE_ASYMF_01;
        cosarg *= cos_x_squared;

        cx = cosarg + sinarg;
        cx *= x;

        if (x > 0.0F)
            cx += tmpl_Float_Sqrt_Pi_By_Eight;
        else
            cx -= tmpl_Float_Sqrt_Pi_By_Eight;
    }

    /* For large values, return the limit of S(x) as x -> +/- infinity.       */
    else
    {
        if (x > 0.0F)
            return tmpl_Float_Sqrt_Pi_By_Eight;
        else
            return -tmpl_Float_Sqrt_Pi_By_Eight;
    }

    return cx;
}
/*  End of tmpl_Float_Fresnel_Cos.                                            */
