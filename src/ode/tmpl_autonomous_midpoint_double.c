#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using midpoint RK2 for autonomous equations, x'(t) = f(x).    */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_Midpoint(const tmpl_FunctionDouble f,
                                const double x,
                                const double h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const double dx0 = f(x);

    /*  Compute the midpoint and the slope at the midpoint.                   */
    const double x1 = x + 0.5 * h * dx0;
    const double dx1 = f(x1);

    /*  Use the midpoint slope to update.                                     */
    return x + h * dx1;
}
/*  End of tmpl_Double_Autonomous_Midpoint.                                   */
