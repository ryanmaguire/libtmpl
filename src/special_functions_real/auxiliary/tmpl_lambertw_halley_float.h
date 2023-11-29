#ifndef TMPL_LAMBERTW_HALLEY_FLOAT_H
#define TMPL_LAMBERTW_HALLEY_FLOAT_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

#define TMPL_HALLEY_MAX_ITERS (8U)

/*  Computes the Lambert W function via Halley's method for single precision. */
TMPL_STATIC_INLINE
float tmpl_Float_LambertW_Halley(float x, float x0, float tol)
{
    unsigned int n;
    float exp_x0 = tmpl_Float_Exp(x0);
    float s = x0 + 1.0F;
    float t = x0*exp_x0 - x;
    float dx = t / (exp_x0*s - 0.5F*(s + 1.0F)*t/s);

    for (n = 0U; n < TMPL_HALLEY_MAX_ITERS; ++n)
    {
        if (tmpl_Float_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_Float_Exp(x0);
        s = x0 + 1.0F;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5F*(s + 1.0F)*t/s);
    }

    return x0 - dx;
}
/*  End of tmpl_Float_LambertW_Halley.                                        */

#undef TMPL_HALLEY_MAX_ITERS

#endif
