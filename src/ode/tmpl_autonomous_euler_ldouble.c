#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Numerical ODE routine using Euler for autonomous equations, x'(t) = f(x). */
TMPL_CONST_FUNC
long double
tmpl_LDouble_Autonomous_Euler(const tmpl_FunctionLongDouble f,
                              const long double x,
                              const long double h)
TMPL_UNSEQUENCED
{
    /*  Since dx / dt = f(x), the slope is simply f(x).                       */
    const long double slope = f(x);

    /*  The next point is obtained by stepping forward by h using the slope.  */
    return x + h * slope;
}
/*  End of tmpl_LDouble_Autonomous_Euler.                                     */
