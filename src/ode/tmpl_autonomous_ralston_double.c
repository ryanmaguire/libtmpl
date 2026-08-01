#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using Ralston's RK2 for autonomous equations, x'(t) = f(x).   */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_Ralston(const tmpl_FunctionDouble f,
                               const double x,
                               const double h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const double dx0 = f(x);

    /*  Compute the next point and the slope there.                           */
    const double x1 = x + 2.0 * h * dx0 / 3.0;
    const double dx1 = f(x1);

    /*  Use the weighted average of the two slopes that have been computed.   */
    return x + h * (0.25 * dx0 + 0.75 * dx1);
}
/*  End of tmpl_Double_Autonomous_Ralston.                                    */
