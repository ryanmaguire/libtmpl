#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  ODE routine using midpoint RK2 for autonomous equations, x'(t) = f(x).    */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Midpoint(const tmpl_FunctionLongDouble f,
                                 const long double x,
                                 const long double h)
TMPL_UNSEQUENCED
{
    /*  The Euler step, the slope at the start of the interval.               */
    const long double dx0 = f(x);

    /*  Compute the midpoint and the slope at the midpoint.                   */
    const long double x1 = x + 0.5L * h * dx0;
    const long double dx1 = f(x1);

    /*  Use the midpoint slope to update.                                     */
    return x + h * dx1;
}
/*  End of tmpl_LDouble_Autonomous_Midpoint.                                  */
