/*  Header file where the prototypes for these functions are defined.         */
#include <libtmpl/include/tmpl_config.h>
#include <libtmpl/include/tmpl_math_private.h>

/*  Only compile if the user requested these algorithms.                      */
#if __TMPL_USE_IEEE754_ALGORITHMS__ != 0

float tmpl_do_sinf(float x)
{
    float x2, sin_x;
    x2 = x*x;

    sin_x = tmpl_sinf_taylor_coeffs[1]*x2 + tmpl_sinf_taylor_coeffs[0];
    sin_x = x*sin_x;
    return sin_x;
}

double tmpl_do_sin(double x)
{
    double x2, sin_x;

    x2 = x*x;

    sin_x = tmpl_sin_taylor_coeffs[3]*x2 + tmpl_sin_taylor_coeffs[2];
    sin_x = x2*sin_x + tmpl_sin_taylor_coeffs[1];
    sin_x = x2*sin_x + tmpl_sin_taylor_coeffs[0];

    sin_x = x*sin_x;
    return sin_x;
}

long double tmpl_do_sinl(long double x)
{
    long double x2, sin_x;

    x2 = x*x;

    sin_x = tmpl_sinl_taylor_coeffs[4]*x2 + tmpl_sinl_taylor_coeffs[3];
    sin_x = x2*sin_x + tmpl_sinl_taylor_coeffs[2];
    sin_x = x2*sin_x + tmpl_sinl_taylor_coeffs[1];
    sin_x = x2*sin_x + tmpl_sinl_taylor_coeffs[0];

    sin_x = x*sin_x;
    return sin_x;
}

float tmpl_do_cosf(float x)
{
    float x2, cos_x;
    x2 = x*x;

    cos_x = tmpl_cosf_taylor_coeffs[1]*x2 + tmpl_cosf_taylor_coeffs[0];
    return cos_x;
}

double tmpl_do_cos(double x)
{
    double x2, cos_x;

    x2 = x*x;

    cos_x = tmpl_cos_taylor_coeffs[3]*x2 + tmpl_cos_taylor_coeffs[2];
    cos_x = x2*cos_x + tmpl_cos_taylor_coeffs[1];
    cos_x = x2*cos_x + tmpl_cos_taylor_coeffs[0];

    return cos_x;
}

long double tmpl_do_cosl(long double x)
{
    long double x2, cos_x;

    x2 = x*x;

    cos_x = tmpl_cosl_taylor_coeffs[4]*x2 + tmpl_cosl_taylor_coeffs[3];
    cos_x = x2*cos_x + tmpl_cosl_taylor_coeffs[2];
    cos_x = x2*cos_x + tmpl_cosl_taylor_coeffs[1];
    cos_x = x2*cos_x + tmpl_cosl_taylor_coeffs[0];

    return cos_x;
}

#endif
/*  End of #if __TMPL_USE_TRIG_ALGORITHMS__ != 0.                             */

