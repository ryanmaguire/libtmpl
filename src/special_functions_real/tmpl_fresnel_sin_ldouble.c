/*******************************************************************************
 *                               Fresnel Sine                                  *
 *******************************************************************************
 * This C program contains several algorithms for the computation of the       *
 * Fresnel Sine and Cosine integrals. This is meant to test the accuracy and   *
 * efficiency of the various algorithms. This file is not included in the      *
 * setup.py file, and thus will not be compiled. The fresnel sine and cosine   *
 * functions that are used in the _special_functions.c file are the functions  *
 * that had the best combination of speed and accuracy. This file is kept so   *
 * that users may experiment with the various known algorithms.                *
 *******************************************************************************
 * We define the Fresnel Sine and Cosine Integrals as follows:                 *
 *           x                                                                 *
 *           -                                                                 *
 *          | |                                                                *
 * S(x) =   |   sin(t^2) dt                                                    *
 *        | |                                                                  *
 *         -                                                                   *
 *         0                                                                   *
 *******************************************************************************
 * It is very common for a pi/2 to be placed inside the sine and cosine terms, *
 * and thus in translating one would need to scale x by sqrt(2/pi) and scale   *
 * the results by sqrt(pi/2). Several of the algorithms implemented compute    *
 * the latter definitions. We have taken this into account in our functions    *
 * and return the values corresponding to the equations above.                 *
 *******************************************************************************
 *                              DEFINED FUNCTIONS                              *
 *******************************************************************************
 *  Fresnel_Sine_Taylor_to_Asymptotic / Fresnel_Cosine_Taylor_to_Asymptotic:   *
 *      This uses the standard Taylor expansion for small inputs (|x|<=3), and *
 *      asymptotic expansions for large input (|x|>3). The Taylor Series are:  *
 *                                                                             *
 *                  ___                                                      *
 *                  \      (-1)^n x^(4n+3)/                                    *
 *        S(x)=     /__                /  (4n+3)(2n+1)!                      *
 *                  n = 0                                                      *
 *                                                                             *
 *      This can be obtained by substituting the Taylor expansions for         *
 *      sin(x^2) and cos(x^2), respectively, and integrating term by term.     *
 *      The interval [0,3] is broken into three pieces, and the appropriate    *
 *      number of terms in the expansion are used accordingly to obtain at     *
 *      least 8 decimals of accuracy.                                          *
 *                                                                             *
 *      The asymptotic expansions can be obtained by iteratively using         *
 *      integration by parts. The Asymptotic expansions diverge for all x, but *
 *      by cutting off the expansion at a particular N, one finds a very good  *
 *      approximations. The series are given by:                               *
 *                                                                             *
 *          a_n(x) = (4n+2)! / (2^(4n+3) (2n+1)! x^(4n+3))                     *
 *          b_n(x) = (4n)! / (2^(4n+1) (2n)! x^(4n+1))                         *
 *                                                                             *
 *                             ___                                           *
 *                             \                                               *
 *        S(x) = sqrt(pi/i) -  /__  (-1)^n (a_n(x)sin(x^2) + b_n(x)cos(x^2)) *
 *                             n = 0                                           *
 *                                                                             *
 *      The error in the asympotic series goes like |a_N(x)|+|b_N(x)|.         *
 *      For large x, and appropriate N, this can be made incredibly small.     *
 *******************************************************************************
 *  Fresnel_Sine_While_to_Asymptotic / Fresnel_Cosine_While_to_Asymptotic:     *
 *      Similar to Fresnel_Sine_Taylor_to_Asymptotic, but a while loop is used *
 *      during the Taylor approximation, stopping once the error is 1.0e-8.    *
 *******************************************************************************
 *  Fresnel_Sine_Heald_Rational_EPS_Minus_Three,                               *
 *  Fresnel_Sine_Heald_Rational_EPS_Minus_Four,                                *
 *  Fresnel_Sine_Heald_Rational_EPS_Minus_Six,                                 *
 *  Fresnel_Sine_Heald_Rational_EPS_Minus_Eight,                               *
 *      Computes fresnel integrals to specified precision using a rational     *
 *      approximation as computed by Mark A. Heald.                            *
 *      See Rational Approximations for the Fresnel Integrals, Mark A. Heald,  *
 *      Mathematics of Computation, Vol. 44, No. 170 (Apr., 1985), pp. 459-461 *
 *******************************************************************************
 *  Author:     Ryan Maguire, Wellesley College                                *
 *  Date:       Febuary 26, 2019                                               *
 ******************************************************************************/

/*  The C Standard Library header for math functions and more found here.     */
#include <libtmpl/include/tmpl_math.h>

/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_special_functions_real.h>

