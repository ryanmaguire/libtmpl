#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using midpoint RK2 for autonomous equations, x'(t) = f(x).    */
TMPL_CONST_FUNC
float
tmpl_Float_Autonomous_Midpoint(const tmpl_FunctionFloat f,
                               const float x,
                               const float h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const float dx0 = f(x);

    /*  Compute the midpoint and the slope at the midpoint.                   */
    const float x1 = x + 0.5 * h * dx0;
    const float dx1 = f(x1);

    /*  Use the midpoint slope to update.                                     */
    return x + h * dx1;
}
/*  End of tmpl_Float_Autonomous_Midpoint.                                    */
