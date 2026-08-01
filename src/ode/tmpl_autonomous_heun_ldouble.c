#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using Heun's RK2 for autonomous equations, x'(t) = f(x).      */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Heun(const tmpl_FunctionLongDouble f,
                             const long double x,
                             const long double h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const long double dx0 = f(x);

    /*  Compute the next point and the slope there.                           */
    const long double x1 = x + h * dx0;
    const long double dx1 = f(x1);

    /*  Use the average of the two slopes that have been computed.            */
    return x + 0.5L * h * (dx0 + dx1);
}
/*  End of tmpl_LDouble_Autonomous_Heun.                                      */