/* Define Coefficients for the Fresnel Sine Taylor Expansion.                 */
#define FRESNEL_SINE_TAYLORL_00  0.33333333333333333333333333333L
#define FRESNEL_SINE_TAYLORL_01 -2.38095238095238095238095238095E-2L
#define FRESNEL_SINE_TAYLORL_02  7.57575757575757575757575757576E-4L
#define FRESNEL_SINE_TAYLORL_03 -1.32275132275132275132275132275E-5L
#define FRESNEL_SINE_TAYLORL_04  1.45038522231504687645038522232E-7L
#define FRESNEL_SINE_TAYLORL_05 -1.08922210371485733804574384285E-9L
#define FRESNEL_SINE_TAYLORL_06  5.94779401363763503681199154450E-12L
#define FRESNEL_SINE_TAYLORL_07 -2.46682701026445692771004257606E-14L
#define FRESNEL_SINE_TAYLORL_08  8.03273501241577360913984452289E-17L
#define FRESNEL_SINE_TAYLORL_09 -2.10785519144213582486050800945E-19L
#define FRESNEL_SINE_TAYLORL_10  4.55184675892820028624362194733E-22L
#define FRESNEL_SINE_TAYLORL_11 -8.23014929921422135684449347133E-25L
#define FRESNEL_SINE_TAYLORL_12  1.26410789889891635219506925867E-27L
#define FRESNEL_SINE_TAYLORL_13 -1.66976179341737202698649397027E-30L
#define FRESNEL_SINE_TAYLORL_14  1.91694286210978253077267196219E-33L
#define FRESNEL_SINE_TAYLORL_15 -1.93035720881510785655551537411E-36L
#define FRESNEL_SINE_TAYLORL_16  1.71885606280178362396819126766E-39L
#define FRESNEL_SINE_TAYLORL_17 -1.36304126177913957635067836351E-42L
#define FRESNEL_SINE_TAYLORL_18  9.68728023887076175384366004096E-46L
#define FRESNEL_SINE_TAYLORL_19 -6.20565791963739670594197460729E-49L
#define FRESNEL_SINE_TAYLORL_20  3.60157930981012591661339989697E-52L
#define FRESNEL_SINE_TAYLORL_21 -1.90254122728987952723942026864E-55L
#define FRESNEL_SINE_TAYLORL_22  9.18642950239868569596123672835E-59L
#define FRESNEL_SINE_TAYLORL_23 -4.07013527785325672297810283986E-62L
#define FRESNEL_SINE_TAYLORL_24  1.66058051345108993284425792700E-65L

/* Define Coefficients for the Fresnel Sine Asymptotic Expansion.             */
#define FRESNEL_SINE_ASYML_00 -0.50L
#define FRESNEL_SINE_ASYML_01 -0.250L
#define FRESNEL_SINE_ASYML_02  0.3750L
#define FRESNEL_SINE_ASYML_03  0.93750L
#define FRESNEL_SINE_ASYML_04 -3.281250L
#define FRESNEL_SINE_ASYML_05 -14.7656250L
#define FRESNEL_SINE_ASYML_06  81.21093750L
#define FRESNEL_SINE_ASYML_07  527.871093750L
#define FRESNEL_SINE_ASYML_08 -3959.0332031250L
#define FRESNEL_SINE_ASYML_09 -33651.78222656250L

long double tmpl_LDouble_Fresnel_Sin(long double x)
{
    /* Variables for S(x) and powers of x, respectively. */
    long double sx;
    long double arg = x*x;
    long double sinarg, cosarg, cos_x_squared, sin_x_squared;

    /* For small x use the Taylor expansion to compute C(x). For larger x,  *
     * use the asymptotic expansion. For values near 3.076, accuracy of 5   *
     * decimals is guaranteed. Higher precicion outside this region. When   *
     * |x| > 1.e8, S(x) returns +/- sqrt(pi/8) to 8 decimals.               */
    if (arg < 11.68L)
    {
        x *= arg;
        arg *= arg;
        sx = arg * FRESNEL_SINE_TAYLORL_24 + FRESNEL_SINE_TAYLORL_23;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_22;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_21;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_20;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_19;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_18;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_17;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_16;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_15;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_14;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_13;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_12;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_11;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_10;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_09;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_08;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_07;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_06;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_05;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_04;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_03;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_02;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_01;
        sx = arg * sx + FRESNEL_SINE_TAYLORL_00;
        sx = sx*x;
    }
    else if (arg < 1.0E16L)
    {
        cos_x_squared = tmpl_LDouble_Cos(arg);
        sin_x_squared = tmpl_LDouble_Sin(arg);

        arg = 1.0L/arg;
        cos_x_squared *= arg;
        arg *= arg;
        sin_x_squared *= arg;

        cosarg  = arg * FRESNEL_SINE_ASYML_08 + FRESNEL_SINE_ASYML_06;
        cosarg  = arg * cosarg + FRESNEL_SINE_ASYML_04;
        cosarg  = arg * cosarg + FRESNEL_SINE_ASYML_02;
        cosarg  = arg * cosarg + FRESNEL_SINE_ASYML_00;
        cosarg *= cos_x_squared;

        sinarg  = arg * FRESNEL_SINE_ASYML_09 + FRESNEL_SINE_ASYML_07;
        sinarg  = arg * sinarg + FRESNEL_SINE_ASYML_05;
        sinarg  = arg * sinarg + FRESNEL_SINE_ASYML_03;
        sinarg  = arg * sinarg + FRESNEL_SINE_ASYML_01;
        sinarg *= sin_x_squared;

        sx = cosarg + sinarg;
        sx *= x;

        if (x > 0.0L)
            sx += tmpl_Sqrt_Pi_By_Eight_L;
        else
            sx -= tmpl_Sqrt_Pi_By_Eight_L;
    }

    /*  For large values, return the limit of S(x) as x -> +/- infinity.      */
    else
    {
        if (x > 0.0L)
            sx = tmpl_Sqrt_Pi_By_Eight_L;
        else
            sx = -tmpl_Sqrt_Pi_By_Eight_L;
    }

    return sx;
}
/*  End of tmpl_LDouble_Fresnel_Sin.                                          */
