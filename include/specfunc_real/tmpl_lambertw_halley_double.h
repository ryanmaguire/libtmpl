#ifndef TMPL_LAMBERTW_HALLEY_DOUBLE_H
#define TMPL_LAMBERTW_HALLEY_DOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

#define TMPL_HALLEY_MAX_ITERS (10U)

/*  Computes the Lambert W function via Halley's method for double precision. */
TMPL_STATIC_INLINE
double tmpl_Double_LambertW_Halley(double x, double x0, double tol)
{
    unsigned int n;
    double exp_x0 = tmpl_Double_Exp(x0);
    double s = x0 + 1.0;
    double t = x0*exp_x0 - x;
    double dx = t / (exp_x0*s - 0.5*(s + 1.0)*t/s);

    for (n = 0U; n < TMPL_HALLEY_MAX_ITERS; ++n)
    {
        if (tmpl_Double_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_Double_Exp(x0);
        s = x0 + 1.0;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5*(s + 1.0)*t/s);
    }

    return x0 - dx;
}
/*  End of tmpl_Double_LambertW_Halley.                                       */

#undef TMPL_HALLEY_MAX_ITERS

#endif
