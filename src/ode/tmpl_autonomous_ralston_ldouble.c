#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using Ralston's RK2 for autonomous equations, x'(t) = f(x).   */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Ralston(const tmpl_FunctionLongDouble f,
                                const long double x,
                                const long double h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const long double dx0 = f(x);

    /*  Compute the next point and the slope there.                           */
    const long double x1 = x + 2.0L * h * dx0 / 3.0L;
    const long double dx1 = f(x1);

    /*  Use the weighted average of the two slopes that have been computed.   */
    return x + h * (0.25L * dx0 + 0.75L * dx1);
}
/*  End of tmpl_LDouble_Autonomous_Ralston.                                   */
