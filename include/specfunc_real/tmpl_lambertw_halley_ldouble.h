#ifndef TMPL_LAMBERTW_HALLEY_LDOUBLE_H
#define TMPL_LAMBERTW_HALLEY_LDOUBLE_H

/*  TMPL_STATIC_INLINE macro found here.                                      */
#include <libtmpl/include/tmpl_config.h>

/*  Exp kernel found here, as is the square root function.                    */
#include <libtmpl/include/tmpl_math.h>

#define TMPL_HALLEY_MAX_ITERS (14U)

/*  Computes the Lambert W function via Halley's method for long double.      */
TMPL_STATIC_INLINE
long double
tmpl_LDouble_LambertW_Halley(long double x, long double x0, long double tol)
{
    unsigned int n;
    long double exp_x0 = tmpl_LDouble_Exp(x0);
    long double s = x0 + 1.0L;
    long double t = x0*exp_x0 - x;
    long double dx = t / (exp_x0*s - 0.5L*(s + 1.0L)*t/s);

    for (n = 0U; n < TMPL_HALLEY_MAX_ITERS; ++n)
    {
        if (tmpl_LDouble_Abs(dx) < tol)
            break;

        x0 = x0 - dx;
        exp_x0 = tmpl_LDouble_Exp(x0);
        s = x0 + 1.0L;
        t = x0*exp_x0 - x;
        dx = t / (exp_x0*s - 0.5L*(s + 1.0L)*t/s);
    }

    return x0 - dx;
}
/*  End of tmpl_LDouble_LambertW_Halley.                                      */

#undef TMPL_HALLEY_MAX_ITERS

#endif
