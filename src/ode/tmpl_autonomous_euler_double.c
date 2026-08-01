#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/tmpl_ode.h>

/*  Numerical ODE routine using Euler for autonomous equations, x'(t) = f(x). */
TMPL_CONST_FUNC
double
tmpl_Double_Autonomous_Euler(const tmpl_FunctionDouble f,
                             const double x,
                             const double h)
TMPL_UNSEQUENCED
{
    /*  Since dx / dt = f(x), the slope is simply f(x).                       */
    const double slope = f(x);

    /*  The next point is obtained by stepping forward by h using the slope.  */
    return x + h * slope;
}
/*  End of tmpl_Double_Autonomous_Euler.                                      */
